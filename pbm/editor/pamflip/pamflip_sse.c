/*=============================================================================
                                   pamflip_sse.c
===============================================================================
  This is part of the Pamflip program.  It contains code that exploits
  the SSE facility of some CPUs.

  This code was originally written by Akira Urushibata ("Douso") in 2010 and is
  contributed to the public domain by all authors.

  The author makes the following request (which is not a reservation of legal
  rights): Please study the code and make adjustments to meet specific needs.
  This part is critical to performance.  I have seen code copied from
  elsewhere poorly implemented.  A lot of work goes into the development of
  free software.  It is sad to see derivative work which fails to reach its
  potential.  Please put a comment in the code so people will know where it
  came from.

=============================================================================*/

#include <assert.h>

#include "pm_config.h"
#include "pm_c_util.h"
#include "mallocvar.h"
#include "pam.h"

#include "config.h"  /* Defines SSE_PBM_XY_FLIP */
#include "flip.h"

#include "pamflip_sse.h"

/* Note that WANT_SSE implies the user expects SSE to be available
   (i.e. <emmintrin.h> exists).
*/

#if SSE_PBM_XY_FLIP

/*----------------------------------------------------------------------------
   This is a specialized routine for row-for-column PBM transformations.
   (-cw, -ccw, -xy).  It requires GCC (>= v. 4.2.0) and SSE2. 

   In each cycle, we read sixteen rows from the input.  We process this band
   left to right in blocks 8 pixels wide.  We use the SSE2 instruction
   pmovmskb128, which reports the MSB of each byte in a 16 byte array, for
   fast processing.  We place the 8x16 block into a 16 byte array, and
   pmovmskb128 reports the 16 pixels on the left edge in one instruction
   execution.  pslldi128 shifts the array contents leftward.

   The following routines can write both in both directions (left and right)
   into the output rows.  They do this by controlling the vertical stacking
   order when they make the 8x16 blocks.

   We do all transposition in 8x16 block units, adding padding to
   the 8 row input buffer and the output plane raster as necessary.
   doPartialBlockTop() or doPartialBlockBottom() handles the partial
   input band.  This part can come from either the top or bottom of the
   vertical input column, but always goes to the right end of the output
   rows.

   As an enhancement, we clear the output raster to zero (=white) in the
   beginning and flip only the 8x16 blocks that contain non-zero bits (=any
   amount of black pixels).  When we add padding to the edges, we initialize
   it all to zero to prevent unnecessary transpositions.  Because most
   real-world documents are largely white, this saves much execution time.  If
   you are porting this code to an environment in which non-zero bits are the
   majority, for example, BMP where zero means black, you should seriously
   consider modifying this.

   All instructions unique to GCC/SSE are in transpose16Bitrows().
   It is possible to write a non-SSE version by providing a generic
   version of transpose16Bitrows() or one tuned for a specific
   architecture.  Use 8x8 blocks to avoid endian issues.
 
   Further enhancement should be possible by employing wider bands,
   larger blocks as wider SIMD registers become available.  Clearing
   the white parts after instead of before transposition is also a
   possibility.
-----------------------------------------------------------------------------*/

#include <emmintrin.h>

typedef char v16qi __attribute__ ((vector_size (16)));
typedef int  v4di  __attribute__ ((vector_size (16)));

/* Beware when making modifications to code which involve SSE.
   This is a sensitive part of GCC.  Different compiler versions
   respond differently to trivial matters such as the difference
   between above v16qi, v4di and a union defined for handling both.
   What can be placed into a register is another issue.  Some
   compilers issue warnings, others abort with error.

   A char array cannot be loaded into v16qi by casting.  A vector
   variable must be vector from the beginning.

   Changes for your local system are okay, but if you intend to
   publish them, please specify the compiler version you used.

   This code has been tested on gcc versions 4.2.0, 4.2.4, 4.3.2,
   4.4.3, 4.4.4, 4.5.0, 4.5.2, 4.6.0 and 4.6.1 clang versions
   3.0, 3.2, 3.3.

   We use SSE instructions in "_mm_" form in favor of "__builtin_".
   In GCC the "__builtin_" form is documented but "_mm_" is not.
   Former versions of this source file used "__builtin_".  This was
   changed to make possible compilation with clang.

   _mm_slli_epi32 : __builtin_ia32_pslldi128
   _mm_cmpeq_epi8 : __builtin_ia32_pcmpeqb128
   _mm_movemask_epi8 : __builtin_ia32_pmovmskb128

   The conversion requires <emmintrin.h> .

*/



