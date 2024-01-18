/*=============================================================================
  This file is the part of wordaccess.h for use under these
  conditions:

  * GCC (>=3.4)  (__builtin_clz appears in GCC 3.4)
  * Little-Endian machines (IA64, X86-64, AMD64)
  * 64 bit long
 
=============================================================================*/

#include "intcode.h"

typedef uint64_t wordint;
typedef unsigned char wordintBytes[sizeof(wordint)];


static __inline__ wordint
bytesToWordint(wordintBytes const bytes) {
    return (wordint) pm_uintFromBigend64(*(bigend64*)bytes);
}



static __inline__ void
wordintToBytes(wordintBytes * const bytesP,
               wordint        const wordInt) {
     *(bigend64*)bytesP = pm_bigendFromUint64(wordInt);
}
