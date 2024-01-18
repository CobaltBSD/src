/* xbmtopbm.c - read an X bitmap file and produce a PBM image
**
** Copyright (C) 1988 by Jef Poskanzer.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
*/


#include <assert.h>
#include <string.h>

#include "pm_c_util.h"
#include "mallocvar.h"
#include "nstring.h"
#include "pbm.h"
#include "bitreverse.h"



#define MAX_LINE 500

static unsigned int hexTable[256];
    /* Hexadecimal ASCII translation table.  Constant */

static void
initHexTable(void) {

    unsigned int i;

    for (i = 0; i < 256; ++i)
        hexTable[i] = 256;

    hexTable['0'] =  0;
    hexTable['1'] =  1;
    hexTable['2'] =  2;
    hexTable['3'] =  3;
    hexTable['4'] =  4;
    hexTable['5'] =  5;
    hexTable['6'] =  6;
    hexTable['7'] =  7;
    hexTable['8'] =  8;
    hexTable['9'] =  9;
    hexTable['A'] = 10;
    hexTable['B'] = 11;
    hexTable['C'] = 12;
    hexTable['D'] = 13;
    hexTable['E'] = 14;
    hexTable['F'] = 15;
    hexTable['a'] = 10;
    hexTable['b'] = 11;
    hexTable['c'] = 12;
    hexTable['d'] = 13;
    hexTable['e'] = 14;
    hexTable['f'] = 15;
}



static void
parseWidthHeightLine(const char *   const line,
                     bool *         const gotWidthP,
                     unsigned int * const widthP,
                     bool *         const gotHeightP,
                     unsigned int * const heightP) {

    int rc;
    char nameAndType[MAX_LINE];
    unsigned int value;

    rc = sscanf(line, "#define %s %u", nameAndType, &value);
    if (rc == 2) {
        const char * underscorePos = strrchr(nameAndType, '_');
        const char * type;
        if (underscorePos)
            type = underscorePos + 1;
        else
            type = nameAndType;
        if (streq(type, "width")) {
            *gotWidthP = TRUE;
            *widthP = value;
        } else if (streq(type, "height")) {
            *gotHeightP = TRUE;
            *heightP = value;
        }
    }
}



static void
parseDeclaration(const char * const line,
                 bool *       const isDeclarationP,
                 bool *       const version10P) {
/*----------------------------------------------------------------------------
   Parse the XBM file line 'line' as the first line of the data structure
   declaration, i.e. the one that looks like this:

      static unsigned char myImage = {

   Return as *isDeclarationP whether the line actually is such a line,
   and if so, return as nameAndType what the variable name ('myImage'
   in the example) is and as *version10P whether it's of the type used
   by X10 as opposed to X11.
-----------------------------------------------------------------------------*/
    char nameAndType[MAX_LINE];
    int rc;
        
    rc = sscanf(line, "static short %s = {", nameAndType);
    if (rc == 1) {
        *version10P     = TRUE;
        *isDeclarationP = TRUE;
    } else {
        int rc;
        rc = sscanf(line, "static char %s = {", nameAndType);
        if (rc == 1) {
            *version10P     = FALSE;
            *isDeclarationP = TRUE;
        } else {
            int rc;
            rc = sscanf(line, "static unsigned char %s = {", nameAndType);
            if (rc == 1) {
                *version10P     = FALSE;
                *isDeclarationP = TRUE;
            } else
                *isDeclarationP = FALSE;
        }
    }
}



static void
getXbmHeader(FILE *         const ifP,
             unsigned int * const widthP,
             unsigned int * const heightP,
             bool *         const version10P) {

    bool foundDeclaration;
        /* In scanning through the bitmap file, we have found the first
           line of the C declaration of the array (the "static char ..."
           or whatever line)
        */
    bool gotWidth, gotHeight;
        /* We found the line in the bitmap file that gives the width
           or height, respectively, of the image (and have set
           *widthP or *heightP to the value in it).
        */

    bool eof;
        /* We've encountered end of file while searching file */

    gotWidth = FALSE;
    gotHeight = FALSE;
    foundDeclaration = FALSE;    /* Haven't found it yet; haven't even looked*/
    eof = FALSE;                 /* Haven't encountered end of file yet */

    while (!foundDeclaration && !eof) {
        char * rc;
        char line[MAX_LINE];

        rc = fgets(line, MAX_LINE, ifP);
        if (rc == NULL)
            eof = TRUE;
        else {
            if (strlen(line) == MAX_LINE - 1)
                pm_error("A line in the input file is %u characters long.  "
                         "%u is the maximum we can handle",
                         (unsigned)strlen(line), MAX_LINE-1);

            parseWidthHeightLine(line, &gotWidth, widthP, &gotHeight, heightP);

            parseDeclaration(line, &foundDeclaration, version10P);
        }
    }

    if (!foundDeclaration) 
        pm_error("Unable to find a line in the file containing the start "
                 "of C array declaration (\"static char\" or whatever)");

    if (!gotWidth)
        pm_error("Unable to find the #define statement that gives the "
                 "width of the image, before the data structure "
                 "declaration.");
    if (!gotHeight)
        pm_error("Unable to find the #define statement that gives the "
                 "height of the image, before the data structure "
                 "declaration.");
}



