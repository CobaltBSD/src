/*
** read a PNM/PAM image and produce a Portable Network Graphics (PNG) file
**
** derived from pnmtorast.c by Jef Poskanzer and pamrgbatopng.c by Bryan
** Henderson <bryanh@giraffe-data.com> and probably some other sources
**
** Copyright (C) 1995-1998 by Alexander Lehmann <alex@hal.rhein-main.de>
**                        and Willem van Schaik <willem@schaik.com>
** Copyright (C) 1999,2001 by Greg Roelofs <newt@pobox.com>
** Copyright (C) 2015 by Willem van Schaik <willem@schaik.com>
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
*/

/*
  This Netpbm program pamtopng was derived in 2015 from the Netpbm program
  Pnmtopng. This was a nearly complete rewrite with the following goals:

  - Add ability to create a PNG alpha channel from the alpha channel in a
    PAM (format P7) file.

  - Simplify the 20 year old pnmtopng code. Because of the many, many features
    that program implements and its need for backward compatibility, the code
    had become rather complex.  This program is roughly 1/3 the size of
    pnmtopng.c that it replaces.

  - In 1995 bandwith was limited and therefore filesize had to be kept
    small. The original program tried to optimize for that by applying
    many "clever tricks". Today that isn't an issue anymore, so gone 
    are filters, palettes, etc. Also, image conversions were removed,
    because those should be done with other NetPBM tools.

  - Add ability to create iTXt (international language) chunks.
*/


#include <stdio.h>
#include <stdlib.h>
#include <png.h>
/* setjmp.h needs to be included after png.h */
#include <setjmp.h>

#include <pbm/util/pm_c_util.h>
#include <pbm/util/mallocvar.h>
#include <pbm/util/nstring.h>
#include <pbm/util/shhopt.h>
#include <pbm/pam.h>
#include "pngx.h"
#include "pngtxt.h"


/* global variable */
static bool verbose;


struct CmdlineInfo {
    const char * inputFileName;
    unsigned int verbose;
    unsigned int transparentSpec;
    const char * transparent;
    unsigned int chromaSpec;
    struct pngx_chroma chroma;
    unsigned int gammaSpec;
    float gamma;
    unsigned int srgbintentSpec;
    pngx_srgbIntent srgbintent;
    unsigned int textSpec;
    const char * text;
    unsigned int ztxtSpec;
    const char * ztxt;
    unsigned int itxtSpec;
    const char * itxt;
    unsigned int backgroundSpec;
    const char * background;
    unsigned int timeSpec;
    time_t time;
};



static void
parseChromaOpt(const char *         const chromaOpt,
               struct pngx_chroma * const chromaP) {

    int count;
    
    count = sscanf(chromaOpt, "%f %f %f %f %f %f %f %f",
                   &chromaP->wx, &chromaP->wy,
                   &chromaP->rx, &chromaP->ry,
                   &chromaP->gx, &chromaP->gy,
                   &chromaP->bx, &chromaP->by);

    if (count != 8)
        pm_error("Invalid syntax for the -rgb option value '%s'.  "
                 "Should be 8 floating point numbers: "
                 "x and y for each of white, red, green, and blue",
                 chromaOpt);
}



static void
parseSrgbintentOpt(const char *      const srgbintentOpt,
                   pngx_srgbIntent * const srgbintentP) {
    
    if (streq(srgbintentOpt, "perceptual"))
        *srgbintentP = PNGX_PERCEPTUAL;
    else if (streq(srgbintentOpt, "relativecolorimetric"))
        *srgbintentP = PNGX_RELATIVE_COLORIMETRIC;
    else if (streq(srgbintentOpt, "saturation"))
        *srgbintentP = PNGX_SATURATION;
    else if (streq(srgbintentOpt, "absolutecolorimetric"))
        *srgbintentP = PNGX_ABSOLUTE_COLORIMETRIC;
    else
        pm_error("Unrecognized sRGB intent value '%s'.  We understand "
                 "only 'perceptual', 'relativecolorimetric', "
                 "'saturation', and 'absolutecolorimetric'",
                 srgbintentOpt);
}



