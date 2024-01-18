/* pnmcrop.c - crop a portable anymap
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

/* IDEA FOR EFFICIENCY IMPROVEMENT:

   If we have to read the input into a regular file because it is not
   seekable (a pipe), find the borders as we do the copy, so that we
   do 2 passes through the file instead of 3.  Also find the background
   color in that pass to save yet another pass with -sides.
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#include "pm_c_util.h"
#include "pnm.h"
#include "shhopt.h"
#include "mallocvar.h"

enum bg_choice {BG_BLACK, BG_WHITE, BG_DEFAULT, BG_SIDES};

typedef enum { LEFT = 0, RIGHT = 1, TOP = 2, BOTTOM = 3} edgeLocation;

static const char * const edgeName[] = {
    "left",
    "right",
    "top",
    "bottom"
};

typedef struct {
    unsigned int size[4];
} borderSet;

typedef enum {
    /* A position in a PNM image file stream */
    FILEPOS_BEG,
        /* Immediately before the raster */
    FILEPOS_END
        /* Immediately after the raster */
} imageFilePos;

struct cmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    const char * inputFilespec;
    enum bg_choice background;
    bool wantCrop[4];
        /* User wants crop of left, right, top, bottom, resp. */
    unsigned int verbose;
    unsigned int margin;
    const char * borderfile;  /* NULL if none */
};



static void
parseCommandLine(int argc, const char ** argv,
                 struct cmdlineInfo *cmdlineP) {
/*----------------------------------------------------------------------------
   Note that the file spec array we return is stored in the storage that
   was passed to us as the argv array.
-----------------------------------------------------------------------------*/
    optEntry * option_def;
        /* Instructions to OptParseOptions3 on how to parse our options.
         */
    optStruct3 opt;

    unsigned int blackOpt, whiteOpt, sidesOpt;
    unsigned int marginSpec, borderfileSpec;
    unsigned int leftOpt, rightOpt, topOpt, bottomOpt;
    
    unsigned int option_def_index;

    MALLOCARRAY_NOFAIL(option_def, 100);

    option_def_index = 0;   /* incremented by OPTENT3 */
    OPTENT3(0, "black",      OPT_FLAG, NULL, &blackOpt,            0);
    OPTENT3(0, "white",      OPT_FLAG, NULL, &whiteOpt,            0);
    OPTENT3(0, "sides",      OPT_FLAG, NULL, &sidesOpt,            0);
    OPTENT3(0, "left",       OPT_FLAG, NULL, &leftOpt,             0);
    OPTENT3(0, "right",      OPT_FLAG, NULL, &rightOpt,            0);
    OPTENT3(0, "top",        OPT_FLAG, NULL, &topOpt,              0);
    OPTENT3(0, "bottom",     OPT_FLAG, NULL, &bottomOpt,           0);
    OPTENT3(0, "verbose",    OPT_FLAG, NULL, &cmdlineP->verbose,   0);
    OPTENT3(0, "margin",     OPT_UINT,   &cmdlineP->margin,    
            &marginSpec,     0);
    OPTENT3(0, "borderfile", OPT_STRING, &cmdlineP->borderfile,
            &borderfileSpec, 0);

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = FALSE;  /* We have no parms that are negative numbers */

    pm_optParseOptions3(&argc, (char **)argv, opt, sizeof(opt), 0);
        /* Uses and sets argc, argv, and some of *cmdlineP and others. */
        
    free(option_def);

    if (argc-1 == 0)
        cmdlineP->inputFilespec = "-";  /* stdin */
    else if (argc-1 == 1)
        cmdlineP->inputFilespec = argv[1];
    else 
        pm_error("Too many arguments (%d).  "
                 "Only need one: the input filespec", argc-1);

    if (blackOpt && whiteOpt)
        pm_error("You cannot specify both -black and -white");
    else if (sidesOpt &&( blackOpt || whiteOpt ))
        pm_error("You cannot specify both -sides and either -black or -white");
    else if (blackOpt)
        cmdlineP->background = BG_BLACK;
    else if (whiteOpt)
        cmdlineP->background = BG_WHITE;
    else if (sidesOpt)
        cmdlineP->background = BG_SIDES;
    else
        cmdlineP->background = BG_DEFAULT;

    if (!leftOpt && !rightOpt && !topOpt && !bottomOpt) {
        unsigned int i;
        for (i = 0; i < 4; ++i)
            cmdlineP->wantCrop[i] = true;
    } else {
        cmdlineP->wantCrop[LEFT]   = !!leftOpt;
        cmdlineP->wantCrop[RIGHT]  = !!rightOpt;
        cmdlineP->wantCrop[TOP]    = !!topOpt;
        cmdlineP->wantCrop[BOTTOM] = !!bottomOpt;
    }
    if (!marginSpec)
        cmdlineP->margin = 0;

    if (!borderfileSpec)
        cmdlineP->borderfile = NULL;
}



