/*=============================================================================
                                 pamdither
===============================================================================
  By Bryan Henderson, July 2006.

  Contributed to the public domain.

  This is meant to replace Ppmdither by Christos Zoulas, 1991.
=============================================================================*/
#include <assert.h>

#include "pm_c_util.h"
#include "mallocvar.h"
#include "nstring.h"
#include "shhopt.h"
#include "pam.h"

/* Besides having to have enough memory available, the limiting factor
   in the dithering matrix power is the size of the dithering value.
   We need 2*dith_power bits in an unsigned int.  We also reserve
   one bit to give headroom to do calculations with these numbers.
*/
#define MAX_DITH_POWER (((unsigned)sizeof(unsigned int)*8 - 1) / 2)


struct colorResolution {
    unsigned int c[3];
        /* comp[PAM_RED_PLANE] is number of distinct red levels, etc. */
};

#define RED PAM_RED_PLANE
#define GRN PAM_GRN_PLANE
#define BLU PAM_BLU_PLANE

struct cmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    const char * inputFileName;  /* File name of input file */
    unsigned int dim;
    struct colorResolution colorRes;
    unsigned int verbose;
};



static void
parseCommandLine(int argc, const char ** const argv,
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

    unsigned int dimSpec, redSpec, greenSpec, blueSpec;

    MALLOCARRAY_NOFAIL(option_def, 100);
    
    option_def_index = 0;   /* incremented by OPTENT3 */
    OPTENT3(0, "dim",          OPT_UINT, 
            &cmdlineP->dim,            &dimSpec,                  0);
    OPTENT3(0, "red",          OPT_UINT, 
            &cmdlineP->colorRes.c[RED],   &redSpec,       0);
    OPTENT3(0, "green",        OPT_UINT, 
            &cmdlineP->colorRes.c[GRN],   &greenSpec,     0);
    OPTENT3(0, "blue",         OPT_UINT,
            &cmdlineP->colorRes.c[BLU],   &blueSpec,      0);
    OPTENT3(0, "verbose",      OPT_FLAG,
            NULL,                      &cmdlineP->verbose,        0);

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = FALSE;  /* We have no parms that are negative numbers */

    pm_optParseOptions3(&argc, (char **)argv, opt, sizeof(opt), 0);
        /* Uses and sets argc, argv, and some of *cmdline_p and others. */

    if (!dimSpec)
        cmdlineP->dim = 4;

    if (cmdlineP->dim > MAX_DITH_POWER)
        pm_error("Dithering matrix power %u (-dim) is too large.  "
                 "Must be <= %u",
                 cmdlineP->dim, MAX_DITH_POWER);
        
    if (redSpec) {
        if (cmdlineP->colorRes.c[RED] < 2)
            pm_error("-red must be at least 2.  You specified %u",
                     cmdlineP->colorRes.c[RED]);
    } else
        cmdlineP->colorRes.c[RED] = 5;

    if (greenSpec) {
        if (cmdlineP->colorRes.c[GRN] < 2)
            pm_error("-green must be at least 2.  You specified %u",
                     cmdlineP->colorRes.c[GRN]);
    } else
        cmdlineP->colorRes.c[GRN] = 9;

    if (blueSpec) {
        if (cmdlineP->colorRes.c[BLU] < 2)
            pm_error("-blue must be at least 2.  You specified %u",
                     cmdlineP->colorRes.c[BLU]);
    } else
        cmdlineP->colorRes.c[BLU] = 5;

    if (argc-1 > 1)
        pm_error("Program takes at most one argument: the input file "
                 "specification.  "
                 "You specified %d arguments.", argc-1);
    if (argc-1 < 1)
        cmdlineP->inputFileName = "-";
    else
        cmdlineP->inputFileName = argv[1];
}



typedef struct {
/*----------------------------------------------------------------------------
   A scaler object scales a red/green/blue triple, each component having its
   own maxval, to a tuple having another maxval.  That maxval is the same for
   all three components.  The input and output maxvals are characteristic of
   the scaler.

   Example: The scaler scales from a red value of 0-3, green value of
   0-3, and blue value of 0-1 to a tuple with maxval 255.  So you can
   ask it to scale (1,1,1) and it responds with (85, 85, 255).
-----------------------------------------------------------------------------*/
    struct colorResolution colorRes;
        /* Number of values of each color component possible, i.e. maxval
           plus 1
        */
    tuple * out;
        /* Malloced array that provides the scaled output when indexed by a
           certain function (see scaler_scale()) of the input red, green, and
           blue values.
        */
} scaler;    