static void
parseTimeOpt(const char * const timeOpt,
             time_t *     const timeP) {

    struct tm brokenTime;
    int year;
    int month;
    int count;

    count = sscanf(timeOpt, "%d-%d-%d %d:%d:%d",
                   &year,
                   &month,
                   &brokenTime.tm_mday,
                   &brokenTime.tm_hour,
                   &brokenTime.tm_min,
                   &brokenTime.tm_sec);

    if (count != 6)
        pm_error("Invalid value for -time '%s'.   It should have "
                 "the form [yy]yy-mm-dd hh:mm:ss.", timeOpt);
    
    if (year < 0)
        pm_error("Year is negative in -time value '%s'", timeOpt);
    if (year > 9999)
        pm_error("Year is more than 4 digits in -time value '%s'",
                 timeOpt);
    if (month < 0)
        pm_error("Month is negative in -time value '%s'", timeOpt);
    if (month > 12)
        pm_error("Month is >12 in -time value '%s'", timeOpt);
    if (brokenTime.tm_mday < 0)
        pm_error("Day of month is negative in -time value '%s'",
                 timeOpt);
    if (brokenTime.tm_mday > 31)
        pm_error("Day of month is >31 in -time value '%s'", timeOpt);
    if (brokenTime.tm_hour < 0)
        pm_error("Hour is negative in -time value '%s'", timeOpt);
    if (brokenTime.tm_hour > 23)
        pm_error("Hour is >23 in -time value '%s'", timeOpt);
    if (brokenTime.tm_min < 0)
        pm_error("Minute is negative in -time value '%s'", timeOpt);
    if (brokenTime.tm_min > 59)
        pm_error("Minute is >59 in -time value '%s'", timeOpt);
    if (brokenTime.tm_sec < 0)
        pm_error("Second is negative in -time value '%s'", timeOpt);
    if (brokenTime.tm_sec > 59)
        pm_error("Second is >59 in -time value '%s'", timeOpt);

    brokenTime.tm_mon = month - 1;
    if (year >= 1900)
        brokenTime.tm_year = year - 1900;
    else
        brokenTime.tm_year = year;

    /* Note that mktime() considers brokeTime to be in local time.
       This is what we want, since we got it from a user.  User should
       set his local time zone to UTC if he wants absolute time.
    */
    *timeP = mktime(&brokenTime);
}



static void
parseCommandLine (int                  argc,
                  const char **        argv,
                  struct CmdlineInfo * const cmdlineP) {
    
    optEntry * option_def;
    optStruct3 opt;
    unsigned int option_def_index = 0;  /* incremented by OPTENT3 */

    const char * srgbintent;
    const char * chroma;
    const char * time;

    MALLOCARRAY(option_def, 100);

    OPTENT3(0,  "verbose",      OPT_FLAG,       NULL,
            &cmdlineP->verbose,        0);
    OPTENT3(0,  "transparent", OPT_STRING,      &cmdlineP->transparent,
            &cmdlineP->transparentSpec, 0);
    OPTENT3(0,  "chroma",       OPT_STRING,     &chroma,
            &cmdlineP->chromaSpec,     0);
    OPTENT3(0,  "gamma",        OPT_FLOAT,      &cmdlineP->gamma,
            &cmdlineP->gammaSpec,      0);
    OPTENT3(0,  "srgbintent",   OPT_STRING,     &srgbintent,
            &cmdlineP->srgbintentSpec, 0);
    OPTENT3(0,  "text",         OPT_STRING,     &cmdlineP->text,
            &cmdlineP->textSpec,       0);
    OPTENT3(0,  "ztxt",         OPT_STRING,     &cmdlineP->ztxt,
            &cmdlineP->ztxtSpec,       0);
    OPTENT3(0,  "itxt",         OPT_STRING,     &cmdlineP->itxt,
            &cmdlineP->itxtSpec,       0);
    OPTENT3(0,  "background",   OPT_STRING,     &cmdlineP->background,
            &cmdlineP->backgroundSpec, 0);
    OPTENT3(0,  "time",         OPT_STRING,        &time,
            &cmdlineP->timeSpec,       0);

    opt.opt_table = option_def;
    opt.short_allowed = false;  /* we have no short (old-fashioned) options */
    opt.allowNegNum = false;  /* we have no parms that are negative numbers */

    /* uses and sets argc, argv, and some of *cmdlineP and others */
    pm_optParseOptions3(&argc, (char **)argv, opt, sizeof(opt), 0);

    if (cmdlineP->chromaSpec)
        parseChromaOpt(chroma, &cmdlineP->chroma);

    if (cmdlineP->srgbintentSpec)
        parseSrgbintentOpt(srgbintent, &cmdlineP->srgbintent);

    if (cmdlineP->timeSpec)
        parseTimeOpt(time, &cmdlineP->time);
    
    /* get the input-file or stdin pipe */
    if (argc-1 < 1)
        cmdlineP->inputFileName = "-";
    else if (argc-1 == 1)
        cmdlineP->inputFileName = argv[1];
    else
        pm_error("Program takes at most one argument: input file name.");

    free(option_def);
}



