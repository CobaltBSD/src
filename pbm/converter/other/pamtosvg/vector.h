/* vector.h: operations on vectors and points. */

#ifndef VECTOR_H
#define VECTOR_H

#include "point.h"
#include "exception.h"

/* Our vectors are represented as displacements along the x and y axes.  */

typedef struct
{
  float dx, dy, dz;
} vector_type;


/* Consider a point as a vector from the origin.  */
vector_type
make_vector(float_coord const);

/* And a vector as a point, i.e., a displacement from the origin.  */
float_coord
vector_to_point(vector_type const);


/* Definitions for these common operations can be found in any decent
   linear algebra book, and most calculus books.  */

float
magnitude(vector_type const);

vector_type
normalize(vector_type const);

vector_type
Vadd(vector_type const,
     vector_type const);

float
Vdot(vector_type const,
     vector_type const);

vector_type
Vmult_scalar(vector_type const,
             float       const);

float
Vangle(vector_type         const in,
       vector_type         const out,
       at_exception_type * const exP);

/* These operations could have been named `P..._vector' just as well as
   V..._point, so we may as well allow both names.  */

#define Padd_vector Vadd_point

float_coord
Vadd_point(float_coord const,
           vector_type const);

#define Psubtract_vector Vsubtract_point

float_coord
Vsubtract_point(float_coord const,
                vector_type const);

vector_type
Pdirection(float_coord const final,
           float_coord const initial);

/* This returns the rounded sum.  */
#define IPadd_vector Vadd_int_point

pm_pixelcoord
Vadd_int_point(pm_pixelcoord const c,
               vector_type   const v);

/* Take the absolute value of both components.  */
vector_type
Vabs(vector_type const);

/* Operations on points with real coordinates.  It is not orthogonal,
   but more convenient, to have the subtraction operator return a
   vector, and the addition operator return a point.  */
vector_type
Psubtract(float_coord const,
          float_coord const);

vector_type
IPsubtract(pm_pixelcoord const coord1,
           pm_pixelcoord const coord2);

/* These are heavily used in spline fitting.  */

float_coord
Padd(float_coord const,
     float_coord const);

float_coord
Pmult_scalar(float_coord const,
             float       const);

#endif
