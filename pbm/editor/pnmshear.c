 /* pnmshear.c - read a portable anymap and shear it by some angle
**
** Copyright (C) 1989, 1991 by Jef Poskanzer.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
*/

#define _XOPEN_SOURCE   /* get M_PI in math.h */

#include <assert.h>
#include <math.h>
#include <string.h>

#include "pm_c_util.h"
#include "mallocvar.h"
#include "ppm.h"
#include "pnm.h"
#include "shhopt.h"

#define SCALE 4096
#define HALFSCALE 2048



struct CmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    const char * inputFileName;   /* Name of input file */
    double       angle;           /* requested shear angle, in radians */
    unsigned int noantialias;     /* -noantialias option */
    const char * background;      /* NULL if none */
};



static void
parseCommandLine(int argc, const char ** argv,
                 struct CmdlineInfo *cmdlineP) {

    optStruct3 opt;
    unsigned int option_def_index = 0;
    optEntry * option_def;

    unsigned int backgroundSpec;

    MALLOCARRAY(option_def, 100);

    OPTENT3(0, "noantialias",      OPT_FLAG,  NULL, &cmdlineP->noantialias, 0);
    OPTENT3(0, "background",       OPT_STRING, &cmdlineP->background,
            &backgroundSpec, 0);
    
    opt.opt_table = option_def;
    opt.short_allowed = FALSE;
    opt.allowNegNum = TRUE;

    pm_optParseOptions3(&argc, (char **)argv, opt, sizeof(opt), 0);

    if (!backgroundSpec)
        cmdlineP->background = NULL;

    if (argc-1 < 1)
        pm_error("Need an argument:  the shear angle.\n");
    else {
        char *endptr;
        cmdlineP->angle = strtod(argv[1], &endptr) * M_PI / 180;
        if (*endptr != '\0' || strlen(argv[1]) == 0)
            pm_error("Angle argument is not a valid floating point number: "
                     "'%s'", argv[1]);
        if (argc-1 < 2)
            cmdlineP->inputFileName = "-";
        else {
            cmdlineP->inputFileName = argv[2];
            if (argc-1 > 2)
                pm_error("too many arguments (%d).  "
                         "The only arguments are shear angle and filespec.",
                         argc-1);
        }
    }
    free(option_def);
}



static void
makeNewXel(xel *  const outputXelP,
           xel    const curXel,
           xel    const prevXel,
           double const fracnew0,
           double const omfracnew0,
           int    const format) {
/*----------------------------------------------------------------------------
   Create an output xel as *outputXel, which is part curXel and part
   prevXel, the part given by the fractions omfracnew0 and fracnew0,
   respectively.  These fraction values are the numerator of a fraction
   whose denominator is SCALE.

   The format of the pixel is 'format'.
-----------------------------------------------------------------------------*/

    switch (PNM_FORMAT_TYPE(format)) {
    case PPM_TYPE:
        PPM_ASSIGN(*outputXelP,
                   (fracnew0 * PPM_GETR(prevXel) 
                    + omfracnew0 * PPM_GETR(curXel) 
                    + HALFSCALE) / SCALE,
                   (fracnew0 * PPM_GETG(prevXel) 
                    + omfracnew0 * PPM_GETG(curXel) 
                    + HALFSCALE) / SCALE,
                   (fracnew0 * PPM_GETB(prevXel) 
                    + omfracnew0 * PPM_GETB(curXel) 
                    + HALFSCALE) / SCALE );
        break;
        
    default:
        PNM_ASSIGN1(*outputXelP,
                    (fracnew0 * PNM_GET1(prevXel) 
                     + omfracnew0 * PNM_GET1(curXel) 
                     + HALFSCALE) / SCALE );
        break;
    }
}



