/* pgmtexture.c - calculate textural features of a PGM image
**
** Author: James Darrell McCauley
**         Texas Agricultural Experiment Station
**         Department of Agricultural Engineering
**         Texas A&M University
**         College Station, Texas 77843-2117 USA
**
** Code written partially taken from pgmtofs.c in the PBMPLUS package
** by Jef Poskanzer.
**
** Algorithms for calculating features (and some explanatory comments) are
** taken from:
**
**   Haralick, R.M., K. Shanmugam, and I. Dinstein. 1973. Textural features
**   for image classification.  IEEE Transactions on Systems, Man, and
**   Cybertinetics, SMC-3(6):610-621.
**
** Copyright (C) 1991 Texas Agricultural Experiment Station, employer for
** hire of James Darrell McCauley
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
**
** THE TEXAS AGRICULTURAL EXPERIMENT STATION (TAES) AND THE TEXAS A&M
** UNIVERSITY SYSTEM (TAMUS) MAKE NO EXPRESS OR IMPLIED WARRANTIES
** (INCLUDING BY WAY OF EXAMPLE, MERCHANTABILITY) WITH RESPECT TO ANY
** ITEM, AND SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL
** OR CONSEQUENTAL DAMAGES ARISING OUT OF THE POSESSION OR USE OF
** ANY SUCH ITEM. LICENSEE AND/OR USER AGREES TO INDEMNIFY AND HOLD
** TAES AND TAMUS HARMLESS FROM ANY CLAIMS ARISING OUT OF THE USE OR
** POSSESSION OF SUCH ITEMS.
** 
** Modification History:
** 24 Jun 91 - J. Michael Carstensen <jmc@imsor.dth.dk> supplied fix for 
**             correlation function.
**
** 05 Oct 05 - Marc Breithecker <Marc.Breithecker@informatik.uni-erlangen.de>
**             Fix calculation or normalizing constants for d > 1.
** 9 Jul 11  - Francois P. S. Luus <fpsluus@gmail.com> supplied fix for sum
**             variance calculation (use F6:savg instead of F8:sentropy in
**             F7:svar equation).


*/

#include <assert.h>
#include <math.h>

#include "pm_c_util.h"
#include "mallocvar.h"
#include "pgm.h"

#define RADIX 2.0
#define EPSILON 0.000000001
#define BL  "Angle                 "
#define F1  "Angular Second Moment "
#define F2  "Contrast              "
#define F3  "Correlation           "
#define F4  "Variance              "
#define F5  "Inverse Diff Moment   "
#define F6  "Sum Average           "
#define F7  "Sum Variance          "
#define F8  "Sum Entropy           "
#define F9  "Entropy               "
#define F10 "Difference Variance   "
#define F11 "Difference Entropy    "
#define F12 "Meas of Correlation-1 "
#define F13 "Meas of Correlation-2 "
#define F14 "Max Correlation Coeff "

#define SWAP(a,b) do {float const y=(a);(a)=(b);(b)=y;} while (0)



static float
sign(float const x,
     float const y) {

    return y < 0 ? -fabs(x) : fabs(x);
}



static bool const sortit = FALSE;



static float *
vector(unsigned int const nl,
       unsigned int const nh) {

    float * v;
    unsigned int i;

    assert(nh >= nl);

    MALLOCARRAY(v, (unsigned) (nh - nl + 1));

    if (v == NULL)
        pm_error("Unable to allocate memory for a vector.");

    for(i = 0; i < nh - nl +1; ++i)
        v[i] = 0;
    return v - nl;
}



static float **
matrix (unsigned int const nrl,
        unsigned int const nrh,
        unsigned int const ncl,
        unsigned int const nch) {
/*----------------------------------------------------------------------------
  Allocate a float matrix with range [nrl..nrh][ncl..nch]

  We do some seedy C here, subtracting an arbitrary integer from a pointer and
  calling the result a pointer.  It normally works because the only way we'll
  use that pointer is by adding that same integer or something greater to it.

  The point of this is not to allocate memory for matrix elements that will
  never be referenced (row < nrl or column < ncl).
-----------------------------------------------------------------------------*/
    unsigned int i;
    float ** m;

    assert(nrh >= nrl);

    /* allocate pointers to rows */
    MALLOCARRAY(m, (unsigned) (nrh - nrl + 1));
    if (m == NULL)
        pm_error("Unable to allocate memory for a matrix.");

    m -= ncl;

    assert (nch >= ncl);

    /* allocate rows and set pointers to them */
    for (i = nrl; i <= nrh; ++i) {
        MALLOCARRAY(m[i], (unsigned) (nch - ncl + 1));
        if (m[i] == NULL)
            pm_error("Unable to allocate memory for a matrix row.");
        m[i] -= ncl;
    }

    /* return pointer to array of pointers to rows */
    return m;
}



