/* ----------------------------------------------------------------------
 *
 * Convert a single-image stereogram to a red/cyan anaglyphic image
 *
 * By Scott Pakin <scott+pbm@pakin.org>
 *
 * ----------------------------------------------------------------------
 *
 * Copyright (C) 2009-2022 Scott Pakin <scott+pbm@pakin.org>
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

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "mallocvar.h"
#include "nstring.h"
#include "shhopt.h"
#include "pam.h"


struct cmdlineInfo {
    /* This structure represents all of the information the user
       supplied in the command line but in a form easy for the program
       to use.
    */
    int separation;
        /* Exact separation in pixels between the left and right eye,
           or -1
        */
    int minSeparation;
        /* Minimum separation in pixels between the left and right eye */
    gray maxGrayVal;
        /* Maximum grayscale value to which to scale the image */
    int swapEyes;
        /* 0=left red, right cyan; 1=left cyan, right red */
    const char *inputFilename;   /* '-' if stdin */
};



static void
parseCommandLine( int argc, const char ** const argv,
                  struct cmdlineInfo * const cmdlineP ) {
/*--------------------------------------------------------------------
  Parse the command line into a structure.
----------------------------------------------------------------------*/

    optEntry     * option_def;
        /* Instructions to OptParseOptions3 on how to parse our options */
    optStruct3     opt;
    unsigned int   option_def_index;
    int            maxgrayval;

    maxgrayval = 63;  /* default */

    MALLOCARRAY(option_def, 100);
    option_def_index = 0;          /* Incremented by OPTENTRY */
    MEMSZERO(cmdlineP);
    cmdlineP->separation = -1;

    OPTENT3('s', "sep",    OPT_INT,  &cmdlineP->separation,    NULL, 0);
    OPTENT3('g', "gray",   OPT_INT,  &maxgrayval,              NULL, 0);
    OPTENT3('i', "invert", OPT_FLAG, &cmdlineP->swapEyes,      NULL, 0);
    OPTENT3('m', "minsep", OPT_INT,  &cmdlineP->minSeparation, NULL, 0);

    opt.opt_table = option_def;
    opt.short_allowed = 1;
    opt.allowNegNum = 0;

    pm_optParseOptions3( &argc, (char **)argv, opt, sizeof(opt), 0 );

    if (argc-1 < 1)
        cmdlineP->inputFilename = "-";
    else {
        cmdlineP->inputFilename = argv[1];
        if (argc-1 > 1)
            pm_error("Too many arguments: %u.  The only argument is the "
                     "optional input file name", argc-1);
    }
    cmdlineP->maxGrayVal = (gray) maxgrayval;
}



static gray **
readAsGray( const char * const fileName,
            gray         const maxGrayVal,
            struct pam * const pamP) {
/*--------------------------------------------------------------------
  Read the input image and convert it to grayscale to reduce the
  number of "almost but not quite" equal pixels.  Return the
  grayscale array and the initialized PAM structure.
  ----------------------------------------------------------------------*/

    FILE       *  fileP;
    tuple      *  tuplerow;
    gray       ** grayArray;
    unsigned int  row;

    fileP = pm_openr( fileName );

    pnm_readpaminit( fileP, pamP, PAM_STRUCT_SIZE(tuple_type) );

    tuplerow = pnm_allocpamrow( pamP );

    grayArray = pgm_allocarray( pamP->width, pamP->height );

    for (row = 0; row < pamP->height; ++row) {
        unsigned int col;
        pnm_readpamrow( pamP, tuplerow );
        for (col = 0; col < pamP->width; ++col) {
            double YP, CbP, CrP;

            if (pamP->depth >= 3)
                pnm_YCbCrtuple(tuplerow[col], &YP, &CbP, &CrP);
            else
                YP = (double) tuplerow[col][0];
            grayArray[row][col] = (gray)
                (YP * maxGrayVal / (double)pamP->maxval);
        }
    }
    pnm_freepamrow( tuplerow );
    pm_close( fileP );
    return grayArray;
}



static int
bestEyeSepWeEncountered(int const bestSeparation[3],
                        int const altBestSeparation) {

    int i;

    for (i = 2; i >= 0; --i) {
        if (bestSeparation[i] != 0)
            return bestSeparation[i];
    }    
    return altBestSeparation;
}



