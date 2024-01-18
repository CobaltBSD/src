/* pnmsmooth.c - smooth out an image by replacing each pixel with the 
**               average of its width x height neighbors.
**
** Version 2.0   December 5, 1994
**
** Copyright (C) 1994 by Mike Burns (burns@chem.psu.edu)
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
*/

/*
  Written by Mike Burns December 5, 1994 and called Version 2.0.
  Based on ideas from a shell script by Jef Poskanzer, 1989, 1991.
  The shell script had no options.
*/


#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <errno.h>

#include "pm_c_util.h"
#include "mallocvar.h"
#include "shhopt.h"
#include "nstring.h"
#include "pm.h"   /* For pm_plain_output */
#include "pm_system.h"
#include "pnm.h"


struct cmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    const char * inputFilespec;  /* Filespec of input file */
    unsigned int width;
    unsigned int height;
    unsigned int dump;
};



static void
parseCommandLine (int argc, const char ** argv,
                  struct cmdlineInfo *cmdlineP) {
/*----------------------------------------------------------------------------
   parse program command line described in Unix standard form by argc
   and argv.  Return the information in the options as *cmdlineP.  

   If command line is internally inconsistent (invalid options, etc.),
   issue error message to stderr and abort program.

   Note that the strings we return are stored in the storage that
   was passed to us as the argv array.  We also trash *argv.
-----------------------------------------------------------------------------*/
    optEntry * option_def;
        /* Instructions to pm_optParseOptions3 on how to parse our options.
         */
    optStruct3 opt;

    unsigned int option_def_index;

    unsigned int widthSpec, heightSpec, sizeSpec;

    MALLOCARRAY_NOFAIL(option_def, 100);
    
    option_def_index = 0;   /* incremented by OPTENT3 */
    OPTENT3(0,   "dump",          OPT_FLAG,   
            NULL,                       &cmdlineP->dump, 0);
    OPTENT3(0,   "width",         OPT_UINT,
            &cmdlineP->width,           &widthSpec, 0);
    OPTENT3(0,   "height",        OPT_UINT,
            &cmdlineP->height,          &heightSpec, 0);
    OPTENT3(0,   "size",          OPT_FLAG,
            NULL,                       &sizeSpec, 0);

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = FALSE;  /* We have no parms that are negative numbers */

    pm_optParseOptions3(&argc, (char **)argv, opt, sizeof(opt), 0);
        /* Uses and sets argc, argv, and some of *cmdline_p and others. */

    free(option_def);

    if (!widthSpec)
        cmdlineP->width = 3;

    if (!heightSpec)
        cmdlineP->height = 3;

    if (sizeSpec) {
        /* -size is strictly for backward compatibility.  This program
           used to use a different command line processor and had
           irregular syntax in which the -size option had two values,
           e.g. "-size <width> <height>" And the options had to go
           before the arguments.  So an old pnmsmooth command looks to us
           like a command with the -size flag option and the first two
           arguments being the width and height.
        */

        if (widthSpec || heightSpec)
            pm_error("-size is obsolete.  Use -width and -height instead");

        if (argc-1 > 3)
            pm_error("Too many arguments.  With -size, there are at most "
                     "3 arguments.");
        else if (argc-1 < 2)
            pm_error("Not enough arguments.  With -size, the first two "
                     "arguments are width and height");
        else {
            cmdlineP->width  = atoi(argv[1]);
            cmdlineP->height = atoi(argv[2]);
            
            if (argc-1 < 3)
                cmdlineP->inputFilespec = "-";
            else
                cmdlineP->inputFilespec = argv[3];
        }
    } else {
        if (argc-1 > 1)
            pm_error("Program takes at most one argument: the input file "
                     "specification.  "
                     "You specified %d arguments.", argc-1);
        if (argc-1 < 1)
            cmdlineP->inputFilespec = "-";
        else
            cmdlineP->inputFilespec = argv[1];
    }
    if (cmdlineP->width % 2 != 1)
        pm_error("The convolution matrix must have an odd number of columns.  "
                 "You specified %u", cmdlineP->width);

    if (cmdlineP->height % 2 != 1)
        pm_error("The convolution matrix must have an odd number of rows.  "
                 "You specified %u", cmdlineP->height);
}


static void
validateComputableDimensions(unsigned int const cols,
                             unsigned int const rows){
/*----------------------------------------------------------------------------
   Make sure that convolution matrix dimensions are small enough to
   represent in a string.
-----------------------------------------------------------------------------*/
    unsigned int const maxStringLength = INT_MAX - 2 -6;

    if (cols >  maxStringLength / rows / 2 )
       pm_error("The convolution matrix size %u x %u is too large.",
                cols, rows);
}



static const char *
makeConvolutionKernel(unsigned int const cols,
                      unsigned int const rows) {
/*----------------------------------------------------------------------------
  Return a value for a Pnmconvol '-matrix' option that specifies a
  convolution kernel with with dimensions 'cols' by 'rows' with 1
  for every weight.  Caller can use this with Pnmconvol -normalize.
-----------------------------------------------------------------------------*/
    unsigned int const maxOptSize = cols * rows * 2;

    char * matrix;

    MALLOCARRAY(matrix, maxOptSize);

    if (matrix == NULL)
        pm_error("Could not get memory for a %u x %u convolution matrix",
                 rows, cols);
    else {
        unsigned int row;
        unsigned int cursor;
     
        for (row = 0, cursor = 0; row < rows; ++row) {
            unsigned int col;

            if (row > 0)
                matrix[cursor++] = ';';

            for (col = 0; col < cols; ++col) {
                if (col > 0)
                    matrix[cursor++] = ',';

                matrix[cursor++] = '1';
            }
        }
        assert(cursor < maxOptSize);
        matrix[cursor] = '\0';
    }

    return matrix;
}



static void
validateMatrixOptSize(unsigned int const rows,
                      unsigned int const cols) {

    /* If the user accidentally specifies absurdly large values for the
       convolution matrix size, the failure mode can be a confusing message
       resulting from the 'pnmconvol' arguments being too large.  To try
       to be more polite in that case, we apply an arbitrary limit on the
       size of the option here.
    */

    if (rows * cols > 5000)
        pm_error("Convolution matrix dimensions %u x %u are too large "
                 "to be useful, so we assume you made a mistake.  "
                 "We refuse to use numbers this large because they might "
                 "cause excessive resource use that would cause failures "
                 "whose cause would not be obvious to you", cols, rows);
}



int
main(int argc, const char ** argv) {

    struct cmdlineInfo cmdline;
    const char * matrixOptValue;

    pm_proginit(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    validateComputableDimensions(cmdline.width, cmdline.height);
    validateMatrixOptSize(cmdline.width, cmdline.height);

    matrixOptValue = makeConvolutionKernel(cmdline.width, cmdline.height);

    if (cmdline.dump) {
        pm_error("-dump option no longer exists.  "
                 "You don't need it because you can now do uniform "
                 "convolution easily with the -matrix and -normalize "
                 "options of 'pnmconvol'.");
    } else {
        const char * const plainOpt = pm_plain_output ? "-plain" : NULL;

        const char * matrixOpt;

        pm_asprintf(&matrixOpt, "-matrix=%s", matrixOptValue);

        pm_message("Running Pnmconvol -normalize %s", matrixOpt);

        pm_system_lp("pnmconvol", NULL, NULL, NULL, NULL,
                     "pnmconvol", matrixOpt, cmdline.inputFilespec,
                     "-normalize", "-quiet", plainOpt, NULL);

        pm_strfree(matrixOpt);
    }
    pm_strfree(matrixOptValue);

    return 0;
}