static void 
results (const char *  const name,
         const float * const a) {

    unsigned int i;

    fprintf(stdout, "%s", name);

    for (i = 0; i < 4; ++i)
        fprintf(stdout, "% 1.3e ", a[i]);

    fprintf(stdout, "% 1.3e\n", (a[0] + a[1] + a[2] + a[3]) / 4);
}



static void 
simplesrt (unsigned int  const n,
           float *       const arr) {

    unsigned int j;
    float a;

    for (j = 2; j <= n; ++j) {
        unsigned int i;

        a = arr[j];
        i = j;

        while (i > 1 && arr[i-1] > a) {
            arr[i] = arr[i-1];
            --i;
        }
        arr[i] = a;
    }
}



static void 
mkbalanced (float **     const a,
            unsigned int const n) {

    float const sqrdx = SQR(RADIX);

    unsigned int last, i;
    float s, r, g, f, c;

    last = 0;
    while (last == 0) {
        last = 1;
        for (i = 1; i <= n; ++i) {
            unsigned int j;
            r = c = 0.0;
            for (j = 1; j <= n; ++j) {
                if (j != i) {
                    c += fabs (a[j][i]);
                    r += fabs (a[i][j]);
                }
            }
            if (c && r) {
                g = r / RADIX;
                f = 1.0;
                s = c + r;
                while (c < g) {
                    f *= RADIX;
                    c *= sqrdx;
                }
                g = r * RADIX;
                while (c > g) {
                    f /= RADIX;
                    c /= sqrdx;
                }
                if ((c + r) / f < 0.95 * s) {
                    unsigned int j;
                    last = 0;
                    g = 1.0 / f;
                    for (j = 1; j <= n; ++j)
                        a[i][j] *= g;
                    for (j = 1; j <= n; ++j)
                        a[j][i] *= f;
                }
            }
        }
    }
}



static void 
reduction (float **     const a,
           unsigned int const n) {

    unsigned int m;

    for (m = 2; m < n; ++m) {
        unsigned int j;
        unsigned int i;
        float x;
        x = 0.0;
        i = m;
        for (j = m; j <= n; ++j) {
            if (fabs(a[j][m - 1]) > fabs(x)) {
                x = a[j][m - 1];
                i = j;
            }
        }
        if (i != m) {
            for (j = m - 1; j <= n; ++j)
                SWAP(a[i][j], a[m][j]);
            for (j = 1; j <= n; j++)
                SWAP(a[j][i], a[j][m]); 
            a[j][i] = a[j][i];
        }
        if (x != 0.0) {
            unsigned int i;
            for (i = m + 1; i <= n; ++i) {
                float y;
                y = a[i][m - 1];
                if (y) {
                    y /= x;
                    a[i][m - 1] = y;
                    for (j = m; j <= n; ++j)
                        a[i][j] -= y * a[m][j];
                    for (j = 1; j <= n; ++j)
                        a[j][m] += y * a[j][i];
                }
            }
        }
    }
}



static float
norm(float **     const a,
     unsigned int const n) {

    float anorm;
    unsigned int i;

    for (i = 2, anorm = fabs(a[1][1]); i <= n; ++i) {
        unsigned int j;
        for (j = (i - 1); j <= n; ++j)
            anorm += fabs(a[i][j]);
    }
    return anorm;
}



