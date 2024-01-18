/* pamflip.c - perform one or more flip operations on a Netpbm image
**
** Copyright (C) 1989 by Jef Poskanzer.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
*/

/*
   transformNonPbmChunk() is the general transformation function.
   It can transform anything, albeit slowly and expensively.
   
   The following are enhancements for specific cases:
   
     transformRowByRowPbm():
       PBM image with left-right or null transformation
     transformRowsBottomTopPbm()
       PBM image with bottom-top transformation
     transformRowByRowNonPbm()
       non-PBM image with left-right or null transformation
       (also works for PBM, but we don't use it)
     transformRowsBottomTopNonPbm()
       non-PBM image with bottom-top transformation
       (also works for PBM, but we don't use it)
     transformRowsToColumnsPbmSse()
       PBM image with column-for-row transformation
       requires Intel/AMD x86 SSE2
       (can only do 90 degree/xy flips)
     transformPbm()
       PBM image with column-for-row transformation
       (also works for all other transformations, but we don't use it)
     transformNonPbmWhole()
       non-PBM column-for-row transformation
       (also works for PBM, but we don't use it)

   Except we don't use any of the above if we can't fit the entire image
   into the amount of memory the user gave us to work with.  In that
   case, we fall back to transformNonPbmChunk().

   Note that while virtual memory can be limited (e.g. sometimes the
   machine's 32 bit address space itself is a limit), real memory is
   also a concern.  With a row-for-column transformation
   (e.g. -transpose), if we can't fit the entire image into _real_
   memory, we will page thrash within an inch our lives.  So we count
   on the user to tell us how much real memory we should expect to
   get -- his -memsize option is the lesser of the available virtual
   and real memory.

   Before Netpbm 10.42 (March 2008), we had a different method for
   dealing with memory shortage.  We didn't worry about virtual memory
   at all, and always kept the whole target image in memory.  We did
   not use temporary files.  But to avoid page thrashing in a
   column-for-row transformation, we transformed in column stripes of
   the source image, reading the input image through multiple times.
*/

#define _BSD_SOURCE 1      /* Make sure strdup() is in string.h */
#define _XOPEN_SOURCE 500  /* Make sure strdup() is in string.h */

#include <assert.h>
#include <limits.h>
#include <string.h>

#include "pm_c_util.h"
#include "pam.h"
#include "shhopt.h"
#include "mallocvar.h"
#include "nstring.h"
#include "bitreverse.h"

#include "config.h"  /* Defines SSE_PBM_XY_FLIP */
#include "flip.h"
#include "pamflip_sse.h"

enum xformType {LEFTRIGHT, TOPBOTTOM, TRANSPOSE};

static void
parseXformOpt(const char *     const xformOpt,
              unsigned int  *  const xformCountP,
              enum xformType * const xformList) {
/*----------------------------------------------------------------------------
   Translate the -xform option string into an array of transform types.

   Return the array as xformList[], which is preallocated for at least
   10 elements.
-----------------------------------------------------------------------------*/
    unsigned int xformCount;
    char * xformOptWork;
    char * cursor;
    bool eol;
    
    xformOptWork = strdup(xformOpt);
    cursor = &xformOptWork[0];
    
    eol = FALSE;    /* initial value */
    xformCount = 0; /* initial value */
    while (!eol && xformCount < 10) {
        const char * token;
        token = pm_strsep(&cursor, ",");
        if (token) {
            if (streq(token, "leftright"))
                xformList[xformCount++] = LEFTRIGHT;
            else if (streq(token, "topbottom"))
                xformList[xformCount++] = TOPBOTTOM;
            else if (streq(token, "transpose"))
                xformList[xformCount++] = TRANSPOSE;
            else if (streq(token, ""))
            { /* ignore it */}
            else
                pm_error("Invalid transform type in -xform option: '%s'",
                         token );
        } else
            eol = TRUE;
    }
    free(xformOptWork);

    *xformCountP = xformCount;
}



/* See transformPoint() for an explanation of the transform matrix types.  The
   difference between xformCore and xformMatrix is that 'xformCore' is
   particular to the source image dimensions and can be used to do the
   transformation, while 'xformCore' is independent of the source image and
   just tells what kind of transformation.
*/

struct xformMatrix {
    /* a b 0
       c d 0
       e f 1
    */
    int a;  /* -1, 0, or 1 */
    int b;  /* -1, 0, or 1 */
    int c;  /* -1, 0, or 1 */
    int d;  /* -1, 0, or 1 */
    int e;  /* 0 or maximum column number in target image */
    int f;  /* 0 or maximum row number in target image */
};



static void
leftright(struct xformCore * const xformP) {
    xformP->a = - xformP->a;
    xformP->c = - xformP->c;
}



static void
topbottom(struct xformCore * const xformP) {
    xformP->b = - xformP->b;
    xformP->d = - xformP->d;
}



static void
swap(int * const xP, int * const yP) {

    int const t = *xP;

    *xP = *yP;
    *yP = t;
}