static png_byte
colorTypeFromInputType(const struct pam * const pamP) {
/*----------------------------------------------------------------------------
  Analyse the Netpbm image for color-type and bit-depth
-----------------------------------------------------------------------------*/
    png_byte retval;

    if (pamP->depth < 1 && pamP->depth > 4)
        pm_error ("Number of color planes must be between 1 and 4 inclusive");

    if (pamP->maxval != 1 && pamP->maxval != 3 && pamP->maxval != 15 &&
        pamP->maxval != 255 && pamP->maxval != 65535)
        pm_error("The maxval of the input image is %u; "
                 "it must be 1, 3, 15, 255 or 65535", (unsigned)pamP->maxval);

    if (strneq(pamP->tuple_type, "RGB_ALPHA", 9)) {
        if (pamP->depth == 4)
            retval = PNG_COLOR_TYPE_RGB_ALPHA;
        else
            pm_error("Input tuple type is RGB_ALPHA, "
                     "but number of planes is %u instead of 4",
                pamP->depth);
    } else if (strneq(pamP->tuple_type, "RGB", 3)) {
        if (pamP->depth == 3)
            retval = PNG_COLOR_TYPE_RGB;
        else
            pm_error("Input tuple type is RGB, "
                     "but number of planes is %u instead of 3",
                     pamP->depth);
    } else if (strneq(pamP->tuple_type, "GRAYSCALE_ALPHA", 15)) {
        if (pamP->depth == 2)
            retval = PNG_COLOR_TYPE_GRAY_ALPHA;
        else
            pm_error("Input tupel type is GRAYSCALE_ALPHA, "
                     "but number of planes is %u instread of 2",
                     pamP->depth);
    } else if (strneq(pamP->tuple_type, "GRAYSCALE", 9)) {
        if (pamP->depth == 1)
            retval = PNG_COLOR_TYPE_GRAY;
        else
            pm_error("Input tuple type is GRAYSCALE, "
                     "but number of planes is %u instead of 1",
                     pamP->depth);
     } else if (strneq(pamP->tuple_type, "BLACKANDWHITE_ALPHA", 19)) {
        if (pamP->depth != 2)
            pm_error("Input tuple type is BLACKANDWHITE_ALPHA, "
                     "but number of planes is %u instead of 2",
                     pamP->depth);
        if (pamP->maxval != 1)
            pm_error("Input tuple type is BLACKANDWHITE_ALPHA, "
                     "but maxval is %u instead of 1", (unsigned)pamP->maxval);

        retval = PNG_COLOR_TYPE_GRAY_ALPHA;
    } else if (strneq(pamP->tuple_type, "BLACKANDWHITE", 13)) {
        if (pamP->depth != 1)
            pm_error("Input tuple type is BLACKANDWHITE, "
                     "but number of planes is %u instead of 1",
                     pamP->depth);
        if (pamP->maxval != 1)
            pm_error("Input tuple type is BLACKANDWHITE, "
                     "but maxval is %u instead of 1", (unsigned)pamP->maxval);

        retval = PNG_COLOR_TYPE_GRAY;
    } else
        pm_error("Unrecognized tuple type: '%s'", pamP->tuple_type);

    return retval;
}



/*****************************************************************************
*  Subroutines that create all the (ancillary) chunks
*****************************************************************************/



static png_color_16
parseAndScaleColor(const char * const colorString,
                   xelval       const pngMaxval) {

    png_color_16 pngColor;

    if (colorString) {
        xel const inputColor = ppm_parsecolor(colorString, PNM_OVERALLMAXVAL);

        xel scaledColor;

        /* Scale the color down to the PNG bit depth */
        PPM_DEPTH(scaledColor, inputColor, PNM_OVERALLMAXVAL, pngMaxval);

        pngColor.red   = PPM_GETR(scaledColor);
        pngColor.green = PPM_GETG(scaledColor);
        pngColor.blue  = PPM_GETB(scaledColor);
        pngColor.gray  = PNM_GET1(scaledColor);
    }

    return pngColor;
}



