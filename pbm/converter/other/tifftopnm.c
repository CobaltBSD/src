/*
** tifftopnm.c - converts a Tagged Image File to a portable anymap
**
** Derived by Jef Poskanzer from tif2ras.c, which is:
**
** Copyright (c) 1990 by Sun Microsystems, Inc.
**
** Author: Patrick J. Naughton
** naughton@wind.sun.com
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted,
** provided that the above copyright notice appear in all copies and that
** both that copyright notice and this permission notice appear in
** supporting documentation.
**
** This file is provided AS IS with no warranties of any kind.  The author
** shall have no liability with respect to the infringement of copyrights,
** trade secrets or any patents by this file or any part thereof.  In no
** event will the author be liable for any lost revenue or profits or
** other special, indirect and consequential damages.
*/

/* Design note:

   We have two different ways of converting from Tiff, as provided by the
   Tiff library:  

   1) decode the entire image into memory at once, using
      TIFFRGBAImageGet(), then convert to PNM and output row by row.
   
   2) read, convert, and output one row at a time using TIFFReadScanline().

   (1) is preferable because the Tiff library does more of the work, which
   means it understands more of the Tiff format possibilities now and in 
   the future.  Also, some compressed TIFF formats don't allow you to 
   extract an individual row.

   (2) uses far less memory, and because our code does more of the work,
   it's possible that it can be more flexible or at least give better
   diagnostic information if there's something wrong with the TIFF.

   In Netpbm, we stress function over performance, so by default we
   try (1) first, and if we can't get enough memory for the decoded
   image or TIFFRGBAImageGet() fails, we fall back to (2).  But we
   give the user the -byrow option to order (2) only.
*/

#define _BSD_SOURCE 1      /* Make sure strdup() is in string.h */
#define _XOPEN_SOURCE 500  /* Make sure strdup() is in string.h */

#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "pm_c_util.h"
#include "shhopt.h"
#include "mallocvar.h"
#include "nstring.h"
#include "pnm.h"

/* See warning about tiffio.h in pamtotiff.c */
#include <tiffio.h>

/* The following are in current tiff.h, but so that we can compile against
   older tiff libraries, we define them here.
*/

#ifndef PHOTOMETRIC_LOGL
#define PHOTOMETRIC_LOGL 32844
#endif
#ifndef PHOTOMETRIC_LOGLUV
#define PHOTOMETRIC_LOGLUV 32845
#endif

#define MAXCOLORS 1024
#ifndef PHOTOMETRIC_DEPTH
#define PHOTOMETRIC_DEPTH 32768
#endif

struct CmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    char * inputFilename;
    unsigned int headerdump;
    char * alphaFilename;
    bool alphaStdout;
    unsigned int respectfillorder;   /* -respectfillorder option */
    unsigned int byrow;
    unsigned int orientraw;
    unsigned int verbose;
};



static void
parseCommandLine(int argc, const char ** const argv,
                 struct CmdlineInfo * const cmdlineP) {
/*----------------------------------------------------------------------------
   Note that many of the strings that this function returns in the
   *cmdlineP structure are actually in the supplied argv array.  And
   sometimes, one of these strings is actually just a suffix of an entry
   in argv!
-----------------------------------------------------------------------------*/
    optStruct3 opt;
    optEntry *option_def;
    unsigned int option_def_index;
    unsigned int alphaSpec;

    MALLOCARRAY_NOFAIL(option_def, 100);

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;
    opt.allowNegNum = FALSE;

    option_def_index = 0;   /* incremented by OPTENT3 */
    OPTENT3(0, "verbose", 
            OPT_FLAG,   NULL, &cmdlineP->verbose,              0);
    OPTENT3(0, "respectfillorder", 
            OPT_FLAG,   NULL, &cmdlineP->respectfillorder,     0);
    OPTENT3(0,   "byrow",   
            OPT_FLAG,   NULL, &cmdlineP->byrow,                0);
    OPTENT3(0,   "orientraw",   
            OPT_FLAG,   NULL, &cmdlineP->orientraw,            0);
    OPTENT3('h', "headerdump", 
            OPT_FLAG,   NULL, &cmdlineP->headerdump,           0);
    OPTENT3(0,   "alphaout",   
            OPT_STRING, &cmdlineP->alphaFilename, &alphaSpec,  0);

    pm_optParseOptions3(&argc, (char **)argv, opt, sizeof(opt), 0);

    if (argc - 1 == 0)
        cmdlineP->inputFilename = strdup("-");  /* he wants stdin */
    else if (argc - 1 == 1)
        cmdlineP->inputFilename = strdup(argv[1]);
    else 
        pm_error("Too many arguments.  The only argument accepted "
                 "is the input file name");

    if (alphaSpec) {
        if (streq(cmdlineP->alphaFilename, "-"))
            cmdlineP->alphaStdout = TRUE;
        else
            cmdlineP->alphaStdout = FALSE;
    } else {
        cmdlineP->alphaFilename = NULL;
        cmdlineP->alphaStdout = FALSE;
    }
}



static TIFF *
newTiffImageObject(const char * const inputFileName) {
/*----------------------------------------------------------------------------
   Create a TIFF library object for accessing the TIFF input in file
   named 'inputFileName'.  If 'inputFileName' is "-", that means
   Standard Input.
-----------------------------------------------------------------------------*/
    const char * const tiffSourceName =
        streq(inputFileName, "-") ? "Standard Input" : inputFileName;

    TIFF * retval;

    retval = TIFFFdOpen(fileno(pm_openr_seekable(inputFileName)),
                        tiffSourceName,
                        "r");

    if (retval == NULL)
        pm_error("Failed to access input file.  The OS opened the file fine, "
                 "but the TIFF library's TIFFFdOpen rejected the open file.");

    return retval;
}



static void
getBps(TIFF *           const tif,
       unsigned short * const bpsP) {

    unsigned short tiffBps;
    unsigned short bps;
    int rc;

    rc = TIFFGetField(tif, TIFFTAG_BITSPERSAMPLE, &tiffBps);
    bps = (rc == 0) ? 1 : tiffBps;

    if (bps < 1 || (bps > 8 && bps != 16 && bps != 32))
        pm_error("This program can process Tiff images with only "
                 "1-8 or 16 bits per sample.  The input Tiff image "
                 "has %hu bits per sample.", bps);
    else
        *bpsP = bps;
}



struct tiffDirInfo {
    /* 'width' and 'height' are the dimensions of the raster matrix in
       the TIFF stream -- what the TIFF spec calls the image.  The
       dimensions of the actual visual image represented may be the
       reverse, because the raster can represent the visual image in
       various orientations, as described by 'orientation'.
    */
    unsigned int   width;
    unsigned int   height;
    unsigned short bps;
    unsigned short spp;
    unsigned short photomet;
    unsigned short planarconfig;
    unsigned short fillorder;
    unsigned short orientation;
};



