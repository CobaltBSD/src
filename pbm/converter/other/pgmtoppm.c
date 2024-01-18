/* pgmtoppm.c - colorize a portable graymap into a portable pixmap
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

#define _XOPEN_SOURCE 500  /* Make sure strdup() is in string.h */
#define _BSD_SOURCE  /* Make sure strdup() is in <string.h> */
#include <string.h>

#include "pm_c_util.h"
#include "mallocvar.h"
#include "shhopt.h"
#include "ppm.h"

struct cmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    const char * inputFilename;  /* '-' if stdin */
    const char * map;
    const char * colorBlack;
    const char * colorWhite;
};



static void
parseCommandLine(int argc, char ** argv,
                 struct cmdlineInfo * const cmdlineP) {
/*----------------------------------------------------------------------------
   parse program command line described in Unix standard form by argc
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

    unsigned int mapSpec;

    MALLOCARRAY_NOFAIL(option_def, 100);

    option_def_index = 0;   /* incremented by OPTENT3 */
    OPTENT3(0, "map",            OPT_STRING,    &cmdlineP->map,
            &mapSpec,            0);

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = FALSE;  /* We have no parms that are negative numbers */

    pm_optParseOptions3(&argc, argv, opt, sizeof(opt), 0);
        /* Uses and sets argc, argv, and some of *cmdlineP and others. */

    if (!mapSpec)
        cmdlineP->map = NULL;

    if (mapSpec) {
        /* No color argument; only argument is file name */
        if (argc-1 < 1)
            cmdlineP->inputFilename = "-";
        else {
            cmdlineP->inputFilename = argv[1];
            if (argc-1 > 1)
                pm_error("With -map option, there is at most one argument: "
                         "the file name.  You specified %u", argc-1);
        }
    } else {
        /* Arguments are color or color range and file name */
        if (argc-1 < 1) {
            cmdlineP->colorBlack = "black";
            cmdlineP->colorWhite = "white";
        } else {
            char * buffer = strdup(argv[1]);
            char * hyphenPos = strchr(buffer, '-');
            if (hyphenPos) {
                *hyphenPos = '\0';
                cmdlineP->colorBlack = buffer;
                cmdlineP->colorWhite = hyphenPos+1;
            } else {
                cmdlineP->colorBlack = "black";
                cmdlineP->colorWhite = buffer;
            }
        }
        if (argc-1 < 2)
            cmdlineP->inputFilename = "-";
        else
            cmdlineP->inputFilename = argv[2];
        
        if (argc-1 > 2)
            pm_error("Program takes at most 2 arguments:  "
                     "color name/range and input file name.  "
                     "You specified %u", argc-1);
    }
}



static void
convertWithMap(FILE * const ifP,
               unsigned int const cols,
               unsigned int const rows,
               gray         const maxval,
               int          const format,
               const char * const mapFileName,
               FILE *       const ofP,
               gray *       const grayrow,
               pixel *      const pixelrow) {

    unsigned int row;
    FILE * mapFileP;
    int mapcols, maprows;
    pixval mapmaxval;
    pixel ** mappixels;
    unsigned int mapmaxcolor;
    
    mapFileP = pm_openr(mapFileName);
    mappixels = ppm_readppm(mapFileP, &mapcols, &maprows, &mapmaxval);
    pm_close(mapFileP);
    mapmaxcolor = maprows * mapcols - 1;

    ppm_writeppminit(ofP, cols, rows, mapmaxval, 0);

    for (row = 0; row < rows; ++row) {
        unsigned int col;
            
        pgm_readpgmrow(ifP, grayrow, cols, maxval, format);

        for (col = 0; col < cols; ++col) {
            unsigned int c;
            if (maxval == mapmaxcolor)
                c = grayrow[col];
            else
                c = grayrow[col] * mapmaxcolor / maxval;
            pixelrow[col] = mappixels[c / mapcols][c % mapcols];
        }
        ppm_writeppmrow(ofP, pixelrow, cols, mapmaxval, 0);
    }
    ppm_freearray(mappixels, maprows);
}



static void
convertLinear(FILE * const ifP,
              unsigned int const cols,
              unsigned int const rows,
              gray         const maxval,
              int          const format,
              const char * const colorNameBlack,
              const char * const colorNameWhite,
              FILE *       const ofP,
              gray *       const grayrow,
              pixel *      const pixelrow) {

    pixel colorBlack, colorWhite;
    pixval red0, grn0, blu0, red1, grn1, blu1;
    unsigned int row;

    ppm_writeppminit(ofP, cols, rows, maxval, 0);

    colorBlack = ppm_parsecolor(colorNameBlack, maxval);
    colorWhite = ppm_parsecolor(colorNameWhite, maxval);
 
    red0 = PPM_GETR(colorBlack);
    grn0 = PPM_GETG(colorBlack);
    blu0 = PPM_GETB(colorBlack);
    red1 = PPM_GETR(colorWhite);
    grn1 = PPM_GETG(colorWhite);
    blu1 = PPM_GETB(colorWhite);

    for (row = 0; row < rows; ++row) {
        unsigned int col;

        pgm_readpgmrow(ifP, grayrow, cols, maxval, format);

        for (col = 0; col < cols; ++col) {
            gray const input = grayrow[col];
            PPM_ASSIGN(
                pixelrow[col],
                (red0 * (maxval - input) + red1 * input) / maxval,
                (grn0 * (maxval - input) + grn1 * input) / maxval,
                (blu0 * (maxval - input) + blu1 * input) / maxval);
        }
        ppm_writeppmrow(ofP, pixelrow, cols, maxval, 0);
    }
}



int
main(int    argc,
     char * argv[]) {

    FILE * ifP;
    struct cmdlineInfo cmdline;
    gray * grayrow;
    pixel * pixelrow;
    int rows, cols, format;
    gray maxval;

    ppm_init(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    ifP = pm_openr(cmdline.inputFilename);

    pgm_readpgminit(ifP, &cols, &rows, &maxval, &format);
    grayrow = pgm_allocrow(cols);
    pixelrow = ppm_allocrow(cols);

    if (cmdline.map)
        convertWithMap(ifP, cols, rows, maxval, format, cmdline.map,
                       stdout, grayrow, pixelrow);
    else
        convertLinear(ifP, cols, rows, maxval, format, 
                      cmdline.colorBlack, cmdline.colorWhite, stdout,
                      grayrow, pixelrow);

    ppm_freerow(pixelrow);
    pgm_freerow(grayrow);
    pm_close(ifP);

    /* If the program failed, it previously aborted with nonzero completion
       code, via various function calls.
    */
    return 0;
}
