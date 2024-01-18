/* winicontoppm.c - read a MS Windows .ico file and write portable pixmap(s)
**
** Copyright (C) 2000,2003 by Lee Benfield - lee@benf.org
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
**
** Changes:
**
** 03/2003 - Added 24+32 bpp capability.
*/

#define _BSD_SOURCE 1      /* Make sure strdup() is in string.h */
#define _XOPEN_SOURCE 500  /* Make sure strdup() is in string.h */

#include <math.h>
#include <string.h>
#include <assert.h>

#include "pm_c_util.h"
#include "ppm.h"
#include "shhopt.h"
#include "nstring.h"
#include "mallocvar.h"
#include "winico.h"

#define MAJVERSION 0
#define MINVERSION 4

static int fileOffset = 0;    /* not actually used, but useful for debug */
static const char     er_read[] = "%s: read error";
static const char *   infname;

struct cmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    const char * inputFilespec;
    const char * outputFilespec;
    unsigned int allicons;
    unsigned int bestqual;
    unsigned int writeands;
    unsigned int multippm;
    unsigned int verbose;
};




static void
parseCommandLine (int argc, const char ** argv,
                  struct cmdlineInfo *cmdlineP ) {
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

    MALLOCARRAY(option_def, 100);

    option_def_index = 0;   /* incremented by OPTENT3 */
    OPTENT3(0, "allicons",     OPT_FLAG,   NULL,
            &cmdlineP->allicons,       0 );
    OPTENT3(0, "bestqual",     OPT_FLAG,   NULL,
            &cmdlineP->bestqual,       0 );
    OPTENT3(0, "writeands",    OPT_FLAG,   NULL,
            &cmdlineP->writeands,      0 );
    OPTENT3(0, "multippm",     OPT_FLAG,   NULL,
            &cmdlineP->multippm,       0 );
    OPTENT3(0, "verbose",      OPT_FLAG,   NULL,
            &cmdlineP->verbose,        0 );

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = FALSE;  /* We have no parms that are negative numbers */

    pm_optParseOptions3(&argc, (char **)argv, opt, sizeof(opt), 0);
        /* Uses and sets argc, argv, and some of *cmdlineP and others. */

    if (argc-1 < 1)
        cmdlineP->inputFilespec = "-";
    else
        cmdlineP->inputFilespec = argv[1];

    if (argc-1 < 2) {
        cmdlineP->outputFilespec = "-";

        if (cmdlineP->writeands || cmdlineP->allicons)
            pm_error("If you specify the -writeands or -allicons option, "
                     "you must also specify an output file name argument.");
    } else
        cmdlineP->outputFilespec = argv[2];

    if (argc-1 > 2)
        pm_error("Too many arguments (%d).  Input filespec and "
                 "output filespec are the only possible arguments.",
                 argc-1);
}




static int
GetByte(FILE * const ifP) {

    int v;

    v = getc(ifP);
    if (v == EOF)
        pm_error(er_read, infname);

    return v;
}



static short
GetShort(FILE * const ifP) {

    short v;

    pm_readlittleshort(ifP, &v);

    return v;
}



static long
GetLong(FILE * const ifP) {

    long v;

    pm_readlittlelong(ifP, &v);

    return v;
}



/*
 * These have no purpose but to wrapper the Byte, Short & Long
 * functions.
 */
static u1
readU1(FILE * const ifP) {

    ++fileOffset;

    return GetByte(ifP);
}



static u1 *
readU1String (FILE *       const ifP,
              unsigned int const length) {

    u1 * string;
    size_t rc;

    MALLOCARRAY(string, length + 1);
    if (string == NULL)
        pm_error("out of memory");

    rc = fread(string, sizeof(u1), length, ifP);
    if (rc < length) {
        if (feof(ifP))
            pm_error("File read failed.  Premature end of file");
        else
            pm_error("File read failed.  Errno=%d (%s)",
                     errno, strerror(errno));
    }

    string[length] = 0;
    fileOffset += length * sizeof(u1);

    return string;
}



