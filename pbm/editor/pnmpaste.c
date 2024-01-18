/* pnmpaste.c - paste a rectangle into a PNM image
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

#include <assert.h>

#include "pm_c_util.h"
#include "mallocvar.h"
#include "nstring.h"
#include "shhopt.h"
#include "pnm.h"


enum boolOp {REPLACE, AND, OR, XOR /*, NAND, NOR, NXOR */ };

struct CmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    const char * baseFilename;
    const char * insetFilename;
    int insertCol;  /* Negative means from right edge */
    int insertRow;  /* Negative means from bottom edge */
    enum boolOp operation;
};



static void
parseCommandLine(int argc, const char ** argv,
                 struct CmdlineInfo * const cmdlineP) {
/*----------------------------------------------------------------------------
   Note that the file spec array we return is stored in the storage that
   was passed to us as the argv array.
-----------------------------------------------------------------------------*/
    optEntry *option_def;
        /* Instructions to OptParseOptions3 on how to parse our options.
         */
    optStruct3 opt;

    unsigned int option_def_index;
    unsigned int replaceOpt, andOpt, orOpt, xorOpt;

    MALLOCARRAY_NOFAIL(option_def, 100);

    option_def_index = 0;   /* incremented by OPTENT3 */
    OPTENT3(0,   "replace",     OPT_FLAG,    NULL,
            &replaceOpt,           0);
    OPTENT3(0,   "and",         OPT_FLAG,    NULL,
            &andOpt,               0);
    OPTENT3(0,   "or",          OPT_FLAG,    NULL,
            &orOpt,                0);
    OPTENT3(0,   "xor",         OPT_FLAG,    NULL,
            &xorOpt,               0);

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = TRUE;  /* We have parms that are negative numbers */

    pm_optParseOptions3(&argc, (char **)argv, opt, sizeof opt, 0);
        /* Uses and sets argc, argv, and some of *cmdlineP and others. */

    if (replaceOpt + andOpt + orOpt + xorOpt > 1)
        pm_error("You may specify only one of -replace, -and, -or, and -xor");

    cmdlineP->operation =
        replaceOpt ? REPLACE :
        andOpt     ? AND     :
        orOpt      ? OR      :
        xorOpt     ? XOR     :
        replaceOpt;
        

    if (argc-1 >= 3) {
        cmdlineP->insetFilename = argv[1];
        cmdlineP->insertCol     = atoi(argv[2]);
        cmdlineP->insertRow     = atoi(argv[3]);

        if (argc-1 >= 4) {
            cmdlineP->baseFilename = argv[4];

            if (argc-1 > 4)
                pm_error("Too many arguments: %u.  This program takes "
                         "at most 4", argc-1);
        } else
            cmdlineP->baseFilename = "-";
    } else
        pm_error("You must specify at least 3 arguments: \"from\" file "
                 "name, insert-at column, and insert-at row.  "
                 "You specified %u", argc-1);

    if (streq(cmdlineP->baseFilename, "-") &&
        streq(cmdlineP->insetFilename, "-"))
        pm_error("You can't use Standard Input for both the input images");
}



static unsigned char
leftBits(unsigned char const x,
         unsigned int  const n){
/*----------------------------------------------------------------------------
  'x' with the leftmost (high) n bits retained and the rest cleared to zero.
-----------------------------------------------------------------------------*/
    assert(n <= 8);

    return (x >> (8-n)) << (8-n);
}



static unsigned char
rightBits(unsigned char const x,
          unsigned int  const n){
/*----------------------------------------------------------------------------
  The rightmost 'n' bits of 'x'.
-----------------------------------------------------------------------------*/
    assert(n <= 8);

    return ((unsigned char)(x << (8-n))) >> (8-n);
}



static void
insertDirect(FILE *          const ifP,
             unsigned char * const destrow,
             unsigned int    const cols,
             int             const format,
             enum boolOp     const operation,
             unsigned char * const buffer) {
/*----------------------------------------------------------------------------
   Read the next row from PBM file 'ifP' and merge it according to
   'operation' into 'destrow', flush left in packed PBM format.

   'cols' and 'format' describe the 'ifP' image.

   'buffer' is a scratch buffer for our use, at least wide enough to hold
   a packed PBM row of 'ifP'.
-----------------------------------------------------------------------------*/
    /* We use pbm_readpbmrow_packed() to read whole bytes rounded up and merge
       those into 'destrow', which means we update more than we're supposed to
       if the image is not a multiple of 8 columns.  In that case, we then fix
       up the last byte by replacing the bits from the original image that we
       messed up.
    */
    unsigned int  const colBytes  = pbm_packed_bytes(cols);
    unsigned int  const last      = colBytes - 1;
    unsigned char const origRight = destrow[last];

    if (operation == REPLACE)
        pbm_readpbmrow_packed(ifP, destrow, cols, format);
    else {
        unsigned int i;

        pbm_readpbmrow_packed(ifP, buffer, cols, format);

        for (i = 0; i < colBytes; ++i) {
            switch (operation) {
            case AND: destrow[i] |= buffer[i]; break;
            case OR : destrow[i] &= buffer[i]; break;
            case XOR: destrow[i]  = ~( destrow[i] ^ buffer[i] ) ; break;
            /*
            case NAND: destrow[i] = ~( destrow[i] | buffer[i] ) ; break;
            case NOR : destrow[i] = ~( destrow[i] & buffer[i] ) ; break;
            case NXOR: destrow[i] ^= buffer[i]  ; break;
            */
            case REPLACE: assert(false); break;
            }
        }
    }

    /* destrow[] now contains garbage in all but the cols % 8 leftmost bits of
       the last byte we touched.  Those are supposed to be unchanged from the
       input, so we restore them now.
    */
    if (cols % 8 > 0)
        destrow[last] = leftBits(destrow[last], cols % 8)
            | rightBits(origRight, 8 - cols % 8);
}



