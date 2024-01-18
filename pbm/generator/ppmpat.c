/* ppmpat.c - make a pixmap
**
** Copyright (C) 1989, 1991 by Jef Poskanzer.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
*/

#define _XOPEN_SOURCE  /* get M_PI in math.h */

#include <assert.h>
#include <math.h>
#include <limits.h>

#include "pm_c_util.h"
#include "mallocvar.h"
#include "shhopt.h"
#include "ppm.h"
#include "ppmdraw.h"


typedef enum {
    PAT_GINGHAM2,
    PAT_GINGHAM3,
    PAT_MADRAS,
    PAT_TARTAN,
    PAT_POLES,
    PAT_SQUIG,
    PAT_CAMO,
    PAT_ANTICAMO
} pattern;

struct cmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    pattern basePattern;
    unsigned int width;
    unsigned int height;
    unsigned int randomseed;
    unsigned int randomseedSpec;
};



static void
parseCommandLine(int argc, const char ** argv,
                 struct cmdlineInfo * const cmdlineP) {
/*----------------------------------------------------------------------------
   Note that the file spec array we return is stored in the storage that
   was passed to us as the argv array.
-----------------------------------------------------------------------------*/
    optEntry * option_def;
        /* Instructions to OptParseOptions3 on how to parse our options.
         */
    optStruct3 opt;

    unsigned int option_def_index;
    unsigned int basePatternCount;
    unsigned int gingham2;
    unsigned int gingham3;
    unsigned int madras;
    unsigned int tartan;
    unsigned int poles;
    unsigned int squig;
    unsigned int camo;
    unsigned int anticamo;

    MALLOCARRAY_NOFAIL(option_def, 100);

    option_def_index = 0;   /* incremented by OPTENTRY */
    OPTENT3(0, "gingham2",      OPT_FLAG,   NULL,
            &gingham2,   0);
    OPTENT3(0, "g2",            OPT_FLAG,   NULL,
            &gingham2,   0);
    OPTENT3(0, "gingham3",      OPT_FLAG,   NULL,
            &gingham3,   0);
    OPTENT3(0, "g3",            OPT_FLAG,   NULL,
            &gingham3,   0);
    OPTENT3(0, "madras",        OPT_FLAG,   NULL,
            &madras,     0);
    OPTENT3(0, "tartan",        OPT_FLAG,   NULL,
            &tartan,     0);
    OPTENT3(0, "poles",         OPT_FLAG,   NULL,
            &poles,      0);
    OPTENT3(0, "squig",         OPT_FLAG,   NULL,
            &squig,      0);
    OPTENT3(0, "camo",          OPT_FLAG,   NULL,
            &camo,       0);
    OPTENT3(0, "anticamo",      OPT_FLAG,   NULL,
            &anticamo,   0);
    OPTENT3(0, "randomseed",    OPT_UINT,   &cmdlineP->randomseed,
            &cmdlineP->randomseedSpec,      0);

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = FALSE;  /* We have no parms that are negative numbers */

    pm_optParseOptions3(&argc, (char **)argv, opt, sizeof(opt), 0);
        /* Uses and sets argc, argv, and some of *cmdlineP and others. */

    basePatternCount =
        gingham2 +
        gingham3 +
        madras +
        tartan +
        poles +
        squig +
        camo +
        anticamo;

    if (basePatternCount < 1)
        pm_error("You must specify a base pattern option such as -gingham2");
    else if (basePatternCount > 1)
        pm_error("You may not specify more than one base pattern option.  "
                 "You specified %u", basePatternCount);
    else {
        if (gingham2)
            cmdlineP->basePattern = PAT_GINGHAM2;
        else if (gingham3)
            cmdlineP->basePattern = PAT_GINGHAM3;
        else if (madras)
            cmdlineP->basePattern = PAT_MADRAS;
        else if (tartan)
            cmdlineP->basePattern = PAT_TARTAN;
        else if (poles)
            cmdlineP->basePattern = PAT_POLES;
        else if (squig)
            cmdlineP->basePattern = PAT_SQUIG;
        else if (camo)
            cmdlineP->basePattern = PAT_CAMO;
        else if (anticamo)
            cmdlineP->basePattern = PAT_ANTICAMO;
        else
            assert(false);  /* Every possibility is accounted for */
    }
    if (argc-1 != 2)
        pm_error("You must specify 2 non-option arguments: width and height "
                 "in pixels.  You specified %u", argc-1);
    else {
        cmdlineP->width  = atoi(argv[1]);
        cmdlineP->height = atoi(argv[2]);

        if (cmdlineP->width < 1)
            pm_error("Width must be at least 1 pixel");
        if (cmdlineP->height < 1)
            pm_error("Height must be at least 1 pixel");
    }
    free(option_def);
}



