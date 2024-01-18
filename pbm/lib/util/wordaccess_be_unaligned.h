/*=============================================================================
  This file is the part of wordaccess.h for use on a big-endian machine
  that does not require word accesses to be word-aligned.
*===========================================================================*/

typedef unsigned long int wordint;
typedef unsigned char wordintBytes[sizeof(wordint)];

static __inline__ wordint
bytesToWordint(wordintBytes bytes) {
    return *((wordint *)bytes);
}



static __inline__ void
wordintToBytes(wordintBytes * const bytesP,
               wordint        const wordInt) {
    *(wordint *)bytesP = wordInt;
}