static void
shearRow(xel *        const xelrow,
         unsigned int const cols, 
         xel *        const newxelrow,
         unsigned int const newcols, 
         double       const shearCols,
         int          const format,
         xel          const bgxel,
         bool         const antialias) {
/*----------------------------------------------------------------------------
   Shear the row 'xelrow' by 'shearCols' columns, and return the result as
   'newxelrow'.  They are 'cols' and 'newcols' columns wide, respectively.
   
   Fill in the part of the output row that doesn't contain image data with
   'bgxel'.

   Use antialiasing iff 'antialias'.

   The format of the input xels (which implies something about the
   output xels too) is 'format'.
-----------------------------------------------------------------------------*/
    unsigned int const intShearCols = (unsigned int) shearCols;

    assert(shearCols >= 0.0);
        
    if (antialias) {
        const long fracnew0 = (shearCols - intShearCols) * SCALE;
        const long omfracnew0 = SCALE - fracnew0;

        unsigned int col;
        xel prevXel;
            
        for (col = 0; col < newcols; ++col)
            newxelrow[col] = bgxel;

        prevXel = bgxel;
        for (col = 0; col < cols; ++col) {
            makeNewXel(&newxelrow[intShearCols + col],
                       xelrow[col], prevXel, fracnew0, omfracnew0,
                       format);
            prevXel = xelrow[col];
        }
        if (fracnew0 > 0) 
            /* Need to add a column for what's left over */
            makeNewXel(&newxelrow[intShearCols + cols],
                       bgxel, prevXel, fracnew0, omfracnew0, format);
    } else {
        unsigned int col;
        for (col = 0; col < intShearCols; ++col)
            newxelrow[col] = bgxel;
        for (col = 0; col < cols; ++col)
            newxelrow[intShearCols+col] = xelrow[col];
        for (col = intShearCols + cols; col < newcols; ++col)
            newxelrow[col] = bgxel;
    }
}


static xel
backgroundColor(const char * const backgroundColorName,
                xel *        const topRow,
                int          const cols,
                xelval       const maxval,
                int          const format) {

    xel retval;

    if (backgroundColorName) {
        retval = pnm_parsecolorxel(backgroundColorName, maxval, format);
    } else 
        retval = pnm_backgroundxelrow(topRow, cols, maxval, format);

    return retval;
}



int
main(int argc, const char * argv[]) {

    FILE * ifP;
    xel * xelrow;
    xel * newxelrow;
    xel bgxel;
    int rows, cols, format; 
    int newformat, newcols; 
    int row;
    xelval maxval, newmaxval;
    double shearfac;
    double newcolsD;

    struct CmdlineInfo cmdline;

    pm_proginit(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    ifP = pm_openr(cmdline.inputFileName);

    pnm_readpnminit(ifP, &cols, &rows, &maxval, &format);
    xelrow = pnm_allocrow(cols);

    /* Promote PBM files to PGM. */
    if (!cmdline.noantialias && PNM_FORMAT_TYPE(format) == PBM_TYPE) {
        newformat = PGM_TYPE;
        newmaxval = PGM_MAXMAXVAL;
        pm_message("promoting from PBM to PGM - "
                   "use -noantialias to avoid this");
    } else {
        newformat = format;
        newmaxval = maxval;
    }

    shearfac = fabs(tan(cmdline.angle));

    newcolsD = (double) rows * shearfac + cols + 0.999999;
    if (newcolsD > INT_MAX-2)
        pm_error("angle is too close to +/-90 degrees; "
                 "output image too wide for computation");
    else
        newcols = (int) newcolsD;

    pnm_writepnminit(stdout, newcols, rows, newmaxval, newformat, 0);
    newxelrow = pnm_allocrow(newcols);
    
    for (row = 0; row < rows; ++row) {
        double shearCols;

        pnm_readpnmrow(ifP, xelrow, cols, newmaxval, format);

        if (row == 0)
            bgxel = backgroundColor(cmdline.background,
                                    xelrow, cols, newmaxval, format);

        if (cmdline.angle > 0.0)
            shearCols = row * shearfac;
        else
            shearCols = (rows - row) * shearfac;

        shearRow(xelrow, cols, newxelrow, newcols, 
                 shearCols, format, bgxel, !cmdline.noantialias);

        pnm_writepnmrow(stdout, newxelrow, newcols, newmaxval, newformat, 0);
    }
    
    pm_close(ifP);
    pm_close(stdout);

    return 0;
}



