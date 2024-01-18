/*=============================================================================
                                  ppmtoascii
===============================================================================

  Convert a PPM image to ASCII with ANSI color graphics terminal controls

  Based on pbmtoascii.
  Copyright (C) 1988, 1992 by Jef Poskanzer.
  Copyright (C) 2010 by Frank Ch. Eigler.

  Permission to use, copy, modify, and distribute this software and its
  documentation for any purpose and without fee is hereby granted, provided
  that the above copyright notice appear in all copies and that both that
  copyright notice and this permission notice appear in supporting
  documentation.  This software is provided "as is" without express or
  implied warranty.
=============================================================================*/

#include "pm_c_util.h"
#include "mallocvar.h"
#include "shhopt.h"
#include "ppm.h"
#include "pm_gamma.h"

/* We use the same algorithm for converting many pixels into a character
   as Pbmtoascii.  See pbmtoascii.c for a full explanation.
*/


#define SQQ '\''
#define BSQ '\\'

/* Bit-map for 1x2 mode:
**     1
**     2
*/
static char const carr1x2[4] = {
/*   0    1    2    3   */
    ' ', '"', 'o', 'M' };

/* Bit-map for 2x4 mode (hex):
**     1  2
**     4  8
**     10 20
**     40 80
** The idea here is first to preserve geometry, then to show density.
*/
#define D08 'M'
#define D07 'H'
#define D06 '&'
#define D05 '$'
#define D04 '?'
static char const carr2x4[256] = {
/*0  1    2   3    4   5    6   7    8   9    A   B    C   D    E   F  */
' ',SQQ, '`','"', '-',SQQ, SQQ,SQQ, '-','`', '`','`', '-','^','^','"',/*00-0F*/
'.',':', ':',':', '|','|', '/',D04, '/','>', '/','>', '~','+','/','*',/*10-1F*/
'.',':', ':',':', BSQ,BSQ, '<','<', '|',BSQ, '|',D04, '~',BSQ,'+','*',/*20-2F*/
'-',':', ':',':', '~',D04, '<','<', '~','>', D04,'>', '=','b','d','#',/*30-3F*/
'.',':', ':',':', ':','!', '/',D04, ':',':', '/',D04, ':',D04,D04,'P',/*40-4F*/
',','i', '/',D04, '|','|', '|','T', '/',D04, '/','7', 'r','}','/','P',/*50-5F*/
',',':', ';',D04, '>',D04, 'S','S', '/',')', '|','7', '>',D05,D05,D06,/*60-6F*/
'v',D04, D04,D05, '+','}', D05,'F', '/',D05, '/',D06, 'p','D',D06,D07,/*70-7F*/
'.',':', ':',':', ':',BSQ, ':',D04, ':',BSQ, '!',D04, ':',D04,D04,D05,/*80-8F*/
BSQ,BSQ, ':',D04, BSQ,'|', '(',D05, '<','%', D04,'Z', '<',D05,D05,D06,/*90-9F*/
',',BSQ, 'i',D04, BSQ,BSQ, D04,BSQ, '|','|', '|','T', D04,BSQ,'4','9',/*A0-AF*/
'v',D04, D04,D05, BSQ,BSQ, D05,D06, '+',D05, '{',D06, 'q',D06,D06,D07,/*B0-BF*/
'_',':', ':',D04, ':',D04, D04,D05, ':',D04, D04,D05, ':',D05,D05,D06,/*C0-CF*/
BSQ,D04, D04,D05, D04,'L', D05,'[', '<','Z', '/','Z', 'c','k',D06,'R',/*D0-DF*/
',',D04, D04,D05, '>',BSQ, 'S','S', D04,D05, 'J',']', '>',D06,'1','9',/*E0-EF*/
'o','b', 'd',D06, 'b','b', D06,'6', 'd',D06, 'd',D07, '#',D07,D07,D08 /*F0-FF*/
};



static const char* rgb2x2x2fg[2][2][2] = {
  {{"\x1b[30m",   /* 000 black */
    "\x1b[34m"},  /* 001 blue */
   {"\x1b[32m",   /* 010 green */
    "\x1b[36m"}}, /* 011 cyan */
  {{"\x1b[31m",   /* 100 red */
    "\x1b[35m"},  /* 101 magenta */
   {"\x1b[33m",   /* 110 yellow */
    "\x1b[37m"}}, /* 111 white */
};



