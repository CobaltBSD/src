/******************************************************************************
                               pnmremap.c
*******************************************************************************

  Replace colors in an input image with colors from a given colormap image.

  For PGM input, do the equivalent.

  By Bryan Henderson, San Jose, CA 2001.12.17

  Derived from ppmquant, originally by Jef Poskanzer.

  Copyright (C) 1989, 1991 by Jef Poskanzer.
  Copyright (C) 2001 by Bryan Henderson.

  Permission to use, copy, modify, and distribute this software and its
  documentation for any purpose and without fee is hereby granted, provided
  that the above copyright notice appear in all copies and that both that
  copyright notice and this permission notice appear in supporting
  documentation.  This software is provided "as is" without express or
  implied warranty.
******************************************************************************/

#include <limits.h>
#include <math.h>
#include <assert.h>

#include "pm_c_util.h"
#include "mallocvar.h"
#include "nstring.h"
#include "shhopt.h"
#include "pam.h"
#include "ppm.h"
#include "pammap.h"

#define MAXCOLORS 32767u

enum MissingMethod {
    MISSING_FIRST,
    MISSING_SPECIFIED,
    MISSING_CLOSE
};

struct CmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    const char * inputFilespec;  /* Filespec of input file */
    const char * mapFilespec;    /* Filespec of colormap file */
    unsigned int floyd;   /* Boolean: -floyd/-fs option */
    unsigned int norandom;
    enum MissingMethod missingMethod;
    char * missingcolor;      
        /* -missingcolor value.  Null if not specified */
    unsigned int verbose;
};



static void
parseCommandLine (int argc, const char ** argv,
                  struct CmdlineInfo * const cmdlineP) {
/*----------------------------------------------------------------------------
   parse program command line described in Unix standard form by argc
   and argv.  Return the information in the options as *cmdlineP.  

   If command line is internally inconsistent (invalid options, etc.),
   issue error message to stderr and abort program.

   Note that the strings we return are stored in the storage that
   was passed to us as the argv array.  We also trash *argv.
-----------------------------------------------------------------------------*/
    optEntry * option_def;
        /* Instructions to pm_optParseOptions3 on how to parse our options.
         */
    optStruct3 opt;

    unsigned int option_def_index;

    unsigned int nofloyd, firstisdefault;
    unsigned int missingSpec, mapfileSpec;

    MALLOCARRAY_NOFAIL(option_def, 100);
    
    option_def_index = 0;   /* incremented by OPTENT3 */
    OPTENT3(0,   "floyd",          OPT_FLAG,   
            NULL,                       &cmdlineP->floyd,    0);
    OPTENT3(0,   "fs",             OPT_FLAG,   
            NULL,                       &cmdlineP->floyd,    0);
    OPTENT3(0,   "nofloyd",        OPT_FLAG,   
            NULL,                       &nofloyd,            0);
    OPTENT3(0,   "nofs",           OPT_FLAG,   
            NULL,                       &nofloyd,            0);
    OPTENT3(0,   "norandom",       OPT_FLAG,   
            NULL,                       &cmdlineP->norandom, 0);
    OPTENT3(0,   "firstisdefault", OPT_FLAG,   
            NULL,                       &firstisdefault,     0);
    OPTENT3(0,   "mapfile",        OPT_STRING, 
            &cmdlineP->mapFilespec,    &mapfileSpec,         0);
    OPTENT3(0,   "missingcolor",   OPT_STRING, 
            &cmdlineP->missingcolor,   &missingSpec,         0);
    OPTENT3(0, "verbose",          OPT_FLAG,   NULL,                  
            &cmdlineP->verbose,                              0);

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = FALSE;  /* We have no parms that are negative numbers */

    cmdlineP->missingcolor = NULL;  /* default value */
    
    pm_optParseOptions3(&argc, (char **)argv, opt, sizeof(opt), 0);
        /* Uses and sets argc, argv, and some of *cmdline_p and others. */

    if (cmdlineP->floyd && nofloyd)
        pm_error("You cannot specify both -floyd and -nofloyd options.");

    if (firstisdefault && missingSpec)
        pm_error("You cannot specify both -missing and -firstisdefault.");

    if (firstisdefault)
        cmdlineP->missingMethod = MISSING_FIRST;
    else if (missingSpec)
        cmdlineP->missingMethod = MISSING_SPECIFIED;
    else
        cmdlineP->missingMethod = MISSING_CLOSE;

    if (!mapfileSpec)
        pm_error("You must specify the -mapfile option.");

    if (argc-1 > 1)
        pm_error("Program takes at most one argument: the input file "
                 "specification.  "
                 "You specified %d arguments.", argc-1);
    if (argc-1 < 1)
        cmdlineP->inputFilespec = "-";
    else
        cmdlineP->inputFilespec = argv[1];

    free(option_def);
}


typedef enum {
    ADJUST_NONE,
    ADJUST_RGBTO1,
    ADJUST_GRAYSCALETO3
} depthAdjustment;