static void
transpose(struct xformCore * const xformP) {
    swap(&xformP->a, &xformP->b);
    swap(&xformP->c, &xformP->d);
}



static void
computeXformCore(unsigned int       const xformCount,
                 enum xformType     const xformType[],
                 struct xformCore * const xformP) {
    
    struct xformCore const nullTransform = {1, 0, 0, 1};

    unsigned int i;

    *xformP = nullTransform;   /* initial value */

    for (i = 0; i < xformCount; ++i) {
        switch (xformType[i]) {
        case LEFTRIGHT: 
            leftright(xformP);
            break;
        case TOPBOTTOM:
            topbottom(xformP);
            break;
        case TRANSPOSE:
            transpose(xformP);
            break;
        }
    }
}



static void
xformDimensions(struct xformCore const xform,
                unsigned int     const inCols,
                unsigned int     const inRows,
                unsigned int *   const outColsP,
                unsigned int *   const outRowsP) {
/*----------------------------------------------------------------------------
   Compute the output dimensions from the input dimensions given a
   matrix that describes a transformation.

   E.g. if it's a 90 degree rotation of a 10 x 20 image, the output is
   a 20 x 10 image.
-----------------------------------------------------------------------------*/
    *outColsP = abs(xform.a * inCols + xform.c * inRows);
    *outRowsP = abs(xform.b * inCols + xform.d * inRows);
}



static void
computeXformMatrix(struct xformMatrix * const xformP, 
                   unsigned int         const sourceCols,
                   unsigned int         const sourceRows,
                   struct xformCore     const xformCore) {

    int colMax = xformCore.a * (sourceCols-1) + xformCore.c * (sourceRows-1);
    int rowMax = xformCore.b * (sourceCols-1) + xformCore.d * (sourceRows-1);

    xformP->a = xformCore.a;
    xformP->b = xformCore.b;
    xformP->c = xformCore.c;
    xformP->d = xformCore.d;
    xformP->e = colMax < 0 ? -colMax : 0;
    xformP->f = rowMax < 0 ? -rowMax : 0;
}



struct cmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    const char * inputFilespec;  /* Filespec of input file */
    struct xformCore xform;
        /* Handy mathematical representation of all of transform options */
    size_t availableMemory;
    unsigned int pageSize;
    unsigned int verbose;
};



static void
interpretMemorySize(unsigned int const memsizeSpec,
                    unsigned int const memsizeOpt,
                    size_t *     const availableMemoryP) {

    size_t const sizeMax = (size_t)(-1);
    unsigned int const Meg = 1024 * 1024;

    if (memsizeSpec) {
        if (memsizeOpt > sizeMax / Meg)
            pm_error("-memsize value too large: %u MiB.  Maximum this program "
                     "can handle is %u MiB", 
                     memsizeOpt, (unsigned)sizeMax / Meg);
        *availableMemoryP = memsizeOpt * Meg;
    } else
        *availableMemoryP = sizeMax;
}



