#ifndef FLOATCODE_H_INCLUDED
#define FLOATCODE_H_INCLUDED

#include "pm_config.h"  /* BYTE_ORDER */

unsigned int const pm_byteOrder = BYTE_ORDER;


typedef struct {
/*----------------------------------------------------------------------------
   This is a big-endian representation of a 32 bit floating point number.
   I.e. bytes[0] contains the sign bit, etc.

   On a big-endian machines, this is bit for bit identical to 'float'.
   On a little-endian machine, it isn't.

   This is an important data type because decent file formats use
   big-endian -- they don't care if some CPU happens to use some other
   code for its own work.
-----------------------------------------------------------------------------*/
    unsigned char bytes[4];
} pm_bigendFloat;


static __inline__ float
pm_floatFromBigendFloat(pm_bigendFloat const arg) {

    float retval;

    switch (pm_byteOrder) {
    case BIG_ENDIAN: {
        union {
            pm_bigendFloat bigend;
            float native;
        } converter;
        
        converter.bigend = arg;
        
        retval = converter.native;
    }; break;
    case LITTLE_ENDIAN: {
        union {
            unsigned char bytes[4];
            float native;
        } converter;

        converter.bytes[0] = arg.bytes[3];
        converter.bytes[1] = arg.bytes[2];
        converter.bytes[2] = arg.bytes[1];
        converter.bytes[3] = arg.bytes[0];

        retval = converter.native;
    } break;
    }
    return retval;
}



static __inline__ pm_bigendFloat
pm_bigendFloatFromFloat(float const arg) {

    pm_bigendFloat retval;

    switch (pm_byteOrder) {
    case BIG_ENDIAN: {
        union {
            pm_bigendFloat bigend;
            float native;
        } converter;
        
        converter.native = arg;

        retval = converter.bigend;
    } break;
    case LITTLE_ENDIAN: {
        union {
            unsigned char bytes[4];
            float native;
        } converter;

        converter.native = arg;

        retval.bytes[0] = converter.bytes[3];
        retval.bytes[1] = converter.bytes[2];
        retval.bytes[2] = converter.bytes[1];
        retval.bytes[3] = converter.bytes[0];
    } break;
    }
    return retval;
}

typedef struct {
/*----------------------------------------------------------------------------
   This is a big-endian representation of a 64 bit floating point number.
   I.e. bytes[0] contains the sign bit, etc.

   On a big-endian machines, this is bit for bit identical to 'float'.
   On a little-endian machine, it isn't.

   This is an important data type because decent file formats use
   big-endian -- they don't care if some CPU happens to use some other
   code for its own work.
-----------------------------------------------------------------------------*/
    unsigned char bytes[8];
} pm_bigendDouble;


static __inline__ double
pm_doubleFromBigendDouble(pm_bigendDouble const arg) {

    double retval;

    switch (pm_byteOrder) {
    case BIG_ENDIAN: {
        union {
            pm_bigendDouble bigend;
            double native;
        } converter;
        
        converter.bigend = arg;
        
        retval = converter.native;
    }; break;
    case LITTLE_ENDIAN: {
        union {
            unsigned char bytes[8];
            double native;
        } converter;

        converter.bytes[0] = arg.bytes[7];
        converter.bytes[1] = arg.bytes[6];
        converter.bytes[2] = arg.bytes[5];
        converter.bytes[3] = arg.bytes[4];
        converter.bytes[4] = arg.bytes[3];
        converter.bytes[5] = arg.bytes[2];
        converter.bytes[6] = arg.bytes[1];
        converter.bytes[7] = arg.bytes[0];

        retval = converter.native;
    } break;
    }
    return retval;
}



static __inline__ pm_bigendDouble
pm_bigendDoubleFromDouble(double const arg) {

    pm_bigendDouble retval;

    switch (pm_byteOrder) {
    case BIG_ENDIAN: {
        union {
            pm_bigendDouble bigend;
            double native;
        } converter;
        
        converter.native = arg;

        retval = converter.bigend;
    } break;
    case LITTLE_ENDIAN: {
        union {
            unsigned char bytes[8];
            double native;
        } converter;

        converter.native = arg;

        retval.bytes[0] = converter.bytes[7];
        retval.bytes[1] = converter.bytes[6];
        retval.bytes[2] = converter.bytes[5];
        retval.bytes[3] = converter.bytes[4];
        retval.bytes[4] = converter.bytes[3];
        retval.bytes[5] = converter.bytes[2];
        retval.bytes[6] = converter.bytes[1];
        retval.bytes[7] = converter.bytes[0];
    } break;
    }
    return retval;
}

#endif
