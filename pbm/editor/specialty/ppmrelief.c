/* ppmrelief.c - generate a relief map of a PPM image
**
** Copyright (C) 1990 by Wilson H. Bent, Jr.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
*/

#include <stdio.h>

#include "pm_c_util.h"
#include "ppm.h"



static pixval
clip(int    const p,
     pixval const maxval) {

    return MAX(0, MIN(maxval, p));
}



int
main(int argc, const char * argv[]) {

    FILE * ifP;
    pixel ** inputbuf;
    pixel * outputrow;
    int argn, format, rows, cols;
    unsigned int row, col;
    pixval maxval;
    const char* const usage = "[ppmfile]";

    pm_proginit(&argc, argv);

    argn = 1;

    if ( argn != argc ) {
        ifP = pm_openr( argv[argn] );
        ++argn;
    } else
        ifP = stdin;

    if ( argn != argc )
        pm_usage( usage );

    ppm_readppminit(ifP, &cols, &rows, &maxval, &format );

    if (cols < 3 || rows < 3 )
        pm_error("Input image too small: %u x %u.  Must be at least 3x3",
                  cols, rows);

    /* Allocate space for 3 input rows, plus an output row. */
    inputbuf  = ppm_allocarray(cols, 3);
    outputrow = ppm_allocrow(cols);

    ppm_writeppminit(stdout, cols, rows, maxval, 0);

    /* Read in the first two rows. */
    ppm_readppmrow(ifP, inputbuf[0], cols, maxval, format);
    ppm_readppmrow(ifP, inputbuf[1], cols, maxval, format);

    /* Write out the first row, all zeros. */
    for (col = 0; col < cols; ++col)
        PPM_ASSIGN( outputrow[col], 0, 0, 0 );

    ppm_writeppmrow(stdout, outputrow, cols, maxval, 0);

    /* Now the rest of the image - read in the 3rd row of inputbuf,
       and convolve with the first row into the output buffer.
    */
    for (row = 2 ; row < rows; ++row) {
        pixval       const mv2 = maxval / 2;
        unsigned int const rowa = row % 3;
        unsigned int const rowb = (rowa + 2) % 3;

        ppm_readppmrow(ifP, inputbuf[rowa], cols, maxval, format);

        for (col = 0; col < cols - 2; ++col) {
            pixel const inputA = inputbuf[rowa][col];
            pixel const inputB = inputbuf[rowb][col + 2];
            
            pixval const r =
                clip(PPM_GETR(inputA) + (mv2 - PPM_GETR(inputB)), maxval);
            pixval const g =
                clip(PPM_GETG(inputA) + (mv2 - PPM_GETG(inputB)), maxval);
            pixval const b =
                clip(PPM_GETB(inputA) + (mv2 - PPM_GETB(inputB)), maxval);

            PPM_ASSIGN(outputrow[col + 1], r, g, b);
        }
        ppm_writeppmrow(stdout, outputrow, cols, maxval, 0);
    }

    /* And write the last row, zeros again. */
    for (col = 0; col < cols; ++col)
        PPM_ASSIGN(outputrow[col], 0, 0, 0);

    ppm_writeppmrow(stdout, outputrow, cols, maxval, 0);

    ppm_freerow(outputrow);
    ppm_freearray(inputbuf, 3);

    pm_close(ifP);
    pm_close(stdout);

    return 0;
}
