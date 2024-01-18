/* ----------------------------------------------------------------------
 *
 * Replace every pixel in an image with one of equal luminance
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "mallocvar.h"
#include "nstring.h"
#include "shhopt.h"
#include "pam.h"

/* Two numbers less than REAL_EPSILON apart are considered equal. */
#define REAL_EPSILON 0.00001

/* Ensure a number N is no less than A and no greater than B. */
#define CLAMPxy(N, A, B) MAX(MIN((float)(N), (float)(B)), (float)(A))


struct rgbfrac {
    /* This structure represents red, green, and blue, each expressed
       as a fraction from 0.0 to 1.0.
    */
    float rfrac;
    float gfrac;
    float bfrac;
};

struct cmdlineInfo {
    /* This structure represents all of the information the user
       supplied in the command line but in a form that's easy for the
       program to use.
    */
    const char *    inputFileName;  /* '-' if stdin */
    const char *    colorfile;      /* NULL if unspecified */
    struct rgbfrac  color2gray;
        /* colorspace/rmult/gmult/bmult options.  Negative numbers if
           unspecified.
        */
    unsigned int    targetcolorSpec;
    struct rgbfrac  targetcolor;
    unsigned int    randomseed;
    unsigned int    randomseedSpec;
};



static float
rgb2gray(struct rgbfrac * const color2grayP,
         float            const red,
         float            const grn,
         float            const blu) {
    return
        color2grayP->rfrac * red +
        color2grayP->gfrac * grn +
        color2grayP->bfrac * blu;
}



static tuplen *
getColorRow(struct pam  * const pamP,
            tuplen     ** const imageData,
            unsigned int  const row,
            unsigned int  const desiredWidth) {
/*----------------------------------------------------------------------
  Return a row of color data.  If the number of columns is too small,
  repeat the existing columns in tiled fashion.
------------------------------------------------------------------------*/
    unsigned int const imageRow = row % pamP->height;

    static tuplen * oneRow = NULL;

    tuplen * retval;

    if (pamP->width >= desiredWidth)
        retval = imageData[imageRow];
    else {
        unsigned int col;

        if (!oneRow) {
            struct pam widePam;

            widePam = *pamP;
            widePam.width = desiredWidth;

            oneRow = pnm_allocpamrown(&widePam);
        }
        for (col = 0; col < desiredWidth; ++col)
            oneRow[col] = imageData[imageRow][col % pamP->width];
        retval = oneRow;
    }
    return retval;
}



static void
convertRowToGray(struct pam     * const pamP,
                 struct rgbfrac * const color2gray,
                 tuplen         * const tupleRow,
                 samplen        * const grayRow) {
/*----------------------------------------------------------------------
  Convert a row of RGB, grayscale, or black-and-white pixels to a row
  of grayscale values in the range [0, 1].
------------------------------------------------------------------------*/
    switch (pamP->depth) {
    case 1:
    case 2: {
        /* Black-and-white or grayscale */
        unsigned int col;
        for (col = 0; col < pamP->width; ++col)
            grayRow[col] = tupleRow[col][0];
    } break;

    case 3:
    case 4: {
        /* RGB color */
        unsigned int col;
        for (col = 0; col < pamP->width; ++col)
            grayRow[col] = rgb2gray(color2gray,
                                    tupleRow[col][PAM_RED_PLANE],
                                    tupleRow[col][PAM_GRN_PLANE],
                                    tupleRow[col][PAM_BLU_PLANE]);
    } break;

    default:
        pm_error("internal error: unexpected image depth %u", pamP->depth);
        break;
    }
}



static void
explicitlyColorRow(struct pam *   const pamP,
                   tuplen *       const rowData,
                   struct rgbfrac const tint) {

    unsigned int col;

    for (col = 0; col < pamP->width; ++col) {
        rowData[col][PAM_RED_PLANE] = tint.rfrac;
        rowData[col][PAM_GRN_PLANE] = tint.gfrac;
        rowData[col][PAM_BLU_PLANE] = tint.bfrac;
    }
}



