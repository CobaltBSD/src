#ifndef WORDINTCLZ_H_INCLUDED
#define WORDINTCLZ_H_INCLUDED

#if (!defined(WORDACCESS_GENERIC) && HAVE_GCC_BITCOUNT )
/* 
   Compiler is GCC and has __builtin_clz()
   wordint is long 
 
   __builtin_clz is available on GCC 3.4 and above
     
   Note that the clz scheme does not work and requires adjustment
   if long type does not make use of all bits for data storage.
  
   This is unlikely.  According to GNU MP (http://www.swox.com/gmp/),
   in rare cases such as Cray, there are smaller data types that take up
   the same space as long, but leave the higher bits silent.
   Currently, there are no known such cases for data type long.
 */

static __inline__ unsigned int
wordintClz(wordint const x){

    assert(sizeof(unsigned long int) == sizeof(wordint));

    if (x == 0)
        return sizeof(wordint) * 8;
    else
        return (__builtin_clzl( (unsigned long int) x ));
}
  
#else

/* wordint is uint32_t: exactly 32 bits wide */
 
static unsigned char const clz8[256]= {
    8, 7, 6, 6, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 
};



static __inline__ unsigned int
clz16(wordint const x) {

    if (x >> 8 != 0)
        return clz8[x >> 8];
    else
        return clz8[x] + 8;
}



static __inline__  unsigned int
clz32(wordint const x) {

    if (x >> 16 != 0)
        return clz16(x >> 16);
    else
        return clz16(x) + 16;
}



static __inline__  unsigned int
wordintClz(wordint const x) {

    assert(sizeof(wordint) == 4);

    return clz32(x);
}

/* Another way to calculate leading zeros:
   x == 0 ? 32 : 31 - floor(log(x)/log(2))
   (Beware: insufficient precision will cause errors)
*/

#endif

#endif