static void
rgbToDepth1(tuple const tuple) {

    unsigned int plane;
    double grayvalue;

    grayvalue = 0.0;  /* initial value */

    for (plane = 0; plane < 3; ++plane)
        grayvalue += pnm_lumin_factor[plane] * tuple[plane];

    tuple[0] = (sample) (grayvalue + 0.5);
}



static void
grayscaleToDepth3(tuple const tuple) {

    tuple[1] = tuple[0];
    tuple[2] = tuple[0];
}



static void
adjustDepthTuple(tuple           const tuple,
                 depthAdjustment const adjustment) {
    
    switch (adjustment) {
    case ADJUST_NONE:
        break;
    case ADJUST_RGBTO1:
        rgbToDepth1(tuple);
        break;
    case ADJUST_GRAYSCALETO3:
        grayscaleToDepth3(tuple);
        break;
    }
}



static void
inverseAdjustDepthTuple(tuple           const tuple,
                        depthAdjustment const adjustment) {
    
    switch (adjustment) {
    case ADJUST_NONE:
        break;
    case ADJUST_RGBTO1:
        grayscaleToDepth3(tuple);
        break;
    case ADJUST_GRAYSCALETO3:
        rgbToDepth1(tuple);
        break;
    }
}



static void
adjustDepthRow(tuple *         const tupleRow,
               unsigned int    const width,
               depthAdjustment const adjustment) {
/*----------------------------------------------------------------------------
   Change tupleRow[] depth as indicated by 'adjustment',
   i.e. turned from RGB to grayscale or grayscale to RGB.

   We assume tupleRow[] is consistent with 'adjustment' -- i.e. if
   'adjustment' says grayscale to RGB, tupleRow[] has an allocation depth of
   at least 3 and if 'adjustment' says from RGB to grayscale, tupleRow[] has
   RGB tuples.
-----------------------------------------------------------------------------*/
    if (adjustment == ADJUST_NONE) {
    } else {
        unsigned int col;

        for (col = 0; col < width; ++col) {
            if (adjustment == ADJUST_RGBTO1)
                rgbToDepth1(tupleRow[col]);
            else {
                assert(adjustment == ADJUST_GRAYSCALETO3);
                grayscaleToDepth3(tupleRow[col]);
            }
        }
    }
}



static void
selectDepthAdjustment(const struct pam * const pamP,
                      unsigned int       const newDepth,
                      depthAdjustment *  const adjustmentP) {
/*----------------------------------------------------------------------------
   Determine what kind of depth adjustment the pixels of an image described
   by 'pamP' need to be comparable to pixels with depth 'newDepth'.

   The only depth changes we know how to do are:

     - from tuple type RGB, depth 3 to depth 1 

       We change it to grayscale or black and white.

       For this, we return *adjustmentP == ADJUST_RGBTO1.

     - from tuple type GRAYSCALE or BLACKANDWHITE depth 1 to depth 3.

       We change it to RGB.

       For this, we return *adjustmentP == ADJUST_GRAYSCALETO3.

   For any other depth change request, we issue an error message and abort
   the program.

   If 'newDepth' is the same depth as the original (no depth change required),
   we return *adjustmentP == ADJUST_NONE.
-----------------------------------------------------------------------------*/
    if (newDepth == pamP->depth)
        *adjustmentP = ADJUST_NONE;
    else {
        if (pm_stripeq(pamP->tuple_type, "RGB")) {
            if (newDepth != 1) {
                pm_error("Map image depth of %u differs from input image "
                         "depth of %u, and the tuple type is RGB.  "
                         "The only depth to which I know how to convert "
                         "an RGB tuple is 1.",
                         newDepth, pamP->depth);
            } else
                *adjustmentP = ADJUST_RGBTO1;
        } else if (pm_stripeq(pamP->tuple_type, "GRAYSCALE") ||
                   pm_stripeq(pamP->tuple_type, "BLACKANDWHITE")) {
            if (newDepth != 3) {
                pm_error("Map image depth of %u differs from input image "
                         "depth of %u, and the tuple type is GRAYSCALE "
                         "or BLACKANDWHITE.  "
                         "The only depth to which I know how to convert "
                         "a GRAYSCALE or BLACKANDWHITE tuple is 3.",
                         newDepth, pamP->depth);
            } else
                *adjustmentP = ADJUST_GRAYSCALETO3;
        } else {
            pm_error("Map image depth of %u differs from input image depth "
                     "of %u, and the input image does not have a tuple type "
                     "that I know how to convert to the map depth.  "
                     "I can convert RGB, GRAYSCALE, and BLACKANDWHITE.  "
                     "The input image is '%.*s'.",
                     newDepth, pamP->depth, 
                     (int)sizeof(pamP->tuple_type), pamP->tuple_type);
        }
    }
}



