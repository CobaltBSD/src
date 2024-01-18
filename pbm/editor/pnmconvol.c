/* pnmconvol.c - general MxN convolution on a Netpbm image
**
** Major rewriting by Mike Burns
** Copyright (C) 1994, 1995 by Mike Burns (burns@chem.psu.edu)
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

/* A change history is at the bottom */

#include <stdlib.h>
#include <assert.h>

#include "pm_c_util.h"
#include "mallocvar.h"
#include "nstring.h"
#include "token.h"
#include "io.h"
#include "shhopt.h"
#include "pam.h"



static sample const
clipSample(sample const unclipped,
           sample const maxval) {

    return MIN(maxval, unclipped);
}



static sample const
makeSample(float  const arg,
           sample const maxval) {
/*----------------------------------------------------------------------------
   From a tentative sample value that could be fractional or negative,
   produce an actual sample value by rounding and clipping.
-----------------------------------------------------------------------------*/
    return MIN(maxval, ROUNDU(MAX(0.0, arg)));
}



static void
validateKernelDimensions(unsigned int const width,
                         unsigned int const height) {

    if (height == 0)
        pm_error("Convolution matrix height is zero");
    if (width == 0)
        pm_error("Convolution matrix width is zero");

    if (height % 2 != 1)
        pm_error("The convolution matrix must have an odd number of rows.  "
                 "Yours has %u", height);

    if (width % 2 != 1)
        pm_error("The convolution matrix must have an odd number of columns.  "
                 "Yours has %u", width);
}



struct matrixOpt {
    unsigned int width;
    unsigned int height;
    float ** weight;
};




struct cmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    const char * inputFileName;  /* '-' if stdin */
    const char * pnmMatrixFileName;
    unsigned int nooffset;
    const char ** matrixfile;
    unsigned int matrixSpec;
    struct matrixOpt matrix;
    unsigned int normalize;
    unsigned int bias;
};



static void
countMatrixOptColumns(const char *   const rowString,
                      unsigned int * const colCtP) {

    const char * cursor;
    unsigned int colCt;

    for (cursor = &rowString[0], colCt = 0; *cursor; ) {
        const char * colString;
        const char * next;
        const char * error;

        pm_gettoken(cursor, ',', &colString, &next, &error);

        if (error) {
            pm_error("Unable to parse -matrix value row '%s'.  %s",
                     rowString, error);
            pm_strfree(error);
        } else {
            ++colCt;

            cursor = next;
            if (*cursor) {
                assert(*cursor == ',');
                ++cursor;  /* advance over comma to next column */
            }
            pm_strfree(colString);
        }
    }
    *colCtP = colCt;
}



static void
getMatrixOptDimensions(const char *   const matrixOptString,
                       unsigned int * const widthP,
                       unsigned int * const heightP) {
/*----------------------------------------------------------------------------
   Given the value of a -matrix option, 'matrixOptString', return the
   height and width of the matrix it describes.

   If it's not valid enough to determine that (e.g. it has rows of different
   widths), abort.

   An example of 'matrixOptString':

     ".04,.15,.04;.15,.24,.15;.04,.15,.04"
-----------------------------------------------------------------------------*/
    unsigned int rowCt;
    const char * cursor;

    for (cursor = &matrixOptString[0], rowCt = 0; *cursor; ) {
        const char * rowString;
        const char * next;
        const char * error;

        pm_gettoken(cursor, ';', &rowString, &next, &error);

        if (error) {
            pm_error("Unable to parse -matrix value '%s'.  %s",
                     matrixOptString, error);
            pm_strfree(error);
        } else {
            unsigned int colCt;
            ++rowCt;

            countMatrixOptColumns(rowString, &colCt);

            if (rowCt == 1)
                *widthP = colCt;
            else {
                if (colCt != *widthP)
                pm_error("-matrix option value contains rows of different "
                         "widths: %u and %u", *widthP, colCt);
            }            
            pm_strfree(rowString);
            cursor = next;

            if (*cursor) {
                assert(*cursor == ';');
                ++cursor;  /* advance cursor over semicolon to next row */
            }
        }
    }
    *heightP = rowCt;
}



static void
parseMatrixRow(const char * const matrixOptRowString,
               unsigned int const width,
               float *      const weight) {

    unsigned int col;
    const char * cursor;

    for (col = 0, cursor = &matrixOptRowString[0]; col < width; ++col) {
        const char * colString;
        const char * next;
        const char * error;

        pm_gettoken(cursor, ',', &colString, &next, &error);

        if (error) {
            pm_error("Failed parsing a row in the -matrix value.  %s", error);
            pm_strfree(error);
        } else {
            if (colString[0] == '\0')
                pm_error("The Column %u element of the row '%s' in the "
                         "-matrix value is a null string", col,
                         matrixOptRowString);
            else {
                char * trailingJunk;
                weight[col] = strtod(colString, &trailingJunk);

                if (*trailingJunk != '\0') 
                    pm_error("The Column %u element of the row '%s' in the "
                             "-matrix value is not a valid floating point "
                             "number", col, matrixOptRowString);
            }
            pm_strfree(colString);

            cursor = next;

            if (*cursor) {
                assert(*cursor == ',');
                ++cursor;  /* advance over comma to next column */
            }
        }
    }
}



static void
parseMatrixOptWithDimensions(const char * const matrixOptString,
                             unsigned int const width,
                             unsigned int const height,
                             float **     const weight) {
    
    unsigned int row;
    const char * cursor;

    for (row = 0, cursor = &matrixOptString[0]; row < height; ++row) {
        const char * rowString;
        const char * next;
        const char * error;

        pm_gettoken(cursor, ';', &rowString, &next, &error);

        if (error) {
            pm_error("Failed parsing -matrix value.  %s", error);
            pm_strfree(error);
        } else {
            parseMatrixRow(rowString, width, weight[row]);

            pm_strfree(rowString);

            cursor = next;

            if (*cursor) {
                assert(*cursor == ';');
                ++cursor;  /* advance over semicolon to next row */
            }
        }
    }
}    



static void
parseMatrixOpt(const char *         const matrixOptString,
               struct matrixOpt *   const matrixOptP) {
/*----------------------------------------------------------------------------
   An example of 'matrixOptString':

     ".04,.15,.04;.15,.24,.15;.04,.15,.04"

-----------------------------------------------------------------------------*/
    unsigned int width, height;

    getMatrixOptDimensions(matrixOptString, &width, &height);

    validateKernelDimensions(width, height);

    matrixOptP->height = height;
    matrixOptP->width  = width;

    {
        unsigned int row;
        MALLOCARRAY_NOFAIL(matrixOptP->weight, height);
        for (row = 0; row < height; ++row)
            MALLOCARRAY_NOFAIL(matrixOptP->weight[row], width);
    }
    parseMatrixOptWithDimensions(matrixOptString, width, height,
                                 matrixOptP->weight);
}



static void
validateMatrixfileOpt(const char ** const matrixFileOpt) {

    if (matrixFileOpt[0] == NULL)
        pm_error("You specified an empty string as the value of "
                 "-matrixfile.  You must specify at least one file name");
}



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
    unsigned int matrixfileSpec;
    const char * matrixOpt;
    unsigned int biasSpec;

    MALLOCARRAY_NOFAIL(option_def, 100);

    option_def_index = 0;   /* incremented by OPTENT3 */
    OPTENT3(0, "matrix",       OPT_STRING, &matrixOpt,
            &cmdlineP->matrixSpec,     0)
    OPTENT3(0, "matrixfile",   OPT_STRINGLIST, &cmdlineP->matrixfile,
            &matrixfileSpec,           0)
    OPTENT3(0, "nooffset",     OPT_FLAG,   NULL,                  
            &cmdlineP->nooffset,       0);
    OPTENT3(0, "normalize",    OPT_FLAG,   NULL,                  
            &cmdlineP->normalize,      0);
    OPTENT3(0, "bias",         OPT_UINT,   &cmdlineP->bias,
            &biasSpec,                 0);

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = FALSE;  /* We have no parms that are negative numbers */

    pm_optParseOptions3( &argc, argv, opt, sizeof(opt), 0);
        /* Uses and sets argc, argv, and some of *cmdlineP and others. */

    if (!biasSpec)
        cmdlineP->bias = 0;

    if (matrixfileSpec && cmdlineP->matrixSpec)
        pm_error("You can't specify by -matrix and -matrixfile");

    if (cmdlineP->matrixSpec)
        parseMatrixOpt(matrixOpt, &cmdlineP->matrix);

    if (matrixfileSpec)
        validateMatrixfileOpt(cmdlineP->matrixfile);
    else
        cmdlineP->matrixfile = NULL;

    if (matrixfileSpec || cmdlineP->matrixSpec) {
        if (cmdlineP->nooffset)
            pm_error("-nooffset is meaningless and not allowed with "
                     "-matrix or -matrixfile");

        cmdlineP->pnmMatrixFileName = NULL;

        if (argc-1 >= 1)
            cmdlineP->inputFileName = argv[1];
        else
            cmdlineP->inputFileName = "-";

        if (argc-1 > 1)
            pm_error("Too many arguments.  When you specify -matrix "
                     "or -matrixfile, the only allowable non-option "
                     "argument is the input file name");
    } else {
        /* It's an old style invocation we accept for backward compatibility */
        
        if (argc-1 < 1)
            pm_error("You must specify either -matrix or -matrixfile "
                     "at least one argument which names an old-style PGM "
                     "convolution matrix file.");
        else {
            cmdlineP->pnmMatrixFileName = argv[1];

            if (argc-1 >= 2)
                cmdlineP->inputFileName = argv[2];
            else
                cmdlineP->inputFileName = "-";
            
            if (argc-1 > 2)
                pm_error("Too many arguments.  Only acceptable arguments are: "
                         "convolution matrix file name and input file name");
        }
    }
}