static void 
hessenberg(float **     const a,
           unsigned int const n,
           float *      const wr,
           float *      const wi) {

    float const anorm = norm(a, n);

    int nn;
    float t;

    assert(n >= 1);

    for (nn = n, t = 0.0; nn >= 1; ) {
        unsigned int its;
        int l;
        its = 0;
        do {
            float x;
            for (l = nn; l >= 2; --l) {
                float s;
                s = fabs (a[l - 1][l - 1]) + fabs (a[l][l]);
                if (s == 0.0)
                    s = anorm;
                if ((float) (fabs (a[l][l - 1]) + s) == s)
                    break;
            }
            assert(nn >= 1);
            x = a[nn][nn];
            if (l == nn) {
                wr[nn] = x + t;
                wi[nn--] = 0.0;
            } else {
                float w, y;
                y = a[nn - 1][nn - 1];  /* initial value */
                w = a[nn][nn - 1] * a[nn - 1][nn];  /* initial value */
                if (l == (nn - 1)) {
                    float const p = 0.5 * (y - x);
                    float const q = p * p + w;
                    float const z = sqrt(fabs(q));
                    x += t;
                    if (q >= 0.0) {
                        float const z2 = p + sign(z, p); 
                        wr[nn - 1] = wr[nn] = x + z2;
                        if (z2)
                            wr[nn] = x - w / z2;
                        wi[nn - 1] = wi[nn] = 0.0;
                    } else {
                        wr[nn - 1] = wr[nn] = x + p;
                        wi[nn - 1] = -(wi[nn] = z);
                    }
                    nn -= 2;
                } else {
                    int i, k, m;
                    float p, q, r;
                    if (its == 30)
                        pm_error("Too many iterations to required "
                                 "to find %s.  Giving up", F14);
                    if (its == 10 || its == 20) {
                        int i;
                        float s;
                        t += x;
                        for (i = 1; i <= nn; ++i)
                            a[i][i] -= x;
                        s = fabs(a[nn][nn - 1]) + fabs(a[nn - 1][nn - 2]);
                        y = x = 0.75 * s;
                        w = -0.4375 * s * s;
                    }
                    ++its;
                    for (m = (nn - 2); m >= l; --m) {
                        float const z = a[m][m];
                        float s, u, v;
                        r = x - z;
                        s = y - z;
                        p = (r * s - w) / a[m + 1][m] + a[m][m + 1];
                        q = a[m + 1][m + 1] - z - r - s;
                        r = a[m + 2][m + 1];
                        s = fabs(p) + fabs(q) + fabs(r);
                        p /= s;
                        q /= s;
                        r /= s;
                        if (m == l)
                            break;
                        u = fabs(a[m][m - 1]) * (fabs(q) + fabs(r));
                        v = fabs(p) * (fabs(a[m - 1][m - 1]) + fabs(z) + 
                                       fabs(a[m + 1][m + 1]));
                        if (u + v == v)
                            break;
                    }
                    for (i = m + 2; i <= nn; ++i) {
                        a[i][i - 2] = 0.0;
                        if (i != (m + 2))
                            a[i][i - 3] = 0.0;
                    }
                    for (k = m; k <= nn - 1; ++k) {
                        float s;
                        if (k != m) {
                            p = a[k][k - 1];
                            q = a[k + 1][k - 1];
                            r = 0.0;
                            if (k != (nn - 1))
                                r = a[k + 2][k - 1];
                            if ((x = fabs(p) + fabs(q) + fabs(r))) {
                                p /= x;
                                q /= x;
                                r /= x;
                            }
                        }
                        s = sign(sqrt(SQR(p) + SQR(q) + SQR(r)), p);
                        if (s) {
                            int const mmin = nn < k + 3 ? nn : k + 3;
                            float z;
                            int j;
                            if (k == m) {
                                if (l != m)
                                    a[k][k - 1] = -a[k][k - 1];
                            } else
                                a[k][k - 1] = -s * x;
                            p += s;
                            x = p / s;
                            y = q / s;
                            z = r / s;
                            q /= p;
                            r /= p;
                            for (j = k; j <= nn; ++j) {
                                p = a[k][j] + q * a[k + 1][j];
                                if (k != (nn - 1)) {
                                    p += r * a[k + 2][j];
                                    a[k + 2][j] -= p * z;
                                }
                                a[k + 1][j] -= p * y;
                                a[k][j] -= p * x;
                            }
                            for (i = l; i <= mmin; ++i) {
                                p = x * a[i][k] + y * a[i][k + 1];
                                if (k != (nn - 1)) {
                                    p += z * a[i][k + 2];
                                    a[i][k + 2] -= p * r;
                                }
                                a[i][k + 1] -= p * q;
                                a[i][k] -= p;
                            }
                        }
                    }
                }
            }
        } while (l < nn - 1);
    }
}



static float 
f1_a2m(float **     const p,
       unsigned int const ng) {
/*----------------------------------------------------------------------------
  Angular Second Moment

  The angular second-moment feature (ASM) f1 is a measure of homogeneity of
  the image. In a homogeneous image, there are very few dominant gray-tone
  transitions. Hence the P matrix for such an image will have fewer entries of
  large magnitude.
-----------------------------------------------------------------------------*/
    unsigned int i;
    float sum;

    for (i = 0, sum = 0.0; i < ng; ++i) {
        unsigned int j;
        for (j = 0; j < ng; ++j)
            sum += p[i][j] * p[i][j];
    }
    return sum;
}



