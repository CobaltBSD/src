/* +-------------------------------------------------------------------+ */
/* | Copyright 1990, 1991, 1993, David Koblas.  (koblas@netcom.com)    | */
/* |   Permission to use, copy, modify, and distribute this software   | */
/* |   and its documentation for any purpose and without fee is hereby | */
/* |   granted, provided that the above copyright notice appear in all | */
/* |   copies and that both that copyright notice and this permission  | */
/* |   notice appear in supporting documentation.  This software is    | */
/* |   provided "as is" without express or implied warranty.           | */
/* +-------------------------------------------------------------------+ */

/* There is a copy of the GIF89 specification, as defined by its inventor,
   Compuserve, in 1990 at: 
   http://www.w3.org/Graphics/GIF/spec-gif89a.txt

   This covers the high level format, but does not cover how the "data"
   contents of a GIF image represent the raster of color table indices.
   An appendix describes extensions to Lempel-Ziv that GIF makes (variable
   length compression codes and the clear and end codes), but does not
   describe the Lempel-Ziv base.
*/

#define _XOPEN_SOURCE 500  /* Make sure strdup() is in string.h */
#define _BSD_SOURCE   /* for strcaseeq */
#include <string.h>
#include <assert.h>

#include "pm_config.h"
#include "pm_c_util.h"
#include "mallocvar.h"
#include "nstring.h"
#include "shhopt.h"
#include "pnm.h"

#define GIFMAXVAL 255
#define MAXCOLORMAPSIZE 256

#define CM_RED 0
#define CM_GRN 1
#define CM_BLU 2

#define MAX_LZW_BITS  12

#ifndef   FASTPBMRENDER
  #define FASTPBMRENDER TRUE
#endif

static const bool useFastPbmRender = FASTPBMRENDER;

#ifndef   REPORTLZWCODES
  #define REPORTLZWCODES FALSE
#endif

static const bool wantLzwCodes = REPORTLZWCODES;
    /* In verbose output, include all the LZW codes */



static void
readFile(FILE *          const ifP,
         unsigned char * const buffer,
         size_t          const len,
         const char **   const errorP) {

    size_t bytesRead;

    bytesRead = fread(buffer, 1, len, ifP);

    if (bytesRead == len)
        *errorP = NULL;
    else {
        if (ferror(ifP))
            pm_asprintf(errorP, "Error reading file.  errno=%d (%s)",
                        errno, strerror(errno));
        else if (feof(ifP))
            pm_asprintf(errorP, "End of file encountered");
        else
            pm_asprintf(errorP, "Short read -- %u bytes of %u",
                        (unsigned)bytesRead, (unsigned)len);
    }
}



struct CmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    const char * inputFilespec;  /* Filespecs of input files */
    unsigned int verbose;    /* -verbose option */
    unsigned int comments;   /* -comments option */
    bool allImages;  /* He wants all the images */
    unsigned int imageNum;
        /* image number he wants from input, starting at 0.  Undefined
           if allImages is TRUE
        */
    const char * alphaFileName;
    unsigned int quitearly;
    unsigned int repair;
};



static void
parseCommandLine(int argc, char ** argv,
                 struct CmdlineInfo * const cmdlineP) {
/*----------------------------------------------------------------------------
   Note that the file spec array we return is stored in the storage that
   was passed to us as the argv array.
-----------------------------------------------------------------------------*/
    optEntry * option_def;
        /* Instructions to pm_optParseOptions3 on how to parse our options.
         */
    
    optStruct3 opt;

    unsigned int alphaSpec, imageSpec;
    const char * image;

    unsigned int option_def_index;

    MALLOCARRAY_NOFAIL(option_def, 100);
    
    option_def_index = 0;   /* incremented by OPTENTRY */
    OPTENT3(0, "verbose",     OPT_FLAG, NULL, 
            &cmdlineP->verbose,         0);
    OPTENT3(0, "comments",    OPT_FLAG, NULL,
            &cmdlineP->comments,        0);
    OPTENT3(0, "quitearly",   OPT_FLAG, NULL,
            &cmdlineP->quitearly,       0);
    OPTENT3(0, "repair",      OPT_FLAG, NULL,
            &cmdlineP->repair,          0);
    OPTENT3(0, "image",       OPT_STRING, &image,
            &imageSpec,                 0);
    OPTENT3(0, "alphaout",    OPT_STRING, &cmdlineP->alphaFileName, 
            &alphaSpec,                 0);

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = FALSE;  /* We have no parms that are negative numbers */

    pm_optParseOptions3( &argc, argv, opt, sizeof(opt), 0);
        /* Uses and sets argc, argv, and some of *cmdlineP and others. */

    free(option_def);

    if (!imageSpec) {
        cmdlineP->imageNum = 0;
        cmdlineP->allImages = FALSE;
    } else {
        if (strcaseeq(image, "all")) { 
            cmdlineP->allImages = TRUE;
        } else {
            char * tailptr;

            long const imageNum = strtol(image, &tailptr, 10);

            if (*tailptr != '\0')
                pm_error("Invalid value for '-image' option.  Must be either "
                         "a number or 'all'.  You specified '%s'", image);
            else if (imageNum < 0)
                pm_error("Invalid value for '-image' option.  Must be "
                         "positive.  You specified %ld", imageNum);
            else if (imageNum == 0)
                pm_error("Invalid value for 'image' option.  You specified "
                         "zero.  The first image is 1.");

            cmdlineP->allImages = FALSE;
            cmdlineP->imageNum = (unsigned int) imageNum - 1;
        }
    }
    
    if (argc-1 == 0) 
        cmdlineP->inputFilespec = "-";
    else if (argc-1 != 1)
        pm_error("Program takes zero or one argument (filename).  You "
                 "specified %d", argc-1);
    else
        cmdlineP->inputFilespec = argv[1];

    if (!alphaSpec) 
        cmdlineP->alphaFileName = NULL;
}



typedef struct {
    unsigned char map[MAXCOLORMAPSIZE][3];
    unsigned int size;
} GifColorMap;

/*----------------------------------------------------------------------
  On GIF color maps:

  The color map can have any number of colors up to 256.  If the color map
  size is not a power of 2 the table is padded up.  The LZW "clear" control
  code is always placed at a power of 2.

  The color map and code table of an image with three colors (black, white
  and red) will look like this:

  0: black
  1: white
  2: red
  3: (unused)
  4: clear code
  5: end code
  6: first LZW string code
  7: second LZW string code
     ...
  4095: last LZW string code

  Some GIFs have odd color maps.

  (1) Some encoders use fixed color maps.  A GIF image produced by this
      kind of encoder may have colors in the table which never appear in
      the image.

      Note that we make the decision on whether the output should be PBM,
      PGM or PPM by scanning through the color map, not the entire image.
      Any unused colors will influence our decision.

  (2) There are GIF editors which allow one to rewrite the color map.
      These programs will produce color maps with multiple entries for the
      same color.

  (3) Some encoders put the transparent code outside the color map.
      (In the above example, the unused value 3.)  Around 2000 there were
      several encoders that did this, including "Animation Gif Maker
      (GifAnim)".  As of 2012, such images are rare.  We reject them with
      an error message unless -repair is specified.
-----------------------------------------------------------------------*/


struct GifScreen {
    unsigned int    width;
    unsigned int    height;
    bool            hasGlobalColorMap;
        /* The stream has a global color map, to wit 'colorMap'.
           (If the stream doesn't have a global color map, the individual
           images must each have a local color map)
        */
    GifColorMap     colorMap;
        /* The global color map for the stream.  Meaningful only if
           'hasGlobalColorMap' is true.
        */
    unsigned int    colorResolution;
    unsigned int    background;
    unsigned int    aspectRatio;
        /* Aspect ratio of each pixel, times 64, minus 15.  (i.e. 1 => 1:4).
           But Zero means 1:1.
        */
    bool     hasGray;  
        /* Boolean: global colormap has at least one gray color
           (not counting black and white) 
        */
    bool     hasColor;
        /* Boolean: global colormap has at least one non-gray,
           non-black, non-white color 
        */
};

