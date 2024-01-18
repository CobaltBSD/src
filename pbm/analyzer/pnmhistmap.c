/* pnmhistmap.c -
 *  Draw a histogram for a PGM or PPM file
 *
 * Options: -verbose: the usual
 *      -max N: force scaling value to N
 *      -black: ignore all-black count
 *      -white: ignore all-white count
 *
 * - PGM histogram is a PBM file, PPM histogram is a PPM file
 * - No conditional code - assumes all three: PBM, PGM, PPM
 *
 * Copyright (C) 1993 by Wilson H. Bent, Jr (whb@usc.edu)
 *
 * 2004-12-11 john h. dubois iii (john@armory.com)
 * - Added options:
 *   -dots, -nmax, -red, -green, -blue, -width, -height, -lval, -rval
 * - Deal properly with maxvals other than 256
 */

#include <assert.h>
#include <string.h>

#include "pm_c_util.h"
#include "pnm.h"
#include "shhopt.h"
#include "mallocvar.h"

static double const epsilon = .00001;

enum wantedColor {WANT_RED=0, WANT_GRN=1, WANT_BLU=2};

struct cmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    const char *inputFilespec;  /* Filespecs of input files */
    unsigned int black;
    unsigned int white;
    unsigned int dots;
    bool         colorWanted[3];
        /* subscript is enum wantedColor */
    unsigned int verbose;
    unsigned int nmaxSpec;
    float        nmax;
    unsigned int lval;
    unsigned int rval;
    unsigned int widthSpec;
    unsigned int width;
    unsigned int height;
};



static void
parseCommandLine(int argc, const char ** argv,
                 struct cmdlineInfo *cmdlineP) {
/*----------------------------------------------------------------------------
   Note that the file spec array we return is stored in the storage that
   was passed to us as the argv array.
-----------------------------------------------------------------------------*/
    optEntry *option_def;
        /* Instructions to pm_optParseOptions3 on how to parse our options.
         */
    optStruct3 opt;

    unsigned int option_def_index;
    unsigned int lvalSpec, rvalSpec, heightSpec;
    unsigned int redSpec, greenSpec, blueSpec;

    MALLOCARRAY_NOFAIL(option_def, 100);

    option_def_index = 0;   /* incremented by OPTENT3 */
    OPTENT3(0, "black",     OPT_FLAG, NULL, &cmdlineP->black,   0);
    OPTENT3(0, "white",     OPT_FLAG, NULL, &cmdlineP->white,   0);
    OPTENT3(0, "dots",      OPT_FLAG, NULL, &cmdlineP->dots,    0);
    OPTENT3(0, "red",       OPT_FLAG, NULL, &redSpec,           0);
    OPTENT3(0, "green",     OPT_FLAG, NULL, &greenSpec,         0);
    OPTENT3(0, "blue",      OPT_FLAG, NULL, &blueSpec,          0);
    OPTENT3(0, "verbose",   OPT_FLAG, NULL, &cmdlineP->verbose, 0);
    OPTENT3(0, "nmax",      OPT_FLOAT, &cmdlineP->nmax,
            &cmdlineP->nmaxSpec,   0);
    OPTENT3(0, "lval",      OPT_UINT, &cmdlineP->lval,
            &lvalSpec,             0);
    OPTENT3(0, "rval",      OPT_UINT, &cmdlineP->rval,
            &rvalSpec,             0);
    OPTENT3(0, "width",     OPT_UINT, &cmdlineP->width,
            &cmdlineP->widthSpec,  0);
    OPTENT3(0, "height",    OPT_UINT, &cmdlineP->height,
            &heightSpec, 0);

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = FALSE;  /* We may have parms that are negative numbers */

    pm_optParseOptions3(&argc, (char **)argv, opt, sizeof(opt), 0);
        /* Uses and sets argc, argv, and some of *cmdlineP and others. */

    if (!lvalSpec)
        cmdlineP->lval = 0;
    if (!rvalSpec)
        cmdlineP->rval = PNM_OVERALLMAXVAL;

    if (!redSpec && !greenSpec && !blueSpec) {
        cmdlineP->colorWanted[WANT_RED] = TRUE;
        cmdlineP->colorWanted[WANT_GRN] = TRUE;
        cmdlineP->colorWanted[WANT_BLU] = TRUE;
    } else {
        cmdlineP->colorWanted[WANT_RED] = redSpec;
        cmdlineP->colorWanted[WANT_GRN] = greenSpec;
        cmdlineP->colorWanted[WANT_BLU] = blueSpec;
    }

    if (!heightSpec)
        cmdlineP->height = 200;

    if (argc-1 == 0) 
        cmdlineP->inputFilespec = "-";
    else if (argc-1 != 1)
        pm_error("Program takes zero or one argument (filename).  You "
                 "specified %u", argc-1);
    else
        cmdlineP->inputFilespec = argv[1];
}