static u2
readU2 (FILE * const ifP) {

    fileOffset +=2;

    return GetShort(ifP);
}



static u4
readU4 (FILE * const ifP) {

    fileOffset += 4;

    return GetLong(ifP);
}



static IC_Entry
readICEntry(FILE * const ifP) {

    IC_Entry entryP;
    u1 widthFld;   /* 0 means 256 */
    u1 heightFld;  /* 0 means 256 */
    u1 colorCtFld; /* 0 means 256 */

    MALLOCVAR(entryP);

    if (entryP == NULL)
        pm_error("Unable to allocate memory for IC entry");

    widthFld              = readU1(ifP);
    heightFld             = readU1(ifP);
    entryP->color_count   = readU1(ifP);
    entryP->reserved      = readU1(ifP);  /* never referenced (should be 0) */
    entryP->planes        = readU2(ifP);  /* never referenced */
    entryP->bitcount      = readU2(ifP);  /* must be 0, 1, 4, or 8 */
    entryP->size_in_bytes = readU4(ifP);  /* never referenced */
    entryP->file_offset   = readU4(ifP);  /* never referenced */
    entryP->colors        = NULL;
    entryP->ih            = NULL;
    entryP->xorBitmap     = NULL;
    entryP->andBitmap     = NULL;

    entryP->width       = widthFld   == 0 ? 256 : widthFld;
    entryP->height      = heightFld  == 0 ? 256 : heightFld;
    entryP->color_count = colorCtFld == 0 ? 256 : colorCtFld;

    if (entryP->width != entryP->height)
        pm_message("warning: icon is not square: %u x %u",
                   entryP->width, entryP->height);

    return entryP;
}



static IC_InfoHeader
readInfoHeader (FILE *   const ifP,
                IC_Entry const entryP) {

    IC_InfoHeader ihP;

    MALLOCVAR(ihP);

    if (ihP == NULL)
        pm_error("Unable to allocate memory for info header");

    ihP->size             = readU4(ifP);  /* never referenced */
    ihP->width            = readU4(ifP);  /* must equal entryP->width */
    ihP->height           = readU4(ifP);  /* must be 2 * entryP->height */
    ihP->planes           = readU2(ifP);  /* never referenced */
    ihP->bitcount         = readU2(ifP);
    ihP->compression      = readU4(ifP);
    ihP->imagesize        = readU4(ifP);  /* never referenced */
    ihP->x_pixels_per_m   = readU4(ifP);  /* never referenced */
    ihP->y_pixels_per_m   = readU4(ifP);  /* never referenced */
    ihP->colors_used      = readU4(ifP);
        /* checked below, otherwise never referenced */
    ihP->colors_important = readU4(ifP);
        /* checked below, otherwise never referenced */

    if ((entryP->width != ihP->width)
        || (entryP->height != ihP->height / 2)) {
        pm_error("mismatch in header and image dimensions "
                 "(%u x %u vs. %u x %u)",
                 entryP->width, entryP->height,
                 ihP->width, ihP->height / 2);
    } else if (ihP->height % 2 != 0)
        pm_error("invalid image height value %u (cannot be an odd number)",
                  ihP->height);

    if (ihP->bitcount > 8)
        pm_error("abnormal bit per pixel value %u", ihP->bitcount);

    if ((entryP->bitcount != 0) && (entryP->bitcount != ihP->bitcount)) {
        pm_error("mismatch in header and image bpp value"
                 "(%u vs. %u)",
                 entryP->bitcount, ihP->bitcount);
    }

    if (ihP->colors_used > entryP->color_count)
        pm_error("'colors used' value %u exceeds total colors %u",
                 ihP->colors_used, entryP->color_count);

    if (ihP->colors_important > entryP->color_count)
        pm_error("'important colors' value %u exceeds total colors %u",
                 ihP->colors_important, entryP->color_count);

    if (ihP->compression) {
        pm_error("Can't handle compressed icons");
    }
    return ihP;
}