typedef struct {
/*----------------------------------------------------------------------------
   This describes a cropping operation of a single border (top, bottom,
   left, or right).

   Our definition of cropping includes padding to make a margin as well as
   chopping stuff out.
-----------------------------------------------------------------------------*/
    unsigned int removeSize;
        /* Size in pixels of the border to remove */
    unsigned int padSize;
        /* Size in pixels of the border to add */
} cropOp;


typedef struct {
    cropOp op[4];
} cropSet;



static xel
background3Corners(FILE * const ifP,
                   int    const rows,
                   int    const cols,
                   pixval const maxval,
                   int    const format) {
/*----------------------------------------------------------------------------
  Read in the whole image, and check all the corners to determine the
  background color.  This is a quite reliable way to determine the
  background color.

  Expect the file to be positioned to the start of the raster, and leave
  it positioned arbitrarily.
----------------------------------------------------------------------------*/
    int row;
    xel ** xels;
    xel background;   /* our return value */

    xels = pnm_allocarray(cols, rows);

    for (row = 0; row < rows; ++row)
        pnm_readpnmrow( ifP, xels[row], cols, maxval, format );

    background = pnm_backgroundxel(xels, cols, rows, maxval, format);

    pnm_freearray(xels, rows);

    return background;
}



static xel
background2Corners(FILE * const ifP,
                   int    const cols,
                   pixval const maxval,
                   int    const format) {
/*----------------------------------------------------------------------------
  Look at just the top row of pixels and determine the background
  color from the top corners; often this is enough to accurately
  determine the background color.

  Expect the file to be positioned to the start of the raster, and leave
  it positioned arbitrarily.
----------------------------------------------------------------------------*/
    xel *xelrow;
    xel background;   /* our return value */
    
    xelrow = pnm_allocrow(cols);

    pnm_readpnmrow(ifP, xelrow, cols, maxval, format);

    background = pnm_backgroundxelrow(xelrow, cols, maxval, format);

    pnm_freerow(xelrow);

    return background;
}



static xel
computeBackground(FILE *         const ifP,
                  int            const cols,
                  int            const rows,
                  xelval         const maxval,
                  int            const format,
                  enum bg_choice const backgroundChoice) {
/*----------------------------------------------------------------------------
   Determine what color is the background color of the image in file
   *ifP, which is described by 'cols', 'rows', 'maxval', and 'format'.

   'backgroundChoice' is the method we are to use in determining the
   background color.
   
   Expect the file to be positioned to the start of the raster, and leave
   it positioned arbitrarily.
-----------------------------------------------------------------------------*/
    xel background;  /* Our return value */
    
    switch (backgroundChoice) {
    case BG_WHITE:
        background = pnm_whitexel(maxval, format);
        break;
    case BG_BLACK:
        background = pnm_blackxel(maxval, format);
        break;
    case BG_SIDES: 
        background = 
            background3Corners(ifP, rows, cols, maxval, format);
        break;
    case BG_DEFAULT: 
        background = 
            background2Corners(ifP, cols, maxval, format);
        break;
    }

    return(background);
}