static void
validateComputableDimensions(unsigned int const cols,
                             unsigned int const rows) {

    /*
      Notes on width and height limits:

      cols * 3, rows * 3 appear in madras, tartan
      cols*rows appears in poles
      cols+rows appears in squig

      PPMD functions use signed integers for pixel positions
      (because they allow you to specify points off the canvas).
    */
      
    if (cols > INT_MAX/4 || rows > INT_MAX/4 || rows > INT_MAX/cols)
        pm_error("Width and/or height are way too large: %u x %u",
                 cols, rows);
}



static pixel
randomColor(pixval const maxval) {

    pixel p;

    PPM_ASSIGN(p,
               rand() % (maxval + 1),
               rand() % (maxval + 1),
               rand() % (maxval + 1)
        );
    
    return p;
}



#define DARK_THRESH 0.25

static pixel
randomBrightColor(pixval const maxval) {

    pixel p;

    do {
        p = randomColor(maxval);
    } while (PPM_LUMIN(p) <= maxval * DARK_THRESH);

    return p;
}



static pixel
randomDarkColor(pixval const maxval) {

    pixel p;

    do {
        p = randomColor(maxval);
    } while (PPM_LUMIN(p) > maxval * DARK_THRESH);

    return p;
}



static pixel
averageTwoColors(pixel const p1,
                 pixel const p2) {

    pixel p;

    PPM_ASSIGN(p,
               (PPM_GETR(p1) + PPM_GETR(p2)) / 2,
               (PPM_GETG(p1) + PPM_GETG(p2)) / 2,
               (PPM_GETB(p1) + PPM_GETB(p2)) / 2);

    return p;
}



static ppmd_drawproc average_drawproc;

static void
average_drawproc(pixel **     const pixels, 
                 int          const cols, 
                 int          const rows, 
                 pixval       const maxval, 
                 int          const col, 
                 int          const row, 
                 const void * const clientdata) {

    if (col >= 0 && col < cols && row >= 0 && row < rows)
        pixels[row][col] =
            averageTwoColors(pixels[row][col], *((const pixel*) clientdata));
}



/*----------------------------------------------------------------------------
   Camouflage stuff
-----------------------------------------------------------------------------*/



static pixel
randomAnticamoColor(pixval const maxval) {

    int v1, v2, v3;
    pixel p;

    v1 = (maxval + 1) / 4;
    v2 = (maxval + 1) / 2;
    v3 = 3 * v1;

    switch (rand() % 15) {
    case 0: case 1:
        PPM_ASSIGN(p, rand() % v1 + v3, rand() % v2, rand() % v2);
        break;

    case 2:
    case 3:
        PPM_ASSIGN(p, rand() % v2, rand() % v1 + v3, rand() % v2);
        break;
        
    case 4:
    case 5:
        PPM_ASSIGN(p, rand() % v2, rand() % v2, rand() % v1 + v3);
        break;

    case 6:
    case 7:
    case 8:
        PPM_ASSIGN(p, rand() % v2, rand() % v1 + v3, rand() % v1 + v3);
        break;

    case 9:
    case 10:
    case 11:
        PPM_ASSIGN(p, rand() % v1 + v3, rand() % v2, rand() % v1 + v3);
        break;

    case 12:
    case 13:
    case 14:
        PPM_ASSIGN(p, rand() % v1 + v3, rand() % v1 + v3, rand() % v2);
        break;
    }
    
    return p;
}



static pixel
randomCamoColor(pixval const maxval) {

    int const v1 = (maxval + 1 ) / 8;
    int const v2 = (maxval + 1 ) / 4;
    int const v3 = (maxval + 1 ) / 2;

    pixel p;

    switch (rand() % 10) {
    case 0:
    case 1:
    case 2:
        /* light brown */
        PPM_ASSIGN(p, rand() % v3 + v3, rand() % v3 + v2, rand() % v3 + v2);
        break;

    case 3:
    case 4:
    case 5:
        /* dark green */
        PPM_ASSIGN(p, rand() % v2, rand() % v2 + 3 * v1, rand() % v2);
        break;
    
    case 6:
    case 7:
        /* brown */
        PPM_ASSIGN(p, rand() % v2 + v2, rand() % v2, rand() % v2);
        break;

    case 8:
    case 9:
        /* dark brown */
        PPM_ASSIGN(p, rand() % v1 + v1, rand() % v1, rand() % v1);
        break;
    }

    return p;
}