static void
tiffToImageDim(unsigned int   const tiffCols,
               unsigned int   const tiffRows,
               unsigned short const orientation,
               unsigned int * const imageColsP,
               unsigned int * const imageRowsP) {

    switch (orientation) {
    case ORIENTATION_TOPLEFT:
    case ORIENTATION_TOPRIGHT:
    case ORIENTATION_BOTRIGHT:
    case ORIENTATION_BOTLEFT:
        *imageColsP = tiffCols;
        *imageRowsP = tiffRows;
        break;
    case ORIENTATION_LEFTTOP:
    case ORIENTATION_RIGHTTOP:
    case ORIENTATION_RIGHTBOT:
    case ORIENTATION_LEFTBOT:
        *imageColsP = tiffRows;
        *imageRowsP = tiffCols;
        break;
    default:
        pm_error("Invalid value for orientation tag in TIFF directory: %u",
                 orientation);
    }
}



static void
getTiffDimensions(TIFF *         const tiffP,
                  unsigned int * const colsP,
                  unsigned int * const rowsP) {
/*----------------------------------------------------------------------------
   Return the dimensions of the image represented by *tiffP.  Not the
   dimensions of the internal raster matrix -- the dimensions of the
   actual visual image.
-----------------------------------------------------------------------------*/
    int ok;

    unsigned int width, length;
    unsigned short tiffOrientation;
    unsigned short orientation;
    int present;

    ok = TIFFGetField(tiffP, TIFFTAG_IMAGEWIDTH, &width);
    if (!ok)
        pm_error("Input Tiff file is invalid.  It has no IMAGEWIDTH tag.");
    ok = TIFFGetField(tiffP, TIFFTAG_IMAGELENGTH, &length);
    if (!ok)
        pm_error("Input Tiff file is invalid.  It has no IMAGELENGTH tag.");

    present = TIFFGetField(tiffP, TIFFTAG_ORIENTATION, &tiffOrientation);
    orientation = present ? tiffOrientation : ORIENTATION_TOPLEFT;

    tiffToImageDim(width, length, orientation, colsP, rowsP);
}



static void 
readDirectory(TIFF *               const tiffP,
              bool                 const headerdump,
              struct tiffDirInfo * const headerP) {
/*----------------------------------------------------------------------------
   Read various values of TIFF tags from the TIFF directory, and
   default them if not in there and make guesses where values are
   invalid.  Exit program with error message if required tags aren't
   there or values are inconsistent or beyond our capabilities.  if
   'headerdump' is true, issue informational messages about what we
   find.

   The TIFF library is capable of returning invalid values (if the
   input file contains invalid values).  We generally return those
   invalid values to our caller.
-----------------------------------------------------------------------------*/
    int rc;
    unsigned short tiffSpp;

    if (headerdump)
        TIFFPrintDirectory(tiffP, stderr, TIFFPRINT_NONE);

    getBps(tiffP, &headerP->bps);

    rc = TIFFGetFieldDefaulted(tiffP, TIFFTAG_FILLORDER, &headerP->fillorder);
    rc = TIFFGetField(tiffP, TIFFTAG_SAMPLESPERPIXEL, &tiffSpp);
    headerP->spp = (rc == 0) ? 1 : tiffSpp;

    rc = TIFFGetField(tiffP, TIFFTAG_PHOTOMETRIC, &headerP->photomet);
    if (rc == 0)
        pm_error("PHOTOMETRIC tag is not in Tiff file.  "
                 "TIFFGetField() of it failed.\n"
                 "This means the input is not valid Tiff.");

    if (headerP->spp > 1) {
        rc = TIFFGetField(tiffP, TIFFTAG_PLANARCONFIG, &headerP->planarconfig);
        if (rc == 0)
            pm_error("PLANARCONFIG tag is not in Tiff file, though it "
                     "has more than one sample per pixel.  "
                     "TIFFGetField() of it failed.  This means the input "
                     "is not valid Tiff.");
    } else
        headerP->planarconfig = PLANARCONFIG_CONTIG;

    switch (headerP->planarconfig) {
    case PLANARCONFIG_CONTIG:
        break;
    case PLANARCONFIG_SEPARATE:
        if (headerP->photomet != PHOTOMETRIC_RGB && 
            headerP->photomet != PHOTOMETRIC_SEPARATED)
            pm_error("This program can handle separate planes only "
                     "with RGB (PHOTOMETRIC tag = %u) or SEPARATED "
                     "(PHOTOMETRIC tag = %u) data.  The input Tiff file " 
                     "has PHOTOMETRIC tag = %hu.",
                     PHOTOMETRIC_RGB, PHOTOMETRIC_SEPARATED,
                     headerP->photomet);
        break;
    default:
        pm_error("Unrecognized PLANARCONFIG tag value in Tiff input: %u.\n",
                 headerP->planarconfig);
    }

    rc = TIFFGetField(tiffP, TIFFTAG_IMAGEWIDTH, &headerP->width);
    if (rc == 0)
        pm_error("Input Tiff file is invalid.  It has no IMAGEWIDTH tag.");
    rc = TIFFGetField(tiffP, TIFFTAG_IMAGELENGTH, &headerP->height);
    if (rc == 0)
        pm_error("Input Tiff file is invalid.  It has no IMAGELENGTH tag.");

    {
        unsigned short tiffOrientation;
        int present;
        present = TIFFGetField(tiffP, TIFFTAG_ORIENTATION, &tiffOrientation);
        headerP->orientation =
            present ? tiffOrientation : ORIENTATION_TOPLEFT;
    }
    if (headerdump) {
        pm_message("%ux%ux%u raster matrix, oriented %u",
                   headerP->width, headerP->height,
                   headerP->bps * headerP->spp, headerP->orientation);
        pm_message("%hu bits/sample, %hu samples/pixel",
                   headerP->bps, headerP->spp);
    }
}



