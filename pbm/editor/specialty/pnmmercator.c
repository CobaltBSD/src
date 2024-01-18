/* pammercator.c - convert a map in PNM image format from 360x180 degrees
**                 to Mercator projection or vice versa
**
** This program borrowed a lot of code from PnmScale which again was derived
** from PpmScale.
**
** Copyright (C) 2009 by Willem van Schaik <willem@schaik.com>
** Copyright (C) 1989, 1991 by Jef Poskanzer.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
**
*/

#define _XOPEN_SOURCE  /* Make sure M_PI is in <math.h> */
#include <math.h>
#include <string.h>

#include "pm_c_util.h"
#include "mallocvar.h"
#include "shhopt.h"
#include "pnm.h"

/* The pnm library allows us to code this program without branching cases for
   PGM and PPM, but we do the branch anyway to speed up processing of PGM
   images. 
*/



struct cmdlineInfo 
{
    /*
    All the information the user supplied in the command line,
    in a form easy for the program to use. 
    */

    const char * input_filespec;  /* Filespecs of input files */
    const char * inputFileName;  /* Filespec of input file */
    unsigned int inverse; /* from Mercator to Degrees */
    unsigned int nomix;
    unsigned int verbose;
    unsigned int vverbose;
};



static void
parseCommandLine(int                        argc, 
                 const char **              argv,
                 struct cmdlineInfo * const cmdlineP ) {

    optEntry * option_def;
    optStruct3 opt;
        /* Instructions to pm_optParseOptions3 on how to parse our options. */
    
    unsigned int option_def_index;

    MALLOCARRAY_NOFAIL(option_def, 100);

    option_def_index = 0;   /* incremented by OPTENT3 */
    OPTENT3(0, "inverse",   OPT_FLAG,    NULL,       &cmdlineP->inverse,   0);
    OPTENT3(0, "nomix",     OPT_FLAG,    NULL,       &cmdlineP->nomix,     0);
    OPTENT3(0, "verbose",   OPT_FLAG,    NULL,       &cmdlineP->verbose,   0);
    OPTENT3(0, "vverbose",  OPT_FLAG,    NULL,       &cmdlineP->vverbose,  0);

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = FALSE;   /* We have no parms that are negative numbers */

    /* Uses and sets argc, argv, and some of *cmdlineP and others. */
    pm_optParseOptions3( &argc, (char **)argv, opt, sizeof(opt), 0 );

    /* Only parameter allowed is optional filespec */
    if (argc-1 < 1)
        cmdlineP->input_filespec = "-";
    else
        cmdlineP->input_filespec = argv[1];
}



static void
computeOutputDimensions(const struct cmdlineInfo cmdline, 
                        const int rows, const int cols,
                        int * newrowsP, int * newcolsP) 
{
    *newcolsP = cols;
    if (!cmdline.inverse)
        *newrowsP = 2 * rows;
    else
        *newrowsP = rows / 2;

    if (*newcolsP < 1) *newcolsP = 1;
    if (*newrowsP < 1) *newrowsP = 1;

    if (cmdline.verbose) {
        if (!cmdline.inverse)
            pm_message("Creating Mercator map, new size is %dx%d",
                       *newcolsP, *newrowsP);
        else
            pm_message("Creating Degrees map, new size is %dx%d",
                       *newcolsP, *newrowsP);
    }
}        



