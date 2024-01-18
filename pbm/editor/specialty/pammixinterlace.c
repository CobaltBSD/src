/******************************************************************************
                             pammixinterlace
*******************************************************************************
  De-interlace an image by merging adjacent rows.
   
  Copyright (C) 2007 Bruce Guenter, FutureQuest, Inc.

  Permission to use, copy, modify, and distribute this software and its
  documentation for any purpose and without fee is hereby granted,
  provided that the above copyright notice appear in all copies and that
  both that copyright notice and this permission notice appear in
  supporting documentation.  This software is provided "as is" without
  express or implied warranty.

******************************************************************************/

#define _BSD_SOURCE    /* Make sure strcaseeq() is in nstring.h */

#include <string.h>

#include "pm_c_util.h"
#include "mallocvar.h"
#include "nstring.h"
#include "shhopt.h"
#include "pam.h"



static sample
clamp(sample const val,
      sample const maxval) {

    return val < 0 ? 0 : val > maxval ? maxval : val;
}



static bool
distant(long const above,
        long const mid,
        long const below) {

    return abs(mid - (above + below) / 2) > abs(above - below);
}



static void
filterLinearBlend(tuple *      const outputrow,
                  tuple **     const tuplerowWindow,
                  unsigned int const width,
                  unsigned int const depth,
                  bool         const adaptive,
                  sample       const maxval) {

    unsigned int col;

    for (col = 0; col < width; ++col) {
        unsigned int plane;

        for (plane = 0; plane < depth; ++plane) {
            long const above = tuplerowWindow[0][col][plane];
            long const mid   = tuplerowWindow[1][col][plane];
            long const below = tuplerowWindow[2][col][plane];

            sample out;

            if (!adaptive || distant(above, mid, below))
                out = (above + mid * 2 + below) / 4;
            else
                out = mid;
            
            outputrow[col][plane] = out;
        }
    }
}



static void
filterFfmpeg(tuple *      const outputrow,
             tuple **     const tuplerowWindow,
             unsigned int const width,
             unsigned int const depth,
             bool         const adaptive,
             sample       const maxval) {

    unsigned int col;
    
    for (col = 0; col < width; ++col) {
        unsigned int plane;
        
        for (plane = 0; plane < depth; ++plane) {
            long const above = tuplerowWindow[1][col][plane];
            long const mid   = tuplerowWindow[2][col][plane];
            long const below = tuplerowWindow[3][col][plane];

            sample out;
            
            if (!adaptive || distant(above, mid, below)) {
                long const a = (- (long)tuplerowWindow[0][col][plane]
                                + above * 4
                                + mid * 2
                                + below * 4
                                - (long)tuplerowWindow[4][col][plane]) / 8;
                out = clamp(a, maxval);
            } else
                out = mid;

            outputrow[col][plane] = out;
        }
    }
}



static void
filterFIR(tuple *      const outputrow,
          tuple **     const tuplerowWindow,
          unsigned int const width,
          unsigned int const depth,
          bool         const adaptive,
          sample       const maxval) {

    unsigned int col;

    for (col = 0; col < width; ++col) {
        unsigned int plane;

        for (plane = 0; plane < depth; ++plane) {

            long const above = tuplerowWindow[1][col][plane];
            long const mid   = tuplerowWindow[2][col][plane];
            long const below = tuplerowWindow[3][col][plane];

            sample out;

            if (!adaptive || distant(above, mid, below)) {
                long const a = (- (long)tuplerowWindow[0][col][plane]
                                + above * 2
                                + mid * 6
                                + below * 2
                                - (long)tuplerowWindow[4][col][plane]) / 8;
                out = clamp(a, maxval);
            } else
                out = mid;
            
            outputrow[col][plane] = out;
        }
    }
}



struct filter {
    const char * name;          /* The command-line name of the filter */
    unsigned int rows;   /* The number of rows the filter operates on */
    void (*filter)(tuple *, tuple **,
                   unsigned int width, unsigned int depth,
                   bool adaptive, sample maxval);
};

static struct filter filters[] = {
    { "fir", 5, filterFIR }, /* FIR is cleanest and default filter */
    { "ffmpeg", 5, filterFfmpeg },
    { "linear", 3, filterLinearBlend },
};

struct cmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    const char * inputFileName;  /* Names of input files */
    struct filter * filterP;
    unsigned int adaptive;
};



