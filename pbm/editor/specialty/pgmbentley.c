/* pgmbentley.c - read a portable graymap and smear it according to brightness
**
** Copyright (C) 1990 by Wilson Bent (whb@hoh-2.att.com)
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
#include "pgm.h"


static unsigned int const N = 4;


int
main(int argc, const char * argv[]) {

    FILE * ifP;
    int rows, cols;
    gray maxval;
    gray ** gin;
    gray ** gout;
    unsigned int row;
    const char * inputFileName;

    pm_proginit(&argc, argv);

    if (argc-1 < 1)
        inputFileName = "-";
    else {
        inputFileName = argv[1];

        if (argc-1 > 1)
            pm_error("There are no options and only one argument.  "
                     "You specified %u", argc-1);
    }
	ifP = pm_openr(inputFileName);

    gin = pgm_readpgm(ifP, &cols, &rows, &maxval);

    pm_close(ifP);

    gout = pgm_allocarray(cols, rows);

    for (row = 0; row < rows; ++row) {
        unsigned int col;
        for (col = 0; col < cols; ++col)
            gout[row][col] = 0;
    }

    for (row = 0; row < rows; ++row) {
        unsigned int col;

        for (col = 0; col < cols; ++col) {
            unsigned int const brow = MIN(rows-1, row + gin[row][col] / N);

            gout[brow][col] = gin[row][col];
	    }
    }
     
    pgm_writepgm(stdout, gout, cols, rows, maxval, 0);

    pm_close(stdout);
    pgm_freearray(gout, rows);

    return 0;
}
