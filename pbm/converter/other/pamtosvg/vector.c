/* vector.c: vector/point operations. */

#define _XOPEN_SOURCE   /* Make sure M_PI is in <math.h> */
#include <math.h>
#include <errno.h>
#include <assert.h>
#include <string.h>

#include "pm_c_util.h"

#include "vector.h"
#include "message.h"
#include "epsilon-equal.h"

static float acos_d (float, at_exception_type * excep);


/* Given the point COORD, return the corresponding vector.  */

vector_type
make_vector(float_coord const c) {

    vector_type v;

    v.dx = c.x;
    v.dy = c.y;
    v.dz = c.z;

    return v;
}



/* And the converse: given a vector, return the corresponding point.  */

float_coord
vector_to_point(vector_type const v) {

    float_coord coord;

    coord.x = v.dx;
    coord.y = v.dy;
    coord.z = v.dz;

    return coord;
}



float
magnitude(vector_type const v) {

    return sqrt(SQR(v.dx) + SQR(v.dy) + SQR(v.dz));
}



vector_type
normalize(vector_type const v) {

    vector_type new_v;
    float const m = magnitude(v);

    if (m > 0.0) {
        new_v.dx = v.dx / m;
        new_v.dy = v.dy / m;
        new_v.dz = v.dz / m;
    } else {
        new_v.dx = v.dx;
        new_v.dy = v.dy;
        new_v.dz = v.dz;
    }
    
    return new_v;
}



vector_type
Vadd(vector_type const v1,
     vector_type const v2) {

    vector_type new_v;

    new_v.dx = v1.dx + v2.dx;
    new_v.dy = v1.dy + v2.dy;
    new_v.dz = v1.dz + v2.dz;

    return new_v;
}



float
Vdot(vector_type const v1,
     vector_type const v2) {

    return v1.dx * v2.dx + v1.dy * v2.dy + v1.dz * v2.dz;
}



vector_type
Vmult_scalar(vector_type const v,
             float       const r) {

    vector_type new_v;

    new_v.dx = v.dx * r;
    new_v.dy = v.dy * r;
    new_v.dz = v.dz * r;

    return new_v;
}



/* Given the IN_VECTOR and OUT_VECTOR, return the angle between them in
   degrees, in the range zero to 180.
*/

float
Vangle(vector_type         const in_vector, 
       vector_type         const out_vector,
       at_exception_type * const exP) {

    vector_type const v1 = normalize(in_vector);
    vector_type const v2 = normalize(out_vector);

    return acos_d(Vdot(v2, v1), exP);
}



float_coord
Vadd_point(float_coord const c,
           vector_type const v) {

    float_coord new_c;

    new_c.x = c.x + v.dx;
    new_c.y = c.y + v.dy;
    new_c.z = c.z + v.dz;

    return new_c;
}



float_coord
Vsubtract_point(float_coord const c,
                vector_type const v) {

    float_coord new_c;

    new_c.x = c.x - v.dx;
    new_c.y = c.y - v.dy;
    new_c.z = c.z - v.dz;

    return new_c;
}



pm_pixelcoord
Vadd_int_point(pm_pixelcoord const c,
               vector_type   const v) {

    pm_pixelcoord a;

    a.col = ROUND ((float) c.col + v.dx);
    a.row = ROUND ((float) c.row + v.dy);
    
    return a;
}



vector_type
Vabs(vector_type const v) {

    vector_type new_v;

    new_v.dx = (float) fabs (v.dx);
    new_v.dy = (float) fabs (v.dy);
    new_v.dz = (float) fabs (v.dz);

    return new_v;
}



/* Operations on points.  */

float_coord
Padd(float_coord const coord1,
     float_coord const coord2) {

    float_coord sum;

    sum.x = coord1.x + coord2.x;
    sum.y = coord1.y + coord2.y;
    sum.z = coord1.z + coord2.z;

    return sum;
}



float_coord
Pmult_scalar(float_coord const coord,
             float       const r) {

    float_coord answer;

    answer.x = coord.x * r;
    answer.y = coord.y * r;
    answer.z = coord.z * r;

    return answer;
}



vector_type
Psubtract(float_coord const c1,
          float_coord const c2) {

    vector_type v;

    v.dx = c1.x - c2.x;
    v.dy = c1.y - c2.y;
    v.dz = c1.z - c2.z;

    return v;
}



vector_type
Pdirection(float_coord const final,
           float_coord const initial) {

    return normalize(Psubtract(final, initial));
}



/* Operations on integer points.  */

vector_type
IPsubtract(pm_pixelcoord const coord1,
           pm_pixelcoord const coord2) {

    vector_type v;

    v.dx = (int) (coord1.col - coord2.col);
    v.dy = (int) (coord1.row - coord2.row);
    v.dz = 0.0;
    
    return v;
}



static float
acos_d(float               const v,
       at_exception_type * const excepP) {

    float vAdj;
    float a;
    float retval;

    if (epsilon_equal(v, 1.0))
        vAdj = 1.0;
    else if (epsilon_equal(v, -1.0))
        vAdj = -1.0;
    else
        vAdj = v;

    errno = 0;
    a = acos(vAdj);
    if (errno == ERANGE || errno == EDOM) {
        at_exception_fatal(excepP, strerror(errno));
        retval = 0.0;
    } else
        retval = a * 180.0 / M_PI;

    return retval;
}
