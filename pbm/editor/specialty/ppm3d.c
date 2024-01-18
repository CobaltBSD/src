/*=============================================================================
                                   ppmto3d
===============================================================================
  This program converts two PPM images into an anaglyph stereogram image PPM.
  (for viewing with red/blue 3D glasses).

=============================================================================*/

#include <assert.h>

#include "pm_c_util.h"
#include "shhopt.h"
#include "mallocvar.h"
#include "ppm.h"
#include "lum.h"



struct cmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    const char * leftInputFileName;  /* '-' if stdin */
    const char * rghtInputFileName;  /* '-' if stdin */
    int offset;
    unsigned int color;
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
    optEntry * option_def;
        /* Instructions to pm_optParseOptions3 on how to parse our options.
         */
    optStruct3 opt;

    unsigned int option_def_index;
    unsigned int offsetSpec;
    const char * offsetArg;

    MALLOCARRAY_NOFAIL(option_def, 100);

    option_def_index = 0;   /* incremented by OPTENT3 */
    OPTENT3(0, "color",   OPT_FLAG,   NULL,
            &cmdlineP->color,   0);
    OPTENT3(0, "offset",  OPT_INT,    &cmdlineP->offset,
            &offsetSpec,  0);

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = FALSE;  /* We have no parms that are negative numbers */

    pm_optParseOptions3( &argc, argv, opt, sizeof(opt), 0);
        /* Uses and sets argc, argv, and some of *cmdlineP and others. */
    
    if (argc-1 < 2)
        pm_error("You must specify at least two arguments: left and right "
                 "input file names.  You specified %u", argc-1);
    else {
        cmdlineP->leftInputFileName = argv[1];
        cmdlineP->rghtInputFileName = argv[2];

        if (argc-1 > 2) {
            offsetArg = argv[3];

            if (argc-1 > 3)
                pm_error("Program takes at most 3 arguments:  left and "
                         "right input file names and offset.  "
                         "You specified %u", argc-1);
        } else
            offsetArg = NULL;
    }

    if (offsetArg && offsetSpec)
        pm_error("You cannot specify both -offset and the offset "
                 "argument (i.e. with -offset, there is at most "
                 "two arguments: left and right input file names");
    else if (!offsetArg && !offsetSpec)
        cmdlineP->offset = 0;
    else if (offsetArg)
        cmdlineP->offset = atoi(offsetArg);
}



static void
computeGrayscaleRow(const pixel * const inputRow,
                    gray *        const outputRow,
                    pixval        const maxval,
                    unsigned int  const cols) {

    if (maxval <= 255) {
        unsigned int col;
        /* Use fast approximation to 0.299 r + 0.587 g + 0.114 b. */
        for (col = 0; col < cols; ++col)
            outputRow[col] = ppm_fastlumin(inputRow[col]);
    } else {
        unsigned int col;
        /* Can't use fast approximation, so fall back on floats. */
        for (col = 0; col < cols; ++col)
            outputRow[col] = PPM_LUMIN(inputRow[col]) + 0.5;
    }
}



static void
compute3dRowMono(gray *       const lGrayrow,
                 gray *       const rGrayrow,
                 pixel *      const pixelrow,
                 unsigned int const cols,
                 int          const offset) {
    
    unsigned int col;
    gray *  lgP;
    gray *  rgP;
    pixel * pP;

    assert(abs(offset) <= cols);

    for (col = 0, pP = pixelrow, lgP = lGrayrow, rgP = rGrayrow;
         col < cols + offset;
         ++col) {
            
        if ((int)col < offset/2)
            ++lgP;
        else if ((int)col < offset) {
            PPM_ASSIGN(*pP, 0, *lgP, *lgP);
            ++lgP;
            ++pP;
        } else if (col < cols) {
            PPM_ASSIGN(*pP, *rgP, *lgP, *lgP);
            ++lgP;
            ++rgP;
            ++pP;
        } else if (col < cols + offset/2) {
            PPM_ASSIGN(*pP, *rgP, 0, 0);
            ++rgP;
            ++pP;
        } else {
            assert(col < cols + offset);
            ++rgP;
        }
    }
}    