struct Gif89 {
    bool         haveTransColor;
        /* The GIF specifies a transparent background color */
    unsigned int transparentIndex;
        /* The color index of the color which is the transparent 
           background color.

           Meaningful only when 'haveTransColor' is true
        */
    bool          haveDelayTime;
    unsigned int  delayTime;
    bool          haveInputFlag;
    unsigned char inputFlag;
    bool          haveDisposal;
    unsigned char disposal;
};

static void
initGif89(struct Gif89 * const gif89P) {
    gif89P->haveTransColor = false;
    gif89P->haveDelayTime  = false;
    gif89P->haveInputFlag  = false;
    gif89P->haveDisposal   = false;
}       


static bool verbose;
static bool showComment;



static void
readColorMap(FILE *        const ifP,
             unsigned int  const cmapSize,
             GifColorMap * const cmapP,
             bool *        const hasGrayP,
             bool *        const hasColorP) {
/*----------------------------------------------------------------------------
   Read a color map from a GIF stream, where the stream is on *ifP,
   which is positioned to a color map, which is 'cmapSize' bytes long.

   Return as *cmapP that color map.

   Furthermore, analyze that color map and return *hasGrayP == true iff it
   contains any gray (black and white don't count) and *hasColorP == true iff
   it contains anything that is not gray or black or white.
-----------------------------------------------------------------------------*/
    unsigned int  i;
    unsigned char rgb[3];

    assert(cmapSize <= MAXCOLORMAPSIZE);

    *hasGrayP = FALSE;  /* initial assumption */
    *hasColorP = FALSE;  /* initial assumption */

    for (i = 0; i < cmapSize; ++i) {
        const char * error;
        readFile(ifP, rgb, sizeof(rgb), &error);
        if (error)
            pm_error("Unable to read Color %u from colormap.  %s", i, error);

        cmapP->map[i][CM_RED] = rgb[0] ;
        cmapP->map[i][CM_GRN] = rgb[1] ;
        cmapP->map[i][CM_BLU] = rgb[2] ;

        if (rgb[0] == rgb[1] && rgb[1] == rgb[2]) {
            if (rgb[0] != 0 && rgb[0] != GIFMAXVAL)
                *hasGrayP = TRUE;
        } else
            *hasColorP = TRUE;
    }
    cmapP->size = cmapSize;
}



static bool zeroDataBlock = FALSE;
    /* the most recently read DataBlock was an EOD marker, i.e. had
       zero length
    */

static void
getDataBlock(FILE *          const ifP, 
             unsigned char * const buf, 
             bool *          const eofP,
             unsigned int *  const lengthP,
             const char **   const errorP) {
/*----------------------------------------------------------------------------
   Read a DataBlock from file 'ifP', return it at 'buf'.

   The first byte of the datablock is the length, in pure binary, of the
   rest of the datablock.  We return the data portion (not the length byte)
   of the datablock at 'buf', and its length as *lengthP.

   Except that if we hit EOF or have an I/O error reading the first
   byte (size field) of the DataBlock, we return *eofP == TRUE and
   *lengthP == 0.

   We return *eofP == FALSE if we don't hit EOF or have an I/O error.

   If we hit EOF or have an I/O error reading the data portion of the
   DataBlock, we exit the program with pm_error().
-----------------------------------------------------------------------------*/
    long const pos = ftell(ifP);

    unsigned char count;
    const char * error;
    
    readFile(ifP, &count, sizeof(count), &error);

    if (error) {
        pm_message("EOF or error in reading DataBlock size from file.  %s",
                   error);
        pm_strfree(error);
        *errorP = NULL;
        *eofP = TRUE;
        *lengthP = 0;
    } else {
        if (verbose)
            pm_message("%d byte block at Position %ld", count, pos);
        *eofP = FALSE;
        *lengthP = count;

        if (count == 0) {
            *errorP = NULL;
            zeroDataBlock = TRUE;
        } else {
            const char * error;

            zeroDataBlock = FALSE;
            readFile(ifP, buf, count, &error); 

            if (error) {
                pm_asprintf(errorP,
                            "Unable to read data portion of %u byte "
                            "DataBlock from file.  %s", count, error);
                pm_strfree(error);
            } else
                *errorP = NULL;
        }
    }
}



static void
readThroughEod(FILE * const ifP) {
/*----------------------------------------------------------------------------
  Read the file 'ifP' through the next EOD marker.  An EOD marker is a
  a zero length data block.

  If there is no EOD marker between the present file position and EOF,
  we read to EOF and issue warning message about a missing EOD marker.
-----------------------------------------------------------------------------*/
    unsigned char buf[256];
    bool eod;

    eod = FALSE;  /* initial value */
    while (!eod) {
        bool eof;
        unsigned int count;
        const char * error;

        getDataBlock(ifP, buf, &eof, &count, &error);
        if (error || eof)
            pm_message("EOF encountered before EOD marker.  The GIF "
                       "file is malformed, but we are proceeding "
                       "anyway as if an EOD marker were at the end "
                       "of the file.");
        if (error || eof || count == 0)
            eod = TRUE;
    }
}



static void
doPlainTextExtension(FILE * const ifP) {
#if 0
    /* incomplete code fragment, attempt to handle Plain Text Extension */
    GetDataBlock(ifP, (unsigned char*) buf, &eof, &length);
    
    lpos   = LM_to_uint(buf[0], buf[1]);
    tpos   = LM_to_uint(buf[2], buf[3]);
    width  = LM_to_uint(buf[4], buf[5]);
    height = LM_to_uint(buf[6], buf[7]);
    cellw  = buf[8];
    cellh  = buf[9];
    foreground = buf[10];
    background = buf[11];
#else
    readThroughEod(ifP);
#endif
}



static void
doCommentExtension(FILE * const ifP) {
/*----------------------------------------------------------------------------
   Read the rest of a comment extension from the input file 'ifP' and handle
   it.
   
   We ought to deal with the possibility that the comment is not text.  I.e.
   it could have nonprintable characters or embedded nulls.  I don't know if
   the GIF spec requires regular text or not.
-----------------------------------------------------------------------------*/
    char buf[256];
    unsigned int blocklen;  
    bool done;

    done = FALSE;
    while (!done) {
        bool eof;
        const char * error;
        getDataBlock(ifP, (unsigned char*) buf, &eof, &blocklen, &error); 
        if (error)
            pm_error("Error reading a data block in a comment extension.  %s",
                     error);
        if (blocklen == 0 || eof)
            done = TRUE;
        else {
            buf[blocklen] = '\0';
            if (showComment) {
                pm_message("gif comment: %s", buf);
            }
        }
    }
}



static unsigned int
LM_to_uint(unsigned char const a,
           unsigned char const b) {

    return ((unsigned int)b << 8) | ((unsigned int) a << 0);
}



static void 
doGraphicControlExtension(FILE *         const ifP,
                          struct Gif89 * const gif89P) {

    bool eof;
    unsigned int length;
    unsigned char buf[256];
    const char * error;

    getDataBlock(ifP, buf, &eof, &length, &error);
    if (error)
        pm_error("Error reading 1st data block of Graphic Control Extension");
    if (eof)
        pm_error("EOF/error encountered reading "
                 "1st DataBlock of Graphic Control Extension.");
    else if (length < 4) 
        pm_error("graphic control extension 1st DataBlock too short.  "
                 "It must be at least 4 bytes; it is %d bytes.",
                 length);
    else {
        gif89P->haveDisposal = true;
        gif89P->disposal = (buf[0] >> 2) & 0x7;
        gif89P->haveInputFlag = true;
        gif89P->inputFlag = (buf[0] >> 1) & 0x1;
        gif89P->haveDelayTime = true;
        gif89P->delayTime = LM_to_uint(buf[1], buf[2]);
        if ((buf[0] & 0x1) != 0) {
            gif89P->haveTransColor = true;
            gif89P->transparentIndex = buf[3];
        }
        readThroughEod(ifP);
    }
}



