/*
** read a PNM image and produce a Portable Network Graphics file
**
** derived from pnmtorast.c (c) 1990,1991 by Jef Poskanzer and some
** parts derived from ppmtogif.c by Marcel Wijkstra <wijkstra@fwi.uva.nl>
**
** Copyright (C) 1995-1998 by Alexander Lehmann <alex@hal.rhein-main.de>
**                        and Willem van Schaik <willem@schaik.com>
** Copyright (C) 1999,2001 by Greg Roelofs <newt@pobox.com>
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
*/

/* This Netpbm version of Pnmtopng was derived from the independently
   distributed program of the same name, Version 2.37.6 (21 July 2001).
*/

/* A performance note: This program reads one row at a time because
   the whole image won't fit in memory always.  When you realize that
   in a Netpbm xel array a one bit pixel can take 96 bits of memory,
   it's easy to see that an ordinary fax could deplete your virtual
   memory and even if it didn't, it might deplete your real memory and
   iterating through the array would cause thrashing.  This program
   iterates through the image multiple times.  

   So instead, we read the image into memory one row at a time, into a
   single row buffer.  We use Netpbm's pm_openr_seekable() facility to
   access the file.  That facility copies the file into a temporary
   file if it isn't seekable, so we always end up with a file that we
   can rewind and reread multiple times.

   This shouldn't cause I/O delays because the entire image ought to fit
   in the system's I/O cache (remember that the file is a lot smaller than
   the xel array you'd get by doing a pnm_readpnm() of it).

   However, it does introduce some delay because of all the system calls 
   required to read the file.  A future enhancement might read the entire
   file into an xel array in some cases, and read one row at a time in 
   others, depending on the needs of the particular use.

   We do still read the entire alpha mask (if there is one) into a
   'gray' array, rather than access it one row at a time.  

   Before May 2001, we did in fact read the whole image into an xel array,
   and we got complaints.  Before April 2000, it wasn't as big a problem
   because xels were only 24 bits.  Now they're 96.
*/
   
#ifndef PNMTOPNG_WARNING_LEVEL
#  define PNMTOPNG_WARNING_LEVEL 0   /* use 0 for backward compatibility, */
#endif                               /*  2 for warnings (1 == error) */

#include <assert.h>
#include <string.h> /* strcat() */
#include <limits.h>
#include <png.h>
/* Because of a design error in png.h, you must not #include <setjmp.h> before
   <png.h>.  If you do, png.h won't compile.
*/
#include <setjmp.h> 
#include <zlib.h>

#include <pbm/util/pm_c_util.h>
#include <pbm/pnm.h>
#include "pngx.h"
#include "pngtxt.h"
#include <pbm/util/shhopt.h>
#include <pbm/util/mallocvar.h>
#include <pbm/util/nstring.h>
#include <pbm/version.h>

struct zlibCompression {
    /* These are parameters that describe a form of zlib compression.
       Values have the same meaning as the similarly named arguments to
       zlib's deflateInit2().  See zlib.h.
    */
    unsigned int levelSpec;
    unsigned int level;
    unsigned int memLevelSpec;
    unsigned int mem_level;
    unsigned int strategySpec;
    unsigned int strategy;
    unsigned int windowBitsSpec;
    unsigned int window_bits;
    unsigned int methodSpec;
    unsigned int method;
    unsigned int bufferSizeSpec;
    unsigned int buffer_size;
};

typedef struct cahitem {
    xel color;
    gray alpha;
    int value;
    struct cahitem * next;
} cahitem;

typedef cahitem ** coloralphahash_table;

struct cmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    const char *  inputFileName;  /* '-' if stdin */
    const char *  alpha;
    unsigned int  verbose;
    unsigned int  downscale;
    unsigned int  interlace;
    const char *  transparent;  /* NULL if none */
    const char *  background;   /* NULL if none */
    unsigned int  gammaSpec;
    float         gamma;        /* Meaningless if !gammaSpec */
    unsigned int  hist;
    unsigned int  rgbSpec;
    struct pngx_chroma rgb;          /* Meaningless if !rgbSpec */
    unsigned int  sizeSpec;
    struct pngx_phys   size;         /* Meaningless if !sizeSpec */
    unsigned int srgbintentSpec;
    pngx_srgbIntent srgbintent;
    const char *  text;         /* NULL if none */
    const char *  ztxt;         /* NULL if none */
    unsigned int  modtimeSpec;
    time_t        modtime;      /* Meaningless if !modtimeSpec */
    const char *  palette;      /* NULL if none */
    bool          filterSetSpec;
    int           filterSet;
    unsigned int  force;
    unsigned int  libversion;
    struct zlibCompression zlibCompression;
};



typedef struct _jmpbuf_wrapper {
  jmp_buf jmpbuf;
} jmpbuf_wrapper;

#ifndef TRUE
#  define TRUE 1
#endif
#ifndef FALSE
#  define FALSE 0
#endif
#ifndef NONE
#  define NONE 0
#endif
#define MAXCOLORS 256
#define MAXPALETTEENTRIES 256

/* PALETTEMAXVAL is the maxval used in a PNG palette */
#define PALETTEMAXVAL 255

#define PALETTEOPAQUE 255
#define PALETTETRANSPARENT 0

static bool verbose;

static jmpbuf_wrapper pnmtopng_jmpbuf_struct;
static int errorlevel;



static void
parseSizeOpt(const char *       const sizeOpt,
             struct pngx_phys * const sizeP) {

    int count;
    
    count = sscanf(sizeOpt, "%d %d %d", &sizeP->x, &sizeP->y, &sizeP->unit);

    if (count != 3)
        pm_error("Invalid syntax for the -size option value '%s'.  "
                 "Should be 3 integers: x, y, and unit code", sizeOpt);
}



