/* ----------------------------------------------------------------------
 *
 * Bleed colors from non-background colors into the background
 *
 * By Scott Pakin <scott+pbm@pakin.org>
 *
 * ----------------------------------------------------------------------
 *
 * Copyright (C) 2010 Scott Pakin <scott+pbm@pakin.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses/.
 *
 * ----------------------------------------------------------------------
 */

/*
  This program contains code to work with Openmp, so that it can process
  multiple columns at once, using multiple threads on multiple CPU cores,
  and thus take less elapsed time to run.

  But that code is dead in a normal Netpbm build, as it does not use the
  required compiler options or link with the required library in any
  conventional environment we know of.  One can exploit this code with a
  modified build, e.g. with CADD and LADD make variables.

  10.04.14
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "mallocvar.h"
#include "nstring.h"
#include "shhopt.h"
#include "pam.h"
#include "pammap.h"


static time_t const timeUpdateDelta = 30;
    /* Seconds between progress updates */
static int const    minUpdates = 4;
    /* Minimum number of progress updates to output */


struct cmdlineInfo {
    /* This structure represents all of the information the user
       supplied in the command line but in a form that's easy for the
       program to use.
    */
    const char * inputFilename;  /* '-' if stdin */
    const char * bgcolor;
    unsigned int wrap;
    unsigned int all;
    float        power;
    unsigned int downsample;
};

struct coords {
    /* This structure represents an (x,y) coordinate within an image and
       the color at that coordinate. */
    unsigned int x;
    unsigned int y;
    tuple        color;
};

typedef double distFunc_t(const struct coords * const p0,
                          const struct coords * const p1,
                          unsigned int          const width,
                          unsigned int          const height);
    /* Distance function */



static void
parseCommandLine(int argc, const char ** const argv,
                 struct cmdlineInfo * const cmdlineP ) {

    optEntry     * option_def;
        /* Instructions to OptParseOptions3 on how to parse our options */
    optStruct3     opt;
    unsigned int   option_def_index;
    unsigned int bgcolorSpec, powerSpec, downsampleSpec;

    MALLOCARRAY_NOFAIL(option_def, 100);
    option_def_index = 0;          /* Incremented by OPTENTRY */

    OPTENT3(0, "bgcolor",    OPT_STRING, &cmdlineP->bgcolor,    
            &bgcolorSpec, 0);
    OPTENT3(0, "wrap",       OPT_FLAG,   NULL,
            &cmdlineP->wrap,       0);
    OPTENT3(0, "all",        OPT_FLAG,   NULL,
            &cmdlineP->all,        0);
    OPTENT3(0, "power",      OPT_FLOAT,  &cmdlineP->power,      
            &powerSpec, 0);
    OPTENT3(0, "downsample", OPT_UINT,   &cmdlineP->downsample, 
            &downsampleSpec, 0);

    opt.opt_table = option_def;
    opt.short_allowed = 0;
    opt.allowNegNum = 1;

    pm_optParseOptions3( &argc, (char **)argv, opt, sizeof(opt), 0 );

    if (!bgcolorSpec)
        cmdlineP->bgcolor = NULL;

    if (!powerSpec)
        cmdlineP->power = -2.0;

    if (!downsampleSpec)
        cmdlineP->downsample = 0;

    if (argc-1 < 1)
        cmdlineP->inputFilename = "-";
    else {
        cmdlineP->inputFilename = argv[1];
        if (argc-1 > 1)
            pm_error("Too many arguments: %u.  The only argument is the "
                     "optional input file name", argc-1);
    }
}


static bool
tupleEqualColor(const struct pam * const pamP,
                tuple              const comparand,
                tuple              const comparator) {
/*----------------------------------------------------------------------------
  Report whether two tuples have equal color, regardless of alpha.
----------------------------------------------------------------------------*/
    unsigned int const nColorPlanes = pamP->depth >= 3 ? 3 : 1;

    unsigned int plane;

    for (plane = 0; plane < nColorPlanes; ++plane)
        if (comparand[plane] != comparator[plane])
            return false;

    return true;
}



struct paintSourceSet {
    struct coords * list;  /* malloc'ed */
        /* The list of places in the image from which paint comes */
    unsigned int size;
        /* Number of entries in sources[] */
    unsigned int alloc;
        /* Number of slots for entries of allocated memory */
};



static void
setPaintSourceColors(struct pam *          const pamP,
                     tuple **              const tuples,
                     struct paintSourceSet const paintSources) {
/*----------------------------------------------------------------------------
   Set the 'color' member of each source in 'paintSources'.

   Set it to the color of the source pixel in tuples[][], indicated by
   'paintSources'.

   Malloc memory to store these colors -- a contiguous block of memory for all
   of them.
-----------------------------------------------------------------------------*/
    struct pam pamPaint;
        /* numPaintSources-wide PAM for use by pnm_allocpamrow() */
    tuple * paintColor;
        /* Points to storage for the color tuples */
    unsigned int    i;

    pamPaint = *pamP;
    pamPaint.width = paintSources.size;
    paintColor = pnm_allocpamrow(&pamPaint);

    for (i = 0; i < paintSources.size; ++i) {
        struct coords * const thisSourceP = &paintSources.list[i];

        thisSourceP->color = paintColor[i];
        pnm_assigntuple(pamP, thisSourceP->color,
                        tuples[thisSourceP->y][thisSourceP->x]);
    }
}