struct ConvKernel {
    unsigned int cols;
        /* Width of the convolution window */
    unsigned int rows;
        /* Height of the convolution window */
    unsigned int planes;
        /* Depth of the kernel -- this had better be the same as the
           depth of the image being convolved.
        */
    float ** weight[3];
        /* weight[PLANE][ROW][COL] is the weight to give to Plane PLANE
           of the pixel at row ROW, column COL within the convolution window.
           
           One means full weight.

           It can have magnitude greater than or less than one.  It can be
           positive or negative.  
        */
    unsigned int bias;
        /* The amount to be added to the linear combination of sample values.
           We take a little liberty with the term "convolution kernel" to
           include this value, since convolution per se does not involve any
           such biasing.
        */
};



static void
warnBadKernel(struct ConvKernel * const convKernelP) {

    float sum[3];
    unsigned int plane;
    unsigned int row;

    for (plane = 0; plane < convKernelP->planes; ++plane)
        sum[plane] = 0.0; /* initial value */
    
    for (row = 0; row < convKernelP->rows; ++row) {
        unsigned int col;
        for (col = 0; col < convKernelP->cols; ++col) {
            unsigned int plane;
            for (plane = 0; plane < convKernelP->planes; ++plane)
                sum[plane] += convKernelP->weight[plane][row][col];
        }
    }

    if (convKernelP->planes == 3) {
        unsigned int plane;
        bool biased, negative;
        for (plane = 0, biased = false, negative = false;
             plane < convKernelP->planes;
             ++plane) {
            if (sum[plane] < 0.9 || sum[plane] > 1.1)
                biased = true;
            if (sum[plane] < 0.0)
                negative = true;
        }
    
        if (biased) {
            pm_message("WARNING - this convolution matrix is biased.  " 
                       "red, green, and blue average weights: %f, %f, %f "
                       "(unbiased would be 1).",
                       sum[PAM_RED_PLANE],
                       sum[PAM_GRN_PLANE],
                       sum[PAM_BLU_PLANE]);

            if (negative)
                pm_message("Maybe you want the -nooffset option?");
        }
    } else if (convKernelP->planes == 1) {
        if (sum[0] < 0.9 || sum[0] > 1.1)
            pm_message("WARNING - this convolution matrix is biased.  "
                       "average weight = %f (unbiased would be 1)",
                       sum[0]);
        if (sum[0] < 0.0)
            pm_message("Maybe you want the -nooffset option?");
    }
}



static void
convKernelCreatePnm(struct pam *         const cpamP,
                    tuple * const *      const ctuples, 
                    unsigned int         const depth,
                    bool                 const offsetPnm,
                    struct ConvKernel ** const convKernelPP) {
/*----------------------------------------------------------------------------
   Compute the convolution matrix in normalized form from the PGM form
   'ctuples'/'cpamP'.  Each element of the output matrix is the actual weight
   we give an input pixel -- i.e. the thing by which we multiple a value from
   the input image.

   'depth' is the required number of planes in the kernel.  If 'ctuples' has
   fewer planes than that, we duplicate as necessary.  E.g. if 'ctuples' is
   from a PGM input file and we're convolving a PPM image, we'll make a
   3-plane convolution kernel by repeating the one plane in 'ctuples'.  If
   'ctuples' has more planes than specified, we ignore the higher numbered
   ones.

   'offsetPnm' means the PNM convolution matrix is defined in offset form so
   that it can represent negative values.  E.g. with maxval 100, 50 means
   0, 100 means 50, and 0 means -50.  If 'offsetPgm' is false, 0 means 0
   and there are no negative weights.
-----------------------------------------------------------------------------*/
    double const scale = (offsetPnm ? 2.0 : 1.0) / cpamP->maxval;
    double const offset = offsetPnm ? - 1.0 : 0.0;
    unsigned int const planes = MIN(3, depth);

    struct ConvKernel * convKernelP;
    unsigned int plane;

    MALLOCVAR_NOFAIL(convKernelP);

    convKernelP->cols   = cpamP->width;
    convKernelP->rows   = cpamP->height;
    convKernelP->planes = planes;

    for (plane = 0; plane < planes; ++plane) {
        unsigned int row;

        MALLOCARRAY_NOFAIL(convKernelP->weight[plane], cpamP->height);
    
        for (row = 0; row < cpamP->height; ++row) {
            unsigned int col;

            MALLOCARRAY_NOFAIL(convKernelP->weight[plane][row], cpamP->width);

            for (col = 0; col < cpamP->width; ++col) {
                sample const inValue = plane < cpamP->depth ?
                    ctuples[row][col][plane] : ctuples[row][col][0];

                convKernelP->weight[plane][row][col] =
                    inValue * scale + offset;
            }
        }
    }
    convKernelP->bias = 0;

    *convKernelPP = convKernelP;
}



static void
convKernelDestroy(struct ConvKernel * const convKernelP) {

    unsigned int plane;

    for (plane = 0; plane < convKernelP->planes; ++plane) {
        unsigned int row;

        for (row = 0; row < convKernelP->rows; ++row)
            free(convKernelP->weight[plane][row]);

        free(convKernelP->weight[plane]);
    }
    free(convKernelP);
}



static void
normalizeKernelPlane(struct ConvKernel * const convKernelP,
                     unsigned int        const plane) {

    unsigned int row;
    float sum;

    for (row = 0, sum = 0.0; row < convKernelP->rows; ++row) {
        unsigned int col;
            
        for (col = 0; col < convKernelP->cols; ++col) {
                
            sum += convKernelP->weight[plane][row][col];
        }
    }

    {
        float const scaler = 1.0/sum;

        unsigned int row;

        for (row = 0; row < convKernelP->rows; ++row) {
            unsigned int col;
                
            for (col = 0; col < convKernelP->cols; ++col)
                convKernelP->weight[plane][row][col] *= scaler;
        }
    }
}



static void
normalizeKernel(struct ConvKernel * const convKernelP) {
/*----------------------------------------------------------------------------
   Modify *convKernelP by scaling every weight in a plane by the same factor
   such that the weights in the plane all add up to 1.
-----------------------------------------------------------------------------*/
    unsigned int plane;

    for (plane = 0; plane < convKernelP->planes; ++plane)
        normalizeKernelPlane(convKernelP, plane);
}



static void
getKernelPnm(const char *         const fileName,
             unsigned int         const depth,
             bool                 const offset,
             struct ConvKernel ** const convKernelPP) {
/*----------------------------------------------------------------------------
   Get the convolution kernel from the PNM file named 'fileName'.
   'offset' means the PNM convolution matrix is defined in offset form so
   that it can represent negative values.  E.g. with maxval 100, 50 means
   0, 100 means 50, and 0 means -50.  If 'offsetPgm' is false, 0 means 0
   and there are no negative weights.

   Make the kernel suitable for convolving an image of depth 'depth'.

   Return the kernel as *convKernelPP.
-----------------------------------------------------------------------------*/
    struct pam cpam;
    FILE * cifP;
    tuple ** ctuples;

    cifP = pm_openr(fileName);

    /* Read in the convolution matrix. */
    ctuples = pnm_readpam(cifP, &cpam, PAM_STRUCT_SIZE(tuple_type));
    pm_close(cifP);
    
    validateKernelDimensions(cpam.width, cpam.height);

    convKernelCreatePnm(&cpam, ctuples, depth, offset, convKernelPP);
}