static void
findBordersInImage(FILE *         const ifP,
                   unsigned int   const cols,
                   unsigned int   const rows,
                   xelval         const maxval,
                   int            const format,
                   xel            const backgroundColor,
                   bool *         const hasBordersP,
                   borderSet *    const borderSizeP) {
/*----------------------------------------------------------------------------
   Find the left, right, top, and bottom borders in the image 'ifP'.
   Return their sizes in pixels as borderSize[n].
   
   Iff the image is all background, *hasBordersP == FALSE.

   Expect the input file to be positioned to the beginning of the
   image raster and leave it positioned arbitrarily.
-----------------------------------------------------------------------------*/
    xel * xelrow;        /* A row of the input image */
    int row;
    bool gottop;
    int left, right, bottom, top;
        /* leftmost, etc. nonbackground pixel found so far; -1 for none */

    xelrow = pnm_allocrow(cols);
    
    left   = cols;  /* initial value */
    right  = -1;    /* initial value */
    top    = rows;  /* initial value */
    bottom = -1;    /* initial value */

    gottop = FALSE;
    for (row = 0; row < rows; ++row) {
        int col;
        int thisRowLeft;
        int thisRowRight;

        pnm_readpnmrow(ifP, xelrow, cols, maxval, format);
        
        col = 0;
        while (col < cols && PNM_EQUAL(xelrow[col], backgroundColor))
            ++col;
        thisRowLeft = col;

        col = cols-1;
        while (col >= thisRowLeft && PNM_EQUAL(xelrow[col], backgroundColor))
            --col;
        thisRowRight = col + 1;

        if (thisRowLeft < cols) {
            /* This row is not entirely background */
            
            left  = MIN(thisRowLeft,  left);
            right = MAX(thisRowRight, right);

            if (!gottop) {
                gottop = TRUE;
                top = row;
            }
            bottom = row + 1;   /* New candidate */
        }
    }
    
    free(xelrow);

    if (right == -1)
        *hasBordersP = FALSE;
    else {
        *hasBordersP = TRUE;
        assert(right <= cols); assert(bottom <= rows);
        borderSizeP->size[LEFT]   = left - 0;
        borderSizeP->size[RIGHT]  = cols - right;
        borderSizeP->size[TOP]    = top - 0;
        borderSizeP->size[BOTTOM] = rows - bottom;
    }
}



static void
analyzeImage(FILE *         const ifP,
             unsigned int   const cols,
             unsigned int   const rows,
             xelval         const maxval,
             int            const format,
             enum bg_choice const backgroundReq,
             imageFilePos   const newFilePos,
             xel *          const backgroundColorP,
             bool *         const hasBordersP,
             borderSet *    const borderSizeP) {
/*----------------------------------------------------------------------------
   Analyze the PNM image on file stream *ifP to determine its borders
   and the color of those borders (the assumed background color).

   Return as *backgroundColorP the background color.

   Return as *borderSizeP the set of border sizes (one for each of the
   four edges).  But iff there are no borders, don't return anything as
   *borderSizeP and return *hasBordersP == false.

   Expect *ifP to be positioned right after the header and seekable.
   Return with it positioned either before or after the raster, as
   requested by 'newFilePos'.
-----------------------------------------------------------------------------*/
    pm_filepos rasterpos;
    xel background;

    pm_tell2(ifP, &rasterpos, sizeof(rasterpos));

    background = computeBackground(ifP, cols, rows, maxval, format,
                                   backgroundReq);

    pm_seek2(ifP, &rasterpos, sizeof(rasterpos));

    findBordersInImage(ifP, cols, rows, maxval, format, 
                       background, hasBordersP, borderSizeP);

    if (newFilePos == FILEPOS_BEG)
        pm_seek2(ifP, &rasterpos, sizeof(rasterpos));

    *backgroundColorP = background;
}



static const char *
ending(unsigned int const n) {

    return n > 1 ? "s" : "";
}