static void
compute3dRowColor(pixel *      const lPixelrow,
                  pixel *      const rPixelrow,
                  pixel *      const pixelrow,
                  unsigned int const cols,
                  unsigned int const offset) {
    
    unsigned int col;
    pixel * lP;
    pixel * rP;
    pixel * pP;

    assert(abs(offset) <= cols);

    for (col = 0, pP = pixelrow, lP = lPixelrow, rP = rPixelrow;
         col < cols + offset;
         ++col) {
            
        if ((int)col < offset/2)
            ++lP;
        else if ((int)col < offset) {
            PPM_ASSIGN(*pP, 0, PPM_GETG(*lP), PPM_GETB(*lP));
            ++lP;
            ++pP;
        } else if (col < cols) {
            PPM_ASSIGN(*pP, PPM_GETR(*rP), PPM_GETG(*lP), PPM_GETB(*lP));
            ++lP;
            ++rP;
            ++pP;
        } else if (col < cols + offset/2) {
            PPM_ASSIGN(*pP, PPM_GETR(*rP), 0, 0);
            ++rP;
            ++pP;
        } else {
            assert(col < cols + offset);
            ++rP;
        }
    }
}    



static void
write3dRaster(FILE *       const ofP,
              FILE *       const lIfP,
              FILE *       const rIfP,
              unsigned int const cols,
              unsigned int const rows,
              pixval       const maxval,
              int          const lFormat,
              int          const rFormat,
              int          const offset,
              bool         const color) {

    pixel * lPixelrow;
    gray *  lGrayrow;
    pixel * rPixelrow;
    gray *  rGrayrow;
    pixel * pixelrow;

    unsigned int row;

    assert(abs(offset) < cols);

    lPixelrow = ppm_allocrow (cols);
    lGrayrow  = pgm_allocrow (cols);
    rPixelrow = ppm_allocrow (cols);
    rGrayrow  = pgm_allocrow (cols);
    pixelrow  = ppm_allocrow (cols);

    for (row = 0; row < rows; ++row) {
        ppm_readppmrow(lIfP, lPixelrow, cols, maxval, lFormat);
        ppm_readppmrow(rIfP, rPixelrow, cols, maxval, rFormat);

        computeGrayscaleRow(lPixelrow, lGrayrow, maxval, cols);
        computeGrayscaleRow(rPixelrow, rGrayrow, maxval, cols);

        if (color)
            compute3dRowColor(lPixelrow, rPixelrow, pixelrow, cols, offset);
        else
            compute3dRowMono(lGrayrow, rGrayrow, pixelrow, cols, offset);

        ppm_writeppmrow(ofP, pixelrow, cols, maxval, 0);
    }

    ppm_freerow(pixelrow);
    pgm_freerow(rGrayrow);
    ppm_freerow(rPixelrow);
    pgm_freerow(lGrayrow);
    ppm_freerow(lPixelrow);
}



int
main(int argc, char *argv[]) {

    struct cmdlineInfo cmdline;
    FILE * lIfP;
    FILE * rIfP;

    int cols, rows;
    pixval maxval;

    int lRows, lCols;
    int lFormat;
    pixval lMaxval;
   
    int rRows, rCols;
    int rFormat;
    pixval rMaxval;
   
    ppm_init(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    lIfP = pm_openr(cmdline.leftInputFileName);
    rIfP = pm_openr(cmdline.rghtInputFileName);

    ppm_readppminit(lIfP, &lCols, &lRows, &lMaxval, &lFormat);
    ppm_readppminit(rIfP, &rCols, &rRows, &rMaxval, &rFormat);
    
    if ((lCols != rCols) || (lRows != rRows) || 
        (lMaxval != rMaxval) || 
        (PPM_FORMAT_TYPE(lFormat) != PPM_FORMAT_TYPE(rFormat)))
        pm_error ("Pictures are not of same size and format");
    
    cols   = lCols;
    rows   = lRows;
    maxval = lMaxval;

    if (abs(cmdline.offset) >= cols)
        pm_error("Magnitude of -offset (%u columns) is not less than "
                 "width of images "
                 "(%u columns)", abs(cmdline.offset), cols);
   
    ppm_writeppminit(stdout, cols, rows, maxval, 0);

    write3dRaster(stdout, lIfP, rIfP, cols, rows, maxval,
                  lFormat, rFormat, cmdline.offset, cmdline.color);

    pm_close(lIfP);
    pm_close(rIfP);
    pm_close(stdout);

    return 0;
}