static void
computeColorMapFromMap(struct pam *   const mappamP, 
                       tuple **       const maptuples, 
                       tupletable *   const colormapP,
                       unsigned int * const newcolorsP) {
/*----------------------------------------------------------------------------
   Produce a colormap containing the colors that we will use in the output.

   Make it include exactly those colors that are in the image
   described by *mappamP and maptuples[][].

   Return the number of colors in the returned colormap as *newcolorsP.
-----------------------------------------------------------------------------*/
    unsigned int colors; 

    if (mappamP->width == 0 || mappamP->height == 0)
        pm_error("colormap file contains no pixels");

    *colormapP = 
        pnm_computetuplefreqtable(mappamP, maptuples, MAXCOLORS, &colors);
    if (*colormapP == NULL)
        pm_error("too many colors in colormap!");
    pm_message("%u colors found in colormap", colors);
    *newcolorsP = colors;
}



#define FS_SCALE 1024

struct fserr {
    unsigned int width;
        /* Width of the image being dithered */
    long ** thiserr;
    long ** nexterr;
    bool    fsForward;
        /* We are in a left-to-right row */
    int     begCol;
        /* First column in the sweep.  Determined by 'fsForward': either
           the leftmost or rightmost column in the row
        */
    int     endCol;
        /* Column after the last column in the sweep.  Determined by
           'fsForward': either one past the left end or one past the right
           end of the row.
        */
    int     step;
        /* What we add to a column number to get the next one in the sweep.
           Determined by 'fsForward': +1 or -1.
        */
};



static void
randomizeError(long **      const err,
               unsigned int const width,
               unsigned int const depth) {
/*----------------------------------------------------------------------------
   Set a random error in the range [-1 .. 1] (normalized via FS_SCALE)
   in the error array err[][].
-----------------------------------------------------------------------------*/
    unsigned int col;

    srand(pm_randseed());

    for (col = 0; col < width; ++col) {
        unsigned int plane;
        for (plane = 0; plane < depth; ++plane) 
            err[plane][col] = rand() % (FS_SCALE * 2) - FS_SCALE;
    }
}



static void
zeroError(long **      const err,
          unsigned int const width,
          unsigned int const depth) {
/*----------------------------------------------------------------------------
   Set all errors to zero in the error array err[][].
-----------------------------------------------------------------------------*/
    unsigned int col;

    for (col = 0; col < width; ++col) {
        unsigned int plane;
        for (plane = 0; plane < depth; ++plane) 
            err[plane][col] = 0;
    }
}



static void
fserrSetForward(struct fserr * const fserrP) {

    fserrP->fsForward = TRUE;
    fserrP->begCol = 0;
    fserrP->endCol = fserrP->width;
    fserrP->step   = +1;
}



static void
fserrSetBackward(struct fserr * const fserrP) {

    fserrP->fsForward = FALSE;
    fserrP->begCol = fserrP->width - 1;
    fserrP->endCol = -1;
    fserrP->step   = -1;
}



static void
initFserr(struct pam *   const pamP,
          struct fserr * const fserrP,
          bool           const initRandom) {
/*----------------------------------------------------------------------------
   Initialize the Floyd-Steinberg error vectors
-----------------------------------------------------------------------------*/
    unsigned int plane;

    unsigned int const fserrSize = pamP->width + 2;

    fserrP->width = pamP->width;

    MALLOCARRAY(fserrP->thiserr, pamP->depth);
    if (fserrP->thiserr == NULL)
        pm_error("Out of memory allocating Floyd-Steinberg structures "
                 "for depth %u", pamP->depth);
    MALLOCARRAY(fserrP->nexterr, pamP->depth);
    if (fserrP->nexterr == NULL)
        pm_error("Out of memory allocating Floyd-Steinberg structures "
                 "for depth %u", pamP->depth);
    
    for (plane = 0; plane < pamP->depth; ++plane) {
        MALLOCARRAY(fserrP->thiserr[plane], fserrSize);
        if (fserrP->thiserr[plane] == NULL)
            pm_error("Out of memory allocating Floyd-Steinberg structures "
                     "for Plane %u, size %u", plane, fserrSize);
        MALLOCARRAY(fserrP->nexterr[plane], fserrSize);
        if (fserrP->nexterr[plane] == NULL)
            pm_error("Out of memory allocating Floyd-Steinberg structures "
                     "for Plane %u, size %u", plane, fserrSize);
    }

    if (initRandom)
        randomizeError(fserrP->thiserr, fserrSize, pamP->depth);
    else
        zeroError(fserrP->thiserr, fserrSize, pamP->depth);

    fserrSetForward(fserrP);
}



static void
floydInitRow(struct pam * const pamP, struct fserr * const fserrP) {

    int col;
    
    for (col = 0; col < pamP->width + 2; ++col) {
        unsigned int plane;
        for (plane = 0; plane < pamP->depth; ++plane) 
            fserrP->nexterr[plane][col] = 0;
    }
}