static void
parseCommandLine(int argc, char ** const argv,
                 struct cmdlineInfo * const cmdlineP) {
/*----------------------------------------------------------------------------
   Note that the file spec array we return is stored in the storage that
   was passed to us as the argv array.
-----------------------------------------------------------------------------*/
    optEntry * option_def;
        /* Instructions to OptParseOptions3 on how to parse our options.
         */
    optStruct3 opt;

    unsigned int option_def_index;

    unsigned int lr, tb, xy, r90, r270, r180, null;
    unsigned int memsizeSpec, pagesizeSpec, xformSpec;
    unsigned int memsizeOpt;
    const char * xformOpt;
    unsigned int xformCount;
        /* Number of transforms in the 'xformType' array */
    enum xformType xformList[10];
        /* Array of transforms to be applied, in order */

    MALLOCARRAY(option_def, 100);

    option_def_index = 0;   /* incremented by OPTENTRY */
    OPTENT3(0, "lr",        OPT_FLAG,    NULL, &lr,      0);
    OPTENT3(0, "leftright", OPT_FLAG,    NULL, &lr,      0);
    OPTENT3(0, "tb",        OPT_FLAG,    NULL, &tb,      0);
    OPTENT3(0, "topbottom", OPT_FLAG,    NULL, &tb,      0);
    OPTENT3(0, "xy",        OPT_FLAG,    NULL, &xy,      0);
    OPTENT3(0, "transpose", OPT_FLAG,    NULL, &xy,      0);
    OPTENT3(0, "r90",       OPT_FLAG,    NULL, &r90,     0);
    OPTENT3(0, "rotate90",  OPT_FLAG,    NULL, &r90,     0);
    OPTENT3(0, "ccw",       OPT_FLAG,    NULL, &r90,     0);
    OPTENT3(0, "r180",      OPT_FLAG,    NULL, &r180,    0);
    OPTENT3(0, "rotate180", OPT_FLAG,    NULL, &r180,    0);
    OPTENT3(0, "r270",      OPT_FLAG,    NULL, &r270,    0);
    OPTENT3(0, "rotate270", OPT_FLAG,    NULL, &r270,    0);
    OPTENT3(0, "cw",        OPT_FLAG,    NULL, &r270,    0);
    OPTENT3(0, "null",      OPT_FLAG,    NULL, &null,    0);
    OPTENT3(0, "verbose",   OPT_FLAG,    NULL, &cmdlineP->verbose,       0);
    OPTENT3(0, "memsize",   OPT_UINT,    &memsizeOpt, 
            &memsizeSpec,       0);
    OPTENT3(0, "pagesize",  OPT_UINT,    &cmdlineP->pageSize,
            &pagesizeSpec,      0);
    OPTENT3(0, "xform",     OPT_STRING,  &xformOpt, 
            &xformSpec, 0);

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = FALSE;  /* We don't parms that are negative numbers */

    pm_optParseOptions3(&argc, argv, opt, sizeof(opt), 0);
        /* Uses and sets argc, argv, and some of *cmdlineP and others. */

    if (lr + tb + xy + r90 + r180 + r270 + null > 1)
        pm_error("You may specify only one type of flip.");
    if (lr + tb + xy + r90 + r180 + r270 + null == 1) {
        if (lr) {
            xformCount = 1;
            xformList[0] = LEFTRIGHT;
        } else if (tb) {
            xformCount = 1;
            xformList[0] = TOPBOTTOM;
        } else if (xy) {
            xformCount = 1;
            xformList[0] = TRANSPOSE;
        } else if (r90) {
            xformCount = 2;
            xformList[0] = TRANSPOSE;
            xformList[1] = TOPBOTTOM;
        } else if (r180) {
            xformCount = 2;
            xformList[0] = LEFTRIGHT;
            xformList[1] = TOPBOTTOM;
        } else if (r270) {
            xformCount = 2;
            xformList[0] = TRANSPOSE;
            xformList[1] = LEFTRIGHT;
        } else if (null) {
            xformCount = 0;
        }
    } else if (xformSpec) 
        parseXformOpt(xformOpt, &xformCount, xformList);
    else
        pm_error("You must specify an option such as -topbottom to indicate "
                 "what kind of flip you want.");

    computeXformCore(xformCount, xformList, &cmdlineP->xform);
    
    interpretMemorySize(memsizeSpec, memsizeOpt, &cmdlineP->availableMemory);

    if (!pagesizeSpec)
        cmdlineP->pageSize = 4*1024;         

    if (argc-1 == 0) 
        cmdlineP->inputFilespec = "-";
    else if (argc-1 != 1)
        pm_error("Program takes zero or one argument (filename).  You "
                 "specified %d", argc-1);
    else
        cmdlineP->inputFilespec = argv[1];

    free(option_def);
}



static void
bitOrderReverse(unsigned char * const bitrow, 
                unsigned int    const cols) {
/*----------------------------------------------------------------------------
  Reverse the bits in a packed pbm row (1 bit per pixel).  I.e. the leftmost
  bit becomes the rightmost, etc.

  Exchange pixels in units of eight.  If both are zero, skip instead of
  exchanging zeros.
-----------------------------------------------------------------------------*/
    unsigned int const lastfullByteIdx = cols/8 - 1;

    if (cols == 0 || bitrow == NULL )
        pm_error("Invalid arguments passed to bitOrderReverse");

    if (cols <= 8)
        bitrow[0] = bitreverse[bitrow[0]] << (8-cols);
    else if (cols % 8 == 0) {
        unsigned int i, j;
        for (i = 0, j = lastfullByteIdx; i <= j; ++i, --j)
            if ((bitrow[j] | bitrow[i]) == 0) {
                /* Both are 0x00 - skip */
            } else {
                unsigned char const t = bitreverse[bitrow[j]]; 
                bitrow[j] = bitreverse[bitrow[i]];
                bitrow[i] = t;
            }
    } else {
        unsigned int const m = cols % 8; 

        unsigned int i, j;
            /* Cursors into bitrow[].  i moves from left to center;
               j moves from right to center as bits of bitrow[] are exchanged.
            */
        unsigned char th, tl;  /* 16 bit temp ( th << 8 | tl ) */
        tl = 0;
        for (i = 0, j = lastfullByteIdx+1; i <= lastfullByteIdx/2; ++i, --j) {
            if( (tl | bitrow[i] | bitrow[j] | bitrow[j-1]) != 0) {
                /* Skip if both are 0x00 */
                th = bitreverse[bitrow[i]];
                bitrow[i] =
                    bitreverse[0xff & ((bitrow[j-1] << 8 
                                        | bitrow[j]) >> (8-m))];
                bitrow[j] = 0xff & ((th << 8 | tl) >> m);
                tl = th;
            }
        }
        if (i == j && (bitrow[i] | tl) != 0) {
            /* bitrow[] has an odd number of bytes (an even number of
               full bytes; lastfullByteIdx is odd), so we did all but
               the center byte above.  We do the center byte now.
            */
            bitrow[j] = 0xff & ((bitreverse[bitrow[i]] << 8 | tl) >> m);
        }
    }
}