static void
reportCroppingParameters(cropSet const crop) {

    unsigned int i;

    for (i = 0; i < 4; ++i) {
        if (crop.op[i].removeSize == 0 && crop.op[i].padSize == 0)
            pm_message("Not cropping %s edge", edgeName[i]);
        else {
            if (crop.op[i].padSize > 0)
                pm_message("Adding %u pixel%s to the %s border",
                           crop.op[i].padSize, ending(crop.op[i].padSize),
                           edgeName[i]);
            if (crop.op[i].removeSize > 0)
                pm_message("Cropping %u pixel%s from the %s border",
                           crop.op[i].removeSize,
                           ending(crop.op[i].removeSize),
                           edgeName[i]);
        }
    }
}




static void
fillRow(xel *        const xelrow,
        unsigned int const cols,
        xel          const color) {

    unsigned int col;

    for (col = 0; col < cols; ++col)
        xelrow[col] = color;
}



static void
readOffBorderNonPbm(unsigned int const height,
                    FILE *       const ifP,
                    unsigned int const cols,
                    xelval       const maxval,
                    int          const format) {

    xel * xelrow;
    unsigned int i;

    xelrow = pnm_allocrow(cols);

    for (i = 0; i < height; ++i)
        pnm_readpnmrow(ifP, xelrow, cols, maxval, format);

    pnm_freerow(xelrow);
}



static void
outputNewBorderNonPbm(unsigned int const height,
                      unsigned int const width,
                      xel          const color,
                      FILE *       const ofP,
                      xelval       const maxval,
                      int          const format) {
/*----------------------------------------------------------------------------
   Output to 'ofP' a horizontal border (i.e. top or bottom)
   of color 'backgroundColor', height 'height', width 'width'.
-----------------------------------------------------------------------------*/
    xel * xelrow;
    unsigned int i;

    xelrow = pnm_allocrow(width);

    fillRow(xelrow, width, color);

    for (i = 0; i < height; ++i)
        pnm_writepnmrow(ofP, xelrow, width, maxval, format, 0);
    
    pnm_freerow(xelrow);
}