static void
floydAdjustColor(struct pam *   const pamP, 
                 tuple          const intuple, 
                 tuple          const outtuple, 
                 struct fserr * const fserrP, 
                 int            const col) {
/*----------------------------------------------------------------------------
  Use Floyd-Steinberg errors to adjust actual color.
-----------------------------------------------------------------------------*/
    unsigned int plane;

    for (plane = 0; plane < pamP->depth; ++plane) {
        long int const s =
            intuple[plane] + fserrP->thiserr[plane][col+1] / FS_SCALE;
        outtuple[plane] = MIN(pamP->maxval, MAX(0,s));
    }
}



static void
floydPropagateErr(struct pam *   const pamP, 
                  struct fserr * const fserrP, 
                  int            const col, 
                  tuple          const oldtuple, 
                  tuple          const newtuple) {
/*----------------------------------------------------------------------------
  Propagate Floyd-Steinberg error terms.

  The error is due to substituting the tuple value 'newtuple' for the
  tuple value 'oldtuple' (both described by *pamP).  The error terms
  are meant to be used to introduce a compensating error into the
  future selection of tuples nearby in the image.
-----------------------------------------------------------------------------*/
    unsigned int plane;
    for (plane = 0; plane < pamP->depth; ++plane) {
        long const newSample = newtuple[plane];
        long const oldSample = oldtuple[plane];
        long const err = (oldSample - newSample) * FS_SCALE;
            
        if (fserrP->fsForward) {
            fserrP->thiserr[plane][col + 2] += ( err * 7 ) / 16;
            fserrP->nexterr[plane][col    ] += ( err * 3 ) / 16;
            fserrP->nexterr[plane][col + 1] += ( err * 5 ) / 16;
            fserrP->nexterr[plane][col + 2] += ( err     ) / 16;
        } else {
            fserrP->thiserr[plane][col    ] += ( err * 7 ) / 16;
            fserrP->nexterr[plane][col + 2] += ( err * 3 ) / 16;
            fserrP->nexterr[plane][col + 1] += ( err * 5 ) / 16;
            fserrP->nexterr[plane][col    ] += ( err     ) / 16;
        }
    }
}



static void
floydSwitchDir(struct pam * const pamP, struct fserr * const fserrP) {

    unsigned int plane;

    for (plane = 0; plane < pamP->depth; ++plane) {
        long * const temperr = fserrP->thiserr[plane];
        fserrP->thiserr[plane] = fserrP->nexterr[plane];
        fserrP->nexterr[plane] = temperr;
    }

    if (fserrP->fsForward)
        fserrSetBackward(fserrP);
    else
        fserrSetForward(fserrP);
}



struct colormapFinder {
/*----------------------------------------------------------------------------
   This is an object that finds a color in a colormap.  The methods
   'searchColormapClose' and 'searchColormapExact' belong to it.

   This object ought to encompass the hash table as well some day and
   possibly encapsulate the color map altogether and just be an object
   that opaquely maps input colors to output colors.
-----------------------------------------------------------------------------*/
    tupletable colormap;
    unsigned int colors;
        /* Number of colors in 'colormap'.  At least 1 */
    unsigned int distanceDivider;
        /* The value by which our intermediate distance calculations
           have to be divided to make sure we don't overflow our
           unsigned int data structure.
           
           To the extent 'distanceDivider' is greater than 1, closest
           color results will be approximate -- there could
           conceivably be a closer one that we miss.
        */
};



static void
createColormapFinder(struct pam *             const pamP,
                     tupletable               const colormap,
                     unsigned int             const colors,
                     struct colormapFinder ** const colormapFinderPP) {

    struct colormapFinder * colormapFinderP;

    MALLOCVAR_NOFAIL(colormapFinderP);

    colormapFinderP->colormap = colormap;
    colormapFinderP->colors = colors;

    {
        unsigned int const maxHandleableSqrDiff = 
            (unsigned int)UINT_MAX / pamP->depth;
        
        if (SQR(pamP->maxval) > maxHandleableSqrDiff)
            colormapFinderP->distanceDivider = (unsigned int)
                (SQR(pamP->maxval) / maxHandleableSqrDiff + 0.1 + 1.0);
                /* The 0.1 is a fudge factor to keep us out of rounding 
                   trouble.  The 1.0 effects a round-up.
                */
        else
            colormapFinderP->distanceDivider = 1;
    }
    *colormapFinderPP = colormapFinderP;
}



static void
destroyColormapFinder(struct colormapFinder * const colormapFinderP) {

    free(colormapFinderP);
}