static void
doExtension(FILE *         const ifP,
            unsigned char  const label,
            struct Gif89 * const gif89P) {

    const char * str;
    
    switch (label) {
    case 0x01:              /* Plain Text Extension */
        str = "Plain Text";
        doPlainTextExtension(ifP);
        break;
    case 0xff:              /* Application Extension */
        str = "Application";
        readThroughEod(ifP);
        break;
    case 0xfe:              /* Comment Extension */
        str = "Comment";
        doCommentExtension(ifP);
        break;
    case 0xf9:              /* Graphic Control Extension */
        str = "Graphic Control";
        doGraphicControlExtension(ifP, gif89P);
        break;
    default: {
        char buf[256];
        sprintf(buf, "UNKNOWN (0x%02x)", label);
        str = buf;
        pm_message("Ignoring unrecognized extension (type 0x%02x)", label);
        readThroughEod(ifP);
    } break;
    }
    if (verbose)
        pm_message(" got a '%s' extension", str);
}



struct GetCodeState {
    unsigned char buf[280];
        /* This is the buffer through which we read the data from the 
           stream.  We must buffer it because we have to read whole data
           blocks at a time, but our client wants one code at a time.
           The buffer typically contains the contents of one data block
           plus two bytes from the previous data block.
        */
    int bufCount;
        /* This is the number of bytes of contents in buf[]. */
    int curbit;
        /* The bit number (starting at 0) within buf[] of the next bit
           to be returned.  If the next bit to be returned is not yet in
           buf[] (we've already returned everything in there), this points
           one beyond the end of the buffer contents.
        */
    bool streamExhausted;
        /* The last time we read from the input stream, we got an EOD marker
           or EOF or an error that prevents further reading of the stream.
        */
};



static void
getAnotherBlock(FILE *                const ifP, 
                struct GetCodeState * const gsP,
                const char **         const errorP) {

    unsigned int count;
    unsigned int assumedCount;
    bool eof;

    /* Shift buffer down so last two bytes are now the
       first two bytes.  Shift 'curbit' cursor, which must
       be somewhere in or immediately after those two
       bytes, accordingly.
    */
    gsP->buf[0] = gsP->buf[gsP->bufCount-2];
    gsP->buf[1] = gsP->buf[gsP->bufCount-1];

    gsP->curbit -= (gsP->bufCount-2)*8;
    gsP->bufCount = 2;
        
    /* Add the next block to the buffer */
    getDataBlock(ifP, &gsP->buf[gsP->bufCount], &eof, &count, errorP);
    if (*errorP)
        gsP->streamExhausted = TRUE;
    else {
        if (eof) {
            pm_message("EOF encountered in image "
                       "before EOD marker.  The GIF "
                       "file is malformed, but we are proceeding "
                       "anyway as if an EOD marker were at the end "
                       "of the file.");
            assumedCount = 0;
        } else
            assumedCount = count;

        gsP->streamExhausted = (assumedCount == 0);
        
        gsP->bufCount += assumedCount;
    }
}



static struct GetCodeState getCodeState;

static void
getCode_init(struct GetCodeState * const getCodeStateP) {
    
    /* Fake a previous data block */
    getCodeStateP->buf[0] = 0;
    getCodeStateP->buf[1] = 0;
    getCodeStateP->bufCount = 2;
    getCodeStateP->curbit = getCodeStateP->bufCount * 8;
    getCodeStateP->streamExhausted = FALSE;
}



static unsigned int
bitsOfLeBuffer(const unsigned char * const buf,
               unsigned int          const start,
               unsigned int          const len) {
/*----------------------------------------------------------------------------
   Return a string of 'len' bits (up to 16) starting at bit 'start' of buffer
   buf[].

   In the buffer, the bits are numbered Intel-style, with the first bit of a
   byte being the least significant bit.  So bit 3 is the "16" bit of the
   first byte of buf[].

   We return the string as an integer such that its pure binary encoding with
   the bits numbered Intel-style is the string.  E.g. the string 0,1,1 
   yields six.
-----------------------------------------------------------------------------*/
    uint32_t codeBlock;
        /* The 3 whole bytes of the buffer that contain the requested
           bit string
        */

    assert(len <= 16);

    if (BYTE_ORDER == LITTLE_ENDIAN && UNALIGNED_OK)
        /* Fast path */
        codeBlock = *(uint32_t *) & buf[start/8];
    else
        /* logic works for little endian too */
        codeBlock =
            (buf[start/8+0] <<  0) |
            (buf[start/8+1] <<  8) |
            (buf[start/8+2] << 16);
            
    return (unsigned int) 
        (codeBlock >> (start % 8)) & ((1 << len) - 1);
}



static void
getCode_get(struct GetCodeState * const gsP,
            FILE *                const ifP, 
            int                   const codeSize,
            bool *                const eofP,
            unsigned int *        const codeP,
            const char **         const errorP) {
/*----------------------------------------------------------------------------
  Read and return the next lzw code from the file *ifP.

  'codeSize' is the number of bits in the code we are to get.

  Return *eofP == TRUE iff we hit the end of the stream.  That means a legal
  end of stream, marked by an EOD marker, not just end of file.  An end of
  file in the middle of the GIF stream is an error.

  If there are bits left in the stream, but not 'codeSize' of them, we
  call that a success with *eofP == TRUE.

  Return the code read (assuming *eofP == FALSE and *errorP == NULL)
  as *codeP.
-----------------------------------------------------------------------------*/

    *errorP = NULL;

    while (gsP->curbit + codeSize > gsP->bufCount * 8 &&
           !gsP->streamExhausted && !*errorP) 
        /* Not enough left in buffer to satisfy request.  Get the next
           data block into the buffer.

           Note that a data block may be as small as one byte, so we may need
           to do this multiple times to get the full code.  (This probably
           never happens in practice).
        */
        getAnotherBlock(ifP, gsP, errorP);

    if (!*errorP) {
        if (gsP->curbit + codeSize > gsP->bufCount * 8) {
            /* The buffer still doesn't have enough bits in it; that means
               there were no data blocks left to read.
            */
            *eofP = TRUE;

            {
                int const bitsUnused = gsP->bufCount * 8 - gsP->curbit;
                if (bitsUnused > 0)
                    pm_message("Stream ends with a partial code "
                               "(%d bits left in file; "
                               "expected a %d bit code).  Ignoring.",
                               bitsUnused, codeSize);
            }
        } else {
            *codeP = bitsOfLeBuffer(gsP->buf, gsP->curbit, codeSize);

            if (verbose && wantLzwCodes)
                pm_message("LZW code=0x%03x [%d]", *codeP, codeSize);

            gsP->curbit += codeSize;
            *eofP = FALSE;
        }
    }
}



struct Stack {
    /* Stack grows from low addresses to high addresses */
    unsigned char * stack;  /* malloc'ed array */
    unsigned char * sp;     /* stack pointer */
    unsigned char * top;    /* next word above top of stack */
};



static void 
initStack(struct Stack * const stackP, unsigned int const size) {

    MALLOCARRAY(stackP->stack, size);
    if (stackP->stack == NULL)
        pm_error("Unable to allocate %d-word stack.", size);
    stackP->sp = stackP->stack;
    stackP->top = stackP->stack + size;
}



static void
pushStack(struct Stack * const stackP, unsigned char const value) {

    if (stackP->sp >= stackP->top)
        pm_error("stack overflow");

    *(stackP->sp++) = value;
}



static bool
stackIsEmpty(const struct Stack * const stackP) {
    return stackP->sp == stackP->stack;
}



static unsigned char
popStack(struct Stack * const stackP) {

    if (stackP->sp <= stackP->stack)
        pm_error("stack underflow");
    
    return *(--stackP->sp);
}



static void
termStack(struct Stack * const stackP) {
    free(stackP->stack);
    stackP->stack = NULL;
}

    

