/*=============================================================================
                                  runlength.c
===============================================================================
  "Packbits" run-length encoding and variants.

  Copyright (C) 2015 by Akira Urushibata (afu@wta.att.ne.jp).

  Permission to use, copy, modify, and distribute this software and its
  documentation for any purpose and without fee is hereby granted, provided
  that the above copyright notice appear in all copies and that both that
  copyright notice and this permission notice appear in supporting
  documentation.  This software is provided "as is" without express or implied
  warranty.

  Functions pm_rlenc_byte() and pm_rlenc_word() are based on algorithm
  originally by Robert A. Knop (rknop@mop.caltech.edu).

  Those who wish to incorporate the code herein into their own programs are
  strongly discouraged from removing the comments within borders consisting
  of "+" marks.  This is a practical consideration based on code inspection
  and bug fixes of various programs which use run-length compression.

===============================================================================

  Packbits is a simple yet efficient simple run-length compression method.  It
  has a provision for uncompressed sequences which allows efficient encoding
  of noisy input.

  A survey of netpbm source code in 2015 found Packbits encoding in the
  following Netpbm programs: pbmtoescp2, pbmtomacp, pnmtopalm, pnmtopclxl,
  pnmtops, ppmtoilbm and ppmtopjxl.
 
  Packbits is an option in the TIFF standard; pamtotiff can generate TIFF
  images that use Packbits compression, but does so via code in the TIFF
  library (not part of Netpbm).

  Variants of Packbits are employed in pnmtosgi,  pamtopdbimg,  pbmtoppa
  and  pbmtogo.

  All the above programs formerly did the same compression through different
  code.  This redundancy bloated the Netpbm package and made maintenance
  difficult.  This maintenance difficulty surfaced as an issue when tests with
  valgrind revealed multiple memory-related problems in the above programs.
  Indeed, just determining which programs do this compression by this method
  was not simple because of differences in terminology.  "Packbits" is often
  called "run length encoding."  In ppmtoilbm the name is "byterun1."

  Today, all Netpbm programs that do Packbits compression use the facilities
  in this file for it.
=============================================================================*/

#include <string.h>

#include "pm.h"
#include "pm_c_util.h"
#include "runlength.h"
#include "mallocvar.h"



static const char * const errorUndefinedMode =
    "Internal error: compression mode %u not supported";



/*-----------------------------------------------------------------------------
   Run length encoding

   In this simple run-length encoding scheme, compressed and uncompressed
   strings follow a single index or "flag" byte N.  There are several
   variations, differing in the format of the flag byte, maximum string length
   and element size (byte or word).
   
   In the most widely used version, Packbits, the meaning of the flag byte N
   is defined as follows:

    0-127 means the next N+1 bytes are uncompressed.
    129-255 means the next byte is to be repeated 257-N times.
    128 is not used.

   The name "Packbits" is misleading: it packs bytes, not bits.
-----------------------------------------------------------------------------*/



void
pm_rlenc_compressbyte(const unsigned char * const inbuf,
                      unsigned char       * const outbuf,
                      enum pm_RleMode       const mode,
                      size_t                const inSize,
                      size_t              * const outputSizeP) {
/*-----------------------------------------------------------------------------
  Compress the contents of input buffer 'inbuf' with Packbits encoding into
  output buffer 'outbuf'.  'inSize' is the number of bytes of data in 'inbuf'.
  Return as *outputSizeP the number of bytes we put in 'outbuf'.

  'outbuf' should be allocated with pm_rlenc_allocoutbuf().

  Always encode 3-byte repeat sequences.

  Encode 2-byte repeat sequences only when they are at the start of the block.
  This ensures that the output is never unnecessary bloated.

  Original algorithm by Robert A. Knop (rknop@mop.caltech.edu)
-----------------------------------------------------------------------------*/
    unsigned int const maxRun = 128;

    size_t inCurs, outCurs;

    if (mode != PM_RLE_PACKBITS)
        pm_error(errorUndefinedMode, mode);

    for (inCurs = 0, outCurs = 0; inCurs < inSize; ) {
        if ((inCurs < inSize - 1) && (inbuf[inCurs] == inbuf[inCurs+1])) {
            /*Begin replicate run*/
            size_t const hold = inCurs;
            size_t count;
            for (count = 0;
                 inCurs < inSize &&
                     inbuf[inCurs] == inbuf[hold] &&
                     count < maxRun; 
                 ++inCurs, ++count)
                ;

            outbuf[outCurs++] = (unsigned char)(257 - count);
            outbuf[outCurs++] = inbuf[hold];
        } else {
            /*Do a non-run*/
            size_t const hold = outCurs;
            size_t count;
            ++outCurs;
            count = 0;
            while(((inCurs + 2 >= inSize) && (inCurs < inSize) ) || 
                  ((inCurs + 2 <  inSize) &&
                   ((inbuf[inCurs] != inbuf[inCurs+1]  )
                    || (inbuf[inCurs] != inbuf[inCurs+2]  ) ) )    ) {
                outbuf[outCurs++] = inbuf[inCurs++];
                if (++count >= 128)
                    break;
            }
            outbuf[hold] = (unsigned char)(count - 1);
        }
    }
    *outputSizeP = outCurs;
}