static void
writeCroppedNonPbm(FILE *       const ifP,
                   unsigned int const cols,
                   unsigned int const rows,
                   xelval       const maxval,
                   int          const format,
                   cropSet      const crop,
                   xel          const backgroundColor,
                   FILE *       const ofP) {

    /* In order to do cropping, padding or both at the same time, we have
       a rather complicated row buffer:

       xelrow[] is both the input and the output buffer.  So it contains
       the foreground pixels, the original border pixels, and the new
       border pixels.

       We're calling foreground everything that isn't being cropped out
       or padded in.  So the "foreground" may include some of what is really
       a background border in the original image -- because the user can
       choose to retain part of that border as a margin.

       The foreground pixels are in the center of the
       buffer, starting at Column 'foregroundLeft' and going to
       'foregroundRight'.

       There is space to the left of that for the larger of the input
       left border and the output left border.

       Similarly, there is space to the right of the foreground pixels
       for the larger of the input right border and the output right
       border.

       We have to read an entire row, including the pixels we'll be
       leaving out of the output, so we pick a starting location in
       the buffer that lines up the first foreground pixel at
       'foregroundLeft'.

       When we output the row, we pick a starting location in the 
       buffer that includes the proper number of left border pixels
       before 'foregroundLeft'.

       That's for the middle rows.  For the top and bottom, we just use
       the left portion of xelrow[], starting at 0.

       This is the general case.  Enhancement for PBM appears below.
       (Logic works for PBM).
    */

    unsigned int const foregroundCols =
        cols - crop.op[LEFT].removeSize - crop.op[RIGHT].removeSize;
    unsigned int const outputCols     = 
        foregroundCols + crop.op[LEFT].padSize + crop.op[RIGHT].padSize;
    unsigned int const foregroundRows =
        rows - crop.op[TOP].removeSize - crop.op[BOTTOM].removeSize;
    unsigned int const outputRows     =
        foregroundRows + crop.op[TOP].padSize + crop.op[BOTTOM].padSize;

    unsigned int const foregroundLeft  =
        MAX(crop.op[LEFT].removeSize, crop.op[LEFT].padSize);
        /* Index into xelrow[] of leftmost pixel of foreground */
    unsigned int const foregroundRight = foregroundLeft + foregroundCols;
        /* Index into xelrow[] just past rightmost pixel of foreground */

    unsigned int const allocCols =
        foregroundRight + MAX(crop.op[RIGHT].removeSize,
                              crop.op[RIGHT].padSize);

    xel * xelrow;
    unsigned int i;

    pnm_writepnminit(ofP, outputCols, outputRows, maxval, format, 0);

    xelrow = pnm_allocrow(allocCols);

    readOffBorderNonPbm(crop.op[TOP].removeSize, ifP, cols, maxval, format);

    outputNewBorderNonPbm(crop.op[TOP].padSize, outputCols, backgroundColor,
                          ofP, maxval, format);

    /* Set left border pixels */
    fillRow(&xelrow[foregroundLeft - crop.op[LEFT].padSize],
            crop.op[LEFT].padSize,
            backgroundColor);

    /* Set right border pixels */
    fillRow(&xelrow[foregroundRight], crop.op[RIGHT].padSize, backgroundColor);

    /* Read and output foreground rows */
    for (i = 0; i < foregroundRows; ++i) {
 
        /* Read foreground pixels */
        pnm_readpnmrow(ifP,
                       &(xelrow[foregroundLeft - crop.op[LEFT].removeSize]),
                       cols, maxval, format);
        
        pnm_writepnmrow(ofP,
                        &(xelrow[foregroundLeft - crop.op[LEFT].padSize]),
                        outputCols, maxval, format, 0);
    }

    readOffBorderNonPbm(crop.op[BOTTOM].removeSize, ifP, cols, maxval, format);
    
    outputNewBorderNonPbm(crop.op[BOTTOM].padSize, outputCols,
                          backgroundColor,
                          ofP, maxval, format);

    pnm_freerow(xelrow);
}



static void
fillRowPBM(unsigned char * const bitrow,
           unsigned int    const cols,
           unsigned int    const blackWhite) {
/*----------------------------------------------------------------------------
   Fill the packed PBM row buffer bitrow[] with 'cols' columns of
   black or white: black if 'blackWhite' is 1; white if it is '0'.
   'blackWhite' cannot be anything else.
-----------------------------------------------------------------------------*/
    unsigned int const colChars = pbm_packed_bytes(cols);
    unsigned int i;

    assert(blackWhite == 0 || blackWhite == 1);
    
    for (i = 0; i < colChars; ++i)
        bitrow[i] = blackWhite * 0xff;
        
    if (cols % 8 > 0)
        bitrow[colChars-1] <<= 8 - cols % 8;
}



static void
readOffBorderPbm(unsigned int const height,
                 FILE *       const ifP,
                 unsigned int const cols,
                 int          const format) {

    unsigned char * bitrow;
    unsigned int i;

    bitrow = pbm_allocrow_packed(cols);

    for (i = 0; i < height; ++i)
        pbm_readpbmrow_packed(ifP, bitrow, cols, format);

    pbm_freerow_packed(bitrow);
}



static void
outputNewBorderPbm(unsigned int const height,
                   unsigned int const width,
                   unsigned int const blackWhite,
                   FILE *       const ofP) {
/*----------------------------------------------------------------------------
   Output to 'ofP' a horizontal border (i.e. top or bottom)
   of height 'height', width 'width'.  Make it black if 'blackWhite' is
   1; white if 'blackWhite' is 0.  'blackWhite' can't be anything else.
-----------------------------------------------------------------------------*/
    unsigned char * bitrow;
    unsigned int i;

    bitrow = pbm_allocrow_packed(width);

    fillRowPBM(bitrow, width, blackWhite);

    for (i = 0; i < height; ++i)
        pbm_writepbmrow_packed(ofP, bitrow, width, 0);
    
    pbm_freerow_packed(bitrow);
}



