/* pnmcat.c - concatenate PNM images
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

#include <assert.h>

#include "pm_c_util.h"
#include "mallocvar.h"
#include "shhopt.h"
#include "bitarith.h"
#include "nstring.h"
#include "pnm.h"

#define LEFTBITS pm_byteLeftBits
#define RIGHTBITS pm_byteRightBits

enum backcolor {BACK_WHITE, BACK_BLACK, BACK_AUTO};

enum orientation {TOPBOTTOM, LEFTRIGHT};

enum justification {JUST_CENTER, JUST_MIN, JUST_MAX};

struct imgInfo {
    /* This obviously should be a struct pam.  We should convert this
       to 'pamcat'.
    */
    FILE * ifP;
    int    cols;
    int    rows;
    int    format;
    xelval maxval;
};



struct cmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    const char ** inputFilespec;
    unsigned int nfiles;
    enum backcolor backcolor;
    enum orientation orientation;
    enum justification justification;
};



static void
parseCommandLine(int argc, const char ** const argv,
                 struct cmdlineInfo * const cmdlineP) {
/*----------------------------------------------------------------------------
   Note that the file spec array we return is stored in the storage that
   was passed to us as the argv array.
-----------------------------------------------------------------------------*/
    optEntry * option_def;
        /* Instructions to OptParseOptions3() on how to parse our options.
         */
    optStruct3 opt;

    unsigned int option_def_index;

    unsigned int leftright, topbottom, black, white, jtop, jbottom,
        jleft, jright, jcenter;

    MALLOCARRAY_NOFAIL(option_def, 100);

    option_def_index = 0;   /* incremented by OPTENTRY */
    OPTENT3(0, "leftright",  OPT_FLAG,   NULL, &leftright,   0);
    OPTENT3(0, "lr",         OPT_FLAG,   NULL, &leftright,   0);
    OPTENT3(0, "topbottom",  OPT_FLAG,   NULL, &topbottom,   0);
    OPTENT3(0, "tb",         OPT_FLAG,   NULL, &topbottom,   0);
    OPTENT3(0, "black",      OPT_FLAG,   NULL, &black,       0);
    OPTENT3(0, "white",      OPT_FLAG,   NULL, &white,       0);
    OPTENT3(0, "jtop",       OPT_FLAG,   NULL, &jtop,        0);
    OPTENT3(0, "jbottom",    OPT_FLAG,   NULL, &jbottom,     0);
    OPTENT3(0, "jleft",      OPT_FLAG,   NULL, &jleft,       0);
    OPTENT3(0, "jright",     OPT_FLAG,   NULL, &jright,      0);
    OPTENT3(0, "jcenter",    OPT_FLAG,   NULL, &jcenter,     0);

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = FALSE;  /* We have no parms that are negative numbers */

    pm_optParseOptions3(&argc, (char **)argv, opt, sizeof(opt), 0);
        /* Uses and sets argc, argv, and some of *cmdlineP and others. */

    free(option_def);

    if (leftright + topbottom > 1)
        pm_error("You may specify only one of -topbottom (-tb) and "
                 "-leftright (-lr)");
    else if (leftright)
        cmdlineP->orientation = LEFTRIGHT;
    else if (topbottom)
        cmdlineP->orientation = TOPBOTTOM;
    else
        pm_error("You must specify either -leftright or -topbottom");

    if (black + white > 1)
        pm_error("You may specify only one of -black and -white");
    else if (black)
        cmdlineP->backcolor = BACK_BLACK;
    else if (white)
        cmdlineP->backcolor = BACK_WHITE;
    else
        cmdlineP->backcolor = BACK_AUTO;

    if (jtop + jbottom + jleft + jright + jcenter > 1)
        pm_error("You may specify onlyone of -jtop, -jbottom, "
                 "-jleft, and -jright");
    else {
        switch (cmdlineP->orientation) {
        case LEFTRIGHT:
            if (jleft)
                pm_error("-jleft is invalid with -leftright");
            if (jright)
                pm_error("-jright is invalid with -leftright");
            if (jtop)
                cmdlineP->justification = JUST_MIN;
            else if (jbottom)
                cmdlineP->justification = JUST_MAX;
            else if (jcenter)
                cmdlineP->justification = JUST_CENTER;
            else
                cmdlineP->justification = JUST_CENTER;
            break;
        case TOPBOTTOM:
            if (jtop)
                pm_error("-jtop is invalid with -topbottom");
            if (jbottom)
                pm_error("-jbottom is invalid with -topbottom");
            if (jleft)
                cmdlineP->justification = JUST_MIN;
            else if (jright)
                cmdlineP->justification = JUST_MAX;
            else if (jcenter)
                cmdlineP->justification = JUST_CENTER;
            else
                cmdlineP->justification = JUST_CENTER;
            break;
        }
    }

    if (argc-1 < 1) {
        MALLOCARRAY_NOFAIL(cmdlineP->inputFilespec, 1);
        cmdlineP->inputFilespec[0] = "-";
        cmdlineP->nfiles = 1;
    } else {
        unsigned int i;
        unsigned int stdinCt;
            /* Number of input files user specified as Standard Input */

        MALLOCARRAY_NOFAIL(cmdlineP->inputFilespec, argc-1);

        for (i = 0, stdinCt = 0; i < argc-1; ++i) {
            cmdlineP->inputFilespec[i] = argv[1+i];
            if (streq(argv[1+i], "-"))
                ++stdinCt;
        }
        cmdlineP->nfiles = argc-1;
        if (stdinCt > 1)
            pm_error("At most one input image can come from Standard Input.  "
                     "You specified %u", stdinCt);
    }
}



