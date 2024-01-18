/* pnmtile.c - replicate a portable anymap into a specified size
**
** Copyright (C) 1989 by Jef Poskanzer.
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
#include "pnm.h"



struct cmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    const char * inputFileName;
    unsigned int width;
    unsigned int height;
};



static void
parseCommandLine(int argc, const char ** argv,
                 struct cmdlineInfo * const cmdlineP) {
/*----------------------------------------------------------------------------
   Note that the file spec array we return is stored in the storage that
   was passed to us as the argv array.
-----------------------------------------------------------------------------*/
    optEntry *option_def;
        /* Instructions to OptParseOptions3 on how to parse our options.
         */
    optStruct3 opt;

    unsigned int option_def_index;

    MALLOCARRAY_NOFAIL(option_def, 100);

    option_def_index = 0;   /* incremented by OPTENT3 */

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = FALSE;  /* We have no parms that are negative numbers */

    OPTENTINIT;

    pm_optParseOptions3(&argc, (char**)argv, opt, sizeof opt, 0);
        /* Uses and sets argc, argv, and some of *cmdlineP and others. */

    if (argc-1 < 2)
        pm_error("You must specify at least two parameters: "
                 "width and height.  You specified %u",
                 argc-1);
    else {
        cmdlineP->width  = pm_parse_width(argv[1]);
        cmdlineP->height = pm_parse_height(argv[2]);

        if (argc-1 > 2) {
            cmdlineP->inputFileName = argv[3];

            if (argc-1 > 3)
                pm_error("There are at most three arguments: "
                         "width, height, file name.  You specified %u",
                         argc-1);
        } else 
            cmdlineP->inputFileName = "-";
    }
}



int
main(int argc, const char ** argv) {

    struct cmdlineInfo cmdline;
    FILE * ifP;
    xel ** xels;
    xel * xelrow;
    xelval maxval;
    int rows, cols;
    int format;
    unsigned int row;

    pm_proginit(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    ifP = pm_openr(cmdline.inputFileName);

    xels = pnm_readpnm(ifP, &cols, &rows, &maxval, &format);
    pm_close(ifP);

    xelrow = pnm_allocrow(cmdline.width);

    pnm_writepnminit(stdout, cmdline.width, cmdline.height, maxval, format, 0);
    for (row = 0; row < cmdline.height; ++row) {
        unsigned int col;
        for (col = 0; col < cmdline.width; ++col)
            xelrow[col] = xels[row % rows][col % cols];
        pnm_writepnmrow(stdout, xelrow, cmdline.width, maxval, format, 0);
    }

    pm_close(stdout);

    return 0;
}
