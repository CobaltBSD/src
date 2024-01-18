/*
 * ppmtobmp.c - Converts from a PPM file to a Microsoft Windows or OS/2
 * .BMP file.
 *
 * Copyright (C) 1992 by David W. Sanderson.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  This software is provided "as is"
 * without express or implied warranty.
 *
 */

#define _BSD_SOURCE 1    /* Make sure strdup() is in string.h */
#define _XOPEN_SOURCE 500  /* Make sure strdup() is in string.h */

#include <assert.h>
#include <string.h>

#include "pm_c_util.h"
#include "nstring.h"
#include "mallocvar.h"
#include "shhopt.h"
#include "bmp.h"
#include "bitio.h"
#include "ppm.h"

#define MAXCOLORS 256

enum colortype {TRUECOLOR, PALETTE};

struct rgb {
    unsigned char red;
    unsigned char grn;
    unsigned char blu;
};

typedef struct {
/*----------------------------------------------------------------------------
   A color map for a BMP file.
-----------------------------------------------------------------------------*/
    unsigned int count;
        /* Number of colors in the map.  The first 'count' elements of these
           arrays are defined; all others are not.

           At most MAXCOLORS.
        */
    colorhash_table cht;

    /* Indices in the following array are the same as in 'cht', above. */
    struct rgb bmpMap[MAXCOLORS];
} colorMap;



static void
freeColorMap(const colorMap * const colorMapP) {

    if (colorMapP->cht)
        ppm_freecolorhash(colorMapP->cht);
}



struct CmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    const char * inputFilename;
    int class;  /* C_WIN or C_OS2 */
    unsigned int bppSpec;
    unsigned int bpp;
    const char * mapfile;
};


static void
parseCommandLine(int argc, const char ** argv,
                 struct CmdlineInfo * const cmdlineP) {
/*----------------------------------------------------------------------------
   Note that many of the strings that this function returns in the
   *cmdline_p structure are actually in the supplied argv array.  And
   sometimes, one of these strings is actually just a suffix of an entry
   in argv!
-----------------------------------------------------------------------------*/
    optEntry * option_def;
        /* Instructions to OptParseOptions3 on how to parse our options.
         */
    optStruct3 opt;

    unsigned int windowsSpec, os2Spec, mapfileSpec;

    unsigned int option_def_index;
    
    MALLOCARRAY(option_def, 100);

    option_def_index = 0;   /* incremented by OPTENTRY */
    OPTENT3('w', "windows",   OPT_FLAG, NULL, &windowsSpec,            0);
    OPTENT3('o', "os2",       OPT_FLAG, NULL, &os2Spec,                0);
    OPTENT3(0,   "bpp",       OPT_UINT, &cmdlineP->bpp, 
            &cmdlineP->bppSpec,      0);
    OPTENT3(0,   "mapfile",   OPT_STRING, &cmdlineP->mapfile, 
            &mapfileSpec,             0);

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = FALSE;  /* We have no parms that are negative numbers */

    pm_optParseOptions3(&argc, (char **)argv, opt, sizeof(opt), 0);

    if (windowsSpec && os2Spec) 
        pm_error("Can't specify both -windows and -os2 options.");
    else if (windowsSpec) 
        cmdlineP->class = C_WIN;
    else if (os2Spec)
        cmdlineP->class = C_OS2;
    else 
        cmdlineP->class = C_WIN;


    if (cmdlineP->bppSpec) {
        if (cmdlineP->bpp != 1 && cmdlineP->bpp != 4 && 
            cmdlineP->bpp != 8 && cmdlineP->bpp != 24)
        pm_error("Invalid -bpp value specified: %u.  The only values valid "
                 "in the BMP format are 1, 4, 8, and 24 bits per pixel",
                 cmdlineP->bpp);
    }

    if (!mapfileSpec)
        cmdlineP->mapfile = NULL;

    if (argc - 1 == 0)
        cmdlineP->inputFilename = pm_strdup("-");  /* he wants stdin */
    else if (argc - 1 == 1)
        cmdlineP->inputFilename = pm_strdup(argv[1]);
    else 
        pm_error("Too many arguments.  The only argument accepted "
                 "is the input file specificaton");

    free(option_def);
}