static int
findRegionEyeSeparation( gray ** const grayArray,
                         int     const width,
                         int     const height ) {
/*----------------------------------------------------------------------
  Determine the number of pixels that corresponds to the separation
  between the viewer's left eye and right eye.  We do this by counting
  the number of pixels that match N pixels ahead in the image for all
  N in [1, W/2].  The first big spike in the number of matched pixels
  determines the N to use for the eye separation.  More specifically,
  if a spike that exceeds 3*stdev+mean is found, the corresponding
  value of N is taken as the eye separation; otherwise, a spike
  exceeding 2*stdev+mean is used, then 1*stdev+mean, and finally, the
  eye separation that produces the minimum average distance between
  matched pixels.  A return value of zero indicates that no eye
  separation could be determined.
------------------------------------------------------------------------*/
    int              bestSeparation[3];
        /* Eye separation corresponding to spikes of N+1 standard deviations */
    int              hShift;
        /* Current horizontal shift */
    double           sumMatches;
        /* Sum of all matches seen so far */
    double           sumSqMatches;
        /* Sum of the squares of all matches seen so far */
    double           meanMatches;
        /* Mean of all matches seen so far */
    double           stdMatches;
        /* Standard deviation of all matches seen so far */
    double           minAvgDist;
        /* Min. average distance between matches */
    int              altBestSeparation;
        /* Shift distance corresponding to the above */
    unsigned int     i;

    /* Try in turn each horizontal shift value from 1 to width/2.  A
       shift of 0 is defined to be a perfect match.  A shift of more
       than width/2 implies that the right-eye image is truncated, which
       is an unnatural way to construct a crosseyed stereogram.
    */
    for (i = 0; i < 3; ++i)
        bestSeparation[i] = 0;

    altBestSeparation = 0;
    sumMatches = sumSqMatches = 0.0;
    meanMatches = stdMatches = minAvgDist = width * height;

    for (hShift = 1; hShift <= width/2; ++hShift) {
        unsigned int row;
        unsigned long numMatches;      /* Number of matched pixels */
        double avgDist;                /* Average distance between matches */

        numMatches = 0;  /* initial value */

        /* Tally the number of matches for this shift distance. */
        for (row = 0; row < height; ++row) {
            unsigned int col;
            for (col = 0; col < width - hShift; ++col)
                if (grayArray[row][col] == grayArray[row][col + hShift])
                    ++numMatches;

            /* See if the number of matches exceeds the running mean plus N
               standard deviations.  Also, keep track of the shortest average
               distance between matches seen so far.
            */
            if (hShift > 1) {
                int i;
                for (i = 2; i >= 0; --i)
                    if (bestSeparation[i] == 0 &&
                        numMatches > meanMatches + (i+1)*stdMatches) {
                        bestSeparation[i] = hShift;
                        break;
                    }
            }
            avgDist = (height * (width-hShift)) / (double)numMatches;
            if (minAvgDist > avgDist) {
                minAvgDist = avgDist;
                altBestSeparation = hShift;
            }

            /* Compute the new mean and standard deviation. */
            sumMatches   += (double)numMatches;
            sumSqMatches += (double)numMatches * (double)numMatches;
            meanMatches = sumMatches / (double)hShift;
            stdMatches  = sqrt(sumSqMatches/hShift - meanMatches*meanMatches);
        }
    }

    return bestEyeSepWeEncountered(bestSeparation, altBestSeparation);
}



#ifndef LITERAL_FN_DEF_MATCH
static qsort_comparison_fn compareInts;
#endif

static int
compareInts(const void * const a,
            const void * const b) {

    const int * const firstP = a;
    const int * const secondP = b;

    int const first  = *firstP;
    int const second = *secondP;

    int retval;

    if (first < second)
        retval = -1;
    else if (first > second)
        retval = +1;
    else
        retval = 0;

    return retval;
}