static void
convKernelCreateMatrixOpt(struct matrixOpt     const matrixOpt,
                          bool                 const normalize,
                          unsigned int         const depth,
                          unsigned int         const bias,
                          struct ConvKernel ** const convKernelPP) {
/*----------------------------------------------------------------------------
   Create a convolution kernel as described by a -matrix command line
   option.
   
   The option value is 'matrixOpt'.

   If 'normalize' is true, we normalize whatever numbers the option specifies
   so that they add up to one; otherwise, we take the numbers as we find them,
   so they may form a biased matrix -- i.e. one which brightens or dims the
   image overall.
-----------------------------------------------------------------------------*/
    struct ConvKernel * convKernelP;
    unsigned int plane;

    MALLOCVAR(convKernelP);

    convKernelP->cols = matrixOpt.width;
    convKernelP->rows = matrixOpt.height;
    convKernelP->planes = depth;

    for (plane = 0; plane < depth; ++plane) {
        unsigned int row;
        MALLOCARRAY_NOFAIL(convKernelP->weight[plane], matrixOpt.height);

        for (row = 0; row < matrixOpt.height; ++row) {
            unsigned int col;

            MALLOCARRAY_NOFAIL(convKernelP->weight[plane][row],
                               matrixOpt.width);
    
            for (col = 0; col < matrixOpt.width; ++col)
                convKernelP->weight[plane][row][col] =
                    matrixOpt.weight[row][col];
        }
    }
    if (normalize)
        normalizeKernel(convKernelP);

    convKernelP->bias = bias;

    *convKernelPP = convKernelP;
}



static void
parsePlaneFileLine(const char *   const line,
                   unsigned int * const widthP,
                   float **       const weightP) {

    unsigned int colCt;
    const char * error;
    float * weight;
    const char * cursor;

    colCt = 0;  /* initial value */
    weight = NULL;

    for (cursor = &line[0]; *cursor; ) {
        const char * token;
        const char * next;

        REALLOCARRAY(weight, colCt + 1);

        pm_gettoken(cursor, ' ', &token, &next, &error);

        if (error)
            pm_error("Invalid format of line in convolution matrix file: "
                     "'%s'.  %s", line, error);

        cursor = next;

        if (*cursor) {
            assert(*next == ' ');
            ++cursor;  /* advance over space */
        }
        if (strlen(token) == 0)
            pm_error("Column %u value in line '%s' of convolution matrix file "
                     "is null string.", colCt, line);
        else {
            char * trailingJunk;
            weight[colCt] = strtod(token, &trailingJunk);
            if (*trailingJunk != '\0') 
                pm_error("The Column %u element of the row '%s' in the "
                         "-matrix value is not a valid floating point "
                         "number", colCt, line);

                ++colCt;
        }
        pm_strfree(token);
    }
    *weightP = weight;
    *widthP = colCt;
}



static void
readPlaneFile(FILE *         const ifP, 
              float ***      const weightP,
              unsigned int * const widthP,
              unsigned int * const heightP) {
/*----------------------------------------------------------------------------
   Read weights of one plane from a file.

   The file is a simple matrix, one line per row, with columns separated
   by a single space.

   Each column is a floating point decimal ASCII number, positive zero,
   or negative, with any magnitude.

   If the rows don't all have the same number of columns, we abort.

   Return the dimensions seen in the file as *widthP and *heightP.
-----------------------------------------------------------------------------*/
    unsigned int rowCt;
    float ** weight;
    unsigned int width;
    bool eof;

    weight = NULL;  /* initial value */

    for (eof = false, rowCt = 0; !eof; ) {
        const char * error;
        const char * line;

        pm_freadline(ifP, &line, &error);

        if (error)
            pm_error("Failed to read row %u "
                     "from the convolutionmatrix file.  %s",
                     rowCt, error);
        else {
            if (line == NULL)
                eof = true;
            else {
                REALLOCARRAY(weight, rowCt + 1);
            
                if (weight == NULL)
                    pm_error("Unable to allocate memory for "
                             "convolution matrix");
                else {
                    unsigned int thisWidth;

                    parsePlaneFileLine(line, &thisWidth, &weight[rowCt]);

                    if (rowCt == 0)
                        width = thisWidth;
                    else {
                        if (thisWidth != width)
                            pm_error("Multiple row widths in the convolution "
                                     "matrix file: %u columns and %u columns.",
                                     width, thisWidth);
                    }                    
                    ++rowCt;
                }
                pm_strfree(line);
            }
        }
    }
    validateKernelDimensions(width, rowCt);

    *weightP = weight;
    *heightP = rowCt;
    *widthP = width;
}



static void
copyWeight(float **       const srcWeight,
           unsigned int   const width,
           unsigned int   const height, 
           float ***      const dstWeightP) {
/*----------------------------------------------------------------------------
   Make a copy, in dynamically allocated memory, of the weight matrix
   'srcWeight', whose dimensions are 'width' by 'height'.  Return the
   new matrix as *dstWeightP.
-----------------------------------------------------------------------------*/
    unsigned int row;
    float ** dstWeight;

    MALLOCARRAY(dstWeight, height);

    if (dstWeight == NULL)
        pm_error("Could not allocate memory for convolution matrix");
   
    for (row = 0; row < height; ++row) {
        unsigned int col;

        MALLOCARRAY(dstWeight[row], width);

        if (dstWeight[row] == NULL)
            pm_error("Could not allocation memory for a "
                     "convolution matrix row");

        for (col = 0; col < width; ++col) {
            dstWeight[row][col] = srcWeight[row][col];
        }
    }
    *dstWeightP = dstWeight;
}



static void
convKernelCreateSimpleFile(const char **        const fileNameList,
                           bool                 const normalize,
                           unsigned int         const depth,
                           unsigned int         const bias,
                           struct ConvKernel ** const convKernelPP) {
/*----------------------------------------------------------------------------
   Create a convolution kernel as described by a convolution matrix file.
   This is the simple file with floating point numbers in it, not the
   legacy pseudo-PNM thing.

   The name of the file is 'fileNameList'.

   If 'normalize' is true, we normalize whatever numbers we find in the file
   so that they add up to one; otherwise, we take the numbers as we find them,
   so they may form a biased matrix -- i.e. one which brightens or dims the
   image overall.
-----------------------------------------------------------------------------*/
    struct ConvKernel * convKernelP;
    unsigned int fileCt;
    unsigned int planeCt;
    unsigned int plane;
    unsigned int width, height;

    fileCt = 0;
    while (fileNameList[fileCt])
        ++fileCt;
    assert(fileCt > 0);

    planeCt = MIN(3, depth);

    MALLOCVAR_NOFAIL(convKernelP);

    convKernelP->planes = planeCt;

    for (plane = 0; plane < planeCt; ++plane) {
        if (plane < fileCt) {
            const char * const fileName = fileNameList[plane];

            FILE * ifP;
            unsigned int thisWidth, thisHeight;

            ifP = pm_openr(fileName);

            readPlaneFile(ifP, &convKernelP->weight[plane],
                          &thisWidth, &thisHeight);

            if (plane == 0) {
                width = thisWidth;
                height = thisHeight;
            } else {
                if (thisWidth != width)
                    pm_error("Convolution matrix files show two different "
                             "widths: %u and %u", width, thisWidth);
                if (thisHeight != height)
                    pm_error("Convolution matrix files show two different "
                             "heights: %u and %u", height, thisHeight);
            }
            pm_close(ifP);
        } else {
            assert(plane > 0);
            copyWeight(convKernelP->weight[0], width, height,
                       &convKernelP->weight[plane]);
        }
    }

    if (normalize)
        normalizeKernel(convKernelP);

    convKernelP->cols = width;
    convKernelP->rows = height;
    convKernelP->bias = bias;

    *convKernelPP = convKernelP;
}



static void
getKernel(struct cmdlineInfo   const cmdline,
          unsigned int         const depth,
          struct ConvKernel ** const convKernelPP) {
/*----------------------------------------------------------------------------
   Figure out what the convolution kernel is.  It can come from various
   sources in various forms, as described on the command line, represented
   by 'cmdline'.

   We generate a kernel object in standard form (free of any indication of
   where it came from) and return a handle to it as *convKernelPP.
----------------------------------------------------------------------------*/
    struct ConvKernel * convKernelP;

    if (cmdline.pnmMatrixFileName)
        getKernelPnm(cmdline.pnmMatrixFileName, depth, !cmdline.nooffset,
                     &convKernelP);
    else if (cmdline.matrixfile)
        convKernelCreateSimpleFile(cmdline.matrixfile, cmdline.normalize,
                                   depth, cmdline.bias, &convKernelP);
    else if (cmdline.matrixSpec)
        convKernelCreateMatrixOpt(cmdline.matrix, cmdline.normalize,
                                  depth, cmdline.bias, &convKernelP);

    warnBadKernel(convKernelP);

    *convKernelPP = convKernelP;
}



static void
validateEnoughImageToConvolve(const struct pam *        const inpamP,
                              const struct ConvKernel * const convKernelP) {
/*----------------------------------------------------------------------------
   Abort program if the image isn't big enough in both directions to have
   at least one convolved pixel.

   The program could theoretically operate with an image smaller than that by
   simply outputting the input unchanged (like it does with the edges of an
   image anyway), but we're too lazy to write code for this special case.  The
   simple code expects the unconvolved edges to exist full-size and some of it
   convolves the first convolveable row and/or column specially and expects it
   to exist.
-----------------------------------------------------------------------------*/

    if (inpamP->height < convKernelP->rows + 1)
        pm_error("Image is too short (%u rows) to convolve with this "
                 "%u-row convolution kernel.",
                 inpamP->height, convKernelP->rows);
    
    if (inpamP->width < convKernelP->cols + 1)
        pm_error("Image is too narrow (%u columns) to convolve with this "
                 "%u-column convolution kernel.",
                 inpamP->width, convKernelP->cols);
}