static void
freeCommandLine(struct CmdlineInfo const cmdline) {

    pm_strfree(cmdline.inputFilename);
}



static void
PutByte(FILE * const fp, unsigned char const v) {
    if (putc(v, fp) == EOF) 
        pm_error("Write of a byte to a file failed.");

    /* Note:  a Solaris/SPARC user reported on 2003.09.29 that the above
       putc() returned EOF when a former version of this code declared
       v as "char" instead of "unsigned char".  This was apparently due
       to a bug in his C library that caused 255 to look like -1 at some
       critical internal point.
    */
}



static void
PutShort(FILE * const fp, short const v) {
    if (pm_writelittleshort(fp, v) == -1) 
        pm_error("Write of a halfword to a file failed.");
}



static void
PutLong(FILE * const fp, long const v) {
    if (pm_writelittlelong(fp, v) == -1)
        pm_error("Write of a word to a file failed.");
}



/*
 * BMP writing
 */

static unsigned int
BMPwritefileheader(FILE *        const fp, 
                   unsigned int  const cbSize,
                   unsigned int  const offBits) {
/*----------------------------------------------------------------------------
  Return the number of bytes written.
-----------------------------------------------------------------------------*/
    PutByte(fp, 'B');
    PutByte(fp, 'M');

    /* cbSize */
    PutLong(fp, cbSize);
    
    /* xHotSpot */
    PutShort(fp, 0);
    
    /* yHotSpot */
    PutShort(fp, 0);
    
    /* offBits */
    PutLong(fp, offBits);
    
    return 14;
}



static int
BMPwriteinfoheader(FILE *        const fp, 
                   int           const class, 
                   unsigned long const bitcount, 
                   unsigned long const x, 
                   unsigned long const y) {
/*----------------------------------------------------------------------------
  Return the number of bytes written.
----------------------------------------------------------------------------*/
    unsigned int cbFix;

    switch (class) {
    case C_WIN: {
        cbFix = 40;
        PutLong(fp, cbFix);

        PutLong(fp, x);         /* cx */
        PutLong(fp, y);         /* cy */
        PutShort(fp, 1);        /* cPlanes */
        PutShort(fp, bitcount); /* cBitCount */

        /*
         * We've written 16 bytes so far, need to write 24 more
         * for the required total of 40.
         */

        PutLong(fp, 0);   /* Compression */
        PutLong(fp, 0);   /* ImageSize */
        PutLong(fp, 0);   /* XpixelsPerMeter */
        PutLong(fp, 0);   /* YpixelsPerMeter */
        PutLong(fp, 0);   /* ColorsUsed */
        PutLong(fp, 0);   /* ColorsImportant */
    }
    break;
    case C_OS2: {
        cbFix = 12;
        PutLong(fp, cbFix);

        PutShort(fp, x);        /* cx */
        PutShort(fp, y);        /* cy */
        PutShort(fp, 1);        /* cPlanes */
        PutShort(fp, bitcount); /* cBitCount */
    }
    break;
    default:
        pm_error(er_internal, "BMPwriteinfoheader");
    }

    return cbFix;
}



static int
BMPwriteRgb(FILE * const fp, 
            int    const class, 
            pixval const R, 
            pixval const G, 
            pixval const B) {
/*----------------------------------------------------------------------------
  Return the number of bytes written.
-----------------------------------------------------------------------------*/
    switch (class) {
    case C_WIN:
        PutByte(fp, B);
        PutByte(fp, G);
        PutByte(fp, R);
        PutByte(fp, 0);
        return 4;
    case C_OS2:
        PutByte(fp, B);
        PutByte(fp, G);
        PutByte(fp, R);
        return 3;
    default:
        pm_error(er_internal, "BMPwriteRgb");
        return -1;  /* avoid compiler warning. */
    }
}