static tuple *
allocScalerMap(unsigned int const size) {
    /* The tuple row data structure starts with 'size' pointers to
       the tuples, immediately followed by the 'size' tuples
       themselves.  Each tuple consists of 3 samples.  
    */

    unsigned int const depth = 3;
    unsigned int const bytesPerTuple = depth * sizeof(sample);

    tuple * map;

    map = malloc(size * (sizeof(tuple *) + bytesPerTuple));
                      
    if (map != NULL) {
        /* Now we initialize the pointers to the individual tuples
           to make this a regulation C two dimensional array.  
        */
        char * p;
        unsigned int i;
        
        p = (char*) (map + size);  /* location of Tuple 0 */
        for (i = 0; i < size; ++i) {
            map[i] = (tuple) p;
            p += bytesPerTuple;
        }
    }
    return map;
}



static void
scaler_create(sample                 const outputMaxval,
              struct colorResolution const colorRes,
              scaler **              const scalerPP) {

    scaler * scalerP;
    unsigned int mapSize;
    
    if (UINT_MAX / colorRes.c[RED] / colorRes.c[GRN] / colorRes.c[BLU] < 1)
        pm_error("red/green/blue dimensions %u/%u/%u is uncomputably large",
                 colorRes.c[RED], colorRes.c[GRN], colorRes.c[BLU]);

    {
        unsigned int plane;
        for (plane = 0, mapSize = 1; plane < 3; ++plane)
            mapSize *= colorRes.c[plane];
    }
    MALLOCVAR_NOFAIL(scalerP);

    scalerP->colorRes = colorRes;

    scalerP->out = allocScalerMap(mapSize);

    if (scalerP->out == NULL)
        pm_error("Unable to allocate memory for %u colors "
                 "(%u red x %u green x %u blue)",
                 mapSize, colorRes.c[RED], colorRes.c[GRN], colorRes.c[BLU]);

    {
        unsigned int r;
        for (r = 0; r < colorRes.c[RED]; ++r) {
            unsigned int g;
            for (g = 0; g < colorRes.c[GRN]; ++g) {
                unsigned int b;
                for (b = 0; b < colorRes.c[BLU]; ++b) {
                    unsigned int const index =
                        (r * colorRes.c[GRN] + g)
                        * colorRes.c[BLU] + b;
                    tuple const t = scalerP->out[index];
                         
                    t[PAM_RED_PLANE] =
                        r * outputMaxval / (colorRes.c[RED] - 1);
                    t[PAM_GRN_PLANE] = 
                        g * outputMaxval / (colorRes.c[GRN] - 1);
                    t[PAM_BLU_PLANE] =
                        b * outputMaxval / (colorRes.c[BLU] - 1);
                }
            }
        }
    }
    *scalerPP = scalerP;
}



static void
scaler_destroy(scaler * const scalerP) {

    free(scalerP->out);

    free(scalerP);
}



static tuple
scaler_scale(const scaler * const scalerP,
             unsigned int   const red,
             unsigned int   const grn,
             unsigned int   const blu) {

    unsigned int const index =
        ((red * scalerP->colorRes.c[GRN]) + grn)
        * scalerP->colorRes.c[BLU] + blu;

    assert(red < scalerP->colorRes.c[RED]);
    assert(grn < scalerP->colorRes.c[GRN]);
    assert(blu < scalerP->colorRes.c[BLU]);

    return scalerP->out[index];
}