/*----------------------------------------------------------------------------
   Some notes on LZW.

   LZW is an extension of Limpel-Ziv.  The two extensions are:

     1) in Limpel-Ziv, codes are all the same number of bits.  In
        LZW, they start out small and increase as the stream progresses.

     2) LZW has a clear code that resets the string table and code
        size.

   The LZW code space is allocated as follows:

   The true data elements are dataWidth bits wide, so the maximum
   value of a true data element is 2**dataWidth-1.  We call that
   max_dataVal.  The first byte in the stream tells you what dataWidth
   is.

   LZW codes 0 - max_dataVal are direct codes.  Each one represents
   the true data element whose value is that of the LZW code itself.
   No decompression is required.

   max_dataVal + 1 and up are compression codes.  They encode
   true data elements:

   max_dataVal + 1 is the clear code.
         
   max_dataVal + 2 is the end code.

   max_dataVal + 3 and up are string codes.  Each string code 
   represents a string of true data elements.  The translation from a
   string code to the string of true data elements varies as the stream
   progresses.  In the beginning and after every clear code, the
   translation table is empty, so no string codes are valid.  As the
   stream progresses, the table gets filled and more string codes 
   become valid.

-----------------------------------------------------------------------------*/

static int const maxLzwCodeCt = (1<<MAX_LZW_BITS);

struct Decompressor {
    struct Stack stack;
    bool fresh;
        /* The stream is right after a clear code or at the very beginning */
    unsigned int codeSize;
        /* The current code size -- each LZW code in this part of the image
           is this many bits.  Ergo, we read this many bits at a time from
           the stream.
        */
    unsigned int maxCodeCt;
        /* The maximum number of LZW codes that can be represented with the 
           current code size.  (1 << codeSize)
        */
    unsigned int nextTableSlot;
        /* Index in the code translation table of the next free entry */
    unsigned int firstcode;
        /* This is always a true data element code */
    unsigned int prevcode;
        /* The code just before, in the image, the one we're processing now */

    /* The following are constant for the life of the decompressor */
    FILE * ifP;
    unsigned int initCodeSize;
    unsigned int cmapSize;
    unsigned int maxDataVal;
    unsigned int clearCode;
    unsigned int endCode;
    bool haveTransColor;
    unsigned int transparentIndex;
        /* meaningful only when 'haveTransColor' is true */
    bool tolerateBadInput; 
        /* We are to tolerate bad input data as best we can, rather than
           just declaring an error and bailing out.
        */
    unsigned int table[(1 << MAX_LZW_BITS)][2];   /* LZW code table */  
};



static void
resetDecompressor(struct Decompressor * const decompP) {

    decompP->codeSize      = decompP->initCodeSize+1;
    decompP->maxCodeCt     = 1 << decompP->codeSize;
    decompP->nextTableSlot = decompP->maxDataVal + 3;
    decompP->fresh         = TRUE;
}



static void
validateTransparentIndex(unsigned int const transparentIndex,
                         bool         const tolerateBadInput,
                         unsigned int const cmapSize,
                         unsigned int const maxDataVal) {

    if (transparentIndex >= cmapSize) {
        if (tolerateBadInput) {
            if (transparentIndex > maxDataVal)
                pm_error("Invalid transparent index value: %d",
                         transparentIndex);
        } else {
            pm_error("Invalid transparent index value %d in image with "
                     "only %u colors.  %s",
                     transparentIndex, cmapSize,
                     transparentIndex <= maxDataVal ?
                     "" :
                     "Use the -repair option to try to render the "
                     "image overriding this error.");
        }
    }
}



static void
lzwInit(struct Decompressor * const decompP, 
        FILE *                const ifP,
        int                   const initCodeSize,
        unsigned int          const cmapSize,
        bool                  const haveTransColor,
        unsigned int          const transparentIndex,
        bool                  const tolerateBadInput) {

    unsigned int const maxDataVal = (1 << initCodeSize) - 1;
    
    if (verbose)
        pm_message("Image says the initial compression code size is "
                   "%d bits", 
                   initCodeSize);
    
    decompP->ifP              = ifP;
    decompP->initCodeSize     = initCodeSize;
    decompP->cmapSize         = cmapSize;
    decompP->tolerateBadInput = tolerateBadInput;
    decompP->maxDataVal       = maxDataVal;
    decompP->clearCode        = maxDataVal + 1;
    decompP->endCode          = maxDataVal + 2;

    if (verbose)
        pm_message("Initial code size is %u bits; clear code = 0x%03x, "
                   "end code = 0x%03x",
                   decompP->initCodeSize, 
                   decompP->clearCode, decompP->endCode);
    
    /* The entries in the translation table for true data codes are
       constant throughout the image.  For PBM output we make an
       adjustment later.  Once set entries never change.
    */
    {
        unsigned int i;
        for (i = 0; i <= maxDataVal; ++i) {
            decompP->table[i][0] = 0;
            decompP->table[i][1] = i < cmapSize ? i : 0;
        }
    }
    decompP->haveTransColor   = haveTransColor;
    decompP->transparentIndex = transparentIndex;

    if (haveTransColor)
        validateTransparentIndex(transparentIndex, tolerateBadInput,
                                 cmapSize, maxDataVal);

    resetDecompressor(decompP);

    getCode_init(&getCodeState);
    
    decompP->fresh = TRUE;
    
    initStack(&decompP->stack, maxLzwCodeCt);

    assert(decompP->initCodeSize < sizeof(decompP->maxDataVal) * 8);
}



static void
lzwAdjustForPBM(struct Decompressor * const decompP,
                GifColorMap           const cmap) {
/*----------------------------------------------------------------------------
  In the PBM case we use the table index value directly instead of looking up
  the color map for each pixel.

  Note that cmap.size is not always 2.

  Similar logic should work for PGM.
----------------------------------------------------------------------------*/
    unsigned int i;
    for (i = 0; i < cmap.size; ++i)
        decompP->table[i][1] = cmap.map[i][0] == 0 ? PBM_BLACK : PBM_WHITE;
}



static void
lzwTerm(struct Decompressor * const decompP) {

    termStack(&decompP->stack);
}



static void
pushWholeStringOnStack(struct Decompressor * const decompP,
                       unsigned int          const code0) {
/*----------------------------------------------------------------------------
  Get the whole string that compression code 'code0' represents and push
  it onto the code stack so the leftmost code is on top.  Set
  decompP->firstcode to the first (leftmost) code in that string.
-----------------------------------------------------------------------------*/
    unsigned int code;
    unsigned int stringCount;

    for (stringCount = 0, code = code0;
         code > decompP->maxDataVal;
         ++stringCount, code = decompP->table[code][0]
        ) {

        pushStack(&decompP->stack, decompP->table[code][1]);
    }
    decompP->firstcode = decompP->table[code][1];
    pushStack(&decompP->stack, decompP->firstcode);
}



static void
expandCodeOntoStack(struct Decompressor * const decompP,
                    unsigned int          const incode,
                    const char **         const errorP) {
/*----------------------------------------------------------------------------
   'incode' is an LZW string code.  It represents a string of true data
   elements, as defined by the string translation table in *decompP.

   Expand the code to a string of LZW direct codes and push them onto the
   stack such that the leftmost code is on top.

   Also add to the translation table where appropriate.

   Iff the translation table contains a cycle (which means the LZW stream
   from which it was built is invalid), fail (return text explanation
   as *errorP).
-----------------------------------------------------------------------------*/
    unsigned int code;

    *errorP = NULL; /* Initial value */

    if (incode <= decompP->maxDataVal) {
        if (incode < decompP->cmapSize)
            code = incode;      /* Direct index */
        else if (decompP->tolerateBadInput &&
                 decompP->haveTransColor &&
                 decompP->table[incode][1] == decompP->transparentIndex)
            /* transparent code outside cmap   exceptional case */
            code = incode;
        else
            pm_asprintf(errorP, "Error in GIF image: invalid color code %u. "
                        "Valid color values are 0 - %u",
                        incode, decompP->cmapSize - 1);
    }
    else if (incode < decompP->nextTableSlot)  
        /* LZW string, defined */
        code = incode;
    else if  (incode == decompP->nextTableSlot && !decompP->fresh) {
        /* It's a code that isn't in our translation table yet.
           This does not happen with the decoder in a fresh state.
        */
        if (wantLzwCodes && verbose)
            pm_message ("LZW code valid, but not in decoder table");

        pushStack(&decompP->stack, decompP->firstcode);
        code = decompP->prevcode;
    } else
        pm_asprintf(errorP, "Error in GIF image: invalid LZW code");

    if (!*errorP) {
        pushWholeStringOnStack(decompP, code);

        if (decompP->nextTableSlot < maxLzwCodeCt) {
            decompP->table[decompP->nextTableSlot][0] = decompP->prevcode;
            decompP->table[decompP->nextTableSlot][1] = decompP->firstcode;
            ++decompP->nextTableSlot;
            if (decompP->nextTableSlot >= decompP->maxCodeCt) {
                /* We've used up all the codes of the current code size.
                   Future codes in the stream will have codes one bit longer.
                   But there's an exception if we're already at the LZW
                   maximum, in which case the codes will simply continue
                   the same size.
                */
                if (decompP->codeSize < MAX_LZW_BITS) {
                    ++decompP->codeSize;
                    decompP->maxCodeCt = 1 << decompP->codeSize;
                }
            }
        }
        decompP->prevcode = incode;
    }
}