static int
BMPwriteColormap(FILE *           const ifP, 
                 int              const class, 
                 int              const bpp,
                 const colorMap * const colorMapP) {
/*----------------------------------------------------------------------------
  Return the number of bytes written.
-----------------------------------------------------------------------------*/
    unsigned int const ncolors = (1 << bpp);

    unsigned int nbyte;
    unsigned int i;

    assert(ncolors <= MAXCOLORS);
    assert(ncolors <= ARRAY_SIZE(colorMapP->bmpMap));

    nbyte = 0;
    for (i = 0; i < colorMapP->count; ++i) {
        const struct rgb * const mapEntryP = &colorMapP->bmpMap[i];
        nbyte += BMPwriteRgb(ifP, class,
                             mapEntryP->red, mapEntryP->grn, mapEntryP->blu);
    }
    for (; i < ncolors; ++i)
        nbyte += BMPwriteRgb(ifP, class, 0, 0, 0);

    return nbyte;
}



static void
lookupColor(colorhash_table const cht,
            pixel           const color,
            unsigned int *  const colorIndexP) {

    int rc;

    rc = ppm_lookupcolor(cht, &color);

    if (rc < 0)
        pm_error("Color (%u,%u,%u) is not in the provided palette",
                 PPM_GETR(color), PPM_GETG(color), PPM_GETB(color));
    else
        *colorIndexP = rc;
}



static void
bmpWriteRow_palette(FILE *          const fp, 
                    const pixel *   const row, 
                    unsigned int    const cols,
                    unsigned short  const bpp, 
                    colorhash_table const cht,
                    unsigned int *  const nBytesP) {
/*----------------------------------------------------------------------------
   Write a row to the raster in paletted format.

   Return the number of bytes written as *nBytesP.
-----------------------------------------------------------------------------*/
    BITSTREAM b;
    
    b = pm_bitinit(fp, "w");
    if (b == NULL)
        pm_error("Failed to initialize output file for output");
    else {
        int rc;
        unsigned int nbyte;
        unsigned int col;
        
        nbyte = 0;      /* initial value */
        
        for (col = 0; col < cols; ++col) {
            unsigned int colorIndex;
            int rc;

            lookupColor(cht, row[col], &colorIndex);

            rc = pm_bitwrite(b, bpp, colorIndex);
            if (rc == -1)
                pm_error("Failed in writing a pixel "
                         "to the raster in the output file");
            else
                nbyte += rc;
        }

        rc = pm_bitfini(b);

        nbyte += rc;
                
        /* Make sure we write a multiple of 4 bytes.  */
        while (nbyte % 4 != 0) {
            PutByte(fp, 0);
            ++nbyte;
        }
        *nBytesP = nbyte;
    }
}



static void
bmpWriteRow_truecolor(FILE *         const fp, 
                      const pixel *  const row, 
                      unsigned long  const cols,
                      pixval         const maxval,
                      unsigned int * const nBytesP) {
/*----------------------------------------------------------------------------
  Write a row of a truecolor BMP image to the file 'fp'.  The row is 
  'row', which is 'cols' columns long.


  Return the number of bytes written as *nBytesP.
-----------------------------------------------------------------------------*/
    /* This works only for 24 bits per pixel.  To implement this for the
       general case (which is only hypothetical -- this program doesn't
       write any truecolor images except 24 bit and apparently no one
       else does either), you would move this function into 
       BMPwriterow_palette, which writes arbitrary bit strings.  But
       that would be a lot slower and less robust.
    */

    int nbyte;  /* Number of bytes we have written to file so far */
    int col;  
        
    nbyte = 0;  /* initial value */
    for (col = 0; col < cols; ++col) {
        /* We scale to the BMP maxval, which is always 255. */
        PutByte(fp, PPM_GETB(row[col]) * 255 / maxval);
        PutByte(fp, PPM_GETG(row[col]) * 255 / maxval);
        PutByte(fp, PPM_GETR(row[col]) * 255 / maxval);
        nbyte += 3;
    }

    /*
     * Make sure we write a multiple of 4 bytes.
     */
    while (nbyte % 4) {
        PutByte(fp, 0);
        ++nbyte;
    }
    
    *nBytesP = nbyte;
}