static float
rnduni(void) {
    return rand() % 32767 / 32767.0;
}



static void
clearBackground(pixel **     const pixels,
                unsigned int const cols,
                unsigned int const rows,
                pixval       const maxval,
                bool         const antiflag) {

    pixel color;

    if (antiflag)
        color = randomAnticamoColor(maxval);
    else
        color = randomCamoColor(maxval);

    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 0, 0, cols, rows, PPMD_NULLDRAWPROC,
        &color);
}


static void
camoFill(pixel **         const pixels,
         unsigned int     const cols,
         unsigned int     const rows,
         pixval           const maxval,
         struct fillobj * const fh,
         bool             const antiflag) {
         
    pixel color;

    if (antiflag)
        color = randomAnticamoColor(maxval);
    else
        color = randomCamoColor(maxval);

    ppmd_fill(pixels, cols, rows, maxval, fh, PPMD_NULLDRAWPROC, &color);
}        



#define BLOBRAD 50

#define MIN_POINTS 7
#define MAX_POINTS 13

#define MIN_ELLIPSE_FACTOR 0.5
#define MAX_ELLIPSE_FACTOR 2.0

#define MIN_POINT_FACTOR 0.5
#define MAX_POINT_FACTOR 2.0



static void
computeXsYs(int *        const xs,
            int *        const ys,
            unsigned int const cols,
            unsigned int const rows,
            unsigned int const pointCt) {

    unsigned int const cx = rand() % cols;
    unsigned int const cy = rand() % rows;
    double const a = rnduni() * (MAX_ELLIPSE_FACTOR - MIN_ELLIPSE_FACTOR) +
        MIN_ELLIPSE_FACTOR;
    double const b = rnduni() * (MAX_ELLIPSE_FACTOR - MIN_ELLIPSE_FACTOR) +
        MIN_ELLIPSE_FACTOR;
    double const theta = rnduni() * 2.0 * M_PI;
    
    unsigned int p;
        
    for (p = 0; p < pointCt; ++p) {
        double const c = rnduni() * (MAX_POINT_FACTOR - MIN_POINT_FACTOR) +
            MIN_POINT_FACTOR;
        double const tx   = a * sin(p * 2.0 * M_PI / pointCt);
        double const ty   = b * cos(p * 2.0 * M_PI / pointCt);
        double const tang = atan2(ty, tx) + theta;
        xs[p] = MAX(0, MIN(cols-1, cx + BLOBRAD * c * sin(tang)));
        ys[p] = MAX(0, MIN(rows-1, cy + BLOBRAD * c * cos(tang)));
    }
}



static void
camo(pixel **     const pixels,
     unsigned int const cols,
     unsigned int const rows,
     pixval       const maxval,
     bool         const antiflag) {

    unsigned int const n = (rows * cols) / (BLOBRAD * BLOBRAD) * 5;

    unsigned int i;

    clearBackground(pixels, cols, rows, maxval, antiflag);

    for (i = 0; i < n; ++i) {
        unsigned int const pointCt =
            rand() % (MAX_POINTS - MIN_POINTS + 1) + MIN_POINTS;

        int xs[MAX_POINTS], ys[MAX_POINTS];
        int x0, y0;
        struct fillobj * fh;

        computeXsYs(xs, ys, cols, rows, pointCt);

        x0 = (xs[0] + xs[pointCt - 1]) / 2;
        y0 = (ys[0] + ys[pointCt - 1]) / 2;

        fh = ppmd_fill_create();

        ppmd_polyspline(
            pixels, cols, rows, maxval, x0, y0, pointCt, xs, ys, x0, y0,
            ppmd_fill_drawproc, fh);
        
        camoFill(pixels, cols, rows, maxval, fh, antiflag);
        
        ppmd_fill_destroy(fh);
    }
}



/*----------------------------------------------------------------------------
   Gingham stuff
-----------------------------------------------------------------------------*/



static void
gingham2(pixel **     const pixels,
         unsigned int const cols,
         unsigned int const rows,
         pixval       const maxval) {

    pixel const backcolor = randomDarkColor(maxval);
    pixel const forecolor = randomBrightColor(maxval);
    unsigned int const colso2 = cols / 2;
    unsigned int const rowso2 = rows / 2;

    /* Warp. */
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 0, 0, colso2, rows, PPMD_NULLDRAWPROC,
        &backcolor);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, colso2, 0, cols - colso2, rows,
        PPMD_NULLDRAWPROC, &forecolor);

    /* Woof. */
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 0, 0, cols, rowso2, average_drawproc,
        &backcolor);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 0, rowso2, cols, rows - rowso2,
        average_drawproc, &forecolor);
}