static void
transformWithMixing(FILE * const ifP,
                    int const cols, int const rows,
                    xelval const maxval, int const format,
                    int const newcols, int const newrows,
                    xelval const newmaxval, int const newformat,
                    bool const inverse,
                    bool const verbose, bool const vverbose) 
{
    /* 
    Transform the map image on input file 'ifP' (which is described by 
    'cols', 'rows', 'format', and 'maxval') to a Mercator projection
    and write the result to standard output as format 'newformat' and 
    with maxval 'newmaxval'.

    We'll blend colors from subsequent rows in the output pixels. 
    */

    xel* oddxelrow;  /* an input row */
    xel* evenxelrow;
    xel* newxelrow;  /* the output row */

    int row;
    double fRow;
    int rowInXelrow;
    int inputRow;
    int col;

    double fFract;
    double fLatRad;
    double fLatMerc;

    oddxelrow = pnm_allocrow(cols); 
    evenxelrow = pnm_allocrow(cols); 
    rowInXelrow = 0;

    newxelrow = pnm_allocrow(newcols);

    for (row = 0; row < newrows; ++row) {
        
        fRow = (double)row + 0.5; /* center on half the pixel */
        if (!inverse) {
            /* the result is mercator, calculate back to degrees */
            fLatMerc = 2.0 * M_PI * (fRow / (double)newrows - 0.5);
                /* merc goes from -pi to +pi */
            fLatRad = 2.0 * (atan(exp(fLatMerc)) - M_PI / 4.0);
            fRow = ((fLatRad / M_PI) + 0.5) * (double)rows;
                /* lat goes from -pi/2 to +pi/2 */
        } else {
            /* the result is in degrees, calculate back to mercator */
            fLatRad = M_PI * (fRow / (double)newrows - 0.5);
                /* lat goes from -pi/2 to +pi/2 */
            fLatMerc = log(tan((M_PI / 4.0 + fLatRad / 2.0)));
            fRow = ((fLatMerc / M_PI / 2.0) + 0.5) * (double)rows;
                /* merc goes from -pi to +pi */
        }
        fRow -= 0.5;

        inputRow = (int) floor(fRow);
        if (inputRow < 0)
            inputRow = 0;
        if (inputRow > rows - 1)
            inputRow = rows - 1;

        /* calculate the fraction */
        fFract = 1.0 - ((fRow) - (double) inputRow);

        if (vverbose) {
            if (!inverse) {
#ifdef DBG_EDGES
                if ((row < 10) || (row > (newrows - 10)))
#else
  #ifdef DBG_MIDDLE
                if ((row > (newrows/2 - 10)) && (row < (newrows/2 + 10)))
  #else
                if (row % 20 == 0)
  #endif
#endif
                    pm_message("outputRow=%d latMerc=%f latRad=%f inputRow=%d "
                               "fRow=%f fFract=%f",
                               row, fLatMerc, fLatRad, inputRow, fRow, fFract);
            } else {
#ifdef DBG_EDGES
                if ((row < 10) || (row > (newrows - 10)))
#else
  #ifdef DBG_MIDDLE
                if ((row > (newrows/2 - 10)) && (row < (newrows/2 + 10)))
  #else
                if (row % 10 == 0)
  #endif
#endif
                    pm_message("outputRow=%d latRad=%f latMerc=%f inputRow=%d"
                               "fRow=%f fFract=%f",
                               row, fLatRad, fLatMerc, inputRow, fRow, fFract);
            }
        }

        while ((rowInXelrow <= inputRow + 1) && 
               (rowInXelrow < rows)) {
            /* we need to read one row ahead */
            if (rowInXelrow % 2 == 0) {
#ifdef DBG_EDGES
                if ((row < 10) || (row > (newrows - 10)))
                    pm_message("read even row - rowInXelrow=%d inputRow=%d",
                               rowInXelrow, inputRow);
#endif
                pnm_readpnmrow(ifP, evenxelrow, cols, newmaxval, format);
            } else {
#ifdef DBG_EDGES
                if ((row < 10) || (row > (newrows - 10)))
                    pm_message("read odd row - rowInXelrow=%d inputRow=%d",
                               rowInXelrow, inputRow);
#endif
                pnm_readpnmrow(ifP, oddxelrow, cols, newmaxval, format);
            }
            ++rowInXelrow;
        }

        for (col = 0; col < newcols; ++col) {
            if (inputRow == 0)
                newxelrow[col] = evenxelrow[col];
            else if (inputRow == rows - 1)
                newxelrow[col] = oddxelrow[col];
            else if (inputRow % 2 == 0) {
                /* the even row is the low one, the odd the high one */
                newxelrow[col].r = fFract * evenxelrow[col].r +
                    (1.0 - fFract) * oddxelrow[col].r;
                newxelrow[col].g = fFract * evenxelrow[col].g +
                    (1.0 - fFract) * oddxelrow[col].g;
                newxelrow[col].b = fFract * evenxelrow[col].b +
                    (1.0 - fFract) * oddxelrow[col].b;
            } else {
                newxelrow[col].r = fFract * oddxelrow[col].r +
                    (1.0 - fFract) * evenxelrow[col].r;
                newxelrow[col].g = fFract * oddxelrow[col].g +
                    (1.0 - fFract) * evenxelrow[col].g;
                newxelrow[col].b = fFract * oddxelrow[col].b +
                    (1.0 - fFract) * evenxelrow[col].b;
            }
        }

        pnm_writepnmrow(stdout, newxelrow, newcols, newmaxval, newformat, 0 );
    }

    pnm_freerow(oddxelrow);
    pnm_freerow(evenxelrow);
    pnm_freerow(newxelrow);
}



