/* ppmmake.c - create a pixmap of a specified color and size
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

#include "pm_c_util.h"
#include "mallocvar.h"
#include "shhopt.h"
#include "ppm.h"

struct cmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    pixel color;
    unsigned int cols;
    unsigned int rows;
    pixval maxval;
};



static void
parseCommandLine(int argc, char ** argv,
                 struct cmdlineInfo * const cmdlineP) {
/*----------------------------------------------------------------------------
  Convert program invocation arguments (argc,argv) into a format the 
  program can use easily, struct cmdlineInfo.  Validate arguments along
  the way and exit program with message if invalid.

  Note that some string information we return as *cmdlineP is in the storage 
  argv[] points to.
-----------------------------------------------------------------------------*/
    optEntry * option_def;
        /* Instructions to OptParseOptions3 on how to parse our options.
         */
    optStruct3 opt;

    unsigned int maxvalSpec;
    unsigned int option_def_index;

    MALLOCARRAY(option_def, 100);

    option_def_index = 0;   /* incremented by OPTENTRY */
    OPTENT3(0,   "maxval",    OPT_UINT, &cmdlineP->maxval, &maxvalSpec,    0);

    opt.opt_table = option_def;
    opt.short_allowed = false;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = false;  /* We have no parms that are negative numbers */

    pm_optParseOptions3(&argc, argv, opt, sizeof(opt), 0);
        /* Uses and sets argc, argv, and some of *cmdlineP and others. */

    free (option_def);

    if (!maxvalSpec)
        cmdlineP->maxval = PPM_MAXMAXVAL;
    else {
        if (cmdlineP->maxval > PPM_OVERALLMAXVAL)
            pm_error("The value you specified for -maxval (%u) is too big.  "
                     "Max allowed is %u", cmdlineP->maxval, PPM_OVERALLMAXVAL);

        if (cmdlineP->maxval < 1)
            pm_error("You cannot specify 0 for -maxval");
    }

    if (argc-1 < 3)
        pm_error("Need 3 arguments: color, width, height.");
    else if (argc-1 > 3)
        pm_error("Only 3 arguments allowed: color, width, height.  "
                 "You specified %d", argc-1);
    else {
        cmdlineP->color = ppm_parsecolor(argv[1], cmdlineP->maxval);
        cmdlineP->cols = pm_parse_width(argv[2]);
        cmdlineP->rows = pm_parse_height(argv[3]);
    }
}



int
main(int argc, char *argv[]) {

    struct cmdlineInfo cmdline;
    pixel * pixrow;
    unsigned int row, col;

    ppm_init(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    ppm_writeppminit(stdout, cmdline.cols, cmdline.rows, cmdline.maxval, 0);
    pixrow = ppm_allocrow(cmdline.cols);

    /* All rows are identical.  Fill once. */
    for (col = 0; col < cmdline.cols; ++col)
        pixrow[col] = cmdline.color;

    for (row = 0; row < cmdline.rows; ++row)
        ppm_writeppmrow(stdout, pixrow, cmdline.cols, cmdline.maxval, 0);

    ppm_freerow(pixrow);
    pm_close(stdout);

    return 0;
}
