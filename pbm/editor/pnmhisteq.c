/*
                 pnmhisteq.c

           Equalize histogram for a PNM image

  By Bryan Henderson 2005.09.10, based on ideas from the program of
  the same name by John Walker (kelvin@fourmilab.ch) -- March MVM.
  WWW home page: http://www.fourmilab.ch/ in 1995.

  This program is contributed to the public domain by its author.
*/

#include <string.h>

#include "pm_c_util.h"
#include "pnm.h"
#include "shhopt.h"
#include "mallocvar.h"


struct cmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    const char * inputFileName;
    unsigned int gray;
    unsigned int noblack;
    unsigned int nowhite;
    const char * wmap;
    const char * rmap;
    unsigned int verbose;
};



static void
parseCommandLine(int argc, char ** argv,
                 struct cmdlineInfo * const cmdlineP) {
/*----------------------------------------------------------------------------
   Note that the file spec array we return is stored in the storage that
   was passed to us as the argv array.
-----------------------------------------------------------------------------*/
    optEntry *option_def;
        /* Instructions to pm_optParseOptions3 on how to parse our options.
         */
    optStruct3 opt;

    unsigned int option_def_index;
    unsigned int rmapSpec, wmapSpec;

    MALLOCARRAY_NOFAIL(option_def, 100);

    option_def_index = 0;   /* incremented by OPTENT3 */
    OPTENT3(0, "rmap",     OPT_STRING, &cmdlineP->rmap, 
            &rmapSpec,          0);
    OPTENT3(0, "wmap",     OPT_STRING, &cmdlineP->wmap, 
            &wmapSpec,          0);
    OPTENT3(0, "gray",     OPT_FLAG,   NULL,
            &cmdlineP->gray,    0);
    OPTENT3(0, "noblack",     OPT_FLAG,   NULL,
            &cmdlineP->noblack,    0);
    OPTENT3(0, "nowhite",     OPT_FLAG,   NULL,
            &cmdlineP->nowhite,    0);
    OPTENT3(0, "verbose",  OPT_FLAG,   NULL,
            &cmdlineP->verbose, 0);

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = FALSE;  /* We may have parms that are negative numbers */

    pm_optParseOptions3(&argc, argv, opt, sizeof(opt), 0);
        /* Uses and sets argc, argv, and some of *cmdlineP and others. */


    if (!wmapSpec)
        cmdlineP->wmap = NULL;
    if (!rmapSpec)
        cmdlineP->rmap = NULL;

    if (argc-1 < 1)
        cmdlineP->inputFileName = "-";
    else {
        cmdlineP->inputFileName = argv[1];
        if (argc-1 > 1)
            pm_error("Too many arguments (%d).  The only argument is the "
                     "input file name.", argc-1);
    }
}



static void
computeLuminosityHistogram(xel * const *   const xels,
                           unsigned int    const rows,
                           unsigned int    const cols,
                           xelval          const maxval,
                           int             const format,
                           bool            const monoOnly,
                           unsigned int ** const lumahistP,
                           unsigned int *  const pixelCountP) {
/*----------------------------------------------------------------------------
  Scan the image and build the luminosity histogram.  If the input is
  a PPM, we calculate the luminosity of each pixel from its RGB
  components.
-----------------------------------------------------------------------------*/
    xelval lmin, lmax;
    unsigned int pixelCount;
    unsigned int * lumahist;

    MALLOCARRAY(lumahist, maxval + 1);
    if (lumahist == NULL)
        pm_error("Out of storage allocating array for %u histogram elements",
                 maxval + 1);

    {
        unsigned int i;
        /* Initialize histogram to zeroes everywhere */
        for (i = 0; i <= maxval; ++i)
            lumahist[i] = 0;
    }
    lmin = maxval;  /* initial value */
    lmax = 0;       /* initial value */

    switch (PNM_FORMAT_TYPE(format)) {
    case PGM_TYPE:
    case PBM_TYPE: {
        /* Compute intensity histogram */

        unsigned int row;

        pixelCount = rows * cols;
        for (row = 0; row < rows; ++row) {
            unsigned int col;
            for (col = 0; col < cols; ++col) {
                xelval const l = PNM_GET1(xels[row][col]);
                lmin = MIN(lmin, l);
                lmax = MAX(lmax, l);
                ++lumahist[l];
            }
        }
    }
    break;
    case PPM_TYPE: {
        unsigned int row;

        for (row = 0, pixelCount = 0; row < rows; ++row) {
            unsigned int col;
            for (col = 0; col < cols; ++col) {
                xel const thisXel = xels[row][col];
                if (!monoOnly || PPM_ISGRAY(thisXel)) {
                    xelval const l = ppm_luminosity(thisXel);

                    lmin = MIN(lmin, l);
                    lmax = MAX(lmax, l);

                    ++lumahist[l];
                    ++pixelCount;
                }
            }
        }
    }
    break;
    default:
        pm_error("invalid input format format");
    }

    *lumahistP = lumahist;
    *pixelCountP = pixelCount;
}



