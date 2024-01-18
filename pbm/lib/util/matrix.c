/*=============================================================================
                                matrix
===============================================================================

  Matrix math.

=============================================================================*/

#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "pm_c_util.h"
#include "mallocvar.h"
#include "nstring.h"

#include "matrix.h"


static double const epsilon = 1e-10;



static void
swap(double * const aP,
     double * const bP) {

    double const oldA = *aP;

    *aP = *bP;
    *bP = oldA;
}



static void
initializeWorkMatrices(unsigned int   const n,
                       double **      const aInit,
                       const double * const cInit,
                       double ***     const aP,
                       double **      const cP,
                       const char **  const errorP) {
/*----------------------------------------------------------------------------
   Allocate memory for an n x n matrix, initialize it to the value of
   aInit[], and return it as *aP.

   Allocate memory for an n x 1 matrix, initialize it to the value of
   cInit[], and return it as *cP.
-----------------------------------------------------------------------------*/
    double ** a;
    double * c;

    MALLOCARRAY2(a, n, n);
    if (a == NULL)
        pm_asprintf(errorP, "Could not get memory for a %u x %u matrix", n, n);
    else {
        unsigned int i;
        for (i = 0; i < n; ++i) {
            unsigned int j;
            for (j = 0; j < n; ++j)
                a[i][j] = aInit[i][j];
        }
        MALLOCARRAY(c, n);
        if (c == NULL)
            pm_asprintf(errorP, "Could not get memory for a %u x 1 matrix", n);
        else {
            unsigned int i;
            for (i = 0; i < n; ++i)
                c[i] = cInit[i];

            *errorP = NULL;
        }
        if (*errorP)
            free(a);
    }
    *aP = a;
    *cP = c;
}



static void
findLargestIthCoeff(unsigned int   const n,
                    double **      const a,
                    unsigned int   const i,
                    unsigned int * const istarP,
                    const char **  const errorP) {
/*----------------------------------------------------------------------------
  Among the 'i'th and following rows in 'a' (which has 'n' total rows),
  find the one with the largest 'i'th column.

  And it had better be greater than zero; if not, we fail (return *errorP
  non-null).

  Return its index as *istarP.
-----------------------------------------------------------------------------*/
    double maxSoFar;
    unsigned int maxIdx;
    unsigned int ii;

    for (ii = i, maxSoFar = 0.0; ii < n; ++ii) {
        double const thisA = fabs(a[ii][i]);
        if (thisA >= maxSoFar) {
            maxIdx = ii;
            maxSoFar = thisA;
        }
    }
    if (maxSoFar < epsilon) {
        const char * const baseMsg = "Matrix equation has no unique solution";
        if (pm_have_float_format())
            pm_asprintf(errorP, "%s.  (debug: coeff %u %e < %e)",
                        baseMsg, i, maxSoFar, epsilon);
        else
            pm_asprintf(errorP, "%s", baseMsg);
    } else {
        *istarP = maxIdx;
        *errorP = NULL;
    }
}



static void
eliminateOneUnknown(unsigned int  const i,
                    unsigned int  const n,
                    double **     const a,
                    double *      const c,
                    const char ** const errorP) {

    unsigned int maxRow;

    findLargestIthCoeff(n, a, i, &maxRow, errorP);

    if (!*errorP) {
        /* swap rows 'i' and 'maxRow' in 'a' and 'c', so that the ith
           row has the largest ith coefficient.
        */
        unsigned int j;
        for (j = 0; j < n; j++)
            swap(&a[maxRow][j], &a[i][j]);

        swap(&c[maxRow], &c[i]);

        /* Combine rows so that the ith coefficient in every row below
           the ith is zero.
        */
        {
            unsigned int ii;
            for (ii = i+1; ii < n; ++ii) {
                double const multiplier = a[ii][i] / a[i][i];
                    /* This is what we multiply the whole ith row by to make
                       its ith coefficient equal to that in the iith row.
                    */
                unsigned int j;

                /* Combine ith row into iith row so that the ith coefficient
                   in the iith is zero.
                */
                c[ii] = c[ii] - multiplier * c[i];

                for (j = 0; j < n; ++j)
                    a[ii][j] = a[ii][j] - multiplier * a[i][j];

                assert(a[ii][i] < epsilon);
            }
        }
        *errorP = NULL;
    }
}



void
pm_solvelineareq(double **     const aArg,
                 double *      const x,
                 double *      const cArg,
                 unsigned int  const n,
                 const char ** const errorP) {
/*----------------------------------------------------------------------------
   Solve the matrix equation 'a' * 'x' = 'c' for 'x'.

   'n' is the dimension of the matrices.  'a' is 'n' x 'n',
   while 'x' and 'c' are 'n' x 1.
-----------------------------------------------------------------------------*/
    /* We use Gaussian reduction. */

    double ** a;
    double * c;

    initializeWorkMatrices(n, aArg, cArg, &a, &c, errorP);

    if (!*errorP) {
        unsigned int i;

        for (i = 0, *errorP = NULL; i < n && !*errorP; ++i)
            eliminateOneUnknown(i, n, a, c, errorP);

        if (!*errorP) {
            /* a[] now has all zeros in the lower left triangle. */
            /* Work from the bottom up to solve for the unknowns x[], from
               the a and c rows in question and all the x[] below it
            */
            
            unsigned int k;
            for (k = 0; k < n; ++k) {
                unsigned int const m = n - k - 1;
                unsigned int j;
                double xwork;

                for (j = m+1, xwork = c[m]; j < n; ++j)
                    xwork -= a[m][j] * x[j];
                    
                x[m] = xwork / a[m][m];
            }
        }
    }
    pm_freearray2((void**)a);
    free(c);
}