static void
searchColormapClose(struct pam *            const pamP,
                    tuple                   const tuple,
                    struct colormapFinder * const colorFinderP,
                    int *                   const colormapIndexP) {
/*----------------------------------------------------------------------------
   Search the colormap indicated by *colorFinderP for the color closest to
   that of tuple 'tuple'.  Return its index as *colormapIndexP.

   *pamP describes the tuple 'tuple' and *colorFinderP has to be
   compatible with it (i.e. the tuples in the color map must also be
   described by *pamP).

   We compute distance between colors simply as the cartesian distance
   between them in the RGB space.  An alternative would be to look at
   the chromaticities and luminosities of the colors.  In experiments
   in 2003, we found that this was actually worse in many cases.  One
   might think that two colors are closer if they have similar hues
   than when they are simply different brightnesses of the same hue.
   Human subjects asked to compare two colors normally say so.  But
   when replacing the color of a pixel in an image, the luminosity is
   much more important, because you need to retain the luminosity
   relationship between adjacent pixels.  If you replace a pixel with
   one that has the same chromaticity as the original, but much
   darker, it may stand out among its neighbors in a way the original
   pixel did not.  In fact, on an image with blurred edges, we saw
   ugly effects at the edges when we substituted colors using a
   chromaticity-first color closeness formula.
-----------------------------------------------------------------------------*/
    unsigned int i;
    unsigned int dist;
        /* The closest distance we've found so far between the value of
           tuple 'tuple' and a tuple in the colormap.  This is measured as
           the square of the cartesian distance between the tuples, except
           that it's divided by 'distanceDivider' to make sure it will fit
           in an unsigned int.
        */

    dist = UINT_MAX;  /* initial value */

    assert(colorFinderP->colors > 0);

    for (i = 0; i < colorFinderP->colors; ++i) {
        unsigned int newdist;  /* candidate for new 'dist' value */
        unsigned int plane;

        newdist = 0;

        for (plane=0; plane < pamP->depth; ++plane) {
            newdist += 
                SQR(tuple[plane] - colorFinderP->colormap[i]->tuple[plane]) 
                / colorFinderP->distanceDivider;
        }
        if (newdist < dist) {
            *colormapIndexP = i;
            dist = newdist;
        }
    }
}



static void
searchColormapExact(struct pam *            const pamP,
                    struct colormapFinder * const colorFinderP,
                    tuple                   const tuple,
                    int *                   const colormapIndexP,
                    bool *                  const foundP) {
/*----------------------------------------------------------------------------
   Search the colormap indicated by *colorFinderP for the color of
   tuple 'tuple'.  If it's in the map, return its index as
   *colormapIndexP and return *foundP == TRUE.  Otherwise, return
   *foundP = FALSE.

   *pamP describes the tuple 'tuple' and *colorFinderP has to be
   compatible with it (i.e. the tuples in the color map must also be
   described by *pamP).
-----------------------------------------------------------------------------*/
    unsigned int i;
    bool found;
    
    found = FALSE;  /* initial value */
    for (i = 0; i < colorFinderP->colors && !found; ++i) {
        unsigned int plane;
        found = TRUE;  /* initial assumption */
        for (plane=0; plane < pamP->depth; ++plane) 
            if (tuple[plane] != colorFinderP->colormap[i]->tuple[plane]) 
                found = FALSE;
        if (found) 
            *colormapIndexP = i;
    }
    *foundP = found;
}



static void
lookupThroughHash(struct pam *            const pamP, 
                  tuple                   const tuple, 
                  bool                    const needExactMatch,
                  struct colormapFinder * const colorFinderP,
                  tuplehash               const colorhash,       
                  int *                   const colormapIndexP,
                  bool *                  const usehashP) {
/*----------------------------------------------------------------------------
   Look up the color of tuple 'tuple' in the color map indicated by
   'colorFinderP' and, if it's in there, return its index as
   *colormapIndexP.  If not, return *colormapIndexP == -1.

   Both the tuple 'tuple' and the colors in color map 'colormap' are
   described by *pamP.

   If 'needExactMatch' isn't true, we find the closest color in the color map,
   and never return *colormapIndex == -1.

   lookaside at the hash table 'colorhash' to possibly avoid the cost of
   a full lookup.  If we do a full lookup, we add the result to 'colorhash'
   unless *usehashP is false, and if that makes 'colorhash' full, we set
   *usehashP false.
-----------------------------------------------------------------------------*/
    int found;

    /* Check hash table to see if we have already matched this color. */
    pnm_lookuptuple(pamP, colorhash, tuple, &found, colormapIndexP);
    if (!found) {
        /* No, have to do a full lookup */
        if (needExactMatch) {
            bool found;

            searchColormapExact(pamP, colorFinderP, tuple,
                                colormapIndexP, &found);
            if (!found)
                *colormapIndexP = -1;
        } else 
            searchColormapClose(pamP, tuple, colorFinderP, colormapIndexP);
        if (*usehashP) {
            int fits;
            pnm_addtotuplehash(pamP, colorhash, tuple, *colormapIndexP, 
                               &fits);
            if (!fits) {
                pm_message("out of memory adding to hash table; "
                           "proceeding without it");
                *usehashP = FALSE;
            }
        }
    }
}