struct cmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    const char * inputFileName;  /* Name of input file */
    unsigned int cellWidth;
    unsigned int cellHeight;
    const char * carr;
};



static void
parseCommandLine(int argc, const char **argv,
                 struct cmdlineInfo * const cmdlineP) {

    optEntry * option_def;
        /* Instructions to OptParseOptions3 on how to parse our options */
    optStruct3 opt;

    unsigned int option_def_index;
    unsigned int dim1x2Spec, dim2x4Spec;

    MALLOCARRAY_NOFAIL(option_def, 100);

    option_def_index = 0;   /* incremented by OPTENTRY */
    OPTENT3(0, "1x2", OPT_FLAG, NULL, &dim1x2Spec, 0);
    OPTENT3(0, "2x4", OPT_FLAG, NULL, &dim2x4Spec, 0);

    opt.opt_table = option_def;
    opt.short_allowed = false;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = false;  /* We have no parms that are negative numbers */

    pm_optParseOptions3(&argc, (char **)argv, opt, sizeof(opt), 0);
        /* Uses and sets argc, argv, and some of *cmdlineP and others. */

    if (dim1x2Spec && dim2x4Spec)
        pm_error("You cannot specify both -1x2 and -2x4");
    else if (dim2x4Spec) {
        cmdlineP->cellWidth  = 2;
        cmdlineP->cellHeight = 4;
        cmdlineP->carr       = carr2x4;
    } else {
        cmdlineP->cellWidth  = 1;
        cmdlineP->cellHeight = 2;
        cmdlineP->carr       = carr1x2;
    }

    if (argc-1 < 1)
        cmdlineP->inputFileName = "-";
    else {
        cmdlineP->inputFileName = argv[1];

        if (argc-1 > 1)
            pm_error("Too many arguments: %u.  The only possible argument "
                     "is the input file name", argc-1);
    }
}



static void
ppmtoascii(pixel * const *    const pixels,
           unsigned int       const cols,
           unsigned int       const rows,
           pixval             const maxval,
           struct cmdlineInfo const cmdline,
           FILE *             const ofP) {

    unsigned int const cellHeight = cmdline.cellHeight;
    unsigned int const cellWidth  = cmdline.cellWidth;
    const char * const carr       = cmdline.carr;
    unsigned int row;

    fprintf(ofP, "\x1b[0m"); /* Clear initial ansi attributes */
    /* TODO: set background to black */

    for (row = 0; row < rows; row += cellHeight) {
        unsigned int col;
        for (col = 0; col < cols; col += cellWidth)	{
            unsigned int const sumthresh = cellWidth * cellHeight * 1.0 / 2;

            float sumr, sumg, sumb;
                /* sum of intensity within cell so far, by component */
            unsigned int b;
            const char * colorstr;
            unsigned int subrow;

            sumr = sumg = sumb = 0;  /* initial value */
            b = 0; /* initial value */

            for (subrow = 0; subrow < cellHeight; ++subrow) {
                unsigned int subcol;
                for (subcol = 0; subcol < cellWidth; ++subcol) {
                    pixel color;
                    pixval value;
                
                    if (row + subrow < rows && col + subcol < cols)
                        color = pixels[row + subrow][col + subcol];
                    else
                        color = ppm_whitepixel (maxval);

                    sumr += pm_ungamma709((float)PPM_GETR(color)/maxval);
                    sumg += pm_ungamma709((float)PPM_GETG(color)/maxval);
                    sumb += pm_ungamma709((float)PPM_GETB(color)/maxval);

                    value = ppm_colorvalue(color);
                    b <<= 1;
                    if (value > maxval/2)
                        b |= 1;
                }
            }
            colorstr = rgb2x2x2fg
                [sumr >= sumthresh]
                [sumg >= sumthresh]
                [sumb >= sumthresh];
            fprintf(ofP, "%s%c", colorstr, carr[b]);
        }
        fprintf(ofP, "\n");
    }
    fprintf(ofP, "\x1b[0m"); /* Clear final ansi attributes */
}



int
main(int argc, const char ** argv) {

    struct cmdlineInfo cmdline;
    FILE * ifP;

    pixval maxval;
    pixel ** pixels;
    int rows, cols;

    pm_proginit(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    ifP = pm_openr(cmdline.inputFileName);
    
    pixels = ppm_readppm(ifP, &cols, &rows, &maxval);

    pm_close(ifP);

    ppmtoascii(pixels, cols, rows, maxval, cmdline, stdout);

    return 0;
}