static void
readscanline(TIFF *          const tif, 
             unsigned char * const scanbuf,
             int             const row, 
             int             const plane,
             unsigned int    const cols, 
             unsigned short  const bps,
             unsigned short  const spp,
             unsigned short  const fillorder,
             unsigned int *  const samplebuf) {
/*----------------------------------------------------------------------------
   Read one scanline out of the Tiff input and store it into samplebuf[].
   Unlike the scanline returned by the Tiff library function, samplebuf[]
   is composed of one sample per array element, which makes it easier for
   our caller to process.

   scanbuf[] is a scratch array for our use, which is big enough to hold
   a Tiff scanline.
-----------------------------------------------------------------------------*/
    int rc;
    unsigned int const bpsmask = (1 << bps) - 1;
      /* A mask for taking the lowest 'bps' bits of a number */

    /* The TIFFReadScanline man page doesn't tell the format of its
       'buf' return value, but it is exactly the same format as the 'buf'
       input to TIFFWriteScanline.  The man page for that doesn't say 
       anything either, but the source code for Pamtotiff contains a
       specification.
    */

    rc = TIFFReadScanline(tif, scanbuf, row, plane);

    if (rc < 0)
        pm_error( "Unable to read row %d, plane %d of input Tiff image.  "
                  "TIFFReadScanline() failed.",
                  row, plane);
    else if (bps == 8) {
        unsigned int sample;
        for (sample = 0; sample < cols * spp; ++sample) 
            samplebuf[sample] = scanbuf[sample];
    } else if (bps < 8) {
        /* Note that in this format, samples do not span bytes.  Rather,
           each byte may have don't-care bits in the right-end positions.
           At least that's how I infer the format from reading pnmtotiff.c
           -Bryan 00.11.18
           */
        unsigned int sample;
        unsigned int bitsleft;
        unsigned char * inP;

        for (sample = 0, bitsleft = 8, inP = scanbuf; 
             sample < cols * spp; 
             ++sample) {
            if (bitsleft == 0) {
                ++inP; 
                bitsleft = 8;
            } 
            switch (fillorder) {
            case FILLORDER_MSB2LSB:
                samplebuf[sample] = (*inP >> (bitsleft-bps)) & bpsmask; 
                break;
            case FILLORDER_LSB2MSB:
                samplebuf[sample] = (*inP >> (8-bitsleft)) & bpsmask;
                break;
            default:
                pm_error("Internal error: invalid value for fillorder: %u", 
                         fillorder);
            }
            assert(bitsleft >= bps);
            bitsleft -= bps; 
            if (bitsleft < bps)
                /* Don't count dregs at end of byte */
                bitsleft = 0;
       }
    } else if (bps == 16) {
        /* Before Netpbm 9.17, this program assumed that scanbuf[]
           contained an array of bytes as read from the Tiff file.  In
           fact, in this bps == 16 case, it's an array of "shorts",
           each stored in whatever format this platform uses (which is
           none of our concern).  The pre-9.17 code also presumed that
           the TIFF "FILLORDER" tag determined the order in which the
           bytes of each sample appear in a TIFF file, which is
           contrary to the TIFF spec.  
        */
        const uint16 * const scanbuf16 = (const uint16 *) scanbuf;
        unsigned int sample;

        for (sample = 0; sample < cols*spp; ++sample)
            samplebuf[sample] = scanbuf16[sample];
    } else if (bps == 32) {
        const uint32 * const scanbuf32 = (const uint32 *) scanbuf;
        unsigned int sample;
        
        for (sample = 0; sample < cols * spp; ++sample)
            samplebuf[sample] = scanbuf32[sample];
    } else 
        pm_error("Internal error: invalid bits per sample passed to "
                 "readscanline()");
}



static void
pick_cmyk_pixel(unsigned int const samplebuf[],
                int          const sampleCursor,
                xelval *     const redP,
                xelval *     const bluP,
                xelval *     const grnP) {

    /* Note that the TIFF spec does not say which of the 4 samples is
       which, but common sense says they're in order C,M,Y,K.  Before
       Netpbm 10.21 (March 2004), we assumed C,Y,M,K for some reason.
       But combined with a compensating error in the CMYK->RGB
       calculation, it had the same effect as C,M,Y,K.
    */
    unsigned int const c = samplebuf[sampleCursor + 0];
    unsigned int const m = samplebuf[sampleCursor + 1];
    unsigned int const y = samplebuf[sampleCursor + 2];
    unsigned int const k = samplebuf[sampleCursor + 3];

    /* The CMYK->RGB formula used by TIFFRGBAImageGet() in the TIFF 
       library is the following, (with some apparent confusion with
       the names of the yellow and magenta pigments being reversed).

       R = (1-K)*(1-C)     (with C,Y,M,K normalized to 0..1)
       G = (1-K)*(1-M)
       B = (1-K)*(1-Y)

       We used that too before Netpbm 10.21 (March 2004).

       Now we use the inverse of what Pnmtotiffcmyk has always used, which
       makes sense as follows:  A microliter of black ink is simply a 
       substitute for a microliter each of cyan, magenta, and yellow ink.
       Yellow ink removes blue light from what the white paper reflects.  
    */

    *redP = 255 - MIN(255, c + k);
    *grnP = 255 - MIN(255, m + k);
    *bluP = 255 - MIN(255, y + k);
}



static void
computeFillorder(unsigned short   const fillorderTag, 
                 unsigned short * const fillorderP, 
                 bool             const respectfillorder) {

    if (respectfillorder) {
        if (fillorderTag != FILLORDER_MSB2LSB && 
            fillorderTag != FILLORDER_LSB2MSB)
            pm_error("Invalid value in Tiff input for the FILLORDER tag: %u.  "
                     "Valid values are %u and %u.  Try omitting the "
                     "-respectfillorder option.", 
                     fillorderTag, FILLORDER_MSB2LSB, FILLORDER_LSB2MSB);
        else
            *fillorderP = fillorderTag;
    } else {
        *fillorderP = FILLORDER_MSB2LSB;
        if (fillorderTag != *fillorderP)
            pm_message("Warning: overriding FILLORDER tag in the tiff input "
                       "and assuming msb-to-lsb.  Consider the "
                       "-respectfillorder option.");
    }
}



static void
analyzeImageType(TIFF *             const tif, 
                 unsigned short     const bps, 
                 unsigned short     const spp, 
                 unsigned short     const photomet,
                 xelval *           const maxvalP, 
                 int *              const formatP, 
                 xel *              const colormap,
                 bool               const headerdump,
                 struct CmdlineInfo const cmdline) {

    bool grayscale; 

        /* How come we don't deal with the photometric for the monochrome 
           case (make sure it's one we know)?  -Bryan 00.03.04
        */
        switch (photomet) {
        case PHOTOMETRIC_MINISBLACK:
        case PHOTOMETRIC_MINISWHITE:
            if (spp != 1)
                pm_error("This grayscale image has %d samples per pixel.  "
                         "We understand only 1.", spp);
            grayscale = TRUE;
            *maxvalP = pm_bitstomaxval(MIN(bps,16));
            if (headerdump)
                pm_message("grayscale image, (min=%s) output maxval %u ", 
                           photomet == PHOTOMETRIC_MINISBLACK ? 
                           "black" : "white",
                           *maxvalP
                           );
            break;
            
        case PHOTOMETRIC_PALETTE: {
            int i;
            int numcolors;
            unsigned short* redcolormap;
            unsigned short* greencolormap;
            unsigned short* bluecolormap;

            if (headerdump)
                pm_message("colormapped");

            if (spp != 1)
                pm_error("This paletted image has %d samples per pixel.  "
                         "We understand only 1.", spp);

            if (!TIFFGetField(tif, TIFFTAG_COLORMAP, 
                              &redcolormap, &greencolormap, &bluecolormap))
                pm_error("error getting colormaps");

            numcolors = 1 << bps;
            if (numcolors > MAXCOLORS)
                pm_error("too many colors");
            *maxvalP = PNM_MAXMAXVAL;
            grayscale = FALSE;
            for (i = 0; i < numcolors; ++i) {
                xelval r, g, b;
                r = (long) redcolormap[i] * PNM_MAXMAXVAL / 65535L;
                g = (long) greencolormap[i] * PNM_MAXMAXVAL / 65535L;
                b = (long) bluecolormap[i] * PNM_MAXMAXVAL / 65535L;
                PPM_ASSIGN(colormap[i], r, g, b);
            }
        }
        break;

        case PHOTOMETRIC_SEPARATED: {
            unsigned short inkset;

            if (headerdump)
                pm_message("color separation");
            if (TIFFGetField(tif, TIFFTAG_INKNAMES, &inkset) == 1
                && inkset != INKSET_CMYK)
            if (inkset != INKSET_CMYK) 
                pm_error("This color separation file uses an inkset (%d) "
                         "we can't handle.  We handle only CMYK.", inkset);
            if (spp != 4) 
                pm_error("This CMYK color separation file is %d samples per "
                         "pixel.  "
                         "We need 4 samples, though: C, M, Y, and K.  ",
                         spp);
            grayscale = FALSE;
            *maxvalP = (1 << bps) - 1;
        }
        break;
            
        case PHOTOMETRIC_RGB:
            if (headerdump)
                pm_message("RGB truecolor");
            grayscale = FALSE;

            if (spp != 3 && spp != 4)
                pm_error("This RGB image has %d samples per pixel.  "
                         "We understand only 3 or 4.", spp);

            *maxvalP = (1 << bps) - 1;
            break;

        case PHOTOMETRIC_MASK:
            pm_error("don't know how to handle PHOTOMETRIC_MASK");

        case PHOTOMETRIC_DEPTH:
            pm_error("don't know how to handle PHOTOMETRIC_DEPTH");

        case PHOTOMETRIC_YCBCR:
            pm_error("don't know how to handle PHOTOMETRIC_YCBCR");

        case PHOTOMETRIC_CIELAB:
            pm_error("don't know how to handle PHOTOMETRIC_CIELAB");

        case PHOTOMETRIC_LOGL:
            pm_error("don't know how to handle PHOTOMETRIC_LOGL");

        case PHOTOMETRIC_LOGLUV:
            pm_error("don't know how to handle PHOTOMETRIC_LOGLUV");
            
        default:
            pm_error("unknown photometric: %d", photomet);
        }
    if (*maxvalP > PNM_OVERALLMAXVAL)
        pm_error("bits/sample (%d) in the input image is too large.",
                 bps);
    if (grayscale) {
        if (*maxvalP == 1) {
            *formatP = PBM_TYPE;
            pm_message("writing PBM file");
        } else {
            *formatP = PGM_TYPE;
            pm_message("writing PGM file");
        }
    } else {
        *formatP = PPM_TYPE;
        pm_message("writing PPM file");
    }
}