static void
writeCroppedPBM(FILE *       const ifP,
                unsigned int const cols,
                unsigned int const rows,
                int          const format,
                cropSet      const crop,
                xel          const backgroundColor,
                FILE *       const ofP) {
    
    /* See comments for writeCroppedNonPBM(), which uses identical logic flow. 
       Uses pbm functions instead of general pnm functions.
    */

    unsigned int const foregroundCols =
        cols - crop.op[LEFT].removeSize - crop.op[RIGHT].removeSize;
    unsigned int const outputCols     = 
        foregroundCols + crop.op[LEFT].padSize + crop.op[RIGHT].padSize;
    unsigned int const foregroundRows =
        rows - crop.op[TOP].removeSize - crop.op[BOTTOM].removeSize;
    unsigned int const outputRows     =
        foregroundRows + crop.op[TOP].padSize + crop.op[BOTTOM].padSize;

    unsigned int const foregroundLeft  =
        MAX(crop.op[LEFT].removeSize, crop.op[LEFT].padSize);
    unsigned int const foregroundRight = foregroundLeft + foregroundCols;

    unsigned int const allocCols =
        foregroundRight + 
        MAX(crop.op[RIGHT].removeSize, crop.op[RIGHT].padSize);

    unsigned int const backgroundBlackWhite =
        PNM_EQUAL(backgroundColor, pnm_whitexel(1, PBM_TYPE)) ? 0: 1;

    unsigned int const readOffset    =
        foregroundLeft - crop.op[LEFT].removeSize;
    unsigned int const writeOffset   = foregroundLeft - crop.op[LEFT].padSize;
    unsigned int const lastWriteChar = writeOffset/8 + (outputCols-1)/8;
    unsigned char * bitrow;
    unsigned int i;
    
    pbm_writepbminit(ofP, outputCols, outputRows, 0);

    bitrow = pbm_allocrow_packed(allocCols);

    readOffBorderPbm(crop.op[TOP].removeSize, ifP, cols, format);

    outputNewBorderPbm(crop.op[TOP].padSize, outputCols, backgroundBlackWhite,
                       ofP);

    /* Prepare padding: left and/or right */
    fillRowPBM(bitrow, allocCols, backgroundBlackWhite);

    /* Read and output foreground rows */
    for (i = 0; i < foregroundRows; ++i) {
        /* Read foreground pixels */
        pbm_readpbmrow_bitoffset(ifP, bitrow, cols, format, readOffset);
  
        pbm_writepbmrow_bitoffset(ofP,
                                  bitrow, outputCols, format, writeOffset);
                              
        /* If there is right-side padding, repair the write buffer
           distorted by pbm_writepbmrow_bitoffset() 
           (No need to mend any left-side padding)
        */
        if (crop.op[RIGHT].padSize > 0)    
            bitrow[lastWriteChar] = backgroundBlackWhite * 0xff;
    }

    readOffBorderPbm(crop.op[BOTTOM].removeSize, ifP, cols, format);

    outputNewBorderPbm(crop.op[BOTTOM].padSize, outputCols,
                       backgroundBlackWhite,
                       ofP);

    pbm_freerow_packed(bitrow);
}



static void
determineCrops(struct cmdlineInfo const cmdline,
               borderSet *        const oldBorderSizeP,
               cropSet *          const cropP) {

    edgeLocation i;

    for (i = 0; i < 4; ++i) {
        if (cmdline.wantCrop[i]) {
            if (oldBorderSizeP->size[i] > cmdline.margin) {
                cropP->op[i].removeSize =
                    oldBorderSizeP->size[i] - cmdline.margin;
                cropP->op[i].padSize    = 0;
            } else {
                cropP->op[i].removeSize = 0;
                cropP->op[i].padSize    =
                    cmdline.margin - oldBorderSizeP->size[i];
            }
        } else {
            cropP->op[i].removeSize = 0;
            cropP->op[i].padSize    = 0;
        }
    }
}