static void
transformRowByRowPbm(struct pam * const inpamP, 
                     struct pam * const outpamP,
                     bool         const reverse) {
/*----------------------------------------------------------------------------
  Transform a PBM raster either by flipping it left for right, or just
  leaving it alone, as indicated by 'reverse'.  Read the raster from
  *inpamP; write the transformed raster to *outpamP.

  Process the image one row at a time and use fast packed PBM bit
  reverse algorithm (where required).
-----------------------------------------------------------------------------*/
    unsigned char * bitrow;
    unsigned int row;

    bitrow = pbm_allocrow_packed(outpamP->width); 

    for (row = 0; row < inpamP->height; ++row) {
        pbm_readpbmrow_packed(inpamP->file,  bitrow, inpamP->width,
                              inpamP->format);

        if (reverse)
            bitOrderReverse(bitrow, inpamP->width);

        pbm_writepbmrow_packed(outpamP->file, bitrow, outpamP->width, 0);
    }
    pbm_freerow_packed(bitrow);
}



static void
transformRowByRowNonPbm(struct pam * const inpamP, 
                        struct pam * const outpamP,
                        bool         const reverse) {
/*----------------------------------------------------------------------------
  Flip a raster left for right or leave it alone.  Read the raster
  from *inpamP; write the transformed raster to *outpamP.

  Process one row at a time.

  This works on any image, but is slower and uses more memory than the
  PBM-only transformRowByRowPbm().
-----------------------------------------------------------------------------*/
    tuple * tuplerow;
    tuple * newtuplerow;
        /* This is not a full tuple row.  It is either an array of pointers
           to the tuples in 'tuplerow' (in reverse order) or just 'tuplerow'
           itself.
        */
    tuple * scratchTuplerow;
    
    unsigned int row;
    
    tuplerow = pnm_allocpamrow(inpamP);
    
    if (reverse) {
        /* Set up newtuplerow[] to point to the tuples of tuplerow[] in
           reverse order.
        */
        unsigned int col;
        
        MALLOCARRAY_NOFAIL(scratchTuplerow, inpamP->width);

        for (col = 0; col < inpamP->width; ++col) 
            scratchTuplerow[col] = tuplerow[inpamP->width - col - 1];
        newtuplerow = scratchTuplerow;
    } else {
        scratchTuplerow = NULL;
        newtuplerow = tuplerow;
    }
    for (row = 0; row < inpamP->height ; ++row) {
        pnm_readpamrow(inpamP, tuplerow);
        pnm_writepamrow(outpamP, newtuplerow);
    }
    
    if (scratchTuplerow)
        free(scratchTuplerow);
    pnm_freepamrow(tuplerow);
}



static void
transformRowsBottomTopPbm(struct pam * const inpamP,
                          struct pam * const outpamP,
                          bool         const reverse) { 
/*----------------------------------------------------------------------------
  Flip a PBM raster top for bottom; read the raster from *inpamP;
  write the flipped raster to *outpamP.

  Read complete image into memory in packed PBM format; Use fast
  packed PBM bit reverse algorithm (where required).
-----------------------------------------------------------------------------*/
    unsigned int const rows=inpamP->height;

    unsigned char ** bitrow;
    unsigned int row;
        
    bitrow = pbm_allocarray_packed(outpamP->width, outpamP->height);
        
    for (row = 0; row < rows; ++row)
        pbm_readpbmrow_packed(inpamP->file, bitrow[row], 
                              inpamP->width, inpamP->format);

    for (row = 0; row < rows; ++row) {
        if (reverse) 
            bitOrderReverse(bitrow[rows-row-1], inpamP->width);

        pbm_writepbmrow_packed(outpamP->file, bitrow[rows - row - 1],
                               outpamP->width, 0);
    }
    pbm_freearray_packed(bitrow, outpamP->height);
}



static void
transformRowsBottomTopNonPbm(struct pam * const inpamP, 
                             struct pam * const outpamP) {
/*----------------------------------------------------------------------------
  Do a simple vertical flip.  Read the raster from *inpamP; write the
  flipped raster to *outpamP.

  We do this faster than the more general subroutines because we just
  move the row pointers.

  But we must fit the entire image into memory at once.

  This works on PBM, but the PBM-specific subroutine is faster.
-----------------------------------------------------------------------------*/
    tuple ** tuplerows;
    unsigned int row;

    tuplerows = pnm_allocpamarray(outpamP);

    for (row = 0; row < inpamP->height ; ++row)
        pnm_readpamrow(inpamP, tuplerows[row]);

    for (row = 0; row < inpamP->height; ++row) {
        tuple * const tuplerow = tuplerows[inpamP->height - row - 1];

        pnm_writepamrow(outpamP, tuplerow);
    }
    
    pnm_freepamarray(tuplerows, outpamP);
}



