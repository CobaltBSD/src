/* pamwipeout.c - read a bitmap and replace it with a gradient between two
** edges
**
** Copyright (C) 2011 by Willem van Schaik (willem@schaik.com)
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "pm_c_util.h"
#include "mallocvar.h"
#include "shhopt.h"
#include "pam.h"


enum Direction {DIR_LR, DIR_TB};

struct cmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    const char *inputFileName;  /* '-' if stdin */
    enum Direction direction;  /* top-bottom or left-right */
};



static void
parseCommandLine(int                        argc, 
                 const char **              argv,
                 struct cmdlineInfo * const cmdlineP ) {
/*----------------------------------------------------------------------------
   Parse program command line described in Unix standard form by argc
   and argv.  Return the information in the options as *cmdlineP.  

   If command line is internally inconsistent (invalid options, etc.),
   issue error message to stderr and abort program.

   Note that the strings we return are stored in the storage that
   was passed to us as the argv array.  We also trash *argv.
-----------------------------------------------------------------------------*/
    optEntry *option_def;
        /* Instructions to pm_optParseOptions3 on how to parse our options.
         */
    optStruct3 opt;

    unsigned int option_def_index;

    unsigned int lr, tb;

    MALLOCARRAY_NOFAIL(option_def, 100);

    option_def_index = 0;   /* incremented by OPTENT3 */
    OPTENT3(0, "lr",     OPT_FLAG,   NULL,                  
            &lr,       0);
    OPTENT3(0, "tb",     OPT_FLAG,   NULL,                  
            &tb,       0);

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = FALSE;  /* We have no parms that are negative numbers */

    pm_optParseOptions3(&argc, (char **)argv, opt, sizeof(opt), 0);
        /* Uses and sets argc, argv, and some of *cmdlineP and others. */

    if (!lr && !tb)
        pm_error("You must specify either -lr or -tb");
    else if (lr && tb)
        pm_error("You may not specify both -lr and -tb");
    else 
        cmdlineP->direction = lr ? DIR_LR : DIR_TB;


    if (argc-1 < 1)
        cmdlineP->inputFileName = "-";
    else {
        cmdlineP->inputFileName = argv[1];
        if (argc-1 > 1)
            pm_error("Too many arguments: %u.  "
                     "The only possible argument is the "
                     "optional input file name", argc-1);
    }
}




static void 
wipeImgByRow (struct pam const inpam, 
              tuple **   const tuples) {

    double const h = (double) inpam.height;

    unsigned int row;
    unsigned int col;

    for (row = 0; row < inpam.height; ++row)  {
        double const y = (double) row;
        for (col = 0; col < inpam.width; ++col)  {
            unsigned int i;
            for (i = 0; i < inpam.depth; ++i) {
                sample const top = tuples[0][col][i];
                sample const bot = tuples[inpam.height - 1][col][i];
                tuples[row][col][i] = (int)
                    floor(((h - y) / h)
                          * (double) top + (y / h)
                          * (double) bot);
            }
        }
    }
}



static void 
wipeRowByCol(struct pam const inpam, 
             tuple **   const tuples, 
             tuple *    const tuplerow) {

    double const w = (double) inpam.width;

    unsigned int col;

    for (col = 0; col < inpam.width; ++col)  {
        double const x = (double) col;
        unsigned int i;
        for (i = 0; i < inpam.depth; ++i) {
            sample const lft = tuplerow[0][i];
            sample const rgt = tuplerow[inpam.width - 1][i];
            tuplerow[col][i] = (int)
                floor( ((w - x) / w)
                       * (double) lft + (x / w)
                       * (double) rgt );
        }
    }
}



static void
wipeoutTb(FILE * const ifP,
          FILE * const ofP) {

    /* top-bottom we have to read the full image */

    struct pam inpam, outpam;
    tuple ** tuples;
    
    tuples = pnm_readpam(ifP, &inpam, PAM_STRUCT_SIZE(tuple_type));

    outpam = inpam; 
    outpam.file = ofP;

    wipeImgByRow(inpam, tuples);

    pnm_writepam(&outpam, tuples);
       
    pnm_freepamarray(tuples, &inpam);
}



static void
wipeoutLr(FILE * const ifP,
          FILE * const ofP) {
    
    /* left-right we can read row-by-row */

    struct pam inpam, outpam;
    tuple ** tuples;
    tuple * tuplerow;
    unsigned int row;

    pnm_readpaminit(ifP, &inpam, PAM_STRUCT_SIZE(tuple_type));

    outpam = inpam;
    outpam.file = ofP;

    pnm_writepaminit(&outpam);

    tuplerow = pnm_allocpamrow(&inpam);

    for (row = 0; row < inpam.height; ++row) {
        pnm_readpamrow(&inpam, tuplerow);

        wipeRowByCol(inpam, tuples, tuplerow);

        pnm_writepamrow(&outpam, tuplerow);
    }

    pnm_freepamrow(tuplerow);
}



int
main(int argc, const char *argv[]) {

    struct cmdlineInfo cmdline;
    FILE * ifP;

    pm_proginit(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    ifP = pm_openr(cmdline.inputFileName);

    switch (cmdline.direction) {
    case DIR_TB:
        wipeoutTb(ifP, stdout);
        break;
    case DIR_LR:
        wipeoutLr(ifP, stdout);
        break;
    }

    pm_close(ifP);
    pm_close(stdout);

    return 0;
}