static void
transformNoneMixing(FILE * const ifP,
                   int const cols, int const rows,
                   xelval const maxval, int const format,
                   int const newcols, int const newrows,
                   xelval const newmaxval, int const newformat,
                   bool const inverse,
                   bool const verbose, bool const vverbose) 
{
    /*
    Transform the map image on input file 'ifP' (which is described by 
    'cols', 'rows', 'format', and 'maxval') to a Mercator projection and
    write the result to standard output as format 'newformat' and with 
    maxval 'newmaxval'.

    Don't mix colors from different input pixels together in the output
    pixels.  Each output pixel is an exact copy of some corresponding 
    input pixel.
    */

    xel* xelrow;          /* an input row */
    xel* newxelrow;         /* the output row */

    int row;
    double fRow;
    int rowInXelrow;
    int inputRow;
    int col;

    double fLatRad;
    double fLatMerc;

    xelrow = pnm_allocrow(cols); 
    rowInXelrow = 0;

    newxelrow = pnm_allocrow(newcols);

    for (row = 0; row < newrows; ++row) {
        
        fRow = (double)row + 0.5; /* center on half the pixel */
        if (!inverse) {
            /* the result is mercator, calculate back to degrees */
            fLatMerc = 2.0 * M_PI * (fRow / (double)newrows - 0.5);
                /* merc goes from -pi to +pi */
            fLatRad = 2.0 * (atan(exp(fLatMerc)) - M_PI / 4.0);
            fRow = ((fLatRad / M_PI) + 0.5) * (double)rows;
                /* lat goes from -pi/2 to +pi/2 */
        } else {
            /* the result is in degrees, calculate back to mercator */
            fLatRad = M_PI * (fRow / (double)newrows - 0.5);
                /* lat goes from -pi/2 to +pi/2 */
            fLatMerc = log(tan((M_PI / 4.0 + fLatRad / 2.0)));
            fRow = ((fLatMerc / M_PI / 2.0) + 0.5) * (double)rows;
                /* merc goes from -pi to +pi */
        }
        /* fRow -= 0.5; */        /* it's weird that this isn't needed */

        inputRow = (int) floor(fRow);
        if (inputRow < 0)
            inputRow = 0;
        if (inputRow > rows - 1)
            inputRow = rows - 1;

        if (vverbose) {
            if (!inverse) {
#ifdef DBG_EDGES
                if ((row < 10) || (row > (newrows - 10)))
#else
  #ifdef DBG_MIDDLE
                if ((row > (newrows/2 - 10)) && (row < (newrows/2 + 10)))
  #else
                if (row % 20 == 0)
  #endif
#endif
                    pm_message("outputRow=%d latMerc=%f latRad=%f inputRow=%d"
                               "fRow=%f",
                               row, fLatMerc, fLatRad, inputRow, fRow);
            } else {
#ifdef DBG_EDGES
                if ((row < 10) || (row > (newrows - 10)))
#else
  #ifdef DBG_MIDDLE
                if ((row > (newrows/2 - 10)) && (row < (newrows/2 + 10)))
  #else
                if (row % 10 == 0)
  #endif
#endif
                    pm_message("outputRow=%d latRad=%f latMerc=%f inputRow=%d"
                               "fRow=%f",
                               row, fLatRad, fLatMerc, inputRow, fRow);
            }
        }

        while ((rowInXelrow <= inputRow) && (rowInXelrow < rows)) {
#ifdef DBG_EDGES
            if ((row < 10) || (row > (newrows - 10)))
                pm_message("read row - rowInXelrow=%d inputRow=%d",
                           rowInXelrow, inputRow);
#endif
            pnm_readpnmrow(ifP, xelrow, cols, newmaxval, format);
            ++rowInXelrow;
        }
        for (col = 0; col < newcols; ++col) {
            newxelrow[col] = xelrow[col];
        }

        pnm_writepnmrow(stdout, newxelrow, newcols, newmaxval, newformat, 0 );
    }

    pnm_freerow(xelrow);
    pnm_freerow(newxelrow);
}



int
main(int argc, const char ** argv ) 
{
    struct cmdlineInfo cmdline;
    FILE* ifP;
    int rows, cols, format, newformat, newrows, newcols;
    xelval maxval, newmaxval;
    bool verbose;

    pm_proginit( &argc, argv );

    parseCommandLine(argc, argv, &cmdline);

    verbose = cmdline.verbose || cmdline.vverbose;

    ifP = pm_openr(cmdline.input_filespec);

    pnm_readpnminit( ifP, &cols, &rows, &maxval, &format );

    /* Promote PBM file to PGM. */
    if ( PNM_FORMAT_TYPE(format) == PBM_TYPE ) {
        newformat = PGM_TYPE;
        newmaxval = PGM_MAXMAXVAL;
        pm_message( "promoting from PBM to PGM" );
    } else {
        newformat = format;
        newmaxval = maxval;
    }

    computeOutputDimensions(cmdline, rows, cols, &newrows, &newcols);

    pnm_writepnminit(stdout, newcols, newrows, newmaxval, newformat, 0);

    if (cmdline.nomix) {
        if (verbose)
            pm_message("Transforming map without mixing/blending colors");
        transformNoneMixing(ifP, cols, rows, maxval, format,
                            newcols, newrows, newmaxval, newformat, 
                            cmdline.inverse, verbose, cmdline.vverbose);
    } else {
        if (verbose)
            pm_message("Transforming map while using intermediate colors");
        transformWithMixing(ifP, cols, rows, maxval, format,
                            newcols, newrows, newmaxval, newformat, 
                            cmdline.inverse, verbose, cmdline.vverbose);
    }

    pm_close(ifP);
    pm_close(stdout);
    
    return 0;
}