static float 
f2_contrast(float **     const p,
            unsigned int const ng) {
/*----------------------------------------------------------------------------
   Contrast
   
   The contrast feature is a difference moment of the P matrix and is a
   measure of the contrast or the amount of local variations present in an
   image.
-----------------------------------------------------------------------------*/
    unsigned int n;
    float bigsum;

    for (n = 0, bigsum = 0.0; n < ng; ++n) {
        unsigned int i;
        float sum;
        for (i = 0, sum = 0.0; i < ng; ++i) {
            unsigned int j;
            for (j = 0; j < ng; ++j) {
                if ((i - j) == n || (j - i) == n)
                    sum += p[i][j];
            }
        }
        bigsum += SQR(n) * sum;
    }
    return bigsum;
}



static float 
f3_corr(float **     const p,
        unsigned int const ng) {
/*----------------------------------------------------------------------------
   Correlation

   This correlation feature is a measure of gray-tone linear-dependencies in
   the image.
-----------------------------------------------------------------------------*/
    unsigned int i;
    float sumSqrx, sumSqry, tmp;
    float * px;
    float meanx, meany, stddevx, stddevy;

    sumSqrx = 0.0; sumSqry = 0.0;
    meanx = 0.0; meany = 0.0;

    px = vector(0, ng);
    for (i = 0; i < ng; ++i)
        px[i] = 0;

    /* px[i] is the (i-1)th entry in the marginal probability matrix obtained
       by summing the rows of p[i][j]
    */
    for (i = 0; i < ng; ++i) {
        unsigned int j;
        for (j = 0; j < ng; ++j)
            px[i] += p[i][j];
    }

    /* Now calculate the means and standard deviations of px and py */
    for (i = 0; i < ng; ++i) {
        meanx += px[i] * i;
        sumSqrx += px[i] * SQR(i);
    }

    meany = meanx;
    sumSqry = sumSqrx;
    stddevx = sqrt(sumSqrx - (SQR(meanx)));
    stddevy = stddevx;

    /* Finally, the correlation ... */
    for (i = 0, tmp = 0; i < ng; ++i) {
        unsigned int j;
        for (j = 0; j < ng; ++j)
            tmp += i * j * p[i][j];
    }
    return (tmp - meanx * meany) / (stddevx * stddevy);
}



static float 
f4_var (float **     const p,
        unsigned int const ng) {
/*----------------------------------------------------------------------------
  Sum of Squares: Variance
-----------------------------------------------------------------------------*/
    unsigned int i;
    float mean, var;

    for (i = 0, mean = 0.0; i < ng; ++i) {
        unsigned int j;
        for (j = 0; j < ng; ++j)
            mean += i * p[i][j];
    }
    for (i = 0, var = 0.0; i < ng; ++i) {
        unsigned int j;
        for (j = 0; j < ng; ++j)
            var += (i + 1 - mean) * (i + 1 - mean) * p[i][j];
    }
    return var;
}



static float 
f5_idm (float **     const p,
        unsigned int const ng) {
/*----------------------------------------------------------------------------
  Inverse Difference Moment
-----------------------------------------------------------------------------*/
    unsigned int i;
    float idm;

    for (i = 0, idm = 0.0; i < ng; ++i) {
        unsigned int j;
        for (j = 0; j < ng; ++j)
            idm += p[i][j] / (1 + (i - j) * (i - j));
    }
    return idm;
}



static float 
f6_savg (float **     const p,
         unsigned int const ng) {
/*----------------------------------------------------------------------------
   Sum Average
-----------------------------------------------------------------------------*/
    float pxpy[2 * (PGM_MAXMAXVAL+1) + 1];
    unsigned int i;
    float savg;

    assert(2*ng < ARRAY_SIZE(pxpy));

    for (i = 0; i <= 2 * ng; ++i)
        pxpy[i] = 0.0;

    for (i = 0; i < ng; ++i) {
        unsigned int j;
        for (j = 0; j < ng; ++j)
            pxpy[i + j + 2] += p[i][j];
    }
    for (i = 2, savg = 0.0; i <= 2 * ng; ++i)
        savg += i * pxpy[i];

    return savg;
}



static float 
f7_svar (float **     const p,
         unsigned int const ng,
         float        const s) {
/*----------------------------------------------------------------------------
   Sum Variance
-----------------------------------------------------------------------------*/
    float pxpy[2 * (PGM_MAXMAXVAL+1) + 1];
    unsigned int i;
    float var;

    assert(2*ng < ARRAY_SIZE(pxpy));

    for (i = 0; i <= 2 * ng; ++i)
        pxpy[i] = 0;

    for (i = 0; i < ng; ++i) {
        unsigned int j;
        for (j = 0; j < ng; ++j)
            pxpy[i + j + 2] += p[i][j];
    }
    for (i = 2, var = 0.0; i <= 2 * ng; ++i)
        var += (i - s) * (i - s) * pxpy[i];

    return var;
}



