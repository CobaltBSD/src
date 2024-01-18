#ifndef INTCODE_H_INCLUDED
#define INTCODE_H_INCLUDED

#include "pm_config.h"  /* For uint32_t, BYTE_ORDER, HAVE_INT64 */

static unsigned int const pm_byteOrder = BYTE_ORDER;

typedef struct {
/*----------------------------------------------------------------------------
   This is a big-endian representation of a 16 bit integer.  I.e.
   bytes[0] is the most significant 8 bits; bytes[1] is the least
   significant 8 bits of the number in pure binary.

   On a big-endian machines, this is bit for bit identical to uint16_t.
   On a little-endian machine, it isn't.

   This is an important data type because decent file formats use
   big-endian -- they don't care if some CPU happens to use some other
   code for its own work.
-----------------------------------------------------------------------------*/
    unsigned char bytes[2];
} bigend16;


static __inline__ uint16_t
pm_uintFromBigend16(bigend16 const arg) {

    uint16_t retval;

    switch (pm_byteOrder) {
    case BIG_ENDIAN: {
        union {
            bigend16 bigend;
            uint16_t native;
        } converter;
        converter.bigend = arg;
        retval = converter.native;
    } break;

    default: {
        retval =
            (arg.bytes[0] << 8) |
            (arg.bytes[1] << 0);
    }
    }
    return retval;
}



static __inline__ bigend16
pm_bigendFromUint16(uint16_t const arg) {

    bigend16 retval;

    switch (pm_byteOrder) {
    case BIG_ENDIAN: {
        union {
            bigend16 bigend;
            uint16_t native;
        } converter;
        converter.native = arg;
        retval = converter.bigend;
    } break;

    default: {
        uint16_t shift;
        shift = arg;
        retval.bytes[1] = shift;  /* Takes lower 8 bits */
        shift >>= 8;
        retval.bytes[0] = shift;  /* Takes lower 8 bits */
    }
    }
    return retval;
}

typedef struct {
/*----------------------------------------------------------------------------
   This is a big-endian representation of a 32 bit integer.  I.e.
   bytes[0] is the most significant 8 bits; bytes[3] is the least
   significant 8 bits of the number in pure binary.

   On a big-endian machines, this is bit for bit identical to uint32_t.
   On a little-endian machine, it isn't.

   This is an important data type because decent file formats use
   big-endian -- they don't care if some CPU happens to use some other
   code for its own work.
-----------------------------------------------------------------------------*/
    unsigned char bytes[4];
} bigend32;


static __inline__ uint32_t
pm_uintFromBigend32(bigend32 const arg) {

    uint32_t retval;

    switch (pm_byteOrder) {
    case BIG_ENDIAN: {
        union {
            bigend32 bigend;
            uint32_t native;
        } converter;
        converter.bigend = arg;
        retval = converter.native;
    } break;

#if HAVE_GCC_BSWAP
    case LITTLE_ENDIAN: {
        /* Use GCC built-in */  
        union {
            bigend32 bigend;
            uint32_t native;
        } converter;
        converter.bigend = arg;
        retval = __builtin_bswap32(converter.native);
    } break;
#endif
    
    default:
        retval =
            (arg.bytes[0] << 24) |
            (arg.bytes[1] << 16) |
            (arg.bytes[2] <<  8) |
            (arg.bytes[3] <<  0);
    }

    return retval;
}



static __inline__ bigend32
pm_bigendFromUint32(uint32_t const arg) {

    bigend32 retval;

    switch (pm_byteOrder) {
    case BIG_ENDIAN: {
        union {
            bigend32 bigend;
            uint32_t native;
        } converter;
        converter.native = arg;
        retval = converter.bigend;
    } break;

#if HAVE_GCC_BSWAP    
    case LITTLE_ENDIAN: {
        /* Use GCC built-in */  
        union {
            bigend32 bigend;
            uint32_t native;
        } converter;
        converter.native = __builtin_bswap32(arg);
        retval = converter.bigend;
    } break;
#endif    

    default: {
        uint32_t shift;
        shift = arg;
        retval.bytes[3] = shift;  /* Takes lower 8 bits */
        shift >>= 8;
        retval.bytes[2] = shift;  /* Takes lower 8 bits */
        shift >>= 8;
        retval.bytes[1] = shift;  /* Takes lower 8 bits */
        shift >>= 8;
        retval.bytes[0] = shift;  /* Takes lower 8 bits */
    }
    }
    return retval;
}


#if HAVE_INT64

typedef struct {
/*----------------------------------------------------------------------------
   This is a big-endian representation of a 64 bit integer.  I.e.
   bytes[0] is the most significant 8 bits; bytes[7] is the least
   significant 8 bits of the number in pure binary.

   On a big-endian machines, this is bit for bit identical to uint64_t.
   On a little-endian machine, it isn't.

   This is an important data type because decent file formats use
   big-endian -- they don't care if some CPU happens to use some other
   code for its own work.
-----------------------------------------------------------------------------*/
    unsigned char bytes[8];
} bigend64;


static __inline__ uint64_t
pm_uintFromBigend64(bigend64 const arg) {

    uint64_t retval;

    switch (pm_byteOrder) {
    case BIG_ENDIAN: {
        union {
            bigend64 bigend;
            uint64_t native;
        } converter;
        converter.bigend = arg;
        retval = converter.native;
    } break;

#if HAVE_GCC_BSWAP    
    case LITTLE_ENDIAN: {
        /* Use GCC built-in */  
        union {
            bigend64 bigend;
            uint64_t native;
        } converter;
        converter.bigend = arg;
        retval = __builtin_bswap64(converter.native);
    } break;
#endif
    default:
        retval =
            ((uint64_t)arg.bytes[0] << 56) | ((uint64_t)arg.bytes[1] << 48) |
            ((uint64_t)arg.bytes[2] << 40) | ((uint64_t)arg.bytes[3] << 32) |
            ((uint64_t)arg.bytes[4] << 24) | ((uint64_t)arg.bytes[5] << 16) |
            ((uint64_t)arg.bytes[6] <<  8) | ((uint64_t)arg.bytes[7] <<  0);
    }
    return retval;
}



static __inline__ bigend64
pm_bigendFromUint64(uint64_t const arg) {

    bigend64 retval;

    switch (pm_byteOrder) {
    case BIG_ENDIAN: {
        union {
            bigend64 bigend;
            uint64_t native;
        } converter;
        converter.native = arg;
        retval = converter.bigend;
    } break;

#if HAVE_GCC_BSWAP
    case LITTLE_ENDIAN: {

        /* Use GCC built-in */  
        union {
            bigend64 bigend;
            uint64_t native;
        } converter;
        converter.native = __builtin_bswap64(arg);
        retval = converter.bigend;
    } break;
#endif
    
    default: {
        uint64_t shift;
        shift = arg;
        retval.bytes[7] = shift;  /* Takes lower 8 bits */
        shift >>= 8;
        retval.bytes[6] = shift;  /* Takes lower 8 bits */
        shift >>= 8;
        retval.bytes[5] = shift;  /* Takes lower 8 bits */
        shift >>= 8;
        retval.bytes[4] = shift;  /* Takes lower 8 bits */
        shift >>= 8;
        retval.bytes[3] = shift;  /* Takes lower 8 bits */
        shift >>= 8;
        retval.bytes[2] = shift;  /* Takes lower 8 bits */
        shift >>= 8;
        retval.bytes[1] = shift;  /* Takes lower 8 bits */
        shift >>= 8;
        retval.bytes[0] = shift;  /* Takes lower 8 bits */
    }
    }
    return retval;
}

#endif /* HAVE_INT64 */

#endif





