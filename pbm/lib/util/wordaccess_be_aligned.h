/*=============================================================================
  This file is the part of wordaccess.h for use under with big-endian
  machines that require word accesses to be word-aligned.
*===========================================================================*/

typedef unsigned long int wordint;
typedef unsigned char wordintBytes[sizeof(wordint)];

static __inline__ wordint
bytesToWordint(wordintBytes bytes) {
    uint16_t const hi = *((uint16_t *) (bytes + 0));
    uint16_t const mh = *((uint16_t *) (bytes + 2));
    uint16_t const ml = *((uint16_t *) (bytes + 4));
    uint16_t const lo = *((uint16_t *) (bytes + 6));
    return
        (((wordint) hi) << 48) |
        (((wordint) mh) << 32) |
        (((wordint) ml) << 24) |
        (((wordint) lo) <<  0);
}



static __inline__ void
wordintToBytes(wordintBytes * const bytesP,
               wordint        const wordInt) {
    uint16_t const hi = ((wordInt >> 48) & 0xFF);
    uint16_t const mh = ((wordInt >> 32) & 0xFF);
    uint16_t const ml = ((wordInt >> 24) & 0xFF);
    uint16_t const lo = ((wordInt >>  0) & 0xFF);
    *(uint16_t *)(bytesP + 0) = hi;
    *(uint16_t *)(bytesP + 2) = mh;
    *(uint16_t *)(bytesP + 4) = ml;
    *(uint16_t *)(bytesP + 6) = lo;
}