static float 
f8_sentropy (float **     const p,
             unsigned int const ng) {
/*----------------------------------------------------------------------------
   Sum Entropy
-----------------------------------------------------------------------------*/
    float pxpy[2 * (PGM_MAXMAXVAL+1) + 1];
    unsigned int i;
    float sentropy;

    assert(2*ng < ARRAY_SIZE(pxpy));

    for (i = 0; i <= 2 * ng; ++i)
        pxpy[i] = 0;

    for (i = 0; i < ng; ++i) {
        unsigned int j;
        for (j = 0; j < ng; ++j)
            pxpy[i + j + 2] += p[i][j];
    }
    for (i = 2, sentropy = 0.0; i <= 2 * ng; ++i)
        sentropy -= pxpy[i] * log10(pxpy[i] + EPSILON);

    return sentropy;
}



static float 
f9_entropy (float **     const p,
            unsigned int const ng) {
/*----------------------------------------------------------------------------
   Entropy
-----------------------------------------------------------------------------*/
    unsigned int i;
    float entropy;

    for (i = 0, entropy = 0.0; i < ng; ++i) {
        unsigned int j;
        for (j = 0; j < ng; ++j)
            entropy += p[i][j] * log10(p[i][j] + EPSILON);
    }
    return -entropy;
}



static float 
f10_dvar (float **     const p,
          unsigned int const ng) {
/*----------------------------------------------------------------------------
   Difference Variance
-----------------------------------------------------------------------------*/
    double pxpy[PGM_MAXMAXVAL + 1];
    unsigned int i;
    double sqrNg;  /* Square of 'ng' */
    double sum;
    double sumSqr;
    double var;

    assert(ng <= ARRAY_SIZE(pxpy));

    for (i = 0; i < ng; ++i)
        pxpy[i] = 0;

    for (i = 0; i < ng; ++i) {
        unsigned int j;
        for (j = 0; j < ng; ++j)
            pxpy[abs(i - j)] += p[i][j];
    }
    /* Now calculate the variance of Pxpy (Px-y) */
    for (i = 0, sum = 0.0, sumSqr = 0.0; i < ng; ++i) {
        sum += pxpy[i];
        sumSqr += SQR(pxpy[i]);
    }
    sqrNg = SQR(ng);
    var = (sqrNg * sumSqr - SQR(sum)) / SQR(sqrNg);

    return var;
}



static float 
f11_dentropy (float **     const p,
              unsigned int const ng) {
/*----------------------------------------------------------------------------
   Difference Entropy
-----------------------------------------------------------------------------*/
    float pxpy[2 * (PGM_MAXMAXVAL+1) + 1];
    unsigned int i;
    float sum;

    assert(2*ng < ARRAY_SIZE(pxpy));

    for (i = 0; i <= 2 * ng; ++i)
        pxpy[i] = 0;

    for (i = 0; i < ng; ++i) {
        unsigned int j;
        for (j = 0; j < ng; ++j)
            pxpy[abs(i - j)] += p[i][j];
    }
    for (i = 0, sum = 0.0; i < ng; ++i)
        sum += pxpy[i] * log10(pxpy[i] + EPSILON);

    return -sum;
}



static float 
f12_icorr (float **     const p,
           unsigned int const ng) {
/*----------------------------------------------------------------------------
  Information Measures of Correlation
-----------------------------------------------------------------------------*/
    unsigned int i;
    float * px;
    float * py;
    float hx, hy, hxy, hxy1, hxy2;

    px = vector(0, ng);
    py = vector(0, ng);

    /*
     * px[i] is the (i-1)th entry in the marginal probability matrix obtained
     * by summing the rows of p[i][j]
     */
    for (i = 0; i < ng; ++i) {
        unsigned int j;
        for (j = 0; j < ng; ++j) {
            px[i] += p[i][j];
            py[j] += p[i][j];
        }
    }

    hx = 0.0; hy = 0.0; hxy = 0.0; hxy1 = 0.0; hxy2 = 0.0;

    for (i = 0; i < ng; ++i) {
        unsigned int j;
        for (j = 0; j < ng; ++j) {
            hxy1 -= p[i][j] * log10(px[i] * py[j] + EPSILON);
            hxy2 -= px[i] * py[j] * log10(px[i] * py[j] + EPSILON);
            hxy  -= p[i][j] * log10 (p[i][j] + EPSILON);
        }
    }
    /* Calculate entropies of px and py - is this right? */
    for (i = 0; i < ng; ++i) {
        hx -= px[i] * log10(px[i] + EPSILON);
        hy -= py[i] * log10(py[i] + EPSILON);
    }
    return (hxy - hxy1) / (hx > hy ? hx : hy);
}