static void
parseRgbOpt(const char *         const rgbOpt,
            struct pngx_chroma * const rgbP) {

    int count;
    
    count = sscanf(rgbOpt, "%f %f %f %f %f %f %f %f",
                   &rgbP->wx, &rgbP->wy,
                   &rgbP->rx, &rgbP->ry,
                   &rgbP->gx, &rgbP->gy,
                   &rgbP->bx, &rgbP->by);

    if (count != 8)
        pm_error("Invalid syntax for the -rgb option value '%s'.  "
                 "Should be 8 floating point numbers: "
                 "x and y for each of white, red, green, and blue",
                 rgbOpt);
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
parseModtimeOpt(const char * const modtimeOpt,
                time_t *     const modtimeP) {

    struct tm brokenTime;
    int year;
    int month;
    int count;

    count = sscanf(modtimeOpt, "%d-%d-%d %d:%d:%d",
                   &year,
                   &month,
                   &brokenTime.tm_mday,
                   &brokenTime.tm_hour,
                   &brokenTime.tm_min,
                   &brokenTime.tm_sec);

    if (count != 6)
        pm_error("Invalid value for -modtime '%s'.   It should have "
                 "the form [yy]yy-mm-dd hh:mm:ss.", modtimeOpt);
    
    if (year < 0)
        pm_error("Year is negative in -modtime value '%s'", modtimeOpt);
    if (year > 9999)
        pm_error("Year is more than 4 digits in -modtime value '%s'",
                 modtimeOpt);
    if (month < 0)
        pm_error("Month is negative in -modtime value '%s'", modtimeOpt);
    if (month > 12)
        pm_error("Month is >12 in -modtime value '%s'", modtimeOpt);
    if (brokenTime.tm_mday < 0)
        pm_error("Day of month is negative in -modtime value '%s'",
                 modtimeOpt);
    if (brokenTime.tm_mday > 31)
        pm_error("Day of month is >31 in -modtime value '%s'", modtimeOpt);
    if (brokenTime.tm_hour < 0)
        pm_error("Hour is negative in -modtime value '%s'", modtimeOpt);
    if (brokenTime.tm_hour > 23)
        pm_error("Hour is >23 in -modtime value '%s'", modtimeOpt);
    if (brokenTime.tm_min < 0)
        pm_error("Minute is negative in -modtime value '%s'", modtimeOpt);
    if (brokenTime.tm_min > 59)
        pm_error("Minute is >59 in -modtime value '%s'", modtimeOpt);
    if (brokenTime.tm_sec < 0)
        pm_error("Second is negative in -modtime value '%s'", modtimeOpt);
    if (brokenTime.tm_sec > 59)
        pm_error("Second is >59 in -modtime value '%s'", modtimeOpt);

    brokenTime.tm_mon = month - 1;
    if (year >= 1900)
        brokenTime.tm_year = year - 1900;
    else
        brokenTime.tm_year = year;

    /* Note that mktime() considers brokeTime to be in local time.
       This is what we want, since we got it from a user.  User should
       set his local time zone to UTC if he wants absolute time.
    */
    *modtimeP = mktime(&brokenTime);
}



static void
parseCommandLine(int argc, const char ** argv,
                 struct cmdlineInfo * const cmdlineP) {
/*----------------------------------------------------------------------------
   parse program command line described in Unix standard form by argc
   and argv.  Return the information in the options as *cmdlineP.  

   If command line is internally inconsistent (invalid options, etc.),
   issue error message to stderr and abort program.

   Note that the strings we return are stored in the storage that
   was passed to us as the argv array.  We also trash *argv.
-----------------------------------------------------------------------------*/
    optEntry *option_def;
        /* Instructions to pm_optParseOptions3 on how to parse our options.
         */
    optStruct3 opt;

    unsigned int option_def_index;

    unsigned int alphaSpec, transparentSpec, backgroundSpec;
    unsigned int textSpec, ztxtSpec, paletteSpec;
    unsigned int filterSpec;

    unsigned int nofilter, sub, up, avg, paeth, filter;
    unsigned int chroma, phys, time;
    const char * size;
    const char * rgb;
    const char * modtime;
    const char * compMethod;
    const char * compStrategy;
    const char * srgbintent;

    MALLOCARRAY_NOFAIL(option_def, 100);

    option_def_index = 0;   /* incremented by OPTENT3 */
    OPTENT3(0, "alpha",            OPT_STRING,    &cmdlineP->alpha,
            &alphaSpec,            0);
    OPTENT3(0, "transparent",      OPT_STRING,    &cmdlineP->transparent,
            &transparentSpec,      0);
    OPTENT3(0, "background",       OPT_STRING,    &cmdlineP->background,
            &backgroundSpec,       0);
    OPTENT3(0, "rgb",              OPT_STRING,    &rgb,
            &cmdlineP->rgbSpec,    0);
    OPTENT3(0, "size",             OPT_STRING,    &size,
            &cmdlineP->sizeSpec,   0);
    OPTENT3(0,  "srgbintent",      OPT_STRING,    &srgbintent,
            &cmdlineP->srgbintentSpec, 0);
    OPTENT3(0, "text",             OPT_STRING,    &cmdlineP->text,
            &textSpec,             0);
    OPTENT3(0, "ztxt",             OPT_STRING,    &cmdlineP->ztxt,
            &ztxtSpec,             0);
    OPTENT3(0, "modtime",          OPT_STRING,    &modtime,
            &cmdlineP->modtimeSpec,0);
    OPTENT3(0, "palette",          OPT_STRING,    &cmdlineP->palette,
            &paletteSpec,          0);
    OPTENT3(0, "compression",      OPT_UINT,
            &cmdlineP->zlibCompression.level,
            &cmdlineP->zlibCompression.levelSpec,            0);
    OPTENT3(0, "comp_mem_level",   OPT_UINT,
            &cmdlineP->zlibCompression.mem_level,
            &cmdlineP->zlibCompression.memLevelSpec,         0);
    OPTENT3(0, "comp_strategy",    OPT_STRING,    &compStrategy,
            &cmdlineP->zlibCompression.strategySpec,         0);
    OPTENT3(0, "comp_window_bits", OPT_UINT,
            &cmdlineP->zlibCompression.window_bits,
            &cmdlineP->zlibCompression.windowBitsSpec,       0);
    OPTENT3(0, "comp_method",      OPT_STRING,    &compMethod,
            &cmdlineP->zlibCompression.methodSpec,           0);
    OPTENT3(0, "comp_buffer_size", OPT_UINT,
            &cmdlineP->zlibCompression.buffer_size,
            &cmdlineP->zlibCompression.bufferSizeSpec,       0);
    OPTENT3(0, "gamma",            OPT_FLOAT,     &cmdlineP->gamma,
            &cmdlineP->gammaSpec,  0);
    OPTENT3(0, "hist",             OPT_FLAG,      NULL,
            &cmdlineP->hist,       0);
    OPTENT3(0, "downscale",        OPT_FLAG,      NULL,
            &cmdlineP->downscale,  0);
    OPTENT3(0, "interlace",        OPT_FLAG,      NULL,
            &cmdlineP->interlace,  0);
    OPTENT3(0, "force",            OPT_FLAG,      NULL,
            &cmdlineP->force,      0);
    OPTENT3(0, "libversion",       OPT_FLAG,      NULL,
            &cmdlineP->libversion, 0);
    OPTENT3(0, "verbose",          OPT_FLAG,      NULL,
            &cmdlineP->verbose,    0);
    OPTENT3(0, "nofilter",         OPT_FLAG,      NULL,
            &nofilter,             0);
    OPTENT3(0, "sub",              OPT_FLAG,      NULL,
            &sub,                  0);
    OPTENT3(0, "up",               OPT_FLAG,      NULL,
            &up,                   0);
    OPTENT3(0, "avg",              OPT_FLAG,      NULL,
            &avg,                  0);
    OPTENT3(0, "paeth",            OPT_FLAG,      NULL,
            &paeth,                0);
    OPTENT3(0, "filter",           OPT_INT,       &filter,
            &filterSpec,           0);
    OPTENT3(0, "verbose",          OPT_FLAG,      NULL,
            &cmdlineP->verbose,    0);
    OPTENT3(0, "chroma",           OPT_FLAG,      NULL,
            &chroma,               0);
    OPTENT3(0, "phys",             OPT_FLAG,      NULL,
            &phys,                 0);
    OPTENT3(0, "time",             OPT_FLAG,      NULL,
            &time,                 0);


    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = FALSE;  /* We have no parms that are negative numbers */

    pm_optParseOptions3(&argc, (char **)argv, opt, sizeof(opt), 0);
        /* Uses and sets argc, argv, and some of *cmdlineP and others. */


    if (chroma)
        pm_error("The -chroma option no longer exists.  Use -rgb instead.");
    if (phys)
        pm_error("The -phys option no longer exists.  Use -size instead.");
    if (time)
        pm_error("The -time option no longer exists.  Use -modtime instead.");

    if (alphaSpec + transparentSpec > 1)
        pm_error("You may not specify both -alpha and -transparent");
    if (!alphaSpec)
        cmdlineP->alpha = NULL;
    if (!transparentSpec)
        cmdlineP->transparent = NULL;
    if (!backgroundSpec)
        cmdlineP->background = NULL;
    if (!textSpec)
        cmdlineP->text = NULL;
    if (!ztxtSpec)
        cmdlineP->ztxt = NULL;
    if (!paletteSpec)
        cmdlineP->palette = NULL;
    
    if (filterSpec && (nofilter + sub + up + avg + paeth > 0))
        pm_error("You may mot specify -filter with "
                 "-nofilter, -sub, -up, -avg, or -paeth");
    
    if (filterSpec) {
        if (filter < 0 || filter > 4)
            pm_error("-filter is obsolete.  Use -nofilter, -sub, -up, -avg, "
                     "and -paeth options instead.");
        else {
            cmdlineP->filterSetSpec = true;

            switch (filter) {
            case 0: cmdlineP->filterSet = PNG_FILTER_NONE;  break;
            case 1: cmdlineP->filterSet = PNG_FILTER_SUB;   break;
            case 2: cmdlineP->filterSet = PNG_FILTER_UP;    break;
            case 3: cmdlineP->filterSet = PNG_FILTER_AVG;   break;
            case 4: cmdlineP->filterSet = PNG_FILTER_PAETH; break;
            }
        }
    } else {
        if (nofilter + sub + up + avg + paeth == 0)
            cmdlineP->filterSetSpec = false;
        else {
            cmdlineP->filterSetSpec = true;
            cmdlineP->filterSet = PNG_NO_FILTERS;  /* initial value */
            if (nofilter)
                cmdlineP->filterSet |= PNG_FILTER_NONE;
            if (sub)
                cmdlineP->filterSet |= PNG_FILTER_SUB;
            if (up)
                cmdlineP->filterSet |= PNG_FILTER_UP;
            if (avg)
                cmdlineP->filterSet |= PNG_FILTER_AVG;
            if (paeth)
                cmdlineP->filterSet |= PNG_FILTER_PAETH;
        }
    }

    if (cmdlineP->sizeSpec)
        parseSizeOpt(size, &cmdlineP->size);

    if (cmdlineP->rgbSpec)
        parseRgbOpt(rgb, &cmdlineP->rgb);
    
    if (cmdlineP->srgbintentSpec)
        parseSrgbintentOpt(srgbintent, &cmdlineP->srgbintent);

    if (cmdlineP->modtimeSpec)
        parseModtimeOpt(modtime, &cmdlineP->modtime);

    if (cmdlineP->zlibCompression.levelSpec &&
        cmdlineP->zlibCompression.level > 9)
        pm_error("-compression value must be from 0 (no compression) "
                 "to 9 (maximum compression).  You specified %u",
                 cmdlineP->zlibCompression.level);

    if (cmdlineP->zlibCompression.memLevelSpec) {
        if (cmdlineP->zlibCompression.mem_level  < 1 ||
            cmdlineP->zlibCompression.mem_level > 9)
        pm_error("-comp_mem_level value must be from 1 (minimum memory usage) "
                 "to 9 (maximum memory usage).  You specified %u",
                 cmdlineP->zlibCompression.mem_level);
    }

    if (cmdlineP->zlibCompression.methodSpec) {
        if (streq(compMethod, "deflated"))
            cmdlineP->zlibCompression.method = Z_DEFLATED;
        else
            pm_error("The only valid value for -method is 'deflated'.  "
                     "You specified '%s'", compMethod);
    }

    if (cmdlineP->zlibCompression.strategySpec) {
        if (streq(compStrategy, "huffman_only"))
            cmdlineP->zlibCompression.strategy = Z_HUFFMAN_ONLY;
        else if (streq(compStrategy, "filtered"))
            cmdlineP->zlibCompression.strategy = Z_FILTERED;
        else
            pm_error("Valid values for -strategy are 'huffman_only' and "
                     "filtered.  You specified '%s'", compStrategy);
    }


    if (argc-1 < 1)
        cmdlineP->inputFileName = "-";
    else if (argc-1 == 1)
        cmdlineP->inputFileName = argv[1];
    else
        pm_error("Program takes at most one argument:  input file name");
}



static void
reportInputType(int    const format,
                xelval const maxval) {

    switch (PNM_FORMAT_TYPE(format)) {
    case PBM_TYPE:
        pm_message ("reading a PBM file");
        break;
    case PGM_TYPE:
        pm_message ("reading a PGM file (maxval=%d)", maxval);
        break;
    case PPM_TYPE:
        pm_message ("reading a PPM file (maxval=%d)", maxval);
        break;
    default:
        assert(false);
    }
}



static png_color_16
xelToPngColor_16(xel    const input, 
                 xelval const maxval, 
                 xelval const pngMaxval) {

    png_color_16 retval;

    xel scaled;
    
    PPM_DEPTH(scaled, input, maxval, pngMaxval);

    retval.red   = PPM_GETR(scaled);
    retval.green = PPM_GETG(scaled);
    retval.blue  = PPM_GETB(scaled);
    retval.gray  = PNM_GET1(scaled);

    return retval;
}



static void
closestColorInPalette(pixel          const targetColor, 
                      pixel                palette_pnm[],
                      unsigned int   const paletteSize,
                      unsigned int * const bestIndexP,
                      unsigned int * const bestMatchP) {
    
    unsigned int paletteIndex;
    unsigned int bestIndex;
    unsigned int bestMatch;

    assert(paletteSize > 0);

    bestMatch = UINT_MAX;
    for (paletteIndex = 0; paletteIndex < paletteSize; ++paletteIndex) {
        unsigned int const dist = 
            PPM_DISTANCE(palette_pnm[paletteIndex], targetColor);

        if (dist < bestMatch) {
            bestMatch = dist;
            bestIndex = paletteIndex;
        }
    }
    if (bestIndexP != NULL)
        *bestIndexP = bestIndex;
    if (bestMatchP != NULL)
        *bestMatchP = bestMatch;
}



/* We really ought to make this hash function actually depend upon
   the "a" argument; we just don't know a decent prime number off-hand.
*/
#define HASH_SIZE 20023
#define hashpixelalpha(p,a) ((((long) PPM_GETR(p) * 33023 + \
                               (long) PPM_GETG(p) * 30013 + \
                               (long) PPM_GETB(p) * 27011 ) \
                              & 0x7fffffff ) % HASH_SIZE )

static coloralphahash_table
alloccoloralphahash(void)  {
    coloralphahash_table caht;
    int i;

    MALLOCARRAY(caht,HASH_SIZE);
    if (caht == NULL)
        pm_error( "out of memory allocating hash table" );

    for (i = 0; i < HASH_SIZE; ++i)
        caht[i] = NULL;

    return caht;
}


static void
freecoloralphahash(coloralphahash_table const caht) {
    int i;

    for (i = 0; i < HASH_SIZE; ++i) {
        cahitem * p;
        cahitem * next;
        for (p = caht[i]; p; p = next) {
            next = p->next;
            free(p);
        }
    }
    free(caht);
}



static void
addtocoloralphahash(coloralphahash_table const caht,
                    pixel *              const colorP,
                    gray *               const alphaP,
                    int                  const value) {

    int hash;
    cahitem * itemP;

    MALLOCVAR(itemP);
    if (itemP == NULL)
        pm_error("Out of memory building hash table");
    hash = hashpixelalpha(*colorP, *alphaP);
    itemP->color = *colorP;
    itemP->alpha = *alphaP;
    itemP->value = value;
    itemP->next = caht[hash];
    caht[hash] = itemP;
}



static int
lookupColorAlpha(coloralphahash_table const caht,
                 const pixel *        const colorP,
                 const gray *         const alphaP) {

    int hash;
    cahitem * p;

    hash = hashpixelalpha(*colorP, *alphaP);
    for (p = caht[hash]; p; p = p->next)
        if (PPM_EQUAL(p->color, *colorP) && p->alpha == *alphaP)
            return p->value;

    return -1;
}



/* The following variables belong to getChv() and freeChv() */
static bool getChv_computed = FALSE;
static colorhist_vector getChv_chv;



static void
getChv(FILE *             const ifP, 
       pm_filepos         const rasterPos,
       int                const cols, 
       int                const rows, 
       xelval             const maxval,
       int                const format, 
       int                const maxColors, 
       colorhist_vector * const chvP,
       unsigned int *     const colorsP) {
/*----------------------------------------------------------------------------
   Return a list of all the colors in a libnetpbm image and the number of
   times they occur.  The image is in the seekable file 'ifP', whose
   raster starts at position 'rasterPos' of the file.  The image's properties
   are 'cols', 'rows', 'maxval', and 'format'.

   Return the number of colors as *colorsP.  Return the details of the 
   colors in newly malloc'ed storage, and its address as *chvP.  If
   there are more than 'maxColors' colors, though, just return NULL as
   *chvP and leave *colorsP undefined.

   Don't spend the time to read the file if this subroutine has been called
   before.  In that case, just assume the inputs are all the same and return
   the previously computed information.  Ick.

   *chvP is in static program storage.
-----------------------------------------------------------------------------*/
    static unsigned int getChv_colors;

    if (!getChv_computed) {
        int colorCount;
        if (verbose) 
            pm_message ("Finding colors in input image...");

        pm_seek2(ifP, &rasterPos, sizeof(rasterPos));
        getChv_chv = ppm_computecolorhist2(ifP, cols, rows, maxval, format, 
                                           maxColors, &colorCount);
        
        getChv_colors = colorCount;

        if (verbose) {
            if (getChv_chv)
                pm_message("%u colors found", getChv_colors);
            else
                pm_message("Too many colors (more than %u) found", maxColors);
        }
        getChv_computed = TRUE;
    }
    *chvP = getChv_chv;
    *colorsP = getChv_colors;
}



static void freeChv(void) {

    if (getChv_computed)
        if (getChv_chv)
            ppm_freecolorhist(getChv_chv);

    getChv_computed = FALSE;
}



