/* pbmtoascii.c - read a PBM image and produce ASCII graphics
**
** Copyright (C) 1988, 1992 by Jef Poskanzer.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
*/

#include <assert.h>
#include "mallocvar.h"
#include "pbm.h"

/*
  The algorithm is based on describing the 2 or 8 pixels in a cell with a
  single integer called a signature, which we use as an index into an array to
  get the character whose glyph best matches those pixels.  The encoding is as
  follows.  Make a string of bits, with each bit being one pixel of the cell,
  1 = black, 0 = white.  The order of the string is left to right across the
  top row, then the next row down, etc.  Considering that string to be a
  binary cipher, the integer it represents is the signature.

  Example: the 2x4 cell consists of these pixels: (* = black)

      * *
      *

        *
  The bit string to represent this is 11100001.  So the signature for this
  cell is the integer 0xE1 (225).

  You index the array carr2x4 with 0xE1, and get '?' as the character to
  represent that cell.  (We don't really try very hard to match the shape;
  it's mostly important to match the density).
*/

#define SQQ '\''
#define BSQ '\\'

/* Bit-map for 1x2 mode:
**     1
**     2
*/
static char const carr1x2[4] = {
/*   0    1    2    3   */
    ' ', '"', 'o', 'M' };

/* Bit-map for 2x4 mode (hex):
**     1  2
**     4  8
**     10 20
**     40 80
** The idea here is first to preserve geometry, then to show density.
*/
#define D08 'M'
#define D07 'H'
#define D06 '&'
#define D05 '$'
#define D04 '?'
static char const carr2x4[256] = {
/*0  1    2   3    4   5    6   7    8   9    A   B    C   D    E   F  */
' ',SQQ, '`','"', '-',SQQ, SQQ,SQQ, '-','`', '`','`', '-','^','^','"',/*00-0F*/
'.',':', ':',':', '|','|', '/',D04, '/','>', '/','>', '~','+','/','*',/*10-1F*/
'.',':', ':',':', BSQ,BSQ, '<','<', '|',BSQ, '|',D04, '~',BSQ,'+','*',/*20-2F*/
'-',':', ':',':', '~',D04, '<','<', '~','>', D04,'>', '=','b','d','#',/*30-3F*/
'.',':', ':',':', ':','!', '/',D04, ':',':', '/',D04, ':',D04,D04,'P',/*40-4F*/
',','i', '/',D04, '|','|', '|','T', '/',D04, '/','7', 'r','}','/','P',/*50-5F*/
',',':', ';',D04, '>',D04, 'S','S', '/',')', '|','7', '>',D05,D05,D06,/*60-6F*/
'v',D04, D04,D05, '+','}', D05,'F', '/',D05, '/',D06, 'p','D',D06,D07,/*70-7F*/
'.',':', ':',':', ':',BSQ, ':',D04, ':',BSQ, '!',D04, ':',D04,D04,D05,/*80-8F*/
BSQ,BSQ, ':',D04, BSQ,'|', '(',D05, '<','%', D04,'Z', '<',D05,D05,D06,/*90-9F*/
',',BSQ, 'i',D04, BSQ,BSQ, D04,BSQ, '|','|', '|','T', D04,BSQ,'4','9',/*A0-AF*/
'v',D04, D04,D05, BSQ,BSQ, D05,D06, '+',D05, '{',D06, 'q',D06,D06,D07,/*B0-BF*/
'_',':', ':',D04, ':',D04, D04,D05, ':',D04, D04,D05, ':',D05,D05,D06,/*C0-CF*/
BSQ,D04, D04,D05, D04,'L', D05,'[', '<','Z', '/','Z', 'c','k',D06,'R',/*D0-DF*/
',',D04, D04,D05, '>',BSQ, 'S','S', D04,D05, 'J',']', '>',D06,'1','9',/*E0-EF*/
'o','b', 'd',D06, 'b','b', D06,'6', 'd',D06, 'd',D07, '#',D07,D07,D08 /*F0-FF*/
};



