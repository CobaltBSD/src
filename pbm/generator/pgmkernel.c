/* pgmkernel.c - generate a PGM convolution kernel
**
** Creates a PGM image containing a convolution filter with max value = 255
** and minimum value > 127 that can be used as a smoothing kernel for
** pnmconvol.
**
** Copyright (C) 1992 by Alberto Accomazzi, Smithsonian Astrophysical
** Observatory.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
*/

#include <math.h>
#include "pm_c_util.h"
#include "shhopt.h"
#include "mallocvar.h"
#include "pgm.h"



struct CmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    unsigned int cols;
    unsigned int rows;
    float weight;
    gray maxval;
};



static void
parseCommandLine(int argc, const char ** argv,
                 struct CmdlineInfo * const cmdlineP) {
/*----------------------------------------------------------------------------
  Convert program invocation arguments (argc,argv) into a format the 
  program can use easily, struct cmdlineInfo.  Validate arguments along
  the way and exit program with message if invalid.

  Note that some string information we return as *cmdlineP is in the storage 
  argv[] points to.
-----------------------------------------------------------------------------*/
    optEntry *option_def;
        /* Instructions to OptParseOptions2 on how to parse our options.
         */
    optStruct3 opt;

    unsigned int weightSpec, maxvalSpec;
    unsigned int option_def_index;

    MALLOCARRAY_NOFAIL(option_def, 100);

    option_def_index = 0;   /* incremented by OPTENTRY */
    OPTENT3(0,   "weight",  OPT_FLOAT, &cmdlineP->weight, 
            &weightSpec,     0);
    OPTENT3(0,   "maxval",  OPT_UINT, &cmdlineP->maxval, 
            &maxvalSpec,     0);

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = FALSE;  /* We have no parms that are negative numbers */

    pm_optParseOptions3(&argc, (char **)argv, opt, sizeof(opt), 0);
        /* Uses and sets argc, argv, and some of *cmdlineP and others. */

    if (!weightSpec)
        cmdlineP->weight = 6.0;

    if (cmdlineP->weight < 0.0)
        pm_error("-weight cannot be negative.  You specified %f",
                 cmdlineP->weight);

    if (!maxvalSpec)
        cmdlineP->maxval = PGM_MAXMAXVAL;

    if (cmdlineP->maxval > PGM_OVERALLMAXVAL)
        pm_error("-maxval is too large: %u.  Maximum is %u",
                 cmdlineP->maxval, PGM_OVERALLMAXVAL);

    if (cmdlineP->maxval == 0)
        pm_error("-maxval cannot be zero");

    if (argc-1 < 1)
        pm_error("Need at least one argument: size of (square) kernel");
    else if (argc-1 == 1) {
        if (atoi(argv[1]) <= 0)
            pm_error("Dimension must be a positive number.  "
                     "You specified '%s'", argv[1]);
        cmdlineP->cols = atoi(argv[1]);
        cmdlineP->rows = atoi(argv[1]);
    } else if (argc-1 == 2) {
        if (atoi(argv[1]) <= 0)
            pm_error("Width must be a positive number.  "
                     "You specified '%s'", argv[1]);
        if (atoi(argv[2]) <= 0)
            pm_error("Height must be a positive number.  "
                     "You specified '%s'", argv[2]);
        cmdlineP->cols = atoi(argv[1]);
        cmdlineP->rows = atoi(argv[2]);
    } else
        pm_error("At most two arguments allowed.  "
                 "You specified %u", argc-1);
}



static double
t(double const dx2,
  double const dy2,
  double const weight) {
/*----------------------------------------------------------------------------
  The t value for a pixel that is (dx, dy) pixels away from the center of
  the kernel, where 'dx2' is SQR(dx) and 'dy2' is SQR(dy), if the distance is
  weighted by 'weight'.
-----------------------------------------------------------------------------*/

    return 1.0 / (1.0 + weight * sqrt(dx2 + dy2));
}



static double
tMaxAllKernel(unsigned int const cols,
              unsigned int const rows,
              double       const weight) {
/*----------------------------------------------------------------------------
   The maximum t value over all pixels in the kernel, if the kernel is
   'cols' by 'rows' pixels and distance is weighted by 'weight'.
-----------------------------------------------------------------------------*/

    /* It depends upon whether there is an even or odd number of rows
       and columns.  If both dimensions are odd, there is a pixel right
       at the center, and it has the greatest t value.  If both dimensions
       are even, the center of the image is in the center of a 4-pixel
       square and each of those 4 pixels has the greatest t value.  If
       one dimension is even and the other odd, the center of the kernel
       is midway between two pixels, horizontally or vertically, and one
       of those two pixels has the greatest t value.
    */

    double dxMax, dyMax;

    switch (cols % 2 + rows % 2) {
    case 0:
        dxMax = 0.5;
        dyMax = 0.5;
        break;
    case 1:
        dxMax = 0.5;
        dyMax = 0.0;
        break;
    case 2:
        dxMax = 0.0;
        dyMax = 0.0;
    }

    return t(SQR(dxMax), SQR(dyMax), weight);
}



static void
writeKernel(FILE *       const ofP,
            unsigned int const cols,
            unsigned int const rows,
            gray         const maxval,
            gray **      const halfKernel,
            unsigned int const halfRows) {

    unsigned int row;

    pgm_writepgminit(stdout, cols, rows, maxval, 0);

    for (row = 0; row < halfRows; ++row)
        pgm_writepgmrow(stdout, halfKernel[row], cols, maxval, 0);

    /* Now write out the same rows in reverse order. */

    for (; row < rows; ++row)
        pgm_writepgmrow(stdout, halfKernel[rows-1-row], cols, maxval, 0);
}



int
main(int argc, const char * argv[]) {

    struct CmdlineInfo cmdline;
    unsigned int arows;
    unsigned int arow;
    double xcenter, ycenter;
        /* row, column "number" of center of kernel */
    double tMax;
        /* The maximum t value over all pixels */
    gray ** halfKernel;
        /* The upper half of the kernel we generate.  The lower half is
           just the mirror image of this.
        */

    pm_proginit(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    xcenter = ((double) cmdline.cols - 1) / 2.0;
    ycenter = ((double) cmdline.rows - 1) / 2.0;

    tMax = tMaxAllKernel(cmdline.cols, cmdline.rows, cmdline.weight);

    /* Output matrix is symmetric vertically and horizontally. */

    arows = (cmdline.rows + 1) / 2;
        /* Half the number of rows.  Add 1 if odd. */
    halfKernel = pgm_allocarray(cmdline.cols, arows);

    for (arow = 0; arow < arows; ++arow) {
        double const dy2 = SQR(arow - ycenter);

        unsigned int col;
        for (col = 0; col < (cmdline.cols +1) / 2; ++col) {
            double const dx2 = SQR(col - xcenter);

            double const normalized = t(dx2, dy2, cmdline.weight) / 2 / tMax;

            gray const grayval = ROUNDU(cmdline.maxval * (0.5 + normalized));

            halfKernel[arow][col                   ] = grayval;
            halfKernel[arow][cmdline.cols - col - 1] = grayval;
        }
    }

    writeKernel(stdout, cmdline.cols, cmdline.rows, cmdline.maxval,
                halfKernel, arows);

    pgm_freearray(halfKernel, arows);

    return 0;
}
