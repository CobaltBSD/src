#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

#include <stdio.h>

void
pm_freadline(FILE *        const fileP,
             const char ** const lineP,
             const char ** const errorP);

#endif