static void
transpose16Bitrows(unsigned int const cols,
                   unsigned int const rows,
                   const bit *  const block[16],
                   uint16_t **  const outplane,
                   unsigned int const outcol16) {
/*--------------------------------------------------------------------------
  Convert input rows to output columns.  Works in units of 8x16.

  Uses pre-calculated pointers ( block[i][col8] ) instead of
  (xdir > 0) ? (i & 0x08) + 7 - (i & 0x07) : (24 - rows % 16 +i) % 16
  for efficiency.

  We load the block directly into a register.  (using a union like:

       union V16 {
          v16qi v;
          unsigned char i[16];
       };
  )

  gcc (v. 4.2, 4.4) sees the suffix [x] of v16.i[x] and apparently decides
  that the variable has to be addressable and therefore needs to be placed
  into memory.)
---------------------------------------------------------------------------*/
    unsigned int col;
    register v16qi zero128;   /* 16 bytes of zero, in a SSE register */

    zero128 = zero128 ^ zero128;

    for (col = 0; col < cols; col += 8) {
        unsigned int const col8 = col / 8;

        register v16qi vReg = {
            block[0][col8],  block[1][col8],
            block[2][col8],  block[3][col8],  
            block[4][col8],  block[5][col8],
            block[6][col8],  block[7][col8],
            block[8][col8],  block[9][col8],
            block[10][col8], block[11][col8],
            block[12][col8], block[13][col8],
            block[14][col8], block[15][col8] };

        register __m128i const compare =
            _mm_cmpeq_epi8((__m128i)vReg, (__m128i)zero128);

        if (_mm_movemask_epi8(compare) != 0xffff) {

            /* There is some black content in this block; write to outplane */
            
            unsigned int outrow;
            unsigned int i;

            outrow = col;  /* initial value */

            for (i = 0; i < 7; ++i) {
                /* GCC (>=4.2) automatically unrolls this loop */  
                outplane[outrow++][outcol16] =
                    _mm_movemask_epi8((__m128i)vReg);
                vReg = (v16qi)_mm_slli_epi32((__m128i)vReg, 1);
            }
            outplane[outrow][outcol16] = _mm_movemask_epi8((__m128i)vReg);
        } else {
            /* The block is completely white; skip. */
        }
    }
}



static void
analyzeBlock(const struct pam * const inpamP,
             bit **             const inrow,
             int                const xdir,
             const bit **       const block,
             const bit **       const blockPartial,
             unsigned int *     const topOfFullBlockP,
             unsigned int *     const outcol16P) {
/*--------------------------------------------------------------------------
  Set up block[] pointer array.  Provide for both directions and the two
  "twists" brought about by Intel byte ordering which occur when:
    (1) 16 bytes are loaded to a SSE register
    (2) 16 bits are written to memory.
 
  If 'rows' is not a multiple of 8, a partial input band appears at one edge.
  Set *topOfFullBlockP accordingly.  blockPartial[] is an adjusted "block" for
  this partial band, brought up to a size of 8 rows.  The extra pointers point
  to a single row which doPartialBlockTop() and doPartialBlockBottom() clear
  to white.
---------------------------------------------------------------------------*/
    if (xdir > 0){
        /* Write output columns left to right */
        unsigned int i;
        for (i = 0; i < 16; ++i){
            unsigned int const index = (i & 0x8) + 7 - (i & 0x7);
            /* Absorb little-endian "twists" */
            block[i] = inrow[index];
            blockPartial[i] = index < inpamP->height%16 ? block[i] : inrow[15];
        }
        *topOfFullBlockP = 0;
        *outcol16P = 0;
    } else {
        /* Write output columns right to left */
        unsigned int i;
        for (i = 0; i < 16; ++i){
            unsigned int const index = ((i & 0x8) ^ 0x8) + (i & 0x7);
            /* Absorb little-endian "twists" */
            block[i]= inrow[index];
            blockPartial[i] = index < (16-inpamP->height%16)
                ? inrow[0]
                : block[i];
        }
        *topOfFullBlockP = inpamP->height % 16;
    
        if (inpamP->height >= 16) {
            *outcol16P = inpamP->height/16 - 1;
        } else
            *outcol16P = 0;
    }
}



static void
doPartialBlockTop(const struct pam * const inpamP,
                  bit **             const inrow,
                  const bit *        const blockPartial[16],
                  unsigned int       const topOfFullBlock,
                  uint16_t **        const outplane) {
    
    if (topOfFullBlock > 0) {
        unsigned int colChar, row;
        unsigned int pad = 16 - topOfFullBlock;

        for (colChar=0; colChar < pbm_packed_bytes(inpamP->width); ++colChar)
            inrow[0][colChar] = 0x00;

        for (row = 0; row < topOfFullBlock; ++row){
            pbm_readpbmrow_packed(inpamP->file, inrow[row+pad],
                                  inpamP->width, inpamP->format);
            if (inpamP->width % 8 > 0){
                /* Clear partial byte at end of input row */
                int const lastByte = pbm_packed_bytes(inpamP->width) -1;

                inrow[row+pad][lastByte] >>= (8 - inpamP->width % 8);
                inrow[row+pad][lastByte] <<= (8 - inpamP->width % 8);
            }
        }

        transpose16Bitrows(inpamP->width, inpamP->height, blockPartial,
                           outplane, inpamP->height /16);
            /* Transpose partial rows on top of input.  Place on right edge of
               output.
            */ 
    }
}