static int
findEyeSeparation( struct pam *  const pamP,
                   gray       ** const grayArray,
                   int           const minSeparation ) {
/*----------------------------------------------------------------------
  Compute the eye separation for each row of the grayscale image.
  Ignore rows for which the eye separation could not be determined and
  return the median of the remaining rows, aborting with an error
  message if there are no remaining rows.  Out of laziness we use
  qsort() to help find the median; if this turns out to be a
  performance problem, it should be replaced with a linear-time median
  finder.
------------------------------------------------------------------------*/
    int bestSeparation;      /* Best eye separation found */

    /* First attempt: Find the best eye separation across the image as a
       whole.  This works well when the image consists of relatively
       small foreground objects in front of a comparatively large
       background plane.
    */
    bestSeparation =
        findRegionEyeSeparation( grayArray, pamP->width, pamP->height );

    /* Second attempt: Compute the best eye separation for each row
       independently and return the median of the best eye
       separations.
    */
    if (bestSeparation < minSeparation) {
        int * rowSeparation;   /* Per-row best separation distance */
        unsigned int numValidRows;
            /* Number of entries in the above (<= #rows) */
        unsigned int row;

        numValidRows = 0;  /* initial value */

        MALLOCARRAY_NOFAIL( rowSeparation, pamP->height );
        for (row = 0; row < pamP->height; ++row) {
            int const sep =
                findRegionEyeSeparation( &grayArray[row], pamP->width, 1);
            if (sep >= minSeparation)
                rowSeparation[numValidRows++] = sep;
        }
        if (numValidRows > 0) {
            qsort(rowSeparation, numValidRows, sizeof(int), compareInts);
            bestSeparation = rowSeparation[numValidRows/2];
        }
        free( rowSeparation );
    }

    if (bestSeparation < minSeparation)
        pm_error("Failed to determine the separation between "
                 "the left and right views");

    return bestSeparation;
}



static void
writeAnaglyph( FILE *       const ofP,
               gray **      const grayArray,
               gray         const maxGrayVal,
               int          const eyeSep,
               int          const swapEyes,
               struct pam * const pamP) {
/*----------------------------------------------------------------------
  Output an anaglyphic stereogram from the given grayscale array and
  eye-separation value.
------------------------------------------------------------------------*/
    struct pam   outPam;
    tuple      * tuplerow;

    outPam.size        = sizeof(struct pam);
    outPam.len         = PAM_STRUCT_SIZE(tuple_type);
    outPam.file        = ofP;
    outPam.format      = PAM_FORMAT;
    outPam.plainformat = 0;
    outPam.height      = pamP->height;
    outPam.width       = pamP->width - eyeSep;
        /* Avoid color bands on the left/right edges. */
    outPam.depth       = 3;
    outPam.maxval      = (sample) maxGrayVal;
    strcpy(outPam.tuple_type, PAM_PPM_TUPLETYPE);

    pnm_writepaminit( &outPam );

    tuplerow = pnm_allocpamrow( &outPam );

    if (swapEyes) {
        unsigned int row;

        for (row = 0; row < outPam.height; ++row) {
            unsigned int col;
            for (col = 0; col < outPam.width; ++col) {
                tuplerow[col][PAM_RED_PLANE] = grayArray[row][col+eyeSep];
                tuplerow[col][PAM_GRN_PLANE] = grayArray[row][col];
                tuplerow[col][PAM_BLU_PLANE] = grayArray[row][col];
            }
            pnm_writepamrow( &outPam, tuplerow );
        }
    } else {
        unsigned int row;
        for (row = 0; row < outPam.height; ++row) {
            unsigned int col;
            for (col = 0; col < outPam.width; ++col) {
                tuplerow[col][PAM_RED_PLANE] = grayArray[row][col];
                tuplerow[col][PAM_GRN_PLANE] = grayArray[row][col+eyeSep];
                tuplerow[col][PAM_BLU_PLANE] = grayArray[row][col+eyeSep];
            }
            pnm_writepamrow( &outPam, tuplerow );
        }
    }
    pnm_freepamrow( tuplerow );
}



int
main(int argc, const char *argv[]) {
    struct pam            inPam;
    gray               ** inImage;
    int                   eyeSep;
    struct cmdlineInfo    cmdline;

    pm_proginit( &argc, argv );
    parseCommandLine( argc, argv, &cmdline );

    inImage = readAsGray( cmdline.inputFilename, cmdline.maxGrayVal, &inPam );

    if (cmdline.separation >= 0)
        eyeSep = cmdline.separation;
    else {
        int const minSeparation =
            cmdline.minSeparation > 0
            ? cmdline.minSeparation : inPam.width / 10;

            /* Minimum separation in pixels between eyes.
               Heuristic: Eye separation must be at least 10% of image width.
            */
        eyeSep = findEyeSeparation ( &inPam, inImage, minSeparation );
    }

    pm_message( "Separation between left/right views = %d pixels", eyeSep );

    writeAnaglyph ( stdout, inImage, cmdline.maxGrayVal,
                    eyeSep, cmdline.swapEyes,
                    &inPam );

    return 0;
}