static void
randomlyColorRow(struct pam *   const pamP,
                 tuplen *       const rowData) {
/*----------------------------------------------------------------------
  Assign each tuple in a row a random color.
------------------------------------------------------------------------*/
    unsigned int col;

    for (col = 0; col < pamP->width; ++col) {
        rowData[col][PAM_RED_PLANE] = rand() / (float)RAND_MAX;
        rowData[col][PAM_GRN_PLANE] = rand() / (float)RAND_MAX;
        rowData[col][PAM_BLU_PLANE] = rand() / (float)RAND_MAX;
    }
}



static void
recolorRow(struct pam     * const inPamP,
           tuplen         * const inRow,
           struct rgbfrac * const color2grayP,
           tuplen         * const colorRow,
           struct pam     * const outPamP,
           tuplen         * const outRow) {
/*----------------------------------------------------------------------
  Map each tuple in a given row to a random color with the same
  luminance.
------------------------------------------------------------------------*/
    static samplen * grayRow = NULL;

    unsigned int col;

    if (!grayRow)
        MALLOCARRAY_NOFAIL(grayRow, inPamP->width);

    convertRowToGray(inPamP, color2grayP, inRow, grayRow);

    for (col = 0; col < inPamP->width; ++col) {
        float targetgray;
        float givengray;
        float red, grn, blu;

        red = colorRow[col][PAM_RED_PLANE];   /* initial value */
        grn = colorRow[col][PAM_GRN_PLANE];   /* initial value */
        blu = colorRow[col][PAM_BLU_PLANE];   /* initial value */

        targetgray = grayRow[col];
        givengray = rgb2gray(color2grayP, red, grn, blu);

        if (givengray == 0.0) {
            /* Special case for black so we don't divide by zero */
            red = targetgray;
            grn = targetgray;
            blu = targetgray;
        }
        else {
            /* Try simply scaling each channel equally. */
            red *= targetgray / givengray;
            grn *= targetgray / givengray;
            blu *= targetgray / givengray;

            if (red > 1.0 || grn > 1.0 || blu > 1.0) {
                /* Repeatedly raise the level of all non-1.0 channels
                 * until all channels are at 1.0 or we reach our
                 * target gray. */
                red = MIN(red, 1.0);
                grn = MIN(grn, 1.0);
                blu = MIN(blu, 1.0);
                givengray = rgb2gray(color2grayP, red, grn, blu);

                while (fabsf(givengray - targetgray) > REAL_EPSILON) {
                    float increment;
                        /* How much to increase each channel (unscaled
                           amount)
                        */
                    int   subOne = 0;
                        /* Number of channels with sub-1.0 values */

                    /* Tally the number of channels that aren't yet maxed
                       out.
                    */
                    if (red < 1.0)
                        subOne++;
                    if (grn < 1.0)
                        subOne++;
                    if (blu < 1.0)
                        subOne++;

                    /* Stop if we've reached our target or can't increment
                     * any channel any further. */
                    if (subOne == 0)
                        break;

                    /* Brighten each non-maxed channel equally. */
                    increment = (targetgray - givengray) / subOne;
                    if (red < 1.0)
                        red = MIN(red + increment / color2grayP->rfrac, 1.0);
                    if (grn < 1.0)
                        grn = MIN(grn + increment / color2grayP->gfrac, 1.0);
                    if (blu < 1.0)
                        blu = MIN(blu + increment / color2grayP->bfrac, 1.0);

                    /* Prepare to try again. */
                    givengray = rgb2gray(color2grayP, red, grn, blu);
                }
            }
            else
                givengray = rgb2gray(color2grayP, red, grn, blu);
        }

        outRow[col][PAM_RED_PLANE] = red;
        outRow[col][PAM_GRN_PLANE] = grn;
        outRow[col][PAM_BLU_PLANE] = blu;
        if (outPamP->depth == 4)
            outRow[col][PAM_TRN_PLANE] = inRow[col][PAM_TRN_PLANE];
    }
}