static bool
pgmBitsAreRepeated(unsigned int const repeatedSize,
                   FILE *       const ifP,
                   pm_filepos   const rasterPos, 
                   int          const cols,
                   int          const rows,
                   xelval       const maxval,
                   int          const format) {
/*----------------------------------------------------------------------------
   Return TRUE iff all the samples in the image in file 'ifP',
   described by 'cols', 'rows', 'maxval', and 'format', consist in the
   rightmost 'repeatedSize' * 2 bits of two identical sets of
   'repeatedSize' bits.

   The file has arbitrary position, but the raster is at file position
   'rasterPos'.

   E.g. for repeatedSize = 2, a sample value of 0xaa would qualify.
   So would 0x0a.

   Leave the file positioned where we found it.
-----------------------------------------------------------------------------*/
    unsigned int const mask2 = (1 << repeatedSize*2) - 1;
    unsigned int const mask1 = (1 << repeatedSize) - 1;

    bool mayscale;
    unsigned int row;
    xel * xelrow;

    xelrow = pnm_allocrow(cols);
    
    pm_seek2(ifP, &rasterPos, sizeof(rasterPos));

    mayscale = TRUE;  /* initial assumption */

    for (row = 0; row < rows && mayscale; ++row) {
        unsigned int col;
        pnm_readpnmrow(ifP, xelrow, cols, maxval, format);
        for (col = 0; col < cols && mayscale; ++col) {
            xelval const testbits2 = PNM_GET1(xelrow[col]) & mask2;
                /* The bits of interest in the sample */
            xelval const testbits1 = testbits2 & mask1;
                /* The lower half of the bits of interest in the sample */
            if (((testbits1 << repeatedSize) | testbits1) != testbits2)
                mayscale = FALSE;
        }
    }
    pnm_freerow(xelrow);

    return mayscale;
}



static void
meaningful_bits_pgm(FILE *         const ifP, 
                    pm_filepos     const rasterPos, 
                    int            const cols,
                    int            const rows,
                    xelval         const maxval,
                    int            const format,
                    unsigned int * const retvalP) {
/*----------------------------------------------------------------------------
   In the PGM raster with maxval 'maxval' at file offset 'rasterPos'
   in file 'ifp', the samples may be composed of groups of 1, 2, 4, or 8
   bits repeated.  This would be the case if the image were converted
   at some point from a 2 bits-per-pixel image to an 8-bits-per-pixel
   image, for example.

   If this is the case, we find out and find out how small these repeated
   groups of bits are and return the number of bits.
-----------------------------------------------------------------------------*/
    unsigned int maxMeaningfulBits;
        /* progressive estimate of the maximum number of meaningful
           (nonrepeated) bits in the samples.
        */

    maxMeaningfulBits = pm_maxvaltobits(maxval);  /* initial value */

    if (maxval == 0xffff || maxval == 0xff || maxval == 0xf || maxval == 0x3) {
        if (maxMeaningfulBits == 16) {
            if (pgmBitsAreRepeated(8,
                                   ifP, rasterPos, cols, rows, maxval, format))
                maxMeaningfulBits = 8;
        }
        if (maxMeaningfulBits == 8) {
            if (pgmBitsAreRepeated(4,
                                   ifP, rasterPos, cols, rows, maxval, format))
                maxMeaningfulBits = 4;
        }
        if (maxMeaningfulBits == 4) {
            if (pgmBitsAreRepeated(2,
                                   ifP, rasterPos, cols, rows, maxval, format))
                maxMeaningfulBits = 2;
        }
        if (maxMeaningfulBits == 2) {
            if (pgmBitsAreRepeated(1,
                                   ifP, rasterPos, cols, rows, maxval, format))
                maxMeaningfulBits = 1;
        }
    }
    *retvalP = maxMeaningfulBits;
}



static void
meaningful_bits_ppm(FILE *         const ifp, 
                    pm_filepos     const rasterPos, 
                    int            const cols,
                    int            const rows,
                    xelval         const maxval,
                    int            const format,
                    unsigned int * const retvalP) {
/*----------------------------------------------------------------------------
   In the PPM raster with maxval 'maxval' at file offset 'rasterPos'
   in file 'ifp', the samples may be composed of groups of 8
   bits repeated twice.  This would be the case if the image were converted
   at some point from a 8 bits-per-pixel image to an 16-bits-per-pixel
   image, for example.

   We return the smallest number of bits we can take from the right of
   a sample without losing information (8 or all).
-----------------------------------------------------------------------------*/
    int mayscale;
    unsigned int row;
    xel * xelrow;
    unsigned int maxMeaningfulBits;
        /* progressive estimate of the maximum number of meaningful
           (nonrepeated) bits in the samples.
        */

    xelrow = pnm_allocrow(cols);

    maxMeaningfulBits = pm_maxvaltobits(maxval);

    if (maxval == 65535) {
        mayscale = TRUE;   /* initial assumption */
        pm_seek2(ifp, &rasterPos, sizeof(rasterPos));
        for (row = 0; row < rows && mayscale; ++row) {
            unsigned int col;
            pnm_readpnmrow(ifp, xelrow, cols, maxval, format);
            for (col = 0; col < cols && mayscale; ++col) {
                xel const p = xelrow[col];
                if ((PPM_GETR(p) & 0xff) * 0x101 != PPM_GETR(p) ||
                    (PPM_GETG(p) & 0xff) * 0x101 != PPM_GETG(p) ||
                    (PPM_GETB(p) & 0xff) * 0x101 != PPM_GETB(p))
                    mayscale = FALSE;
            }
        }
        if (mayscale)
            maxMeaningfulBits = 8;
    }
    pnm_freerow(xelrow);

    *retvalP = maxMeaningfulBits;
}



static void
tryTransparentColor(FILE *     const ifp, 
                    pm_filepos const rasterPos, 
                    int        const cols, 
                    int        const rows, 
                    xelval     const maxval,
                    int        const format, 
                    gray **    const alphaMask,
                    gray       const alphaMaxval,
                    pixel      const transcolor,
                    bool *     const singleColorIsTransP) {

    int const pnmType = PNM_FORMAT_TYPE(format);

    xel * xelrow;
    bool singleColorIsTrans;
        /* So far, it looks like a single color is uniquely transparent */
    int row;

    xelrow = pnm_allocrow(cols);

    pm_seek2(ifp, &rasterPos, sizeof(rasterPos));

    singleColorIsTrans = TRUE;  /* initial assumption */
        
    for (row = 0; row < rows && singleColorIsTrans; ++row) {
        int col;
        pnm_readpnmrow(ifp, xelrow, cols, maxval, format);
        for (col = 0 ; col < cols && singleColorIsTrans; ++col) {
            if (alphaMask[row][col] == 0) { /* transparent */
                /* If we have a second transparent color, we're
                   disqualified
                */
                if (pnmType == PPM_TYPE) {
                    if (!PPM_EQUAL(xelrow[col], transcolor))
                        singleColorIsTrans = FALSE;
                } else {
                    if (PNM_GET1(xelrow[col]) != PNM_GET1(transcolor))
                        singleColorIsTrans = FALSE;
                }
            } else if (alphaMask[row][col] != alphaMaxval) {
                /* Here's an area of the mask that is translucent.  That
                   disqualified us.
                */
                singleColorIsTrans = FALSE;
            } else {
                /* Here's an area of the mask that is opaque.  If it's
                   the same color as our candidate transparent color,
                   that disqualifies us.
                */
                if (pnmType == PPM_TYPE) {
                    if (PPM_EQUAL(xelrow[col], transcolor))
                        singleColorIsTrans = FALSE;
                } else {
                    if (PNM_GET1(xelrow[col]) == PNM_GET1(transcolor))
                        singleColorIsTrans = FALSE;
                }
            }
        }
    }  
    *singleColorIsTransP = singleColorIsTrans;

    pnm_freerow(xelrow);
}



static void
analyzeAlpha(FILE *       const ifP,
             pm_filepos   const rasterPos, 
             unsigned int const cols, 
             unsigned int const rows, 
             xelval       const maxval,
             int          const format, 
             gray **      const alphaMask,
             gray         const alphaMaxval,
             bool *       const allOpaqueP,
             bool *       const singleColorIsTransP, 
             pixel *      const alphaTranscolorP) {
/*----------------------------------------------------------------------------
  Get information about the alpha mask, in combination with the masked
  image, that Caller can use to choose the most efficient way to
  represent the information in the alpha mask in a PNG.  Simply
  putting the alpha mask in the PNG is a last resort.  But if the mask
  says all opaque, we can simply omit any mention of transparency
  instead -- default is opaque.  And if the mask makes all the pixels
  of a certain color fully transparent and every other pixel opaque,
  we can simply identify that color in the PNG.

  We have to do this before any scaling occurs, since alpha is only
  possible with 8 and 16-bit.
-----------------------------------------------------------------------------*/
    xel * xelrow;
    bool foundTransparentPixel;
        /* We found a pixel in the image where the alpha mask says it is
           transparent.
        */
    pixel transcolor;
        /* Color of the transparent pixel mentioned above. */
    bool foundNonOpaquePixel;
        /* We found a pixel in the image where the alpha mask says it is
           not fully opaque.
        */
    
    xelrow = pnm_allocrow(cols);

    {
        unsigned int row;
        /* See if the mask says every pixel is opaque. */
        foundNonOpaquePixel = false;  /* initial assumption */
        pm_seek2(ifP, &rasterPos, sizeof(rasterPos));
        for (row = 0; row < rows && !foundNonOpaquePixel; ++row) {
            unsigned int col;
            pnm_readpnmrow(ifP, xelrow, cols, maxval, format);
            for (col = 0; col < cols && !foundNonOpaquePixel; ++col) {
                if (alphaMask[row][col] != maxval)
                    foundNonOpaquePixel = true;
            }
        }
    }

    if (foundNonOpaquePixel) {
        unsigned int row;
        /* Find a candidate transparent color -- the color of any pixel in the
           image that the alpha mask says should be transparent.
        */
        foundTransparentPixel = false;  /* initial assumption */
        pm_seek2(ifP, &rasterPos, sizeof(rasterPos));
        for (row = 0; row < rows && !foundTransparentPixel; ++row) {
            unsigned int col;
            pnm_readpnmrow(ifP, xelrow, cols, maxval, format);
            for (col = 0; col < cols && !foundTransparentPixel; ++col) {
                if (alphaMask[row][col] == 0) {
                    foundTransparentPixel = TRUE;
                    transcolor = pnm_xeltopixel(xelrow[col], format);
                }
            }
        }
    } else
        foundTransparentPixel = false;

    pnm_freerow(xelrow);

    *allOpaqueP = !foundNonOpaquePixel;

    if (foundTransparentPixel) {
        tryTransparentColor(ifP, rasterPos, cols, rows, maxval, format,
                            alphaMask, alphaMaxval, transcolor,
                            singleColorIsTransP);
        *alphaTranscolorP = transcolor;
    } else
        *singleColorIsTransP = false;
}



static void
determineTransparency(struct cmdlineInfo const cmdline,
                      FILE *             const ifP,
                      pm_filepos         const rasterPos,
                      unsigned int       const cols,
                      unsigned int       const rows,
                      xelval             const maxval,
                      int                const format,
                      FILE *             const afP,
                      bool *             const alphaP,
                      int *              const transparentP,
                      pixel *            const transColorP,
                      bool *             const transExactP,
                      gray ***           const alphaMaskP,
                      gray *             const alphaMaxvalP) {
/*----------------------------------------------------------------------------
   Determine the various aspects of transparency we need to generate the
   PNG.

   Note that there are two kinds of transparency: pixel-by-pixel
   transparency/translucency with an alpha mask and all pixels of a certain
   color being transparent.  Both these exist both in input from the user and
   as representations in the PNG -- i.e. user may supply an alpha mask,
   or identify a transparent color and the PNG may contain an alpha mask
   or identify a transparent color.

   We return as *transparentP:
   
     -1 PNG is not to have single-color transparency
      1 PNG is to have single-color transparency as directed by user
      2 PNG is to have single-color transparency that effects an alpha
            mask that the user supplied.

   In the cases where there is to be single-color transparency, *transColorP
   is that color.
-----------------------------------------------------------------------------*/
    if (cmdline.alpha) {
        pixel alphaTranscolor;
        bool alphaCanBeTransparencyIndex;
        bool allOpaque;
        int alphaCols, alphaRows;
        gray alphaMaxval;
        gray ** alphaMask;

        if (verbose)
            pm_message("reading alpha-channel image...");
        alphaMask = pgm_readpgm(afP, &alphaCols, &alphaRows, &alphaMaxval);

        if (alphaCols != cols || alphaRows != rows) {
            pm_error("dimensions for image and alpha mask do not agree");
        }
        analyzeAlpha(ifP, rasterPos, cols, rows, maxval, format, 
                     alphaMask, alphaMaxval, &allOpaque,
                     &alphaCanBeTransparencyIndex, &alphaTranscolor);

        if (alphaCanBeTransparencyIndex && !cmdline.force) {
            if (verbose)
                pm_message("converting alpha mask to transparency index");
            *alphaP       = FALSE;
            *transparentP = 2;
            *transColorP  = alphaTranscolor;
        } else if (allOpaque) {
            if (verbose)
                pm_message("Skipping alpha because mask is all opaque");
            *alphaP       = FALSE;
            *transparentP = -1;
        } else {
            *alphaP       = TRUE;
            *transparentP = -1;
        }
        *alphaMaxvalP = alphaMaxval;
        *alphaMaskP   = alphaMask;
    } else {
        /* Though there's no alpha_mask, we still need an alpha_maxval for
           use with trans[], which can have stuff in it if the user specified
           a transparent color.
        */
        *alphaP       = FALSE;
        *alphaMaxvalP = 255;

        if (cmdline.transparent) {
            const char * transstring2;  
            /* The -transparent value, but with possible leading '=' removed */
            if (cmdline.transparent[0] == '=') {
                *transExactP = TRUE;
                transstring2 = &cmdline.transparent[1];
            } else {
                *transExactP = FALSE;
                transstring2 = cmdline.transparent;
            }  
            /* We do this funny PPM_DEPTH thing instead of just passing 'maxval'
               to ppm_parsecolor() because ppm_parsecolor() does a cheap maxval
               scaling, and this is more precise.
            */
            PPM_DEPTH(*transColorP, 
                      ppm_parsecolor(transstring2, PNM_OVERALLMAXVAL),
                      PNM_OVERALLMAXVAL, maxval);

            *transparentP = 1;
        } else
            *transparentP = -1;
    }
}