static void
setFlagElement(void            * const outP,
               enum pm_RleMode   const mode,
               bool              const isRepeatRun,
               size_t            const count) {
/*---------------------------------------------------------------------------
  Write the flag byte or word at specified point in the output buffer.
-----------------------------------------------------------------------------*/
    switch (mode) {
    case PM_RLE_SGI16:
        * (uint16_t *) outP =  (isRepeatRun ? 0x00 : 0x80 ) | count;
        break;
    case PM_RLE_PALM16:
        * (unsigned char *) outP = isRepeatRun ?
            (unsigned char)(257 - count) : (unsigned char) (count - 1);
        break;
    default:
        pm_error(errorUndefinedMode, mode);
    }
}



void
pm_rlenc_compressword(const uint16_t   * const inbuf,
                      unsigned char *    const outbuf,
                      enum pm_RleMode    const mode,
                      size_t             const inSize,
                      size_t           * const outputSizeP) {
/*---------------------------------------------------------------------------
   Similar to pm_rlenc_byte(), but this works with two-byte elements.  The
   difference between SGI16 and PALM16 is the size of the flag.  SGI16 : 16
   bits; PALM16 : 8 bits

   'inSize' is a number of words,but *outputSizeP is a number of bytes.
-----------------------------------------------------------------------------*/
    size_t inCurs, outCurs;
    size_t flagSz;
    unsigned int maxRunSz;

    switch (mode) {
    case PM_RLE_SGI16:
        flagSz = 2;
        maxRunSz = 127;
        break;
    case PM_RLE_PALM16:
        flagSz = 1;
        maxRunSz = 128;
        break;
    default:
        pm_error(errorUndefinedMode, mode);
    }

    for (inCurs = 0, outCurs = 0; inCurs < inSize; ) {
        if ((inCurs < inSize - 1) && (inbuf[inCurs] == inbuf[inCurs+1])) {
            uint16_t const runValue = inbuf[inCurs];
            size_t count;
            /* Do a run of 'runValue' values */
            for (count = 0;
                 count < maxRunSz &&
                     inCurs < inSize &&
                     inbuf[inCurs] == runValue;
                 ++inCurs, ++count)
                ;
            setFlagElement(&outbuf[outCurs], mode, TRUE, count);
            outCurs += flagSz;
            * (uint16_t *) &outbuf[outCurs] = runValue;
            outCurs += 2;
        } else {
            /*Do a non run*/
            size_t const nonrunStart = inCurs;
            size_t count;
            count = 0;
            while (count < maxRunSz &&
                   ((inCurs + 2 >= inSize && inCurs < inSize) ||
                    (inCurs + 2 <  inSize &&
                     (inbuf[inCurs] != inbuf[inCurs+1]
                      || inbuf[inCurs] != inbuf[inCurs+2])))) {
                ++inCurs;
                ++count;
            }
            setFlagElement(&outbuf[outCurs], mode, FALSE, count);
            outCurs += flagSz;
            memcpy(&outbuf[outCurs], &inbuf[nonrunStart], count * 2);
            outCurs += count * 2;
        }
    }
    
    if (mode == PM_RLE_SGI16) {
        * (uint16_t *) &outbuf[outCurs] = 0;     /* terminator */
        outCurs += 2;
    }

    *outputSizeP = outCurs;
}



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   Worst case output size

   The term "worst-case output size" can mean one of two things depending on
   whether the encoder is efficient or not.

   Sub-optimal encoder: the output size can be up to twice the input size.
   This happens (or one may rather say "is achieved by a determined encoder")
   when input is split into one-byte blocks.

   Efficient encoder: the output is larger than the input by the minimum
   number of flag bytes.  The worst case happens when there are no repeat
   sequences in the input.

   The key to an efficient encoder is correct handling of short, inefficient
   sequences.  The following algorithm (not actually used in this file)
   describes the idea.

   A run is a maximal set of two or more consecutive identical values in the
   input.  A nonrun is a maximal set of values in which every value is
   different from its neighbors.

   A compressed block is one that encodes a sequence of identical values
   (which could be a run or just part of a run) as a value and a count.
   count.  An uncompressed block is one that encodes a sequence of any values
   by listing the values individually.

   Start by encoding the entire input as uncompressed blocks.  Seek runs that
   can be encoded with compressed blocks, but only if doing so doesn't make
   the output larger.

   Criteria to avoid bloat:

     - Overhead for a single uncompressed block: 1 byte.

     - Overhead for one uncompressed block and a compressed block: 2 bytes.

     - Overhead for two uncompressed blocks and a compressed block: 3 bytes.

     - New blocks at the edge of any existing block add 1 byte of overhead.
       New blocks in the middle of existing blocks add 2 bytes of overhead.

     - Whenever savings are larger than the added overhead, encode the run
       as a compressed block.
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