static void
addPaintSource(unsigned int            const row,
               unsigned int            const col,
               struct paintSourceSet * const paintSourcesP) {

    if (paintSourcesP->size == paintSourcesP->alloc) {
        paintSourcesP->alloc += 1024;
        REALLOCARRAY(paintSourcesP->list, paintSourcesP->alloc);
        if (!paintSourcesP->list)
            pm_error("Out of memory");
    }
    paintSourcesP->list[paintSourcesP->size].x = col;
    paintSourcesP->list[paintSourcesP->size].y = row;
    ++paintSourcesP->size;
}



static void
locatePaintSources(struct pam *            const pamP,
                   tuple **                const tuples,
                   tuple                   const bgColor,
                   unsigned int            const downsample,
                   struct paintSourceSet * const paintSourcesP) {
/*--------------------------------------------------------------------
  Construct a list of all pixel coordinates in the input image that
  represent a non-background color.
  ----------------------------------------------------------------------*/
    struct paintSourceSet paintSources;
    int row;  /* signed so it works with Openmp */

    paintSources.list  = NULL;
    paintSources.size  = 0;
    paintSources.alloc = 0;

    #pragma omp parallel for
    for (row = 0; row < pamP->height; ++row) {
        unsigned int col;
        for (col = 0; col < pamP->width; ++col) {
            if (!tupleEqualColor(pamP, tuples[row][col], bgColor))
                #pragma omp critical (addPaintSource)
                addPaintSource(row, col, &paintSources);
        }
    }

    pm_message("Image contains %u background + %u non-background pixels",
               pamP->width * pamP->height - paintSources.size,
               paintSources.size);
    
    /* Reduce the number of paint sources to reduce execution time. */
    if (downsample > 0 && downsample < paintSources.size) {
        unsigned int i;

        srand(time(NULL));

        for (i = 0; i < downsample; ++i) {
            unsigned int const swapIdx =
                i + rand() % (paintSources.size - i);
            struct coords const swapVal = paintSources.list[i];

            paintSources.list[i] = paintSources.list[swapIdx];
            paintSources.list[swapIdx] = swapVal;
        }
        paintSources.size = downsample;
    }

    setPaintSourceColors(pamP, tuples, paintSources);

    *paintSourcesP    = paintSources;
}



static distFunc_t euclideanDistanceSqr;

static double
euclideanDistanceSqr(const struct coords * const p0,
                     const struct coords * const p1,
                     unsigned int          const width,
                     unsigned int          const height) {
/*----------------------------------------------------------------------------
   Return the square of the Euclidian distance between p0 and p1.
-----------------------------------------------------------------------------*/
    double const deltax = (double) (int) (p1->x - p0->x);
    double const deltay = (double) (int) (p1->y - p0->y);

    return SQR(deltax) + SQR(deltay);
}



static distFunc_t euclideanDistanceTorusSqr;

static double
euclideanDistanceTorusSqr(const struct coords * const p0,
                          const struct coords * const p1,
                          unsigned int          const width,
                          unsigned int          const height) {
/*----------------------------------------------------------------------------
   Return the square of the Euclidian distance between p0 and p1, assuming
   it's a toroidal surface on which the top row curves around to meet the
   bottom and the left column to the right.
-----------------------------------------------------------------------------*/
    struct coords p0Adj, p1Adj;

    if (p1->x >= p0->x + width / 2) {
        p0Adj.x = p0->x + width;
        p1Adj.x = p1->x;
    } else if (p0->x >= p1->x + width / 2) {
        p0Adj.x = p0->x;
        p1Adj.x = p1->x + width;
    } else {
        p0Adj.x = p0->x;
        p1Adj.x = p1->x;
    }
    if (p1->y >= p0->y + height / 2) {
        p0Adj.y = p0->y + height;
        p1Adj.y = p1->y;
    } else if (p0->y >= p1->y + height / 2) {
        p0Adj.y = p0->y;
        p1Adj.y = p1->y + height;
    } else {
        p0Adj.y = p0->y;
        p1Adj.y = p1->y;
    }

    return euclideanDistanceSqr(&p0Adj, &p1Adj, 0, 0);
}