static void
gingham3(pixel **     const pixels,
         unsigned int const cols,
         unsigned int const rows,
         pixval       const maxval) {

    unsigned int const colso4 = cols / 4;
    unsigned int const rowso4 = rows / 4;

    pixel const backcolor  = randomDarkColor(maxval);
    pixel const fore1color = randomBrightColor(maxval);
    pixel const fore2color = randomBrightColor(maxval);

    /* Warp. */
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 0, 0, colso4, rows, PPMD_NULLDRAWPROC,
        &backcolor);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, colso4, 0, colso4, rows, PPMD_NULLDRAWPROC,
        &fore1color);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 2 * colso4, 0, colso4, rows,
        PPMD_NULLDRAWPROC, &fore2color);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 3 * colso4, 0, cols - colso4, rows,
        PPMD_NULLDRAWPROC, &fore1color);

    /* Woof. */
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 0, 0, cols, rowso4, average_drawproc,
        &backcolor);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 0, rowso4, cols, rowso4, average_drawproc,
        &fore1color);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 0, 2 * rowso4, cols, rowso4,
        average_drawproc, &fore2color);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 0, 3 * rowso4, cols, rows - rowso4,
        average_drawproc, &fore1color);
}



static void
madras(pixel **     const pixels,
       unsigned int const cols,
       unsigned int const rows,
       pixval       const maxval) {

    unsigned int const cols2  = cols * 2 / 44;
    unsigned int const rows2  = rows * 2 / 44;
    unsigned int const cols3  = cols * 3 / 44;
    unsigned int const rows3  = rows * 3 / 44;
    unsigned int const cols12 = cols - 10 * cols2 - 4 * cols3;
    unsigned int const rows12 = rows - 10 * rows2 - 4 * rows3;
    unsigned int const cols6a = cols12 / 2;
    unsigned int const rows6a = rows12 / 2;
    unsigned int const cols6b = cols12 - cols6a;
    unsigned int const rows6b = rows12 - rows6a;
    pixel const backcolor  = randomDarkColor(maxval);
    pixel const fore1color = randomBrightColor(maxval);
    pixel const fore2color = randomBrightColor(maxval);

    /* Warp. */
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 0, 0, cols2, rows, PPMD_NULLDRAWPROC,
        &backcolor);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, cols2, 0, cols3, rows, PPMD_NULLDRAWPROC,
        &fore1color);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, cols2 + cols3, 0, cols2, rows,
        PPMD_NULLDRAWPROC, &backcolor);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 2 * cols2 + cols3, 0, cols2, rows,
        PPMD_NULLDRAWPROC, &fore2color);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 3 * cols2 + cols3, 0, cols2, rows,
        PPMD_NULLDRAWPROC, &backcolor);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 4 * cols2 + cols3, 0, cols6a, rows,
        PPMD_NULLDRAWPROC, &fore1color);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 4 * cols2 + cols3 + cols6a, 0, cols2, rows,
        PPMD_NULLDRAWPROC, &backcolor);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 5 * cols2 + cols3 + cols6a, 0, cols3, rows,
        PPMD_NULLDRAWPROC, &fore2color);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 5 * cols2 + 2 * cols3 + cols6a, 0, cols2,
        rows, PPMD_NULLDRAWPROC, &backcolor);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 6 * cols2 + 2 * cols3 + cols6a, 0, cols3,
        rows, PPMD_NULLDRAWPROC, &fore2color);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 6 * cols2 + 3 * cols3 + cols6a, 0, cols2,
        rows, PPMD_NULLDRAWPROC, &backcolor);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 7 * cols2 + 3 * cols3 + cols6a, 0, cols6b,
        rows, PPMD_NULLDRAWPROC, &fore1color);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 7 * cols2 + 3 * cols3 + cols6a + cols6b, 0,
        cols2, rows, PPMD_NULLDRAWPROC, &backcolor);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 8 * cols2 + 3 * cols3 + cols6a + cols6b, 0,
        cols2, rows, PPMD_NULLDRAWPROC, &fore2color);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 9 * cols2 + 3 * cols3 + cols6a + cols6b, 0,
        cols2, rows, PPMD_NULLDRAWPROC, &backcolor);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 10 * cols2 + 3 * cols3 + cols6a + cols6b, 
        0, cols3, rows, PPMD_NULLDRAWPROC, &fore1color);

    /* Woof. */
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 0, 0, cols, rows2, average_drawproc,
        &backcolor);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 0, rows2, cols, rows3, average_drawproc,
        &fore2color);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 0, rows2 + rows3, cols, rows2,
        average_drawproc, &backcolor);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 0, 2 * rows2 + rows3, cols, rows2,
        average_drawproc, &fore1color);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 0, 3 * rows2 + rows3, cols, rows2,
        average_drawproc, &backcolor);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 0, 4 * rows2 + rows3, cols, rows6a,
        average_drawproc, &fore2color);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 0, 4 * rows2 + rows3 + rows6a, cols, rows2,
        average_drawproc, &backcolor);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 0, 5 * rows2 + rows3 + rows6a, cols, rows3,
        average_drawproc, &fore1color);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 0, 5 * rows2 + 2 * rows3 + rows6a, cols,
        rows2, average_drawproc, &backcolor);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 0, 6 * rows2 + 2 * rows3 + rows6a, cols,
        rows3, average_drawproc, &fore1color);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 0, 6 * rows2 + 3 * rows3 + rows6a, cols,
        rows2, average_drawproc, &backcolor);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 0, 7 * rows2 + 3 * rows3 + rows6a, cols,
        rows6b, average_drawproc, &fore2color);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 0, 7 * rows2 + 3 * rows3 + rows6a + rows6b,
        cols, rows2, average_drawproc, &backcolor);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 0, 8 * rows2 + 3 * rows3 + rows6a + rows6b,
        cols, rows2, average_drawproc, &fore1color);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 0, 9 * rows2 + 3 * rows3 + rows6a + rows6b,
        cols, rows2, average_drawproc, &backcolor);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 0, 
        10 * rows2 + 3 * rows3 + rows6a + rows6b,
        cols, rows3, average_drawproc, &fore2color);
}