typedef struct {
    FILE *       imageoutFileP;
        /* The stream to which we write the PNM image.  Null for none. */
    FILE *       alphaFileP;
        /* The stream to which we write the alpha channel.  Null for none. */
    unsigned int inCols;
        /* Width of each row that gets passed to this object */
    unsigned int inRows;
        /* Number of rows that get passed to this object */
    unsigned int outCols;
        /* Width of each row this object writes out to the file */
    unsigned int outRows;
        /* Number of rows this object writes out */
    xelval       maxval;
        /* Maxval of the output image */
    int          format;
        /* Format of the output image */
    gray         alphaMaxval;
        /* Maxval of the alpha channel */
    bool         flipping;
        /* We're passing rows through a Pamflip process, rather than writing
           them directly to *imageoutFileP, *alphaFileP.
        */
    FILE *       imagePipeP;
        /* Stream hooked up to pipe that goes to a Pamflip process.
           Meaningful only when 'flipping' is true.
        */
    FILE *       alphaPipeP;
        /* Stream hooked up to pipe that goes to a Pamflip process.
           Meaningful only when 'flipping' is true.
        */
    pid_t        imageFlipPid;
        /* Process ID of the Pamflip process.
           Meaningful only when 'flipping' is true.
        */
    pid_t        alphaFlipPid;
        /* Process ID of the Pamflip process.
           Meaningful only when 'flipping' is true.
        */
} pnmOut;



static const char *
xformNeeded(unsigned short const tiffOrientation) {
/*----------------------------------------------------------------------------
   Return the value of the Pamflip -xform option that causes Pamflip
   to change a raster from orienation 'tiffOrientation' to Row 0 top,
   Column 0 left.
-----------------------------------------------------------------------------*/
    switch (tiffOrientation) {
    case ORIENTATION_TOPLEFT:  return "";
    case ORIENTATION_TOPRIGHT: return "leftright";
    case ORIENTATION_BOTRIGHT: return "topbottom,leftright";
    case ORIENTATION_BOTLEFT:  return "topbottom";
    case ORIENTATION_LEFTTOP:  return "transpose";
    case ORIENTATION_RIGHTTOP: return "transpose,leftright";
    case ORIENTATION_RIGHTBOT: return "transpose,topbottom,leftright";
    case ORIENTATION_LEFTBOT:  return "transpose,topbottom";
    default:
        pm_error("Invalid value for orientation tag in TIFF directory: %u",
                 tiffOrientation);
        return "";
    }
}



/* File descriptors array indices for use with pipe() */
#define PIPE_READ 0
#define PIPE_WRITE 1

static void
spawnWithInputPipe(const char *  const shellCmd,
                   FILE **       const pipePP,
                   pid_t *       const pidP,
                   const char ** const errorP) {

    int fd[2];
    int rc;

    rc = pm_pipe(fd);

    if (rc != 0)
        pm_asprintf(errorP, "Failed to create pipe for process input.  "
                    "Errno=%d (%s)", errno, strerror(errno));
    else {
        int iAmParent;
        pid_t childPid;

        pm_fork(&iAmParent, &childPid, errorP);

        if (!*errorP) {
            if (iAmParent) {
                close(fd[PIPE_READ]);

                *pidP   = childPid;
                *pipePP = fdopen(fd[PIPE_WRITE], "w");
                
                if (*pipePP == NULL)
                    pm_asprintf(errorP,"Unable to create stream from pipe.  "
                                "fdopen() fails with errno=%d (%s)",
                                errno, strerror(errno));
                else
                    *errorP = NULL;
            } else {
                int rc;
                close(fd[PIPE_WRITE]);
                close(STDIN_FILENO);
                dup2(fd[PIPE_READ], STDIN_FILENO);

                rc = system(shellCmd);

                exit(rc);
            }
        }
    }
}

                  

static void
createFlipProcess(FILE *         const outFileP,
                  unsigned short const orientation,
                  bool           const verbose,
                  FILE **        const inPipePP,
                  pid_t *        const pidP) {
/*----------------------------------------------------------------------------
   Create a process that runs the program Pamflip and writes its output
   to *imageoutFileP.

   The process takes its input from a pipe that we create.  We return as
   *inPipePP a file stream connected to the other end of that pipe.

   I.e. Caller will write a Netpbm file stream to **inPipePP and a flipped
   version of it will go to *outFileP.

   The flipping it does turns the input from orientation 'orientation'
   to Netpbm orientation, i.e. raster row 0 top, raster column 0 left,
   where the raster stream is divided into rows, with row 0 being first
   in the stream, and column 0 being first within each row.

   Caller must close *inPipePP when he is done.
-----------------------------------------------------------------------------*/
    const char * pamflipCmd;
    const char * error;

    /* Hooking up the process to the output stream is kind of tricky
       because the stream (FILE *) is an entity local to this process.
       We just assume that nothing in this process actually touches
       the stream so that having the process write to the underlying
       file descriptor is equivalent to writing to the stream.
    */

    pm_asprintf(&pamflipCmd, "pamflip -xform=%s >&%u",
                xformNeeded(orientation), fileno(outFileP));

    if (verbose)
        pm_message("Reorienting raster with shell command '%s'", pamflipCmd);

    spawnWithInputPipe(pamflipCmd, inPipePP, pidP, &error);

    if (error) {
        pm_error("Shell command '%s', to reorient the TIFF "
                 "raster, failed.  %s.  To work around this, you can use "
                 "the -orientraw option.", pamflipCmd, error);

        pm_strfree(error);
    }
}