static IC_Color
readICColor(FILE * const ifP)  {

    IC_Color colorP;

    MALLOCVAR(colorP);

    if (colorP == NULL)
        pm_error("Unable to allocate memory for color");

    /* I don't know why this isn't the same as the spec, it just isn't.
       The colors honestly seem to be stored BGR.  Bizarre.

       I've checked this in the BMP code for bmptoppm and the gimp.  Guess the
       spec I have is just plain wrong.
    */

    colorP->blue     = readU1(ifP);
    colorP->green    = readU1(ifP);
    colorP->red      = readU1(ifP);
    colorP->reserved = readU1(ifP);

    return colorP;
}



static u1 *
read1Bitmap (FILE *       const ifP,
             unsigned int const width,
             unsigned int const height) {

    unsigned int row;
    unsigned int xByteCt;
    u1 * bitmap;
    unsigned int wt;

    MALLOCARRAY(bitmap, width * height);
    if (bitmap == NULL)
        pm_error("out of memory");

    /* Depending on if the image is stored as 1bpp, 4bpp or 8bpp, the
       encoding mechanism is different.

       8bpp => 1 byte/palette index.
       4bpp => High Nibble, Low Nibble
       1bpp => 1 palette value per bit, high bit 1st.
    */

    wt = width >> 3;

    if ((wt & 0x3) != 0) {
        wt = (wt & ~0x3) + 4;
    }
    xByteCt = wt;

    for (row = 0; row < height; ++row) {
        u1 * const imgRow = readU1String(ifP, xByteCt);

        unsigned int col;
        unsigned int rowByte;
        unsigned int xOrVal;

        for (col = 0, rowByte = 0, xOrVal = 0x80; col < width; ++col) {
            *(bitmap+((height - row - 1) * width) + col) =
                (imgRow[rowByte] & xOrVal) / xOrVal;
            if (xOrVal == 0x01) {
                xOrVal = 0x80;
                ++rowByte;
            } else
                xOrVal >>= 1;
        }
        free(imgRow);
    }
    return bitmap;
}



static u1 *
read4Bitmap (FILE *       const ifP,
             unsigned int const width,
             unsigned int const height) {

    unsigned int row;
    u1 * bitmap;

    unsigned int wt;
    unsigned int xByteCt;

    MALLOCARRAY(bitmap, width * height);
    if (bitmap == NULL)
        pm_error("out of memory");

    wt = width >> 1;

    if (wt & 0x3) {
        wt = (wt & ~0x3) + 4;
    }
    xByteCt = wt;

    for (row = 0; row < height; ++row) {
        u1 * const imgRow = readU1String(ifP, xByteCt);

        unsigned int rowByte;
        bool bottom;
        unsigned int col;
        for (col = 0, rowByte = 0, bottom = true; col < width; ++col) {
            /* 2 nibbles, 2 values */
            if (bottom) {
                *(bitmap + ((height - row - 1) * width) + col) =
                    (imgRow[rowByte] & 0xF0) >> 4;
            } else {
                *(bitmap + ((height - row -1) * width) + col) =
                    (imgRow[rowByte] & 0xF);
                ++rowByte;
            }
            bottom = !bottom;
        }
        free(imgRow);
    }
    return bitmap;
}