static void
tartan(pixel **     const pixels,
       unsigned int const cols,
       unsigned int const rows,
       pixval       const maxval) {

    unsigned int const cols1  = cols / 22;
    unsigned int const rows1  = rows / 22;
    unsigned int const cols3  = cols * 3 / 22;
    unsigned int const rows3  = rows * 3 / 22;
    unsigned int const cols10 = cols - 3 * cols1 - 3 * cols3;
    unsigned int const rows10 = rows - 3 * rows1 - 3 * rows3;
    unsigned int const cols5a = cols10 / 2;
    unsigned int const rows5a = rows10 / 2;
    unsigned int const cols5b = cols10 - cols5a;
    unsigned int const rows5b = rows10 - rows5a;
    pixel const backcolor  = randomDarkColor(maxval);
    pixel const fore1color = randomBrightColor(maxval);
    pixel const fore2color = randomBrightColor(maxval);

    /* Warp. */
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 0, 0, cols5a, rows, PPMD_NULLDRAWPROC,
        &backcolor);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, cols5a, 0, cols1, rows, PPMD_NULLDRAWPROC,
        &fore1color);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, cols5a + cols1, 0, cols5b, rows,
        PPMD_NULLDRAWPROC, &backcolor );
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, cols10 + cols1, 0, cols3, rows,
        PPMD_NULLDRAWPROC, &fore2color);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, cols10 + cols1 + cols3, 0, cols1, rows,
        PPMD_NULLDRAWPROC, &backcolor);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, cols10 + 2 * cols1 + cols3, 0, cols3, rows,
        PPMD_NULLDRAWPROC, &fore2color);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, cols10 + 2 * cols1 + 2 * cols3, 0, cols1,
        rows, PPMD_NULLDRAWPROC, &backcolor);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, cols10 + 3 * cols1 + 2 * cols3, 0, cols3,
        rows, PPMD_NULLDRAWPROC, &fore2color);

    /* Woof. */
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 0, 0, cols, rows5a, average_drawproc,
        &backcolor);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 0, rows5a, cols, rows1, average_drawproc,
        &fore1color);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 0, rows5a + rows1, cols, rows5b,
        average_drawproc, &backcolor);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 0, rows10 + rows1, cols, rows3,
        average_drawproc, &fore2color);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 0, rows10 + rows1 + rows3, cols, rows1,
        average_drawproc, &backcolor);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 0, rows10 + 2 * rows1 + rows3, cols, rows3,
        average_drawproc, &fore2color);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 0, rows10 + 2 * rows1 + 2 * rows3, cols,
        rows1, average_drawproc, &backcolor);
    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 0, rows10 + 3 * rows1 + 2 * rows3, cols,
        rows3, average_drawproc, &fore2color);
}



/*----------------------------------------------------------------------------
   Poles stuff
-----------------------------------------------------------------------------*/



#define MAXPOLES 500