static void
mapTuple(struct pam *            const pamP,
         tuple                   const inTuple,
         tuple                   const defaultColor,
         tupletable              const colormap,
         struct colormapFinder * const colorFinderP,
         tuplehash               const colorhash, 
         bool *                  const usehashP,
         tuple                   const outTuple,
         bool *                  const missingP) {

    int colormapIndex;
        /* Index into the colormap of the replacement color, or -1 if
           there is no usable color in the color map.
        */

    lookupThroughHash(pamP, inTuple, !!defaultColor, colorFinderP, 
                      colorhash, &colormapIndex, usehashP);

    if (colormapIndex == -1) {
        *missingP = TRUE;

        assert(defaultColor);  /* Otherwise, lookup would have succeeded */

        pnm_assigntuple(pamP, outTuple, defaultColor);
    } else {
        *missingP = FALSE;
        pnm_assigntuple(pamP, outTuple, colormap[colormapIndex]->tuple);
    }
}



static void
convertRowStraight(struct pam *            const inpamP,
                   struct pam *            const outpamP, 
                   tuple                         inrow[],
                   depthAdjustment         const depthAdjustment,
                   tupletable              const colormap,
                   struct colormapFinder * const colorFinderP,
                   tuplehash               const colorhash, 
                   bool *                  const usehashP,
                   tuple                   const defaultColor,
                   tuple                         outrow[],
                   unsigned int *          const missingCountP) {
/*----------------------------------------------------------------------------
  Like convertRow(), compute outrow[] from inrow[], replacing each pixel with
  the new colors.  Do a straight pixel for pixel remap; no dithering.

  Return the number of pixels that were not matched in the color map as
  *missingCountP.

  *colorFinderP is a color finder based on 'colormap' -- it tells us what
  index of 'colormap' corresponds to a certain color.
-----------------------------------------------------------------------------*/
    unsigned int col;
    unsigned int missingCount;
    
    /* The following modify tuplerow, to make it consistent with
     *outpamP instead of *inpamP.
     */
    assert(outpamP->allocation_depth >= inpamP->depth);

    pnm_scaletuplerow(inpamP, outrow, inrow, outpamP->maxval);

    adjustDepthRow(outrow, outpamP->width, depthAdjustment);

    missingCount = 0;  /* initial value */
    
    for (col = 0; col < outpamP->width; ++col) {
        bool missing;
        mapTuple(outpamP, outrow[col], defaultColor,
                 colormap, colorFinderP,
                 colorhash, usehashP, outrow[col], &missing);

        if (missing)
            ++missingCount;
    }

    *missingCountP = missingCount;
}



static void
convertRowDither(struct pam *            const inpamP,
                 struct pam *            const outpamP,
                 tuple                   const inrow[],
                 depthAdjustment         const depthAdjustment,
                 tupletable              const colormap,
                 struct colormapFinder * const colorFinderP,
                 tuplehash               const colorhash, 
                 bool *                  const usehashP,
                 tuple                   const defaultColor,
                 struct fserr *          const fserrP,
                 tuple                         outrow[],
                 unsigned int *          const missingCountP) {
/*----------------------------------------------------------------------------
  Like convertRow(), compute outrow[] from inrow[], replacing each pixel with
  the new colors.  Do a Floyd-Steinberg dither, using and updating the error
  accumulator *fserrP.

  Return the number of pixels that were not matched in the color map as
  *missingCountP.

  *colorFinderP is a color finder based on 'colormap' -- it tells us what
  index of 'colormap' corresponds to a certain color.
-----------------------------------------------------------------------------*/
    tuple const ditheredTuple = pnm_allocpamtuple(inpamP);
        /* The input tuple we're converting, adjusted by the dither */
    tuple const normTuple = pnm_allocpamtuple(outpamP);
        /* Same as above, normalized to the maxval of the output file /
           colormap.
        */
    unsigned int missingCount;
    int col;

    floydInitRow(inpamP, fserrP);

    missingCount = 0;  /* initial value */
    
    for (col = fserrP->begCol; col != fserrP->endCol; col += fserrP->step) {
        bool missing;

        floydAdjustColor(inpamP, inrow[col], ditheredTuple, fserrP, col);

        /* Convert tuple to the form of those in the colormap */
        assert(outpamP->allocation_depth >= inpamP->depth);
        pnm_scaletuple(inpamP, normTuple, ditheredTuple, outpamP->maxval);
        adjustDepthTuple(normTuple, depthAdjustment);

        mapTuple(outpamP, normTuple, defaultColor,
                 colormap, colorFinderP,
                 colorhash, usehashP, outrow[col], &missing);

        if (missing)
            ++missingCount;

        /* Convert tuple back to the form of the input, where dithering
           takes place.
        */
        pnm_scaletuple(outpamP, normTuple, outrow[col], inpamP->maxval);
        inverseAdjustDepthTuple(normTuple, depthAdjustment);

        floydPropagateErr(inpamP, fserrP, col, inrow[col], normTuple);
    }

    floydSwitchDir(inpamP, fserrP);

    pnm_freepamtuple(normTuple);
    pnm_freepamtuple(ditheredTuple);

    *missingCountP = missingCount;
}