static u1 *
read8Bitmap (FILE *       const ifP,
             unsigned int const width,
             unsigned int const height) {

    unsigned int row;
    unsigned int xByteCt;
    unsigned int wt;
    u1 * bitmap;

    MALLOCARRAY(bitmap, width * height);
    if (bitmap == NULL)
        pm_error("out of memory");

    wt = width;
    if (wt & 0x3) {
        wt = (wt & ~0x3) + 4;
    }
    xByteCt = wt;

    for (row = 0; row < height; ++row) {
        u1 * imgRow = readU1String(ifP, xByteCt);

        unsigned int rowByte;
        unsigned int col;
        for (col = 0, rowByte = 0; col < width; ++col)
            *(bitmap + ((height - row - 1) * width) + col) = imgRow[rowByte++];

        free(imgRow);
    }
    return bitmap;
}



static u1 *
readXBitmap (FILE *       const ifP,
             unsigned int const width,
             unsigned int const height,
             unsigned int const bpp) {
/*----------------------------------------------------------------------------
  Read a true color bitmap. (24/32 bits)

  The output routine deplanarizes it for us, we keep it flat here.
-----------------------------------------------------------------------------*/
    unsigned int const byteCt = bpp >> 3;
    unsigned int const xByteCt = width * byteCt;

    u1 * bitmap;
        /* remember - bmp (dib) stored upside down, so reverse */

    MALLOCARRAY(bitmap, byteCt * width * height);
    if (bitmap == NULL)
        pm_error("out of memory allocating bitmap array");

    {
        unsigned int i;
        u1 * bitcurptr;

        for (i = 0, bitcurptr = &bitmap[byteCt * width * (height-1)];
             i < height;
             ++i, bitcurptr -= xByteCt) {

            u1 * const row = readU1String(ifP, xByteCt);
            memcpy(bitcurptr, row, xByteCt);
            free(row);
        }
    }
    return bitmap;
}



static MS_Ico
readIconFile(FILE * const ifP,
             bool   const verbose) {

    unsigned int i;

    MS_Ico MSIconData;

    MALLOCVAR(MSIconData);

    MSIconData->reserved = readU2(ifP);  /* should be 0 */
    MSIconData->type     = readU2(ifP);  /* should be 1 (ICO) or 2 (CUR) */
    MSIconData->count    = readU2(ifP);  /* # icons in file */

    if (MSIconData->reserved != 0)
       pm_message("Signature 'reserved' field is %u (should be 0)",
                  MSIconData->reserved);

    if (MSIconData->type != 1 && MSIconData->type != 2)
        pm_error("Type %u file.  Can handle only type 1 or 2.",
                 MSIconData->type);

    if (MSIconData->count == 0)
        pm_error("Invalid image count: 0");
    else if (verbose)
        pm_message("File contains %u images", MSIconData->count);

    MALLOCARRAY(MSIconData->entries, MSIconData->count);
    if (MSIconData->entries == NULL)
        pm_error("out of memory");

    /* Read in each of the entries */
    for (i = 0; i < MSIconData->count; ++i)
        MSIconData->entries[i] = readICEntry(ifP);

    /* Read in the infoheader, color map (if any) and the actual bit/pix maps
       for the icons.
    */
    if (verbose)
        pm_message("#\tColors\tBPP\tWidth\tHeight\n");

    for (i = 0; i < MSIconData->count; ++i) {
        IC_Entry const entryP = MSIconData->entries[i];

        unsigned int bpp;  /* bits per pixel */

        entryP->ih = readInfoHeader(ifP, MSIconData->entries[i]);

        bpp  = entryP->bitcount ? entryP->bitcount : entryP->ih->bitcount;

        /* Read the palette, if appropriate */
        switch (bpp) {
        case 24:
        case 32:
            /* 24/32 bpp icon has no palette */
            break;
        default: {
            unsigned int j;

            MALLOCARRAY(entryP->colors, entryP->color_count);
            if (!entryP->colors)
                pm_error("Could get memory for %u colors",
                         entryP->color_count);

            for (j = 0; j < entryP->color_count; ++j)
                entryP->colors[j] = readICColor(ifP);
        }
        }
        if (verbose) {
            char colsText[10];
            sprintf (colsText, "%d", entryP->color_count);
            pm_message("%d\t%s\t%d\t%d\t%d\n", i,
                       entryP->color_count ? colsText : "TRUE",
                       bpp, entryP->width, entryP->height);
        }
        /* Pixels are stored bottom-up, left-to-right. Pixel lines are
         * padded with zeros to end on a 32bit (4byte) boundary. Every
         * line will have the same number of bytes. Color indices are
         * zero based, meaning a pixel color of 0 represents the first
         * color table entry, a pixel color of 255 (if there are that
         * many) represents the 256th entry.
         *
         * 24+32 bit (16 is an abomination, which I'll avoid, and expect
         * no-one to mind) are stored 1byte/plane with a spare (alpha?)
         * byte for 32 bit.
         */
        {
            /*
             * Read XOR Bitmap
             */
            switch (bpp) {
            case 1:
                entryP->xorBitmap =
                    read1Bitmap(ifP, entryP->width, entryP->height);
                break;
            case 4:
                entryP->xorBitmap =
                    read4Bitmap(ifP, entryP->width, entryP->height);
                break;
            case 8:
                entryP->xorBitmap =
                    read8Bitmap(ifP, entryP->width, entryP->height);
                break;
            case 24:
            case 32:
                entryP->xorBitmap =
                    readXBitmap(ifP, entryP->width, entryP->height,bpp);
                break;
            default:
                pm_error("Uncatered bit depth %u", bpp);
            }
            /*
             * Read AND Bitmap
             */
            entryP->andBitmap =
                read1Bitmap(ifP, entryP->width, entryP->height);
        }

    }
    return MSIconData;
}



