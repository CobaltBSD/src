#ifndef RUNLENGTH_INCLUDED
#define RUNLENGTH_INCLUDED

#include "pm_config.h"

#include <limits.h>

#ifdef __cplusplus
extern "C" {
#endif
#if 0
} /* to fake out automatic code indenters */
#endif


enum pm_RleMode { PM_RLE_PACKBITS,          /* most common mode */
                  PM_RLE_GRAPHON,           /* reserved */ 
                  PM_RLE_PPA,               /* reserved */
                  PM_RLE_SGI8,              /* reserved */
                  PM_RLE_SGI16,
                  PM_RLE_PALM16
                };

size_t
pm_rlenc_maxbytes (size_t          const inSize,
                   enum pm_RleMode const mode);

void
pm_rlenc_allocoutbuf(unsigned char ** const outbufP,
                     size_t           const inSize,
                     enum pm_RleMode  const mode);


void
pm_rlenc_freebuf(void * const buf);

void
pm_rlenc_compressbyte(const unsigned char * const inbuf,
                      unsigned char       * const outbuf,
                      enum pm_RleMode       const mode,
                      size_t                const inSize,
                      size_t              * const outputSizeP);

void
pm_rlenc_compressword(const uint16_t      * const inbuf,
                      unsigned char       * const outbuf,
                      enum pm_RleMode       const mode,
                      size_t                const itemCnt,
                      size_t              * const outputSizeP);

#endif