static void
makeRowOfSigs(FILE *         const ifP,
              unsigned int   const cols,
              unsigned int   const rows,
              int            const format,
              unsigned int   const cellWidth,
              unsigned int   const cellHeight,
              unsigned int   const row,
              unsigned int * const sig,
              unsigned int   const ccols) {
/*----------------------------------------------------------------------------
   Compute the signatures for every cell in a row.

   Read the pixels from *ifP, which is positioned to the first pixel row
   of the cell row, which is row number 'row'.  The image dimensions are
   'cols' x 'rows' pixels.

   Each cell is 'cellWidth' x 'cellHeight'.

   Return the signatures as sig[], which is 'ccols' wide because that's how
   many cells you get from 'cols' pixels divided into cells 'cellWidth' pixels
   wide.
-----------------------------------------------------------------------------*/
    unsigned int b;
    unsigned int subrow;  /* row within cell */
    bit * bitrow;        /* malloc'ed array */

    bitrow = pbm_allocrow(cols);
    {
        unsigned int col;
        for (col = 0; col < ccols; ++col)
            sig[col] = 0;
    }

    b = 0x1;  /* initial value */
    for (subrow = 0; subrow < cellHeight; ++subrow) {
        if (row + subrow < rows) {
            unsigned int subcol;  /* col within cell */
            pbm_readpbmrow(ifP, bitrow, cols, format);
            for (subcol = 0; subcol < cellWidth; ++subcol) {
                unsigned int col, ccol;
                for (col = subcol, ccol = 0;
                     col < cols;
                     col += cellWidth, ++ccol) {
                    if (bitrow[col] == PBM_BLACK)
                        sig[ccol] |= b;
                }
                b <<= 1;
            }
        }
    }
    pbm_freerow(bitrow);
}



static void
findRightMargin(const unsigned int * const sig,
                unsigned int         const ccols,
                const char *         const carr,
                unsigned int *       const endColP) {
/*----------------------------------------------------------------------------
   Find the first cell of the right margin, i.e. a contiguous set of
   all-white cells at the right end of the row.
-----------------------------------------------------------------------------*/
    unsigned int endcol;

    for (endcol = ccols; endcol > 0; --endcol) {
        if (carr[sig[endcol-1]] != ' ')
            break;
    }
    *endColP = endcol;
}



static void
assembleCellRow(const unsigned int * const sig,
                unsigned int         const ccols,
                const char *         const carr,
                char *               const line) {
/*----------------------------------------------------------------------------
   Return as line[] the line of ASCII codes for the characters of one
   row of cells, ready for printing.
-----------------------------------------------------------------------------*/
    unsigned int col;

    for (col = 0; col < ccols; ++col)
        line[col] = carr[sig[col]];

    line[ccols] = '\0';
}



static void
pbmtoascii(FILE *       const ifP,
           unsigned int const cellWidth,
           unsigned int const cellHeight,
           const char * const carr) {

    int cols, rows, format;
    unsigned int ccols;
    char * line;         /* malloc'ed array */
    unsigned int row;
    unsigned int * sig;  /* malloc'ed array */
        /* This describes in a single integer the pixels of a cell,
           as described above.
        */
    assert(cellWidth * cellHeight <= sizeof(sig[0])*8);

    pbm_readpbminit(ifP, &cols, &rows, &format);

    ccols = (cols + cellWidth - 1) / cellWidth;

    MALLOCARRAY(sig, ccols);
    if (sig == NULL)
        pm_error("No memory for %u columns", ccols);
    MALLOCARRAY_NOFAIL(line, ccols+1);
    if (line == NULL)
        pm_error("No memory for %u columns", ccols);

    for (row = 0; row < rows; row += cellHeight) {
        unsigned int endCol;

        makeRowOfSigs(ifP, cols, rows, format, cellWidth, cellHeight,
                      row, sig, ccols);

        findRightMargin(sig, ccols, carr, &endCol);

        assembleCellRow(sig, endCol, carr, line);

        puts(line);
    }
    free(sig);
    free(line);
}



int
main(int argc, const char ** argv) {

    FILE * ifP;
    int argn, gridx, gridy;
    const char * carr;
    const char* usage = "[-1x2|-2x4] [pbmfile]";

    pm_proginit(&argc, argv);

    /* Set up default parameters. */
    argn = 1;
    gridx = 1;
    gridy = 2;
    carr = carr1x2;

    /* Check for flags. */
    while ( argn < argc && argv[argn][0] == '-' && argv[argn][1] != '\0' )
    {
        if ( pm_keymatch( argv[argn], "-1x2", 2 ) )
        {
            gridx = 1;
            gridy = 2;
            carr = carr1x2;
        }
        else if ( pm_keymatch( argv[argn], "-2x4", 2 ) )
        {
            gridx = 2;
            gridy = 4;
            carr = carr2x4;
        }
        else
            pm_usage( usage );
        ++argn;
    }

    if ( argn < argc )
    {
        ifP = pm_openr( argv[argn] );
        ++argn;
    }
    else
        ifP = stdin;
    
    if ( argn != argc )
        pm_usage( usage );

    pbmtoascii(ifP, gridx, gridy, carr);

    pm_close(ifP);

    return 0;
}