static void
determineBackground(struct cmdlineInfo const cmdline,
                    xelval             const maxval,
                    xel *              const backColorP) {

  if (cmdline.background) 
      PPM_DEPTH(*backColorP,
                ppm_parsecolor(cmdline.background, PNM_OVERALLMAXVAL), 
                PNM_OVERALLMAXVAL, maxval);;
}



static bool
hasColor(FILE *       const ifP,
         unsigned int const cols,
         unsigned int const rows,
         xelval       const maxval,
         int          const format,
         pm_filepos   const rasterPos) {
/*----------------------------------------------------------------------------
   The image contains colors other than black, white, and gray.
-----------------------------------------------------------------------------*/
    bool retval;

    if (PNM_FORMAT_TYPE(format) == PPM_TYPE) {
        unsigned int row;
        xel * xelrow;    /* malloc'ed */
            /* The row of the input image currently being analyzed */
        bool isGray;

        xelrow = pnm_allocrow(cols);

        pm_seek2(ifP, &rasterPos, sizeof(rasterPos));

        for (row = 0, isGray = true; row < rows && isGray; ++row) {
            unsigned int col;

            pnm_readpnmrow(ifP, xelrow, cols, maxval, format);

            for (col = 0; col < cols && isGray; ++col) {
                    xel const p = xelrow[col];
                if (PPM_GETR(p) != PPM_GETG(p) || PPM_GETG(p) != PPM_GETB(p))
                    isGray = FALSE;
            }
        }

        pnm_freerow(xelrow);

        retval = !isGray;
    } else
        retval = false;

    return retval;
}



static void
findRedundantBits(FILE *         const ifp, 
                  int            const rasterPos, 
                  int            const cols,
                  int            const rows,
                  xelval         const maxval,
                  int            const format,
                  bool           const alpha,
                  bool           const force,
                  unsigned int * const meaningfulBitsP) {
/*----------------------------------------------------------------------------
   Find out if we can use just a subset of the bits from each input
   sample.  Often, people create an image with e.g. 8 bit samples from
   one that has e.g. only 4 bit samples by scaling by 255/15, which is
   the same as repeating the bits.  E.g.  1011 becomes 10111011.  We
   detect this case.  We return as *meaningfulBitsP the minimum number
   of bits, starting from the least significant end, that contain
   original information.
-----------------------------------------------------------------------------*/
  if (!alpha && PNM_FORMAT_TYPE(format) == PGM_TYPE && !force) 
      meaningful_bits_pgm(ifp, rasterPos, cols, rows, maxval, format,
                          meaningfulBitsP);
  else if (PNM_FORMAT_TYPE(format) == PPM_TYPE && !force)
      meaningful_bits_ppm(ifp, rasterPos, cols, rows, maxval, format,
                          meaningfulBitsP);
  else 
      *meaningfulBitsP = pm_maxvaltobits(maxval);

  if (verbose && *meaningfulBitsP != pm_maxvaltobits(maxval))
      pm_message("Using only %d rightmost bits of input samples.  The "
                 "rest are redundant.", *meaningfulBitsP);
}



static void
readOrderedPalette(FILE *         const pfp,
                   xel                  ordered_palette[], 
                   unsigned int * const ordered_palette_size_p) {

    xel ** xels;
    int cols, rows;
    xelval maxval;
    int format;
    
    if (verbose)
        pm_message("reading ordered palette (colormap)...");

    xels = pnm_readpnm(pfp, &cols, &rows, &maxval, &format);
    
    if (PNM_FORMAT_TYPE(format) != PPM_TYPE) 
        pm_error("ordered palette must be a PPM file, not type %d", format);

    *ordered_palette_size_p = rows * cols;
    if (*ordered_palette_size_p > MAXCOLORS) 
        pm_error("ordered-palette image contains %d pixels.  Maximum is %d",
                 *ordered_palette_size_p, MAXCOLORS);
    if (verbose)
        pm_message("%u colors found", *ordered_palette_size_p);

    {
        unsigned int j;
        unsigned int row;
        j = 0;  /* initial value */
        for (row = 0; row < rows; ++row) {
            int col;
            for (col = 0; col < cols; ++col) 
                ordered_palette[j++] = xels[row][col];
        }
    }
    pnm_freearray(xels, rows);
}        



static void
compute_nonalpha_palette(colorhist_vector const chv,
                         int              const colors,
                         pixval           const maxval,
                         FILE *           const pfp,
                         pixel                  palette_pnm[],
                         unsigned int *   const paletteSizeP,
                         gray                   trans_pnm[],
                         unsigned int *   const transSizeP) {
/*----------------------------------------------------------------------------
   Compute the palette corresponding to the color set 'chv'
   (consisting of 'colors' distinct colors) assuming a pure-color (no
   transparency) palette.

   If 'pfp' is non-null, assume it's a PPM file and read the palette
   from that.  Make sure it contains the same colors as the palette
   we computed ourself would have.  Caller supplied the file because he
   wants the colors in a particular order in the palette.
-----------------------------------------------------------------------------*/
    unsigned int colorIndex;
    
    xel ordered_palette[MAXCOLORS];
    unsigned int ordered_palette_size;

    if (pfp) {
        readOrderedPalette(pfp, ordered_palette, &ordered_palette_size);

        if (colors != ordered_palette_size) 
            pm_error("sizes of ordered palette (%d) "
                     "and existing palette (%d) differ",
                     ordered_palette_size, colors);
        
        /* Make sure the ordered palette contains all the colors in
           the image 
        */
        for (colorIndex = 0; colorIndex < colors; colorIndex++) {
            int j;
            bool found;
            
            found = FALSE;
            for (j = 0; j < ordered_palette_size && !found; ++j) {
                if (PNM_EQUAL(ordered_palette[j], chv[colorIndex].color)) 
                    found = TRUE;
            }
            if (!found) 
                pm_error("failed to find color (%d, %d, %d), which is in the "
                         "input image, in the ordered palette",
                         PPM_GETR(chv[colorIndex].color),
                         PPM_GETG(chv[colorIndex].color),
                         PPM_GETB(chv[colorIndex].color));
        }
        /* OK, the ordered palette passes muster as a palette; go ahead
           and return it as the palette.
        */
        for (colorIndex = 0; colorIndex < colors; ++colorIndex)
            palette_pnm[colorIndex] = ordered_palette[colorIndex];
    } else {
        for (colorIndex = 0; colorIndex < colors; ++colorIndex) 
            palette_pnm[colorIndex] = chv[colorIndex].color;
    }
    *paletteSizeP = colors;
    *transSizeP = 0;
}



static bool
isPowerOfTwoOrZero(unsigned int const arg) {

    unsigned int i;
    unsigned int mask;
    unsigned int nOneBit;

    for (i = 0, mask = 0x1, nOneBit = 0;
         i < sizeof(arg) * 8;
         ++i, mask <<= 1) {

        if (arg & mask)
            ++nOneBit;
        if (nOneBit > 1)
            return false;
    }
    return true;
}



static void
addColorAlphaPair(gray **        const alphasOfColor,
                  unsigned int * const alphasOfColorCnt,
                  unsigned int   const colorIndex,
                  gray           const alpha) {
/*----------------------------------------------------------------------------
   Add the pair (colorIndex, alpha) to the palette
   (alphasOfColor, alphasOfColorCnt).
-----------------------------------------------------------------------------*/
    unsigned int const colorCnt = alphasOfColorCnt[colorIndex];

    if (isPowerOfTwoOrZero(colorCnt)) {
        /* We've filled the current memory allocation.  Expand. */

        REALLOCARRAY(alphasOfColor[colorIndex], MAX(1, colorCnt * 2));

        if (alphasOfColor[colorIndex] == NULL)
            pm_error("Out of memory allocating color/alpha palette space "
                     "for %u alpha values for color index %u",
                     colorCnt * 2, colorIndex);
    }

    alphasOfColor[colorIndex][colorCnt] = alpha;
    ++alphasOfColorCnt[colorIndex];
}



static void
freeAlphasOfColor(gray **      const alphasOfColor,
                  unsigned int const colorCount) {

    unsigned int colorIndex;

    for (colorIndex = 0; colorIndex < colorCount; ++colorIndex)
        free(alphasOfColor[colorIndex]);
}



static void
computeUnsortedAlphaPalette(FILE *           const ifP,
                            int              const cols,
                            int              const rows,
                            xelval           const maxval,
                            int              const format,
                            pm_filepos       const rasterPos,
                            gray **          const alphaMask,
                            colorhist_vector const chv,
                            int              const colors,
                            unsigned int     const maxPaletteEntries,
                            gray *                 alphasOfColor[],
                            unsigned int           alphasFirstIndex[],
                            unsigned int           alphasOfColorCnt[],
                            bool *           const tooBigP) {
/*----------------------------------------------------------------------------
   Read the image at position 'rasterPos' in file *ifP, which is a PNM
   described by 'cols', 'rows', 'maxval', and 'format'.

   Using the alpha mask 'alpha_mask' and color map 'chv' (of size 'colors')
   for the image, construct a palette of (color index, alpha) ordered pairs 
   for the image, as follows.

   The alpha/color palette is the set of all ordered pairs of
   (color,alpha) in the PNG, including the background color.  The
   actual palette is an array.  Each array element contains a color
   index from the color palette and an alpha value.  All the elements
   with the same color index are contiguous.  alphasFirstIndex[x] is
   the index in the alpha/color palette of the first element that has
   color index x.  alphasOfColorCnt[x] is the number of elements that
   have color index x.  alphasOfColor[x][y] is the yth alpha value
   that appears with color index x (in order of appearance).

   The palette we produce does not go out of its way to include the
   background color; unless the background color is also in the image,
   Caller will have to add it.

   To save time, we give up as soon as we know there are more than
   'maxPaletteEntries' in the palette.  We return *tooBigP indicating
   whether that was the case.
-----------------------------------------------------------------------------*/
    colorhash_table cht;
    int colorIndex;
    bool tooBig;
    int row;
    xel * xelrow;
    unsigned int alphaColorPairCnt;
        /* Number of different alpha/color pairs we've seen so far as we
           iterate through the image.
        */

    cht = ppm_colorhisttocolorhash(chv, colors);

    /* We have not seen any alphas of any color yet. */
    alphaColorPairCnt = 0;
    for (colorIndex = 0; colorIndex < colors; ++colorIndex) {
        alphasOfColor[colorIndex] = NULL;
        alphasOfColorCnt[colorIndex] = 0;
    }
 
    pm_seek2(ifP, &rasterPos, sizeof(rasterPos));

    xelrow = pnm_allocrow(cols);

    tooBig = false;  /* initial assumption */

    for (row = 0; row < rows && !tooBig; ++row) {
        unsigned int col;
        pnm_readpnmrow(ifP, xelrow, cols, maxval, format);
        pnm_promoteformatrow(xelrow, cols, maxval, format, maxval, PPM_TYPE);

        for (col = 0; col < cols; ++col) {
            unsigned int i;
            int const colorIndex = ppm_lookupcolor(cht, &xelrow[col]);
            for (i = 0 ; i < alphasOfColorCnt[colorIndex] ; ++i) {
                if (alphaMask[row][col] == alphasOfColor[colorIndex][i])
                    break;
            }
            if (i == alphasOfColorCnt[colorIndex]) {
                if (alphaColorPairCnt >= maxPaletteEntries) {
                    tooBig = true;
                    break;
                } else {
                    addColorAlphaPair(alphasOfColor, alphasOfColorCnt,
                                      colorIndex, alphaMask[row][col]);
                    ++alphaColorPairCnt;
                }
            }
        }
    }
    if (tooBig)
        freeAlphasOfColor(alphasOfColor, colors);
    else {
        unsigned int i;
        alphasFirstIndex[0] = 0;
        for (i = 1; i < colors; ++i)
            alphasFirstIndex[i] = alphasFirstIndex[i-1] +
                alphasOfColorCnt[i-1];
    }
    pnm_freerow(xelrow);
    ppm_freecolorhash(cht);

    *tooBigP = tooBig;
}