static float 
f13_icorr (float **     const p, 
           unsigned int const ng) {
/*----------------------------------------------------------------------------
  Information Measures of Correlation
-----------------------------------------------------------------------------*/
    unsigned int i;
    float * px;
    float * py;
    float hx, hy, hxy, hxy1, hxy2;

    px = vector(0, ng);
    py = vector(0, ng);

    /*
     * px[i] is the (i-1)th entry in the marginal probability matrix obtained
     * by summing the rows of p[i][j]
     */
    for (i = 0; i < ng; ++i) {
        unsigned int j;
        for (j = 0; j < ng; ++j) {
            px[i] += p[i][j];
            py[j] += p[i][j];
        }
    }

    hx = 0.0; hy = 0.0; hxy = 0.0; hxy1 = 0.0; hxy2 = 0.0;

    for (i = 0; i < ng; ++i) {
        unsigned int j;
        for (j = 0; j < ng; ++j) {
            hxy1 -= p[i][j] * log10(px[i] * py[j] + EPSILON);
            hxy2 -= px[i] * py[j] * log10(px[i] * py[j] + EPSILON);
            hxy  -= p[i][j] * log10(p[i][j] + EPSILON);
        }
    }
    /* Calculate entropies of px and py */
    for (i = 0; i < ng; ++i) {
        hx -= px[i] * log10 (px[i] + EPSILON);
        hy -= py[i] * log10 (py[i] + EPSILON);
    }
    return sqrt(fabs(1 - exp (-2.0 * (hxy2 - hxy))));
}



static float 
f14_maxcorr (float **     const p,
             unsigned int const ng) {
/*----------------------------------------------------------------------------
  The Maximal Correlation Coefficient
-----------------------------------------------------------------------------*/
    unsigned int i;
    float *px, *py;
    float ** q;
    float * x;
    float * iy;
    float tmp;

    px = vector(0, ng);
    py = vector(0, ng);
    q = matrix(1, ng + 1, 1, ng + 1);
    x = vector(1, ng);
    iy = vector(1, ng);

    /*
     * px[i] is the (i-1)th entry in the marginal probability matrix obtained
     * by summing the rows of p[i][j]
     */
    for (i = 0; i < ng; ++i) {
        unsigned int j;
        for (j = 0; j < ng; ++j) {
            px[i] += p[i][j];
            py[j] += p[i][j];
        }
    }

    /* Compute the Q matrix */
    for (i = 0; i < ng; ++i) {
        unsigned int j;
        for (j = 0; j < ng; ++j) {
            unsigned int k;
            q[i + 1][j + 1] = 0;
            for (k = 0; k < ng; ++k)
                q[i + 1][j + 1] += p[i][k] * p[j][k] / px[i] / py[k];
        }
    }

    /* Balance the matrix */
    mkbalanced(q, ng);
    /* Reduction to Hessenberg Form */
    reduction(q, ng);
    /* Finding eigenvalue for nonsymetric matrix using QR algorithm */
    hessenberg(q, ng, x, iy);
    if (sortit)
        simplesrt(ng, x);

    /* Return the sqrt of the second largest eigenvalue of q */
    for (i = 2, tmp = x[1]; i <= ng; ++i)
        tmp = (tmp > x[i]) ? tmp : x[i];

    return sqrt(x[ng - 1]);
}