static void
lzwReadByteFresh(struct GetCodeState * const getCodeStateP,
                 struct Decompressor * const decompP,
                 bool *                const endOfImageP,
                 unsigned char *       const dataReadP,
                 const char **         const errorP) {
/*----------------------------------------------------------------------------
  Read off all initial clear codes, read the first non-clear code, and return
  it as *dataReadP.

  Iff we hit end of image in so doing, return *endOfImageP true and nothing as
  *dataReadP.  One way we hit end of image is for that first non-clear code to
  be an end code.

  Assume the decompressor is fresh, i.e. there are no strings in the table
  yet, so the next code must be a direct true data code.
-----------------------------------------------------------------------------*/
    unsigned int code;
    bool eof;

    assert(decompP->fresh);  /* Entry requirement */

    decompP->fresh = FALSE;

    do {
        getCode_get(getCodeStateP, decompP->ifP, decompP->codeSize,
                    &eof, &code, errorP);
    } while (!*errorP && !eof && code == decompP->clearCode);

    if (!*errorP) {
        if (eof)
            *endOfImageP = TRUE;
        else if (code == decompP->endCode) {
            if (!zeroDataBlock)
                readThroughEod(decompP->ifP);
            *endOfImageP = TRUE;
        } else if (code >= decompP->cmapSize) { 
            pm_asprintf(errorP, "Error in GIF image: invalid color code %u. "
                        "Valid color values are: 0 - %u",
                        code, decompP->cmapSize-1);
            /* Set these values in order to avoid errors in the -repair
               case
            */
            decompP->prevcode = decompP->firstcode = 0;

            *endOfImageP = FALSE;
        } else {    /* valid code */
            decompP->prevcode  = code;
            decompP->firstcode = decompP->table[code][1];
            *dataReadP = decompP->firstcode;
            *endOfImageP = FALSE;
        }
    }
}




static void
lzwReadByte(struct Decompressor * const decompP,
            unsigned char *       const dataReadP,
            bool *                const endOfImageP,
            const char **         const errorP) {
/*----------------------------------------------------------------------------
  Return the next data element of the decompressed image.  In the context
  of a GIF, a data element is the color table index of one pixel.

  We read and return the next byte of the decompressed image.

  If we can't, because the stream is too corrupted to make sense out of
  it or the stream ends, we fail (return text description of why as
  *errorP).

  We forgive the case that the "end" code is the end of the stream --
  not followed by an EOD marker (zero length DataBlock).

  Iff we can't read a byte because we've hit the end of the image,
  we return *endOfImageP = true.
-----------------------------------------------------------------------------*/
    if (!stackIsEmpty(&decompP->stack)) {
        *errorP = NULL;
        *endOfImageP = FALSE;
        *dataReadP = popStack(&decompP->stack);
    } else if (decompP->fresh) {
        lzwReadByteFresh(&getCodeState, decompP, endOfImageP, dataReadP,
                         errorP);
    } else {
        unsigned int code;
        bool eof;
        getCode_get(&getCodeState, decompP->ifP, decompP->codeSize,
                    &eof, &code, errorP);
        if (!*errorP) {
            if (eof)
                pm_asprintf(errorP,
                            "Premature end of file; no proper GIF closing");
            else {
                if (code == decompP->clearCode) {
                    resetDecompressor(decompP);
                    lzwReadByteFresh(&getCodeState, decompP, endOfImageP,
                    dataReadP, errorP);
                } else {
                    if (code == decompP->endCode) {
                        if (!zeroDataBlock)
                            readThroughEod(decompP->ifP);
                        *endOfImageP = TRUE;
                        *errorP = NULL;
                    } else {
                        *endOfImageP = FALSE;
                        expandCodeOntoStack(decompP, code, errorP);
                        if (!*errorP)
                            *dataReadP = popStack(&decompP->stack);
                    }
                }
            }
        }
    }
}



enum pass {MULT8PLUS0, MULT8PLUS4, MULT4PLUS2, MULT2PLUS1};

static void
bumpRowInterlace(unsigned int   const rows,
                 unsigned int * const rowP,
                 enum pass *    const passP) {
/*----------------------------------------------------------------------------
   Move *pixelCursorP to the next row in the interlace pattern.
-----------------------------------------------------------------------------*/
    /* There are 4 passes:
       MULT8PLUS0: Rows 8, 16, 24, 32, etc.
       MULT8PLUS4: Rows 4, 12, 20, 28, etc.
       MULT4PLUS2: Rows 2, 6, 10, 14, etc.
       MULT2PLUS1: Rows 1, 3, 5, 7, 9, etc.
    */
    
    switch (*passP) {
    case MULT8PLUS0:
        *rowP += 8;
        break;
    case MULT8PLUS4:
        *rowP += 8;
        break;
    case MULT4PLUS2:
        *rowP += 4;
        break;
    case MULT2PLUS1:
        *rowP += 2;
        break;
    }
    /* Set the proper pass for the next read.  Note that if there are
       more than 4 rows, the sequence of passes is sequential, but
       when there are fewer than 4, we may skip e.g. from MULT8PLUS0
       to MULT4PLUS2.
    */
    while (*rowP >= rows && *passP != MULT2PLUS1) {
        switch (*passP) {
        case MULT8PLUS0:
            *passP = MULT8PLUS4;
            *rowP = 4;
            break;
        case MULT8PLUS4:
            *passP = MULT4PLUS2;
            *rowP = 2;
            break;
        case MULT4PLUS2:
            *passP = MULT2PLUS1;
            *rowP = 1;
            break;
        case MULT2PLUS1:
            /* We've read the entire image */
            break;
        }
    }
}


static void
renderRow(unsigned char *    const cmapIndexRow,
          unsigned int       const cols,
          GifColorMap        const cmap, 
          bool               const haveTransColor,
          unsigned int       const transparentIndex,
          FILE *             const imageOutfile,
          int                const format,
          xel *              const xelrow,
          FILE *             const alphaFileP,
          bit *              const alphabits) {
/*----------------------------------------------------------------------------
  Convert one row of cmap indexes to PPM/PGM/PBM output.

  Render the alpha row to *alphaFileP iff 'alphabits' is non-NULL.  If
  'haveTransColor' is false, render all white (i.e. the row is
  opaque).  'alphabits' is otherwise just a one-row buffer for us to use
  in rendering the alpha row.
  
  imageOutfile is NULL if user wants only the alpha file.
----------------------------------------------------------------------------*/
    if (alphabits) {
        unsigned int col;

        for (col=0; col < cols; ++col) {
            alphabits[col] =
                (haveTransColor && cmapIndexRow[col] == transparentIndex) ?
                PBM_BLACK : PBM_WHITE;
        }
        pbm_writepbmrow(alphaFileP, alphabits, cols, false);
    }

    if (imageOutfile) {
        if (useFastPbmRender && format == PBM_FORMAT && !haveTransColor) {

            bit * const bitrow = cmapIndexRow; 

            pbm_writepbmrow(imageOutfile, bitrow, cols, false);
        } else {
            /* PPM, PGM and PBM with transparent */
            unsigned int col;
            for (col = 0; col < cols; ++col) {
                unsigned char const cmapIndex = cmapIndexRow[col];
                const unsigned char * const color = cmap.map[cmapIndex];
                assert(cmapIndex < cmap.size);
                PPM_ASSIGN(xelrow[col],
                           color[CM_RED], color[CM_GRN],color[CM_BLU]);
            }
            pnm_writepnmrow(imageOutfile, xelrow, cols,
                            GIFMAXVAL, format, false);
        }
    }
}