static int
BMPwritebits(FILE *          const fp, 
             unsigned long   const cols, 
             unsigned long   const rows,
             enum colortype  const colortype,
             unsigned short  const cBitCount, 
             const pixel **  const pixels, 
             pixval          const maxval,
             colorhash_table const cht) {
/*----------------------------------------------------------------------------
  Return the number of bytes written.
-----------------------------------------------------------------------------*/
    unsigned int nbyte;
    int row;

    if (cBitCount > 24)
        pm_error("cannot handle cBitCount: %hu", cBitCount);

    nbyte = 0;  /* initial value */

    /* The picture is stored bottom line first, top line last */

    for (row = rows - 1; row >= 0; --row) {
        unsigned int nBytesThisRow;

        if (colortype == PALETTE)
            bmpWriteRow_palette(fp, pixels[row], cols, 
                                cBitCount, cht, &nBytesThisRow);
        else 
            bmpWriteRow_truecolor(fp, pixels[row], cols, maxval,
                                  &nBytesThisRow);

        if (nBytesThisRow % 4 != 0)
            pm_error("row had bad number of bytes: %u", nBytesThisRow);
        nbyte += nBytesThisRow;
    }

    return nbyte;
}



static void
bmpEncode(FILE *           const ifP, 
          int              const class, 
          enum colortype   const colortype,
          unsigned int     const bpp,
          int              const x, 
          int              const y, 
          const pixel **   const pixels, 
          pixval           const maxval,
          const colorMap * const colorMapP) {
/*----------------------------------------------------------------------------
  Write a BMP file of the given class.
-----------------------------------------------------------------------------*/
    unsigned int const cbSize  = BMPlenfile(class, bpp, 0, x, y);
    unsigned int const offbits = BMPoffbits(class, bpp, 0);

    unsigned long nbyte;

    if (colortype == PALETTE)
        pm_message("Writing %u bits per pixel with a color palette", bpp);
    else
        pm_message("Writing %u bits per pixel truecolor (no palette)", bpp);

    nbyte = 0;  /* initial value */
    nbyte += BMPwritefileheader(ifP, cbSize, offbits);
    nbyte += BMPwriteinfoheader(ifP, class, bpp, x, y);
    if (colortype == PALETTE)
        nbyte += BMPwriteColormap(ifP, class, bpp, colorMapP);

    if (nbyte != offbits)
        pm_error(er_internal, "BmpEncode 1");

    nbyte += BMPwritebits(ifP, x, y, colortype, bpp, pixels, maxval,
                          colorMapP->cht);
    if (nbyte != cbSize)
        pm_error(er_internal, "BmpEncode 2");
}



static void
makeBilevelColorMap(colorMap * const colorMapP) {

    colorMapP->count  = 2;
    colorMapP->cht    = NULL;
    colorMapP->bmpMap[0].red = 0;
    colorMapP->bmpMap[0].grn = 0;
    colorMapP->bmpMap[0].blu = 0;
    colorMapP->bmpMap[1].red = 255;
    colorMapP->bmpMap[1].grn = 255;
    colorMapP->bmpMap[1].blu = 255;
}



