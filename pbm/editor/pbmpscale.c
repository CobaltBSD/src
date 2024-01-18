/* pbmpscale.c - pixel scaling with jagged edge smoothing.
 * AJCD 13/8/90
 */

#include <stdio.h>
#include "pm_c_util.h"
#include "mallocvar.h"
#include "shhopt.h"
#include "pbm.h"
#include "bitarith.h"

#define LEFTBITS pm_byteLeftBits
#define RIGHTBITS pm_byteRightBits

/* Table for translating bit pattern into "corners" flag element */ 

unsigned char const
transTable[512] = {
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04,
     0x00, 0x00, 0x04, 0x04, 0xaa, 0xa2, 0x82, 0x82, 0x8a, 0x82, 0x82, 0x82,
     0xa0, 0xa0, 0x40, 0x40, 0xc0, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0x10, 0x10,
     0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x28, 0x28, 0x00, 0x00, 0x28, 0x28,
     0x0a, 0x03, 0x01, 0x03, 0x0a, 0x03, 0x01, 0x03, 0xff, 0xff, 0xff, 0xff,
     0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x04, 0x04, 0x00, 0x00, 0x04, 0x04, 0xa8, 0xa0, 0xc0, 0xc0,
     0x88, 0x80, 0x80, 0x80, 0xa0, 0xa0, 0xc0, 0xc0, 0x80, 0x80, 0x80, 0x80,
     0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x28, 0x28,
     0x00, 0x00, 0x28, 0x28, 0x0c, 0xff, 0xff, 0xff, 0x08, 0xff, 0xff, 0xff,
     0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
     0xff, 0xff, 0xff, 0xff, 0x01, 0x01, 0x0a, 0x0a, 0x01, 0x01, 0x0a, 0x0a,
     0x28, 0x30, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x10, 0x30, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0xa0, 0xa0, 0x40, 0x40, 0xa0, 0xa0,
     0x82, 0x82, 0xff, 0xff, 0x82, 0x82, 0xff, 0xff, 0x04, 0x00, 0x00, 0x00,
     0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0x01, 0x0a, 0x0a,
     0x01, 0x01, 0x0a, 0x0a, 0x28, 0x30, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
     0x10, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0xa0, 0xa0,
     0x40, 0x40, 0xa0, 0xa0, 0x82, 0x82, 0xff, 0xff, 0x82, 0x82, 0xff, 0xff,
     0x0c, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x04, 0x04, 0x00, 0x00, 0x04, 0x04, 0x2a, 0x22, 0x03, 0x02,
     0x0a, 0x02, 0x03, 0x02, 0x30, 0x20, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
     0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x28, 0x28,
     0x00, 0x00, 0x28, 0x28, 0x0a, 0x02, 0x03, 0x02, 0x0a, 0x02, 0x03, 0x02,
     0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x00, 0x00, 0x04, 0x04,
     0x28, 0x20, 0xff, 0xff, 0x08, 0xff, 0xff, 0xff, 0x30, 0x20, 0xff, 0xff,
     0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x10, 0x10,
     0x00, 0x00, 0x28, 0x28, 0x00, 0x00, 0x28, 0x28, 0x0c, 0xff, 0xff, 0xff,
     0x08, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
     0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0x01, 0x0a, 0x0a,
     0x01, 0x01, 0x0a, 0x0a, 0x28, 0x20, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
     0x30, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0xa0, 0xa0,
     0x40, 0x40, 0xa0, 0xa0, 0x82, 0x82, 0xff, 0xff, 0x82, 0x82, 0xff, 0xff,
     0x04, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
     0x01, 0x01, 0x0a, 0x0a, 0x01, 0x01, 0x0a, 0x0a, 0x28, 0x20, 0x00, 0x00,
     0x08, 0x00, 0x00, 0x00, 0x30, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x40, 0x40, 0xa0, 0xa0, 0x40, 0x40, 0xa0, 0xa0, 0x82, 0x82, 0xff, 0xff,
     0x82, 0x82, 0xff, 0xff, 0x0c, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  };