static void
insertShift(FILE *          const ifP,
            unsigned char * const destrow,
            unsigned int    const cols,
            unsigned int    const format,
            unsigned int    const offset,
            enum boolOp     const operation,
            unsigned char * const buffer) {
/*----------------------------------------------------------------------------
   Same as insertDirect(), but start merging 'offset' bits from the left
   end of 'destrow'.  'offset' is less than 8.

   buffer[] is wide enough to hold a packed PBM row of *ifP plus two
   bytes of margin.
-----------------------------------------------------------------------------*/
    unsigned int  const shiftByteCt = pbm_packed_bytes(cols + offset);
    unsigned int  const last        = shiftByteCt - 1;
    unsigned char const origLeft    = destrow[0];
    unsigned char const origRight   = destrow[last];

    unsigned int const padOffset = (cols + offset) % 8;

    unsigned int i;

    assert(offset < 8);

    pbm_readpbmrow_packed(ifP, &buffer[1], cols, format);

    /* Note that buffer[0] is undefined. */

    for (i = 0; i < shiftByteCt; ++i) {
        unsigned int  const rsh = offset;
        unsigned int  const lsh = 8-rsh;
        unsigned char const t = buffer[i] << lsh | buffer[i+1] >> rsh;

        switch (operation) {
        case REPLACE: destrow[i] = t; break;
        case AND:     destrow[i] |= t; break;
        case OR :     destrow[i] &= t; break;
        case XOR:     destrow[i] = ~ (destrow[i] ^ t); break;
        /*
        case NAND:    destrow[i] = ~ (destrow[i] | t); break;
        case NOR :    destrow[i] = ~ (destrow[i] & t); break;
        case NXOR:    destrow[i] ^= t; break;
        */
        }
    }

    /* destrow[] now contains garbage in the 'offset' leftmost bits and
       8-offset rightmost bits of the last byte we touched.  Those are
       supposed to be unchanged from the input, so we restore them now.
    */

    destrow[0] = leftBits(origLeft, offset) |
        rightBits(destrow[0], 8-offset);
   
    if (padOffset % 8 > 0)
        destrow[last] = leftBits(destrow[last], padOffset) |
            rightBits(origRight , 8-padOffset);
}



static void
pastePbm(FILE *       const fpInset,
         FILE *       const fpBase,
         int          const insetFormat,
         int          const baseFormat,
         unsigned int const insetRows,
         unsigned int const baseRows,
         unsigned int const insetCols,
         unsigned int const baseCols,
         unsigned int const insertCol,
         unsigned int const insertRow,
         enum boolOp  const operation) {
/*----------------------------------------------------------------------------
  Fast paste for PBM
-----------------------------------------------------------------------------*/
    unsigned char * const baserow       = pbm_allocrow_packed(baseCols);
    unsigned char * const buffer        = pbm_allocrow_packed(insetCols+16);
    unsigned int    const shiftByteCt   = insertCol / 8;
    unsigned int    const shiftOffset   = insertCol % 8;
    unsigned int    const baseColByteCt = pbm_packed_bytes(baseCols);

    unsigned int row;

    pbm_writepbminit(stdout, baseCols, baseRows, 0);

    for (row = 0; row < baseRows; ++row) {
        pbm_readpbmrow_packed(fpBase, baserow, baseCols, baseFormat);
        
        if (row >= insertRow && row < insertRow + insetRows) {
            if (shiftOffset == 0)
                insertDirect(fpInset, &baserow[shiftByteCt], insetCols,
                             insetFormat, operation, buffer);
            else
                insertShift(fpInset, &baserow[shiftByteCt], insetCols,
                            insetFormat, shiftOffset, operation, buffer);
        }

        if (baseCols % 8 > 0)
            baserow[baseColByteCt-1]
                = leftBits(baserow[baseColByteCt-1] , baseCols % 8);

        pbm_writepbmrow_packed(stdout, baserow, baseCols, 0);
    }
    pbm_freerow_packed(buffer);
    pbm_freerow_packed(baserow);
}