static void
computeOutputParms(unsigned int     const nfiles,
                   enum orientation const orientation,
                   struct imgInfo   const img[],
                   unsigned int *   const newcolsP,
                   unsigned int *   const newrowsP,
                   xelval *         const newmaxvalP,
                   int *            const newformatP) {

    double newcols, newrows;
    int newformat;
    xelval newmaxval;

    unsigned int i;

    newcols = 0;
    newrows = 0;

    for (i = 0; i < nfiles; ++i) {
        const struct imgInfo * const imgP = &img[i];

        if (i == 0) {
            newmaxval = imgP->maxval;
            newformat = imgP->format;
        } else {
            if (PNM_FORMAT_TYPE(imgP->format) > PNM_FORMAT_TYPE(newformat))
                newformat = imgP->format;
            if (imgP->maxval > newmaxval)
                newmaxval = imgP->maxval;
        }
        switch (orientation) {
        case LEFTRIGHT:
            newcols += imgP->cols;
            if (imgP->rows > newrows)
                newrows = imgP->rows;
            break;
        case TOPBOTTOM:
            newrows += imgP->rows;
            if (imgP->cols > newcols)
                newcols = imgP->cols;
            break;
        }
    }

    /* Note that while 'double' is not in general a precise numerical type,
       in the case of a sum of integers which is less than INT_MAX, it
       is exact, because double's precision is greater than int's.
    */
    if (newcols > INT_MAX)
       pm_error("Output width too large: %.0f.", newcols);
    if (newrows > INT_MAX)
       pm_error("Output height too large: %.0f.", newrows);

    *newrowsP   = (unsigned int)newrows;
    *newcolsP   = (unsigned int)newcols;
    *newmaxvalP = newmaxval;
    *newformatP = newformat;
}



