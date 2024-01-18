/* pgmmorphconv.c - morphological convolutions on a graymap: dilation and 
** erosion
**
** Copyright (C) 2000 by Luuk van Dijk/Mind over Matter
**
** Based on 
** pnmconvol.c - general MxN convolution on a portable anymap
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

#include "pm_c_util.h"
#include "shhopt.h"
#include "mallocvar.h"
#include "pgm.h"



enum Operation { ERODE, DILATE, OPEN, CLOSE, GRADIENT };



struct CmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    const char * inputFileName;  /* File name of input file */
    const char * templateFileName;  /* File name of template file */

    enum Operation operation;
};



static void
parseCommandLine(int argc, const char ** const argv,
                 struct CmdlineInfo * const cmdlineP) {
/*----------------------------------------------------------------------------
   Note that the file spec array we return is stored in the storage that
   was passed to us as the argv array.
-----------------------------------------------------------------------------*/
    optEntry * option_def;
        /* Instructions to OptParseOptions3 on how to parse our options.
         */
    optStruct3 opt;
    unsigned int option_def_index;
    unsigned int erode, dilate, open, close, gradient;

    MALLOCARRAY_NOFAIL(option_def, 100);

    option_def_index = 0;   /* incremented by OPTENT3 */
    OPTENT3(0,   "erode",        OPT_FLAG,   NULL, &erode,           0);
    OPTENT3(0,   "dilate",       OPT_FLAG,   NULL, &dilate,          0);
    OPTENT3(0,   "open",         OPT_FLAG,   NULL, &open,            0);
    OPTENT3(0,   "close",        OPT_FLAG,   NULL, &close,           0);
    OPTENT3(0,   "gradient",     OPT_FLAG,   NULL, &gradient,        0);

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = TRUE;  /* We may have parms that are negative numbers */

    pm_optParseOptions3(&argc, (char **)argv, opt, sizeof(opt), 0);
        /* Uses and sets argc, argv, and some of *cmdlineP and others. */

    if (erode + dilate + open + close + gradient > 1)
        pm_error("You may specify at most one of -erode, -dilate, "
                 "-open, -close, or -gradient");

    if (erode)
        cmdlineP->operation = ERODE;
    else if (dilate)
        cmdlineP->operation = DILATE;
    else if (open)
        cmdlineP->operation = OPEN;
    else if (close)
        cmdlineP->operation = CLOSE;
    else if (gradient)
        cmdlineP->operation = GRADIENT;
    else
        cmdlineP->operation = DILATE;

    if (argc-1 < 1)
        pm_error("You must specify the template file name as an argument");
    else {
        cmdlineP->templateFileName = argv[1];

        if (argc-1 < 2)
            cmdlineP->inputFileName = "-";
        else {
            cmdlineP->inputFileName = argv[2];
            
            if (argc-1 > 2)
                pm_error("Too many arguments: %u.  "
                         "The only possible arguments "
                         "are the template file name and the input file name",
                         argc-1);
        }
    }
}



static void
readTemplateMatrix(const char *   const fileName,
                   bit ***        const templateP,
                   unsigned int * const rowsP,
                   unsigned int * const colsP) {
/*----------------------------------------------------------------------------
  Read in the template matrix.
-----------------------------------------------------------------------------*/
    FILE * templateFileP;
    int cols, rows;

    templateFileP = pm_openr(fileName);

    *templateP = pbm_readpbm(templateFileP, &cols, &rows);

    pm_close(templateFileP);

    if (cols % 2 != 1 || rows % 2 != 1)
        pm_error("the template matrix must have an odd number of "
                 "rows and columns" );

        /* the reason is that we want the middle pixel to be the origin */
    *rowsP = rows;
    *colsP = cols;
}



static void
setAllPixel(gray **      const image,
            unsigned int const rows,
            unsigned int const cols,
            gray         const value) {

    unsigned int col;

    for (col = 0; col < cols; ++col) {
        unsigned int row;
        for (row = 0; row < rows; ++row)
            image[row][col] = value; 
    }
}



static void
dilate(bit **         const template,
       int            const trowso2,
       int            const tcolso2, 
       gray **        const inImage,
       gray **        const outImage, 
       unsigned int   const rows,
       unsigned int   const cols,
       unsigned int * const templateCountP) {

    unsigned int templateCount;
    int tr;

    setAllPixel(outImage, rows, cols, 0);

    /* for each non-black pixel of the template add in to out */

    for (tr = -trowso2, templateCount = 0; tr <= trowso2; ++tr) {
        int tc;
        for (tc = -tcolso2; tc <= tcolso2; ++tc) {
            int r;
            if (template[trowso2+tr][tcolso2+tc] != PBM_BLACK) {
                ++templateCount;

                for (r = ((tr > 0) ? 0 : -tr);
                     r < ((tr > 0) ? (rows-tr) : rows);
                     ++r) {
                    int c;
                    for (c = ((tc > 0) ? 0 : -tc);
                         c < ((tc > 0) ? (cols-tc) : cols);
                         ++c) {
                        gray const source = inImage[r+tr][c+tc];
                        outImage[r][c] = MAX(source, outImage[r][c]);
                    }
                }
            }
        }
    }
    *templateCountP = templateCount;
}