static void
convertRow(struct pam *            const inpamP,
           struct pam *            const outpamP,
           tuple                         inrow[],
           depthAdjustment               depthAdjustment,
           tupletable              const colormap,
           struct colormapFinder * const colorFinderP,
           tuplehash               const colorhash, 
           bool *                  const usehashP,
           bool                    const floyd, 
           tuple                   const defaultColor,
           struct fserr *          const fserrP,
           tuple                         outrow[],
           unsigned int *          const missingCountP) {
/*----------------------------------------------------------------------------
  Replace the colors in row tuplerow[] (described by *inpamP) with the
  new colors and convert so it is described by *outpamP.

  Use and update the Floyd-Steinberg state *fserrP.

  Return the number of pixels that were not matched in the color map as
  *missingCountP.

  *colorFinderP is a color finder based on 'colormap' -- it tells us what
  index of 'colormap' corresponds to a certain color.

  outrow[] doubles as a work space, so we require it to have an allocation
  depth at least as great as that of inrow[].
-----------------------------------------------------------------------------*/
    /* The following both consults and adds to 'colorhash' and
       its associated '*usehashP'.  It modifies 'tuplerow' too.
    */
    if (floyd)
        convertRowDither(inpamP, outpamP, inrow,
                         depthAdjustment, colormap, colorFinderP, colorhash,
                         usehashP, defaultColor,
                         fserrP, outrow, missingCountP);
    else 
        convertRowStraight(inpamP, outpamP, inrow,
                           depthAdjustment, colormap, colorFinderP, colorhash,
                           usehashP, defaultColor,
                           outrow, missingCountP);
}



static void
copyRaster(struct pam *       const inpamP, 
           struct pam *       const outpamP,
           tupletable         const colormap, 
           unsigned int       const colormapSize,
           bool               const floyd, 
           bool               const randomize,
           tuple              const defaultColor, 
           unsigned int *     const missingCountP) {

    tuplehash const colorhash = pnm_createtuplehash();

    tuple * inrow;
    tuple * outrow;
    struct pam workpam;
        /* This is for work space we use for building up the output
           pixels.  To save time and memory, we modify them in place in a
           buffer, which ultimately holds the output pixels.  This pam
           structure is thus the same as the *outpamP, but with a tuple
           allocation depth large enough to handle intermediate results.
        */
    depthAdjustment depthAdjustment;
    struct colormapFinder * colorFinderP;
    bool usehash;
    struct fserr fserr;
    int row;

    workpam = *outpamP;
    workpam.allocation_depth = MAX(workpam.depth, inpamP->depth);
    workpam.size             = sizeof(workpam);
    workpam.len              = PAM_STRUCT_SIZE(allocation_depth);

    inrow  = pnm_allocpamrow(inpamP);
    outrow = pnm_allocpamrow(&workpam);

    if (outpamP->maxval != inpamP->maxval && defaultColor)
        pm_error("The maxval of the colormap (%u) is not equal to the "
                 "maxval of the input image (%u).  This is allowable only "
                 "if you are doing an approximate mapping (i.e. you don't "
                 "specify -firstisdefault or -missingcolor)",
                 (unsigned int)outpamP->maxval, (unsigned int)inpamP->maxval);

    selectDepthAdjustment(inpamP, outpamP->depth, &depthAdjustment);

    usehash = TRUE;

    createColormapFinder(outpamP, colormap, colormapSize, &colorFinderP);

    if (floyd)
        initFserr(inpamP, &fserr, randomize);

    *missingCountP = 0;  /* initial value */

    for (row = 0; row < inpamP->height; ++row) {
        unsigned int missingCount;

        pnm_readpamrow(inpamP, inrow);

        convertRow(inpamP, &workpam, inrow,
                   depthAdjustment, colormap, colorFinderP, colorhash,
                   &usehash, floyd, defaultColor,
                   &fserr,  outrow, &missingCount);
        
        *missingCountP += missingCount;
        
        pnm_writepamrow(outpamP, outrow);
    }
    destroyColormapFinder(colorFinderP);
    pnm_freepamrow(inrow);
    pnm_freepamrow(outrow);
    pnm_destroytuplehash(colorhash);
}