static void __inline__
transformPoint(int                const col, 
               int                const row, 
               struct xformMatrix const xform, 
               unsigned int *     const newcolP, 
               unsigned int *     const newrowP ) {
/*----------------------------------------------------------------------------
   Compute the location in the output of a pixel that is at row 'row',
   column 'col' in the input.  Assume the output image is 'newcols' by
   'newrows' and the transformation is as described by 'xform'.

   Return the output image location of the pixel as *newcolP and *newrowP.
-----------------------------------------------------------------------------*/
    /* The transformation is:
     
                 [ a b 0 ]
       [ x y 1 ] [ c d 0 ] = [ x2 y2 1 ]
                 [ e f 1 ]

       Where (x, y) is the source pixel location and (x2, y2) is the
       target pixel location.

       Note that this is more of a logical computation than an arithmetic
       one: a, b, c, and d are -1, 0, or 1.  e is the maximum column number
       in the target image or 0; f is the maximum row number or 0.
    */
    *newcolP = xform.a * col + xform.c * row + xform.e * 1;
    *newrowP = xform.b * col + xform.d * row + xform.f * 1;

    assert(*newcolP >= 0);
    assert(*newrowP >= 0);
}



static void
writeRaster(struct pam *    const pamP,
            tuple * const * const tuples) {

    unsigned int outRow;

    for (outRow = 0; outRow < pamP->height; ++ outRow)
        pnm_writepamrow(pamP, tuples[outRow]);
}







static void
transformPbmGen(struct pam *     const inpamP,
                struct pam *     const outpamP,
                struct xformCore const xformCore) { 
/*----------------------------------------------------------------------------
   This is the same as transformGen, except that it uses less 
   memory, since the PBM buffer format uses one bit per pixel instead
   of twelve bytes + pointer space

   This can do any PBM transformation, but is slower and uses more
   memory than the more restricted transformRowByRowPbm() and
   transformRowsBottomTopPbm().
-----------------------------------------------------------------------------*/
    bit * bitrow;
    bit ** newbits;
    struct xformMatrix xform;
    unsigned int row;
            
    computeXformMatrix(&xform, inpamP->width, inpamP->height, xformCore);
    
    bitrow = pbm_allocrow_packed(inpamP->width);
    newbits = pbm_allocarray_packed( outpamP->width, outpamP->height );
            
    /* Initialize entire array to zeroes.  One bits will be or'ed in later */
    for (row = 0; row < outpamP->height; ++row) {
        unsigned int col;
        for (col = 0; col < pbm_packed_bytes(outpamP->width); ++col) 
            newbits[row][col] = 0; 
    }
    
    for (row = 0; row < inpamP->height; ++row) {
        unsigned int col;

        pbm_readpbmrow_packed(inpamP->file, bitrow,
                              inpamP->width, inpamP->format);
        for (col = 0; col < inpamP->width; ) {
            if (bitrow[col/8] == 0x00) 
                col += 8;  /* Blank.   Skip to next byte. */
            else {      /* Examine each pixel. */
                unsigned int const colLimit = MIN(col+8, inpamP->width);
                unsigned int i;

                for (i = 0; col < colLimit; ++i, ++col) {
                    bool const bitIsOne = (bitrow[col/8] >> (7-i)) & 0x01;
                    if (bitIsOne) {
                        /* Write in only the one bits. */  
                        unsigned int newcol, newrow;
                        transformPoint(col, row, xform, &newcol, &newrow);
                        newbits[newrow][newcol/8] |= 0x01 << (7 - newcol % 8);
                            /* Use of "|=" patterned after
                               pbm_readpbmrow_packed().
                            */
                    }
                }
            }
        }
    }

    for (row = 0; row < outpamP->height; ++row)
        pbm_writepbmrow_packed(outpamP->file, newbits[row], outpamP->width, 0);
    
    pbm_freearray(newbits, outpamP->height);
    pbm_freerow(bitrow);
}



static void
transformNonPbmWhole(struct pam *     const inpamP,
                     struct pam *     const outpamP,
                     struct xformCore const xformCore,
                     bool             const verbose) {
/*----------------------------------------------------------------------------
  Do the transform using "pam" library functions, as opposed to "pbm"
  ones.

  Read the raster from *inpamP; write the transformed raster to *outpamP.

  Assume input file is positioned to the raster (just after the
  header).

  This can do any transformation, but is slower and uses more memory
  than some of the alternatives which are usable only for certain
  cases.  But we do require a certain amount of virtual and real memory;
  transformNonPbmChunk() is even more general in that it doesn't.
-----------------------------------------------------------------------------*/
    tuple * tuplerow;
    tuple ** newtuples;
    struct xformMatrix xform;
    unsigned int row;

    computeXformMatrix(&xform, inpamP->width, inpamP->height, xformCore);
    
    tuplerow = pnm_allocpamrow(inpamP);
    newtuples = pnm_allocpamarray(outpamP);
    
    for (row = 0; row < inpamP->height; ++row) {
        unsigned int col;
        pnm_readpamrow(inpamP, tuplerow);
        
        for (col = 0; col < inpamP->width; ++col) {
            unsigned int newcol, newrow;

            transformPoint(col, row, xform, &newcol, &newrow);

            assert(newcol < outpamP->width);
            assert(newrow < outpamP->height);

            pnm_assigntuple(inpamP, newtuples[newrow][newcol],
                            tuplerow[col]);
        }
    }
    
    writeRaster(outpamP, newtuples);
    
    pnm_freepamarray(newtuples, outpamP);
    pnm_freepamrow(tuplerow);
}