static void
sortAlphaPalette(gray *         const alphasOfColor[],
                 unsigned int   const alphasFirstIndex[],
                 unsigned int   const alphasOfColorCnt[],
                 unsigned int   const colors,
                 gray           const alphaMaxval,
                 unsigned int         mapping[],
                 unsigned int * const transSizeP) {
/*----------------------------------------------------------------------------
   Remap the palette indices so opaque entries are last.

   This is _not_ a sort in place -- we do not modify our inputs.

   alphas_of_color[], alphas_first_index[], and alphas_of_color_cnt[]
   describe an unsorted PNG (alpha/color) palette.  We generate
   mapping[] such that mapping[x] is the index into the sorted PNG
   palette of the alpha/color pair whose index is x in the unsorted
   PNG palette.  This mapping sorts the palette so that opaque entries
   are last.

   The unsorted PNG palette is sorted enough that all entries for a particular
   color (with varying transparencies) are contiguous.  alphasFirstIndex[x] is
   the index in the unsorted PNG palette of the first entry with color x
   (where x is an index into some other palette).  alphasOfColorCnt[x] is the
   number of non-opaque entries in the unsorted PNG palette with color x.

   alphasOfColor[x][y] is the y'th alpha value for color x, in no particular
   order.

   Return as *transSizeP the number of non-opaque entries in the palette
   (i.e. the index in the palette of the first opaque entry).
-----------------------------------------------------------------------------*/
    if (colors == 0)
        *transSizeP = 0;
    else {
        unsigned int bot_idx;
        unsigned int top_idx;
        unsigned int colorIndex;
    
        /* We start one index at the bottom of the palette index range
           and another at the top.  We run through the unsorted palette,
           and when we see an opaque entry, we map it to the current top
           cursor and bump it down.  When we see a non-opaque entry, we map 
           it to the current bottom cursor and bump it up.  Because the input
           and output palettes are the same size, the two cursors should meet
           right when we process the last entry of the unsorted palette.
        */    
        bot_idx = 0;
        top_idx = alphasFirstIndex[colors-1] + alphasOfColorCnt[colors-1] - 1;
    
        for (colorIndex = 0;  colorIndex < colors;  ++colorIndex) {
            unsigned int j;
            for (j = 0; j < alphasOfColorCnt[colorIndex]; ++j) {
                unsigned int const paletteIndex = 
                    alphasFirstIndex[colorIndex] + j;
                if (alphasOfColor[colorIndex][j] == alphaMaxval)
                    mapping[paletteIndex] = top_idx--;
                else
                    mapping[paletteIndex] = bot_idx++;
            }
        }
        /* indices should have just crossed paths */
        if (bot_idx != top_idx + 1) {
            pm_error ("internal inconsistency: "
                      "remapped bot_idx = %u, top_idx = %u",
                      bot_idx, top_idx);
        }
        *transSizeP = bot_idx;
    }
}



static void
compute_alpha_palette(FILE *         const ifP, 
                      int            const cols,
                      int            const rows,
                      xelval         const maxval,
                      int            const format,
                      pm_filepos     const rasterPos,
                      gray **        const alpha_mask,
                      gray           const alphaMaxval,
                      pixel                palette_pnm[],
                      gray                 trans_pnm[],
                      unsigned int * const paletteSizeP,
                      unsigned int * const transSizeP,
                      bool *         const tooBigP) {
/*----------------------------------------------------------------------------
   Return the palette of color/alpha pairs for the image indicated by
   'ifP', 'cols', 'rows', 'maxval', 'format', and 'rasterPos'.
   alpha_mask[] is the Netpbm-style alpha mask for the image.

   Return the palette as the arrays palette_pnm[] and trans_pnm[].
   The ith entry in the palette is the combination of palette_pnm[i],
   which defines the color, and trans_pnm[i], which defines the
   transparency.

   Return the number of entries in the palette as *paletteSizeP.

   The palette is sorted so that the opaque entries are last, and we return
   *transSizeP as the number of non-opaque entries.

   palette[] and trans[] are allocated by the caller to at least 
   MAXPALETTEENTRIES elements.

   If there are more than MAXPALETTEENTRIES color/alpha pairs in the image, 
   don't return any palette information -- just return *tooBigP == TRUE.
-----------------------------------------------------------------------------*/
    colorhist_vector chv;
    unsigned int colors;

    gray * alphas_of_color[MAXPALETTEENTRIES];
    unsigned int alphas_first_index[MAXPALETTEENTRIES];
    unsigned int alphas_of_color_cnt[MAXPALETTEENTRIES];
 
    getChv(ifP, rasterPos, cols, rows, maxval, format, MAXCOLORS, 
           &chv, &colors);

    assert(colors <= ARRAY_SIZE(alphas_of_color));

    computeUnsortedAlphaPalette(ifP, cols, rows, maxval, format, rasterPos,
                                alpha_mask, chv, colors,
                                MAXPALETTEENTRIES,
                                alphas_of_color,
                                alphas_first_index,
                                alphas_of_color_cnt,
                                tooBigP);

    if (!*tooBigP) {
        unsigned int mapping[MAXPALETTEENTRIES];
            /* Sorting of the alpha/color palette.  mapping[x] is the
               index into the sorted PNG palette of the alpha/color
               pair whose index is x in the unsorted PNG palette.
               This mapping sorts the palette so that opaque entries
               are last.  
            */

        *paletteSizeP = colors == 0 ?
            0 :
            alphas_first_index[colors-1] + alphas_of_color_cnt[colors-1];
        assert(*paletteSizeP <= MAXPALETTEENTRIES);

        /* Make the opaque palette entries last */
        sortAlphaPalette(alphas_of_color, alphas_first_index,
                         alphas_of_color_cnt, colors, alphaMaxval,
                         mapping, transSizeP);

        {
            unsigned int colorIndex;

            for (colorIndex = 0; colorIndex < colors; ++colorIndex) {
                unsigned int j;
                for (j = 0; j < alphas_of_color_cnt[colorIndex]; ++j) {
                    unsigned int const paletteIndex = 
                        alphas_first_index[colorIndex] + j;
                    palette_pnm[mapping[paletteIndex]] = chv[colorIndex].color;
                    trans_pnm[mapping[paletteIndex]] = 
                    alphas_of_color[colorIndex][j];
                }
            }
        }
        freeAlphasOfColor(alphas_of_color, colors);
    }
} 



static void
makeOneColorTransparentInPalette(xel            const transColor, 
                                 bool           const exact,
                                 pixel                palette_pnm[],
                                 unsigned int   const paletteSize,
                                 gray                 trans_pnm[],
                                 unsigned int * const transSizeP) {
/*----------------------------------------------------------------------------
   Find the color 'transColor' in the color/alpha palette defined by
   palette_pnm[], paletteSize, trans_pnm[] and *transSizeP.  

   Make that entry fully transparent.

   Rearrange the palette so that that entry is first.  (The PNG compressor
   can do a better job when the opaque entries are all last in the 
   color/alpha palette).

   If the specified color is not there and exact == TRUE, return
   without changing anything, but issue a warning message.  If it's
   not there and exact == FALSE, just find the closest color.

   We assume every entry in the palette is opaque upon entry.

   A valid palette has at least one color.
-----------------------------------------------------------------------------*/
    unsigned int transparentIndex;
    unsigned int distance;

    assert(paletteSize > 0);
    
    if (*transSizeP != 0)
        pm_error("Internal error: trying to make a color in the palette "
                 "transparent where there already is one.");

    closestColorInPalette(transColor, palette_pnm, paletteSize, 
                          &transparentIndex, &distance);

    if (distance != 0 && exact) {
        pm_message("specified transparent color not present in palette; "
                   "ignoring -transparent");
        errorlevel = PNMTOPNG_WARNING_LEVEL;
    } else {        
        /* Swap this with the first entry in the palette */
        pixel tmp;
    
        tmp = palette_pnm[transparentIndex];
        palette_pnm[transparentIndex] = palette_pnm[0];
        palette_pnm[0] = tmp;
        
        /* Make it transparent */
        trans_pnm[0] = PGM_TRANSPARENT;
        *transSizeP = 1;
        if (verbose) {
            pixel const p = palette_pnm[0];
            pm_message("Making all occurrences of color (%u, %u, %u) "
                       "transparent.",
                       PPM_GETR(p), PPM_GETG(p), PPM_GETB(p));
        }
    }
}



static void
findOrAddBackgroundInPalette(pixel          const backColor, 
                             pixel                palette_pnm[], 
                             unsigned int * const paletteSizeP,
                             unsigned int * const backgroundIndexP) {
/*----------------------------------------------------------------------------
  Add the background color 'backColor' to the palette, unless
  it's already in there.  If it's not present and there's no room to
  add it, choose a background color that's already in the palette,
  as close to 'backColor' as possible.

  If we add an entry to the palette, make it opaque.  But in searching the 
  existing palette, ignore transparency.

  Note that PNG specs say that transparency of the background is meaningless;
  i.e. a viewer must ignore the transparency of the palette entry when 
  using the background color.

  Return the palette index of the background color as *backgroundIndexP.
-----------------------------------------------------------------------------*/
    int backgroundIndex;  /* negative means not found */
    unsigned int paletteIndex;

    backgroundIndex = -1;
    for (paletteIndex = 0; 
         paletteIndex < *paletteSizeP; 
         ++paletteIndex) 
        if (PPM_EQUAL(palette_pnm[paletteIndex], backColor))
            backgroundIndex = paletteIndex;

    if (backgroundIndex >= 0) {
        /* The background color is already in the palette. */
        *backgroundIndexP = backgroundIndex;
        if (verbose) {
            pixel const p = palette_pnm[*backgroundIndexP];
            pm_message("background color (%u, %u, %u) appears in image.",
                       PPM_GETR(p), PPM_GETG(p), PPM_GETB(p));
        }
    } else {
        /* Try to add the background color, opaque, to the palette. */
        if (*paletteSizeP < MAXCOLORS) {
            /* There's room, so just add it to the end of the palette */

            /* Because we're not expanding the transparency palette, this
               entry is not in it, and is thus opaque.
            */
            *backgroundIndexP = (*paletteSizeP)++;
            palette_pnm[*backgroundIndexP] = backColor;
            if (verbose) {
                pixel const p = palette_pnm[*backgroundIndexP];
                pm_message("added background color (%u, %u, %u) to palette.",
                           PPM_GETR(p), PPM_GETG(p), PPM_GETB(p));
            }
        } else {
            closestColorInPalette(backColor, palette_pnm, *paletteSizeP,
                                  backgroundIndexP, NULL);
            errorlevel = PNMTOPNG_WARNING_LEVEL;
            {
                pixel const p = palette_pnm[*backgroundIndexP];
                pm_message("no room in palette for background color; "
                           "using closest match (%u, %u, %u) instead",
                           PPM_GETR(p), PPM_GETG(p), PPM_GETB(p));
            }
        }
    }
}



static void 
buildColorLookup(pixel                   palette_pnm[], 
                 unsigned int      const paletteSize,
                 colorhash_table * const chtP) {
/*----------------------------------------------------------------------------
   Create a colorhash_table out of the palette described by
   palette_pnm[] (which has 'paletteSize' entries) so one can look up
   the palette index of a given color.

   Where the same color appears twice in the palette, the lookup table
   finds an arbitrary one of them.  We don't consider transparency of
   palette entries, so if the same color appears in the palette once
   transparent and once opaque, the lookup table finds an arbitrary one
   of those two.
-----------------------------------------------------------------------------*/
    colorhash_table const cht = ppm_alloccolorhash();
    unsigned int paletteIndex;

    for (paletteIndex = 0; paletteIndex < paletteSize; ++paletteIndex) {
        ppm_addtocolorhash(cht, &palette_pnm[paletteIndex], paletteIndex);
    }
    *chtP = cht;
}



