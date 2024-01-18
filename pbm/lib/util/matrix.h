#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

void
pm_solvelineareq(double **     const aArg,
                 double *      const x,
                 double *      const cArg,
                 unsigned int  const n,
                 const char ** const errorP);

#endif