static void
copyBitrow(const unsigned char * const source,
           unsigned char *       const destBitrow,
           unsigned int          const cols,
           unsigned int          const offset) {
/*----------------------------------------------------------------------------
  Copy from source to destBitrow, without shifting.  Preserve
  surrounding image data.
-----------------------------------------------------------------------------*/
    unsigned char * const dest = & destBitrow[ offset/8 ];
        /* Copy destination, with leading full bytes ignored. */
    unsigned int const rs = offset % 8;
        /* The "little offset", as measured from start of dest.  Source
           is already shifted by this value.
        */
    unsigned int const trs = (cols + rs) % 8;
        /* The number of partial bits in the final char. */
    unsigned int const colByteCnt = pbm_packed_bytes(cols + rs);
        /* # bytes to process, including partial ones on both ends. */
    unsigned int const last = colByteCnt - 1;

    unsigned char const origHead = dest[0];
    unsigned char const origEnd  = dest[last];

    unsigned int i;

    assert(colByteCnt >= 1);

    for (i = 0; i < colByteCnt; ++i)
        dest[i] = source[i];

    if (rs > 0)
        dest[0] = LEFTBITS(origHead, rs) | RIGHTBITS(dest[0], 8-rs);

    if (trs > 0)
        dest[last] = LEFTBITS(dest[last], trs) | RIGHTBITS(origEnd, 8-trs);
}



static void
padFillBitrow(unsigned char * const destBitrow,
              unsigned char   const padColor,
              unsigned int    const cols,
              unsigned int    const offset) {
/*----------------------------------------------------------------------------
   Fill destBitrow, starting at offset, with padColor.  padColor is a
   byte -- 0x00 or 0xff -- not a single bit.
-----------------------------------------------------------------------------*/
    unsigned char * const dest = &destBitrow[offset/8];
    unsigned int const rs = offset % 8;
    unsigned int const trs = (cols + rs) % 8;
    unsigned int const colByteCnt = pbm_packed_bytes(cols + rs);
    unsigned int const last = colByteCnt - 1;

    unsigned char const origHead = dest[0];
    unsigned char const origEnd  = dest[last];

    unsigned int i;

    assert(colByteCnt > 0);

    for (i = 0; i < colByteCnt; ++i)
        dest[i] = padColor;

    if (rs > 0)
        dest[0] = LEFTBITS(origHead, rs) | RIGHTBITS(dest[0], 8-rs);

    if (trs > 0)
        dest[last] = LEFTBITS(dest[last], trs) | RIGHTBITS(origEnd, 8-trs);
}



/* concatenateLeftRightPBM() and concatenateLeftRightGen()
   employ almost identical algorithms.
   The difference is in the data types and functions.

   Same for concatenateTopBottomPBM() and concatenateTopBottomGen().
*/


struct imgInfoPbm2 {
    /* Information about one image */
    unsigned char * proberow;
        /* Top row of image, when background color is
           auto-determined.
        */
    unsigned int offset;
        /* start position of image, in bits, counting from left
           edge
        */
    unsigned char background;
        /* Background color.  0x00 means white; 0xff means black */
    unsigned int padtop;
        /* Top padding amount */
};



static void
getPbmImageInfo(struct imgInfo        const img[],
                unsigned int          const nfiles,
                unsigned int          const newrows,
                enum justification    const justification,
                enum backcolor        const backcolor,
                struct imgInfoPbm2 ** const img2P) {
/*----------------------------------------------------------------------------
   Read the first row of each image in img[] and return that and additional
   information about images as *img2P.
-----------------------------------------------------------------------------*/
    struct imgInfoPbm2 * img2;
    unsigned int i;

    MALLOCARRAY_NOFAIL(img2, nfiles);

    for (i = 0; i < nfiles; ++i) {
        switch (justification) {
        case JUST_MIN:    img2[i].padtop = 0;                           break;
        case JUST_MAX:    img2[i].padtop = newrows - img[i].rows;       break;
        case JUST_CENTER: img2[i].padtop = (newrows - img[i].rows) / 2; break;
        }
        
        img2[i].offset = (i == 0) ? 0 : img2[i-1].offset + img[i-1].cols;
        
        if (img[i].rows == newrows)  /* no padding */
            img2[i].proberow = NULL;
        else {                   /* determine pad color for image i */
            switch (backcolor) {
            case BACK_AUTO: {
                bit bgBit;
                img2[i].proberow =
                    pbm_allocrow_packed((unsigned int)img[i].cols + 7);
                pbm_readpbmrow_bitoffset(
                    img[i].ifP, img2[i].proberow,
                    img[i].cols, img[i].format, img2[i].offset % 8);

                bgBit = pbm_backgroundbitrow(
                    img2[i].proberow, img[i].cols, img2[i].offset % 8);

                img2[i].background = bgBit == PBM_BLACK ? 0xff : 0x00;
            } break;
            case BACK_BLACK:
                img2[i].proberow   = NULL;
                img2[i].background = 0xff;
                break;
            case BACK_WHITE:
                img2[i].proberow   = NULL;
                img2[i].background = 0x00;
                break;
            }
        }
    }
    *img2P = img2;
}