static void
readMapFile(const char * const rmapFileName,
            xelval       const maxval,
            gray *       const lumamap) {

    int rmcols, rmrows; 
    gray rmmaxv;
    int rmformat;
    FILE * rmapfP;
        
    rmapfP = pm_openr(rmapFileName);
    pgm_readpgminit(rmapfP, &rmcols, &rmrows, &rmmaxv, &rmformat);
    
    if (rmmaxv != maxval)
        pm_error("maxval in map file (%u) different from input (%u)",
                 rmmaxv, maxval);
    
    if (rmrows != 1)
        pm_error("Map must have 1 row.  Yours has %u", rmrows);
    
    if (rmcols != maxval + 1)
        pm_error("Map must have maxval + 1 (%u) columns.  Yours has %u",
                 maxval + 1, rmcols);
    
    pgm_readpgmrow(rmapfP, lumamap, maxval+1, rmmaxv, rmformat);
    
    pm_close(rmapfP);
}



static xelval
maxLumaPresent(const xelval * const lumahist,
               xelval         const darkestCandidate,
               xelval         const brightestCandidate) {
/*----------------------------------------------------------------------------
    The maximum luminosity in the image, in the range ['darkestCandidate',
   'brightestCandidate'], given that the luminosity histogram for the image is
   'lumahist' (lumahist[N] is the number of pixels in the image with
   luminosity N).
-----------------------------------------------------------------------------*/
    xelval maxluma;
    xelval i;

    for (i = darkestCandidate, maxluma = darkestCandidate;
         i <= brightestCandidate;
         ++i) {

        if (lumahist[i] > 0)
            maxluma = i;
    }
    return maxluma;
}



static void
equalize(const unsigned int * const lumahist,
         xelval               const darkestRemap,
         xelval               const brightestRemap,
         unsigned int         const remapPixelCount,
         gray *               const lumamap) {
/*----------------------------------------------------------------------------
   Fill in the mappings of luminosities from 'darkestRemap' through
   'brightestRemap' in 'lumamap', to achieve an equalization based on the
   histogram 'lumahist'.  lumahist[N] is the number of pixels in the original
   image of luminosity N.

   'remapPixelCount' is the number of pixels in the given luminosity range.
   It is redundant with 'lumahist'; we get it for computational convenience.
-----------------------------------------------------------------------------*/
    xelval const maxluma =
        maxLumaPresent(lumahist, darkestRemap, brightestRemap);

    unsigned int const range = brightestRemap - darkestRemap;
    
    {
        xelval origLum;
        unsigned int pixsum;

        for (origLum = darkestRemap, pixsum = 0;
             origLum <= brightestRemap;
             ++origLum) {
            
            /* With 16 bit grays, the following calculation can overflow a 32
               bit long.  So, we do it in floating point.
            */

            lumamap[origLum] =
                darkestRemap +
                ROUNDU((((double) pixsum * range)) / remapPixelCount);
            
            pixsum += lumahist[origLum];
        }

    }
    {
        double const lscale = (double)range /
            ((lumamap[maxluma] > darkestRemap) ?
             (double) lumamap[maxluma] - darkestRemap : (double) range);

        xelval origLum;

        /* Normalize so that the brightest pixels are set to maxval. */

        for (origLum = darkestRemap; origLum <= brightestRemap; ++origLum)
            lumamap[origLum] =
                MIN(brightestRemap, 
                    darkestRemap + ROUNDU(lumamap[origLum] * lscale));
    }
}