static void
bmpEncodePbm(FILE *           const ifP, 
             int              const class, 
             int              const cols, 
             int              const rows, 
             unsigned char ** const bitrow) {
/*----------------------------------------------------------------------------
  Write a bi-level BMP file of the given class.
-----------------------------------------------------------------------------*/
    /* Note:
       Only PBM input uses this routine.  Color images represented by 1 bpp via
       color palette use the general bmpEncode().
    */
    unsigned int const cbSize       = BMPlenfile(class, 1, 0, cols, rows);
    unsigned int const offbits      = BMPoffbits(class, 1, 0);
    unsigned int const adjustedCols = (cols + 31) / 32 * 32;
    unsigned int const packedBytes  = adjustedCols / 8;

    unsigned long nbyte;
    colorMap bilevelColorMap;
    unsigned int row;
    
    /* colortype == PALETTE */
    pm_message("Writing 1 bit per pixel with a black-white palette");

    nbyte = 0;  /* initial value */
    nbyte += BMPwritefileheader(ifP, cbSize, offbits);
    nbyte += BMPwriteinfoheader(ifP, class, 1, cols, rows);

    makeBilevelColorMap(&bilevelColorMap);

    nbyte += BMPwriteColormap(ifP, class, 1, &bilevelColorMap);

    if (nbyte != offbits)
        pm_error(er_internal, "bmpEncodePbm 1");

    for (row = 0; row < rows; ++row){
        size_t bytesWritten;

        bytesWritten = fwrite(bitrow[row], 1, packedBytes, ifP);
        if (bytesWritten != packedBytes){
            if (feof(ifP))
                pm_error("End of file writing row %u of BMP raster.", row);
            else 
                pm_error("Error writing BMP raster.  Errno=%d (%s)",
                         errno, strerror(errno));
        }  else
            nbyte += bytesWritten;
    }

    if (nbyte != cbSize)
        pm_error(er_internal, "bmpEncodePbm 2");
}



static void
makeHashFromBmpMap(const struct rgb * const bmpMap,
                   unsigned int       const nColors,
                   colorhash_table *  const chtP) {

    colorhist_vector chv;
    unsigned int i;

    MALLOCARRAY_NOFAIL(chv, nColors);

    for (i = 0; i < nColors; ++i) {
        const struct rgb * const mapEntryP = &bmpMap[i];

        PPM_ASSIGN(chv[i].color,
                   mapEntryP->red, mapEntryP->grn, mapEntryP->blu);
    }

    *chtP = ppm_colorhisttocolorhash(chv, nColors);

    ppm_freecolorhist(chv);
}



static unsigned int
minBmpBitsForColorCount(unsigned int const colorCount) {

    unsigned int const minbits = pm_maxvaltobits(colorCount - 1);

    /* Only 1, 4, 8, and 24 are defined in the BMP spec we
       implement and other bpp's have in fact been seen to confuse
       viewers.  There is an extended BMP format that has 16 bpp
       too, but this program doesn't know how to generate that
       (see Bmptopnm.c, though).  
    */
    if (minbits == 1)
        return 1;
    else if (minbits <= 4)
        return 4;
    else if (minbits <= 8)
        return 8;
    else
        return 24;
}



static void
getMapFile(const char *   const mapFileName,
           unsigned int * const minimumBppP,
           colorMap *     const colorMapP) {
/*----------------------------------------------------------------------------
   Get the color map (palette) for the BMP from file 'mapFileName'.

   Return the color map as *colormapP.

   Return as *minimumBppP the minimum number of bits per pixel it will
   take to represent all the colors in the map in the BMP format.
-----------------------------------------------------------------------------*/

    FILE * mapFileP;
    int cols, rows;
    pixval maxval;
    pixel ** pixels;
    unsigned int row;
    unsigned int count;

    mapFileP = pm_openr(mapFileName);

    pixels = ppm_readppm(mapFileP, &cols, &rows, &maxval);

    if (cols * rows > MAXCOLORS)
        pm_error("The colormap file you gave (-mapfile) has too "
                 "many entries for a BMP.  A BMP can have at most "
                 "%u colors; the file has %u pixels, each of which "
                 "represents an entry in the color map.",
                 MAXCOLORS, cols * rows);

    count = 0; /* initial value */
    
    for (row = 0; row < rows; ++row) {
        unsigned int col;
        for (col = 0; col < cols; ++col) {
            pixel        const color     = pixels[row][col];
            struct rgb * const mapEntryP = &colorMapP->bmpMap[count++];

            assert(count <= ARRAY_SIZE(colorMapP->bmpMap));

            mapEntryP->red = PPM_GETR(color) * 255 / maxval;
            mapEntryP->grn = PPM_GETG(color) * 255 / maxval;
            mapEntryP->blu = PPM_GETB(color) * 255 / maxval;
        }
    }
    ppm_freearray(pixels, rows);

    colorMapP->count = count;

    makeHashFromBmpMap(colorMapP->bmpMap, colorMapP->count, &colorMapP->cht);

    *minimumBppP = minBmpBitsForColorCount(count);

    pm_close(mapFileP);
}