static void
setupFlipper(pnmOut *       const pnmOutP,
             unsigned short const orientation,
             bool           const flipIfNeeded,
             bool           const orientraw,
             bool           const verbose,
             bool *         const flipOkP,
             bool *         const noflipOkP) {
/*----------------------------------------------------------------------------
   Set up the Pamflip processes to flip the raster, where needed.

   Whether we need a Pamflip process is a complex decision.  For
   reasons of efficiency and robustness, we don't want one unless
   flipping is actually required.  Flipping is not required if the
   TIFF image is already oriented like a PNM.  It also isn't required
   if the user explicitly asks for raw orientation.  Finally, it's not
   required when the user is using the TIFF library whole-image
   conversion services, because they do the flipping and thus the
   'pnmOut' object will see properly oriented pixels as input.

   'flipIfNeeded' says to set up the flipping pipe if 'orientation'
   indicates something other than standard PNM orientation.

   'orientation' is the orientation of the TIFF raster.

   'orientraw' says the final output should be in the same
   orientation, 'orientation', not the proper PNM orientation.

   *flipOkP means that as we set up the pnmOut object,
   it is OK if Caller flips the raster on his own.  *noflipOk means
   is is OK if Caller does not flip the raster on his own.  Note
   that they are both true if the raster is already in the PNM
   orientation, because then flipping is idempotent.
-----------------------------------------------------------------------------*/

    if (orientation == ORIENTATION_TOPLEFT) {
        /* Ah, the easy case.  Flipping and not flipping are identical,
           so none of the other parameters matter.  Just write directly
           to the output file and let Caller flip or not flip as he
           wishes.
        */
        pnmOutP->flipping = FALSE;
        *flipOkP   = TRUE;
        *noflipOkP = TRUE;
    } else {
        if (orientraw) {
            /* Raster is not to be flipped, so go directly to file,
               and tell Caller not to flip it either.
            */
            pnmOutP->flipping = FALSE;
            *flipOkP   = FALSE;
            *noflipOkP = TRUE;
        } else {            
            if (flipIfNeeded) {
                if (verbose)
                    pm_message("Transforming raster with Pamflip");

                if (pnmOutP->alphaFileP)
                    createFlipProcess(pnmOutP->alphaFileP, orientation,
                                      verbose,
                                      &pnmOutP->alphaPipeP,
                                      &pnmOutP->alphaFlipPid);
                if (pnmOutP->imageoutFileP)
                    createFlipProcess(pnmOutP->imageoutFileP, orientation,
                                      verbose,
                                      &pnmOutP->imagePipeP,
                                      &pnmOutP->imageFlipPid);
                
                /* The stream will flip it, so Caller must not: */
                pnmOutP->flipping = TRUE;
                *flipOkP   = FALSE;
                *noflipOkP = TRUE;
            } else {
                /* It needs flipping, but Caller doesn't want us to do it.
                   So Caller must do it:
                */
                pnmOutP->flipping = FALSE;
                *flipOkP   = TRUE;
                *noflipOkP = FALSE;
            }
        }
    }
}



static void
computeOutputDimensions(unsigned int       const tiffCols,
                        unsigned int       const tiffRows,
                        unsigned short     const orientation,
                        bool               const orientraw,
                        unsigned int *     const colsP,
                        unsigned int *     const rowsP,
                        bool               const verbose) {
/*----------------------------------------------------------------------------
   Compute the dimensions of the image.  We're talking about the
   actual image, not what the TIFF spec calls the image.  What the
   TIFF spec calls the image is matrix of pixels within the TIFF file.
   That matrix can represent the actual image in various ways.
   E.g. the first row of the matrix might be the right edge of the
   image.

   'tiffCols' and 'tiffRows' are the images of the TIFF matrix and
   'orientation' is the orientation of that matrix.

   'orientraw' says we want to output the matrix in its natural
   orientation, not the true image.
-----------------------------------------------------------------------------*/
    if (orientraw) {
        *colsP = tiffCols;
        *rowsP = tiffRows;
    } else
        tiffToImageDim(tiffCols, tiffRows, orientation, colsP, rowsP);

    if (verbose)
        pm_message("Generating %uw x %uh PNM image", *colsP, *rowsP);
}



static void
pnmOut_init(FILE *         const imageoutFileP,
            FILE *         const alphaFileP,
            unsigned int   const cols,
            unsigned int   const rows,
            unsigned short const orientation,
            xelval         const maxval,
            int            const format,
            gray           const alphaMaxval,
            bool           const flipIfNeeded,
            bool           const orientraw,
            bool           const verbose,
            bool *         const flipOkP,
            bool *         const noflipOkP,
            pnmOut *       const pnmOutP) {
/*----------------------------------------------------------------------------
   'cols' and 'rows' are the dimensions of the raster matrix which is
   oriented according to 'orientation' with respect to the image.

   If the user flips the data before giving it to the pnmOut object,
   pnmOut may see the inverse dimensions; if the pnmOut object flips the
   data, pnmOut get 'cols' x 'rows' data, but its output file may be
   'rows x cols'.

   Because we must set up the pnmOut object either to receive flipped or not
   flipped input, we have *flipOkP and *noflipOkP outputs that tell Caller
   whether he has to flip or not.  Note that Caller also influences which way
   we set up pnmOut, with his 'flipIfNeeded' argument.  In the unique case
   that the TIFF matrix is already oriented the way the output PNM file needs
   to be, flipping is idempotent, so both *flipOkP and *noflipOkP are true.
-----------------------------------------------------------------------------*/
    pnmOutP->imageoutFileP = imageoutFileP;
    pnmOutP->alphaFileP    = alphaFileP;
    pnmOutP->maxval        = maxval;
    pnmOutP->format        = format;
    pnmOutP->alphaMaxval   = alphaMaxval;

    setupFlipper(pnmOutP, orientation, flipIfNeeded, orientraw, verbose,
                 flipOkP, noflipOkP);

    computeOutputDimensions(cols, rows, orientation, orientraw,
                            &pnmOutP->outCols, &pnmOutP->outRows, verbose);

    if (pnmOutP->flipping) {
        pnmOutP->inCols = cols;         /* Caller won't flip */
        pnmOutP->inRows = rows;
    } else {
        pnmOutP->inCols = pnmOutP->outCols;  /* Caller will flip */
        pnmOutP->inRows = pnmOutP->outRows;
    }    
    if (pnmOutP->flipping) {
        if (pnmOutP->imagePipeP != NULL) 
            pnm_writepnminit(pnmOutP->imagePipeP,
                             pnmOutP->inCols, pnmOutP->inRows,
                             pnmOutP->maxval, pnmOutP->format, 0);
        if (pnmOutP->alphaPipeP != NULL) 
            pgm_writepgminit(pnmOutP->alphaPipeP,
                             pnmOutP->inCols, pnmOutP->inRows,
                             pnmOutP->alphaMaxval, 0);
    } else {
        if (imageoutFileP != NULL) 
            pnm_writepnminit(pnmOutP->imageoutFileP,
                             pnmOutP->outCols, pnmOutP->outRows,
                             pnmOutP->maxval, pnmOutP->format, 0);
        if (alphaFileP != NULL) 
            pgm_writepgminit(pnmOutP->alphaFileP,
                             pnmOutP->outCols, pnmOutP->outRows,
                             pnmOutP->alphaMaxval, 0);
    }
}