static void
remap(FILE *             const ifP,
      const struct pam * const outpamCommonP,
      tupletable         const colormap, 
      unsigned int       const colormapSize,
      bool               const floyd,
      bool               const randomize,
      tuple              const defaultColor,
      bool               const verbose) {
/*----------------------------------------------------------------------------
   Remap the pixels from the raster on *ifP to the 'colormapSize' colors in
   'colormap'.

   Where the input pixel's color is in the map, just use that for the output.
   Where it isn't, use 'defaultColor', except if that is NULL, use the
   closest color in the map to the input color.

   But if 'floyd' is true and 'defaultColor' is NULL, also do Floyd-Steinberg
   dithering on the output so the aggregate color of a region is about the
   same as that of the input even though the individual pixels have different
   colors.
-----------------------------------------------------------------------------*/
    int eof;
    eof = FALSE;
    while (!eof) {
        struct pam inpam, outpam;
        unsigned int missingCount;
            /* Number of pixels that were mapped to 'defaultColor' because
               they weren't present in the color map.
            */

        pnm_readpaminit(ifP, &inpam, PAM_STRUCT_SIZE(allocation_depth));
    
        outpam = *outpamCommonP;
        outpam.width  = inpam.width;
        outpam.height = inpam.height;

        pnm_writepaminit(&outpam);

        /* Set up so input buffers have extra space as needed to
           convert the input to the output depth.
        */
        pnm_setminallocationdepth(&inpam, outpam.depth);
    
        copyRaster(&inpam, &outpam, colormap, colormapSize, floyd,
                   randomize, defaultColor, &missingCount);
        
        if (verbose)
            pm_message("%u pixels not matched in color map", missingCount);
        
        pnm_nextimage(ifP, &eof);
    }
}



static void
processMapFile(const char *   const mapFileName,
               struct pam *   const outpamCommonP,
               tupletable *   const colormapP,
               unsigned int * const colormapSizeP,
               tuple *        const firstColorP) {
/*----------------------------------------------------------------------------
   Read a color map from the file named 'mapFileName'.  It's a map that
   associates each color in that file with a unique whole number.  Return the
   map as *colormapP, with the number of entries in it as *colormapSizeP.

   Also determine the first color (top left) in the map file and return that
   as *firstColorP.
-----------------------------------------------------------------------------*/
    FILE * mapfile;
    struct pam mappam;
    tuple ** maptuples;
    tuple firstColor;

    mapfile = pm_openr(mapFileName);
    maptuples = pnm_readpam(mapfile, &mappam, PAM_STRUCT_SIZE(tuple_type));
    pm_close(mapfile);

    computeColorMapFromMap(&mappam, maptuples, colormapP, colormapSizeP);

    firstColor = pnm_allocpamtuple(&mappam);
    pnm_assigntuple(&mappam, firstColor, maptuples[0][0]);
    *firstColorP = firstColor;

    pnm_freepamarray(maptuples, &mappam);

    *outpamCommonP = mappam; 
    outpamCommonP->file = stdout;
}



static void
getSpecifiedMissingColor(struct pam * const pamP,
                         const char * const colorName,
                         tuple *      const specColorP) {

    tuple specColor;
                             
    specColor = pnm_allocpamtuple(pamP);

    if (colorName) {
        pixel const color = ppm_parsecolor(colorName, pamP->maxval);
        if (pamP->depth == 3) {
            specColor[PAM_RED_PLANE] = PPM_GETR(color);
            specColor[PAM_GRN_PLANE] = PPM_GETG(color);
            specColor[PAM_BLU_PLANE] = PPM_GETB(color);
        } else if (pamP->depth == 1) {
            specColor[0] = ppm_luminosity(color);
        } else {
            pm_error("You may not use -missing with a colormap that is not "
                     "of depth 1 or 3.  Yours has depth %u",
                     pamP->depth);
        }
    }
    *specColorP = specColor;
}



int
main(int argc, const char * argv[] ) {

    struct CmdlineInfo cmdline;
    FILE * ifP;
    struct pam outpamCommon;
        /* Describes the output images.  Width and height fields are
           not meaningful, because different output images might have
           different dimensions.  The rest of the information is common
           across all output images.
        */
    tupletable colormap;
    unsigned int colormapSize;
    tuple specColor;
        /* A tuple of the color the user specified to use for input colors
           that are not in the colormap.  Arbitrary tuple if he didn't
           specify any.
        */
    tuple firstColor;
        /* A tuple of the first color present in the map file */
    tuple defaultColor;
        /* The color to which we will map an input color that is not in the
           colormap.  NULL if we are not to map such a color to a particular
           color (i.e. we'll choose an approximate match from the map).
        */

    pm_proginit(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    ifP = pm_openr(cmdline.inputFilespec);

    processMapFile(cmdline.mapFilespec, &outpamCommon,
                   &colormap, &colormapSize, &firstColor);

    getSpecifiedMissingColor(&outpamCommon, cmdline.missingcolor, &specColor);

    switch (cmdline.missingMethod) {
    case MISSING_CLOSE:
        defaultColor = NULL;
        break;
    case MISSING_FIRST:
        defaultColor = firstColor;
        break;
    case MISSING_SPECIFIED:
        defaultColor = specColor;
        break;
    }

    remap(ifP, &outpamCommon, colormap, colormapSize, 
          cmdline.floyd, !cmdline.norandom, defaultColor,
          cmdline.verbose);

    pnm_freepamtuple(firstColor);
    pnm_freepamtuple(specColor);

    pm_close(stdout);

    pm_close(ifP);

    return 0;
}