/* starting positions for corners */
#define NE(f) ((f) & 3)
#define SE(f) (((f) >> 2) & 3)
#define SW(f) (((f) >> 4) & 3)
#define NW(f) (((f) >> 6) & 3)



struct cmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    unsigned int scale;
    const char * inputFileName;  /* File name of input file */
};



static void
parseCommandLine(int argc, const char ** const argv,
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

    MALLOCARRAY_NOFAIL(option_def, 100);

    option_def_index = 0;   /* incremented by OPTENT3 */

    OPTENTINIT;

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = FALSE;  /* We may have parms that are negative numbers */

    pm_optParseOptions3(&argc, (char **)argv, opt, sizeof(opt), 0);
        /* Uses and sets argc, argv, and some of *cmdlineP and others. */

    if (argc-1 < 1)
        pm_error("You must specify the scale factor as an argument");
    else {
        int const scale = atoi(argv[1]);
        if (scale < 1)
            pm_error("Scale argument must be at least one.  You specified %d",
                     scale);
        else
            cmdlineP->scale = scale;

        if (argc-1 < 2)
            cmdlineP->inputFileName = "-";
        else {
            cmdlineP->inputFileName = argv[2];

            if (argc-1 > 2)
                pm_error("Too many arguments.  The only arguments are the "
                         "scale factor and optional input file name.  "
                         "You specified %u", argc-1);
        }
    }
    free(option_def);
}



static void
validateComputableDimensions(unsigned int const width,
                             unsigned int const height,
                             unsigned int const scaleFactor) {
/*----------------------------------------------------------------------------
   Make sure that multiplication for output image width and height do not
   overflow.
   See validateComputetableSize() in libpam.c
   and pbm_readpbminitrest() in libpbm2.c
-----------------------------------------------------------------------------*/
    unsigned int const maxWidthHeight = INT_MAX - 10;
    unsigned int const maxScaleFactor = maxWidthHeight / MAX(height, width);

    if (scaleFactor > maxScaleFactor)
       pm_error("Scale factor '%u' too large.  "
                "The maximum for this %u x %u input image is %u.",
                scaleFactor, width, height, maxScaleFactor);
}



static void
writeBitSpan(unsigned char * const packedBitrow,
             unsigned int    const cols,
             unsigned int    const offset,
             int             const color) {
/*----------------------------------------------------------------------------
   Write white (color="0") or black (="1") bits into packedBitrow[],
   starting at 'offset', length 'cols'.
-----------------------------------------------------------------------------*/
    unsigned char * const dest     = &packedBitrow[offset/8];
    unsigned int    const rs       = offset % 8;
    unsigned int    const trs      = (cols + rs) % 8;
    unsigned int    const colBytes = pbm_packed_bytes(cols + rs);
    unsigned int    const last     = colBytes - 1;

    unsigned char const origHead = dest[0];
    unsigned char const origEnd =  dest[last];

    unsigned int i;

    for (i = 0; i < colBytes; ++i)
        dest[i] = color * 0xff;

    if (rs > 0)
        dest[0] = LEFTBITS(origHead, rs) | RIGHTBITS(dest[0], 8-rs);

    if (trs > 0)
        dest[last] = LEFTBITS(dest[last], trs) | RIGHTBITS(origEnd, 8-trs);
}