static unsigned int
dither(sample       const p,
       sample       const maxval,
       unsigned int const d,
       unsigned int const ditheredMaxval,
       unsigned int const ditherMatrixArea) {
/*----------------------------------------------------------------------------
  Return the dithered brightness for a component of a pixel whose real 
  brightness for that component is 'p' based on a maxval of 'maxval'.
  The returned brightness is based on a maxval of ditheredMaxval.

  'd' is the entry in the dithering matrix for the position of this pixel
  within the dithered square.

  'ditherMatrixArea' is the area (number of pixels in) the dithered square.
-----------------------------------------------------------------------------*/
    unsigned int const ditherSquareMaxval = ditheredMaxval * ditherMatrixArea;
        /* This is the maxval for an intensity that an entire dithered
           square can represent.
        */
    unsigned int const pScaled = ditherSquareMaxval * p / maxval;
        /* This is the input intensity P expressed with a maxval of
           'ditherSquareMaxval'
        */
    
    /* Now we scale the intensity back down to the 'ditheredMaxval', and
       as that will involve rounding, we round up or down based on the position
       in the dithered square, as determined by 'd'
    */

    return (pScaled + d) / ditherMatrixArea;
}



static unsigned int
dithValue(unsigned int const yArg,
          unsigned int const xArg,
          unsigned int const dithPower) { 
/*----------------------------------------------------------------------------
  Return the value of a dither matrix which is 2 ** dithPower elements
  square at Row x, Column y.
  [graphics gems, p. 714]
-----------------------------------------------------------------------------*/
    unsigned int d;
        /*
          Think of d as the density. At every iteration, d is shifted
          left one and a new bit is put in the low bit based on x and y.
          If x is odd and y is even, or visa versa, then a bit is shifted in.
          This generates the checkerboard pattern seen in dithering.
          This quantity is shifted again and the low bit of y is added in.
          This whole thing interleaves a checkerboard pattern and y's bits
          which is what you want.
        */
    unsigned int x, y;
    unsigned int i;

    for (i = 0, d = 0, x = xArg, y = yArg;
         i < dithPower;
         ++i, x >>= 1, y >>= 1)
        d = (d << 2) | (((x & 1) ^ (y & 1)) << 1) | (y & 1);

    return d;
}



static unsigned int **
dithMatrix(unsigned int const dithPower) {
/*----------------------------------------------------------------------------
   Create the dithering matrix for dimension 'dithDim'.

   Return it in newly malloc'ed storage.

   Note that we assume 'dithPower' is small enough that the 'dithMatSize'
   computed within fits in an int.  Otherwise, results are undefined.
-----------------------------------------------------------------------------*/
    unsigned int const dithDim = 1 << dithPower;

    unsigned int ** dithMat;

    assert(dithPower < sizeof(unsigned int) * 8);

    {
        unsigned int const dithMatSize = 
            (dithDim * sizeof(*dithMat)) + /* pointers */
            (dithDim * dithDim * sizeof(**dithMat)); /* data */
        
        dithMat = malloc(dithMatSize);
        
        if (dithMat == NULL) 
            pm_error("Out of memory.  "
                     "Cannot allocate %u bytes for dithering matrix.",
                     dithMatSize);
    }
    {
        unsigned int * const rowStorage = (unsigned int *)&dithMat[dithDim];
        unsigned int y;
        for (y = 0; y < dithDim; ++y)
            dithMat[y] = &rowStorage[y * dithDim];
    }
    {
        unsigned int y;
        for (y = 0; y < dithDim; ++y) {
            unsigned int x;
            for (x = 0; x < dithDim; ++x)
                dithMat[y][x] = dithValue(y, x, dithPower);
        }
    }
    return dithMat;
}



static void
validateNoDitherOverflow(unsigned int           const ditherMatrixArea,
                         struct pam *           const inpamP,
                         struct colorResolution const colorRes) {
/*----------------------------------------------------------------------------
   Validate that we'll be able to do the dithering calculations based on
   the parameters above without busting out of an integer.
-----------------------------------------------------------------------------*/
    unsigned int maxDitherMaxval;
    unsigned int plane;

    for (plane = 0, maxDitherMaxval = 1; plane < 0; ++plane) {
        assert(colorRes.c[plane] >= 2);
        maxDitherMaxval = MAX(maxDitherMaxval, colorRes.c[plane]-1);
    }

    if (UINT_MAX / ditherMatrixArea / inpamP->maxval / maxDitherMaxval < 1)
        pm_error("Numbers are too large to compute.  You must reduce "
                 "the dither power, the input maxval, or the number of "
                 "component levels in the output");
}