typedef struct {
/*----------------------------------------------------------------------------
   A description of the quilt of cells that make up the output image.
-----------------------------------------------------------------------------*/
    unsigned int rankCt, fileCt;
        /* Dimensions of the output image in cells */
    struct pam ** pam;
        /* pam[y][x] is the pam structure for the cell at rank y, file x
           in the output.
        */

    /* Each of the cells corresponds to a temporary file; the 'file'
       member of its pam structure identifies it.  But it is not a normal
       Netpbm file; it contains only the raster portion.  The program
       writes the raster to the file, starting at offset zero, then rewinds
       and reads it out later.  The header is unnecessary because the pam
       structure is still available at readback time.
    */
} outputMap;



static void
initOutCell(struct pam *     const outCellPamP,
            unsigned int     const inCellWidth,
            unsigned int     const inCellHeight,
            struct pam *     const inpamP,
            struct xformCore const xformCore) {
/*----------------------------------------------------------------------------
   Set up an output cell.  Create and open a temporary file to hold its
   raster.  Figure out the dimensions of the cell.  Return a PAM structure
   that describes the cell (including identifying that temporary file).
-----------------------------------------------------------------------------*/
    unsigned int outCellFileCt, outCellRankCt;

    *outCellPamP = *inpamP;  /* initial value */

    outCellPamP->len  = PAM_STRUCT_SIZE(tuple_type);

    outCellPamP->file = pm_tmpfile();

    xformDimensions(xformCore, inCellWidth, inCellHeight,
                    &outCellFileCt, &outCellRankCt);

    outCellPamP->width = outCellFileCt;
    outCellPamP->height = outCellRankCt;
}



static outputMap *
createOutputMap(struct pam *       const inpamP,
                unsigned int       const maxRows,
                struct xformMatrix const cellXform,
                struct xformCore   const xformCore) {
/*----------------------------------------------------------------------------
   Create and return the output map.  That's a map of all the output cells
   (from which the output image can be assembled, once those cells are filled
   in).

   The map contains the dimensions of each output cell as well as file
   stream handles for the temporary files containing the pixels of each
   cell.  We create and open those files.

   Note that a complexity of determining cell dimensions (which we handle)
   is that the input image isn't necessarily a whole multiple of the input
   cell size, so the last cell may be short.

   The map does not contain the mapping from input cells to output cells
   (e.g. in a top-bottom transformation of a 10-cell image, input cell
   0 maps to output cell 9); caller can compute that when needed from
   'cellXform'.
-----------------------------------------------------------------------------*/
    unsigned int const inCellFileCt = 1;
    unsigned int const inCellRankCt = (inpamP->height + maxRows - 1) / maxRows;

    outputMap * mapP;
    unsigned int outCellRank;
    unsigned int inCellRank;

    MALLOCVAR_NOFAIL(mapP);

    xformDimensions(xformCore, inCellFileCt, inCellRankCt,
                    &mapP->fileCt, &mapP->rankCt);

    MALLOCARRAY(mapP->pam, mapP->rankCt);
    if (mapP->pam == NULL)
        pm_error("Could not allocate a cell array for %u ranks of cells.",
                 mapP->rankCt);

    for (outCellRank = 0; outCellRank < mapP->rankCt; ++outCellRank) {

        MALLOCARRAY(mapP->pam[outCellRank], mapP->fileCt);

        if (mapP->pam[outCellRank] == NULL)
            pm_error("Failed to allocate rank %u of the cell array, "
                     "%u cells wide", outCellRank, mapP->fileCt);
    }

    for (inCellRank = 0; inCellRank < inCellRankCt; ++inCellRank) {
        unsigned int const inCellFile = 0;
        unsigned int const inCellStartRow = inCellRank * maxRows;
        unsigned int const inCellRowCt =
            MIN(inpamP->height - inCellStartRow, maxRows);

        unsigned int outCellFile, outCellRank;
        transformPoint(inCellFile, inCellRank, cellXform,
                       &outCellFile, &outCellRank);
    
        initOutCell(&mapP->pam[outCellRank][outCellFile],
                    inpamP->width, inCellRowCt,
                    inpamP, xformCore);
    }
    return mapP;
}
                


static void
destroyOutputMap(outputMap * const mapP) {

    unsigned int outCellRank;

    for (outCellRank = 0; outCellRank < mapP->rankCt; ++outCellRank)
        free(mapP->pam[outCellRank]);

    free(mapP->pam);

    free(mapP);
}



static void
rewindCellFiles(outputMap * const outputMapP) {

    unsigned int outCellRank;

    for (outCellRank = 0; outCellRank < outputMapP->rankCt; ++outCellRank) {
        unsigned int outCellFile;
        for (outCellFile = 0; outCellFile < outputMapP->fileCt; ++outCellFile)
            pm_seek(outputMapP->pam[outCellRank][outCellFile].file, 0);
    }
}