static unsigned int
maxSlotCount(const unsigned int * const hist,
             unsigned int         const histWidth,
             bool                 const no_white,
             bool                 const no_black) {
/*----------------------------------------------------------------------------
   Return the maximum count among all the slots in hist[], not counting
   the first and last as suggested by 'no_white' and 'no_black'.
-----------------------------------------------------------------------------*/
    unsigned int hmax;
    unsigned int i;

    unsigned int const start = (no_black ? 1 : 0);
    unsigned int const finish = (no_white ? histWidth - 1 : histWidth);
    for (hmax = 0, i = start; i < finish; ++i)
        if (hmax < hist[i])
            hmax = hist[i];

    return hmax;
}



static void
clipHistogram(unsigned int * const hist,
              unsigned int   const histWidth,
              unsigned int   const hmax) {

    unsigned int i;

    for (i = 0; i < histWidth; ++i)
        hist[i] = MIN(hmax, hist[i]);
}



static void
countComp(xelval         const value,
          xelval         const startval,
          xelval         const endval,
          unsigned int   const histWidth,
          unsigned int * const hist) {

    double const hscale = (float)(histWidth-1) / (endval - startval - 1);

    if (value >= startval && value < endval) {
        unsigned int const bin = ROUNDU((value-startval) * hscale);

        assert(bin < histWidth);
        ++hist[bin];
    }
}



static void
pgmHist(FILE *       const ifP,
        int          const cols,
        int          const rows,
        xelval       const maxval,
        int          const format,
        bool         const dots,
        bool         const no_white,
        bool         const no_black,
        bool         const verbose,
        xelval       const startval,
        xelval       const endval,
        unsigned int const histWidth,
        unsigned int const histHeight,
        bool         const clipSpec,
        unsigned int const clipCount) {

    gray * grayrow;
    bit ** bits;
    int i, j;
    unsigned int * ghist;
    double vscale;
    unsigned int hmax;
    
    MALLOCARRAY(ghist, histWidth);
    if (ghist == NULL)
        pm_error("Not enough memory for histogram array (%u bytes)",
                 histWidth * (unsigned)sizeof(int));
    bits = pbm_allocarray(histWidth, histHeight);
    if (bits == NULL)
        pm_error("no space for output array (%u bits)",
                 histWidth * histHeight);
    memset(ghist, 0, histWidth * sizeof(ghist[0]));

    /* read the pixel values into the histogram arrays */
    grayrow = pgm_allocrow(cols);

    if (verbose)
        pm_message("making histogram...");

    for (i = rows; i > 0; --i) {
        pgm_readpgmrow (ifP, grayrow, cols, maxval, format);
        for (j = cols-1; j >= 0; --j)
            countComp(grayrow[j], startval, endval, histWidth, ghist);
    }
    pgm_freerow(grayrow);

    /* find the highest-valued slot and set the vertical scale value */
    if (verbose)
        pm_message("finding max. slot height...");
    if (clipSpec)
        hmax = clipCount;
    else 
        hmax = maxSlotCount(ghist, histWidth, no_white, no_black);

    assert(hmax > 0);

    if (verbose)
        pm_message("Done: height = %u", hmax);

    clipHistogram(ghist, histWidth, hmax);

    vscale = (double) histHeight / hmax;

    for (i = 0; i < histWidth; ++i) {
        int mark = histHeight - (int)(vscale * ghist[i]);
        for (j = 0; j < mark; ++j)
            bits[j][i] = PBM_BLACK;
        if (j < histHeight)
            bits[j++][i] = PBM_WHITE;
        for ( ; j < histHeight; ++j)
            bits[j][i] = dots ? PBM_BLACK : PBM_WHITE;
    }

    pbm_writepbm(stdout, bits, histWidth, histHeight, 0);
}