static void 
buildColorAlphaLookup(pixel              palette_pnm[], 
                      unsigned int const paletteSize,
                      gray               trans_pnm[], 
                      unsigned int const transSize,
                      gray         const alphaMaxval,
                      coloralphahash_table * const cahtP) {
    
    coloralphahash_table const caht = alloccoloralphahash();

    unsigned int paletteIndex;

    for (paletteIndex = 0; paletteIndex < paletteSize; ++paletteIndex) {
        gray paletteTrans;

        if (paletteIndex < transSize)
            paletteTrans = alphaMaxval;
        else
            paletteTrans = trans_pnm[paletteIndex];

        addtocoloralphahash(caht, &palette_pnm[paletteIndex],
                            &trans_pnm[paletteIndex], paletteIndex);
    }
    *cahtP = caht;
}



static void
tryAlphaPalette(FILE *         const ifP,
                int            const cols,
                int            const rows,
                xelval         const maxval,
                int            const format,
                pm_filepos     const rasterPos,
                gray **        const alpha_mask,
                gray           const alphaMaxval,
                FILE *         const pfP,
                pixel *        const palette_pnm,
                unsigned int * const paletteSizeP,
                gray *         const trans_pnm,
                unsigned int * const transSizeP,
                const char **  const impossibleReasonP) {
/*----------------------------------------------------------------------------
   Try to make an alpha palette as 'trans_pnm', size *transSizeP.

   If it's impossible, return as *impossibleReasonP newly malloced storage
   containing text that tells why.  But if we succeed, return
   *impossibleReasonP == NULL.
-----------------------------------------------------------------------------*/
    bool tooBig;
    if (pfP)
        pm_error("This program is not capable of generating "
                 "a PNG with transparency when you specify "
                 "the palette with -palette.");

    compute_alpha_palette(ifP, cols, rows, maxval, format, 
                          rasterPos,  alpha_mask, alphaMaxval,
                          palette_pnm, trans_pnm, 
                          paletteSizeP, transSizeP, &tooBig);
    if (tooBig) {
        pm_asprintf(impossibleReasonP,
                    "too many color/transparency pairs "
                    "(more than the PNG maximum of %u", 
                    MAXPALETTEENTRIES);
    } else
        *impossibleReasonP = NULL;
} 



static void
computePixelWidth(bool           const colorPng,
                  unsigned int   const pnmMeaningfulBitCt,
                  bool           const alpha,
                  unsigned int * const bitsPerSampleP,
                  unsigned int * const bitsPerPixelP) {

    unsigned int bitsPerSample, bitsPerPixel;

    if (colorPng || alpha) {
        /* PNG allows only depths of 8 and 16 for a truecolor image 
           and for a grayscale image with an alpha channel.
          */
        if (pnmMeaningfulBitCt > 8)
            bitsPerSample = 16;
        else 
            bitsPerSample = 8;
    } else {
        /* A grayscale, non-colormapped, no-alpha PNG may have any 
             bit depth from 1 to 16
          */
        if (pnmMeaningfulBitCt > 8)
            bitsPerSample = 16;
        else if (pnmMeaningfulBitCt > 4)
            bitsPerSample = 8;
        else if (pnmMeaningfulBitCt > 2)
            bitsPerSample = 4;
        else if (pnmMeaningfulBitCt > 1)
            bitsPerSample = 2;
        else
            bitsPerSample = 1;
    }
    if (alpha) {
        if (colorPng)
            bitsPerPixel = 4 * bitsPerSample;
        else
            bitsPerPixel = 2 * bitsPerSample;
    } else {
        if (colorPng)
            bitsPerPixel = 3 * bitsPerSample;
        else
            bitsPerPixel = bitsPerSample;
    }
    if (bitsPerPixelP)
        *bitsPerPixelP = bitsPerPixel;
    if (bitsPerSampleP)
        *bitsPerSampleP = bitsPerSample;
}



static unsigned int
paletteIndexBits(unsigned int const nColors) {
/*----------------------------------------------------------------------------
  Return the number of bits that a palette index in the PNG will
  occupy given that the palette has 'nColors' colors in it.  It is 1,
  2, 4, or 8 bits.
  
  If 'nColors' is not a valid PNG palette size, return 0.
-----------------------------------------------------------------------------*/
    unsigned int retval;

    if (nColors < 1)
        retval = 0;
    else if (nColors <= 2)
        retval = 1;
    else if (nColors <= 4)
        retval = 2;
    else if (nColors <= 16)
        retval = 4;
    else if (nColors <= 256)
        retval = 8;
    else
        retval = 0;

    return retval;
}



static void
computeColorMap(FILE *         const ifP,
                pm_filepos     const rasterPos,
                int            const cols,
                int            const rows,
                xelval         const maxval,
                bool           const colorPng,
                int            const format,
                bool           const force,
                FILE *         const pfP,
                bool           const alpha,
                bool           const transparent,
                pixel          const transcolor,
                bool           const transexact,
                bool           const background,
                pixel          const backcolor,
                gray **        const alpha_mask,
                gray           const alphaMaxval,
                unsigned int   const pnm_meaningful_bits,
                /* Outputs */
                pixel *        const palette_pnm,
                unsigned int * const paletteSizeP,
                gray *         const trans_pnm,
                unsigned int * const transSizeP,
                unsigned int * const backgroundIndexP,
                const char **  const noColormapReasonP) {
/*---------------------------------------------------------------------------
  Determine whether to do a colormapped or truecolor PNG and if
  colormapped, compute the full PNG palette -- both color and
  transparency.

  If we decide to do truecolor, we return as *noColormapReasonP a text
  description of why, in newly malloced memory.  If we decide to go
  with colormapped, we return *noColormapReasonP == NULL.

  In the colormapped case, we return the palette as arrays
  palette_pnm[] and trans_pnm[], allocated by Caller, with sizes
  *paletteSizeP and *transSizeP.

  'pfP' is a handle to the file that the user requested be used for the
  palette (it's a Netpbm image whose colors are the colors of the palette).
  'pfP' is null if the user did not request a particular palette.

  'background' means the image is to have a background color, and that
  color is 'backcolor'.  'backcolor' is meaningless when 'background'
  is false.

  If the image is to have a background color, we return the palette index
  of that color as *backgroundIndexP.

  'colorPng' means the PNG will be of the RGB variety.
-------------------------------------------------------------------------- */
    if (force)
        pm_asprintf(noColormapReasonP, "You requested no color map");
    else if (maxval > PALETTEMAXVAL)
        pm_asprintf(noColormapReasonP, "The maxval of the input image (%u) "
                    "exceeds the PNG palette maxval (%u)", 
                    maxval, PALETTEMAXVAL);
    else {
        unsigned int bitsPerPixel;
        computePixelWidth(colorPng, pnm_meaningful_bits, alpha,
                          NULL, &bitsPerPixel);

        if (!pfP && bitsPerPixel == 1)
            /* No palette can beat 1 bit per pixel -- no need to waste time
               counting the colors.
            */
            pm_asprintf(noColormapReasonP, "pixel is already only 1 bit");
        else {
            /* We'll have to count the colors ('colors') to know if a
               palette is possible and desirable.  Along the way, we'll
               compute the actual set of colors (chv) too, and then create
               the palette itself if we decide we want one.
            */
            colorhist_vector chv;
            unsigned int colors;
            
            getChv(ifP, rasterPos, cols, rows, maxval, format, MAXCOLORS, 
                   &chv, &colors);

            if (chv == NULL) {
                pm_asprintf(noColormapReasonP, 
                            "More than %u colors found -- too many for a "
                            "colormapped PNG", MAXCOLORS);
            } else {
                /* There are few enough colors that a palette is possible */
                if (bitsPerPixel <= paletteIndexBits(colors) && !pfP)
                    pm_asprintf(noColormapReasonP, 
                                "palette index for %u colors would be "
                                "no smaller than the indexed value (%u bits)", 
                                colors, bitsPerPixel);
                else {
                    unsigned int paletteSize;
                    unsigned int transSize;
                    if (alpha)
                        tryAlphaPalette(ifP, cols, rows, maxval, format,
                                        rasterPos, alpha_mask, alphaMaxval,
                                        pfP,
                                        palette_pnm, &paletteSize, 
                                        trans_pnm, &transSize,
                                        noColormapReasonP);

                    else {
                        *noColormapReasonP = NULL;

                        compute_nonalpha_palette(chv, colors, maxval, pfP,
                                                 palette_pnm, &paletteSize, 
                                                 trans_pnm, &transSize);
    
                        if (transparent)
                            makeOneColorTransparentInPalette(
                                transcolor, transexact, 
                                palette_pnm, paletteSize, trans_pnm, 
                                &transSize);
                    }
                    if (!*noColormapReasonP) {
                        if (background)
                            findOrAddBackgroundInPalette(
                                backcolor, palette_pnm, &paletteSize,
                                backgroundIndexP);
                        *paletteSizeP = paletteSize;
                        *transSizeP   = transSize;
                    }
                }
            }
            freeChv();
        }
    }
}



static void computeColorMapLookupTable(
    bool                   const colorMapped,
    pixel                        palette_pnm[],
    unsigned int           const palette_size,
    gray                         trans_pnm[],
    unsigned int           const trans_size,
    bool                   const alpha,
    xelval                 const alpha_maxval,
    colorhash_table *      const chtP,
    coloralphahash_table * const cahtP) {
/*----------------------------------------------------------------------------
   Compute applicable lookup tables for the palette index.  If there's no
   alpha mask, this is just a standard Netpbm colorhash_table.  If there's
   an alpha mask, it is the slower Pnmtopng-specific 
   coloralphahash_table.

   If a lookup table is not applicable to the image, return NULL as
   its address.  (If the image is not colormapped, both will be NULL).
-----------------------------------------------------------------------------*/
    if (colorMapped) {
        if (alpha) {
            buildColorAlphaLookup(palette_pnm, palette_size, 
                                  trans_pnm, trans_size, alpha_maxval, cahtP);
            *chtP = NULL;
        } else { 
            buildColorLookup(palette_pnm, palette_size, chtP);
            *cahtP = NULL;
        }
        if (verbose)
            pm_message("PNG palette has %u entries, %u of them non-opaque",
                       palette_size, trans_size);
    } else {
        *chtP = NULL;
        *cahtP = NULL;
    }
}



static void
computeRasterWidth(bool           const colorMapped,
                   unsigned int   const paletteSize,
                   bool           const colorPng,
                   unsigned int   const pnmMeaningfulBitCt,
                   bool           const alpha,
                   unsigned int * const bitsPerSampleP,
                   unsigned int * const bitsPerPixelP) {
/*----------------------------------------------------------------------------
   Compute the number of bits per raster sample and per raster pixel:
   *bitsPerSampleP and *bitsPerPixelP.  Note that a raster element may be a
   palette index, or a gray value or color with or without alpha mask.
-----------------------------------------------------------------------------*/
    if (colorMapped) {
        /* The raster element is a palette index */
        if (paletteSize <= 2)
            *bitsPerSampleP = 1;
        else if (paletteSize <= 4)
            *bitsPerSampleP = 2;
        else if (paletteSize <= 16)
            *bitsPerSampleP = 4;
        else
            *bitsPerSampleP = 8;
        *bitsPerPixelP = *bitsPerSampleP;
        if (verbose)
            pm_message("Writing %u-bit color indexes", *bitsPerSampleP);
    } else {
        /* The raster element is an explicit pixel -- color and transparency */
        computePixelWidth(colorPng, pnmMeaningfulBitCt, alpha,
                          bitsPerSampleP, bitsPerPixelP);

        if (verbose)
            pm_message("Writing %u bits per component per pixel", 
                       *bitsPerSampleP);
    }
}


static void
createPngPalette(pixel              palette_pnm[], 
                 unsigned int const paletteSize, 
                 pixval       const maxval,
                 gray               trans_pnm[],
                 unsigned int const transSize,
                 gray               alpha_maxval,
                 png_color          palette[],
                 png_byte           trans[]) {
/*----------------------------------------------------------------------------
   Create the data structure to be passed to the PNG compressor to represent
   the palette -- the whole palette, color + transparency.

   This is basically just a maxval conversion from the Netpbm-format
   equivalents we get as input.
-----------------------------------------------------------------------------*/
    unsigned int i;

    for (i = 0; i < paletteSize; ++i) {
        pixel p;
        PPM_DEPTH(p, palette_pnm[i], maxval, PALETTEMAXVAL);
        palette[i].red   = PPM_GETR(p);
        palette[i].green = PPM_GETG(p);
        palette[i].blue  = PPM_GETB(p);
    }

    for (i = 0; i < transSize; ++i) {
        unsigned int const newmv = PALETTEMAXVAL;
        unsigned int const oldmv = alpha_maxval;
        trans[i] = ROUNDDIV(trans_pnm[i] * newmv, oldmv);
    }
}