static void
pnmOut_term(pnmOut * const pnmOutP,
            bool     const verbose) {

    if (pnmOutP->flipping) {
        /* Closing the pipes also causes the Pamflip processes to terminate
           and they consequently flush their output to pnmOutP->imageoutFileP
           and pnmOutP->alphaFileP and close those file descriptors.

           We wait for the processes to exit before returning so that we
           know everything is flushed, so the invoker of Tifftopnm is free
           to use its output.
        */
        if (verbose)
            pm_message("Flushing data through Pamflip process, "
                       "waiting for Pamflip to terminate");

        if (pnmOutP->imagePipeP) {
            fclose(pnmOutP->imagePipeP);
            pm_waitpidSimple(pnmOutP->imageFlipPid);
        }
        if (pnmOutP->alphaPipeP) {
            fclose(pnmOutP->alphaPipeP);
            pm_waitpidSimple(pnmOutP->alphaFlipPid);
        }
    } else {
        if (pnmOutP->imageoutFileP)
            fflush(pnmOutP->imageoutFileP);
        if (pnmOutP->alphaFileP)
            fflush(pnmOutP->alphaFileP);
    }
}



static void
pnmOut_writeRow(pnmOut *     const pnmOutP,
                unsigned int const cols,
                const xel *  const imageRow,
                const gray * const alphaRow) {

    assert(cols == pnmOutP->inCols);

    if (pnmOutP->flipping) {
        if (pnmOutP->imagePipeP != NULL) 
            pnm_writepnmrow(pnmOutP->imagePipeP, (xel *)imageRow,
                            pnmOutP->inCols, pnmOutP->maxval,
                            pnmOutP->format, 0);
        if (pnmOutP->alphaPipeP != NULL) 
            pgm_writepgmrow(pnmOutP->alphaPipeP, alphaRow,
                            pnmOutP->inCols, pnmOutP->alphaMaxval, 0);
    } else {
        if (pnmOutP->imageoutFileP != NULL) 
            pnm_writepnmrow(pnmOutP->imageoutFileP, (xel *)imageRow,
                            pnmOutP->outCols, pnmOutP->maxval,
                            pnmOutP->format, 0);
        if (pnmOutP->alphaFileP != NULL) 
            pgm_writepgmrow(pnmOutP->alphaFileP, alphaRow,
                            pnmOutP->outCols, pnmOutP->alphaMaxval, 0);
    }
}



static void
convertRow(unsigned int   const samplebuf[], 
           xel *          const xelrow, 
           gray *         const alpharow,
           int            const cols, 
           xelval         const maxval, 
           unsigned short const photomet, 
           unsigned short const spp,
           xel            const colormap[]) {
/*----------------------------------------------------------------------------
   Assuming samplebuf[] is an array of raster values as returned by the Tiff
   library, convert it to a libnetpbm row in xelrow[] and alpharow[].
-----------------------------------------------------------------------------*/
    switch (photomet) {
    case PHOTOMETRIC_MINISBLACK: {
        int col;
        for (col = 0; col < cols; ++col) {
            PNM_ASSIGN1(xelrow[col], samplebuf[col]);
            alpharow[col] = 0;
        }
    }
    break;
    
    case PHOTOMETRIC_MINISWHITE: {
        int col;
        for (col = 0; col < cols; ++col) {
            PNM_ASSIGN1(xelrow[col], maxval - samplebuf[col]);
            alpharow[col] = 0;
        }
    }
    break;

    case PHOTOMETRIC_PALETTE: {
        int col;
        for ( col = 0; col < cols; ++col ) {
            /* We know the following array index is in bounds because
               we filled samplebuf with samples of 'bps' bits each and
               we verified that the largest number that fits in 'bps'
               bits is less than MAXCOLORS, the dimension of the array.
            */
            xelrow[col] = colormap[samplebuf[col]];
            alpharow[col] = 0;
        }
    }
    break;

    case PHOTOMETRIC_SEPARATED: {
        int col, sample;
        for (col = 0, sample = 0; col < cols; ++col, sample+=spp) {
            xelval r, g, b;
            pick_cmyk_pixel(samplebuf, sample, &r, &b, &g);
            
            PPM_ASSIGN(xelrow[col], r, g, b);
            alpharow[col] = 0;
        }
    }
    break;

    case PHOTOMETRIC_RGB: {
        int col, sample;
        for (col = 0, sample = 0; col < cols; ++col, sample+=spp) {
            PPM_ASSIGN(xelrow[col], samplebuf[sample+0],
                       samplebuf[sample+1], samplebuf[sample+2]);
            if (spp >= 4)
                alpharow[col] = samplebuf[sample+3];
            else
                alpharow[col] = 0;
        }
        break;
    }       
    default:
        pm_error("internal error:  unknown photometric in the picking "
                 "routine: %d", photomet);
    }
}



static void
scale32to16(unsigned int * const samplebuf,
            unsigned int   const cols,
            unsigned int   const spp) {
/*----------------------------------------------------------------------------
  Convert every sample in samplebuf[] to something that can be expressed
  in 16 bits, assuming it takes 32 bits now.
-----------------------------------------------------------------------------*/
    unsigned int i;
    for (i = 0; i < cols * spp; ++i)
        samplebuf[i] >>= 16; 
}



static void
convertMultiPlaneRow(TIFF *          const tif,
                     xel *           const xelrow,
                     gray *          const alpharow,
                     int             const cols,
                     xelval          const maxval,
                     int             const row,
                     unsigned short  const photomet,
                     unsigned short  const bps,
                     unsigned short  const spp,
                     unsigned short  const fillorder,
                     unsigned char * const scanbuf,
                     unsigned int *  const samplebuf) {

    /* The input is in separate planes, so we need to read one
       scanline for the reds, another for the greens, then another
       for the blues.
    */

    if (photomet != PHOTOMETRIC_RGB)
        pm_error("This is a multiple-plane file, but is not an RGB "
                 "file.  This program does not know how to handle that.");
    else {
        unsigned int col;

        /* First, clear the buffer so we can add red, green,
           and blue one at a time.  
        */
        for (col = 0; col < cols; ++col) 
            PPM_ASSIGN(xelrow[col], 0, 0, 0);

        /* Read the reds */
        readscanline(tif, scanbuf, row, 0, cols, bps, spp, fillorder, 
                     samplebuf);
        if (bps == 32)
            scale32to16(samplebuf, cols, spp);
        for (col = 0; col < cols; ++col) 
            PPM_PUTR(xelrow[col], samplebuf[col]);
                
        /* Next the greens */
        readscanline(tif, scanbuf, row, 1, cols, bps, spp, fillorder,
                     samplebuf);
        if (bps == 32)
            scale32to16(samplebuf, cols, spp);
        for (col = 0; col < cols; ++col) 
            PPM_PUTG( xelrow[col], samplebuf[col] );
            
        /* And finally the blues */
        readscanline(tif, scanbuf, row, 2, cols, bps, spp, fillorder,
                     samplebuf);
        if (bps == 32)
            scale32to16(samplebuf, cols, spp);
        for (col = 0; col < cols; ++col) 
            PPM_PUTB(xelrow[col], samplebuf[col]);

        /* Could there be an alpha plane?  (We assume no.  But if so,
           here is where to read it) 
        */
        for (col = 0; col < cols; ++col) 
            alpharow[col] = 0;
    }
}