static void
placeAndColorPolesRandomly(int *        const xs,
                           int *        const ys,
                           pixel *      const colors,
                           unsigned int const cols,
                           unsigned int const rows,
                           pixval       const maxval,
                           unsigned int const poleCt) {

    unsigned int i;

    for (i = 0; i < poleCt; ++i) {
        xs[i] = rand() % cols;
        ys[i] = rand() % rows;
        colors[i] = randomBrightColor(maxval);
    }
}



static void
assignInterpolatedColor(pixel * const resultP,
                        pixel   const color1,
                        double  const dist1,
                        pixel   const color2,
                        double  const dist2) {
    
    if (dist1 == 0) 
        /* pixel is a pole */
        *resultP = color1;
    else {
        double const sum = dist1 + dist2;

        pixval const r = (PPM_GETR(color1)*dist2 + PPM_GETR(color2)*dist1)/sum;
        pixval const g = (PPM_GETG(color1)*dist2 + PPM_GETG(color2)*dist1)/sum;
        pixval const b = (PPM_GETB(color1)*dist2 + PPM_GETB(color2)*dist1)/sum;
        
        PPM_ASSIGN(*resultP, r, g, b);
    }
}



static void
poles(pixel **     const pixels,
      unsigned int const cols,
      unsigned int const rows,
      pixval       const maxval) {

    unsigned int const poleCt = MAX(2, MIN(MAXPOLES, cols * rows / 30000));
    
    int xs[MAXPOLES], ys[MAXPOLES];
    pixel colors[MAXPOLES];
    unsigned int row;

    placeAndColorPolesRandomly(xs, ys, colors, cols, rows, maxval, poleCt);

    /* Interpolate points */

    for (row = 0; row < rows; ++row) {
        unsigned int col;
        for (col = 0; col < cols; ++col) {
            double dist1, dist2;
            pixel color1, color2;
            unsigned int i;

            /* Find two closest poles. */
            dist1 = dist2 = (SQR((double)cols) + SQR((double)rows));
            for (i = 0; i < poleCt; ++i) {
                double const newdist =
                    (double)((int)col - xs[i]) * ((int)col - xs[i]) +
                    (double)((int)row - ys[i]) * ((int)row - ys[i]);
                if (newdist < dist1) {
                    dist2  = dist1;
                    color2 = color1;
                    dist1  = newdist;
                    color1 = colors[i];
                } else if (newdist < dist2) {
                    dist2  = newdist;
                    color2 = colors[i];
                }
            }
            assignInterpolatedColor(&pixels[row][col],
                                    color1, dist1, color2, dist2);
        }
    }
}



/*----------------------------------------------------------------------------
   Squig stuff
-----------------------------------------------------------------------------*/

#define SQUIGS 5
#define SQ_POINTS 7
#define SQ_MAXCIRCLE_POINTS 5000

static int sq_circlecount;
static pixel sq_colors[SQ_MAXCIRCLE_POINTS];
static ppmd_point sq_offs[SQ_MAXCIRCLE_POINTS];



static void
validateSquigAspect(unsigned int const cols,
                    unsigned int const rows) {

    if (cols / rows >= 25 || rows / cols >= 25)
        pm_error("Image too narrow.  Aspect ratio: %u/%u=%f "
                 "is outside accepted range: 0.04 - 25.0",
                 cols, rows, (float)cols/rows ); 

}



static ppmd_point
vectorSum(ppmd_point const a,
          ppmd_point const b) {

    return ppmd_makePoint(a.x + b.x, a.y + b.y);
}



static ppmd_drawprocp sqMeasureCircleDrawproc;

static void
sqMeasureCircleDrawproc(pixel**      const pixels, 
                        unsigned int const cols, 
                        unsigned int const rows, 
                        pixval       const maxval, 
                        ppmd_point   const p,
                        const void * const clientdata) {

    sq_offs[sq_circlecount++] = p;
}



static ppmd_drawprocp sqRainbowCircleDrawproc;

static void
sqRainbowCircleDrawproc(pixel **     const pixels, 
                        unsigned int const cols, 
                        unsigned int const rows, 
                        pixval       const maxval, 
                        ppmd_point   const p,
                        const void * const clientdata) {

    unsigned int i;

    for (i = 0; i < sq_circlecount; ++i)
        ppmd_point_drawprocp(
            pixels, cols, rows, maxval, vectorSum(p, sq_offs[i]),
            &sq_colors[i]);
}