static void
destroyPbmImg2(struct imgInfoPbm2 * const img2,
               unsigned int         const nfiles) {

    unsigned int i;

    for (i = 0; i < nfiles; ++i) {
        if (img2[i].proberow)
            free(img2[i].proberow);
    }
    free(img2);
}



static void
concatenateLeftRightPbm(FILE *             const ofP,
                        unsigned int       const nfiles,
                        unsigned int       const newcols,
                        unsigned int       const newrows,
                        enum justification const justification,
                        struct imgInfo     const img[],   
                        enum backcolor     const backcolor) {

    unsigned char * const outrow = pbm_allocrow_packed(newcols);
        /* We use just one outrow.  All padding and image data (with the
           exeption of following img2.proberow) goes directly into this
           packed PBM row. 
        */

    struct imgInfoPbm2 * img2;
        /* malloc'ed array, one element per image.  Shadows img[] */
    unsigned int row;

    getPbmImageInfo(img, nfiles, newrows, justification, backcolor, &img2);

    outrow[pbm_packed_bytes(newcols)-1] = 0x00;

    for (row = 0; row < newrows; ++row) {
        unsigned int i;

        for (i = 0; i < nfiles; ++i) {

            if ((row == 0 && img2[i].padtop > 0) ||
                row == img2[i].padtop + img[i].rows) {

                /* This row begins a run of padding, either above or below
                   file 'i', so set 'outrow' to padding.
                */
                padFillBitrow(outrow, img2[i].background, img[i].cols,
                              img2[i].offset);
            }

            if (row == img2[i].padtop && img2[i].proberow != NULL) {
                /* Top row has been read to proberow[] to determine
                   background.  Copy it to outrow[].
                */
                copyBitrow(img2[i].proberow, outrow,
                           img[i].cols, img2[i].offset);
            } else if (row >= img2[i].padtop &&
                       row < img2[i].padtop + img[i].rows) {
                pbm_readpbmrow_bitoffset(
                    img[i].ifP, outrow, img[i].cols, img[i].format,
                    img2[i].offset);
            } else {
                /* It's a row of padding, so outrow[] is already set
                   appropriately.
                */
            }
        }
        pbm_writepbmrow_packed(ofP, outrow, newcols, 0);
    }

    destroyPbmImg2(img2, nfiles);

    pbm_freerow_packed(outrow);
}



