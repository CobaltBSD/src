#ifndef PAMFLIP_SSE_H_INCLUDED
#define PAMFLIP_SSE_H_INCLUDED

struct pam;
#include "flip.h"

void
pamflip_transformRowsToColumnsPbmSse(const struct pam *     const inpamP,
                                     const struct pam *     const outpamP,
                                     struct xformCore       const xformCore);

#endif