static void
convertRasterByRows(pnmOut *       const pnmOutP,
                    unsigned int   const cols, 
                    unsigned int   const rows,
                    xelval         const maxval,
                    TIFF *         const tif,
                    unsigned short const photomet, 
                    unsigned short const planarconfig,
                    unsigned short const bps,
                    unsigned short const spp,
                    unsigned short const fillorder,
                    xel            const colormap[],
                    bool           const verbose) {
/*----------------------------------------------------------------------------
   With the TIFF header all processed (and relevant information from it in 
   our arguments), write out the TIFF raster to the Netpbm output files
   as described by *pnmOutP.

   Do this one row at a time, employing the TIFF library's
   TIFFReadScanline.
-----------------------------------------------------------------------------*/
    unsigned char * scanbuf;
        /* Buffer for a raster line in the format returned by TIFF library's
           TIFFReadScanline
        */
    unsigned int * samplebuf;
        /* Same info as 'scanbuf' above, but with each raster column (sample)
           represented as single array element, so it's easy to work with.
        */
    xel * xelrow;
        /* The ppm-format row of the image row we are presently converting */
    gray * alpharow;
        /* The pgm-format row representing the alpha values for the image 
           row we are presently converting.
        */

    unsigned int row;

    if (verbose)
        pm_message("Converting row by row ...");

    MALLOCARRAY(scanbuf, TIFFScanlineSize(tif));
    if (scanbuf == NULL)
        pm_error("can't allocate memory for scanline buffer");

    MALLOCARRAY(samplebuf, cols * spp);
    if (samplebuf == NULL)
        pm_error("can't allocate memory for row buffer");

    xelrow = pnm_allocrow(cols);
    alpharow = pgm_allocrow(cols);

    for (row = 0; row < rows; ++row) {
        /* Read one row of samples into samplebuf[] */

        if (planarconfig == PLANARCONFIG_CONTIG) {
            readscanline(tif, scanbuf, row, 0, cols, bps, spp, fillorder, 
                         samplebuf);
            if (bps == 32)
                scale32to16(samplebuf, cols, spp);
            convertRow(samplebuf, xelrow, alpharow, cols, maxval, 
                       photomet, spp, colormap);
        } else 
            convertMultiPlaneRow(tif, xelrow, alpharow, cols, maxval, row,
                                 photomet, bps, spp, fillorder,
                                 scanbuf, samplebuf);

        pnmOut_writeRow(pnmOutP, cols, xelrow, alpharow);
    }
    pgm_freerow(alpharow);
    pnm_freerow(xelrow);

    free(samplebuf);
    free(scanbuf);
}    



static void
warnBrokenTiffLibrary(TIFF * const tiffP) {

/* TIFF library bug:

   In every version of the TIFF library we've seen, TIFFRGBAImageGet()
   fails when the raster orientation (per the TIFF_ORIENTATION tag)
   requires a transposition, e.g. ORIENTATION_LEFTBOT.  It simply omits
   the transposition part, so e.g. it treats ORIENTATION_LEFTBOT as
   ORIENTATION_BOTLEFT.  And because we provide a raster buffer dimensioned
   for the properly transposed image, the result is somewhat of a mess.
   
   We have found no documentation of the TIFF library that suggests
   this behavior is as designed, so it's probably not a good idea to
   work around it; it might be fixed somewhere.

   The user can of course work around just by using -byrow and therefore
   not using TIFFRGBAImageGet().

   There is some evidence of an interface in the TIFF library that
   lets you request that TIFFRGBAImageGet() produce a raster in the
   same orientation as the one in the TIFF image.
   (tiff.req_orientation).  We could conceivably use that and then do
   a Pamflip to get the proper orientation, but that somewhat defeats
   the philosophy of using TIFFRGBAImageGet(), so I would like to wait
   until there's a good practical reason to do it.
*/

    unsigned short tiffOrientation;
    int present;
    present = TIFFGetField(tiffP, TIFFTAG_ORIENTATION, &tiffOrientation);
    if (present) {
        switch (tiffOrientation) {
        case ORIENTATION_LEFTTOP:
        case ORIENTATION_RIGHTTOP:
        case ORIENTATION_RIGHTBOT:
        case ORIENTATION_LEFTBOT:
            pm_message("WARNING: This TIFF image has an orientation that "
                       "most TIFF libraries convert incorrectly.  "
                       "Use -byrow to circumvent.");
            break;
        }
    }
}



static void 
convertTiffRaster(uint32 *        const raster, 
                  unsigned int    const cols,
                  unsigned int    const rows,
                  xelval          const maxval,
                  pnmOut *        const pnmOutP) {
/*----------------------------------------------------------------------------
   Convert the raster 'raster' from the format generated by the TIFF library
   to PPM (plus PGM alpha mask where applicable) and output it to
   the object *pnmOutP.  The raster is 'cols' wide by 'rows' high.
-----------------------------------------------------------------------------*/
    xel * xelrow;
        /* The ppm-format row of the image row we are
           presently converting 
        */
    gray * alpharow;
        /* The pgm-format row representing the alpha values
           for the image row we are presently converting.  
        */
    unsigned int row;

    xelrow = pnm_allocrow(cols);
    alpharow = pgm_allocrow(cols);

    for (row = 0; row < rows; ++row) {
        uint32 * rp;  
            /* Address of pixel in 'raster' we are presently converting */
        unsigned int col;

        /* Start at beginning of row: */
        rp = raster + (rows - row - 1) * cols;
    
        for (col = 0; col < cols; ++col) {
            uint32 const tiffPixel = *rp++;
                    
            PPM_ASSIGN(xelrow[col], 
                       TIFFGetR(tiffPixel) * maxval / 255, 
                       TIFFGetG(tiffPixel) * maxval / 255, 
                       TIFFGetB(tiffPixel) * maxval / 255);
            alpharow[col] = TIFFGetA(tiffPixel) * maxval / 255 ;
        }
        pnmOut_writeRow(pnmOutP, cols, xelrow, alpharow);
    }
    
    pgm_freerow(alpharow);
    pnm_freerow(xelrow);
}    



enum convertDisp {CONV_DONE,
                  CONV_OOM,
                  CONV_UNABLE,
                  CONV_FAILED, 
                  CONV_NOTATTEMPTED};

