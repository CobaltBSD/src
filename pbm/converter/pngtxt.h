#ifndef PNGTXT_H_INCLUDED
#define PNGTXT_H_INCLUDED

#include <stdbool.h>
#include <stdio.h>
#include <png.h>

struct pngx;

void 
pngtxt_addChunk(struct pngx * const pngxP,
                FILE *        const tfp, 
                bool          const ztxt,
                bool          const itxt,
                bool          const verbose);

#endif
