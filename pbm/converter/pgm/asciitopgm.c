/* asciitopgm.c - read an ASCII graphics file and produce a PGM
**
** Copyright (C) 1989 by Wilson H. Bent, Jr
**
** - Based on fstopgm.c and other works which bear the following notice:
** Copyright (C) 1989 by Jef Poskanzer.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
*/

#include <string.h>

#include "pm_c_util.h"
#include "mallocvar.h"
#include "nstring.h"
#include "pgm.h"

static unsigned int const gmap [128] = {
/*00 nul-bel*/  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/*08 bs -si */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/*10 dle-etb*/  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/*18 can-us */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/*20 sp - ' */  0x00, 0x21, 0x1b, 0x7f, 0x70, 0x25, 0x20, 0x0a,
/*28  ( - / */  0x11, 0x11, 0x2a, 0x2b, 0x0b, 0x13, 0x04, 0x10,
/*30  0 - 7 */  0x30, 0x28, 0x32, 0x68, 0x39, 0x35, 0x39, 0x16,
/*38  8 - ? */  0x38, 0x39, 0x14, 0x15, 0x11, 0x1c, 0x11, 0x3f,
/*40  @ - G */  0x40, 0x49, 0x52, 0x18, 0x44, 0x3c, 0x38, 0x38,
/*48  H - O */  0x55, 0x28, 0x2a, 0x70, 0x16, 0x7f, 0x70, 0x14,
/*50  P - W */  0x60, 0x20, 0x62, 0x53, 0x1a, 0x55, 0x36, 0x57,
/*58  X - _ */  0x50, 0x4c, 0x5a, 0x24, 0x10, 0x24, 0x5e, 0x13,
/*60  ` - g */  0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
/*68  h - o */  0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x2a,
/*70  p - w */  0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
/*78  x -del*/  0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f,
};

static gray const maxval = 127;



static void
zeroObuf(unsigned int * const obuf,
         unsigned int   const cols) {

    unsigned int col;
    for (col = 0; col < cols; ++col)
        obuf[col] = 0;
}



static void
convertRowToPgm(const unsigned int * const obuf,
                unsigned int         const cols,
                gray                 const maxval,
                gray *               const grayrow) {

    unsigned int col;

    for (col = 0; col < cols; ++col)
        grayrow[col] = maxval - MIN(maxval, obuf[col]);
}



static bool warnedNonAscii;

static unsigned int
darknessOfChar(char const c) {

    unsigned char asciifiedC;

    if (c & 0x80) {       /* !isascii(c) */
        if (!warnedNonAscii) {
            pm_message("Warning: non-ASCII char(s) in input");
            warnedNonAscii = true;
        }
        asciifiedC = c & 0x7f;      /* toascii(c) */
    } else
        asciifiedC = c;

    return gmap[asciifiedC];
}



static void
convertAsciiToPgm(FILE *         const ifP,
                  unsigned int   const cols,
                  unsigned int   const rows,
                  unsigned int   const divisor,
                  gray           const maxval,
                  gray **        const grays,
                  unsigned int * const obuf) {

    unsigned int outRow;
    unsigned int outCursor;
    bool beginningOfImage;
    bool beginningOfLine;
    bool warnedTrunc;
    bool eof;

    zeroObuf(obuf, cols);

    warnedNonAscii = false;
    warnedTrunc = false;
    outRow = 0;
    outCursor = 0;
    beginningOfImage = true;
    beginningOfLine = true;
    eof = false;
    while (outRow < rows && !eof) {
        int c;

        c = getc(ifP);

        if (c == EOF)
            eof = true;
        else {
            if (beginningOfLine) {
                if (c == '+') {
                    /* + at start of line means rest of line 
                       overstrikes previous
                    */
                    c = getc(ifP);
                    if (c == EOF)
                        eof = true;
                } else {
                    if (!beginningOfImage) {
                        /* Output previous line, move to next */

                        convertRowToPgm(obuf, cols, maxval, grays[outRow]);

                        zeroObuf(obuf, cols);

                        ++outRow;
                    }
                }
                outCursor = 0;
                beginningOfLine = false;
            }
            if (!eof) {
                if (c == '\n')
                    beginningOfLine = true;
                else {
                    if (outRow < rows && outCursor < cols)
                        obuf[outCursor++] += darknessOfChar(c) / divisor;
                    else {
                        if (!warnedTrunc) {
                            pm_message("Warning: "
                                       "truncating image to %u columns "
                                       "x %u rows", cols, rows);
                            warnedTrunc = true;
                        }
                    }
                }
            }
        }
        beginningOfImage = false;
    }
    while (outRow < rows) {
        /* Output previous line, move to next */

        convertRowToPgm(obuf, cols, maxval, grays[outRow]);

        zeroObuf(obuf, cols);

        ++outRow;
    }
}



int
main(int argc, const char ** argv) {

    FILE * ifP;
    gray ** grays;
    int argn;
    unsigned int rows, cols;
    unsigned int divisor;
    unsigned int * obuf;  /* malloced */
    const char * const usage = "[-d <val>] height width [asciifile]";

    pm_proginit(&argc, argv);

    rows = 0;  /* initial value */
    cols = 0;  /* initial value */
    divisor = 1; /* initial value */
    
    argn = 1;

    if ( argc < 3 || argc > 6 )
        pm_usage( usage );

    if ( argv[argn][0] == '-' )
    {
        if ( streq( argv[argn], "-d" ) )
        {
            if ( argc == argn + 1 )
                pm_usage( usage );
            if ( sscanf( argv[argn+1], "%u", &divisor ) != 1 )
                pm_usage( usage );
            argn += 2;
        }
        else
            pm_usage( usage );
    }

    if ( sscanf( argv[argn++], "%u", &rows ) != 1 )
        pm_usage( usage );
    if ( sscanf( argv[argn++], "%u", &cols ) != 1 )
        pm_usage( usage );
    if ( rows < 1 )
        pm_error( "height is less than 1" );
    if ( cols < 1 )
        pm_error( "width is less than 1" );

    if ( argc > argn + 1 )
        pm_usage( usage );

    if ( argc == argn + 1 )
        ifP = pm_openr(argv[argn]);
    else
        ifP = stdin;

    MALLOCARRAY(obuf, cols);
    if (obuf == NULL)
        pm_error("Unable to allocate memory for %u columns", cols);

    grays = pgm_allocarray(cols, rows);

    convertAsciiToPgm(ifP, cols, rows, divisor, maxval, grays, obuf);

    pm_close(ifP);

    pgm_writepgm(stdout, grays, cols, rows, maxval, 0);

    free(obuf);
    pgm_freearray(grays, rows);

    return 0;
}