static struct rgbfrac
color2GrayFromCsName(const char * const csName) {

    struct rgbfrac retval;

    /* Thanks to
       http://www.brucelindbloom.com/index.html?Eqn_RGB_XYZ_Matrix.html
       for these values.
    */
    if (streq(csName, "ntsc")) {
        /* NTSC RGB with an Illuminant C reference white */
        retval.rfrac = 0.2989164;
        retval.gfrac = 0.5865990;
        retval.bfrac = 0.1144845;
    } else if (streq(csName, "srgb")) {
        /* sRGB with a D65 reference white */
        retval.rfrac = 0.2126729;
        retval.gfrac = 0.7151522;
        retval.bfrac = 0.0721750;
    } else if (streq(csName, "adobe")) {
        /* Adobe RGB (1998) with a D65 reference white */
        retval.rfrac = 0.2973769;
        retval.gfrac = 0.6273491;
        retval.bfrac = 0.0752741;
    } else if (streq(csName, "apple")) {
        /* Apple RGB with a D65 reference white */
        retval.rfrac = 0.2446525;
        retval.gfrac = 0.6720283;
        retval.bfrac = 0.0833192;
    } else if (streq(csName, "cie")) {
        /* CIE with an Illuminant E reference white */
        retval.rfrac = 0.1762044;
        retval.gfrac = 0.8129847;
        retval.bfrac = 0.0108109;
    } else if (streq(csName, "pal")) {
        /* PAL/SECAM with a D65 reference white */
        retval.rfrac = 0.2220379;
        retval.gfrac = 0.7066384;
        retval.bfrac = 0.0713236;
    } else if (streq(csName, "smpte-c")) {
        /* SMPTE-C with a D65 reference white */
        retval.rfrac = 0.2124132;
        retval.gfrac = 0.7010437;
        retval.bfrac = 0.0865432;
    } else if (streq(csName, "wide")) {
        /* Wide gamut with a D50 reference white */
        retval.rfrac = 0.2581874;
        retval.gfrac = 0.7249378;
        retval.bfrac = 0.0168748;
    } else
        pm_error("Unknown color space name \"%s\"", csName);

    return retval;
}



static void
parseCommandLine(int argc, const char ** const argv,
                 struct cmdlineInfo * const cmdlineP ) {

    optEntry     * option_def;
        /* Instructions to OptParseOptions3 on how to parse our options */
    optStruct3     opt;
    unsigned int   option_def_index;
    const char *   colorspaceOpt;
    const char *   targetcolorOpt;
    unsigned int   csSpec, rmultSpec, gmultSpec, bmultSpec,
        colorfileSpec;

    MALLOCARRAY_NOFAIL(option_def, 100);
    option_def_index = 0;          /* Incremented by OPTENTRY */

    OPTENT3(0, "colorspace",   OPT_STRING, &colorspaceOpt, &csSpec, 0);
    OPTENT3(0, "rmult",        OPT_FLOAT,  &cmdlineP->color2gray.rfrac,
            &rmultSpec, 0);
    OPTENT3(0, "gmult",        OPT_FLOAT,  &cmdlineP->color2gray.gfrac,
            &gmultSpec, 0);
    OPTENT3(0, "bmult",        OPT_FLOAT,  &cmdlineP->color2gray.bfrac,
            &bmultSpec, 0);
    OPTENT3(0, "colorfile",    OPT_STRING, &cmdlineP->colorfile,
            &colorfileSpec, 0);
    OPTENT3(0, "targetcolor",  OPT_STRING, &targetcolorOpt,
            &cmdlineP->targetcolorSpec, 0);
    OPTENT3(0,   "randomseed",   OPT_UINT,    &cmdlineP->randomseed,
            &cmdlineP->randomseedSpec,      0);

    opt.opt_table = option_def;
    opt.short_allowed = 0;
    opt.allowNegNum = 0;

    pm_optParseOptions3(&argc, (char **)argv, opt, sizeof(opt), 0);

    if (rmultSpec || gmultSpec || bmultSpec) {
        /* If the user explicitly specified RGB multipliers, ensure that
         * (a) he didn't specify --colorspace,
         * (b) he specified all three channels, and
         * (c) the values add up to 1.
         */
        float maxLuminance;

        if (csSpec)
            pm_error("The --colorspace option is mutually exclusive with "
                     "the --rmult, --gmult, and --bmult options");
        if (!(rmultSpec && gmultSpec && bmultSpec))
            pm_error("If you specify any of --rmult, --gmult, or --bmult, "
                     "you must specify all of them");
        maxLuminance =
            cmdlineP->color2gray.rfrac +
            cmdlineP->color2gray.gfrac +
            cmdlineP->color2gray.bfrac;
        if (fabsf(1.0 - maxLuminance) > REAL_EPSILON)
            pm_error("The values given for --rmult, --gmult, and --bmult must "
                     "sum to 1.0, not %.10g", maxLuminance);
    } else if (csSpec)
        cmdlineP->color2gray = color2GrayFromCsName(colorspaceOpt);
    else
        cmdlineP->color2gray = color2GrayFromCsName("ntsc");

    if (colorfileSpec && cmdlineP->targetcolorSpec)
        pm_error("The --colorfile option and the --targetcolor option are "
                 "mutually exclusive");

    if (!colorfileSpec)
        cmdlineP->colorfile = NULL;

    if (cmdlineP->targetcolorSpec) {
        sample const colorMaxVal = (1<<16) - 1;
            /* Maximum PAM maxval for precise sample-to-float conversion */
        tuple const targetTuple = pnm_parsecolor(targetcolorOpt, colorMaxVal);
        cmdlineP->targetcolor.rfrac =
            targetTuple[PAM_RED_PLANE] / (float)colorMaxVal;
        cmdlineP->targetcolor.gfrac =
            targetTuple[PAM_GRN_PLANE] / (float)colorMaxVal;
        cmdlineP->targetcolor.bfrac =
            targetTuple[PAM_BLU_PLANE] / (float)colorMaxVal;
    }

    if (argc-1 < 1)
        cmdlineP->inputFileName = "-";
    else {
        cmdlineP->inputFileName = argv[1];
        if (argc-1 > 1)
            pm_error("Too many arguments: %u.  The only argument is the "
                     "optional input file name", argc-1);
    }
}