static void
pasteNonPbm(FILE *       const fpInset,
            FILE *       const fpBase,
            int          const formatInset,
            int          const formatBase,
            int          const newformat,
            xelval       const maxvalInset,
            xelval       const maxvalBase,
            unsigned int const rowsInset,
            unsigned int const rowsBase,
            unsigned int const colsInset,
            unsigned int const colsBase,
            unsigned int const insertCol,
            unsigned int const insertRow) {

    /* Logic works for PBM, but cannot do bitwise operations */             

    xelval const newmaxval = MAX(maxvalInset, maxvalBase);

    xel * const xelrowInset = pnm_allocrow(colsInset);
    xel * const xelrowBase  = pnm_allocrow(colsBase);

    unsigned int row;

    pnm_writepnminit(stdout, colsBase, rowsBase, newmaxval, newformat, 0);

    for (row = 0; row < rowsBase; ++row) {
        pnm_readpnmrow(fpBase, xelrowBase, colsBase, maxvalBase, formatBase);
        pnm_promoteformatrow(xelrowBase, colsBase, maxvalBase, formatBase,
                             newmaxval, newformat);

        if (row >= insertRow && row < insertRow + rowsInset) {
            unsigned int colInset;

            pnm_readpnmrow(fpInset, xelrowInset, colsInset, maxvalInset,
                           formatInset);
            pnm_promoteformatrow(xelrowInset, colsInset, maxvalInset,
                                 formatInset, newmaxval, newformat );
            for (colInset = 0; colInset < colsInset; ++colInset)
                xelrowBase[insertCol + colInset] = xelrowInset[colInset];
        }
        pnm_writepnmrow(stdout, xelrowBase, colsBase, newmaxval, newformat, 0);
    }
    
    pnm_freerow(xelrowBase);
    pnm_freerow(xelrowInset);
}



int
main(int argc, const char ** argv) {

    struct CmdlineInfo cmdline;
    FILE * fpInset;
    FILE * fpBase;
    xelval maxvalInset, maxvalBase;
    int rowsInset, colsInset;
    int formatInset;
    int rowsBase, colsBase;
    int formatBase;
    int newformat;
    unsigned int insertRow, insertCol;

    pm_proginit(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    fpInset = pm_openr(cmdline.insetFilename);
    fpBase  = pm_openr(cmdline.baseFilename);

    pnm_readpnminit(fpInset, &colsInset, &rowsInset,
                    &maxvalInset, &formatInset);
    pnm_readpnminit(fpBase, &colsBase, &rowsBase, &maxvalBase, &formatBase);

    if (colsBase < colsInset)
        pm_error(
            "Image to paste is wider than base image by %u cols",
            colsInset - colsBase);
    else if (cmdline.insertCol <= -colsBase)
        pm_error(
            "x is too negative -- the second image has only %u cols",
            colsBase);
    else if (cmdline.insertCol >= colsBase)
        pm_error(
            "x is too large -- the second image has only %u cols",
            colsBase);

    if (rowsBase < rowsInset)
        pm_error(
            "Image to paste is taller than base image by %u rows",
            rowsInset - rowsBase);
    else if (cmdline.insertRow <= -rowsBase)
        pm_error(
            "y is too negative -- the second image has only %u rows",
            rowsBase);
    else if (cmdline.insertRow >= rowsBase)
        pm_error(
            "y is too large -- the second image has only %d rows",
            rowsBase);

    insertCol = cmdline.insertCol < 0 ?
        colsBase + cmdline.insertCol : cmdline.insertCol;
    insertRow = cmdline.insertRow < 0 ?
        rowsBase + cmdline.insertRow : cmdline.insertRow;

    if (insertCol + colsInset > colsBase)
        pm_error("Extends over right edge by %u pixels",
                 (insertCol + colsInset) - colsBase);
    if (insertRow + rowsInset > rowsBase)
        pm_error("Extends over bottom edge by %u pixels",
                 (insertRow + rowsInset) - rowsBase);

    newformat = MAX(PNM_FORMAT_TYPE(formatInset), PNM_FORMAT_TYPE(formatBase));

    if (cmdline.operation != REPLACE && newformat != PBM_TYPE)
        pm_error("no logical operations allowed for a non-PBM image");

    if (newformat == PBM_TYPE)
        pastePbm(fpInset, fpBase, formatInset, formatBase,
                 rowsInset, rowsBase, colsInset, colsBase,
                 insertCol, insertRow, cmdline.operation);
    else
        pasteNonPbm(fpInset, fpBase,
                    formatInset, formatBase, newformat,
                    maxvalInset, maxvalBase,
                    rowsInset, rowsBase, colsInset, colsBase,
                    insertCol, insertRow);

    pm_close(fpInset);
    pm_close(fpBase);
    pm_close(stdout);

    return 0;
}