static char *
trimmedOutputName(const char inputName[]) {
    /*
     * Just trim off the final ".ppm", if there is one, else return as is.
     * oh, for =~ ... :)
     */
    char * const outFile = strdup(inputName);
    if (streq(outFile + (strlen(outFile) - 4), ".ppm")) {
        *(outFile + (strlen(outFile) - 4)) = 0;
    }
    return outFile;

}



static int
getBestQualityIcon(MS_Ico MSIconData)
{
    unsigned int i;
    unsigned int best;
    unsigned int bestSize;
    unsigned int bestBpp;

    for (i = 0, bestSize = 0, bestBpp = 0; i < MSIconData->count; ++i) {
        IC_Entry const entryP = MSIconData->entries[i];
        unsigned int const size = entryP->width * entryP->height;
        unsigned int const bpp  =
            entryP->bitcount ? entryP->bitcount : entryP->ih->bitcount;

        if (size > bestSize) {
            best = i;
            bestSize = size;
        } else if (size == bestSize && bpp > bestBpp) {
            best = i;
            bestBpp = bpp;
        }
    }
    return best;
}



static void
writeXors(FILE *   const multiOutF,
          char *   const outputFileBase,
          IC_Entry const entryP,
          int      const entryNum,
          bool     const multiple,
          bool     const xor) {
/*----------------------------------------------------------------------------
   Write an "xor" image (i.e. the main image) out.

   'multiple' means this is one of multiple images that are being written.
   'entryNum' is the sequence number within the winicon file of the image
   we are writing.

   'xor' means to include "xor" in the output file name.

   if 'multiOutF' is non-null, it is the stream descriptor of an open
   stream to which we are to write the image.  If it is null,
   we are to open a file using outputFileBase[] and 'entryNum' and 'xor'
   to derive its name, and close it afterward.
-----------------------------------------------------------------------------*/
    FILE * ofP;
    pixel ** pixArray;
    unsigned int row;
    const char * outputFileName;

    if (multiOutF) {
        ofP = multiOutF;
        outputFileName = strdup("");
    } else {
        if (outputFileBase) {
            if (multiple) {
                pm_asprintf(&outputFileName, "%s%s_%d.ppm",
                            outputFileBase,(xor ? "_xor" : ""), entryNum);
            } else {
                pm_asprintf(&outputFileName, "%s%s.ppm",
                            outputFileBase,(xor ? "_xor" : ""));
            }
        } else
            outputFileName = strdup("-");

        ofP = pm_openw(outputFileName);
    }
    /*
       Allocate an array to save the bmp data into.
       note that entry->height will be 1/2 entry->ih->height,
       as the latter adds "and" and "xor" height.
    */
    pixArray = ppm_allocarray(entryP->width, entryP->height);
    for (row = 0; row < entryP->height; ++row) {
        switch (entryP->bitcount) {
        case 24:
        case 32: {
            unsigned int const pixelSize = entryP->bitcount >> 3;
            u1 * const xorRow =
                entryP->xorBitmap + row * entryP->width * pixelSize;
            unsigned int col;
            for (col = 0; col < entryP->width * pixelSize; col += pixelSize)
                PPM_ASSIGN(pixArray[row][col/pixelSize],
                           xorRow[col+2], xorRow[col+1], xorRow[col]);
        } break;
        default: {
            u1 * const xorRow = entryP->xorBitmap + row * entryP->width;
            unsigned int col;
            for (col = 0; col < entryP->width; ++col) {
                unsigned int const colorIndex = xorRow[col];
                if (colorIndex >= entryP->color_count) {
                    pm_error("Invalid color index %u (max is %u)",
                              colorIndex, entryP->color_count - 1);
                } else {
                    IC_Color const colorP = entryP->colors[colorIndex];
                    PPM_ASSIGN(pixArray[row][col],
                               colorP->red, colorP->green, colorP->blue);
                }
            }
        } break;
        }
    }

    ppm_writeppm(ofP, pixArray, entryP->width, entryP->height,
                 255 /* maxval */, false /* text */);
    ppm_freearray(pixArray, entryP->height);

    pm_strfree(outputFileName);

    if (!multiOutF)
        pm_close(ofP);
}



