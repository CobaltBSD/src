/*=============================================================================

  This file is the part of wordaccess.h for use under any of these
  conditions:

  * Compiler other than GCC
  * GCC before version 3.4
  * Requested by the user with WORDACCESS_GENERIC
=============================================================================*/

#include "intcode.h"

typedef uint32_t wordint;
typedef unsigned char wordintBytes[sizeof(wordint)];

    
static __inline__ wordint
bytesToWordint(wordintBytes  const bytes) {

    return (wordint)  pm_uintFromBigend32( * (bigend32*) bytes);
}


static __inline__ void
wordintToBytes(wordintBytes * const bytesP,
               wordint    const wordInt) {

    * (bigend32*) bytesP = pm_bigendFromUint32((uint32_t)wordInt);
}