static void
computeMap(const unsigned int * const lumahist,
           xelval               const maxval,
           unsigned int         const pixelCount,
           bool                 const noblack,
           bool                 const nowhite,
           gray *               const lumamap) {
/*----------------------------------------------------------------------------
  Calculate initial histogram equalization curve.

  'lumahist' is the luminosity histogram for the image; lumahist[N] is
  the number of pixels that have luminosity N.

  'maxval' is the maxval of the image (ergo the maximum luminosity).

  'pixelCount' is the number of pixels in the image, which is redundant
  with 'lumahist' but provided for computational convenience.
   
  'noblack' means don't include the black pixels in the equalization and
  make the black pixels in the output the same ones as in the input.

  'nowhite' is equivalent for the white pixels.

  We return the map as *lumamap, where lumamap[N] is the luminosity in the
  output of a pixel with luminosity N in the input.  Its storage size must
  be at least 'maxval' + 1.
-----------------------------------------------------------------------------*/
    xelval darkestRemap, brightestRemap;
        /* The lowest and highest luminosity values that we will remap
           according to the equalization strategy.  They're just 0 and maxval
           unless modified by 'noblack' and 'nowhite'.
        */
    unsigned int remapPixelCount;
        /* The number of pixels we map according to the equalization
           strategy; it doesn't include black pixels and white pixels that
           are excluded from the equalization because of 'noblack' and
           'nowhite'
        */

    remapPixelCount = pixelCount;  /* Initial assumption */

    if (noblack) {
        lumamap[0] = 0;
        darkestRemap = 1;
        remapPixelCount -= lumahist[0];
    } else {
        darkestRemap = 0;
    }

    if (nowhite) {
        lumamap[maxval] = maxval;
        brightestRemap = maxval - 1;
        remapPixelCount -= lumahist[maxval];
    } else {
        brightestRemap = maxval;
    }

    equalize(lumahist, darkestRemap, brightestRemap, remapPixelCount,
             lumamap);
}



static void
getMapping(const char *         const rmapFileName,
           const unsigned int * const lumahist,
           xelval               const maxval,
           unsigned int         const pixelCount,
           bool                 const noblack,
           bool                 const nowhite,
           gray **              const lumamapP) {
/*----------------------------------------------------------------------------
  Calculate the luminosity mapping table which gives the
  histogram-equalized luminosity for each original luminosity.
-----------------------------------------------------------------------------*/
    gray * lumamap;

    lumamap = pgm_allocrow(maxval+1);

    if (rmapFileName)
        readMapFile(rmapFileName, maxval, lumamap);
    else
        computeMap(lumahist, maxval, pixelCount, noblack, nowhite, lumamap);

    *lumamapP = lumamap;
}



static void
reportMap(const unsigned int * const lumahist,
          xelval               const maxval,
          const gray *         const lumamap) {

    unsigned int i;

    fprintf(stderr, "  Luminosity map    Number of\n");
    fprintf(stderr, " Original    New     Pixels  \n");

    for (i = 0; i <= maxval; ++i) {
        if (lumahist[i] > 0) {
            fprintf(stderr,"%6d -> %6d  %8u\n", i,
                    lumamap[i], lumahist[i]);
        }
    }
}