static png_color_8
sigBitsFmImgType(unsigned int const pnmBitDepth,
                 int          const pngColorType) {
/*----------------------------------------------------------------------------
   A representation used in PNG of color resolutions in an original image.
-----------------------------------------------------------------------------*/
    png_color_8 retval;

    /* Initial values */
    if (pnmBitDepth < 8) {
        switch (pngColorType) {
        case PNG_COLOR_TYPE_RGB:
            retval.red   = pnmBitDepth;
            retval.green = pnmBitDepth;
            retval.blue  = pnmBitDepth;
            retval.gray  = 0;
            retval.alpha = 0;
            break;
        case PNG_COLOR_TYPE_RGB_ALPHA:
            retval.red   = pnmBitDepth;
            retval.green = pnmBitDepth;
            retval.blue  = pnmBitDepth;
            retval.gray  = 0;
            retval.alpha = pnmBitDepth;
            break;
        case PNG_COLOR_TYPE_GRAY:
            /* PNG can (so presumably will) use original bit depth */
            retval.red   = 0;
            retval.green = 0;
            retval.blue  = 0;
            retval.gray  = 0;
            retval.alpha = 0;
            break;
        case PNG_COLOR_TYPE_GRAY_ALPHA:
            retval.red   = 0;
            retval.green = 0;
            retval.blue  = 0;
            retval.gray  = pnmBitDepth;
            retval.alpha = pnmBitDepth;
            break;
        }
    } else {
        /* PNG can (so presumably will) use original bit depth */
        retval.red   = 0;
        retval.green = 0;
        retval.blue  = 0;
        retval.gray  = 0;
        retval.alpha = 0;
    }
    return retval;
}



static void
doTrnsChunk(const struct pam * const pamP,
            struct pngx *      const pngxP,
            const char *       const trans) {

    if (pngx_colorType(pngxP) == PNG_COLOR_TYPE_GRAY_ALPHA || 
        pngx_colorType(pngxP) == PNG_COLOR_TYPE_RGB_ALPHA)
        pm_error("Both alpha channel and transparency chunk not allowed.");
    else {
        xelval const pngMaxval = pm_bitstomaxval(pngx_bitDepth(pngxP));
        png_color_16 const pngColor = parseAndScaleColor(trans, pngMaxval);
            /* Transparent color from text format scaled from 16-bit to
               maxval.
            */

        pngx_setTrnsValue(pngxP, pngColor);

        if (verbose) {
            if (pngx_colorType(pngxP) == PNG_COLOR_TYPE_GRAY) {
                pm_message("writing tRNS chunk with color {gray} = {%u}",
                           pngColor.gray );
            } else if (pngx_colorType(pngxP) == PNG_COLOR_TYPE_RGB) {
                pm_message("writing tRNS chunk with color "
                           "{red, green, blue} = {%u, %u, %u}",
                           pngColor.red, pngColor.green, pngColor.blue);
            }
        }
    }
}



static void
doChrmChunk(struct pngx *      const pngxP,
            struct pngx_chroma const chroma) {
    
    pngx_setChrm(pngxP, chroma);

    if (verbose) {
        pm_message("writing cHRM chunk { wx, wy, rx, ry, gx, gy, bx, by } = "
                   "{ %4.2f, %4.2f, %4.2f, %4.2f, "
                   "%4.2f, %4.2f, %4.2f, %4.2f }", 
                   chroma.wx, chroma.wy,
                   chroma.rx, chroma.ry,
                   chroma.gx, chroma.gy,
                   chroma.bx, chroma.by);
    }
}



static void 
doGamaChunk(struct pngx *  const pngxP,
            float          const gamma) {

    pngx_setGama(pngxP, gamma);

    if (verbose) {
        pm_message("writing gAMA chunk with image gamma value %4.2f", gamma);
    }
}



static void
doSbitChunk(const struct pam * const pamP,
            struct pngx *      const pngxP,
            png_color_8        const sigBits) {

    if (sigBits.red + sigBits.green + sigBits.blue +
        sigBits.gray + sigBits.alpha > 0) {
        pngx_setSbit(pngxP, sigBits);
    }
}



static void
doSrgbChunk(struct pngx *   const pngxP,
            pngx_srgbIntent const srgbIntent) {

    pngx_setSrgb(pngxP, srgbIntent);

    if (verbose) {
        pm_message("writing sRGB chunk with intent value %s",
                   pngx_srgbIntentDesc(srgbIntent));
    }
}



static void
doTextChunkSet(struct pngx * const pngxP,
               const char *  const textFileName) {

    bool const ztxt = true;
    bool const itxt = false;

    FILE * tfP;

    tfP = pm_openr(textFileName);
    
    pngtxt_addChunk(pngxP, tfP, ztxt, itxt, verbose);
    
    pm_close(tfP);
}