static void
writeAnds(FILE *       const multiOutF,
          char         const outputFileBase[],
          IC_Entry     const entryP,
          unsigned int const entryNum,
          bool         const multiple) {
/*----------------------------------------------------------------------------
   Write the "and" image (i.e. the alpha mask) of the image *entryP out.

   'multiple' means this is one of multiple images that are being written.
   'entryNum' is the sequence number within the winicon file of the image
   we are writing.

   if 'multiOutF' is non-null, it is the stream descriptor of an open
   stream to which we are to write the image.  If it is null,
   we are to open a file using outputFileBase[] and 'entryNum' and 'xor'
   to derive its name, and close it afterward.
-----------------------------------------------------------------------------*/
    FILE * ofP;
    bit ** bitArray;
    unsigned int row;

    if (multiOutF)
        ofP = multiOutF;
    else {
        const char * outputFileName;

        assert(outputFileBase);

        if (multiple)
            pm_asprintf(&outputFileName, "%s_and_%u.pbm",
                        outputFileBase, entryNum);
        else
            pm_asprintf(&outputFileName, "%s_and.pbm", outputFileBase);
        ofP = pm_openw(outputFileName);
        pm_strfree(outputFileName);
    }
    bitArray = pbm_allocarray(entryP->width, entryP->height);
    for (row = 0; row < entryP->height; ++row) {
        u1 * const andRow = entryP->andBitmap + row * entryP->width;
        unsigned int col;
        for (col = 0; col < entryP->width; ++col) {
            /* Note: black is transparent in a Netpbm alpha mask */
            bitArray[row][col] = andRow[col] ? PBM_BLACK: PBM_WHITE;
        }
    }

    pbm_writepbm(ofP, bitArray, entryP->width, entryP->height, 0);

    pbm_freearray(bitArray, entryP->height);
    if (!multiOutF)
        pm_close(ofP);
}



