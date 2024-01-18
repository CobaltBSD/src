#ifndef WORDACCESS_H_INCLUDED
#define WORDACCESS_H_INCLUDED

/* These are facilities for accessing data in C programs in ways that
   exploit the way the machine defines words in order to squeeze out
   speed and CPU efficiency.

   In particular, routines in this file exploit the endianness of the
   machine and use explicit machine instructions to access C
   variables.

   A word is the amount of data that fits in a register; the amount of
   data that a single machine instruction can process.  For example,
   on IA32, a word is 32 bits because a single load or store
   instruction moves that many bits and a single add instruction
   operates on that many bits.


   These facilities revolve around two data types:  wordInt and
   wordIntBytes.

   wordint is an unsigned integer with precision (size) of one word.
   It is just the number -- nothing is implied about how it is
   represented in memory.

   wordintBytes is an array of bytes that represent a word-sized
   unsigned integer.  x[0] is the high order 8 digits of the binary
   coding of the integer, x[1] the next highest 8 digits, etc.
   Note that it has big-endian form, regardless of what endianness the
   underlying machine uses.

   The actual size of word differs by machine.  Usually it is 32 or 64
   bits.  Logically it can be as small as one byte.  Fixed bit sequences
   in each program impose a lower limit of word width.  For example, the
   longest bit sequence in pbmtog3 has 13 bits, so an 8-bit word won't
   work with that.

   We also assume that a char is 8 bits.

   HAVE_GCC_BITCOUNT and HAVE_GCC_BSWAP are set in pm_config.h

   BITS_PER_LONG is the number of bits in long int.
*/

#include "pm_config.h"

#if defined(WORDACCESS_GENERIC)
  /* User wants this, regardless of whether machine can do better */
  #include "wordaccess_generic.h"
#elif BYTE_ORDER == BIG_ENDIAN
  #if UNALIGNED_OK
     #include "wordaccess_be_unaligned.h"
  #else
    /* Sparc */
    #include "wordaccess_be_aligned.h"
  #endif
#elif HAVE_GCC_BITCOUNT
  #if (BITS_PER_LONG == 64)
    /* AMD Athlon 64, Intel x86_64, Intel Itanium, etc. */
    #include "wordaccess_64_le.h"
  #elif (BITS_PER_LONG == 32)
    /* Intel x86_32 (80386, 80486, Pentium), etc. */
      #include "wordaccess_generic.h"
  #else
     /* Extremely rare case.
        If long is neither 32 nor 64 bits, (say, 128) it comes here.
     */
     #include "wordaccess_generic.h"
  #endif
#else
  /* Non GCC or GCC prior to v.3.4; little-endian  */
  #include "wordaccess_generic.h"
#endif

#endif