static void
doZtxtChunkSet(struct pngx * const pngxP,
               const char *  const textFileName) {

    bool const ztxt = true;
    bool const itxt = false;

    FILE * tfP;

    tfP = pm_openr(textFileName);
    
    pngtxt_addChunk(pngxP, tfP, ztxt, itxt, verbose);
    
    pm_close(tfP);
}




static void
doItxtChunkSet(struct pngx * const pngxP,
               const char *  const textFileName) {

    bool const ztxt = true;
    bool const itxt = true;

    FILE * tfP;

    tfP = pm_openr(textFileName);

    pngtxt_addChunk(pngxP, tfP, ztxt, itxt, verbose);
}



static void
doBkgdChunk (const struct pam * const pamP,
             struct pngx *      const pngxP,
             const char *       const colorName)
{
    xelval const pngMaxval = pm_bitstomaxval(pngx_bitDepth(pngxP));

    png_color_16 const pngColor = parseAndScaleColor(colorName, pngMaxval);
        /* Background color from text format, scaled from 16-bit to maxval */

    pngx_setBkgdRgb(pngxP, pngColor);

    if (verbose) {
        if (pngx_colorType(pngxP) == PNG_COLOR_TYPE_GRAY || 
            pngx_colorType(pngxP) == PNG_COLOR_TYPE_GRAY_ALPHA) {
            pm_message("writing bKGD chunk with gray level = %u",
                       pngColor.gray);
        } else if (pngx_colorType(pngxP) == PNG_COLOR_TYPE_RGB || 
                   pngx_colorType(pngxP) == PNG_COLOR_TYPE_RGB_ALPHA) {
            pm_message("writing bKGD chunk with color {red, green, blue} = "
                       "{%u, %u, %u}",
                       pngColor.red, pngColor.green, pngColor.blue);
        }
    }
}



static void
doTimeChunk(struct pngx * const pngxP,
            time_t        const time) {

    pngx_setTime(pngxP, time);

    if (verbose) {
        struct tm * const brokenTimeP = gmtime(&time);

        char buffer[100];

        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", brokenTimeP);

        pm_message("Writing tIME chunk specifying datetime %s", buffer);
    }
}



static void
setShift(struct pngx * const pngxP,
         png_color_8   const sigBits) {

    if (sigBits.red + sigBits.green + sigBits.blue +
        sigBits.gray + sigBits.alpha > 0) {

        /* Move the 1, 2, 4 bits to most significant bits */
        pngx_setShift(pngxP, sigBits);
    }
}



static void
convertRaster(const struct pam * const pamP,
              const tuple *      const tuplerow,
              png_byte *         const pngRow,
              unsigned int       const bitDepth) {

    unsigned int col;

    /* An image row consists of columns x planes like gray or rgb(a) x 8 or 16
       bits.
    */
    for (col = 0; col < pamP->width; ++col) {
        unsigned int plane;
        for (plane = 0; plane < pamP->depth; ++plane) {
            if (bitDepth > 8) {
                /* Copy 2 bytes = 16 bits for one pixel */
                pngRow[2 * (pamP->depth * col + plane)] =
                    (tuplerow[col][plane] >> 8) & 0xff ;
                pngRow[2 * (pamP->depth * col + plane) + 1] =
                    tuplerow[col][plane] & 0xff ;
            } else {
                /* Copy 1 byte for one pixel. Later, a packing of 2, 4 or 8
                   pixels into a single byte can still happen.
                */
                pngRow[pamP->depth * col + plane] = tuplerow[col][plane];
            }
        }
    }
}



static void
writeRaster(const struct pam * const pamP,
            struct pngx *      const pngxP,
            int                const bitDepth) {

    tuple * tupleRow;
    png_byte * pngRow;
    unsigned int row;

    /* We process row-by-row and do not read the complete image into memory */

    tupleRow = pnm_allocpamrow(pamP);

    MALLOCARRAY(pngRow, pamP->width * 8);
        /* sufficient to store a 16-bit RGB+A row */

    if (pngRow == NULL)
        pm_error("Unable to allocate space for PNG pixel row for "
                 "%u columns", pamP->width);
    else {
        for (row = 0; row < pamP->height; ++row) {
            pnm_readpamrow(pamP, tupleRow);

            convertRaster(pamP, tupleRow, pngRow, bitDepth);

            png_write_row(pngxP->png_ptr, pngRow);
        }
        free(pngRow);
    }
    pnm_freepamrow(tupleRow);
}