static xel
scaleXel(xel    const thisXel,
         double const scaler) {
/*----------------------------------------------------------------------------
   Scale the components of 'xel' by multiplying by 'scaler'.

   Assume this doesn't cause it to exceed maxval.
-----------------------------------------------------------------------------*/
    xel retval;

    PNM_ASSIGN(retval,
               ((xelval)(PNM_GETR(thisXel) * scaler + 0.5)),
               ((xelval)(PNM_GETG(thisXel) * scaler + 0.5)),
               ((xelval)(PNM_GETB(thisXel) * scaler + 0.5)));
    
    return retval;
}



static xel
remapRgbValue(xel          const thisXel,
              xelval       const maxval,
              const gray * const lumamap) {
/*----------------------------------------------------------------------------
  Return the color 'thisXel' with its HSV value changed per 'lumamap' but
  the same hue and saturation.

  'maxval' is the maxval for 'xel' and our return value.
-----------------------------------------------------------------------------*/
    struct hsv const hsv =
        ppm_hsv_from_color(thisXel, maxval);
    xelval const oldValue =
        MIN(maxval, ROUNDU(hsv.v * maxval));
    xelval const newValue =
        lumamap[oldValue];
    
    return scaleXel(thisXel, (double)newValue/oldValue);
}



static void
remap(xel **       const xels,
      unsigned int const cols,
      unsigned int const rows,
      xelval       const maxval,
      int          const format,
      bool         const monoOnly,
      const gray * const lumamap) {
/*----------------------------------------------------------------------------
   Update the array 'xels' to have the new intensities.
-----------------------------------------------------------------------------*/
    switch (PNM_FORMAT_TYPE(format)) {
    case PPM_TYPE: {
        unsigned int row;
        for (row = 0; row < rows; ++row) {
            unsigned int col;
            for (col = 0; col < cols; ++col) {
                xel const thisXel = xels[row][col];
                if (monoOnly && PPM_ISGRAY(thisXel)) {
                    /* Leave this pixel alone */
                } else {
                    xels[row][col] = remapRgbValue(xels[row][col],
                                                   maxval, lumamap);
                }
            }
        }
    }
    break;

    case PBM_TYPE:
    case PGM_TYPE: {
        unsigned int row;
        for (row = 0; row < rows; ++row) {
            unsigned int col;
            for (col = 0; col < cols; ++col)
                PNM_ASSIGN1(xels[row][col],
                            lumamap[PNM_GET1(xels[row][col])]);
        }
    }
    break;
    }
}



static void
writeMap(const char * const wmapFileName,
         const gray * const lumamap,
         xelval       const maxval) {

    FILE * const wmapfP = pm_openw(wmapFileName);

    pgm_writepgminit(wmapfP, maxval+1, 1, maxval, 0);

    pgm_writepgmrow(wmapfP, lumamap, maxval+1, maxval, 0);

    pm_close(wmapfP);
}



int
main(int argc, char * argv[]) {

    struct cmdlineInfo cmdline;
    FILE * ifP;
    gray * lumamap;           /* Luminosity map */
    unsigned int * lumahist;  /* Histogram of luminosity values */
    int rows, cols;           /* Rows, columns of input image */
    xelval maxval;            /* Maxval of input image */
    int format;               /* Format indicator (PBM/PGM/PPM) */
    xel ** xels;              /* Pixel array */
    unsigned int pixelCount;

    pnm_init(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    ifP = pm_openr(cmdline.inputFileName);

    xels = pnm_readpnm(ifP, &cols, &rows, &maxval, &format);

    pm_close(ifP);

    computeLuminosityHistogram(xels, rows, cols, maxval, format, cmdline.gray,
                               &lumahist, &pixelCount);

    getMapping(cmdline.rmap, lumahist, maxval, pixelCount,
               cmdline.noblack > 0, cmdline.nowhite > 0,
               &lumamap);

    if (cmdline.verbose)
        reportMap(lumahist, maxval, lumamap);

    remap(xels, cols, rows, maxval, format, !!cmdline.gray, lumamap);

    pnm_writepnm(stdout, xels, cols, rows, maxval, format, 0);

    if (cmdline.wmap)
        writeMap(cmdline.wmap, lumamap, maxval);

    pgm_freerow(lumamap);

    return 0;
}