int
main(int argc, const char *argv[]) {
    struct cmdlineInfo cmdline;          /* Command-line parameters */
    struct pam         inPam;
    struct pam         outPam;
    struct pam         colorPam;
    FILE *             ifP;
    FILE *             colorfP;
    const char *       comments;
    tuplen *           inRow;
    tuplen *           outRow;
    tuplen **          colorData;
    tuplen *           colorRowBuffer;
    unsigned int       row;

    pm_proginit(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    srand(cmdline.randomseedSpec ? cmdline.randomseed : pm_randseed());

    ifP = pm_openr(cmdline.inputFileName);
    inPam.comment_p = &comments;
    pnm_readpaminit(ifP, &inPam, PAM_STRUCT_SIZE(comment_p));

    outPam = inPam;
    outPam.file = stdout;
    outPam.format = PAM_FORMAT;
    outPam.depth = 4 - (inPam.depth % 2);
    outPam.allocation_depth = outPam.depth;
    strcpy(outPam.tuple_type, PAM_PPM_TUPLETYPE);
    pnm_writepaminit(&outPam);

    if (cmdline.colorfile) {
        colorfP = pm_openr(cmdline.colorfile);
        colorPam.comment_p = NULL;
        colorData =
            pnm_readpamn(colorfP, &colorPam, PAM_STRUCT_SIZE(comment_p));
    } else {
        colorfP = NULL;
        colorPam = outPam;
        colorData = NULL;
    }

    inRow = pnm_allocpamrown(&inPam);
    outRow = pnm_allocpamrown(&outPam);

    colorRowBuffer = pnm_allocpamrown(&outPam);

    for (row = 0; row < inPam.height; ++row) {
        tuplen * colorRow;

        pnm_readpamrown(&inPam, inRow);

        if (cmdline.colorfile)
            colorRow = getColorRow(&colorPam, colorData, row, outPam.width);
        else {
            colorRow = colorRowBuffer;

            if (cmdline.targetcolorSpec)
                explicitlyColorRow(&colorPam, colorRow, cmdline.targetcolor);
            else
                randomlyColorRow(&colorPam, colorRow);
        }
        recolorRow(&inPam, inRow,
                   &cmdline.color2gray, colorRow,
                   &outPam, outRow);
        pnm_writepamrown(&outPam, outRow);
    }
    pnm_freepamrown(outRow);
    pnm_freepamrown(inRow);
    pnm_freepamrown(colorRowBuffer);

    if (colorData)
        pnm_freepamarrayn(colorData, &colorPam);

    if (colorfP)
        pm_close(colorfP);
    pm_close(ifP);

    return 0;
}