static void
setFlags(const bit *     const prevrow,
         const bit *     const thisrow,
         const bit *     const nextrow,
         unsigned char * const flags,
         unsigned int    const cols ) {
/*----------------------------------------------------------------------------
   Scan one row, examining the row above and row below, and determine 
   whether there are "corners" for each pixel.  Feed a 9 bit sample into 
   pre-calculated array transTable[512] to calculate all four corner statuses
   at once.

   Bits in the 9 bit sample represent the current pixel and neighbors:
       NW : N : NE : W: Current : E : SW : S : SE

   Bits in flag are divided into 4 fields of width 2 each:
       NW : SW : SE : NE

   Code 0xff is an exception.  It is a variation of 0x00.
     0x00 : no corners, no color change from above row (Current == N)
     0xff : no corners, but color changed (Current != N)

   Most transTable[] entries are "no corners".
   0x00 appears 180 times, 0xff 109 times.
-----------------------------------------------------------------------------*/

#if 0
    /* The following code is from the previous version, which examined
       the corners one by one:
    */

    /* list of corner patterns; bit 7 is current color, bits 0-6 are squares
       around (excluding square behind), going clockwise.
       The high byte of the patterns is a mask, which determines which bits are
       not ignored.
    */
    uint16_t const patterns[] 
        = { 0x0000,   0xd555,            /* no corner */
            0x0001,   0xffc1, 0xd514,    /* normal corner */
            0x0002,   0xd554, 0xd515, 0xbea2, 0xdfc0, 0xfd81, 0xfd80, 0xdf80,
            /* reduced corners */
            0x0003,   0xbfa1, 0xfec2 };  /* reduced if cutoff > 1 */

    /*
      For example, the NE corner is examined with the following 8 bit sample:
      Current : W : NW : N : NE : E : SE : S
      (SW is the "square behind") 
      */
#endif

    uint32_t prevrow24, thisrow24, nextrow24;
    unsigned int col;

    /* higher bits are set to 0 */
    prevrow24 = prevrow[0];  /* initial value */
    thisrow24 = thisrow[0];  /* initial value */
    nextrow24 = nextrow[0];  /* initial value */

    for (col = 0; col < cols; ++col) {
        unsigned int const col8   = col / 8;
        unsigned int const offset = col % 8;

        unsigned int sample;

        if (offset == 0) {
            prevrow24 = prevrow24 << 8 | prevrow[col8 + 1];
            thisrow24 = thisrow24 << 8 | thisrow[col8 + 1];
            nextrow24 = nextrow24 << 8 | nextrow[col8 + 1];
        }

        sample = ( ( prevrow24 >> ( 8 -offset) ) & 0x01c0 )
            | ( ( thisrow24 >> (11 -offset) ) & 0x0038 )
            | ( ( nextrow24 >> (14 -offset) ) & 0x0007 );
        
        flags[col] =  transTable[sample];
    }
}



static void
expandRow(const bit *     const thisrow,
          const bit *     const prevrow,
          bit *           const outrow,
          unsigned char * const flags,
          unsigned int    const cols,
          int             const scale,
          int             const cutoff,
          int             const ucutoff) {
/*----------------------------------------------------------------------------
  Process one row, using flags array as reference.  If pixel has no corners
  output a NxN square of the given color, otherwise output with the 
  specified corner area(s) clipped off.
-----------------------------------------------------------------------------*/
    unsigned int const outcols = cols * scale;

    unsigned int i;
    unsigned int col;
    
    for (i = 0; i < scale; ++i) {
        int const zone = (i > ucutoff) - (i < cutoff);
        int const cut1 =
            (zone < 0) ? (cutoff - i) : (zone > 0) ? (i - ucutoff) : 0;

        unsigned int outcol;
        int cut[4];

        outcol = 0; /* initial value */

        cut[0] = 0;
        cut[1] = cut1;
        cut[2] = cut1 ? cut1 - 1 : 0;
        cut[3] = (cut1 && cutoff > 1) ? cut1 - 1 : cut1;
      
        for (col = 0; col < cols; ++col) {
            unsigned int const col8 = col / 8;
            unsigned int const offset = col % 8;
            int const pix = (thisrow[col8] >> (7-offset) ) & 0x01;
            int const flag = flags[col];

            int cutl, cutr;

            if (flag == 0x00) {
                /* There are no corners, no color change */
                outcol += scale;
            } else { 
                switch (zone) {
                case -1:
                    if (i==0 && flag == 0xff) {
                        /* No corners, color changed */ 
                        cutl = cutr = 0;
                        flags[col] = 0x00;
                            /* Use above skip procedure next cycle */
                    } else {
                        cutl = cut[NW(flag)];
                        cutr = cut[NE(flag)];
                    }
                    break;
                case 0:
                    cutl = cutr = 0;
                    break ;
                case 1:
                    cutl = cut[SW(flag)];
                    cutr = cut[SE(flag)];
                    break;
                }
                
                if (cutl > 0) {
                    writeBitSpan(outrow, cutl, outcol, !pix);
                    outcol += cutl;
                }
                {
                    unsigned int const center = scale - cutl - cutr;

                    if (center > 0) {
                        writeBitSpan(outrow, center, outcol,  pix);
                        outcol += center;
                    }
                }
                if (cutr > 0) {
                    writeBitSpan(outrow, cutr, outcol, !pix);
                    outcol += cutr;
                }
            }
        }
        pbm_writepbmrow_packed(stdout, outrow, outcols, 0) ;
    }
}