static void
verifyPixelRead(bool          const endOfImage,
                const char *  const readError,
                unsigned int  const cols,
                unsigned int  const rows,
                const char ** const errorP) {

    if (readError)
        *errorP = pm_strdup(readError);
    else {
        if (endOfImage)
            pm_asprintf(errorP,
                        "Error in GIF image: Not enough raster data to fill "
                        "%u x %u dimensions.  "
                        "The image has proper ending sequence, so "
                        "this is not just a truncated file.",
                        cols, rows);
        else
            *errorP = NULL;
    }
}



static int
pnmFormat(bool const hasGray,
          bool const hasColor) {
/*----------------------------------------------------------------------------
  The proper PNM format (PBM, PGM, or PPM) for an image described
  by 'hasGray' and 'hasColor'.
-----------------------------------------------------------------------------*/
    int format;
    const char * formatName;
           
    if (hasColor) {
        format = PPM_FORMAT;
        formatName = "PPM";
    } else if (hasGray) {
        format = PGM_FORMAT;
        formatName = "PGM";
    } else {
        format = PBM_FORMAT;
        formatName = "PBM";
    }
    if (verbose) 
        pm_message("writing a %s file", formatName);
 
    return format;
}



static void
makePnmRow(struct Decompressor * const decompP,
           unsigned int          const cols,
           unsigned int          const rows,
           bool                  const fillWithZero,
           unsigned char *       const cmapIndexRow,
           const char **         const errorP) {

    bool fillingWithZero;
    unsigned int col;

    *errorP = NULL;  /* initial value */

    for (col = 0, fillingWithZero = fillWithZero;
         col < cols;
         ++col) {

        unsigned char colorIndex;

        if (fillingWithZero)
            colorIndex = 0;
        else { 
            const char *  readError;
            unsigned char readColorIndex;
            bool          endOfImage;

            lzwReadByte(decompP, &readColorIndex, &endOfImage, &readError);

            verifyPixelRead(endOfImage, readError, cols, rows, errorP);

            if (readError)
                pm_strfree(readError);

            if (*errorP) {
                /* Caller may want to try to ignore this error, so we
                   fill out the row with zeroes.  Note that we can't possibly
                   have another error while doing that.
                */
                fillingWithZero = true;
                colorIndex = 0;
            } else
                colorIndex = readColorIndex;
        }
        cmapIndexRow[col] = colorIndex;
    }
}



static void
convertRaster(struct Decompressor * const decompP,
              unsigned int          const cols,
              unsigned int          const rows,
              GifColorMap           const cmap, 
              bool                  const interlace,
              FILE *                const imageOutFileP,
              FILE *                const alphaFileP,
              bool                  const hasGray,
              bool                  const hasColor) {
/*----------------------------------------------------------------------------
   Read the raster from the GIF decompressor *decompP, and write it as a
   complete PNM stream (starting with the header) on *imageOutFileP and
   *alphaFileP.

   Assume that raster is 'cols' x 'rows', refers to colormap 'cmap', and is
   interlaced iff 'interlace' is true.

   Assume the image has gray levels and/or color per 'hasGray' and 'hasColor'.
-----------------------------------------------------------------------------*/
    int const format = pnmFormat(hasGray, hasColor);

    enum pass pass;
    bool fillingMissingPixels;
    unsigned int row;
    unsigned char ** cmapIndexArray;
    bit * alphabits;
    xel * xelrow;
    unsigned int outrow;
        /* Non-interlace: outrow is always 0: cmapIndexRow keeps pointing
           to the single row in array.

           Interlace: outrow is modified with each call to bumpRowInterface().
        */

    MALLOCARRAY2(cmapIndexArray, interlace ? rows : 1 , cols);

    if (imageOutFileP)
        pnm_writepnminit(imageOutFileP, cols, rows, GIFMAXVAL, format, FALSE);
    if (alphaFileP)
        pbm_writepbminit(alphaFileP, cols, rows, FALSE);

    xelrow = pnm_allocrow(cols);  
    if (!xelrow)
        pm_error("couldn't alloc space for image" );

    if (alphaFileP) {
        alphabits = pbm_allocrow(cols);
        if (!alphabits)
            pm_error("couldn't alloc space for alpha image" );
    } else
        alphabits = NULL;

    fillingMissingPixels = false;  /* initial value */
    pass = MULT8PLUS0;
    outrow = 0;

    for (row = 0; row < rows; ++row) {
        const char * problem;
        makePnmRow(decompP, cols, rows, fillingMissingPixels,
                   cmapIndexArray[outrow], &problem);

        if (problem) {
            /* makePnmRow() recovered from the problem and produced an output
               row, stuffed with zeroes as necessary
            */
            if (decompP->tolerateBadInput) {
                pm_message("WARNING: %s.  "
                           "Filling bottom %u rows with arbitrary color",
                           problem, rows - row);
                fillingMissingPixels = true;
            } else
                pm_error("Unable to read input image.  %s "
                         "(Output row: %u).  "
                         "Use the -repair option to try to salvage "
                         "some of the image",
                         problem, interlace ? outrow : row);
        }

        if (interlace)
            bumpRowInterlace(rows, &outrow, &pass);
        else
            renderRow(cmapIndexArray[outrow], cols, cmap,
                      decompP->haveTransColor, decompP->transparentIndex,
                      imageOutFileP, format, xelrow, alphaFileP, alphabits);
    }
    /* All rows decompressed (and rendered and output if non-interlaced) */  
    if (interlace) {
        unsigned int row;
        for (row = 0; row < rows; ++row) 
            renderRow(cmapIndexArray[row], cols, cmap,
                      decompP->haveTransColor, decompP->transparentIndex,
                      imageOutFileP, format, xelrow, alphaFileP, alphabits);
    }

    pnm_freerow(xelrow);
    if (alphabits)
        pbm_freerow(alphabits);
    pm_freearray2((void **)cmapIndexArray);
}



static void
skipExtraneousData(struct Decompressor * const decompP) {

    unsigned char byteRead;
    bool endOfImage;
    const char * error;

    endOfImage = FALSE;  /* initial value */

    lzwReadByte(decompP, &byteRead, &endOfImage, &error);

    if (error)
        pm_strfree(error);
    else {
        if (!endOfImage) {
            pm_message("Extraneous data at end of image.  "
                       "Skipped to end of image");

            while (!endOfImage && !error)
                lzwReadByte(decompP, &byteRead, &endOfImage, &error);

            if (error) {
                pm_message("Error encountered skipping to end of image: %s",
                           error);
                pm_strfree(error);
            }
        }
    }
}



static void
issueTransparencyMessage(bool         const haveTransColor,
                         unsigned int const transparentIndex, 
                         GifColorMap  const cmap) {
/*----------------------------------------------------------------------------
   If user wants verbose output, tell him whether there is a transparent
   background color ('haveTransColor') and if so what it is
   ('transparentIndex').
   
   Some GIFs put transparentIndex outside the color map.  Allow this only
   with "-repair", checked in lzwInit().  Here we issue a warning and report
   the substitute color.
-----------------------------------------------------------------------------*/
    if (verbose) {
        if (haveTransColor) {
            if (transparentIndex >= cmap.size) {
                const unsigned char * const color = cmap.map[0];
                pm_message("WARNING: Transparent index %u "
                           "is outside color map. "
                           "substitute background color: rgb:%02x/%02x/%02x ",
                           transparentIndex,
                           color[CM_RED],
                           color[CM_GRN],
                           color[CM_BLU]
                    );
            } else {
                const unsigned char * const color = cmap.map[transparentIndex];
                pm_message("transparent background color: rgb:%02x/%02x/%02x "
                           "Index %u",
                           color[CM_RED],
                           color[CM_GRN],
                           color[CM_BLU],
                           transparentIndex
                    );
            }
        } else
            pm_message("no transparency");
    }
}