static void
doFullBlocks(const struct pam * const inpamP,
             bit **             const inrow,
             int                const xdir,
             const bit *        const block[16],
             unsigned int       const topOfFullBlock,
             unsigned int       const initOutcol16,
             uint16_t **        const outplane) {

    unsigned int row;
    unsigned int outcol16;
    unsigned int modrow;
    /* Number of current row within buffer */

    for (row = topOfFullBlock, outcol16 = initOutcol16, modrow = 0;
         row < inpamP->height;
         ++row) {

        pbm_readpbmrow_packed(inpamP->file, inrow[modrow],
                              inpamP->width, inpamP->format);
        if (inpamP->width % 8 > 0) {
            /* Clear partial byte at end of input row */
            int const lastByte = pbm_packed_bytes(inpamP->width) - 1;
            inrow[modrow][lastByte] >>= (8 - inpamP->width % 8);
            inrow[modrow][lastByte] <<= (8 - inpamP->width % 8);
        }

        ++modrow;
        if (modrow == 16) {
            /* 16 row buffer is full.  Transpose. */
            modrow = 0; 

            transpose16Bitrows(inpamP->width, inpamP->height,
                               block, outplane, outcol16);
            outcol16 += xdir;
        }
    }
}



static void
doPartialBlockBottom(const struct pam * const inpamP,
                     bit **             const inrow,
                     int                const xdir,
                     const bit *        const blockPartial[16],
                     uint16_t **        const outplane) {
    
    if (xdir > 0 && inpamP->height % 16 > 0) {
        unsigned int colChar;

        for (colChar=0; colChar < pbm_packed_bytes(inpamP->width); ++colChar)
            inrow[15][colChar] = 0x00;

        transpose16Bitrows(inpamP->width, inpamP->height, blockPartial,
                           outplane, inpamP->height/16);
            /* Transpose partial rows on bottom of input.  Place on right edge
               of output.
            */ 
    }
}



static void
writeOut(const struct pam * const outpamP,
         uint16_t **        const outplane,
         int                const ydir) {
             
    unsigned int row;

    for (row = 0; row < outpamP->height; ++row) {
        unsigned int const outrow = (ydir > 0) ?
            row :
            outpamP->height - row - 1;  /* reverse order */

        pbm_writepbmrow_packed(stdout, (bit *)outplane[outrow],
                               outpamP->width, 0);
    }
}


static void
clearOutplane(const struct pam * const outpamP,
              uint16_t **        const outplane) { 
    
    unsigned int row;
    
    for (row = 0; row < outpamP->height; ++row) {
        unsigned int col16;  /* column divided by 16 */
        for (col16 = 0; col16 < (outpamP->width + 15)/16; ++col16)
            outplane[row][col16] = 0x0000;
    }
} 



void
pamflip_transformRowsToColumnsPbmSse(const struct pam * const inpamP,
                                     const struct pam * const outpamP,
                                     struct xformCore const xformCore) { 
/*----------------------------------------------------------------------------
  This is a specialized routine for row-for-column PBM transformations.
  (-cw, -ccw, -xy).
-----------------------------------------------------------------------------*/
    int const xdir = xformCore.c;
        /* Input top  => output left (+1)/ right (-1)  */
    int const ydir = xformCore.b;
        /* Input left => output top  (+1)/ bottom (-1) */
    int const blocksPerRow = ((unsigned int) outpamP->width + 15) /16;

    bit ** inrow;
    uint16_t ** outplane;
    const bit * block[16];
    const bit * blockPartial[16];
    unsigned int topOfFullBlock;
    unsigned int outcol16;

    inrow = pbm_allocarray_packed( inpamP->width, 16);
    MALLOCARRAY2(outplane, outpamP->height + 7, blocksPerRow);
    if (outplane == NULL)
        pm_error("Could not allocate %u x %u array of 16 bit units",
                 blocksPerRow, outpamP->height + 7);

    /* We write to the output array in 16 bit units.  Add margin. */  

    clearOutplane(outpamP, outplane);

    analyzeBlock(inpamP, inrow, xdir, block, blockPartial, 
                 &topOfFullBlock, &outcol16);

    doPartialBlockTop(inpamP, inrow, blockPartial, topOfFullBlock, outplane);

    doFullBlocks(inpamP, inrow, xdir, block,
                 topOfFullBlock, outcol16, outplane);

    doPartialBlockBottom(inpamP, inrow, xdir, blockPartial, outplane);

    writeOut(outpamP, outplane, ydir);

    pbm_freearray(outplane, outpamP->height + 7);
    pbm_freearray(inrow, 16);
}
#else  /* WANT_SSE */

void
pamflip_transformRowsToColumnsPbmSse(const struct pam * const inpamP,
                                     const struct pam * const outpamP,
                                     struct xformCore   const xformCore) { 

    /* Nobody is supposed to call this */
    assert(false);
}
#endif 