static void
closeCellFiles(outputMap * const outputMapP) {

    unsigned int outCellRank;

    for (outCellRank = 0; outCellRank < outputMapP->rankCt; ++outCellRank) {
        unsigned int outCellFile;
        for (outCellFile = 0; outCellFile < outputMapP->fileCt; ++outCellFile)
            pm_close(outputMapP->pam[outCellRank][outCellFile].file);
    }
}



static void
transformCell(struct pam *     const inpamP,
              struct pam *     const outpamP,
              struct xformCore const xformCore) {

    struct xformMatrix xform;
    tuple * inTupleRow;
    tuple ** outTuples;
    unsigned int inRow;

    computeXformMatrix(&xform, inpamP->width, inpamP->height, xformCore);

    inTupleRow = pnm_allocpamrow(inpamP);

    outTuples = pnm_allocpamarray(outpamP);

    for (inRow = 0; inRow < inpamP->height; ++inRow) {
        unsigned int inCol;

        pnm_readpamrow(inpamP, inTupleRow);
        
        for (inCol = 0; inCol < inpamP->width; ++inCol) {
            unsigned int outCol, outRow;

            transformPoint(inCol, inRow, xform, &outCol, &outRow);

            assert(outCol < outpamP->width);
            assert(outRow < outpamP->height);

            pnm_assigntuple(inpamP,
                            outTuples[outRow][outCol], inTupleRow[inCol]);
        }
    }
    pnm_freepamrow(inTupleRow);

    writeRaster(outpamP, outTuples);

    pnm_freepamarray(outTuples, outpamP);
}



static void
stitchCellsToOutput(outputMap *  const outputMapP,
                    struct pam * const outpamP) {

    unsigned int outRank;
    tuple * tupleRow;

    tupleRow = pnm_allocpamrow(outpamP);

    for (outRank = 0; outRank < outputMapP->rankCt; ++outRank) {
        unsigned int const cellRows = outputMapP->pam[outRank][0].height;
            /* Number of rows in every cell in this rank */

        unsigned int cellRow;

        for (cellRow = 0; cellRow < cellRows; ++cellRow) {
            unsigned int outFile;
            unsigned int outCol;

            outCol = 0;

            for (outFile = 0; outFile < outputMapP->fileCt; ++outFile) {
                struct pam * const outCellPamP = 
                    &outputMapP->pam[outRank][outFile];

                assert(outCellPamP->height == cellRows);

                assert(outCol < outpamP->width);
                pnm_readpamrow(outCellPamP, &tupleRow[outCol]);

                outCol += outCellPamP->width;
            }

            assert(outCol = outpamP->width);

            pnm_writepamrow(outpamP, tupleRow);
        }
    }
    pnm_freepamrow(tupleRow);
}



static void
transformNonPbmChunk(struct pam *     const inpamP,
                     struct pam *     const outpamP,
                     struct xformCore const xformCore,
                     unsigned int     const maxRows,
                     bool             const verbose) {
/*----------------------------------------------------------------------------
  Same as transformNonPbmWhole(), except we read 'maxRows' rows of the
  input into memory at a time, storing intermediate results in temporary
  files, to limit our use of virtual and real memory.

  Assume input file is positioned to the raster (just after the
  header).

  We call the strip of 'maxRows' rows that we read a source cell.  We
  transform that cell according to 'xformCore' to create a
  target cell.  We store all the target cells in temporary files.
  We consider the target cells to be arranged in a column matrix the
  same as the source cells within the source image; we transform that
  matrix according to 'xformCore'.  The resulting cell matrix is the
  target image.
-----------------------------------------------------------------------------*/
    /* The cells of the source image ("inCell") are in a 1-column matrix.
       "rank" is the vertical position of a cell in that matrix; "file" is
       the horizontal position (always 0, of course).
    */
    unsigned int const inCellFileCt = 1;
    unsigned int const inCellRankCt = (inpamP->height + maxRows - 1) / maxRows;

    struct xformMatrix cellXform;
    unsigned int inCellRank;
    outputMap * outputMapP;

    if (verbose)
        pm_message("Transforming in %u chunks, using temp files",
                   inCellRankCt);

    computeXformMatrix(&cellXform, inCellFileCt, inCellRankCt, xformCore);

    outputMapP = createOutputMap(inpamP, maxRows, cellXform, xformCore);

    for (inCellRank = 0; inCellRank < inCellRankCt; ++inCellRank) {
        unsigned int const inCellFile = 0;
        unsigned int const inCellStartRow = inCellRank * maxRows;
        unsigned int const inCellRows =
            MIN(inpamP->height - inCellStartRow, maxRows);

        struct pam inCellPam;
        struct pam * outCellPamP;
        unsigned int outCellFile, outCellRank;

        transformPoint(inCellFile, inCellRank, cellXform,
                       &outCellFile, &outCellRank);
    
        outCellPamP = &outputMapP->pam[outCellRank][outCellFile];

        /* Input cell is just the next 'inCellRows' rows of input image */
        inCellPam = *inpamP;
        inCellPam.height = inCellRows;

        transformCell(&inCellPam, outCellPamP, xformCore);
    }    

    rewindCellFiles(outputMapP);

    stitchCellsToOutput(outputMapP, outpamP);

    closeCellFiles(outputMapP);

    destroyOutputMap(outputMapP);
}