static tuple **
allocRowbuf(struct pam * const pamP,
            unsigned int const height) {

    tuple ** rowbuf;

    MALLOCARRAY(rowbuf, height);

    if (rowbuf == NULL)
        pm_error("Failed to allocate %u-row buffer", height);
    else {
        unsigned int row;
    
        for (row = 0; row < height; ++row)
            rowbuf[row] = pnm_allocpamrow(pamP);
    }

    return rowbuf;
}



static void
freeRowbuf(tuple **     const rowbuf,
           unsigned int const height) {

    unsigned int row;

    for (row = 0; row < height; ++row)
        pnm_freepamrow(rowbuf[row]);

    free(rowbuf);
}



static void
readAndScaleRow(struct pam * const inpamP,
                tuple *      const inrow,
                sample       const newMaxval,
                unsigned int const newDepth) {

    pnm_readpamrow(inpamP, inrow);

    if (newMaxval != inpamP->maxval)
        pnm_scaletuplerow(inpamP, inrow, inrow, newMaxval);

    if (newDepth == 3 && inpamP->depth == 1)
        pnm_makerowrgb(inpamP, inrow);
}



static void
readAndScaleRows(struct pam *              const inpamP,
                 unsigned int              const count,
                 tuple **                  const rowbuf,
                 sample                    const outputMaxval,
                 unsigned int              const outputDepth) {
/*----------------------------------------------------------------------------
  Read in 'count' rows into rowbuf[].
  
  Scale the contents to maxval 'outputMaxval' and expand to depth
  'outputDepth'.
-----------------------------------------------------------------------------*/
    unsigned int row;

    for (row = 0; row < count; ++row)
        readAndScaleRow(inpamP, rowbuf[row], outputMaxval, outputDepth);
}



static void
writePamRowBiased(struct pam * const outpamP,
                  tuple *      const row,
                  unsigned int const bias) {
/*----------------------------------------------------------------------------
   Write row[] to the output file according to *outpamP, but with
   'bias' added to each sample value, clipped to maxval.
-----------------------------------------------------------------------------*/
    if (bias == 0)
        pnm_writepamrow(outpamP, row);
    else {
        unsigned int col;

        tuple * const outrow = pnm_allocpamrow(outpamP);

        for (col = 0; col < outpamP->width; ++col) {
            unsigned int plane;

            for (plane = 0; plane < outpamP->depth; ++plane) {
                outrow[col][plane] =
                    MIN(outpamP->maxval, bias + row[col][plane]);
            }
        }
        pnm_writepamrow(outpamP, outrow);

        pnm_freepamrow(outrow);
    }
}



static void
writeUnconvolvedTop(struct pam *              const outpamP,
                    const struct ConvKernel * const convKernelP,
                    tuple **                  const rowbuf) {
/*----------------------------------------------------------------------------
   Write out the top part that we can't convolve because the convolution
   kernel runs off the top of the image.

   Assume those rows are in the window rowbuf[], with the top row of the
   image as the first row in rowbuf[].
-----------------------------------------------------------------------------*/
    unsigned int row;

    for (row = 0; row < convKernelP->rows/2; ++row)
        writePamRowBiased(outpamP, rowbuf[row], convKernelP->bias);
}



static void
writeUnconvolvedBottom(struct pam *              const outpamP,
                       const struct ConvKernel * const convKernelP,
                       unsigned int              const windowHeight,
                       tuple **                  const circMap) {
/*----------------------------------------------------------------------------
  Write out the bottom part that we can't convolve because the convolution
  kernel runs off the bottom of the image.

  Assume the 'windowHeight' rows at the bottom of the image are in the row
  buffer, mapped by 'circMap' such that the top of the window is circMap[0].
-----------------------------------------------------------------------------*/
    unsigned int row;

    for (row = windowHeight - convKernelP->rows / 2;
         row < windowHeight;
         ++row) {

        writePamRowBiased(outpamP, circMap[row], convKernelP->bias);
    }
}



static void
setupCircMap(tuple **     const circMap,
             tuple **     const rowbuf,
             unsigned int const windowHeight,
             unsigned int const topRowbufRow) {
/*----------------------------------------------------------------------------
  Set up circMap[] to reflect the case that index 'topRowbufRow' of rowbuf[]
  is for the topmost row in the window.
-----------------------------------------------------------------------------*/
    unsigned int row;
    unsigned int i;

    i = 0;

    for (row = topRowbufRow; row < windowHeight; ++i, ++row)
        circMap[i] = rowbuf[row];

    for (row = 0; row < topRowbufRow; ++row, ++i)
        circMap[i] = rowbuf[row];
}



static void
convolveGeneralRowPlane(struct pam *              const pamP,
                        tuple **                  const window,
                        const struct ConvKernel * const convKernelP,
                        unsigned int              const plane,
                        tuple *                   const outputrow) {
/*----------------------------------------------------------------------------
   Given a window of input window[], where window[0] is the top row of the
   window and the window is the height of the convolution kernel, convolve
   Plane 'plane' of the row at the center of the window.

   Return the convolved row as outputrow[].

   *pamP describes the rows in window[] (but not the number of rows).

   *convKernelP is the convolution kernel to use.
-----------------------------------------------------------------------------*/
    unsigned int const crowso2 = convKernelP->rows / 2;
    unsigned int const ccolso2 = convKernelP->cols / 2;

    unsigned int col;
    
    for (col = 0; col < pamP->width; ++col) {
        if (col < ccolso2 || col >= pamP->width - ccolso2)
            /* The unconvolved left or right edge */
            outputrow[col][plane] =
                clipSample(convKernelP->bias + window[crowso2][col][plane],
                           pamP->maxval);
        else {
            unsigned int const leftcol = col - ccolso2;
            unsigned int crow;
            float sum;
            sum = 0.0;
            for (crow = 0; crow < convKernelP->rows; ++crow) {
                const tuple * const leftrptr = &window[crow][leftcol];
                unsigned int ccol;
                for (ccol = 0; ccol < convKernelP->cols; ++ccol)
                    sum += leftrptr[ccol][plane] *
                        convKernelP->weight[plane][crow][ccol];
            }
            outputrow[col][plane] =
                makeSample(convKernelP->bias + sum, pamP->maxval);
        }
    }
}



static void
convolveGeneral(struct pam *              const inpamP,
                struct pam *              const outpamP,
                const struct ConvKernel * const convKernelP) {
/*----------------------------------------------------------------------------
   Do the convolution without taking advantage of any useful redundancy in the
   convolution matrix.
-----------------------------------------------------------------------------*/
    tuple ** rowbuf;
        /* A vertical window of the input image.  It holds as many rows as the
           convolution kernel covers -- the rows we're currently using to
           create output rows.  It is a circular buffer.
        */
    tuple ** circMap;
        /* A map from image row number within window to element of rowbuf[].
           E.g. if rowbuf[] if 5 rows high and rowbuf[2] contains the
           topmost row, then circMap[0] == 2, circMap[1] = 3,
           circMap[4] = 1.  You could calculate the same thing with a mod
           function, but that is sometimes more expensive.
        */
    tuple * outputrow;
        /* The convolved row to be output */
    unsigned int row;
        /* Row number of the bottom of the current convolution window;
           i.e. the row to be read or just read from the input file.
        */

    rowbuf = allocRowbuf(outpamP, convKernelP->rows);
    MALLOCARRAY_NOFAIL(circMap, convKernelP->rows);
    outputrow = pnm_allocpamrow(outpamP);

    pnm_writepaminit(outpamP);

    assert(convKernelP->rows > 0);

    readAndScaleRows(inpamP, convKernelP->rows - 1, rowbuf,
                      outpamP->maxval, outpamP->depth);

    writeUnconvolvedTop(outpamP, convKernelP, rowbuf);

    /* Now the rest of the image - read in the row at the bottom of the
       window, then convolve and write out the row in the middle of the
       window.
    */
    for (row = convKernelP->rows - 1; row < inpamP->height; ++row) {
        unsigned int const rowbufRow = row % convKernelP->rows;

        unsigned int plane;

        setupCircMap(circMap, rowbuf, convKernelP->rows,
                     (row + 1) % convKernelP->rows);

        readAndScaleRow(inpamP, rowbuf[rowbufRow],
                        outpamP->maxval, outpamP->depth);

        for (plane = 0; plane < outpamP->depth; ++plane)
            convolveGeneralRowPlane(outpamP, circMap, convKernelP, plane,
                                    outputrow);

        pnm_writepamrow(outpamP, outputrow);
    }
    writeUnconvolvedBottom(outpamP, convKernelP, convKernelP->rows, circMap);

    freeRowbuf(rowbuf, convKernelP->rows);
}