static void
parseCommandLine(int argc, char ** argv,
                 struct cmdlineInfo * const cmdlineP) {
/*----------------------------------------------------------------------------
   Note that the file spec array we return is stored in the storage that
   was passed to us as the argv array.
-----------------------------------------------------------------------------*/
    optStruct3 opt;  /* set by OPTENT3 */
    optEntry * option_def;
    unsigned int option_def_index;
    const char * filterName;
    unsigned int filterSpec;

    MALLOCARRAY_NOFAIL(option_def, 100);

    option_def_index = 0;   /* incremented by OPTENT3 */
    OPTENT3(0, "filter",   OPT_STRING, &filterName, &filterSpec, 0);
    OPTENT3(0, "adaptive", OPT_FLAG, NULL, &cmdlineP->adaptive, 0);

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = FALSE;  /* We have no parms that are negative numbers */

    pm_optParseOptions3(&argc, argv, opt, sizeof(opt), 0);
    /* Uses and sets argc, argv, and some of *cmdlineP and others. */

    if (!filterSpec)
        cmdlineP->filterP = &filters[0];
    else {
        unsigned int i;
        cmdlineP->filterP = NULL;
        for (i = 0; i < sizeof filters / sizeof(struct filter); ++i) {
            if (strcaseeq(filterName, filters[i].name)) {
                cmdlineP->filterP = &filters[i];
                break;
            }
        }
        if (!cmdlineP->filterP)
            pm_error("The filter name '%s' is not known.", filterName);
    }
    
    if (argc-1 < 1)
        cmdlineP->inputFileName = "-";
    else if (argc-1 == 1)
        cmdlineP->inputFileName = argv[1];
    else
        pm_error("You specified too many arguments (%d).  The only "
                 "argument is the optional input file specification.",
                 argc-1);
}



static void
allocateRowWindowBuffer(struct pam * const pamP,
                        tuple **     const tuplerowWindow,
                        unsigned int const rows) {

    unsigned int row;

    for (row = 0; row < rows; ++row)
        tuplerowWindow[row] = pnm_allocpamrow(pamP);
}



static void
freeRowWindowBuffer(tuple **     const tuplerowWindow,
                    unsigned int const rows) {

    unsigned int row;

    for (row = 0; row < rows; ++row)
        pnm_freepamrow(tuplerowWindow[row]);
}



static void
slideWindowDown(tuple **     const tuplerowWindow,
                unsigned int const rows) {
/*----------------------------------------------------------------------------
  Slide the rows-line tuple row window tuplerowWindow[] down one by moving
  pointers.
-----------------------------------------------------------------------------*/
    tuple * const oldrow0 = tuplerowWindow[0];

    unsigned int i;

    for (i = 0; i < rows-1; ++i)
        tuplerowWindow[i] = tuplerowWindow[i+1];

    tuplerowWindow[i] = oldrow0;
}



int
main(int argc, char *argv[]) {

    FILE * ifP;
    struct cmdlineInfo cmdline;
    struct pam inpam;  
    struct pam outpam;
    tuple * tuplerowWindow[5];
    tuple * outputrow;
    unsigned int rows;
    
    pnm_init(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    rows = cmdline.filterP->rows;

    ifP = pm_openr(cmdline.inputFileName);
    
    pnm_readpaminit(ifP, &inpam, PAM_STRUCT_SIZE(tuple_type));

    outpam = inpam;    /* Initial value -- most fields should be same */
    outpam.file = stdout;

    pnm_writepaminit(&outpam);

    allocateRowWindowBuffer(&inpam, tuplerowWindow, rows);
    outputrow = pnm_allocpamrow(&outpam);

    if (inpam.height < rows) {
        unsigned int row;
        pm_message("WARNING: Image height less than %d.  No mixing done.",
                   rows);
        for (row = 0; row < inpam.height; ++row) {
            pnm_readpamrow(&inpam, tuplerowWindow[0]);
            pnm_writepamrow(&outpam, tuplerowWindow[0]);
        }
    } else {
        unsigned int row;

    for (row = 0; row < rows-1; ++row)
        pnm_readpamrow(&inpam, tuplerowWindow[row]);

    /* Pass through first unfilterable rows */
    for (row = 0; row < rows/2; ++row)
        pnm_writepamrow(&outpam, tuplerowWindow[row]);

    for (row = rows / 2 + 1; row < inpam.height - rows / 2 + 1; ++row) {
        pnm_readpamrow(&inpam, tuplerowWindow[rows-1]);
        cmdline.filterP->filter(outputrow, tuplerowWindow,
                                inpam.width, inpam.depth,
                                cmdline.adaptive, inpam.maxval);
        pnm_writepamrow(&outpam, outputrow);
        
        slideWindowDown(tuplerowWindow, rows);
    }
    
    /* Pass through last rows */
    for (row = rows/2; row < rows-1; ++row)
        pnm_writepamrow(&outpam, tuplerowWindow[row]);
    }

    freeRowWindowBuffer(tuplerowWindow, rows);
    pnm_freepamrow(outputrow);
    pm_close(inpam.file);
    pm_close(outpam.file);
    
    return 0;
}