static void
sqAssignColors(unsigned int const circlecount,
               pixval       const maxval,
               pixel *      const colors) {

    pixel const rc1 = randomBrightColor(maxval);
    pixel const rc2 = randomBrightColor(maxval);
    pixel const rc3 = randomBrightColor(maxval);
    float const cco3 = (circlecount - 1) / 3.0;

    unsigned int i;

    for (i = 0; i < circlecount ; ++i) {
        if (i < cco3) {
            float const frac = (float)i/cco3;
            PPM_ASSIGN(colors[i],
                       (float) PPM_GETR(rc1) +
                       ((float) PPM_GETR(rc2) - (float) PPM_GETR(rc1)) * frac,
                       (float) PPM_GETG(rc1) +
                       ((float) PPM_GETG(rc2) - (float) PPM_GETG(rc1)) * frac,
                       (float) PPM_GETB(rc1) +
                       ((float) PPM_GETB(rc2) - (float) PPM_GETB(rc1)) * frac
                );
        } else if (i < 2.0 * cco3) {
            float const frac = (float)i/cco3 - 1.0;
            PPM_ASSIGN(colors[i],
                       (float) PPM_GETR(rc2) +
                       ((float) PPM_GETR(rc3) - (float) PPM_GETR(rc2)) * frac,
                       (float) PPM_GETG(rc2) +
                       ((float) PPM_GETG(rc3) - (float) PPM_GETG(rc2)) * frac,
                       (float) PPM_GETB(rc2) +
                       ((float) PPM_GETB(rc3) - (float) PPM_GETB(rc2)) * frac
                       );
        } else {
            float const frac = (float)i/cco3 - 2.0;
            PPM_ASSIGN(colors[i],
                       (float) PPM_GETR(rc3) +
                       ((float) PPM_GETR(rc1) - (float) PPM_GETR(rc3)) * frac,
                       (float) PPM_GETG(rc3) +
                       ((float) PPM_GETG(rc1) - (float) PPM_GETG(rc3)) * frac,
                       (float) PPM_GETB(rc3) +
                       ((float) PPM_GETB(rc1) - (float) PPM_GETB(rc3)) * frac
                );
        }
    }
}



static void
clearImageToBlack(pixel **     const pixels,
                  unsigned int const cols,
                  unsigned int const rows,
                  pixval       const maxval) {

    pixel color;

    PPM_ASSIGN(color, 0, 0, 0);

    ppmd_filledrectangle(
        pixels, cols, rows, maxval, 0, 0, cols, rows, PPMD_NULLDRAWPROC,
        &color);
}



static void
chooseWrapAroundPoint(unsigned int const cols,
                      unsigned int const rows,
                      ppmd_point * const pFirstP,
                      ppmd_point * const pLastP,
                      ppmd_point * const p0P,
                      ppmd_point * const p1P,
                      ppmd_point * const p2P,
                      ppmd_point * const p3P) {
                      
    switch (rand() % 4) {
    case 0:
        p1P->x = rand() % cols;
        p1P->y = 0;
        if (p1P->x < cols / 2)
            pFirstP->x = rand() % (p1P->x * 2 + 1);
        else
            pFirstP->x = cols - 1 - rand() % ((cols - p1P->x) * 2);
        pFirstP->y = rand() % rows;
        p2P->x = p1P->x;
        p2P->y = rows - 1;
        pLastP->x = 2 * p2P->x - pFirstP->x;
        pLastP->y = p2P->y - pFirstP->y;
        p0P->x = pLastP->x;
        p0P->y = pLastP->y - rows;
        p3P->x = pFirstP->x;
        p3P->y = pFirstP->y + rows;
        break;

    case 1:
        p2P->x = rand() % cols;
        p2P->y = 0;
        if (p2P->x < cols / 2)
            pLastP->x = rand() % (p2P->x * 2 + 1);
        else
            pLastP->x = cols - 1 - rand() % ((cols - p2P->x) * 2);
        pLastP->y = rand() % rows;
        p1P->x = p2P->x;
        p1P->y = rows - 1;
        pFirstP->x = 2 * p1P->x - pLastP->x;
        pFirstP->y = p1P->y - pLastP->y;
        p0P->x = pLastP->x;
        p0P->y = pLastP->y + rows;
        p3P->x = pFirstP->x;
        p3P->y = pFirstP->y - rows;
        break;

    case 2:
        p1P->x = 0;
        p1P->y = rand() % rows;
        pFirstP->x = rand() % cols;
        if (p1P->y < rows / 2)
            pFirstP->y = rand() % (p1P->y * 2 + 1);
        else
            pFirstP->y = rows - 1 - rand() % ((rows - p1P->y) * 2);
        p2P->x = cols - 1;
        p2P->y = p1P->y;
        pLastP->x = p2P->x - pFirstP->x;
        pLastP->y = 2 * p2P->y - pFirstP->y;
        p0P->x = pLastP->x - cols;
        p0P->y = pLastP->y;
        p3P->x = pFirstP->x + cols;
        p3P->y = pFirstP->y;
        break;

    case 3:
        p2P->x = 0;
        p2P->y = rand() % rows;
        pLastP->x = rand() % cols;
        if (p2P->y < rows / 2)
            pLastP->y = rand() % (p2P->y * 2 + 1);
        else
            pLastP->y = rows - 1 - rand() % ((rows - p2P->y) * 2);
        p1P->x = cols - 1;
        p1P->y = p2P->y;
        pFirstP->x = p1P->x - pLastP->x;
        pFirstP->y = 2 * p1P->y - pLastP->y;
        p0P->x = pLastP->x + cols;
        p0P->y = pLastP->y;
        p3P->x = pFirstP->x - cols;
        p3P->y = pFirstP->y;
        break;
    }
}