static sample **
allocSum(unsigned int const depth,
         unsigned int const size) {

    sample ** sum;

    MALLOCARRAY(sum, depth);

    if (!sum)
        pm_error("Could not allocate memory for %u planes of sums", depth);
    else {
        unsigned int plane;

        for (plane = 0; plane < depth; ++plane) {
            MALLOCARRAY(sum[plane], size);
            
            if (!sum[plane])
                pm_error("Could not allocate memory for %u sums", size);
        }
    }
    return sum;
}



static void
freeSum(sample **    const sum,
        unsigned int const depth) {

    unsigned int plane;

    for (plane = 0; plane < depth; ++plane)
        free(sum[plane]);

    free(sum);
}



static void
computeInitialColumnSums(struct pam *              const pamP,
                         tuple **                  const window,
                         const struct ConvKernel * const convKernelP,
                         sample **                 const convColumnSum) {
/*----------------------------------------------------------------------------
  Add up the sum of each column of window[][], whose rows are described
  by *inpamP.  The window's height is that of tthe convolution kernel
  *convKernelP.

  Return it as convColumnSum[][].
-----------------------------------------------------------------------------*/
    unsigned int plane;

    for (plane = 0; plane < pamP->depth; ++plane) {
        unsigned int col;

        for (col = 0; col < pamP->width; ++col) {
            unsigned int row;
            for (row = 0, convColumnSum[plane][col] = 0;
                 row < convKernelP->rows;
                 ++row)
                convColumnSum[plane][col] += window[row][col][plane];
        }            
    }
}



static void
convolveRowWithColumnSumsMean(const struct ConvKernel * const convKernelP,
                              struct pam *              const pamP,
                              tuple **                  const window,
                              tuple *                   const outputrow,
                              sample **                 const convColumnSum) {
/*----------------------------------------------------------------------------
  Convolve the rows in window[][] -- one convolution kernel's worth, where
  window[0] is the top.  Put the result in outputrow[].

  Use convColumnSum[][]: the sum of the pixels in each column over the
  convolution window, where convColumnSum[P][C] is the sum for Plane P of
  Column C.

  Assume the convolution weight is the same everywhere within the convolution
  matrix.  Ergo, we don't need any more information about the contents of a
  column than the sum of its pixels.

  Except that we need the individual input pixels for the edges (which can't
  be convolved because the convolution window runs off the edge).
-----------------------------------------------------------------------------*/
    unsigned int plane;
    
    for (plane = 0; plane < pamP->depth; ++plane) {
        unsigned int const crowso2 = convKernelP->rows / 2;
        unsigned int const ccolso2 = convKernelP->cols / 2;
        float const weight = convKernelP->weight[plane][0][0];

        unsigned int col;
        sample gisum;

        for (col = 0, gisum = 0; col < pamP->width; ++col) {
            if (col < ccolso2 || col >= pamP->width - ccolso2) {
                /* The unconvolved left or right edge */
                outputrow[col][plane] =
                    clipSample(convKernelP->bias +
                               window[crowso2][col][plane],
                               pamP->maxval);
            } else {
                if (col == ccolso2) {
                    unsigned int const leftcol = col - ccolso2;

                    unsigned int ccol;

                    for (ccol = 0; ccol < convKernelP->cols; ++ccol)
                        gisum += convColumnSum[plane][leftcol + ccol];
                } else {
                    /* Column numbers to subtract or add to isum */
                    unsigned int const subcol = col - ccolso2 - 1;
                    unsigned int const addcol = col + ccolso2;  

                    gisum -= convColumnSum[plane][subcol];
                    gisum += convColumnSum[plane][addcol];
                }
                outputrow[col][plane] =
                    makeSample(convKernelP->bias + gisum * weight,
                               pamP->maxval);
            }
        }
    }
}



static void
convolveRowWithColumnSumsVertical(
    const struct ConvKernel * const convKernelP,
    struct pam *              const pamP,
    tuple **                  const window,
    tuple *                   const outputrow,
    sample **                 const convColumnSum) {
/*----------------------------------------------------------------------------
  Convolve the rows in window[][] -- one convolution kernel's worth, where
  window[0] is the top.  Put the result in outputrow[].

  Use convColumnSum[][]: the sum of the pixels in each column over the
  convolution window, where convColumnSum[P][C] is the sum for Plane P of
  Column C.

  Assume the convolution weight is the same everywhere within a column.  Ergo,
  we don't need any more information about the contents of a column than the
  sum of its pixels.

  Except that we need the individual input pixels for the edges (which can't
  be convolved because the convolution window runs off the edge).
-----------------------------------------------------------------------------*/
    unsigned int const crowso2 = convKernelP->rows / 2;
    unsigned int const ccolso2 = convKernelP->cols / 2;

    unsigned int plane;

    for (plane = 0; plane < pamP->depth; ++plane) {
        unsigned int col;
    
        for (col = 0; col < pamP->width; ++col) {
            if (col < ccolso2 || col >= pamP->width - ccolso2) {
                /* The unconvolved left or right edge */
                outputrow[col][plane] =
                    clipSample(convKernelP->bias +
                               window[crowso2][col][plane],
                               pamP->maxval);
            } else {
                unsigned int const leftcol = col - ccolso2;
                unsigned int ccol;
                float sum;

                sum = 0.0;

                for (ccol = 0; ccol < convKernelP->cols; ++ccol)
                    sum += convColumnSum[plane][leftcol + ccol] *
                        convKernelP->weight[plane][0][ccol];

                outputrow[col][plane] =
                    makeSample(convKernelP->bias + sum, pamP->maxval);
            }
        }
    }
}



static void
convolveMeanRowPlane(struct pam *              const pamP,
                     tuple **                  const window,
                     const struct ConvKernel * const convKernelP,
                     unsigned int              const plane,
                     tuple *                   const outputrow,
                     sample *                  const convColumnSum) {
/*----------------------------------------------------------------------------
  Convolve plane 'plane' of one row of the image.  window[] is a vertical
  window of the input image, one convolution kernel plus one row high.  The
  top row (window[0] is the row that just passed out of the convolution
  window, whereas the bottom row is the row that just entered it.

  *pamP describes the tuple rows in window[] and also 'outputrow' (they are
  the same).

  Return the convolution result as outputrow[].

  We update convColumnSum[] for use in convolving later rows.
-----------------------------------------------------------------------------*/
    unsigned int const crowso2 = convKernelP->rows / 2;
    unsigned int const ccolso2 = convKernelP->cols / 2;
    float const weight = convKernelP->weight[plane][0][0];
    unsigned int const subrow = 0;
        /* Row just above convolution window -- what we subtract from
           running sum
        */
    unsigned int const addrow = 1 + (convKernelP->rows - 1);
        /* Bottom row of convolution window: What we add to running sum */

    unsigned int col;
    sample gisum;

    for (col = 0, gisum = 0; col < pamP->width; ++col) {
        if (col < ccolso2 || col >= pamP->width - ccolso2) {
            /* The unconvolved left or right edge */
            outputrow[col][plane] =
                clipSample(convKernelP->bias + window[crowso2][col][plane],
                           pamP->maxval);
        } else {
            if (col == ccolso2) {
                unsigned int const leftcol = col - ccolso2;

                unsigned int ccol;

                for (ccol = 0; ccol < convKernelP->cols; ++ccol) {
                    sample * const thisColumnSumP =
                        &convColumnSum[leftcol + ccol];
                    *thisColumnSumP = *thisColumnSumP
                        - window[subrow][ccol][plane]
                        + window[addrow][ccol][plane];
                    gisum += *thisColumnSumP;
                }
            } else {
                /* Column numbers to subtract or add to isum */
                unsigned int const subcol = col - ccolso2 - 1;
                unsigned int const addcol = col + ccolso2;  
                
                convColumnSum[addcol] = convColumnSum[addcol]
                    - window[subrow][addcol][plane]
                    + window[addrow][addcol][plane];
                
                gisum = gisum - convColumnSum[subcol] + convColumnSum[addcol];
            }
            outputrow[col][plane] =
                makeSample(convKernelP->bias + gisum * weight, pamP->maxval);
        }
    }
}



typedef void convolver(struct pam *              const inpamP,
                       struct pam *              const outpamP,
                       const struct ConvKernel * const convKernelP);



static convolver convolveMean;