static unsigned int
maxRowsThatFit(struct pam * const pamP,
               size_t       const availableMemory) {

    unsigned long const otherNeeds = 100*1024;
        /* A wild guess at how much memory (from the same pool as the
           input rows) is needed for things other than the input rows
        */
    unsigned long const availForRows =
        availableMemory > otherNeeds ? availableMemory - otherNeeds : 0;
    unsigned int const bytesPerTuple =
        pamP->depth * sizeof(sample) + sizeof(tuple *);
    unsigned int const bytesPerRow =
        pamP->width * bytesPerTuple + sizeof(tuple **);

    unsigned long const maxRows = availForRows / bytesPerRow;

    if (maxRows < 1)
        pm_error("You haven't allowed enough memory to fit even one row "
                 "of the source image in memory.  The minimum chunk size "
                 "is one row; we need at least %lu bytes.",
                 otherNeeds + bytesPerRow);

    return (unsigned int)MIN(maxRows, UINT_MAX);
}



static void
transformPbm(struct pam *     const inpamP,
             struct pam *     const outpamP,
             struct xformCore const xform,
             bool             const verbose) {

    if (xform.b == 0 && xform.c == 0) {
        /* Rows of input map to rows of target; no column-for-row */
        if (xform.d == 1)
            /* Row N of the output is based only on Row N of the
               input, so we can transform row by row and avoid
               in-memory buffering altogether.
            */
            transformRowByRowPbm(inpamP, outpamP, xform.a == -1);
        else
            /* Row N of the output is based only on Row ~N of the
               input.  We need all the rows in memory, but have to pass
               through them only twice, so there is no page thrashing concern.
            */
            transformRowsBottomTopPbm(inpamP, outpamP, xform.a == -1);
    } else {
        /* This is a column-for-row type of transformation, which requires
           complex traversal of an in-memory image.
        */
        if (SSE_PBM_XY_FLIP)
            pamflip_transformRowsToColumnsPbmSse(inpamP, outpamP, xform);
        else
            transformPbmGen(inpamP, outpamP, xform);
    }
}



static void
transformNonPbm(struct pam *     const inpamP,
                struct pam *     const outpamP,
                struct xformCore const xform,
                unsigned int     const availableMemory,
                bool             const verbose) {

    if (xform.b == 0 && xform.c == 0 && xform.d == 1) {
        /* Row N of the output is based only on Row N of the
           input, so we can transform row by row and avoid
           in-memory buffering altogether.
        */
        if (verbose)
            pm_message("Transforming row by row");
        transformRowByRowNonPbm(inpamP, outpamP, xform.a == -1);
    } else {
        unsigned int const maxRows = maxRowsThatFit(inpamP, availableMemory);
        if (maxRows >= inpamP->height) {
            /* We can fit the whole image in memory at once and avoid
               temporary files.
            */
            if (xform.b == 0 && xform.c == 0 && xform.d == -1 &&
                xform.a == 1) {
                /* This is just a vertical flip;  We can move whole rows
                   instead of individual pixels and save time.
                */
                if (verbose)
                    pm_message("Transforming whole rows, all in memory");

                transformRowsBottomTopNonPbm(inpamP, outpamP);
            } else {
                if (verbose)
                    pm_message("Transforming whole image at once, "
                               "pixel by pixel");
                transformNonPbmWhole(inpamP, outpamP, xform, verbose);
            }
        } else
            /* No optimizations possible */
            transformNonPbmChunk(inpamP, outpamP, xform, maxRows, verbose);
    }
}



int
main(int argc, char * argv[]) {
    struct cmdlineInfo cmdline;
    struct pam inpam;
    struct pam outpam;
    unsigned int cols, rows;
    FILE * ifP;

    pnm_init(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    if (cmdline.availableMemory < UINT_MAX)
        ifP = pm_openr_seekable(cmdline.inputFilespec);
    else
        ifP = pm_openr(cmdline.inputFilespec);
    
    pnm_readpaminit(ifP, &inpam, PAM_STRUCT_SIZE(tuple_type));

    outpam = inpam;  /* initial value */

    outpam.file = stdout;
    xformDimensions(cmdline.xform, inpam.width, inpam.height, &cols, &rows);
    outpam.width = cols; outpam.height = rows;

    pnm_writepaminit(&outpam);

    switch (PNM_FORMAT_TYPE(inpam.format)) {
    case PBM_TYPE:
        transformPbm(&inpam, &outpam, cmdline.xform, cmdline.verbose);
        break;
    default:
        transformNonPbm(&inpam, &outpam, cmdline.xform,
                        cmdline.availableMemory, cmdline.verbose);
    }
    pm_close(inpam.file);
    pm_close(outpam.file);
    
    return 0;
}