static void
openMultiXor(char    const outputFileBase[],
             bool    const writeands,
             FILE ** const multiOutFP) {

    const char * outputFileName;

    if (outputFileBase) {
        pm_asprintf(&outputFileName, "%s%s.ppm",
                    outputFileBase, (writeands ? "_xor" : ""));
    } else
        outputFileName = strdup("-");

    *multiOutFP = pm_openw(outputFileName);

    pm_strfree(outputFileName);
}



static void
openMultiAnd(char    const outputFileBase[],
             FILE ** const multiAndOutFP) {

    const char * outputFileName;

    assert(outputFileBase);

    pm_asprintf(&outputFileName, "%s_and.pbm", outputFileBase);

    *multiAndOutFP = pm_openw(outputFileName);

    pm_strfree(outputFileName);
}



static void
freeIconentry(IC_Entry const entryP) {

    if (entryP->colors && entryP->color_count) {
        unsigned int i;
        for (i = 0; i <entryP->color_count; ++i)
            free(entryP->colors[i]);
        free(entryP->colors);
    }
    if (entryP->andBitmap) free(entryP->andBitmap);
    if (entryP->xorBitmap) free(entryP->xorBitmap);
    if (entryP->ih) free(entryP->ih);
    free(entryP);
}



static void
freeIcondata(MS_Ico const MSIconDataP) {

    unsigned int i;
    for (i = 0; i < MSIconDataP->count; ++i)
        freeIconentry(MSIconDataP->entries[i]);

    free(MSIconDataP);
}



int
main(int argc, const char *argv[]) {

    struct cmdlineInfo cmdline;
    FILE * ifP;
    unsigned int startEntry, endEntry;
    MS_Ico MSIconDataP;
    char * outputFileBase;
    FILE * multiOutF;
    FILE * multiAndOutF;

    pm_proginit(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    if (cmdline.bestqual && cmdline.allicons)
        pm_message("-bestqual doesn't make sense with -allicons.  "
                   "Ignoring -bestqual.");

    if (streq(cmdline.outputFilespec, "-"))
        outputFileBase = NULL;
    else
        outputFileBase = trimmedOutputName(cmdline.outputFilespec);

    ifP = pm_openr(cmdline.inputFilespec);

    infname = cmdline.inputFilespec;

    MSIconDataP = readIconFile(ifP, cmdline.verbose);
    /*
     * Now we've read the icon file in (Hopefully! :)
     * Go through each of the entries, and write out files of the
     * form
     *
     * fname_0_xor.ppm
     * fname_0_and.ppm
     *
     * (or to stdout, depending on args parsing above).
     */
    /*
     * If allicons is set, we want everything, if not, just go through once.
     */
    if (cmdline.bestqual) {
        startEntry = getBestQualityIcon(MSIconDataP);
        endEntry = startEntry+1;
    } else {
        startEntry = 0;
        if (cmdline.allicons)
            endEntry = MSIconDataP->count;
        else
            endEntry = 1;
    }

    if (cmdline.multippm)
        openMultiXor(outputFileBase, cmdline.writeands, &multiOutF);
    else
        multiOutF = NULL;

    if (cmdline.writeands && cmdline.multippm)
        openMultiAnd(outputFileBase, &multiAndOutF);
    else
        multiAndOutF = NULL;

    {
        unsigned int entryNum;

        for (entryNum = startEntry; entryNum < endEntry; ++entryNum) {
            IC_Entry const entryP = MSIconDataP->entries[entryNum];

            writeXors(multiOutF, outputFileBase, entryP, entryNum,
                      cmdline.allicons, cmdline.writeands);
            if (cmdline.writeands)
                writeAnds(multiAndOutF, outputFileBase,
                          entryP, entryNum, cmdline.allicons);
        }
    }
    if (multiOutF)
        pm_close(multiOutF);
    if (multiAndOutF)
        pm_close(multiAndOutF);

    /* free up the image data here. */
    freeIcondata(MSIconDataP);

    return 0;
}