static void
erode(bit **         const template,
      int            const trowso2,
      int            const tcolso2, 
      gray **        const inImage,
      gray **        const outImage, 
      unsigned int   const rows,
      unsigned int   const cols,
      unsigned int * const templateCountP) {

    unsigned int templateCount;
    int tr;

    setAllPixel(outImage, rows, cols, PGM_MAXMAXVAL);

    /* For each non-black pixel of the template add in to out */

    for (tr = -trowso2, templateCount = 0; tr <= trowso2; ++tr) {
        int tc;
        for (tc = -tcolso2; tc <= tcolso2; ++tc) {
            if (template[trowso2+tr][tcolso2+tc] != PBM_BLACK) {
                int r;
                ++templateCount;

                for (r = ((tr > 0) ? 0 : -tr);
                     r < ((tr > 0) ? (rows-tr) : rows);
                     ++r){
                    int c;

                    for (c = ((tc > 0) ? 0 : -tc);
                         c < ((tc > 0) ? (cols-tc) : cols);
                         ++c) {
                        
                        gray const source = inImage[r+tr][c+tc];
                        outImage[r][c] = MIN(source, outImage[r][c]);
      
                    }
                }
            }
        }
    }
    *templateCountP = templateCount;
}



static void
openMorph(bit **         const template,
          int            const trowso2,
          int            const tcolso2, 
          gray **        const inputImage,
          gray **        const outputImage, 
          unsigned int   const rows,
          unsigned int   const cols,
          unsigned int * const templateCountP) {

    gray ** erodedImage;
    unsigned int erodedTemplateCount;

    erodedImage = pgm_allocarray(cols, rows);
    
    erode(template, trowso2, tcolso2, 
          inputImage, erodedImage, rows, cols, &erodedTemplateCount);

    dilate(template, trowso2, tcolso2, 
           erodedImage, outputImage, rows, cols, templateCountP);

    pgm_freearray(erodedImage, rows);
}



static void
closeMorph(bit **         const template,
           int            const trowso2,
           int            const tcolso2, 
           gray **        const inputImage,
           gray **        const outputImage, 
           unsigned int   const rows,
           unsigned int   const cols,
           unsigned int * const templateCountP) {

    gray ** dilatedImage;
    unsigned int dilatedTemplateCount;

    dilatedImage = pgm_allocarray(cols, rows);

    dilate(template, trowso2, tcolso2, 
           inputImage, dilatedImage, rows, cols, &dilatedTemplateCount);

    erode(template, trowso2, tcolso2, 
          dilatedImage, outputImage, rows, cols, templateCountP);

    pgm_freearray(dilatedImage, rows);
}



static void
subtract(gray **      const subtrahendImage,
         gray **      const subtractorImage,
         gray **      const outImage, 
         unsigned int const rows,
         unsigned int const cols ) {

    /* (I call the minuend the subtrahend and the subtrahend the subtractor,
       to be consistent with other arithmetic terminology).
    */

    unsigned int c;

    for (c = 0; c < cols; ++c) {
        unsigned int r;
        for (r = 0; r < rows; ++r)
            outImage[r][c] = subtrahendImage[r][c] - subtractorImage[r][c];
    }
}



static void
gradient(bit **         const template,
         int            const trowso2,
         int            const tcolso2, 
         gray **        const inputImage,
         gray **        const outputImage, 
         unsigned int   const rows,
         unsigned int   const cols,
         unsigned int * const templateCountP) {

    gray ** dilatedImage;
    gray ** erodedImage;
    unsigned int dilatedTemplateCount;
    
    dilatedImage = pgm_allocarray(cols, rows);
    erodedImage = pgm_allocarray(cols, rows);

    dilate(template, trowso2, tcolso2, 
           inputImage, dilatedImage, rows, cols, &dilatedTemplateCount);

    erode(template, trowso2, tcolso2, 
          inputImage, erodedImage, rows, cols, templateCountP);

    subtract(dilatedImage, erodedImage, outputImage, rows, cols);

    pgm_freearray(erodedImage, rows );
    pgm_freearray(dilatedImage, rows );
}



int
main(int argc, const char ** argv) {

    struct CmdlineInfo cmdline;
    FILE * ifP;
    bit ** template;
    unsigned int templateCols, templateRows;
    int cols, rows;
    gray maxval;
    gray ** inputImage;
    gray ** outputImage;
    unsigned int templateCount;

    pm_proginit(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    ifP = pm_openr(cmdline.inputFileName);

    readTemplateMatrix(cmdline.templateFileName,
                       &template, &templateRows, &templateCols);

    /* Template coords run from -templateCols/2 .. 0 .. + templateCols/2 */
  
    inputImage = pgm_readpgm(ifP, &cols, &rows, &maxval);

    if (cols < templateCols || rows < templateRows)
        pm_error("the image is smaller than the convolution matrix" );
  
    outputImage = pgm_allocarray(cols, rows);
  
    switch (cmdline.operation) {
    case DILATE:
        dilate(template, templateRows/2, templateCols/2,
               inputImage, outputImage, rows, cols,
               &templateCount);
        break;
    case ERODE:
        erode(template, templateRows/2, templateCols/2,
              inputImage, outputImage, rows, cols,
              &templateCount);
        break;
    case OPEN:
        openMorph(template, templateRows/2, templateCols/2,
              inputImage, outputImage, rows, cols,
              &templateCount);
        break;
    case CLOSE:
        closeMorph(template, templateRows/2, templateCols/2,
                   inputImage, outputImage, rows, cols,
                   &templateCount);
        break;
    case GRADIENT:
        gradient(template, templateRows/2, templateCols/2,
                 inputImage, outputImage, rows, cols,
                 &templateCount);
        break;
    }

    if (templateCount == 0)
        pm_error( "The template was empty!" );

    pgm_writepgm(stdout, outputImage, cols, rows, maxval, 0);

    pgm_freearray(outputImage, rows);
    pgm_freearray(inputImage, rows);
    pm_close(ifP);

    return 0;
}