size_t
pm_rlenc_maxbytes(size_t          const inSize,  /* number of elements */
                  enum pm_RleMode const mode) {
/*---------------------------------------------------------------------------
   Calculate worst case output size from input size and encoding mode.

   'inSize' counts the number of elements, not bytes: input size is (2 *
   inSize) bytes if input is an array of 16-bit words.

   Return value is the maximum possible output size in bytes regardless of
   type of input.

   Abort the program if the maximum possible output size is greater than
   INT_MAX.
-----------------------------------------------------------------------------*/
   /* The upper limit could be raised above INT_MAX, but no program needs that
      today.
   */
    size_t blockSize;
    size_t flagSize;
    size_t itemSize;
    size_t miscSize;
    size_t overhead;

    switch (mode) {
    case PM_RLE_PACKBITS:
        blockSize = 128; flagSize = 1; itemSize = 1; miscSize = 0; break;
    case PM_RLE_SGI8:
        blockSize = 127; flagSize = 1; itemSize = 1; miscSize = 0; break;
    case PM_RLE_GRAPHON:  case PM_RLE_PPA:
        blockSize =  64; flagSize = 1; itemSize = 1; miscSize = 0; break;
    case PM_RLE_SGI16:
        blockSize = 127; flagSize = 2; itemSize = 2; miscSize = 2; break;
    case PM_RLE_PALM16:
        blockSize = 128; flagSize = 1; itemSize = 2; miscSize = 0; break;
    default:
        pm_error(errorUndefinedMode, mode);
    }
    
    overhead = miscSize +
        (inSize / blockSize + (inSize % blockSize > 0 ? 1 : 0) ) * flagSize;

    if (inSize > INT_MAX / itemSize ||
        inSize * itemSize > INT_MAX - overhead)
        pm_error("Cannot do RLE compression.  Input too large.");

    return inSize * itemSize + overhead;
}



void
pm_rlenc_allocoutbuf(unsigned char ** const outbufP,
                     size_t           const inSize,  /* element count */
                     enum pm_RleMode  const mode) {
/*---------------------------------------------------------------------------
   Allocate an output buffer sufficient for input with inSize elements, using
   compression mode 'mode'.  Element may be byte or word, whichever 'mode'
   implies.
-----------------------------------------------------------------------------*/
    size_t const size = pm_rlenc_maxbytes(inSize, mode);

    unsigned char * outbuf;

    MALLOCARRAY(outbuf, size);
    if (outbuf == NULL)
        pm_error("Out of memory trying to get %u bytes for RLE output buffer",
                 (unsigned)size);

    *outbufP = outbuf;
}



void
pm_rlenc_freebuf(void * const buf) {
    free(buf);
}