static void
getHexByte(FILE *         const ifP,
           unsigned int * const valueP) {

    int c1, c2;
    unsigned int value;

    c1 = getc(ifP);
    c2 = getc(ifP);
    if (c1 == EOF || c2 == EOF)
        pm_error("EOF / read error");

    assert(c1 >= 0); assert(c1 < 256);
    assert(c2 >= 0); assert(c2 < 256);
    
    value = (hexTable[c1] << 4) + hexTable[c2];
    if (value >= 256)
        pm_error("Invalid XBM input.  What should be a two digit "
                 "hexadecimal cipher is instead '%c%c'", c1, c2);

    *valueP = value;
}


                     
static void
readX10Raster(FILE *          const ifP,
              unsigned int    const rasterLength,
              unsigned char * const data,
              unsigned int    const bytesPerLine,
              bool            const mustPad) {

    unsigned int bytesDone;
    unsigned char * p;

    for (bytesDone = 0, p = &data[0];
         bytesDone < rasterLength;
         bytesDone += 2) {

        unsigned int value1;
        unsigned int value2;

        while (getc(ifP) != 'x') {}  /* Read up through the 'x' in 0x1234 */

        getHexByte(ifP, &value1);  /* Read first two hex digits */
        getHexByte(ifP, &value2);  /* Read last two hex digits */

        *p++ = value2;

        if (!mustPad || ((bytesDone + 2) % bytesPerLine))
            *p++ = value1;
    }
}



static void
readX11Raster(FILE * const ifP,
              unsigned int const rasterLength,
              unsigned char * data) {

    unsigned int i;

    for (i = 0; i < rasterLength; ++i) {
        unsigned int value;
        int c;

        /* Read up through the 'x' in 0x12 */
        while ((c = getc(ifP))) {
            if (c == EOF)
                pm_error("EOF where 0x expected");
            else if (toupper(c) == 'X')
                break;
        }

        getHexByte(ifP, &value);  /* Read the two hex digits */

        assert(value < 256);

        data[i] = value;
    }
}



static void
readBitmapFile(FILE *           const ifP,
               unsigned int *   const widthP,
               unsigned int *   const heightP,
               unsigned char ** const dataP) {

    bool version10;
    unsigned int rasterLength;
    unsigned int width, height;
    unsigned char * data;

    unsigned int bytesPerLine;
    bool mustPad;

    getXbmHeader(ifP, &width, &height, &version10);

    *widthP = width;
    *heightP = height;

    mustPad = (width % 16 >= 1 && width % 16 <= 8 && version10);

    bytesPerLine = (width + 7) / 8 + (mustPad ? 1 : 0);
    
    rasterLength = bytesPerLine * height;

    MALLOCARRAY(data, rasterLength);
    if (data == NULL)
        pm_error("Unable to allocate memory for the %u-byte raster",
                 rasterLength);

    if (version10)
        readX10Raster(ifP, rasterLength, data, bytesPerLine, mustPad);
    else
        readX11Raster(ifP, rasterLength, data);

    *dataP = data;
}



int
main(int    argc,
     char * argv[]) {

    FILE * ifP;
    bit * bitrow;
    unsigned int rows, cols;
    unsigned int row;
    unsigned char * data;
    const char * inputFileName;
    unsigned char * p;
        /* Cursor in raster data data[] */
    
    initHexTable();

    pbm_init(&argc, argv);

    if (argc-1 > 1)
        pm_error("The only possible argument is the input file name.  "
                 "You specified %u arguments", argc-1);
    
    if (argc-1 > 0)
        inputFileName = argv[1];
    else
        inputFileName = "-";

    ifP = pm_openr(inputFileName);

    readBitmapFile(ifP, &cols, &rows, &data);

    pm_close(ifP);

    pbm_writepbminit(stdout, cols, rows, 0);
    bitrow = pbm_allocrow_packed(cols);

    p = &data[0];  /* Start at beginning of raster */

    for (row = 0; row < rows; ++row) {
        unsigned int const bytesPerRow = pbm_packed_bytes(cols);
        unsigned int i;
        
        for (i = 0; i < bytesPerRow; ++i)
            bitrow[i] = bitreverse[*p++];

        pbm_cleanrowend_packed(bitrow, cols);
        pbm_writepbmrow_packed(stdout, bitrow, cols, 0);
    }

    pbm_freerow(bitrow);
    free(data);
    pm_close(stdout);

    return 0;
}

/*  CHANGE HISTORY:

  99.09.08 bryanh    Recognize "static unsigned char" declaration.

  06.10 (afu)
   Changed bitrow from plain to raw, write function from pbm_writepbmrow()
   to pbm_writepbmrow_packed().
   Retired bitwise transformation functions.

*/