static void
readImageData(FILE *       const ifP, 
              unsigned int const cols,
              unsigned int const rows,
              GifColorMap  const cmap, 
              bool         const interlace,
              bool         const haveTransColor,
              unsigned int const transparentIndex,
              FILE *       const imageOutFileP,
              FILE *       const alphaFileP,
              bool         const hasGray,
              bool         const hasColor,
              bool         const tolerateBadInput) {

    unsigned char lzwMinCodeSize;      
    struct Decompressor decomp;
    const char * error;

    readFile(ifP, &lzwMinCodeSize, sizeof(lzwMinCodeSize), &error);
    if (error)
        pm_error("Can't read GIF stream "
                 "right after an image separator; no "
                 "image data follows.  %s", error);

    if (lzwMinCodeSize > MAX_LZW_BITS)
        pm_error("Invalid minimum code size value in image data: %u.  "
                 "Maximum allowable code size in GIF is %u", 
                 lzwMinCodeSize, MAX_LZW_BITS);

    lzwInit(&decomp, ifP, lzwMinCodeSize, cmap.size,
            haveTransColor, transparentIndex, tolerateBadInput);

    issueTransparencyMessage(haveTransColor, transparentIndex, cmap);

    if (useFastPbmRender && !hasGray && ! hasColor && !haveTransColor) {
        if (verbose)
            pm_message("Using fast PBM rendering");
        lzwAdjustForPBM(&decomp, cmap);
    }
    convertRaster(&decomp, cols, rows, cmap, interlace,
                  imageOutFileP, alphaFileP,
                  hasGray, hasColor);

    skipExtraneousData(&decomp);

    lzwTerm(&decomp);
}



static void
warnUserNotSquare(unsigned int const aspectRatio) {

    const char * baseMsg =
        "warning - input pixels are not square, "
        "but we are rendering them as square pixels "
        "in the output";

    if (pm_have_float_format()) {
        float const r = ((float)aspectRatio + 15.0 ) / 64.0;

        pm_message("%s.  To fix the output, run it through "
                   "'pamscale -%cscale %g'",
                   baseMsg,
                   r < 1.0 ? 'x' : 'y',
                   r < 1.0 ? 1.0 / r : r );
    } else
        pm_message("%s", baseMsg);
}



static void
readGifHeader(FILE *             const gifFileP,
              struct GifScreen * const gifScreenP) {
/*----------------------------------------------------------------------------
   Read the GIF stream header off the file *gifFileP, which is present
   positioned to the beginning of a GIF stream.  Return the info from it
   as *gifScreenP.
-----------------------------------------------------------------------------*/
#define GLOBALCOLORMAP  0x80

    unsigned char buf[16];
    char version[4];
    unsigned int cmapSize;
    const char * error;

    readFile(gifFileP, buf, 6, &error);
    if (error)
        pm_error("Error reading magic number.  %s", error);
    
    if (!strneq((char *)buf, "GIF", 3))
        pm_error("File does not contain a GIF stream.  It does not start "
                 "with 'GIF'.");
    
    strncpy(version, (char *)buf + 3, 3);
    version[3] = '\0';
    
    if (verbose)
        pm_message("GIF format version is '%s'", version);
    
    if ((!streq(version, "87a")) && (!streq(version, "89a")))
        pm_error("Bad version number, not '87a' or '89a'" );
    
    readFile(gifFileP, buf, 7, &error);
    if (error)
        pm_error("Failed to read screen descriptor.  %s", error);
    
    gifScreenP->width           = LM_to_uint(buf[0],buf[1]);
    gifScreenP->height          = LM_to_uint(buf[2],buf[3]);
    cmapSize                    = 1 << ((buf[4] & 0x07) + 1);
    gifScreenP->colorResolution = (buf[4] & 0x70 >> 3) + 1;
    gifScreenP->background      = buf[5];
    gifScreenP->aspectRatio     = buf[6];

    if (verbose) {
        pm_message("GIF Width = %u GIF Height = %u "
                   "Pixel aspect ratio = %u (%f:1)",
                   gifScreenP->width, gifScreenP->height, 
                   gifScreenP->aspectRatio, 
                   gifScreenP->aspectRatio == 0 ? 
                   1 : (gifScreenP->aspectRatio + 15) / 64.0);
        pm_message("Global color count = %u   Color Resolution = %u",
                   cmapSize, gifScreenP->colorResolution);
    }           
    if (buf[4] & GLOBALCOLORMAP) {
        gifScreenP->hasGlobalColorMap = true;
        readColorMap(gifFileP, cmapSize, &gifScreenP->colorMap,
                     &gifScreenP->hasGray, &gifScreenP->hasColor);
        if (verbose) {
            pm_message("Global color map %s grays, %s colors", 
                       gifScreenP->hasGray ? "contains" : "doesn't contain",
                       gifScreenP->hasColor ? "contains" : "doesn't contain");
        }
    } else
        gifScreenP->hasGlobalColorMap = false;
    
    if (gifScreenP->aspectRatio != 0 && gifScreenP->aspectRatio != 49)
        warnUserNotSquare(gifScreenP->aspectRatio);

#undef GLOBALCOLORMAP
}



static void
readExtensions(FILE*          const ifP, 
               struct Gif89 * const gif89P,
               bool *         const eodP,
               const char **  const errorP) {
/*----------------------------------------------------------------------------
   Read extension blocks from the GIF stream to which the file *ifP is
   positioned.  Read up through the image separator that begins the
   next image or GIF stream terminator.

   If we encounter EOD (end of GIF stream) before we find an image 
   separator, we return *eodP == TRUE.  Else *eodP == FALSE.

   If we hit end of file before an EOD marker, we fail.
-----------------------------------------------------------------------------*/
    bool imageStart;
    bool eod;

    *errorP = NULL;  /* initial value */

    eod = FALSE;
    imageStart = FALSE;

    /* Read the image descriptor */
    while (!imageStart && !eod && !*errorP) {
        unsigned char c;
        const char * error;

        readFile(ifP, &c, sizeof(c), &error);

        if (error) {
            pm_asprintf(errorP, "File read error where start of image "
                        "descriptor or end of GIF expected.  %s",
                        error);
            pm_strfree(error);
        } else {
            if (c == ';') {         /* GIF terminator */
                eod = TRUE;
            } else if (c == '!') {         /* Extension */
                unsigned char functionCode;
                const char * error;

                readFile(ifP, &functionCode, 1, &error);

                if (error) {
                    pm_asprintf(errorP, "Failed to read function code "
                                "of GIF extension (immediately after the '!' "
                                "extension delimiter) from input.  %s", error);
                    pm_strfree(error);
                } else {
                    doExtension(ifP, functionCode, gif89P);
                }
            } else if (c == ',') 
                imageStart = TRUE;
            else 
                pm_message("Encountered invalid character 0x%02x while "
                           "seeking extension block, ignoring", (int)c);
        }
    }
    *eodP = eod;
}



struct GifImageHeader {
/*----------------------------------------------------------------------------
   Information in the header (first 9 bytes) of a GIF image.
-----------------------------------------------------------------------------*/
    bool hasLocalColormap;
        /* The image has its own color map.  Its size is 'localColorMapSize' */
        /* (If an image does not have its own color map, the image uses the 
           global color map for the GIF stream)
        */
    unsigned int localColorMapSize;
        /* Meaningful only if 'hasLocalColormap' is true. */

    /* Position of the image (max 65535) */
    unsigned int lpos;
    unsigned int tpos;

    /* Dimensions of the image (max 65535) */
    unsigned int cols;
    unsigned int rows;

    bool interlaced;
};



static void
reportImageHeader(struct GifImageHeader const imageHeader) {

    pm_message("reading %u by %u%s GIF image",
               imageHeader.cols, imageHeader.rows,
               imageHeader.interlaced ? " interlaced" : "" );

    if (imageHeader.lpos > 0 || imageHeader.tpos > 0)
        pm_message("  Image left position: %u top position: %u",
                   imageHeader.lpos, imageHeader.tpos);
    
    if (imageHeader.hasLocalColormap)
        pm_message("  Uses local colormap of %u colors",
                   imageHeader.localColorMapSize);
    else
        pm_message("  Uses global colormap");
}



