/* yuvtoppm.c - convert Abekas YUV bytes into a portable pixmap
**
** by Marc Boucher
** Internet: marc@PostImage.COM
** 
** Based on Example Conversion Program, A60/A64 Digital Video Interface
** Manual, page 69
**
** Uses integer arithmetic rather than floating point for better performance
**
** Copyright (C) 1991 by DHD PostImage Inc.
** Copyright (C) 1987 by Abekas Video Systems Inc.
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



struct CmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    unsigned int cols;
    unsigned int rows;
    const char * inputFileName;  /* Name of input file */
};



static void
parseCommandLine(int argc, const char ** argv,
                 struct CmdlineInfo * const cmdlineP) {

    optEntry * option_def;
        /* Instructions to OptParseOptions3 on how to parse our options */
    optStruct3 opt;

    MALLOCARRAY_NOFAIL(option_def, 100);

    OPTENTINIT;

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = FALSE;  /* We have no parms that are negative numbers */

    pm_optParseOptions3(&argc, (char **)argv, opt, sizeof(opt), 0);
        /* Uses and sets argc, argv, and some of *cmdlineP and others. */

    if (argc-1 < 2)
        pm_error("You need at least two arguments: width and height in "
                 "pixels.  You specified %u", argc-1);
    else {
        int const widthArg  = atoi(argv[1]);
        int const heightArg = atoi(argv[2]);

        if (widthArg < 0)
            pm_error("Negative number for width: %d", widthArg);
        if (heightArg < 0)
            pm_error("Negative number for height: %d", heightArg);

        cmdlineP->cols = widthArg;
        cmdlineP->rows = heightArg;
                 
        if (cmdlineP->cols % 2 != 0)
            pm_error("Number of columns (%u) is odd.  "
                     "A YUV image must have an "
                     "even number of columns.", cmdlineP->cols);

        if (argc-1 < 3)
            cmdlineP->inputFileName = "-";
        else {
            cmdlineP->inputFileName = argv[3];

            if (argc-1 > 3)
                pm_error("Too many arguments: %u.  "
                         "The only possible arguments are "
                         "width, height, and input file name", argc-1);
        }
    }
}



static int
limit(int const x) {

    if (x > 0xffffff)
        return 0xff;
    else if (x <= 0xffff)
        return 0;
    else
        return ((x >> 16) & 0xff);
}



static int
nonneg(int const x) {
/*----------------------------------------------------------------------------
  Raise 'x' to 0 if negative
-----------------------------------------------------------------------------*/
    return x < 0 ? 0 : x;
}



struct Yuv {
/*----------------------------------------------------------------------------
  This is an element of a YUV file.  It describes two side-by-side pixels.

  This is the actual layout of the data in the file (4 bytes).
-----------------------------------------------------------------------------*/
    unsigned char u;
    unsigned char y1;
    unsigned char v;
    unsigned char y2;
};



static void
readYuv(FILE *       const ifP,
        struct Yuv * const yuvP) {

    size_t readCt;

    readCt = fread(yuvP, sizeof(*yuvP), 1, ifP);

    if (readCt != 1) {
        if (feof(ifP))
            pm_error("Premature end of input.");
        else
            pm_error("Error reading input.");
    }
}



static void
yuvtoppm(FILE *       const ifP,
         unsigned int const cols,
         unsigned int const rows,
         FILE *       const ofP) {

    pixval const maxval = 255;

    pixel * pixrow;
    unsigned int row;

    ppm_writeppminit(ofP, cols, rows, maxval, 0);

    pixrow = ppm_allocrow(cols);

    for (row = 0; row < rows; ++row) {
        unsigned int col;
        for (col = 0; col < cols; col += 2) {
            /* Produce two pixels in pixrow[] */
            struct Yuv yuv;
            int     y1, u, v, y2, r, g, b;

            readYuv(ifP, &yuv);

            u = yuv.u - 128;
            y1 = nonneg (yuv.y1 - 16);
            v = yuv.v - 128;
            y2 = nonneg (yuv.y2 - 16);

            r = 104635 * v;
            g = -25690 * u + -53294 * v;
            b = 132278 * u;

            y1 *= 76310;
            y2 *= 76310;

            PPM_ASSIGN(pixrow[col],
                       limit(r + y1), limit(g + y1), limit(b + y1));
            PPM_ASSIGN(pixrow[col + 1],
                       limit(r + y2), limit(g + y2), limit(b + y2));
        }
        ppm_writeppmrow(ofP, pixrow, cols, maxval, 0);
    }

    ppm_freerow(pixrow);

    if (fgetc(ifP) != EOF)
        pm_message("Extraneous data at end of image.");
}



int
main (int argc, const char ** argv) {

    FILE * ifP;
    struct CmdlineInfo cmdline;

    pm_proginit(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    ifP = pm_openr(cmdline.inputFileName);

    yuvtoppm(ifP, cmdline.cols, cmdline.rows, stdout);
    
    pm_close(ifP);
    pm_close(stdout);

    return 0;
}
