/* curve.h: data structures for the conversion from pixels to splines. */

#ifndef CURVE_H
#define CURVE_H

#include "autotrace.h"
#include "point.h"
#include "vector.h"

/* We are simultaneously manipulating two different representations of
   the same outline: one based on (x,y) positions in the plane, and one
   based on parametric splines.  (We are trying to match the latter to
   the former.)  Although the original (x,y)'s are pixel positions,
   i.e., integers, after filtering they are reals.  */

typedef struct {
    float_coord coord;
    float       t;
} point_type;



typedef struct curve {
/*----------------------------------------------------------------------------
  An ordered list of contiguous points in the raster, with no corners
  in it.  I.e. something that could reasonably be fit to a spline.
-----------------------------------------------------------------------------*/
    point_type *   point_list;
        /* Array of the points in the curve.  Malloc'ed.  Size is 'length'.
           if 'length' is zero, this is meaningless and no memory is
           allocated.
        */
    unsigned       length;
        /* Number of points in the curve */
    bool           cyclic;

    /* 'previous' and 'next' links are for the doubly linked list which is
       a chain of all curves in an outline.  The chain is a cycle for a
       closed outline and linear for an open outline.
    */
    struct curve * previous;
    struct curve * next;
} curve;

typedef struct curve * curve_type;

/* Get at the coordinates and the t values.  */
#define CURVE_POINT(c, n) ((c)->point_list[n].coord)
#define LAST_CURVE_POINT(c) ((c)->point_list[(c)->length-1].coord)
#define CURVE_T(c, n) ((c)->point_list[n].t)
#define LAST_CURVE_T(c) ((c)->point_list[(c)->length-1].t)

/* This is the length of `point_list'.  */
#define CURVE_LENGTH(c)  ((c)->length)

/* A curve is ``cyclic'' if it didn't have any corners, after all, so
   the last point is adjacent to the first.  */
#define CURVE_CYCLIC(c)  ((c)->cyclic)

/* If the curve is cyclic, the next and previous points should wrap
   around; otherwise, if we get to the end, we return CURVE_LENGTH and
   -1, respectively.  */
#define CURVE_NEXT(c, n)						\
  ((n) + 1 >= CURVE_LENGTH (c)						\
  ? CURVE_CYCLIC (c) ? ((n) + 1) % CURVE_LENGTH (c) : CURVE_LENGTH (c)	\
  : (n) + 1)
#define CURVE_PREV(c, n)						\
  ((signed int) (n) - 1 < 0							\
  ? CURVE_CYCLIC (c) ? (signed int) CURVE_LENGTH (c) + (signed int) (n) - 1 : -1\
  : (signed int) (n) - 1)

#define PREVIOUS_CURVE(c) ((c)->previous)
#define NEXT_CURVE(c) ((c)->next)


/* Return an entirely empty curve.  */
extern curve_type new_curve (void);

/* Return a curve the same as C, except without any points.  */
extern curve_type copy_most_of_curve (curve_type c);

void
move_curve(curve * const dstP,
           curve * const srcP);

void
free_curve(curve * const curveP);

/* Like `append_pixel', for a point in real coordinates.  */
void
append_point(curve_type  const curve,
             float_coord const coord);

/* Append the point P to the end of C's list.  */
void
append_pixel(curve_type    const c,
             pm_pixelcoord const p);

/* Write some or all, respectively, of the curve C in human-readable
   form to the log file, if logging is enabled.  */
extern void log_curve (curve_type c, bool print_t);
extern void log_entire_curve (curve_type c);

/* Display the curve C online, if displaying is enabled.  */
extern void display_curve (curve_type);



typedef struct {
/*----------------------------------------------------------------------------
   An ordered list of contiguous curves of a particular color.
-----------------------------------------------------------------------------*/
    curve ** data;
        /* data[i] is the handle of the ith curve in the list */
    unsigned length;
    bool     clockwise;
    pixel    color;
    bool     open;
        /* The curve list does not form a closed shape;  i.e. the last
           curve doesn't end where the first one starts.
        */
} curve_list_type;

/* Number of curves in the list.  */
#define CURVE_LIST_LENGTH(c_l)  ((c_l).length)
#define CURVE_LIST_EMPTY(c_l) ((c_l).length == 0)

/* Access the individual curves.  */
#define CURVE_LIST_ELT(c_l, n) ((c_l).data[n])
#define LAST_CURVE_LIST_ELT(c_l) ((c_l).data[CURVE_LIST_LENGTH (c_l) - 1])

/* Says whether the outline that this curve list represents moves
   clockwise or counterclockwise.  */
#define CURVE_LIST_CLOCKWISE(c_l) ((c_l).clockwise)


extern curve_list_type new_curve_list (void);

void
free_curve_list(curve_list_type * const curve_list);

extern void append_curve (curve_list_type *, curve_type);

/* And a character is a list of outlines.  I named this
   `curve_list_array_type' because `curve_list_list_type' seemed pretty
   monstrous.  */
typedef struct
{
  curve_list_type *data;
  unsigned length;
} curve_list_array_type;

/* Turns out we can use the same definitions for lists of lists as for
   just lists.  But we define the usual names, just in case.  */
#define CURVE_LIST_ARRAY_LENGTH CURVE_LIST_LENGTH
#define CURVE_LIST_ARRAY_ELT CURVE_LIST_ELT
#define LAST_CURVE_LIST_ARRAY_ELT LAST_CURVE_LIST_ELT

curve_list_array_type
new_curve_list_array(void);

void
free_curve_list_array(const curve_list_array_type * const curve_list_array,
                      at_progress_func                    notify_progress, 
                      void *                        const client_data);

void
append_curve_list(curve_list_array_type * const curve_list_array,
                  curve_list_type         const curve_list);

#endif