static void
concatenateTopBottomPbm(FILE *             const ofP,
                        unsigned int       const nfiles,
                        int                const newcols,
                        int                const newrows,
                        enum justification const justification,
                        struct imgInfo     const img[],
                        enum backcolor     const backcolor) {

    unsigned char * const outrow = pbm_allocrow_packed(newcols);
        /* Like the left-right PBM case, all padding and image data
           goes directly into outrow.  There is no proberow.
        */
    unsigned char background, backgroundPrev;
        /* 0x00 means white; 0xff means black */
    unsigned int  padleft;
    bool          backChange;
        /* Background color is different from that of the previous
           input image.
        */

    unsigned int i;
    unsigned int row, startRow;
    
    outrow[pbm_packed_bytes(newcols)-1] = 0x00;

    switch (backcolor){
    case BACK_AUTO:   /* do nothing */    break;
    case BACK_BLACK:  background = 0xff;  break;
    case BACK_WHITE:  background = 0x00;  break;
    }

    for (i = 0; i < nfiles; ++i) {
        if (img[i].cols == newcols) {
            /* No padding */
            startRow = 0;
            backChange = FALSE;
            padleft = 0;
            outrow[pbm_packed_bytes(newcols)-1] = 0x00;
        } else {
            /* Determine amount of padding and color */
            switch (justification) {
            case JUST_MIN:     padleft = 0;                           break;
            case JUST_MAX:     padleft = newcols - img[i].cols;       break;
            case JUST_CENTER:  padleft = (newcols - img[i].cols) / 2; break;
            }

            switch (backcolor) {
            case BACK_AUTO: {
                bit bgBit;

                startRow = 1;
                
                pbm_readpbmrow_bitoffset(img[i].ifP,
                                         outrow, img[i].cols, img[i].format,
                                         padleft);

                bgBit = pbm_backgroundbitrow(outrow, img[i].cols, padleft);
                background = bgBit == PBM_BLACK ? 0xff : 0x00;

                backChange = (i == 0 || background != backgroundPrev);
            } break;
            case BACK_WHITE:
            case BACK_BLACK:
                startRow = 0;
                backChange = (i==0);
                break;
            }

            if (backChange || (i > 0 && img[i-1].cols > img[i].cols)) {
                unsigned int const padright = newcols - padleft - img[i].cols;
                
                if (padleft > 0)
                    padFillBitrow(outrow, background, padleft, 0);
                
                if (padright > 0)            
                    padFillBitrow(outrow, background, padright,
                                  padleft + img[i].cols);
                
            }
        }
            
        if (startRow == 1)
            /* Top row already read for auto background color
               determination.  Write it out.
            */
            pbm_writepbmrow_packed(ofP, outrow, newcols, 0);
        
        for (row = startRow; row < img[i].rows; ++row) {
            pbm_readpbmrow_bitoffset(img[i].ifP, outrow, img[i].cols,
                                     img[i].format, padleft);
            pbm_writepbmrow_packed(ofP, outrow, newcols, 0);
        }

        backgroundPrev = background;
    }
    pbm_freerow_packed(outrow);
}



struct imgGen2 {
    xel * xelrow;
    xel * inrow;
    xel   background;
    int   padtop;
};



static void
getGenImgInfo(struct imgInfo     const img[],
              unsigned int       const nfiles,
              xel *              const newxelrow,
              unsigned int       const newrows,
              xelval             const newmaxval,
              int                const newformat,
              enum justification const justification,
              enum backcolor     const backcolor,
              struct imgGen2 **  const img2P) {

    struct imgGen2 * img2;
    unsigned int i;

    MALLOCARRAY_NOFAIL(img2, nfiles);

    for (i = 0; i < nfiles; ++i) {
        switch (justification) {  /* Determine top padding */
            case JUST_MIN:
                img2[i].padtop = 0;
                break;
            case JUST_MAX:
                img2[i].padtop = newrows - img[i].rows;
                break;
            case JUST_CENTER:
                img2[i].padtop = (newrows - img[i].rows) / 2;
                break;
        }

        img2[i].inrow =
            (i == 0 ? &newxelrow[0] : img2[i-1].inrow + img[i-1].cols);

        if (img[i].rows == newrows)  /* no padding */
            img2[i].xelrow = NULL;
        else {
            /* Determine pad color */
            switch (backcolor){
            case BACK_AUTO:
                img2[i].xelrow = pnm_allocrow(img[i].cols);
                pnm_readpnmrow(img[i].ifP, img2[i].xelrow,
                               img[i].cols, img[i].maxval, img[i].format);
                pnm_promoteformatrow(img2[i].xelrow, img[i].cols,
                                     img[i].maxval, img[i].format,
                                     newmaxval, newformat);
                img2[i].background = pnm_backgroundxelrow(
                    img2[i].xelrow, img[i].cols, newmaxval, newformat);
                break;
            case BACK_BLACK:
                img2[i].xelrow = NULL;
                img2[i].background = pnm_blackxel(newmaxval, newformat);
                break;
            case BACK_WHITE:
                img2[i].xelrow = NULL;
                img2[i].background = pnm_whitexel(newmaxval, newformat);
                break;
            }
        }
    }
    *img2P = img2;
}