static void
setZlibCompression(struct pngx *          const pngxP,
                   struct zlibCompression const zlibCompression) {

    if (zlibCompression.levelSpec)
        png_set_compression_level(pngxP->png_ptr, zlibCompression.level);

    if (zlibCompression.memLevelSpec)
        png_set_compression_mem_level(pngxP->png_ptr,
                                      zlibCompression.mem_level);

    if (zlibCompression.strategySpec)
        png_set_compression_strategy(pngxP->png_ptr, zlibCompression.strategy);

    if (zlibCompression.windowBitsSpec)
        png_set_compression_window_bits(pngxP->png_ptr,
                                        zlibCompression.window_bits);

    if (zlibCompression.methodSpec)
        png_set_compression_method(pngxP->png_ptr, zlibCompression.method);

    if (zlibCompression.bufferSizeSpec) {
        pngx_setCompressionSize(pngxP, zlibCompression.buffer_size);
    }
}
                  


static void
makePngLine(png_byte *           const line,
            const xel *          const xelrow,
            unsigned int         const cols,
            xelval               const maxval,
            bool                 const alpha,
            gray *               const alpha_mask,
            colorhash_table      const cht,
            coloralphahash_table const caht,
            struct pngx *        const pngxP,
            xelval               const png_maxval,
            unsigned int         const depth) {
            
    unsigned int col;
    png_byte *pp;

    pp = line;  /* start at beginning of line */
    for (col = 0; col < cols; ++col) {
        xel p_png;
        xel const p = xelrow[col];
        PPM_DEPTH(p_png, p, maxval, png_maxval);
        if (pngx_colorType(pngxP) == PNG_COLOR_TYPE_GRAY ||
            pngx_colorType(pngxP) == PNG_COLOR_TYPE_GRAY_ALPHA) {
            if (depth == 16)
                *pp++ = PNM_GET1(p_png) >> 8;
            *pp++ = PNM_GET1(p_png) & 0xff;
        } else if (pngx_colorType(pngxP) == PNG_COLOR_TYPE_PALETTE) {
            unsigned int paletteIndex;
            if (alpha)
                paletteIndex = lookupColorAlpha(caht, &p, &alpha_mask[col]);
            else
                paletteIndex = ppm_lookupcolor(cht, &p);
            *pp++ = paletteIndex;
        } else if (pngx_colorType(pngxP) == PNG_COLOR_TYPE_RGB ||
                   pngx_colorType(pngxP) == PNG_COLOR_TYPE_RGB_ALPHA) {
            if (depth == 16)
                *pp++ = PPM_GETR(p_png) >> 8;
            *pp++ = PPM_GETR(p_png) & 0xff;
            if (depth == 16)
                *pp++ = PPM_GETG(p_png) >> 8;
            *pp++ = PPM_GETG(p_png) & 0xff;
            if (depth == 16)
                *pp++ = PPM_GETB(p_png) >> 8;
            *pp++ = PPM_GETB(p_png) & 0xff;
        } else
            pm_error("INTERNAL ERROR: undefined color_type");
                
        if (pngx_colorType(pngxP) & PNG_COLOR_MASK_ALPHA) {
            int const png_alphaval = (int)
                alpha_mask[col] * (float) png_maxval / maxval + 0.5;
            if (depth == 16)
                *pp++ = png_alphaval >> 8;
            *pp++ = png_alphaval & 0xff;
        }
    }
}



static void
writeRaster(struct pngx *        const pngxP,
            FILE *               const ifP,
            pm_filepos           const rasterPos,
            unsigned int         const cols,
            unsigned int         const rows,
            xelval               const maxval,
            int                  const format,
            xelval               const png_maxval,
            unsigned int         const depth,
            bool                 const alpha,
            gray **              const alpha_mask,
            colorhash_table      const cht,
            coloralphahash_table const caht
            ) {
/*----------------------------------------------------------------------------
   Write the PNG raster via compressor *pngxP, reading the PNM raster
   from file *ifP, position 'rasterPos'.

   The PNG raster consists of IDAT chunks.

   'alpha_mask' is defined only if 'alpha' is true.
-----------------------------------------------------------------------------*/
    xel * xelrow;
    png_byte * line;
    unsigned int pass;

    xelrow = pnm_allocrow(cols);

    /* max: 3 color channels, one alpha channel, 16-bit */
    MALLOCARRAY(line, cols * 8);
    if (line == NULL)
        pm_error("out of memory allocating PNG row buffer");

    for (pass = 0; pass < pngxP->numPassesRequired; ++pass) {
        unsigned int row;
        pm_seek2(ifP, &rasterPos, sizeof(rasterPos));
        for (row = 0; row < rows; ++row) {
            pnm_readpnmrow(ifP, xelrow, cols, maxval, format);
            pnm_promoteformatrow(xelrow, cols, maxval, format, maxval,
                                 PPM_TYPE);
            
            makePngLine(line, xelrow, cols, maxval,
                        alpha, alpha ? alpha_mask[row] : NULL,
                        cht, caht, pngxP, png_maxval, depth);

            pngx_writeRow(pngxP, line);
        }
    }
    pnm_freerow(xelrow);
}



static void
doHistChunk(struct pngx * const pngxP,
            bool          const histRequested,
            pixel         const palettePnm[],
            FILE *        const ifP,
            pm_filepos    const rasterPos,
            unsigned int  const cols,
            unsigned int  const rows,
            xelval        const maxval,
            int           const format,
            bool          const verbose) {

    if (histRequested) {
        colorhist_vector chv;
        unsigned int colorCt;
        colorhash_table cht;
        
        getChv(ifP, rasterPos, cols, rows, maxval, format, MAXCOLORS, 
               &chv, &colorCt);

        cht = ppm_colorhisttocolorhash(chv, colorCt);
                
        { 
            png_uint_16 * histogram;  /* malloc'ed */
        
            MALLOCARRAY(histogram, MAXCOLORS);

            if (!histogram)
                pm_error("Failed to allocate memory for %u-color histogram",
                         MAXCOLORS);
            else {
                unsigned int i;
                for (i = 0 ; i < MAXCOLORS; ++i) {
                    int const chvIndex = ppm_lookupcolor(cht, &palettePnm[i]);
                    if (chvIndex == -1)
                        histogram[i] = 0;
                    else
                        histogram[i] = chv[chvIndex].value;
                }
            
                pngx_setHist(pngxP, histogram);

                if (verbose)
                    pm_message("histogram created in PNG stream");
            }
        }
        ppm_freecolorhash(cht);
    }
}



static void
doIhdrChunk(struct pngx * const pngxP,
            unsigned int  const width,
            unsigned int  const height,
            unsigned int  const depth,
            bool          const colorMapped,
            bool          const colorPng,
            bool          const alpha,
            bool          const interlace) {

    int const interlaceMethod =
        interlace ? PNG_INTERLACE_ADAM7 : PNG_INTERLACE_NONE;

    int colorType;

    if (colorMapped)
        colorType = PNG_COLOR_TYPE_PALETTE;
    else if (colorPng)
        colorType = PNG_COLOR_TYPE_RGB;
    else
        colorType = PNG_COLOR_TYPE_GRAY;

    if (alpha && colorType != PNG_COLOR_TYPE_PALETTE)
        colorType |= PNG_COLOR_MASK_ALPHA;

    pngx_setIhdr(pngxP, width, height, depth, colorType,
                 interlaceMethod, 0, 0);
}



static void
doGamaChunk(struct cmdlineInfo const cmdline,
            struct pngx *      const pngxP) {
            
    if (cmdline.gammaSpec)
        pngx_setGama(pngxP, cmdline.gamma);
}



static void
doChrmChunk(struct cmdlineInfo const cmdline,
            struct pngx *      const pngxP) {

    if (cmdline.rgbSpec)
        pngx_setChrm(pngxP, cmdline.rgb);
}



static void
doPhysChunk(struct cmdlineInfo const cmdline,
            struct pngx *      const pngxP) {

    if (cmdline.sizeSpec)
        pngx_setPhys(pngxP, cmdline.size);
}



static void
doTimeChunk(struct cmdlineInfo const cmdline,
            struct pngx *      const pngxP) {

    if (cmdline.modtimeSpec)
        pngx_setTime(pngxP, cmdline.modtime);
}



static void
reportFilterSet(int const filterSet) {

    pm_message("Limiting filter to: %s%s%s%s%s",
               (filterSet & PNG_FILTER_NONE)  ? "NONE "  : "",
               (filterSet & PNG_FILTER_SUB)   ? "SUB "   : "",
               (filterSet & PNG_FILTER_UP)    ? "UP "    : "",
               (filterSet & PNG_FILTER_AVG)   ? "AVG "   : "",
               (filterSet & PNG_FILTER_PAETH) ? "PAETH " : "");
}



static void
doFilters(struct cmdlineInfo const cmdline,
          struct pngx *      const pngxP) {

    if (cmdline.filterSetSpec) {
        if (verbose)
            reportFilterSet(cmdline.filterSet);
        pngx_setFilter(pngxP, cmdline.filterSet);
    }
}



static void
reportTrans(struct pngx * const pngxP) {

    if (pngx_chunkIsPresent(pngxP, PNG_INFO_tRNS)) {
        struct pngx_trns const transInfo = pngx_trns(pngxP);

        pm_message("%u transparency values", transInfo.numTrans);
        
        pm_message("Transparent color {gray, red, green, blue} = "
                   "{%d, %d, %d, %d}",
                   transInfo.transColor.gray,
                   transInfo.transColor.red,
                   transInfo.transColor.green,
                   transInfo.transColor.blue);
    } else
        pm_message("No transparent color");
}


static void
doTrnsChunk(struct pngx * const pngxP,
            png_byte      const transPalette[],
            unsigned int  const transPaletteSize,
            int           const transparent,
            pixel         const transColor,
            xelval        const maxval,
            xelval        const pngMaxval) {

    switch (pngx_colorType(pngxP)) {
    case PNG_COLOR_TYPE_PALETTE:
        if (transPaletteSize > 0)
            pngx_setTrnsPalette(pngxP, transPalette,
                                transPaletteSize /* omit opaque values */);
        break;
    case PNG_COLOR_TYPE_GRAY:
    case PNG_COLOR_TYPE_RGB:
        if (transparent > 0)
            pngx_setTrnsValue(pngxP,
                              xelToPngColor_16(transColor, maxval, pngMaxval));
        break;
    default:
        /* This is PNG_COLOR_MASK_ALPHA.  Transparency will be handled
           by the alpha channel, not a transparency color.
        */
    {}
    }
    if (verbose)
        reportTrans(pngxP);
}



static void
doBkgdChunk(struct pngx * const pngxP,
            bool          const bkgdRequested,
            unsigned int  const backgroundIndex,
            pixel         const backColor,
            xelval        const maxval,
            xelval        const pngMaxval,
            bool          const verbose) {
    
    if (bkgdRequested) {
        if (pngx_colorType(pngxP) == PNG_COLOR_TYPE_PALETTE)
            pngx_setBkgdPalette(pngxP, backgroundIndex);
        else {
            png_color_16 const pngBackground = 
                xelToPngColor_16(backColor, maxval, pngMaxval);
            pngx_setBkgdRgb(pngxP, pngBackground);
            if (verbose)
                pm_message("Writing bKGD chunk with background color "
                           " {gray, red, green, blue} = {%d, %d, %d, %d}",
                           pngBackground.gray, 
                           pngBackground.red, 
                           pngBackground.green, 
                           pngBackground.blue ); 
        }
    }
}