int
main(int argc, const char ** argv) {

    struct cmdlineInfo cmdline;
    FILE * ifP;
    bit ** buffer;
    bit * prevrow;
    bit * thisrow;
    bit * nextrow;
    bit * edgerow;
    bit * outrow;
    unsigned int row;
    unsigned int i;
    int cols, rows;
    int format;
    unsigned int outcols;
    unsigned int outrows;
    int cutoff;
    int ucutoff ;
    unsigned char * flags;  /* malloc'ed */

    pm_proginit(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    ifP = pm_openr(cmdline.inputFileName);

    pbm_readpbminit(ifP, &cols, &rows, &format) ;

    validateComputableDimensions(cols, rows, cmdline.scale); 

    outcols = cols * cmdline.scale;
    outrows = rows * cmdline.scale; 

    /* Initialize input buffers.
       We add a margin of 8 bits on the right of the three rows.

       On the top and bottom of the image we place an imaginary blank row
       ("edgerow") to facilitate the process.
    */

    buffer  = pbm_allocarray_packed(cols + 8, 3);
    edgerow = pbm_allocrow_packed(cols + 8);

    for (i = 0; i < pbm_packed_bytes(cols + 8); ++i)
        edgerow[i] = 0x00;

    /* Add blank bytes at right edges */ 
    for (i = 0; i < 3; ++i)
        buffer[i][pbm_packed_bytes(cols + 8) - 1] = 0x00;

    thisrow = edgerow;
    nextrow = buffer[0];

    /* Read the top line into nextrow and clean the right end. */

    pbm_readpbmrow_packed(ifP, nextrow, cols, format);
    pbm_cleanrowend_packed(nextrow, cols);

    outrow = pbm_allocrow_packed(outcols);
    for (i = 0; i < pbm_packed_bytes(outcols); ++i)
        outrow[i] = 0x00;

    MALLOCARRAY(flags, cols);
    if (flags == NULL)
        pm_error("Couldn't get memory for %u columns of flags", cols);

    pbm_writepbminit(stdout, outcols, outrows, 0) ;

    cutoff = cmdline.scale / 2;
    ucutoff = cmdline.scale - 1 - cutoff;

    for (row = 0; row < rows; ++row) {
        prevrow = thisrow;  /* Slide up the input row window */
        thisrow = nextrow;
        if (row < rows - 1) {
            nextrow = buffer[(row + 1) % 3];
            /* We take the address directly instead of shuffling the rows.
               This provision is for proper handling of the initial edgerow.
            */
            pbm_readpbmrow_packed(ifP, nextrow, cols, format);
            pbm_cleanrowend_packed(nextrow, cols);
        } else
            /* Bottom of image.  */
            nextrow = edgerow;

        setFlags(prevrow, thisrow, nextrow, flags, cols);

        expandRow(thisrow, prevrow, outrow, flags, cols, cmdline.scale,
                  cutoff, ucutoff);
    }
    pbm_freearray(buffer,3);
    pbm_freerow(edgerow);
    pbm_freerow(outrow);
    free (flags);
    pm_close(ifP);
    return 0;
}