static unsigned int
maxSlotCountAll(unsigned int *       const hist[3],
                unsigned int         const histWidth,
                bool                 const no_white,
                bool                 const no_black) {
/*----------------------------------------------------------------------------
   Return the maximum count among all the slots in hist[x] not
   counting the first and last as suggested by 'no_white' and
   'no_black'.  hist[x] may be NULL to indicate none.
-----------------------------------------------------------------------------*/
    unsigned int hmax;
    unsigned int color;

    hmax = 0;

    for (color = 0; color < 3; ++color)
        if (hist[color])
            hmax = MAX(hmax, 
                       maxSlotCount(hist[color], 
                                    histWidth, no_white, no_black));
    
    return hmax;
}



static void
createHist(bool             const colorWanted[3],
           unsigned int     const histWidth,
           unsigned int * (* const histP)[3]) {
/*----------------------------------------------------------------------------
   Allocate the histogram arrays and set each slot count to zero.
-----------------------------------------------------------------------------*/
    unsigned int color;

    for (color = 0; color < 3; ++color) {
        if (colorWanted[color]) {
            unsigned int * hist;
            unsigned int i;
            MALLOCARRAY(hist, histWidth);
            if (hist == NULL)
                pm_error("Not enough memory for histogram arrays (%u bytes)",
                         histWidth * (unsigned)sizeof(hist[0]) * 3);

            for (i = 0; i < histWidth; ++i)
                hist[i] = 0;
            (*histP)[color] = hist;
        } else
            (*histP)[color] = NULL;
    }
}



static void
clipHistogramAll(unsigned int * const hist[3],
                 unsigned int   const histWidth,
                 unsigned int   const hmax) {

    unsigned int color;

    for (color = 0; color < 3; ++color)
        if (hist[color])
            clipHistogram(hist[color], histWidth, hmax);
}



static void
fillPpmBins(FILE *          const ifP,
            unsigned int    const cols,
            unsigned int    const rows,
            xelval          const maxval,
            int             const format,
            bool            const colorWanted[3],
            bool            const verbose,
            xelval          const startval,
            xelval          const endval,
            unsigned int    const histWidth,
            unsigned int ** const hist) {
/*----------------------------------------------------------------------------
   For each wanted color component, given by colorWanted[], hist[color] is the
   histogram.  Each histogram as 'histWidth' bins; we ignore color component
   values less than 'startval' and greater than or equal to 'endval' and
   spread the rest evenly across the 'histWidth' bins.

   We get the color component values from the PNM image on *ifP,
   which is positioned to the raster, whose format is described
   by 'cols', 'rows', 'maxval', and 'format'.
-----------------------------------------------------------------------------*/
    pixel * pixrow;
    unsigned int row;

    pixrow = ppm_allocrow(cols);

    if (verbose)
        pm_message("making histogram...");

    for (row = 0; row < rows; ++row) {
        unsigned int col;
        ppm_readppmrow(ifP, pixrow, cols, maxval, format);
        for (col = 0; col < cols; ++col) {
            if (colorWanted[WANT_RED])
                countComp(PPM_GETR(pixrow[col]),
                          startval, endval, histWidth, hist[WANT_RED]);

            if (colorWanted[WANT_GRN])
                countComp(PPM_GETG(pixrow[col]),
                          startval, endval, histWidth, hist[WANT_GRN]);

            if (colorWanted[WANT_BLU])
                countComp(PPM_GETB(pixrow[col]),
                          startval, endval, histWidth, hist[WANT_BLU]);
        }
    }
    ppm_freerow(pixrow);
}



