/* rawtoppm.c - convert raw RGB bytes into a portable pixmap
**
** Copyright (C) 1991 by Jef Poskanzer.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
*/

#include <math.h>
#include "ppm.h"

enum order { ORD_RGB, ORD_RBG, ORD_GRB, ORD_GBR, ORD_BRG, ORD_BGR };

enum interleave { INT_PIX, INT_ROW };

static void
dorowskip(FILE * const ifP,
          int    const rowskip) {

    unsigned int i;

    for (i = 0; i < rowskip; ++i) {
        int const val = getc(ifP);
        if (val == EOF)
            pm_error("EOF / read error");
    }
}



static void
doRowPixInterleave(pixel *      const pixrow,
                   unsigned int const cols,
                   FILE *       const ifP,
                   enum order   const order,
                   int          const rowskip) {

    unsigned int col;

    for (col = 0; col < cols; ++col) {
        int const val1 = getc(ifP);
        int const val2 = getc(ifP);
        int const val3 = getc(ifP);

        if (val1 == EOF)
            pm_error("EOF / read error");
        if (val2 == EOF)
            pm_error("EOF / read error");
        if (val3 == EOF)
            pm_error("EOF / read error");

        switch (order) {
        case ORD_RGB:
            PPM_ASSIGN(pixrow[col], val1, val2, val3);
            break;
        case ORD_RBG:
            PPM_ASSIGN(pixrow[col], val1, val3, val2);
            break;
        case ORD_GRB:
            PPM_ASSIGN(pixrow[col], val2, val1, val3);
            break;
        case ORD_GBR:
            PPM_ASSIGN(pixrow[col], val3, val1, val2);
            break;
        case ORD_BRG:
            PPM_ASSIGN(pixrow[col], val2, val3, val1);
            break;
        case ORD_BGR:
            PPM_ASSIGN(pixrow[col], val3, val2, val1);
            break;
        }
    }
    dorowskip(ifP, rowskip);
}



static void
doRowRowInterleave(pixel *      const pixrow,
                   unsigned int const cols,
                   FILE *       const ifP,
                   enum order   const order,
                   int          const rowskip,
                   pixval *     const grow1,
                   pixval *     const grow2,
                   pixval *     const grow3) {

    unsigned int col;

    for (col = 0; col < cols; ++col) {
        int const val1 = getc(ifP);
        if (val1 == EOF)
            pm_error("EOF / read error");
        grow1[col] = val1;
    }
    dorowskip(ifP, rowskip);
    for (col = 0; col < cols; ++col) {
        int const val2 = getc(ifP);
        if (val2 == EOF)
            pm_error( "EOF / read error" );
        grow2[col] = val2;
    }
    dorowskip(ifP, rowskip);
    for (col = 0; col < cols; ++col) {
        int const val3 = getc(ifP);
        if (val3 == EOF)
            pm_error( "EOF / read error" );
        grow3[col] = val3;
    }
    dorowskip(ifP, rowskip);

    for (col = 0; col < cols; ++col) {
        switch (order) {
        case ORD_RGB:
            PPM_ASSIGN(pixrow[col], grow1[col], grow2[col], grow3[col]);
            break;
        case ORD_RBG:
            PPM_ASSIGN(pixrow[col], grow1[col], grow3[col], grow2[col]);
            break;
        case ORD_GRB:
            PPM_ASSIGN(pixrow[col], grow2[col], grow1[col], grow3[col]);
            break;
        case ORD_GBR:
            PPM_ASSIGN(pixrow[col], grow3[col], grow1[col], grow2[col]);
            break;
        case ORD_BRG:
            PPM_ASSIGN(pixrow[col], grow2[col], grow3[col], grow1[col]);
            break;
        case ORD_BGR:
            PPM_ASSIGN(pixrow[col], grow3[col], grow2[col], grow1[col]);
            break;
        }
    }
}



int
main(int argc, const char * argv[]) {

    pixval const maxval = 255;

    FILE * ifP;
    pixel * pixrow;
    int argn, headerskip, rowskip, rows, cols, row, i;
    enum order order;
    enum interleave interleave;
    gray * grow1;
    gray * grow2;
    gray * grow3;
    const char* const usage = "[-headerskip N] [-rowskip N] [-rgb|-rbg|-grb|-gbr|-brg|-bgr] [-interpixel|-interrow] <width> <height> [rawfile]";

    pm_proginit(&argc, argv);

    argn = 1;
    headerskip = 0;
    rowskip = 0;
    order = ORD_RGB;
    interleave = INT_PIX;

    while ( argn < argc && argv[argn][0] == '-' && argv[argn][1] != '\0' )
        {
        if ( pm_keymatch( argv[argn], "-headerskip", 2 ) )
            {
            ++argn;
            if ( argn >= argc )
                pm_usage( usage );
            headerskip = atoi( argv[argn] );
            }
        else if ( pm_keymatch( argv[argn], "-rowskip", 3 ) )
            {
            ++argn;
            if ( argn >= argc )
                pm_usage( usage );
            rowskip = atoi( argv[argn] );
            }
        else if ( pm_keymatch( argv[argn], "-rgb", 3 ) )
            order = ORD_RGB;
        else if ( pm_keymatch( argv[argn], "-rbg", 3 ) )
            order = ORD_RBG;
        else if ( pm_keymatch( argv[argn], "-grb", 3 ) )
            order = ORD_GRB;
        else if ( pm_keymatch( argv[argn], "-gbr", 3 ) )
            order = ORD_GBR;
        else if ( pm_keymatch( argv[argn], "-brg", 3 ) )
            order = ORD_BRG;
        else if ( pm_keymatch( argv[argn], "-bgr", 3 ) )
            order = ORD_BGR;
        else if ( pm_keymatch( argv[argn], "-interpixel", 7 ) )
            interleave = INT_PIX;
        else if ( pm_keymatch( argv[argn], "-interrow", 7 ) )
            interleave = INT_ROW;
        else
            pm_usage( usage );
        ++argn;
        }

    if ( argn + 2 > argc )
        pm_usage( usage );
    
    cols = pm_parse_width(argv[argn++]);
    rows = pm_parse_height(argv[argn++]);

    if ( argn < argc )
        {
        ifP = pm_openr( argv[argn] );
        ++argn;
        }
    else
        ifP = stdin;

    if ( argn != argc )
        pm_usage( usage );

    ppm_writeppminit(stdout, cols, rows, (pixval) 255, 0);
    pixrow = ppm_allocrow(cols);

    if (interleave == INT_ROW) {
        grow1 = pgm_allocrow(cols);
        grow2 = pgm_allocrow(cols);
        grow3 = pgm_allocrow(cols);
    }

    for (i = 0; i < headerskip; ++i) {
        int const val = getc(ifP);
        if (val == EOF)
            pm_error("EOF / read error");
    }

    for (row = 0; row < rows; ++row) {
        switch (interleave) {
        case INT_PIX:
            doRowPixInterleave(pixrow, cols, ifP, order, rowskip);
            break;

        case INT_ROW:
            doRowRowInterleave(pixrow, cols, ifP, order, rowskip,
                               grow1, grow2, grow3);
            break;
        }
        ppm_writeppmrow(stdout, pixrow, cols, maxval, 0);
    }

    pm_close( ifP );
    pm_close( stdout );

    exit( 0 );
    }