static void
ditherRow(struct pam *           const inpamP,
          const tuple *          const inrow,
          const scaler *         const scalerP,
          unsigned int **        const ditherMatrix,
          unsigned int           const ditherMatrixArea,
          struct colorResolution const colorRes,
          unsigned int           const row,
          unsigned int           const modMask,
          struct pam *           const outpamP,
          tuple *                const outrow) {

    unsigned int col;

    for (col = 0; col < inpamP->width; ++col) {
        unsigned int const d =
            ditherMatrix[row & modMask][(inpamP->width-col-1) & modMask];

        unsigned int dithered[3];
        unsigned int plane;

        assert(inpamP->depth >= 3);

        for (plane = 0; plane < 3; ++plane)
            dithered[plane] =
                dither(inrow[col][plane], inpamP->maxval, d,
                       colorRes.c[plane]-1, ditherMatrixArea);

        pnm_assigntuple(outpamP,
                        outrow[col],
                        scaler_scale(scalerP,
                                     dithered[PAM_RED_PLANE],
                                     dithered[PAM_GRN_PLANE],
                                     dithered[PAM_BLU_PLANE]));
    }
}



static void
ditherImage(struct pam *           const inpamP,
            const scaler *         const scalerP,
            unsigned int           const dithPower,
            struct colorResolution const colorRes,
            struct pam *           const outpamP,
            tuple ***              const outTuplesP) {

    unsigned int const dithDim = 1 << dithPower;
    unsigned int const ditherMatrixArea = SQR(dithDim);

    unsigned int const modMask = (dithDim - 1);
       /* And this into N to compute N % dithDim cheaply, since we
          know (though the compiler doesn't) that dithDim is a power of 2
       */
    unsigned int ** const ditherMatrix = dithMatrix(dithPower);

    tuple * inrow;
    tuple ** outTuples;
    unsigned int row; 
    struct pam ditherPam;
        /* Describes the tuples that ditherRow() sees */

    assert(dithPower < sizeof(unsigned int) * 8);
    assert(UINT_MAX / dithDim >= dithDim);
    
    validateNoDitherOverflow(ditherMatrixArea, inpamP, colorRes);

    inrow = pnm_allocpamrow(inpamP);

    outTuples = pnm_allocpamarray(outpamP);

    /* We will modify the input to promote it to depth 3 */
    ditherPam = *inpamP;
    ditherPam.depth = 3;

    for (row = 0; row < inpamP->height; ++row) {
        pnm_readpamrow(inpamP, inrow);

        pnm_makerowrgb(inpamP, inrow);

        ditherRow(&ditherPam, inrow, scalerP, ditherMatrix, ditherMatrixArea,
                  colorRes, row, modMask,
                  outpamP, outTuples[row]);
    }
    free(ditherMatrix);
    pnm_freepamrow(inrow);
    *outTuplesP = outTuples;
}



int
main(int           argc,
     const char ** argv) {

    struct cmdlineInfo cmdline;
    FILE * ifP;
    tuple ** outTuples;        /* Output image */
    scaler * scalerP;
    struct pam inpam;
    struct pam outpam;

    pm_proginit(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    ifP = pm_openr(cmdline.inputFileName);

    pnm_readpaminit(ifP, &inpam, PAM_STRUCT_SIZE(allocation_depth));

    pnm_setminallocationdepth(&inpam, 3);
    
    outpam.size               = sizeof(outpam);
    outpam.len                = PAM_STRUCT_SIZE(tuple_type);
    outpam.file               = stdout;
    outpam.width              = inpam.width;
    outpam.height             = inpam.height;
    outpam.depth              = 3;
    outpam.maxval             =
        pm_lcm(cmdline.colorRes.c[RED]-1,
               cmdline.colorRes.c[GRN]-1,
               cmdline.colorRes.c[BLU]-1,
               PPM_MAXMAXVAL);
    outpam.bytes_per_sample   = inpam.bytes_per_sample;
    STRSCPY(outpam.tuple_type, "RGB");
    outpam.format             = RPPM_FORMAT;
    outpam.plainformat        = false;

    scaler_create(outpam.maxval, cmdline.colorRes, &scalerP);

    ditherImage(&inpam, scalerP, cmdline.dim, cmdline.colorRes,
                &outpam, &outTuples);

    pnm_writepam(&outpam, outTuples);

    scaler_destroy(scalerP);

    pnm_freepamarray(outTuples, &outpam);

    pm_close(ifP);

    return 0;
}