static void
analyzeColors(const pixel **    const pixels, 
              int               const cols, 
              int               const rows, 
              pixval            const maxval, 
              unsigned int *    const minimumBppP,
              colorMap *        const colorMapP) {
/*----------------------------------------------------------------------------
  Look at the colors in the image 'pixels' and compute values to use in
  representing those colors in a BMP image.  

  First of all, count the distinct colors.  Return as *minimumBppP
  the minimum number of bits per pixel it will take to represent all
  the colors in BMP format.

  If there are few enough colors to represent with a palette, also
  return the number of colors as *colors_p and a suitable palette
  (colormap) and a hash table in which to look up indexes into that
  palette as *colorMapP.  Use only the first *colors_p entries of the
  map.

  If there are too many colors for a palette, return colorMapP->cht
  == NULL.

  Issue informational messages.
-----------------------------------------------------------------------------*/
    /* Figure out the colormap. */
    colorhist_vector chv;
    int colorCount;

    pm_message("analyzing colors...");
    chv = ppm_computecolorhist((pixel**)pixels, cols, rows, MAXCOLORS, 
                               &colorCount);
    colorMapP->count = colorCount;
    if (chv == NULL) {
        pm_message("More than %u colors found", MAXCOLORS);
        *minimumBppP = 24;
        colorMapP->cht = NULL;
    } else {
        unsigned int i;

        pm_message("%u colors found", colorMapP->count);

        *minimumBppP = minBmpBitsForColorCount(colorMapP->count);

        /*
         * Now scale the maxval to 255 as required by BMP format.
         */
        for (i = 0; i < colorMapP->count; ++i) {
            struct rgb * const mapEntryP = &colorMapP->bmpMap[i];
            mapEntryP->red = (pixval) PPM_GETR(chv[i].color) * 255 / maxval;
            mapEntryP->grn = (pixval) PPM_GETG(chv[i].color) * 255 / maxval;
            mapEntryP->blu = (pixval) PPM_GETB(chv[i].color) * 255 / maxval;
        }
    
        /* And make a hash table for fast lookup. */
        colorMapP->cht = ppm_colorhisttocolorhash(chv, colorMapP->count);
        ppm_freecolorhist(chv);
    }
}



static void
chooseColortypeBpp(bool             const userRequestsBpp,
                   unsigned int     const requestedBpp,
                   unsigned int     const minimumBpp,
                   enum colortype * const colortypeP, 
                   unsigned int *   const bitsPerPixelP) {
/*----------------------------------------------------------------------------
   Determine whether the BMP raster should contain RGB values or palette
   indices and how many bits is should have for each pixel.

   'userRequestsBpp' says the user has requested a particular number of
   bits per pixel.  'requestedBpp' is his request, and we assume it's a
   valid value for a BMP.

   'colors' is how many colors are in the image.

   'minimumBpp' is the minimum number of bits it takes to represent all
   the colors in the image.  We assume it is valid for a BMP.

   We return our choices as *colortypeP and *bitsPerPixelP.
-----------------------------------------------------------------------------*/
    if (!userRequestsBpp) {
        /* User has no preference as to bits per pixel.  Choose the
           smallest number possible for this image.
        */
        *bitsPerPixelP = minimumBpp;
    } else {
        if (requestedBpp < minimumBpp)
            pm_error("There are too many colors in the image to "
                     "represent in the "
                     "number of bits per pixel you requested: %d.  "
                     "You may use Pnmquant to reduce the number of "
                     "colors in the image.",
                     requestedBpp);
        else
            *bitsPerPixelP = requestedBpp;
    }

    assert(*bitsPerPixelP == 1 || 
           *bitsPerPixelP == 4 || 
           *bitsPerPixelP == 8 || 
           *bitsPerPixelP == 24);

    if (*bitsPerPixelP > 8) 
        *colortypeP = TRUECOLOR;
    else {
        *colortypeP = PALETTE;
    }
}