static void
convolveMean(struct pam *              const inpamP,
             struct pam *              const outpamP,
             const struct ConvKernel * const convKernelP) {
/*----------------------------------------------------------------------------
  Mean Convolution

  This is for the common case where you just want the target pixel replaced
  with the average value of its neighbors.  This can work much faster than the
  general case because you can reduce the number of floating point operations
  that are required since all the weights are the same.  You will only need to
  multiply by the weight once, not for every pixel in the convolution matrix.

  This algorithm works as follows: At a certain vertical position in the
  image, create sums for each column fragment of the convolution height all
  the way across the image.  Then add those sums across the convolution width
  to obtain the total sum over the convolution area and multiply that sum by
  the weight.  As you move left to right, to calculate the next output pixel,
  take the total sum you just generated, add in the value of the next column
  and subtract the value of the leftmost column.  Multiply that by the weight
  and that's it.  As you move down a row, calculate new column sums by using
  previous sum for that column and adding in pixel on current row and
  subtracting pixel in top row.

  We assume the convolution kernel is uniform -- same weights everywhere.

  We assume the output is PGM and the input is PGM or PBM.
-----------------------------------------------------------------------------*/
    unsigned int const windowHeight = convKernelP->rows + 1;
        /* The height of the window we keep in the row buffer.  The buffer
           contains the rows covered by the convolution kernel, plus the row
           immediately above that.  The latter is there because to compute
           the sliding mean, we need to subtract off the row that the
           convolution kernel just slid past.
        */
    unsigned int const crowso2 = convKernelP->rows / 2;
        /* Number of rows of the convolution window above/below the current
           row.  Note that the convolution window is always an odd number
           of rows, so this rounds down.
        */
    tuple ** rowbuf;
        /* Same as in convolveGeneral */
    tuple ** circMap;
        /* Same as in convolveGeneral */
    tuple * outputrow;
        /* Same as in convolveGeneral */
    unsigned int row;
        /* Row number of the row currently being convolved; i.e. the row
           at the center of the current convolution window and the row of
           the output file to be output next.
        */
    sample ** convColumnSum;  /* Malloc'd */
        /* convColumnSum[plane][col] is the sum of Plane 'plane' of all the
           pixels in the Column 'col' of the image within the current vertical
           convolution window.  I.e. if our convolution kernel is 5 rows high
           and we're now looking at Rows 10-15, convColumn[0][3] is the sum of
           Plane 0 of Column 3, Rows 10-15.
        */

    rowbuf = allocRowbuf(outpamP, windowHeight);
    MALLOCARRAY_NOFAIL(circMap, windowHeight);
    outputrow = pnm_allocpamrow(outpamP);

    convColumnSum = allocSum(outpamP->depth, outpamP->width);

    pnm_writepaminit(outpamP);

    readAndScaleRows(inpamP, convKernelP->rows, rowbuf,
                      outpamP->maxval, outpamP->depth);

    writeUnconvolvedTop(outpamP, convKernelP, rowbuf);

    setupCircMap(circMap, rowbuf, windowHeight, 0);

    /* Convolve the first window the long way */
    computeInitialColumnSums(inpamP, circMap, convKernelP, convColumnSum);

    convolveRowWithColumnSumsMean(convKernelP, outpamP, circMap,
                                  outputrow, convColumnSum);

    pnm_writepamrow(outpamP, outputrow);

    /* For all subsequent rows do it this way as the columnsums have been
       generated.  Now we can use them to reduce further calculations.  We
       slide the window down a row at a time by reading a row into the bottom
       of the circular buffer, adding it to the column sums, then subtracting
       out the row at the top of the circular buffer.
    */
    for (row = crowso2 + 1; row < inpamP->height - crowso2; ++row) {
        unsigned int const windowBotRow = row + crowso2;
            /* Row number of bottom-most row present in rowbuf[],
               which is the bottom of the convolution window for the current
               row.
            */
        unsigned int const windowTopRow = row - crowso2 - 1;
            /* Row number of top-most row present in rowbuf[], which is
               the top row of the convolution window for the previous row:
               just above the convolution window for the current row.
            */
        unsigned int plane;

        readAndScaleRow(inpamP, rowbuf[windowBotRow % windowHeight],
                        outpamP->maxval, outpamP->depth);

        setupCircMap(circMap, rowbuf, windowHeight,
                     windowTopRow % windowHeight);

        for (plane = 0; plane < outpamP->depth; ++plane)
            convolveMeanRowPlane(outpamP, circMap, convKernelP, plane,
                                 outputrow, convColumnSum[plane]);

        pnm_writepamrow(outpamP, outputrow);
    }
    writeUnconvolvedBottom(outpamP, convKernelP, windowHeight, circMap);

    freeSum(convColumnSum, outpamP->depth);
    freeRowbuf(rowbuf, windowHeight);
}



static sample ***
allocRowSum(unsigned int const depth,
            unsigned int const height,
            unsigned int const width) {

    sample *** sum;

    MALLOCARRAY(sum, depth);

    if (!sum)
        pm_error("Could not allocate memory for %u planes of sums", depth);
    else {
        unsigned int plane;

        for (plane = 0; plane < depth; ++plane) {
            MALLOCARRAY(sum[plane], height);
            
            if (!sum[plane])
                pm_error("Could not allocate memory for %u rows of sums",
                         height);
            else {
                unsigned int row;

                for (row = 0; row < height; ++row) {
                    MALLOCARRAY(sum[plane][row], width);
                    
                    if (!sum[plane][row])
                        pm_error("Could not allocate memory "
                                 "for a row of sums");
                }
            }
        }
    }
    return sum;
}



static void
freeRowSum(sample ***   const sum,
           unsigned int const depth,
           unsigned int const height) {

    unsigned int plane;

    for (plane = 0; plane < depth; ++plane) {
        unsigned int row;

        for (row = 0; row < height; ++row)
            free(sum[plane][row]);

        free(sum[plane]);
    }
    free(sum);
}



static void
convolveHorizontalRowPlane0(struct pam *              const outpamP,
                            tuple **                  const window,
                            const struct ConvKernel * const convKernelP,
                            unsigned int              const plane,
                            tuple *                   const outputrow,
                            sample **                 const sumWindow) {
/*----------------------------------------------------------------------------
   Convolve the first convolvable row and generate the row sums from scratch.
   (For subsequent rows, Caller can just incrementally modify the row sums).
-----------------------------------------------------------------------------*/
    unsigned int const crowso2 = convKernelP->rows / 2;
    unsigned int const ccolso2 = convKernelP->cols / 2;

    unsigned int col;

    for (col = 0; col < outpamP->width; ++col) {
        if (col < ccolso2 || col >= outpamP->width - ccolso2) {
            /* The unconvolved left or right edge */
            outputrow[col][plane] =
                clipSample(convKernelP->bias + window[crowso2][col][plane],
                           outpamP->maxval);
        } else {
            float matrixSum;

            if (col == ccolso2) {
                /* This is the first column for which the entire convolution
                   kernel fits within the image horizontally.  I.e. the window
                   starts at the left edge of the image.
                */
                unsigned int const leftcol = 0;
            
                unsigned int crow;

                for (crow = 0, matrixSum = 0.0;
                     crow < convKernelP->rows;
                     ++crow) {
                    tuple * const tuplesInWindow = &window[crow][leftcol];

                    unsigned int ccol;
                
                    sumWindow[crow][col] = 0;
                    for (ccol = 0; ccol < convKernelP->cols; ++ccol)
                        sumWindow[crow][col] += tuplesInWindow[ccol][plane];
                    matrixSum +=
                        sumWindow[crow][col] *
                        convKernelP->weight[plane][crow][0];
                }
            } else {
                unsigned int const subcol  = col - ccolso2 - 1;
                unsigned int const addcol  = col + ccolso2;

                unsigned int crow;
                
                for (crow = 0, matrixSum = 0.0;
                     crow < convKernelP->rows;
                     ++crow) {
                    sumWindow[crow][col] = sumWindow[crow][col-1] +
                        + window[crow][addcol][plane]
                        - window[crow][subcol][plane];
                    matrixSum +=
                        sumWindow[crow][col] *
                        convKernelP->weight[plane][crow][0];
                }
            }
            outputrow[col][plane] =
                makeSample(convKernelP->bias + matrixSum, outpamP->maxval);
        }
    }
}



static void
setupCircMap2(tuple **     const rowbuf,
              sample **    const convRowSum,
              tuple **     const circMap,
              sample **    const sumCircMap,
              unsigned int const windowTopRow,
              unsigned int const windowHeight) {

    unsigned int const toprow = windowTopRow % windowHeight;
    
    unsigned int crow;
    unsigned int i;


    i = 0;

    for (crow = toprow; crow < windowHeight; ++i, ++crow) {
        circMap[i] = rowbuf[crow];
        sumCircMap[i] = convRowSum[crow];
    }
    for (crow = 0; crow < toprow; ++crow, ++i) {
        circMap[i] = rowbuf[crow];
        sumCircMap[i] = convRowSum[crow];
    }
}