static void
readImageHeader(FILE *                  const ifP,
                struct GifImageHeader * const imageHeaderP) {

#define LOCALCOLORMAP  0x80
#define INTERLACE      0x40

    unsigned char buf[16];
    const char * error;

    readFile(ifP, buf, 9, &error);
    if (error)
        pm_error("couldn't read left/top/width/height.  %s", error);

    imageHeaderP->hasLocalColormap  = !!(buf[8] & LOCALCOLORMAP);
    imageHeaderP->localColorMapSize = 1u << ((buf[8] & 0x07) + 1);
    imageHeaderP->lpos              = LM_to_uint(buf[0], buf[1]);
    imageHeaderP->tpos              = LM_to_uint(buf[2], buf[3]);
    imageHeaderP->cols              = LM_to_uint(buf[4], buf[5]);
    imageHeaderP->rows              = LM_to_uint(buf[6], buf[7]);
    imageHeaderP->interlaced        = !!(buf[8] & INTERLACE);

    if (verbose)
        reportImageHeader(*imageHeaderP);

#undef INTERLACE
#undef LOCALCOLORMAP
}



static void
validateWithinGlobalScreen(struct GifImageHeader const imageHeader,
                           struct GifScreen      const gifScreen) {

    unsigned long int const rpos = imageHeader.lpos + imageHeader.cols;
    unsigned long int const bpos = imageHeader.tpos + imageHeader.rows; 

    if (rpos > gifScreen.width)
        pm_error("Image right end (%lu) is outside global screen: %u x %u",
                 rpos, gifScreen.width, gifScreen.height);
    if (bpos > gifScreen.height)
        pm_error("Image bottom end (%lu) is outside global screen: "
                 "%u x %u",
                 bpos, gifScreen.width, gifScreen.height);
}



static void
skipImageData(FILE * const ifP) {
    unsigned char lzwMinCodeSize;
    const char * error;

    readFile(ifP, &lzwMinCodeSize, sizeof(lzwMinCodeSize), &error);
    if (error) {
        pm_message("Unable to read file to skip image DataBlock.  %s", error);
        pm_strfree(error);
    }
    readThroughEod(ifP);
}



static void
convertImage(FILE *           const ifP, 
             bool             const skipIt, 
             FILE *           const imageoutFileP, 
             FILE *           const alphafileP, 
             struct GifScreen const gifScreen,
             struct Gif89     const gif89,
             bool             const tolerateBadInput) {
/*----------------------------------------------------------------------------
   Read a single GIF image from the current position of file 'ifP'.

   If 'skipIt' is TRUE, don't do anything else.  Otherwise, write the
   image to the current position of files *imageoutFileP and *alphafileP.
   If *alphafileP is NULL, though, don't write any alpha information.
-----------------------------------------------------------------------------*/
    struct GifImageHeader imageHeader;
    GifColorMap localColorMap;
    const GifColorMap * currentColorMapP;
    bool hasGray, hasColor;

    readImageHeader(ifP, &imageHeader);

    validateWithinGlobalScreen(imageHeader, gifScreen);

    if (imageHeader.hasLocalColormap) {
        readColorMap(ifP, imageHeader.localColorMapSize, &localColorMap, 
                     &hasGray, &hasColor);
        currentColorMapP = &localColorMap;
    } else if (gifScreen.hasGlobalColorMap) {
        currentColorMapP = &gifScreen.colorMap;
        hasGray  = gifScreen.hasGray;
        hasColor = gifScreen.hasColor;
    } else {
        pm_error("Invalid GIF: "
                 "Image has no local color map and stream has no global "
                 "color map either.");
    }

    if (!skipIt) {
        readImageData(ifP, imageHeader.cols, imageHeader.rows,
                      *currentColorMapP,
                      imageHeader.interlaced,
                      gif89.haveTransColor, gif89.transparentIndex,
                      imageoutFileP, alphafileP,
                      hasGray, hasColor,
                      tolerateBadInput);
    } else
        skipImageData(ifP);
}



static void
disposeOfReadExtensionsError(const char * const error,
                             bool         const tolerateBadInput,
                             unsigned int const imageSeq,
                             bool *       const eodP) {
    if (error) {
        if (tolerateBadInput)
            pm_message("Error accessing Image %u of stream; no further "
                       "images can be accessed.  %s",
                       imageSeq, error);
        else
            pm_error("Error accessing Image %u of stream.  %s",
                     imageSeq, error);
        pm_strfree(error);
        *eodP = TRUE;
    }
}



static void
convertImages(FILE *       const ifP, 
              bool         const allImages,
              unsigned int const requestedImageSeq, 
              bool         const drainStream,
              FILE *       const imageOutFileP, 
              FILE *       const alphaFileP,
              bool         const tolerateBadInput) {
/*----------------------------------------------------------------------------
   Read a GIF stream from file 'ifP' and write one or more images from
   it as PNM images to file 'imageOutFileP'.  If the images have transparency
   and 'alphafile' is non-NULL, write PGM alpha masks to file 'alphaFileP'.

   'allImages' means Caller wants all the images in the stream.  

   'requestedImageSeq' is meaningful only when 'allImages' is FALSE.  It 
   is the sequence number of the one image Caller wants from the stream,
   with the first image being 0.

   'drainInput' means to read the entire GIF stream, even after
   reading the image Caller asked for.  We read the stream, not just
   the file it's in, so we still recognize certain errors in the GIF
   format in the tail of the stream and there may yet be more stuff in
   the file when we return.
-----------------------------------------------------------------------------*/
    unsigned int imageSeq;
        /* Sequence within GIF stream of image we are currently processing.
           First is 0.
        */
    struct GifScreen gifScreen;
    struct Gif89 gif89;
    bool eod;
        /* We've read through the GIF terminator character */

    /* Set 'gif89' to initial values, to be updated as we encounter the
       relevant extensions in the GIF stream.
    */
    initGif89(&gif89);

    readGifHeader(ifP, &gifScreen);

    for (imageSeq = 0, eod = FALSE;
         !eod && (allImages || imageSeq <= requestedImageSeq || drainStream);
         ++imageSeq) {

        const char * error;

        readExtensions(ifP, &gif89, &eod, &error);

        disposeOfReadExtensionsError(error, tolerateBadInput, imageSeq, &eod);

        if (eod) {
            /* GIF stream ends before image with sequence imageSeq */
            if (!allImages && (imageSeq <= requestedImageSeq))
                pm_error("You requested Image %d, but "
                         "only %d image%s found in GIF stream",
                         requestedImageSeq + 1,
                         imageSeq, imageSeq > 1 ? "s" : "");
        } else {
            if (verbose)
                pm_message("Reading Image Sequence %u", imageSeq);

            convertImage(ifP, !allImages && (imageSeq != requestedImageSeq), 
                         imageOutFileP, alphaFileP, gifScreen, gif89,
                         tolerateBadInput);
        }
    }
}



int
main(int argc, char **argv) {

    struct CmdlineInfo cmdline;
    FILE * ifP;
    FILE * alphaFileP;
    FILE * imageOutFileP;

    pnm_init(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);
    verbose = cmdline.verbose;
    showComment = cmdline.comments;
   
    ifP = pm_openr(cmdline.inputFilespec);

    if (cmdline.alphaFileName == NULL)
        alphaFileP = NULL;
    else
        alphaFileP = pm_openw(cmdline.alphaFileName);

    if (alphaFileP && streq(cmdline.alphaFileName, "-"))
        imageOutFileP = NULL;
    else
        imageOutFileP = stdout;

    convertImages(ifP, cmdline.allImages, cmdline.imageNum, 
                  !cmdline.quitearly, imageOutFileP, alphaFileP,
                  cmdline.repair);

    pm_close(ifP);
    if (imageOutFileP != NULL) 
        pm_close(imageOutFileP);
    if (alphaFileP != NULL)
        pm_close(alphaFileP);

    return 0;
}