static void
doPbm(FILE *       const ifP,
      unsigned int const cols,
      unsigned int const rows,
      int          const format,
      int          const class,
      FILE *       const ofP) {
    
    /* We read the raster directly from the input with
        pbm_readpbmrow_packed().  The raster format is almost
        identical, except that BMP specifies rows to be zero-filled to
        32 bit borders and that in BMP the bottom row comes first in
        order.
    */
    int const colChars = pbm_packed_bytes(cols);
    int const adjustedCols = (cols+31) /32 * 32;
    int const packedBytes  =  adjustedCols /8;

    unsigned char ** bitrow;    
    unsigned int row;

    bitrow = pbm_allocarray_packed(adjustedCols, rows);

    for (row = 0; row < rows; ++row) {
        unsigned char * const thisRow = bitrow[rows - row - 1];

        /* Clear end of each row */
        thisRow[packedBytes-1] = 0x00;
        thisRow[packedBytes-2] = 0x00;
        thisRow[packedBytes-3] = 0x00;
        thisRow[packedBytes-4] = 0x00;
        
        pbm_readpbmrow_packed(ifP, thisRow, cols, format);

        {
            unsigned int i;
            for (i = 0; i < colChars; ++i) 
                thisRow[i] = ~thisRow[i]; /* flip all pixels */
        }
        /* This may seem unnecessary, because the color palette 
           (RGB[] in bmpEncodePbm) can be inverted for the same effect.
           However we take this precaution, for there is indication that
           some BMP viewers may get confused with that.
        */

        /* Clean off remainder of fractional last character */
        pbm_cleanrowend_packed(thisRow, cols);
    }

    bmpEncodePbm(ofP, class, cols, rows, bitrow);
}            



static void
doPgmPpm(FILE *       const ifP,
         unsigned int const cols,
         unsigned int const rows,
         pixval       const maxval,
         int          const ppmFormat,
         int          const class,
         bool         const userRequestsBpp,
         unsigned int const requestedBpp,
         const char * const mapFileName,
         FILE *       const ofP) {

    /* PGM and PPM.  We read the input image into a PPM array, scan it
       to analyze the colors, and convert it to a BMP raster.  Logic
       works for PBM.
    */
    unsigned int minimumBpp;
    unsigned int bitsPerPixel;
    enum colortype colortype;
    unsigned int row;
    
    pixel ** pixels;
    colorMap colorMap;
    
    pixels = ppm_allocarray(cols, rows);
    
    for (row = 0; row < rows; ++row)
        ppm_readppmrow(ifP, pixels[row], cols, maxval, ppmFormat);
    
    if (mapFileName)
        getMapFile(mapFileName, &minimumBpp, &colorMap);
    else
        analyzeColors((const pixel**)pixels, cols, rows, maxval, 
                      &minimumBpp, &colorMap);
    
    chooseColortypeBpp(userRequestsBpp, requestedBpp, minimumBpp,
                       &colortype, &bitsPerPixel);
    
    bmpEncode(ofP, class, colortype, bitsPerPixel,
              cols, rows, (const pixel**)pixels, maxval, &colorMap);
    
    freeColorMap(&colorMap);

    ppm_freearray(pixels, rows);
}



int
main(int           argc,
     const char ** argv) {

    struct CmdlineInfo cmdline;
    FILE * ifP;
    int rows;
    int cols;
    pixval maxval;
    int ppmFormat;

    pm_proginit(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    ifP = pm_openr(cmdline.inputFilename);
    
    ppm_readppminit(ifP, &cols, &rows, &maxval, &ppmFormat);
    
    if (PPM_FORMAT_TYPE(ppmFormat) == PBM_TYPE)
        doPbm(ifP, cols, rows, ppmFormat, cmdline.class, stdout);
    else
        doPgmPpm(ifP, cols, rows, maxval, ppmFormat,
                 cmdline.class, cmdline.bppSpec, cmdline.bpp, cmdline.mapfile,
                 stdout);

    freeCommandLine(cmdline);

    pm_close(ifP);
    pm_close(stdout);

    return 0;
}