static void
squig(pixel **     const pixels,
      unsigned int const cols,
      unsigned int const rows,
      pixval       const maxval) {

    int i;

    validateSquigAspect(cols, rows);
    
    clearImageToBlack(pixels, cols, rows, maxval);

    /* Draw the squigs. */
    ppmd_setlinetype(PPMD_LINETYPE_NODIAGS);
    ppmd_setlineclip(0);
    for (i = SQUIGS; i > 0; --i) {
        unsigned int const radius = (cols + rows) / 2 / (25 + i * 2);

        ppmd_point c[SQ_POINTS];
        ppmd_point p0, p1, p2, p3;
        sq_circlecount = 0;
        ppmd_circlep(pixels, cols, rows, maxval,
                     ppmd_makePoint(0, 0), radius,
                     sqMeasureCircleDrawproc, NULL);
        sqAssignColors(sq_circlecount, maxval, sq_colors);

        chooseWrapAroundPoint(cols, rows, &c[0], &c[SQ_POINTS-1],
                              &p0, &p1, &p2, &p3);

        {
            /* Do the middle points */
            unsigned int j;

            for (j = 1; j < SQ_POINTS - 1; ++j) {
              /* validateSquigAspect() assures that
                 cols - 2 * radius, rows -2 * radius are positive
              */
                c[j].x = (rand() % (cols - 2 * radius)) + radius;
                c[j].y = (rand() % (rows - 2 * radius)) + radius;
            }
        }

        ppmd_linep(
            pixels, cols, rows, maxval, p0, p1,
            sqRainbowCircleDrawproc, NULL);
        ppmd_polysplinep(
            pixels, cols, rows, maxval, p1, SQ_POINTS, c, p2,
            sqRainbowCircleDrawproc, NULL);
        ppmd_linep(
            pixels, cols, rows, maxval, p2, p3,
            sqRainbowCircleDrawproc, NULL);
    }
}



int
main(int argc, const char ** argv) {

    struct cmdlineInfo cmdline;
    pixel ** pixels;

    pm_proginit(&argc, argv);
    
    parseCommandLine(argc, argv, &cmdline);

    validateComputableDimensions(cmdline.width, cmdline.height);
    
    srand(cmdline.randomseedSpec ? cmdline.randomseed : pm_randseed());

    pixels = ppm_allocarray(cmdline.width, cmdline.height);

    switch (cmdline.basePattern) {
    case PAT_GINGHAM2:
        gingham2(pixels, cmdline.width, cmdline.height, PPM_MAXMAXVAL);
        break;

    case PAT_GINGHAM3:
        gingham3(pixels, cmdline.width, cmdline.height, PPM_MAXMAXVAL);
        break;

    case PAT_MADRAS:
        madras(pixels, cmdline.width, cmdline.height, PPM_MAXMAXVAL);
        break;

    case PAT_TARTAN:
        tartan(pixels, cmdline.width, cmdline.height, PPM_MAXMAXVAL);
        break;

    case PAT_POLES:
        poles(pixels, cmdline.width, cmdline.height, PPM_MAXMAXVAL);
        break;

    case PAT_SQUIG:
        squig(pixels, cmdline.width, cmdline.height, PPM_MAXMAXVAL);
        break;

    case PAT_CAMO:
        camo(pixels, cmdline.width, cmdline.height, PPM_MAXMAXVAL, 0);
        break;

    case PAT_ANTICAMO:
        camo(pixels, cmdline.width, cmdline.height, PPM_MAXMAXVAL, 1);
        break;

    default:
        pm_error("can't happen!");
    }

    ppm_writeppm(stdout, pixels, cmdline.width, cmdline.height,
                 PPM_MAXMAXVAL, 0);

    ppm_freearray(pixels, cmdline.height);

    return 0;
}



