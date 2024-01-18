/* ppmtorgb3.c - separate a PPM image into 3 PGM images.
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

#include <string.h>
#include "pm_c_util.h"
#include "mallocvar.h"
#include "nstring.h"
#include "ppm.h"
#include "pgm.h"



struct Cmdline {
    const char * inputFileName;
};



static const char *
strippedOfExtension(const char * const arg) {

    char * buffer;

    MALLOCARRAY(buffer, strlen(arg) + 1);

    strcpy(buffer, arg);

    {
        char * const dotPos = strrchr(buffer, '.');
        if (dotPos)
            *dotPos = '\0';
    }
    return buffer;
}



static void
openComponentOut(const char * const suffix,
                 const char * const baseName,
                 FILE **      const fpP) {

    const char * fileName;

    pm_asprintf(&fileName, "%s.%s", baseName, suffix);

    *fpP = pm_openw(fileName);

    pm_strfree(fileName);
}



int
main(int argc, const char ** argv) {

    FILE * ifP;
    FILE * redfP;
    FILE * grnfP;
    FILE * blufP;
    pixel * pixelrow;
    gray * grayrow;
    int rows, cols;
    int format;
    unsigned int row;
    pixval maxval;
    struct Cmdline cmdline;
    const char * baseFileName;

    pm_proginit(&argc, argv);

    if (argc-1 > 1)
        pm_error("Too many arguments (%u).  The only possible argument "
                 "is the input file name", argc-1);

    if (argc-1 < 1)
        cmdline.inputFileName = "-";
    else
        cmdline.inputFileName = argv[1];

    ifP = pm_openr(cmdline.inputFileName);

    if (streq(cmdline.inputFileName, "-"))
        baseFileName = strdup("noname");
    else
        baseFileName = strippedOfExtension(cmdline.inputFileName);

    ppm_readppminit(ifP, &cols, &rows, &maxval, &format);

    pixelrow = ppm_allocrow(cols);

    openComponentOut("red", baseFileName, &redfP);
    openComponentOut("grn", baseFileName, &grnfP);
    openComponentOut("blu", baseFileName, &blufP);

    pgm_writepgminit(redfP, cols, rows, maxval, 0);
    pgm_writepgminit(grnfP, cols, rows, maxval, 0);
    pgm_writepgminit(blufP, cols, rows, maxval, 0);

    grayrow = pgm_allocrow(cols);

    for (row = 0; row < rows; ++row) {
        unsigned int col;

        ppm_readppmrow(ifP, pixelrow, cols, maxval, format);

        for (col = 0; col < cols; ++col)
            grayrow[col] = PPM_GETR(pixelrow[col]);

        pgm_writepgmrow(redfP, grayrow, cols, maxval, 0);

        for (col = 0; col < cols; ++col)
            grayrow[col] = PPM_GETG(pixelrow[col]);

        pgm_writepgmrow(grnfP, grayrow, cols, maxval, 0);

        for (col = 0; col < cols; ++col)
            grayrow[col] = PPM_GETB(pixelrow[col]);

        pgm_writepgmrow(blufP, grayrow, cols, maxval, 0);
    }

    pgm_freerow(grayrow);
    ppm_freerow(pixelrow);
    pm_strfree(baseFileName);
    pm_close(ifP);
    pm_close(blufP);
    pm_close(grnfP);
    pm_close(redfP);

    return 0;
}