static void
ppmHist(FILE *       const ifP,
        unsigned int const cols,
        unsigned int const rows,
        xelval       const maxval,
        int          const format,
        bool         const dots,
        bool         const no_white,
        bool         const no_black,
        bool         const colorWanted[3],
        bool         const verbose,
        xelval       const startval,
        xelval       const endval,
        unsigned int const histWidth,
        unsigned int const histHeight,
        bool         const clipSpec,
        unsigned int const clipCount) {

    pixel ** pixels;
    unsigned int i;
    unsigned int * hist[3];  /* Subscript is enum wantedColor */
    double vscale;
    unsigned int hmax;

    createHist(colorWanted, histWidth, &hist);

    if ((pixels = ppm_allocarray (histWidth, histHeight)) == NULL)
        pm_error("no space for output array (%u pixels)",
                 histWidth * histHeight);
    for (i = 0; i < histHeight; ++i)
        memset(pixels[i], 0, histWidth * sizeof(pixels[i][0]));

    fillPpmBins(ifP, cols, rows, maxval, format, colorWanted, verbose,
                startval, endval, histWidth, hist);

    /* find the highest-valued slot and set the vertical scale value */
    if (verbose)
        pm_message("finding max. slot height...");
    if (clipSpec)
        hmax = clipCount;
    else 
        hmax = maxSlotCountAll(hist, histWidth, no_white, no_black);

    assert(hmax > 0);

    clipHistogramAll(hist, histWidth, hmax);

    vscale = (double) histHeight / hmax;
    if (verbose && pm_have_float_format())
        pm_message("Done: height = %u, vertical scale factor = %g", 
                   hmax, vscale);

    for (i = 0; i < histWidth; ++i) {
        if (hist[WANT_RED]) {
            unsigned int j;
            bool plotted;
            plotted = FALSE;
            for (j = histHeight - (int)(vscale * hist[WANT_RED][i]); 
                 j < histHeight && !plotted; 
                 ++j) {
                PPM_PUTR(pixels[j][i], maxval);
                plotted = dots;
            }
        }
        if (hist[WANT_GRN]) {
            unsigned int j;
            bool plotted;
            plotted = FALSE;
            for (j = histHeight - (int)(vscale * hist[WANT_GRN][i]); 
                 j < histHeight && !plotted; 
                 ++j) {
                PPM_PUTG(pixels[j][i], maxval);
                plotted = dots;
            }
        }
        if (hist[WANT_BLU]) {
            unsigned int j;
            bool plotted;
            plotted = FALSE;
            for (j = histHeight - (int)(vscale * hist[WANT_BLU][i]); 
                 j < histHeight && !plotted; 
                 ++j) {
                PPM_PUTB(pixels[j][i], maxval);
                plotted = dots;
            }
        }
    }
    ppm_writeppm(stdout, pixels, histWidth, histHeight, maxval, 0);
}



static void
reportScale(unsigned int const histWidth,
            unsigned int const range,
            bool         const verbose) {

    double const hscale = (float)(histWidth-1) / (range-1);

    if (hscale - 1.0 < epsilon && verbose && pm_have_float_format())
        pm_message("Horizontal scale factor: %g", hscale);
}



int
main(int argc, const char ** argv) {

    struct cmdlineInfo cmdline;
    FILE * ifP;
    int cols, rows;
    xelval maxval;
    int format;
    unsigned int histWidth;
    unsigned int range;
    unsigned int hmax;
    xelval startval, endval;

    pm_proginit(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    ifP = pm_openr(cmdline.inputFilespec);

    pnm_readpnminit(ifP, &cols, &rows, &maxval, &format);

    startval = cmdline.lval;
    endval   = MIN(maxval, cmdline.rval) + 1;

    range = endval - startval;

    if (cmdline.widthSpec)
        histWidth = cmdline.width;
    else
        histWidth = range;

    reportScale(histWidth, range, cmdline.verbose);
    if (cmdline.nmaxSpec)
        hmax = cols * rows / histWidth * cmdline.nmax;

    switch (PNM_FORMAT_TYPE(format)) {
    case PPM_TYPE:
        ppmHist(ifP, cols, rows, maxval, format,
                cmdline.dots, cmdline.white, cmdline.black,
                cmdline.colorWanted,
                cmdline.verbose, startval, endval,
                histWidth, cmdline.height, cmdline.nmaxSpec, hmax);
        break;
    case PGM_TYPE:
        pgmHist(ifP, cols, rows, maxval, format,
                cmdline.dots, cmdline.white, cmdline.black,
                cmdline.verbose, startval, endval,
                histWidth, cmdline.height, cmdline.nmaxSpec, hmax);
        break;
    case PBM_TYPE:
        pm_error("Cannot do a histogram of a a PBM file");
        break;
    }
    pm_close(ifP);

    return 0;
}