static void
convertRasterInMemory(pnmOut *           const pnmOutP,
                      xelval             const maxval,
                      TIFF *             const tif,
                      unsigned short     const photomet, 
                      unsigned short     const planarconfig,
                      unsigned short     const bps,
                      unsigned short     const spp,
                      unsigned short     const fillorder,
                      xel                const colormap[],
                      bool               const verbose,
                      enum convertDisp * const statusP) {
/*----------------------------------------------------------------------------
   With the TIFF header all processed (and relevant information from
   it in our arguments), write out the TIFF raster to the file images
   *imageoutFileP and *alphaFileP.

   Do this by reading the entire TIFF image into memory at once and formatting
   it with the TIFF library's TIFFRGBAImageGet().

   'cols' and 'rows' are the dimensions of the actual image, not of the
   TIFF raster matrix; ('tif' knows the TIFF raster matrix dimensions).

   Return *statusP == CONV_OOM iff we are unable to proceed because we cannot
   get memory to store the entire raster.  This means Caller may still be able
   to do the conversion using a row-by-row strategy.  Like typical Netpbm
   programs, we simply abort the program if we are unable to allocate
   memory for other things.
-----------------------------------------------------------------------------*/
    unsigned int cols, rows;  /* Dimensions of output image */

    if (verbose)
        pm_message("Converting in memory ...");

    warnBrokenTiffLibrary(tif);

    getTiffDimensions(tif, &cols, &rows);

    if (rows == 0 || cols == 0) 
        *statusP = CONV_DONE;
    else {
        char emsg[1024];
        int ok;
        ok = TIFFRGBAImageOK(tif, emsg);
        if (!ok) {
            pm_message("%s", emsg);
            *statusP = CONV_UNABLE;
        } else {
            uint32 * raster;

            /* Note that TIFFRGBAImageGet() converts any bits per sample
               to 8.  Maxval of the raster it returns is always 255.
            */
            if (cols > UINT_MAX/rows) {
                pm_message("%u rows of %u columns is too large to compute",
                           rows, cols);
                *statusP = CONV_OOM;
                return;
            }

            MALLOCARRAY(raster, cols * rows);
            if (raster == NULL) {
                pm_message("Unable to allocate space for a raster of %u "
                           "pixels.", cols * rows);
                *statusP = CONV_OOM;
            } else {
                int const stopOnErrorFalse = FALSE;
                TIFFRGBAImage img;
                int ok;
                
                ok = TIFFRGBAImageBegin(&img, tif, stopOnErrorFalse, emsg);
                if (!ok) {
                    pm_message("%s", emsg);
                    *statusP = CONV_FAILED;
                } else {
                    int ok;
                    ok = TIFFRGBAImageGet(&img, raster, cols, rows);
                    TIFFRGBAImageEnd(&img) ;
                    if (!ok) {
                        pm_message("%s", emsg);
                        *statusP = CONV_FAILED;
                    } else {
                        *statusP = CONV_DONE;
                        convertTiffRaster(raster, cols, rows, maxval, pnmOutP);
                    }
                } 
                free(raster);
            }
        }
    }
}



static void
convertRaster(pnmOut *           const pnmOutP,
              TIFF *             const tifP,
              struct tiffDirInfo const tiffDir,
              xelval             const maxval,
              unsigned short     const fillorder,
              const xel *        const colormap,
              bool               const byrow,
              bool               const flipOk,
              bool               const noflipOk,
              bool               const verbose) {

    enum convertDisp status;

    if (byrow || !flipOk)
        status = CONV_NOTATTEMPTED;
    else {
        convertRasterInMemory(
            pnmOutP, maxval,
            tifP, tiffDir.photomet, tiffDir.planarconfig, 
            tiffDir.bps, tiffDir.spp, fillorder,
            colormap, verbose, &status);
    }
    if (status == CONV_DONE) {
        if (tiffDir.bps > 8)
            pm_message("actual resolution has been reduced to 24 bits "
                       "per pixel in the conversion.  You can get the "
                       "full %u bits that are in the TIFF with the "
                       "-byrow option.", tiffDir.bps);
    } else {
        if (status != CONV_NOTATTEMPTED) {
            pm_message("In-memory conversion failed; "
                       "using more primitive row-by-row conversion.");

            if (!noflipOk)
                pm_error("TIFF raster is in nonstandard orientation, "
                         "and we already committed to in-memory "
                         "conversion.  To avoid this failure, "
                         "use -byrow .");
        }            
        convertRasterByRows(
            pnmOutP, tiffDir.width, tiffDir.height, maxval,
            tifP, tiffDir.photomet, tiffDir.planarconfig,
            tiffDir.bps, tiffDir.spp, fillorder, colormap, verbose);
    }
}



static void
convertImage(TIFF *             const tifP,
             FILE *             const alphaFileP,
             FILE *             const imageoutFileP,
             struct CmdlineInfo const cmdline) {

    struct tiffDirInfo tiffDir;
    int format;
    xelval maxval;
    xel colormap[MAXCOLORS];
    unsigned short fillorder;
    bool flipOk, noflipOk;
    pnmOut pnmOut;

    readDirectory(tifP, cmdline.headerdump, &tiffDir);

    computeFillorder(tiffDir.fillorder, &fillorder, cmdline.respectfillorder);

    analyzeImageType(tifP, tiffDir.bps, tiffDir.spp, tiffDir.photomet, 
                     &maxval, &format, colormap, cmdline.headerdump, cmdline);

    pnmOut_init(imageoutFileP, alphaFileP, tiffDir.width, tiffDir.height,
                tiffDir.orientation, maxval, format, maxval,
                cmdline.byrow, cmdline.orientraw,
                cmdline.verbose,
                &flipOk, &noflipOk,
                &pnmOut);

    convertRaster(&pnmOut, tifP, tiffDir, maxval,
                  fillorder, colormap, cmdline.byrow, flipOk, noflipOk,
                  cmdline.verbose);

    pnmOut_term(&pnmOut, cmdline.verbose);
}



static void
convertIt(TIFF *             const tifP,
          FILE *             const alphaFile, 
          FILE *             const imageoutFile,
          struct CmdlineInfo const cmdline) {

    unsigned int imageSeq;
    bool eof;

    imageSeq = 0;
    eof = FALSE;

    while (!eof) {
        bool success;

        if (cmdline.verbose)
            pm_message("Converting Image %u", imageSeq);
        convertImage(tifP, alphaFile, imageoutFile, cmdline);
        success = TIFFReadDirectory(tifP);
        eof = !success;
        ++imageSeq;
    }
}



int
main(int argc, const char * argv[]) {

    struct CmdlineInfo cmdline;
    TIFF * tiffP;
    FILE * alphaFile;
    FILE * imageoutFile;

    pm_proginit(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    tiffP = newTiffImageObject(cmdline.inputFilename);

    if (cmdline.alphaStdout)
        alphaFile = stdout;
    else if (cmdline.alphaFilename == NULL) 
        alphaFile = NULL;
    else
        alphaFile = pm_openw(cmdline.alphaFilename);

    if (cmdline.alphaStdout) 
        imageoutFile = NULL;
    else
        imageoutFile = stdout;

    convertIt(tiffP, alphaFile, imageoutFile, cmdline);

    if (imageoutFile != NULL) 
        pm_close( imageoutFile );
    if (alphaFile != NULL)
        pm_close( alphaFile );

    TIFFClose(tiffP);

    pm_strfree(cmdline.inputFilename);

    /* If the program failed, it previously aborted with nonzero completion
       code, via various function calls.
    */
    return 0;
}