static void
convolveHorizontalRowPlane(struct pam *              const pamP,
                           tuple **                  const window,
                           const struct ConvKernel * const convKernelP,
                           unsigned int              const plane,
                           tuple *                   const outputrow,
                           sample **                 const sumWindow) {
/*----------------------------------------------------------------------------
   Convolve the row at the center of the convolution window described
   by *convKernelP, where window[][] contains the input image tuples
   for the window.  *pamP describes the rows in it, but its height is
   one convolution window.

   Convolve only the Plane 'plane' samples.

   sumWindow[][] mirrors window[].  sumWindow[R] applies to window[R].
   sumWindow[R][C] is the sum of samples in row R of the convolution window
   centered on Column C.  We assume the convolution weights are the same
   everywhere within a row of the kernel, so that we can generate these
   sums incrementally, moving to the right through the image.
-----------------------------------------------------------------------------*/
    unsigned int const ccolso2 = convKernelP->cols / 2;
    unsigned int const crowso2 = convKernelP->rows / 2;

    unsigned int const newrow  = convKernelP->rows - 1;

    unsigned int col;

    for (col = 0; col < pamP->width; ++col) {
        float matrixSum;

        if (col < ccolso2 || col >= pamP->width - ccolso2) {
            outputrow[col][plane] =
                clipSample(convKernelP->bias + window[crowso2][col][plane],
                           pamP->maxval);
        } else if (col == ccolso2) {
            unsigned int const leftcol = 0;
                /* Window is up againt left edge of image */

            {
                unsigned int ccol;
                sumWindow[newrow][col] = 0;
                for (ccol = 0; ccol < convKernelP->cols; ++ccol)
                    sumWindow[newrow][col] +=
                        window[newrow][leftcol + ccol][plane];
            }
            {
                unsigned int crow;
                for (crow = 0, matrixSum = 0.0;
                     crow < convKernelP->rows;
                     ++crow) {
                    matrixSum += sumWindow[crow][col] *
                        convKernelP->weight[plane][crow][0];
                }
            }
        } else {
            unsigned int const subcol  = col - ccolso2 - 1;
            unsigned int const addcol  = col + ccolso2;  

            unsigned int crow;

            sumWindow[newrow][col] =
                sumWindow[newrow][col-1]
                + window[newrow][addcol][plane]
                - window[newrow][subcol][plane];

            for (crow = 0, matrixSum = 0.0; crow < convKernelP->rows; ++crow) {
                matrixSum += sumWindow[crow][col] *
                    convKernelP->weight[plane][crow][0];
            }
        }
        outputrow[col][plane] =
            makeSample(convKernelP->bias + matrixSum, pamP->maxval);
    }
}



static convolver convolveHorizontal;

static void
convolveHorizontal(struct pam *              const inpamP,
                   struct pam *              const outpamP,
                   const struct ConvKernel * const convKernelP) {
/*----------------------------------------------------------------------------
  Horizontal Convolution

  Similar idea to using columnsums of the Mean and Vertical convolution, but
  uses temporary sums of row values.  Need to multiply by weights once for
  each row in the convolution kernel.  Each time we start a new line, we must
  recalculate the initials rowsums for the newest row only.  Uses queue to
  still access previous row sums.
-----------------------------------------------------------------------------*/
    unsigned int const crowso2 = convKernelP->rows / 2;
        /* Same as in convolveMean */
    unsigned int const windowHeight = convKernelP->rows;
        /* Same as in convolveMean */

    tuple ** rowbuf;
        /* Same as in convolveGeneral */
    tuple ** circMap;
        /* Same as in convolveGeneral */
    tuple * outputrow;
        /* Same as in convolveGeneral */
    unsigned int plane;
    sample *** convRowSum;  /* Malloc'd */
    sample ** sumCircMap;  /* Malloc'd */

    rowbuf = allocRowbuf(inpamP, windowHeight);
    MALLOCARRAY_NOFAIL(circMap, windowHeight);
    outputrow = pnm_allocpamrow(outpamP);

    convRowSum = allocRowSum(outpamP->depth, windowHeight, outpamP->width);
    MALLOCARRAY_NOFAIL(sumCircMap, windowHeight);

    pnm_writepaminit(outpamP);

    readAndScaleRows(inpamP, convKernelP->rows, rowbuf,
                      outpamP->maxval, outpamP->depth);

    writeUnconvolvedTop(outpamP, convKernelP, rowbuf);

    setupCircMap(circMap, rowbuf, windowHeight, 0);

    /* Convolve the first convolvable row and generate convRowSum[][] */
    for (plane = 0; plane < outpamP->depth; ++plane) {
        unsigned int crow;

        for (crow = 0; crow < convKernelP->rows; ++crow)
            sumCircMap[crow] = convRowSum[plane][crow];
 
        convolveHorizontalRowPlane0(outpamP, circMap, convKernelP, plane,
                                    outputrow, sumCircMap);
    }
    pnm_writepamrow(outpamP, outputrow);

    /* Convolve the rest of the rows, using convRowSum[] */

    for (plane = 0; plane < outpamP->depth; ++plane) {
        unsigned int row;
            /* Same as in convolveMean */

        for (row = convKernelP->rows/2 + 1;
             row < inpamP->height - convKernelP->rows/2;
             ++row) {

            unsigned int const windowBotRow = row + crowso2;
            unsigned int const windowTopRow = row - crowso2;
                /* Same as in convolveMean */

            readAndScaleRow(inpamP, rowbuf[windowBotRow % windowHeight],
                            outpamP->maxval, outpamP->depth);
            
            setupCircMap2(rowbuf, convRowSum[plane], circMap, sumCircMap,
                          windowTopRow, windowHeight);

            convolveHorizontalRowPlane(outpamP, circMap, convKernelP, plane,
                                       outputrow, sumCircMap);
            
            pnm_writepamrow(outpamP, outputrow);
        }
    }

    writeUnconvolvedBottom(outpamP, convKernelP, windowHeight, circMap);

    freeRowSum(convRowSum, outpamP->depth, windowHeight);
    freeRowbuf(rowbuf, windowHeight);
}



static void
convolveVerticalRowPlane(struct pam *              const pamP,
                         tuple **                  const circMap,
                         const struct ConvKernel * const convKernelP,
                         unsigned int              const plane,
                         tuple *                   const outputrow,
                         sample *                  const convColumnSum) {

    unsigned int const crowso2 = convKernelP->rows / 2;
    unsigned int const ccolso2 = convKernelP->cols / 2;

    unsigned int const subrow = 0;
        /* Row just above convolution window -- what we subtract from
           running sum
        */
    unsigned int const addrow = 1 + (convKernelP->rows - 1);
        /* Bottom row of convolution window: What we add to running sum */
    
    unsigned int col;

    for (col = 0; col < pamP->width; ++col) {
        if (col < ccolso2 || col >= pamP->width - ccolso2) {
            /* The unconvolved left or right edge */
            outputrow[col][plane] =
                clipSample(convKernelP->bias + circMap[crowso2][col][plane],
                           pamP->maxval);
        } else {
            float matrixSum;

            if (col == ccolso2) {
                unsigned int const leftcol = 0;
                    /* Convolution window is againt left edge of image */

                unsigned int ccol;

                /* Slide window down in the first kernel's worth of columns */
                for (ccol = 0; ccol < convKernelP->cols; ++ccol) {
                    convColumnSum[leftcol + ccol] +=
                        circMap[addrow][leftcol + ccol][plane];
                    convColumnSum[leftcol + ccol] -=
                        circMap[subrow][leftcol + ccol][plane];
                }
                for (ccol = 0, matrixSum = 0.0;
                     ccol < convKernelP->cols;
                     ++ccol) {
                    matrixSum += convColumnSum[leftcol + ccol] *
                        convKernelP->weight[plane][0][ccol];
                }
            } else {
                unsigned int const leftcol = col - ccolso2;
                unsigned int const addcol  = col + ccolso2;

                unsigned int ccol;

                /* Slide window down in the column that just entered the
                   window
                */
                convColumnSum[addcol] += circMap[addrow][addcol][plane];
                convColumnSum[addcol] -= circMap[subrow][addcol][plane];

                for (ccol = 0, matrixSum = 0.0;
                     ccol < convKernelP->cols;
                     ++ccol) {
                    matrixSum += convColumnSum[leftcol + ccol] *
                        convKernelP->weight[plane][0][ccol];
                }
            }
            outputrow[col][plane] =
                makeSample(convKernelP->bias + matrixSum, pamP->maxval);
        }
    }
}



static convolver convolveVertical;

