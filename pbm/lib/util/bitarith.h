#ifndef BITARITH_H_INCLUDED
#define BITARITH_H_INCLUDED

#include "pm_config.h"

static __inline__ unsigned char
pm_byteLeftBits(unsigned char const x,
                unsigned int  const n) {
/*----------------------------------------------------------------------------
  Clear rightmost (8-n) bits, retain leftmost (=high) n bits.

  Return arbitrary value if n > 8.
-----------------------------------------------------------------------------*/
    unsigned char retval;

    retval = x;
    retval >>= (8-n);
    retval <<= (8-n);

    return retval;
}



static __inline__ unsigned char
pm_byteRightBits(unsigned char const x,
                 unsigned int  const n){
/*----------------------------------------------------------------------------
  Return rightmost (=low) n bits of x.

  Return arbitrary value if n > 8.
-----------------------------------------------------------------------------*/
    unsigned char retval;

    retval = x;
    retval <<= (8-n);
    retval >>= (8-n);

    return retval;
}

#endif