static void
concatenateLeftRightGen(FILE *             const ofP,
                        unsigned int       const nfiles,
                        unsigned int       const newcols,
                        unsigned int       const newrows,
                        xelval             const newmaxval,
                        int                const newformat,
                        enum justification const justification,
                        struct imgInfo     const img[],
                        enum backcolor     const backcolor) {

    xel * const outrow = pnm_allocrow(newcols);
    struct imgGen2 * img2;
    unsigned int row;

    getGenImgInfo(img, nfiles, outrow, newrows,
                  newmaxval, newformat, justification, backcolor, &img2);

    for (row = 0; row < newrows; ++row) {
        unsigned int i;

        for (i = 0; i < nfiles; ++i) {
            if ((row == 0 && img2[i].padtop > 0) ||
                row == img2[i].padtop + img[i].rows) {
                /* This row begins a run of padding, either above or below
                   file 'i', so set 'outrow' to padding.
                */
                unsigned int col;
                for (col = 0; col < img[i].cols; ++col)
                    img2[i].inrow[col] = img2[i].background;
            }
            if (row == img2[i].padtop && img2[i].xelrow) {
                /* We're at the top row of file 'i', and that row
                   has already been read to xelrow[] to determine
                   background.  Copy it to 'outrow'.
                */
                unsigned int col;
                for (col = 0; col < img[i].cols; ++col)
                    img2[i].inrow[col] = img2[i].xelrow[col];
                
                free(img2[i].xelrow);
            } else if (row >= img2[i].padtop &&
                       row < img2[i].padtop + img[i].rows) {
                pnm_readpnmrow(
                    img[i].ifP, img2[i].inrow, img[i].cols, img[i].maxval,
                    img[i].format);
                pnm_promoteformatrow(
                    img2[i].inrow, img[i].cols, img[i].maxval,
                    img[i].format, newmaxval, newformat);
            } else {
                /* It's a row of padding, so outrow[] is already set
                   appropriately.
                */
            }
        }
        pnm_writepnmrow(ofP, outrow, newcols, newmaxval, newformat, 0);
    }
    pnm_freerow(outrow);
}