static void
validateComputableSize(unsigned int const cols,
                       unsigned int const rows,
                       cropSet      const crop) {

    double const newcols =
        (double)cols +
        (double)crop.op[LEFT].padSize + (double)crop.op[RIGHT].padSize;

    double const newrows =
        (double)rows +
        (double)crop.op[TOP].padSize + (double)crop.op[BOTTOM].padSize;

    if (newcols > INT_MAX)
       pm_error("Output width too large: %.0f.", newcols);
    if (newrows > INT_MAX)
       pm_error("Output height too large: %.0f.", newrows);
}



static void
cropOneImage(struct cmdlineInfo const cmdline,
             FILE *             const ifP,
             FILE *             const bdfP,
             FILE *             const ofP) {
/*----------------------------------------------------------------------------
   Crop the image to which the stream *ifP is presently positioned
   and write the results to *ofP.  If bdfP is non-null, use the image
   to which stream *bdfP is presently positioned as the borderfile
   (the file that tells us where the existing borders are in the input
   image).  Leave *ifP and *bdfP positioned after the image.

   Both files are seekable.
-----------------------------------------------------------------------------*/
    xelval maxval, bmaxval;
    int format, bformat;
    int rows, cols, brows, bcols;
    bool hasBorders;
    borderSet oldBorder;
        /* The sizes of the borders in the input image */
    cropSet crop;
        /* The crops we have to do on each side */
    xel background;

    pnm_readpnminit(ifP, &cols, &rows, &maxval, &format);

    if (bdfP)
        pnm_readpnminit(bdfP, &bcols, &brows, &bmaxval, &bformat);

    if (bdfP)
        analyzeImage(bdfP, bcols, brows, bmaxval, bformat, cmdline.background,
                     FILEPOS_END,
                     &background, &hasBorders, &oldBorder);
    else
        analyzeImage(ifP, cols, rows, maxval, format, cmdline.background,
                     FILEPOS_BEG,
                     &background, &hasBorders, &oldBorder);

    if (cmdline.verbose) {
        pixel const backgroundPixel = pnm_xeltopixel(background, format);
        pm_message("Background color is %s", 
                   ppm_colorname(&backgroundPixel, maxval, TRUE /*hexok*/));
    }
    if (!hasBorders)
        pm_error("The image is entirely background; "
                 "there is nothing to crop.");

    determineCrops(cmdline, &oldBorder, &crop);

    validateComputableSize(cols, rows, crop);

    if (cmdline.verbose) 
        reportCroppingParameters(crop);

    if (PNM_FORMAT_TYPE(format) == PBM_TYPE)
        writeCroppedPBM(ifP, cols, rows, format, crop, background, ofP);
    else
        writeCroppedNonPbm(ifP, cols, rows, maxval, format, crop,
                           background, ofP);
}



int
main(int argc, const char *argv[]) {

    struct cmdlineInfo cmdline;
    FILE * ifP;   
        /* The program's regular input file.  Could be a seekable copy of
           it in a temporary file.
        */
    FILE * bdfP;
        /* The border file.  NULL if none. */
    int eof;    /* no more images in input stream */
    int beof;   /* no more images in borderfile stream */

    pm_proginit(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    ifP = pm_openr_seekable(cmdline.inputFilespec);

    if (cmdline.borderfile)
        bdfP = pm_openr(cmdline.borderfile);
    else
        bdfP = NULL;

    eof = beof = FALSE;
    while (!eof) {
        cropOneImage(cmdline, ifP, bdfP, stdout);

        pnm_nextimage(ifP, &eof);

        if (bdfP) {
            pnm_nextimage(bdfP, &beof);
            
            if (eof != beof) {
                if (!eof)
                    pm_error("Input file has more images than border file."); 
                else
                    pm_error("Border file has more images than image file.");
            }
        }
    }

    pm_close(stdout);
    pm_close(ifP);
    if (bdfP)
        pm_close(bdfP);

    return 0;
}