static void
writePng(const struct pam * const pamP,
         FILE *             const ofP,
         struct CmdlineInfo const cmdline) {

    unsigned int const pnmBitDepth = pm_maxvaltobits(pamP->maxval);
    int const pngColorType = colorTypeFromInputType(pamP);

    struct pngx * pngxP;
    unsigned int pngBitDepth;
    png_color_8 sBit;

    pngx_create(&pngxP, PNGX_WRITE, NULL);



    if ((pngColorType == PNG_COLOR_TYPE_RGB ||
         pngColorType == PNG_COLOR_TYPE_RGB_ALPHA ||
         pngColorType == PNG_COLOR_TYPE_GRAY_ALPHA) &&
        pnmBitDepth < 8) {

        pngBitDepth = 8;
    } else
        pngBitDepth = pnmBitDepth;

    png_init_io(pngxP->png_ptr, ofP);

    pngx_setIhdr(pngxP, pamP->width, pamP->height,
                 pngBitDepth, pngColorType,
                 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE,
                 PNG_FILTER_TYPE_BASE);

    sBit = sigBitsFmImgType(pnmBitDepth, pngColorType);

    /* Where requested, add ancillary chunks */
    if (cmdline.transparentSpec)
        doTrnsChunk(pamP, pngxP,cmdline.transparent);

    if (cmdline.chromaSpec)
        doChrmChunk(pngxP, cmdline.chroma);

    if (cmdline.gammaSpec)
        doGamaChunk(pngxP, cmdline.gamma);

    /* no iccp */

    doSbitChunk(pamP, pngxP, sBit);

    if (cmdline.srgbintentSpec)
        doSrgbChunk(pngxP, cmdline.srgbintent);

    if (cmdline.textSpec)
        doTextChunkSet(pngxP, cmdline.text);

    if (cmdline.ztxtSpec)
        doZtxtChunkSet(pngxP, cmdline.ztxt);

    if (cmdline.itxtSpec)
        doItxtChunkSet(pngxP, cmdline.itxt);

    if (cmdline.backgroundSpec)
        doBkgdChunk(pamP, pngxP, cmdline.background);

    /* no hist */

    /* no phys */

    /* no splt */

    if (cmdline.timeSpec)
        doTimeChunk(pngxP, cmdline.time);

    setShift(pngxP, sBit);

    /* Write the ancillary chunks to PNG file */
    pngx_writeInfo(pngxP);

    if (pngColorType != PNG_COLOR_TYPE_GRAY && pnmBitDepth < 8) {
        /* Move the 1, 2, 4 bits to most significant bits */
        pngx_setShift(pngxP, sBit);
    }
    if ((pngColorType == PNG_COLOR_TYPE_GRAY) && (pnmBitDepth < 8)) {
        /* Pack multiple pixels in a byte */
        pngx_setPacking(pngxP);
    }

    writeRaster(pamP, pngxP, pnmBitDepth);

    pngx_writeEnd(pngxP);
    pngx_destroy(pngxP);
}




static void
reportInputFormat(const struct pam * const pamP) {

    const char * formatDesc;

    if (pamP->format == PBM_FORMAT || pamP->format == RPBM_FORMAT)
        formatDesc = "PBM";
    else if (pamP->format == PGM_FORMAT || pamP->format == RPGM_FORMAT)
        formatDesc = "PGM";
    else if (pamP->format == PPM_FORMAT || pamP->format == RPPM_FORMAT)
        formatDesc = "PPM";
    else if (pamP->format == PAM_FORMAT)
        formatDesc = "PAM";
    else
        formatDesc = NULL;

    if (formatDesc)
        pm_message("Input format = %s", formatDesc);
    else
        pm_message("Unrecognized input format, format code = 0x%x",
                   pamP->format);

    pm_message("Input tuple type = '%s'", pamP->tuple_type);
    pm_message("Input depth = %u", pamP->depth);
    pm_message("Input maxval = %u", (unsigned int) pamP->maxval);
}



int
main(int           argc,
     const char ** argv) {

    FILE * ifP;
    struct CmdlineInfo cmdline;
    struct pam pam;

    pm_proginit(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    verbose = cmdline.verbose;

    ifP = pm_openr(cmdline.inputFileName);

    pnm_readpaminit(ifP, &pam, PAM_STRUCT_SIZE(tuple_type));

    if (verbose)
        reportInputFormat(&pam);

    writePng(&pam, stdout, cmdline);

    pm_close(ifP);

    return 0;
}