static void
concatenateTopBottomGen(FILE *             const ofP,
                        unsigned int       const nfiles,
                        int                const newcols,
                        int                const newrows,
                        xelval             const newmaxval,
                        int                const newformat,
                        enum justification const justification,
                        struct imgInfo     const img[],
                        enum backcolor     const backcolor) {

    xel * const newxelrow = pnm_allocrow(newcols);
    xel * inrow;
    unsigned int padleft;
    unsigned int i;
    unsigned int row, startRow;
    xel background, backgroundPrev;
    bool backChange;
        /* The background color is different from that of the previous
           input image.
        */

    switch (backcolor) {
    case BACK_AUTO: /* do nothing now, determine at start of each image */
                     break;
    case BACK_BLACK: background = pnm_blackxel(newmaxval, newformat);
                     break;
    case BACK_WHITE: background = pnm_whitexel(newmaxval, newformat);
                     break;
    }

    for ( i = 0; i < nfiles; ++i, backgroundPrev = background) {
        if (img[i].cols == newcols) {
            /* no padding */
            startRow = 0;
            backChange = FALSE;
            inrow = newxelrow;
        } else { /* Calculate left padding amount */ 
            switch (justification) {
            case JUST_MIN:    padleft = 0;                            break;
            case JUST_MAX:    padleft = newcols - img[i].cols;        break;
            case JUST_CENTER: padleft = (newcols - img[i].cols) / 2;  break;
            }

            if (backcolor == BACK_AUTO) {
                /* Determine background color */

                startRow = 1;
                inrow = &newxelrow[padleft];

                pnm_readpnmrow(img[i].ifP, inrow,
                               img[i].cols, img[i].maxval, img[i].format);
                pnm_promoteformatrow(inrow, img[i].cols, img[i].maxval,
                                     img[i].format,
                                     newmaxval, newformat);
                background = pnm_backgroundxelrow(
                    inrow, img[i].cols, newmaxval, newformat);

                backChange = i==0 || !PNM_EQUAL(background, backgroundPrev);
            } else {
                /* background color is constant: black or white */
                startRow = 0;
                inrow = &newxelrow[padleft];
                backChange = (i==0);
            }

            if (backChange || (i > 0 && img[i-1].cols > img[i].cols)) {
                unsigned int col;

                for (col = 0; col < padleft; ++col)
                    newxelrow[col] = background;
                for (col = padleft + img[i].cols; col < newcols; ++col)
                    newxelrow[col] = background;
            }
        }

        if (startRow == 1)
            /* Top row already read for auto background
               color determination.  Write it out. */
            pnm_writepnmrow(ofP, newxelrow, newcols, newmaxval, newformat, 0);

        for (row = startRow; row < img[i].rows; ++row) {
            pnm_readpnmrow(img[i].ifP,
                           inrow, img[i].cols, img[i].maxval, img[i].format);
            pnm_promoteformatrow(
                inrow, img[i].cols, img[i].maxval, img[i].format,
                newmaxval, newformat);

            pnm_writepnmrow(ofP, newxelrow, newcols, newmaxval, newformat, 0);
        }
    }
    pnm_freerow(newxelrow);
}



int
main(int           argc,
     const char ** argv) {

    struct cmdlineInfo cmdline;
    struct imgInfo * img;  /* malloc'ed array */
    xelval newmaxval;
    int newformat;
    unsigned int i;
    unsigned int newrows, newcols;

    pm_proginit(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    MALLOCARRAY_NOFAIL(img, cmdline.nfiles);

    for (i = 0; i < cmdline.nfiles; ++i) {
        img[i].ifP = pm_openr(cmdline.inputFilespec[i]);
        pnm_readpnminit(img[i].ifP, &img[i].cols, &img[i].rows,
                        &img[i].maxval, &img[i].format);
    }

    computeOutputParms(cmdline.nfiles, cmdline.orientation, img,
                       &newcols, &newrows, &newmaxval, &newformat);

    pnm_writepnminit(stdout, newcols, newrows, newmaxval, newformat, 0);

    if (PNM_FORMAT_TYPE(newformat) == PBM_TYPE) {
        switch (cmdline.orientation) {
        case LEFTRIGHT:
            concatenateLeftRightPbm(stdout, cmdline.nfiles,
                                    newcols, newrows, cmdline.justification,
                                    img, cmdline.backcolor);
            break;
        case TOPBOTTOM:
            concatenateTopBottomPbm(stdout, cmdline.nfiles,
                                    newcols, newrows, cmdline.justification,
                                    img, cmdline.backcolor);
            break;
        }
    } else {
        switch (cmdline.orientation) {
        case LEFTRIGHT:
            concatenateLeftRightGen(stdout, cmdline.nfiles,
                                    newcols, newrows, newmaxval, newformat,
                                    cmdline.justification, img,
                                    cmdline.backcolor);
            break;
        case TOPBOTTOM:
            concatenateTopBottomGen(stdout, cmdline.nfiles,
                                    newcols, newrows, newmaxval, newformat,
                                    cmdline.justification, img,
                                    cmdline.backcolor);
            break;
        }
    }
    for (i = 0; i < cmdline.nfiles; ++i)
        pm_close(img[i].ifP);
    free(cmdline.inputFilespec);
    free(img);
    pm_close(stdout);

    return 0;
}