static void
doSbitChunk(struct pngx * const pngxP,
            xelval        const pngMaxval,
            xelval        const maxval,
            bool          const alpha,
            xelval        const alphaMaxval) {

    if (pngx_colorType(pngxP) != PNG_COLOR_TYPE_PALETTE &&
        (pngMaxval > maxval || (alpha && pngMaxval > alphaMaxval))) {

        /* We're writing in a bit depth that doesn't match the maxval
           of the input image and the alpha mask.  So we write an sBIT
           chunk to tell what the original image's maxval was.  The
           sBit chunk doesn't let us specify any maxval -- only powers
           of two minus one.  So we pick the power of two minus one
           which is greater than or equal to the actual input maxval.
           
           PNG also doesn't let an sBIT chunk indicate a maxval
           _greater_ than the the PNG maxval.  The designers probably
           did not conceive of the case where that would happen.  The
           case is this: We detected redundancy in the bits so were
           able to store fewer bits than the user provided.  But since
           PNG doesn't allow it, we don't attempt to create such an
           sBIT chunk.
        */

        {
            int const sbitval = pm_maxvaltobits(MIN(maxval, pngMaxval));

            png_color_8 sbit;

            if (pngx_colorType(pngxP) & PNG_COLOR_MASK_COLOR) {
                sbit.red   = sbitval;
                sbit.green = sbitval;
                sbit.blue  = sbitval;
            } else
                sbit.gray  = sbitval;
            
            if (verbose)
                pm_message("Writing sBIT chunk with bits = %d", sbitval);

            if (pngx_colorType(pngxP) & PNG_COLOR_MASK_ALPHA) {
                sbit.alpha = pm_maxvaltobits(MIN(alphaMaxval, pngMaxval));
                if (verbose)
                    pm_message("  alpha bits = %d", sbit.alpha);
            }

            pngx_setSbit(pngxP, sbit);
        }
    }
}



static void
addSrgbChunk(struct pngx *   const pngxP,
             pngx_srgbIntent const srgbIntent) {

    pngx_setSrgb(pngxP, srgbIntent);

    if (verbose) {
        pm_message("writing sRGB chunk with intent value %s",
                   pngx_srgbIntentDesc(srgbIntent));
    }
}



static void 
convertpnm(struct cmdlineInfo const cmdline,
           FILE *             const ifP,
           FILE *             const ofP,
           FILE *             const afP,
           FILE *             const pfP,
           FILE *             const tfP,
           int *              const errorLevelP
    ) {
/*----------------------------------------------------------------------------
   Design note:  It's is really a modularity violation that we have
   all the command line parameters as an argument.  We do it because we're
   lazy -- it takes a great deal of work to carry all that information as
   separate arguments -- and it's only a very small violation.
-----------------------------------------------------------------------------*/
    int rows, cols, format;
    xelval maxval;
    /* The maxval of the input image */
    xelval pngMaxval;
        /* The maxval of the samples in the PNG output 
           (must be 1, 3, 7, 15, 255, or 65535)
        */
    pixel transcolor;
        /* The color that is to be transparent, with maxval equal to that
           of the input image.
        */
    bool transExact;  
        /* boolean: the user wants only the exact color he specified to be
           transparent; not just something close to it.
        */
    int transparent;
    bool alpha;
        /* There will be an alpha mask */
    unsigned int pnmMeaningfulBitCt;
    pixel backColor;
        /* The background color, with maxval equal to that of the input
           image.
        */
    jmp_buf jmpbuf;
    struct pngx * pngxP;

    bool colorMapped;
    pixel palettePnm[MAXCOLORS];
    png_color palette[MAXCOLORS];
        /* The color part of the color/alpha palette passed to the PNG
           compressor 
        */
    unsigned int paletteSize;

    gray transPnm[MAXCOLORS];
    png_byte  trans[MAXCOLORS];
        /* The alpha part of the color/alpha palette passed to the PNG
           compressor 
        */
    unsigned int transSize;

    colorhash_table cht;
    coloralphahash_table caht;

    unsigned int backgroundIndex;
        /* Index into palette[] of the background color. */

    gray alphaMaxval;
    const char * noColormapReason;
        /* The reason that we shouldn't make a colormapped PNG, or NULL if
           we should.  malloc'ed null-terminated string.
        */
    unsigned int depth;
        /* The number of bits per sample in the (uncompressed) png 
           raster -- if the raster contains palette indices, this is the
           number of bits in the index.
        */
    unsigned int fulldepth;
        /* The total number of bits per pixel in the (uncompressed) png
           raster, including all channels.
        */
    pm_filepos rasterPos;  
        /* file position in input image file of start of image (i.e. after
           the header)
        */
    xel * xelrow;    /* malloc'ed */
        /* The row of the input image currently being processed */

    gray ** alpha_mask;

    bool colorPng;
        /* The PNG shall be of the color (RGB) variety */

    /* We initialize these guys to quiet compiler warnings: */
    depth = 0;

    errorlevel = 0;

    if (setjmp(jmpbuf))
        pm_error ("setjmp returns error condition");

    pngx_create(&pngxP, PNGX_WRITE, &jmpbuf);

    pnm_readpnminit(ifP, &cols, &rows, &maxval, &format);
    pm_tell2(ifP, &rasterPos, sizeof(rasterPos));

    xelrow = pnm_allocrow(cols);

    if (verbose)
        reportInputType(format, maxval);

    determineTransparency(cmdline, ifP, rasterPos, cols, rows, maxval, format,
                          afP,
                          &alpha, &transparent, &transcolor, &transExact,
                          &alpha_mask, &alphaMaxval);

    determineBackground(cmdline, maxval, &backColor);

    if (cmdline.force)
        colorPng = (PNM_FORMAT_TYPE(format) == PPM_TYPE);
    else {
        if (PNM_FORMAT_TYPE(format) == PPM_TYPE) {
            colorPng = hasColor(ifP, cols, rows, maxval, format, rasterPos); 
        } else
            colorPng = false;
    }


    /* handle `odd' maxvalues */

    if (maxval > 65535 && !cmdline.downscale) {
        pm_error("can only handle files up to 16-bit "
                 "(use -downscale to override");
    }

    findRedundantBits(ifP, rasterPos, cols, rows, maxval, format, alpha,
                      cmdline.force, &pnmMeaningfulBitCt);
  
    computeColorMap(ifP, rasterPos, cols, rows, maxval, colorPng, format,
                    cmdline.force, pfP,
                    alpha, transparent >= 0, transcolor, transExact, 
                    !!cmdline.background, backColor,
                    alpha_mask, alphaMaxval, pnmMeaningfulBitCt,
                    palettePnm, &paletteSize, transPnm, &transSize,
                    &backgroundIndex, &noColormapReason);

    if (noColormapReason) {
        if (pfP)
            pm_error("You specified a particular palette, but this image "
                     "cannot be represented by any palette.  %s",
                     noColormapReason);
        if (verbose)
            pm_message("Not using color map.  %s", noColormapReason);
        pm_strfree(noColormapReason);
        colorMapped = FALSE;
    } else
        colorMapped = TRUE;
  
    computeColorMapLookupTable(colorMapped, palettePnm, paletteSize,
                               transPnm, transSize, alpha, alphaMaxval,
                               &cht, &caht);

    computeRasterWidth(colorMapped, paletteSize, colorPng,
                       pnmMeaningfulBitCt, alpha,
                       &depth, &fulldepth);
    if (verbose)
        pm_message ("writing a%s %d-bit %s%s file%s",
                    fulldepth == 8 ? "n" : "", fulldepth,
                    colorMapped ? "palette": 
                    colorPng ? "RGB" : "gray",
                    alpha ? (colorMapped ? "+transparency" : "+alpha") : "",
                    cmdline.interlace ? " (interlaced)" : "");

    /* now write the file */

    pngMaxval = pm_bitstomaxval(depth);

    if (setjmp (pnmtopng_jmpbuf_struct.jmpbuf)) {
        pm_error ("setjmp returns error condition (2)");
    }

    doIhdrChunk(pngxP, cols, rows, depth, colorMapped, colorPng, alpha,
                cmdline.interlace);

    doGamaChunk(cmdline, pngxP);

    doChrmChunk(cmdline, pngxP);

    doPhysChunk(cmdline, pngxP);

    if (pngx_colorType(pngxP) == PNG_COLOR_TYPE_PALETTE) {

        /* creating PNG palette (Not counting the transparency palette) */

        createPngPalette(palettePnm, paletteSize, maxval,
                         transPnm, transSize, alphaMaxval, 
                         palette, trans);
        pngx_setPlte(pngxP, palette, paletteSize);

        doHistChunk(pngxP, cmdline.hist, palettePnm, ifP, rasterPos,
                    cols, rows, maxval, format, cmdline.verbose);
    }

    doTrnsChunk(pngxP, trans, transSize,
                transparent, transcolor, maxval, pngMaxval);

    doBkgdChunk(pngxP, !!cmdline.background,
                backgroundIndex, backColor,
                maxval, pngMaxval, cmdline.verbose);

    doSbitChunk(pngxP, pngMaxval, maxval, alpha, alphaMaxval);

    if (cmdline.srgbintentSpec)
        addSrgbChunk(pngxP, cmdline.srgbintent);

    /* tEXT and zTXT chunks */
    if (cmdline.text || cmdline.ztxt)
        pngtxt_addChunk(pngxP, tfP, !!cmdline.ztxt, false, cmdline.verbose);

    doTimeChunk(cmdline, pngxP);

    doFilters(cmdline, pngxP);

    setZlibCompression(pngxP, cmdline.zlibCompression);

    png_init_io(pngxP->png_ptr, ofP);

    /* write the png-info struct */
    pngx_writeInfo(pngxP);

    /* let libpng take care of, e.g., bit-depth conversions */
    pngx_setPacking(pngxP);

    pngx_setInterlaceHandling(pngxP);

    writeRaster(pngxP, ifP, rasterPos,
                cols, rows, maxval, format,
                pngMaxval, depth, alpha, alpha_mask, cht, caht);

    pngx_writeEnd(pngxP);

    pngx_destroy(pngxP);

    pnm_freerow(xelrow);

    if (cht)
        ppm_freecolorhash(cht);
    if (caht)
        freecoloralphahash(caht);

    *errorLevelP = errorlevel;
}



static void
displayVersion() {

    fprintf(stderr,"Pnmtopng version %s.\n", NETPBM_VERSION);

    /* We'd like to display the version of libpng with which we're _linked_ as
       well as the one with which we're compiled, but it isn't practical.
       While libpng is capable of telling you what it's level is, different
       versions of it do it two different ways: with png_libpng_ver or with
       png_get_header_ver.  So we have to be compiled for a particular version
       just to find out what version it is! It's not worth having a link
       failure, much less a compile failure, if we choose wrong.
       png_get_header_ver is not in anything older than libpng 1.0.2a (Dec
       1998).  png_libpng_ver is not there in libraries built without
       USE_GLOBAL_ARRAYS.  Cygwin versions are normally built without
       USE_GLOBAL_ARRAYS.  -bjh 2002.06.17.

       We'd also like to display the version of libz with which we're linked,
       with zlib_version (which nowadays is a macro for zlibVersion), but we
       can't for reasons of modularity: We don't really link libz.  libpng
       does.  It's none of our business whether libz is even present.  And at
       least on Mac OS X, we can't access libz's symbols from here -- we get
       undefined reference to zlibVersion.  We would have to explicitly link
       libz just to find out its version.  The right way to do this is for a
       subroutine in libpng to give us the information.  Until 10.07.08, we
       did display zlib_version, but for years Mac OS X build was failing (and
       we erroneously thought it was a libpng-config --ldflags bug).

       We _do_ use the compile-time part of libpng (<png.h>), because it's
       part of the interface to libpng.
    */
    fprintf(stderr, "   Pnmtopng Compiled with libpng %s.\n",
            PNG_LIBPNG_VER_STRING);
    fprintf(stderr, "   Pnmtopng (not libpng) compiled with zlib %s.\n",
            ZLIB_VERSION);
    fprintf(stderr, "\n");
}



int 
main(int argc, const char * argv[]) {

    struct cmdlineInfo cmdline;
    FILE * ifP;
    FILE * afP;
    FILE * pfP;
    FILE * tfP;

    int errorlevel;
    
    pm_proginit(&argc, argv);
    
    parseCommandLine(argc, argv, &cmdline);
    
    if (cmdline.libversion) {
        displayVersion();
        return 0;
    }
    verbose = cmdline.verbose;
    
    ifP = pm_openr_seekable(cmdline.inputFileName);
    
    if (cmdline.alpha)
        afP = pm_openr(cmdline.alpha);
    else
        afP = NULL;
    
    if (cmdline.palette)
        pfP = pm_openr(cmdline.palette);
    else
        pfP = NULL;
    
    if (cmdline.text)
        tfP = pm_openr(cmdline.text);
    else if (cmdline.ztxt)
        tfP = pm_openr(cmdline.ztxt);
    else
        tfP = NULL;

    convertpnm(cmdline, ifP, stdout, afP, pfP, tfP, &errorlevel);
    
    if (afP)
        pm_close(afP);
    if (pfP)
        pm_close(pfP);
    if (tfP)
        pm_close(tfP);

    pm_close(ifP);
    pm_close(stdout);

    return errorlevel;
}