static void
reportProgress(unsigned int const rowsComplete,
               unsigned int const height) {

    static time_t prevOutputTime = 0;
    time_t        now;                  /* Current time in seconds */

    if (prevOutputTime == 0)
        prevOutputTime = time(NULL);

    /* Output our progress only every timeUpdateDelta seconds. */
    now = time(NULL);
    if (prevOutputTime) {
        if (now - prevOutputTime >= timeUpdateDelta
            || rowsComplete % (height/minUpdates) == 0) {
            pm_message("%5.1f%% complete",
                       rowsComplete * 100.0 / height);
            prevOutputTime = now;
        }
    } else
        prevOutputTime = now;
}



static void
spillOnePixel(struct pam *          const pamP,
              struct coords         const target,
              struct paintSourceSet const paintSources,
              distFunc_t *          const distFunc,
              double                const distPower,
              tuple                 const outTuple,
              double *              const newColor) {

    unsigned int plane;
    unsigned int ps;
    double       totalWeight;

    for (plane = 0; plane < pamP->depth; ++plane)
        newColor[plane] = 0.0;
    totalWeight = 0.0;
    for (ps = 0; ps < paintSources.size; ++ps) {
        struct coords const source = paintSources.list[ps];
        double const distSqr =
            (*distFunc)(&target, &source,
                        pamP->width, pamP->height);

        if (distSqr > 0.0) {
            /* We do special cases for some common cases with code
               that is much faster than pow().
            */
            double const weight =
                distPower == -2.0 ? 1.0 / distSqr :
                distPower == -1.0 ? 1.0 / sqrt(distSqr):
                pow(distSqr, distPower/2);

            unsigned int plane;

            for (plane = 0; plane < pamP->depth; ++plane)
                newColor[plane] += weight * source.color[plane];

            totalWeight += weight;
        }
    }
    for (plane = 0; plane < pamP->depth; ++plane)
        outTuple[plane] = (sample) (newColor[plane] / totalWeight);
}



static void
produceOutputImage(struct pam *          const pamP,
                   tuple **              const intuples,
                   tuple                 const bgColor,
                   struct paintSourceSet const paintSources,
                   distFunc_t *          const distFunc,
                   double                const distPower,
                   bool                  const all,
                   tuple ***             const outtuplesP) {
/*--------------------------------------------------------------------
  Color each background pixel (or, if allPixels is 1, all pixels)
  using a fraction of each paint source as determined by its distance
  to the background pixel.
----------------------------------------------------------------------*/
    int row;   /* signed so it works with Openmp */
    unsigned int rowsComplete;
    tuple ** outtuples;

    outtuples = pnm_allocpamarray(pamP);

    rowsComplete = 0;
    #pragma omp parallel for
    for (row = 0; row < pamP->height; ++row) {
        struct coords   target;
        double        * newColor;
        
        MALLOCARRAY(newColor, pamP->depth);

        target.y = row;
        for (target.x = 0; target.x < pamP->width; ++target.x) {
            tuple const targetTuple = intuples[target.y][target.x];
            tuple const outputTuple = outtuples[target.y][target.x];

            if (all || tupleEqualColor(pamP, targetTuple, bgColor))
                spillOnePixel(pamP, target, paintSources, distFunc, distPower,
                              outputTuple, newColor);
            else
                pnm_assigntuple(pamP,  outputTuple, targetTuple);
        }
        #pragma omp critical (rowTally)
        reportProgress(++rowsComplete, pamP->height);

        free(newColor);
    }
    *outtuplesP = outtuples;
}



int
main(int argc, const char *argv[]) {
    FILE *             ifP;
    struct cmdlineInfo cmdline;          /* Command-line parameters */
    tuple              bgColor;          /* Input image's background color */
    struct paintSourceSet paintSources;
        /* The set of paint-source indexes into 'tuples' */
    distFunc_t *       distFunc;         /* The distance function */
    struct pam inPam;
    struct pam outPam;
    tuple ** inTuples;
    tuple ** outTuples;

    pm_proginit(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    ifP = pm_openr(cmdline.inputFilename);

    inTuples = pnm_readpam(ifP, &inPam, PAM_STRUCT_SIZE(allocation_depth));

    pm_close(ifP);

    distFunc = cmdline.wrap ? euclideanDistanceTorusSqr : euclideanDistanceSqr;

    if (cmdline.bgcolor)
        bgColor = pnm_parsecolor(cmdline.bgcolor, inPam.maxval) ;
    else
        bgColor = pnm_backgroundtuple(&inPam, inTuples);

    pm_message("Treating %s as the background color",
               pnm_colorname(&inPam, bgColor, PAM_COLORNAME_HEXOK));

    locatePaintSources(&inPam, inTuples, bgColor, cmdline.downsample,
                       &paintSources);

    produceOutputImage(&inPam, inTuples, bgColor, paintSources, distFunc,
                       cmdline.power, cmdline.all, &outTuples);

    outPam = inPam;
    outPam.file = stdout;
    pnm_writepam(&outPam, outTuples);

    pnm_freepamarray(outTuples, &inPam);
    pnm_freepamarray(inTuples, &outPam);

    return 0;
}