int
main (int argc, const char ** argv) {

    FILE * ifP;
    gray ** grays;
    unsigned int tone[PGM_MAXMAXVAL+1];
    unsigned int r0, r45, r90;
    unsigned int d;
    unsigned int x, y;
    unsigned int row;
    int rows, cols;
    int argn;
    unsigned int itone;
    unsigned int toneCt;
    float ** p_matrix0, ** p_matrix45, ** p_matrix90, ** p_matrix135;
    float a2m[4], contrast[4], corr[4], var[4], idm[4], savg[4];
    float sentropy[4], svar[4], entropy[4], dvar[4], dentropy[4];
    float icorr[4], maxcorr[4];
    gray maxval;
    unsigned int i;
    const char * const usage = "[-d <d>] [pgmfile]";

    pm_proginit(&argc, argv);

    argn = 1;

    /* Check for flags. */
    if ( argn < argc && argv[argn][0] == '-' )
    {
        if ( argv[argn][1] == 'd' )
        {
            ++argn;
            if ( argn == argc || sscanf( argv[argn], "%u", &d ) != 1 )
                pm_usage( usage );
        }
        else
            pm_usage( usage );
        ++argn;
    }

    if ( argn < argc )
    {
        ifP = pm_openr( argv[argn] );
        ++argn;
    }
    else
        ifP = stdin;

    if ( argn != argc )
        pm_usage( usage );

    d = 1;

    grays = pgm_readpgm(ifP, &cols, &rows, &maxval);
    pm_close (ifP);

    /* Determine the number of different gray scales (not maxval) */
    for (i = 0; i <= PGM_MAXMAXVAL; ++i)
        tone[i] = -1;
    for (row = 0; row < rows; ++row) {
        unsigned int col;
        for (col = 0; col < cols; ++col)
            tone[grays[row][col]] = grays[row][col];
    }
    for (i = 0, toneCt = 0; i <= PGM_MAXMAXVAL; ++i) {
        if (tone[i] != -1)
            ++toneCt;
    }
    pm_message("(Image has %u gray levels.)", toneCt);

    /* Collapse array, taking out all zero values */
    for (row = 0, itone = 0; row <= PGM_MAXMAXVAL; ++row)
        if (tone[row] != -1)
            tone[itone++] = tone[row];
    /* Now array contains only the gray levels present (in ascending order) */

    /* Allocate memory for gray-tone spatial dependence matrix */
    p_matrix0   = matrix (0, toneCt, 0, toneCt);
    p_matrix45  = matrix (0, toneCt, 0, toneCt);
    p_matrix90  = matrix (0, toneCt, 0, toneCt);
    p_matrix135 = matrix (0, toneCt, 0, toneCt);

    for (row = 0; row < toneCt; ++row) {
        unsigned int col;
        for (col = 0; col < toneCt; ++col) {
            p_matrix0 [row][col] = p_matrix45 [row][col] = 0;
            p_matrix90[row][col] = p_matrix135[row][col] = 0;
        }
    }
    if (d > cols)
        pm_error("Image is narrower (%u columns) "
                 "than specified distance (%u)", cols, d);

    /* Find gray-tone spatial dependence matrix */
    pm_message("Computing spatial dependence matrix...");
    for (row = 0; row < rows; ++row) {
        unsigned int col;
        for (col = 0; col < cols; ++col) {
            unsigned int angle;
            for (angle = 0, x = 0; angle <= 135; angle += 45) {
                while (tone[x] != grays[row][col])
                    ++x;
                if (angle == 0 && col + d < cols) {
                    y = 0;
                    while (tone[y] != grays[row][col + d])
                        ++y;
                    ++p_matrix0[x][y];
                    ++p_matrix0[y][x];
                }
                if (angle == 90 && row + d < rows) {
                    y = 0;
                    while (tone[y] != grays[row + d][col])
                        ++y;
                    ++p_matrix90[x][y];
                    ++p_matrix90[y][x];
                }
                if (angle == 45 && row + d < rows && col >= d) {
                    y = 0;
                    while (tone[y] != grays[row + d][col - d])
                        ++y;
                    ++p_matrix45[x][y];
                    ++p_matrix45[y][x];
                }
                if (angle == 135 && row + d < rows && col + d < cols) {
                    y = 0;
                    while (tone[y] != grays[row + d][col + d])
                        ++y;
                    ++p_matrix135[x][y];
                    ++p_matrix135[y][x];
                }
            }
        }
    }
    /* Gray-tone spatial dependence matrices are complete */

    /* Find normalizing constants */
    r0  = 2 * rows * (cols - d);
    r45 = 2 * (rows - d) * (cols - d);
    r90 = 2 * (rows - d) * cols;

    /* Normalize gray-tone spatial dependence matrix */
    for (itone = 0; itone < toneCt; ++itone) {
        unsigned int jtone;
        for (jtone = 0; jtone < toneCt; ++jtone) {
            p_matrix0[itone][jtone]   /= r0;
            p_matrix45[itone][jtone]  /= r45;
            p_matrix90[itone][jtone]  /= r90;
            p_matrix135[itone][jtone] /= r45;
        }
    }
    pm_message(" ...done.");

    pm_message("Computing textural features ...");

    fprintf(stdout, "\n");
    fprintf(stdout,
            "%s         0         45         90        135        Avg\n",
            BL);

    a2m[0] = f1_a2m(p_matrix0,   toneCt);
    a2m[1] = f1_a2m(p_matrix45,  toneCt);
    a2m[2] = f1_a2m(p_matrix90,  toneCt);
    a2m[3] = f1_a2m(p_matrix135, toneCt);
    results(F1, a2m);

    contrast[0] = f2_contrast(p_matrix0,   toneCt);
    contrast[1] = f2_contrast(p_matrix45,  toneCt);
    contrast[2] = f2_contrast(p_matrix90,  toneCt);
    contrast[3] = f2_contrast(p_matrix135, toneCt);
    results(F2, contrast);


    corr[0] = f3_corr(p_matrix0,   toneCt);
    corr[1] = f3_corr(p_matrix45,  toneCt);
    corr[2] = f3_corr(p_matrix90,  toneCt);
    corr[3] = f3_corr(p_matrix135, toneCt);
    results(F3, corr);

    var[0] = f4_var(p_matrix0,   toneCt);
    var[1] = f4_var(p_matrix45,  toneCt);
    var[2] = f4_var(p_matrix90,  toneCt);
    var[3] = f4_var(p_matrix135, toneCt);
    results(F4, var);


    idm[0] = f5_idm(p_matrix0,   toneCt);
    idm[1] = f5_idm(p_matrix45,  toneCt);
    idm[2] = f5_idm(p_matrix90,  toneCt);
    idm[3] = f5_idm(p_matrix135, toneCt);
    results(F5, idm);

    savg[0] = f6_savg(p_matrix0,  toneCt);
    savg[1] = f6_savg(p_matrix45,  toneCt);
    savg[2] = f6_savg(p_matrix90,  toneCt);
    savg[3] = f6_savg(p_matrix135, toneCt);
    results(F6, savg);

    svar[0] = f7_svar(p_matrix0,   toneCt, savg[0]);
    svar[1] = f7_svar(p_matrix45,  toneCt, savg[1]);
    svar[2] = f7_svar(p_matrix90,  toneCt, savg[2]);
    svar[3] = f7_svar(p_matrix135, toneCt, savg[3]);
    results(F7, svar);

    sentropy[0] = f8_sentropy(p_matrix0,   toneCt);
    sentropy[1] = f8_sentropy(p_matrix45,  toneCt);
    sentropy[2] = f8_sentropy(p_matrix90,  toneCt);
    sentropy[3] = f8_sentropy(p_matrix135, toneCt);
    results(F8, sentropy);

    entropy[0] = f9_entropy(p_matrix0,   toneCt);
    entropy[1] = f9_entropy(p_matrix45,  toneCt);
    entropy[2] = f9_entropy(p_matrix90,  toneCt);
    entropy[3] = f9_entropy(p_matrix135, toneCt);
    results(F9, entropy);

    dvar[0] = f10_dvar(p_matrix0,   toneCt);
    dvar[1] = f10_dvar(p_matrix45,  toneCt);
    dvar[2] = f10_dvar(p_matrix90,  toneCt);
    dvar[3] = f10_dvar(p_matrix135, toneCt);
    results(F10, dvar);

    dentropy[0] = f11_dentropy(p_matrix0,   toneCt);
    dentropy[1] = f11_dentropy(p_matrix45,  toneCt);
    dentropy[2] = f11_dentropy(p_matrix90,  toneCt);
    dentropy[3] = f11_dentropy(p_matrix135, toneCt);
    results (F11, dentropy);

    icorr[0] = f12_icorr(p_matrix0,   toneCt);
    icorr[1] = f12_icorr(p_matrix45,  toneCt);
    icorr[2] = f12_icorr(p_matrix90,  toneCt);
    icorr[3] = f12_icorr(p_matrix135, toneCt);
    results(F12, icorr);

    icorr[0] = f13_icorr(p_matrix0,   toneCt);
    icorr[1] = f13_icorr(p_matrix45,  toneCt);
    icorr[2] = f13_icorr(p_matrix90,  toneCt);
    icorr[3] = f13_icorr(p_matrix135, toneCt);
    results(F13, icorr);

    maxcorr[0] = f14_maxcorr(p_matrix0,   toneCt);
    maxcorr[1] = f14_maxcorr(p_matrix45,  toneCt);
    maxcorr[2] = f14_maxcorr(p_matrix90,  toneCt);
    maxcorr[3] = f14_maxcorr(p_matrix135, toneCt);
    results(F14, maxcorr);

    pm_message(" ...done.");

    return 0;
}