static void
convolveVertical(struct pam *              const inpamP,
                 struct pam *              const outpamP,
                 const struct ConvKernel * const convKernelP) {

    /* Uses column sums as in mean convolution, above */

    unsigned int const windowHeight = convKernelP->rows + 1;
        /* Same as in convolveMean */
    unsigned int const crowso2 = convKernelP->rows / 2;
        /* Same as in convolveMean */

    tuple ** rowbuf;
        /* Same as in convolveGeneral */
    tuple ** circMap;
        /* Same as in convolveGeneral */
    tuple * outputrow;
        /* Same as in convolveGeneral */
    unsigned int row;
        /* Row number of next row to read in from the file */
    sample ** convColumnSum;  /* Malloc'd */
        /* Same as in convolveMean() */

    rowbuf = allocRowbuf(inpamP, windowHeight);
    MALLOCARRAY_NOFAIL(circMap, windowHeight);
    outputrow = pnm_allocpamrow(outpamP);

    convColumnSum = allocSum(outpamP->depth, outpamP->width);

    pnm_writepaminit(outpamP);

    readAndScaleRows(inpamP, convKernelP->rows, rowbuf,
                      outpamP->maxval, outpamP->depth);

    writeUnconvolvedTop(outpamP, convKernelP, rowbuf);

    setupCircMap(circMap, rowbuf, windowHeight, 0);

    /* Convolve the first window the long way */
    computeInitialColumnSums(inpamP, circMap, convKernelP, convColumnSum);

    convolveRowWithColumnSumsVertical(convKernelP, outpamP, circMap,
                                      outputrow, convColumnSum);

    pnm_writepamrow(outpamP, outputrow);

    for (row = crowso2 + 1; row < inpamP->height - crowso2; ++row) {
        unsigned int const windowBotRow = row + crowso2;
            /* Same as in convolveMean */
        unsigned int const windowTopRow = row - crowso2 - 1;
            /* Same as in convolveMean */
        unsigned int plane;

        readAndScaleRow(inpamP, rowbuf[windowBotRow % windowHeight],
                        outpamP->maxval, outpamP->depth);

        /* Remember the window is one row higher than the convolution
           kernel.  The top row in the window is not part of this convolution.
        */

        setupCircMap(circMap, rowbuf, windowHeight,
                     windowTopRow % windowHeight);

        for (plane = 0; plane < outpamP->depth; ++plane)
            convolveVerticalRowPlane(outpamP, circMap, convKernelP, plane,
                                     outputrow, convColumnSum[plane]);

        pnm_writepamrow(outpamP, outputrow);
    }
    writeUnconvolvedBottom(outpamP, convKernelP, windowHeight, circMap);

    freeSum(convColumnSum, outpamP->depth);
    freeRowbuf(rowbuf, windowHeight);
}



struct convolveType {
    convolver * convolve;
};



static bool
convolutionIncludesHorizontal(const struct ConvKernel * const convKernelP) {

    bool horizontal;
    unsigned int row;

    for (row = 0, horizontal = TRUE;
         row < convKernelP->rows && horizontal;
        ++row) {
        unsigned int col;
        for (col = 1, horizontal = TRUE;
             col < convKernelP->cols && horizontal;
             ++col) {

            unsigned int plane;

            for (plane = 0; plane < convKernelP->planes; ++plane) {
                if (convKernelP->weight[plane][row][col] !=
                    convKernelP->weight[plane][row][0])
                    horizontal = FALSE;
            }
        }
    }
    return horizontal;
}



static bool
convolutionIncludesVertical(const struct ConvKernel * const convKernelP) {

    bool vertical;
    unsigned int col;

    for (col = 0, vertical = TRUE;
         col < convKernelP->cols && vertical;
        ++col) {
        unsigned int row;
        for (row = 1, vertical = TRUE;
             row < convKernelP->rows && vertical;
             ++row) {

            unsigned int plane;

            for (plane = 0; plane < convKernelP->planes; ++plane) {
                if (convKernelP->weight[plane][row][col] !=
                    convKernelP->weight[plane][0][col])
                    vertical = FALSE;
            }
        }
    }
    return vertical;
}



static void
determineConvolveType(const struct ConvKernel * const convKernelP,
                      struct convolveType *     const typeP) {
/*----------------------------------------------------------------------------
   Determine which form of convolution is best to convolve the kernel
   *convKernelP over tuples[][].  The general form always works, but with some
   special case convolution matrices, faster forms of convolution are
   possible.

   We don't check for the case that the planes can have differing types.  We
   handle only cases where all planes are of the same special case.
-----------------------------------------------------------------------------*/
    bool const horizontal = convolutionIncludesHorizontal(convKernelP);
    bool const vertical   = convolutionIncludesVertical(convKernelP);

    if (horizontal && vertical) {
        pm_message("Convolution is a simple mean horizontally and vertically");
        typeP->convolve = convolveMean;
    } else if (horizontal) {
        pm_message("Convolution is a simple mean horizontally");
        typeP->convolve = convolveHorizontal;
    } else if (vertical) {
        pm_message("Convolution is a simple mean vertically");
        typeP->convolve = convolveVertical;
    } else {
        typeP->convolve = convolveGeneral;
    }
}



int
main(int argc, char * argv[]) {

    struct cmdlineInfo cmdline;
    FILE * ifP;
    struct convolveType convolveType;
    struct ConvKernel * convKernelP;
    struct pam inpam;
    struct pam outpam;

    pnm_init(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    ifP = pm_openr(cmdline.inputFileName);

    pnm_readpaminit(ifP, &inpam, PAM_STRUCT_SIZE(allocation_depth));

    getKernel(cmdline, inpam.depth, &convKernelP);

    outpam = inpam;  /* initial value */

    outpam.file = stdout;

    if ((PNM_FORMAT_TYPE(inpam.format) == PBM_TYPE ||
         PNM_FORMAT_TYPE(inpam.format) == PGM_TYPE) &&
        convKernelP->planes == 3) {

        pm_message("promoting to PPM");
        outpam.format = PPM_FORMAT;
    }

    outpam.depth = MAX(inpam.depth, convKernelP->planes);

    pnm_setminallocationdepth(&inpam, MAX(inpam.depth, outpam.depth));

    validateEnoughImageToConvolve(&inpam, convKernelP);

    /* Handle certain special cases when runtime can be improved. */

    determineConvolveType(convKernelP, &convolveType);

    convolveType.convolve(&inpam, &outpam, convKernelP);

    convKernelDestroy(convKernelP);
    pm_close(stdout);
    pm_close(ifP);

    return 0;
}



/******************************************************************************
                            SOME CHANGE HISTORY
*******************************************************************************

 Version 2.0.1 Changes
 ---------------------
 Fixed four lines that were improperly allocated as sizeof( float ) when they
 should have been sizeof( long ).

 Version 2.0 Changes
 -------------------

 Version 2.0 was written by Mike Burns (derived from Jef Poskanzer's
 original) in January 1995.

 Reduce run time by general optimizations and handling special cases of
 convolution matrices.  Program automatically determines if convolution 
 matrix is one of the types it can make use of so no extra command line
 arguments are necessary.

 Examples of convolution matrices for the special cases are

    Mean       Horizontal    Vertical
    x x x        x x x        x y z
    x x x        y y y        x y z
    x x x        z z z        x y z

 I don't know if the horizontal and vertical ones are of much use, but
 after working on the mean convolution, it gave me ideas for the other two.

 Some other compiler dependent optimizations
 -------------------------------------------
 Created separate functions as code was getting too large to put keep both
 PGM and PPM cases in same function and also because SWITCH statement in
 inner loop can take progressively more time the larger the size of the 
 convolution matrix.  GCC is affected this way.

 Removed use of MOD (%) operator from innermost loop by modifying manner in
 which the current xelbuf[] is chosen.

 This is from the file pnmconvol.README, dated August 1995, extracted in
 April 2000, which was in the March 1994 Netpbm release:

 ----------------------------------------------------------------------------- 
 This is a faster version of the pnmconvol.c program that comes with netpbm.
 There are no changes to the command line arguments, so this program can be
 dropped in without affecting the way you currently run it.  An updated man
 page is also included.
 
 My original intention was to improve the running time of applying a
 neighborhood averaging convolution matrix to an image by using a different
 algorithm, but I also improved the run time of performing the general
 convolution by optimizing that code.  The general convolution runs in 1/4 to
 1/2 of the original time and neighborhood averaging runs in near constant
 time for the convolution masks I tested (3x3, 5x5, 7x7, 9x9).
 
 Sample times for two computers are below.  Times are in seconds as reported
 by /bin/time for a 512x512 pgm image.
 
 Matrix                  IBM RS6000      SUN IPC
 Size & Type                220
 
 3x3
 original pnmconvol         6.3            18.4
 new general case           3.1             6.0
 new average case           1.8             2.6
 
 5x5
 original pnmconvol        11.9            44.4
 new general case           5.6            11.9
 new average case           1.8             2.6
 
 7x7
 original pnmconvol        20.3            82.9
 new general case           9.4            20.7
 new average case           1.8             2.6
 
 9x9
 original pnmconvol        30.9           132.4
 new general case          14.4            31.8
 new average case           1.8             2.6
 
 
 Send all questions/comments/bugs to me at burns@chem.psu.edu.
 
 - Mike
 
 ----------------------------------------------------------------------------
 Mike Burns                                              System Administrator
 burns@chem.psu.edu                                   Department of Chemistry
 (814) 863-2123                             The Pennsylvania State University
 ----------------------------------------------------------------------------

*/
