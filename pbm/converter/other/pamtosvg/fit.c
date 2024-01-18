/* fit.c: turn a bitmap representation of a curve into a list of splines.
    Some of the ideas, but not the code, comes from the Phoenix thesis.
   See README for the reference.

   The code was partially derived from limn.

   Copyright (C) 1992 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

#include <math.h>
#include <limits.h>
#include <float.h>
#include <string.h>
#include <assert.h>

#include "pm_c_util.h"
#include "mallocvar.h"

#include "autotrace.h"
#include "fit.h"
#include "message.h"
#include "logreport.h"
#include "spline.h"
#include "vector.h"
#include "curve.h"
#include "pxl-outline.h"
#include "epsilon-equal.h"

#define CUBE(x) ((x) * (x) * (x))

/* We need to manipulate lists of array indices.  */

typedef struct index_list
{
  unsigned *data;
  unsigned length;
} index_list_type;

/* The usual accessor macros.  */
#define GET_INDEX(i_l, n)  ((i_l).data[n])
#define INDEX_LIST_LENGTH(i_l)  ((i_l).length)
#define GET_LAST_INDEX(i_l)  ((i_l).data[INDEX_LIST_LENGTH (i_l) - 1])




static pm_pixelcoord
real_to_int_coord(float_coord const real_coord) {
/*----------------------------------------------------------------------------
  Turn an real point into a integer one.
-----------------------------------------------------------------------------*/

    pm_pixelcoord int_coord;

    int_coord.col = ROUND(real_coord.x);
    int_coord.row = ROUND(real_coord.y);
    
    return int_coord;
}


/* Lists of array indices (well, that is what we use it for).  */

static index_list_type
new_index_list (void)
{
  index_list_type index_list;

  index_list.data = NULL;
  INDEX_LIST_LENGTH (index_list) = 0;

  return index_list;
}

static void
free_index_list (index_list_type *index_list)
{
  if (INDEX_LIST_LENGTH (*index_list) > 0)
    {
      free (index_list->data);
      index_list->data = NULL;
      INDEX_LIST_LENGTH (*index_list) = 0;
    }
}

static void
append_index (index_list_type *list, unsigned new_index)
{
  INDEX_LIST_LENGTH (*list)++;
  REALLOCARRAY_NOFAIL(list->data, INDEX_LIST_LENGTH(*list));
  list->data[INDEX_LIST_LENGTH (*list) - 1] = new_index;
}


/* Return the Euclidean distance between P1 and P2.  */

static float
distance (float_coord p1, float_coord p2)
{
  float x = p1.x - p2.x, y = p1.y - p2.y, z = p1.z - p2.z;
  return (float) sqrt (SQR(x) + SQR(y) + SQR(z));
}



static void
appendCorner(index_list_type *  const cornerListP,
             unsigned int       const pixelSeq,
             pixel_outline_type const outline,
             float              const angle,
             char               const logType) {

    pm_pixelcoord const coord = O_COORDINATE(outline, pixelSeq);

    append_index(cornerListP, pixelSeq);
    LOG4(" (%d,%d)%c%.3f", coord.col, coord.row, logType, angle);
}



static void
find_vectors(unsigned int       const test_index,
             pixel_outline_type const outline,
             vector_type *      const in,
             vector_type *      const out,
             unsigned int       const corner_surround) {
/*----------------------------------------------------------------------------
  Return the difference vectors coming in and going out of the outline
  OUTLINE at the point whose index is TEST_INDEX.  In Phoenix,
  Schneider looks at a single point on either side of the point we're
  considering.  That works for him because his points are not touching.
  But our points *are* touching, and so we have to look at
  `corner_surround' points on either side, to get a better picture of
  the outline's shape.
-----------------------------------------------------------------------------*/
    int i;
    unsigned n_done;
    pm_pixelcoord const candidate = O_COORDINATE(outline, test_index);

    in->dx  = in->dy  = in->dz  = 0.0;
    out->dx = out->dy = out->dz = 0.0;
    
    /* Add up the differences from p of the `corner_surround' points
       before p.
    */
    for (i = O_PREV(outline, test_index), n_done = 0;
         n_done < corner_surround;
         i = O_PREV(outline, i), ++n_done)
        *in = Vadd(*in, IPsubtract(O_COORDINATE(outline, i), candidate));
    
    /* And the points after p. */
    for (i = O_NEXT (outline, test_index), n_done = 0;
         n_done < corner_surround;
         i = O_NEXT(outline, i), ++n_done)
        *out = Vadd(*out, IPsubtract(O_COORDINATE(outline, i), candidate));
}



static void
lookAheadForBetterCorner(pixel_outline_type  const outline,
                         unsigned int        const basePixelSeq,
                         float               const baseCornerAngle,
                         unsigned int        const cornerSurround,
                         unsigned int        const cornerAlwaysThreshold,
                         unsigned int *      const highestExaminedP,
                         float *             const bestCornerAngleP,
                         unsigned int *      const bestCornerIndexP,
                         index_list_type *   const equallyGoodListP,
                         index_list_type *   const cornerListP,
                         at_exception_type * const exceptionP) {
/*----------------------------------------------------------------------------
   'basePixelSeq' is the sequence position within 'outline' of a pixel
   that has a sufficiently small angle (to wit 'baseCornerAngle') to
   be a corner.  We look ahead in 'outline' for an even better one.
   We'll look up to 'cornerSurround' pixels ahead.

   We return the pixel sequence of the best corner we find (which could
   be the base) as *bestCornerIndexP.  Its angle is *bestCornerAngleP.

   We return as *highestExaminedP the pixel sequence of the last pixel
   we examined in our search (Caller can use this information to avoid
   examining them again).

   And we have this really dirty side effect: If we encounter any
   corner whose angle is less than 'cornerAlwaysThreshold', we add
   that to the list *cornerListP along the way.
-----------------------------------------------------------------------------*/
    float bestCornerAngle;
    unsigned bestCornerIndex;
    index_list_type equallyGoodList;
    unsigned int q;
    unsigned int i;

    bestCornerIndex = basePixelSeq;     /* initial assumption */
    bestCornerAngle = baseCornerAngle;    /* initial assumption */
    
    equallyGoodList = new_index_list();
    
    q = basePixelSeq;
    i = basePixelSeq + 1;  /* Start with the next pixel */
    
    while (i < bestCornerIndex + cornerSurround &&
           i < O_LENGTH(outline) &&
           !at_exception_got_fatal(exceptionP)) {

        vector_type inVector, outVector;
        float cornerAngle;
        
        /* Check the angle.  */

        q = i % O_LENGTH(outline);
        find_vectors(q, outline, &inVector, &outVector, cornerSurround);
        cornerAngle = Vangle(inVector, outVector, exceptionP);
        if (!at_exception_got_fatal(exceptionP)) {
            /* Perhaps the angle is sufficiently small that we want to
               consider this a corner, even if it's not the best
               (unless we've already wrapped around in the search, in
               which case we have already added the corner, and we
               don't want to add it again).
            */
            if (cornerAngle <= cornerAlwaysThreshold && q >= basePixelSeq)
                appendCorner(cornerListP, q, outline, cornerAngle, '\\');

            if (epsilon_equal(cornerAngle, bestCornerAngle))
                append_index(&equallyGoodList, q);
            else if (cornerAngle < bestCornerAngle) {
                bestCornerAngle = cornerAngle;
                /* We want to check `cornerSurround' pixels beyond the
                   new best corner.
                */
                i = bestCornerIndex = q;
                free_index_list(&equallyGoodList);
                equallyGoodList = new_index_list();
            }
            ++i;
        }
    }
    *bestCornerAngleP = bestCornerAngle;
    *bestCornerIndexP = bestCornerIndex;
    *equallyGoodListP = equallyGoodList;
    *highestExaminedP = q;
}



static void
establishCornerSearchLimits(pixel_outline_type  const outline,
                            fitting_opts_type * const fittingOptsP,
                            unsigned int *      const firstP,
                            unsigned int *      const lastP) {
/*----------------------------------------------------------------------------
   Determine where in the outline 'outline' we should look for corners.
-----------------------------------------------------------------------------*/
    assert(O_LENGTH(outline) >= 1);
    assert(O_LENGTH(outline) - 1 >= fittingOptsP->corner_surround);

    *firstP = 0;
    *lastP  = O_LENGTH(outline) - 1;
    if (outline.open) {
        *firstP += fittingOptsP->corner_surround;
        *lastP  -= fittingOptsP->corner_surround;
    }
}



static void
remove_adjacent_corners(index_list_type *   const list,
                        unsigned int        const last_index,
                        bool                const remove_adj_corners,
                        at_exception_type * const exception) {
/*----------------------------------------------------------------------------
   Remove adjacent points from the index list LIST.  We do this by first
   sorting the list and then running through it.  Since these lists are
   quite short, a straight selection sort (e.g., p.139 of the Art of
   Computer Programming, vol.3) is good enough.  LAST_INDEX is the index
   of the last pixel on the outline, i.e., the next one is the first
   pixel. We need this for checking the adjacency of the last corner.

   We need to do this because the adjacent corners turn into
   two-pixel-long curves, which can be fit only by straight lines.
-----------------------------------------------------------------------------*/
  unsigned int j;
  unsigned int last;
  index_list_type new_list = new_index_list ();

  for (j = INDEX_LIST_LENGTH (*list) - 1; j > 0; j--)
    {
      unsigned search;
      unsigned temp;
      /* Find maximal element below `j'.  */
      unsigned max_index = j;

      for (search = 0; search < j; search++)
        if (GET_INDEX (*list, search) > GET_INDEX (*list, max_index))
          max_index = search;

      if (max_index != j)
        {
          temp = GET_INDEX (*list, j);
          GET_INDEX (*list, j) = GET_INDEX (*list, max_index);
          GET_INDEX (*list, max_index) = temp;
        }
    }

  /* The list is sorted.  Now look for adjacent entries.  Each time
     through the loop we insert the current entry and, if appropriate,
     the next entry.  */
  for (j = 0; j < INDEX_LIST_LENGTH (*list) - 1; j++)
    {
      unsigned current = GET_INDEX (*list, j);
      unsigned next = GET_INDEX (*list, j + 1);

      /* We should never have inserted the same element twice.  */
      /* assert (current != next); */

      if ((remove_adj_corners) && ((next == current + 1) || (next == current)))
        j++;

      append_index (&new_list, current);
    }

  /* Don't append the last element if it is 1) adjacent to the previous
     one; or 2) adjacent to the very first one.  */
  last = GET_LAST_INDEX (*list);
  if (INDEX_LIST_LENGTH (new_list) == 0
      || !(last == GET_LAST_INDEX (new_list) + 1
           || (last == last_index && GET_INDEX (*list, 0) == 0)))
    append_index (&new_list, last);

  free_index_list (list);
  *list = new_list;
}

/* A ``knee'' is a point which forms a ``right angle'' with its
   predecessor and successor.  See the documentation (the `Removing
   knees' section) for an example and more details.

   The argument CLOCKWISE tells us which direction we're moving.  (We
   can't figure that information out from just the single segment with
   which we are given to work.)

   We should never find two consecutive knees.

   Since the first and last points are corners (unless the curve is
   cyclic), it doesn't make sense to remove those.
*/

/* This evaluates to true if the vector V is zero in one direction and
   nonzero in the other.  */
#define ONLY_ONE_ZERO(v)                                                \
  (((v).dx == 0.0 && (v).dy != 0.0) || ((v).dy == 0.0 && (v).dx != 0.0))

/* There are four possible cases for knees, one for each of the four
   corners of a rectangle; and then the cases differ depending on which
   direction we are going around the curve.  The tests are listed here
   in the order of upper left, upper right, lower right, lower left.
   Perhaps there is some simple pattern to the
   clockwise/counterclockwise differences, but I don't see one.  */
#define CLOCKWISE_KNEE(prev_delta, next_delta)                                                  \
  ((prev_delta.dx == -1.0 && next_delta.dy == 1.0)                                              \
   || (prev_delta.dy == 1.0 && next_delta.dx == 1.0)                                    \
   || (prev_delta.dx == 1.0 && next_delta.dy == -1.0)                                   \
   || (prev_delta.dy == -1.0 && next_delta.dx == -1.0))

#define COUNTERCLOCKWISE_KNEE(prev_delta, next_delta)                                   \
  ((prev_delta.dy == 1.0 && next_delta.dx == -1.0)                                              \
   || (prev_delta.dx == 1.0 && next_delta.dy == 1.0)                                    \
   || (prev_delta.dy == -1.0 && next_delta.dx == 1.0)                                   \
   || (prev_delta.dx == -1.0 && next_delta.dy == -1.0))



static void
remove_knee_points(curve * const curveP,
                   bool    const clockwise) {

    unsigned int const offset = CURVE_CYCLIC(curveP) ? 0 : 1;
    curve * const trimmedCurveP = copy_most_of_curve(curveP);

    pm_pixelcoord previous;
    unsigned int i;

    if (!CURVE_CYCLIC(curveP))
        append_pixel(trimmedCurveP,
                     real_to_int_coord(CURVE_POINT(curveP, 0)));

    previous = real_to_int_coord(CURVE_POINT(curveP,
                                             CURVE_PREV(curveP, offset)));

    for (i = offset; i < CURVE_LENGTH(curveP) - offset; ++i) {
        pm_pixelcoord const current =
            real_to_int_coord(CURVE_POINT(curveP, i));
        pm_pixelcoord const next =
            real_to_int_coord(CURVE_POINT(curveP, CURVE_NEXT(curveP, i)));
        vector_type const prev_delta = IPsubtract(previous, current);
        vector_type const next_delta = IPsubtract(next, current);

        if (ONLY_ONE_ZERO(prev_delta) && ONLY_ONE_ZERO(next_delta)
            && ((clockwise && CLOCKWISE_KNEE(prev_delta, next_delta))
                || (!clockwise
                    && COUNTERCLOCKWISE_KNEE(prev_delta, next_delta))))
            LOG2(" (%d,%d)", current.col, current.row);
        else {
            previous = current;
            append_pixel(trimmedCurveP, current);
        }
    }

    if (!CURVE_CYCLIC(curveP))
        append_pixel(trimmedCurveP,
                     real_to_int_coord(LAST_CURVE_POINT(curveP)));

    if (CURVE_LENGTH(trimmedCurveP) == CURVE_LENGTH(curveP))
        LOG(" (none)");

    LOG(".\n");

    move_curve(curveP, trimmedCurveP);
}



static void
filter(curve *             const curveP,
       fitting_opts_type * const fittingOptsP) {
/*----------------------------------------------------------------------------
  Smooth the curve by adding in neighboring points.  Do this
  fittingOptsP->filter_iterations times.  But don't change the corners.
-----------------------------------------------------------------------------*/
    unsigned int const offset = CURVE_CYCLIC(curveP) ? 0 : 1;

    unsigned int iteration, thisPoint;
    float_coord prevNewPoint;
    
    /* We must have at least three points -- the previous one, the current
       one, and the next one.  But if we don't have at least five, we will
       probably collapse the curve down onto a single point, which means
       we won't be able to fit it with a spline.
    */
    if (CURVE_LENGTH(curveP) < 5) {
        LOG1("Length is %u, not enough to filter.\n", CURVE_LENGTH(curveP));
        return;
    }

    prevNewPoint.x = FLT_MAX;
    prevNewPoint.y = FLT_MAX;
    prevNewPoint.z = FLT_MAX;
    
    for (iteration = 0;
         iteration < fittingOptsP->filter_iterations;
         ++iteration) {
        curve * const newcurveP = copy_most_of_curve(curveP);

        bool collapsed;
        
        collapsed = false;  /* initial value */

        /* Keep the first point on the curve.  */
        if (offset)
            append_point(newcurveP, CURVE_POINT(curveP, 0));
        
        for (thisPoint = offset;
             thisPoint < CURVE_LENGTH(curveP) - offset;
             ++thisPoint) {
            vector_type in, out, sum;
            float_coord newPoint;
            
            /* Calculate the vectors in and out, computed by looking
               at n points on either side of this_point.  Experimental
               it was found that 2 is optimal.
            */

            signed int prev, prevprev; /* have to be signed */
            unsigned int next, nextnext;
            float_coord candidate = CURVE_POINT(curveP, thisPoint);
            
            prev = CURVE_PREV(curveP, thisPoint);
            prevprev = CURVE_PREV(curveP, prev);
            next = CURVE_NEXT(curveP, thisPoint);
            nextnext = CURVE_NEXT(curveP, next);
            
            /* Add up the differences from p of the `surround' points
               before p.
            */
            in.dx = in.dy = in.dz = 0.0;

            in = Vadd(in, Psubtract(CURVE_POINT(curveP, prev), candidate));
            if (prevprev >= 0)
                in = Vadd(in,
                          Psubtract(CURVE_POINT(curveP, prevprev), candidate));
            
            /* And the points after p.  Don't use more points after p than we
               ended up with before it.
            */
            out.dx = out.dy = out.dz = 0.0;
            
            out = Vadd(out, Psubtract(CURVE_POINT(curveP, next), candidate));
            if (nextnext < CURVE_LENGTH(curveP))
                out = Vadd(out,
                           Psubtract(CURVE_POINT(curveP, nextnext),
                                     candidate));
            
            /* Start with the old point.  */
            newPoint = candidate;
            sum = Vadd(in, out);
            /* We added 2*n+2 points, so we have to divide the sum by 2*n+2 */
            newPoint.x += sum.dx / 6;
            newPoint.y += sum.dy / 6;
            newPoint.z += sum.dz / 6;
            if (fabs(prevNewPoint.x - newPoint.x) < 0.3
                && fabs (prevNewPoint.y - newPoint.y) < 0.3
                && fabs (prevNewPoint.z - newPoint.z) < 0.3) {
                collapsed = true;
                break;
            }
            
            /* Put the newly computed point into a separate curve, so it
               doesn't affect future computation (on this iteration).
            */
            append_point(newcurveP, prevNewPoint = newPoint);
        }
        
        if (collapsed)
            free_curve(newcurveP);
        else {
            /* Just as with the first point, we have to keep the last
               point.
            */
            if (offset)
                append_point(newcurveP, LAST_CURVE_POINT(curveP));
            
            /* Set the original curve to the newly filtered one, and go
               again.
            */
            move_curve(curveP, newcurveP);
        }
    }
    log_curve(curveP, false);
}



static void
removeAdjacent(index_list_type *   const cornerListP,
               pixel_outline_type  const outline,
               fitting_opts_type * const fittingOptsP,
               at_exception_type * const exception) {
               
    /* We never want two corners next to each other, since the
       only way to fit such a ``curve'' would be with a straight
       line, which usually interrupts the continuity dreadfully.
    */

    if (INDEX_LIST_LENGTH(*cornerListP) > 0)
        remove_adjacent_corners(
            cornerListP,
            O_LENGTH(outline) - (outline.open ? 2 : 1),
            fittingOptsP->remove_adjacent_corners,
            exception);
}



static index_list_type
find_corners(pixel_outline_type  const outline,
             fitting_opts_type * const fittingOptsP,
             at_exception_type * const exceptionP) {

    /* We consider a point to be a corner if (1) the angle defined by
       the `corner_surround' points coming into it and going out from
       it is less than `corner_threshold' degrees, and no point within
       `corner_surround' points has a smaller angle; or (2) the angle
       is less than `corner_always_threshold' degrees.
    */
    unsigned int p;
    unsigned int firstPixelSeq, lastPixelSeq;
    index_list_type cornerList;

    cornerList = new_index_list();

    if (O_LENGTH(outline) <= fittingOptsP->corner_surround * 2 + 1)
        return cornerList;

    establishCornerSearchLimits(outline, fittingOptsP,
                                &firstPixelSeq, &lastPixelSeq);
    
    /* Consider each pixel on the outline in turn.  */
    for (p = firstPixelSeq; p <= lastPixelSeq;) {
        vector_type inVector, outVector;
        float cornerAngle;

        /* Check if the angle is small enough.  */
        find_vectors(p, outline, &inVector, &outVector,
                     fittingOptsP->corner_surround);
        cornerAngle = Vangle(inVector, outVector, exceptionP);
        if (at_exception_got_fatal(exceptionP))
            goto cleanup;

        if (fabs(cornerAngle) <= fittingOptsP->corner_threshold) {
            /* We want to keep looking, instead of just appending the
               first pixel we find with a small enough angle, since there
               might be another corner within `corner_surround' pixels, with
               a smaller angle.  If that is the case, we want that one.

               If we come across a corner that is just as good as the
               best one, we should make it a corner, too.  This
               happens, for example, at the points on the `W' in some
               typefaces, where the "points" are flat.
            */
            float bestCornerAngle;
            unsigned bestCornerIndex;
            index_list_type equallyGoodList;
            unsigned int q;

            if (cornerAngle <= fittingOptsP->corner_always_threshold)
                /* The angle is sufficiently small that we want to
                   consider this a corner, even if it's not the best.
                */
                appendCorner(&cornerList, p, outline, cornerAngle, '\\');

            lookAheadForBetterCorner(outline, p, cornerAngle,
                                     fittingOptsP->corner_surround,
                                     fittingOptsP->corner_always_threshold,
                                     &q,
                                     &bestCornerAngle, &bestCornerIndex,
                                     &equallyGoodList,
                                     &cornerList,
                                     exceptionP);

            if (at_exception_got_fatal(exceptionP))
                goto cleanup;

            /* `q' is the index of the last point lookAhead checked.
               He added the corner if `bestCornerAngle' is less than
               `corner_always_threshold'.  If we've wrapped around, we
               added the corner on the first pass.  Otherwise, we add
               the corner now.
            */
            if (bestCornerAngle > fittingOptsP->corner_always_threshold
                && bestCornerIndex >= p) {

                unsigned int j;
                
                appendCorner(&cornerList, bestCornerIndex,
                             outline, bestCornerAngle, '/');
                
                for (j = 0; j < INDEX_LIST_LENGTH (equallyGoodList); ++j)
                    appendCorner(&cornerList, GET_INDEX(equallyGoodList, j),
                                 outline, bestCornerAngle, '@');
            }
            free_index_list(&equallyGoodList);

            /* If we wrapped around in our search, we're done;
               otherwise, we move on to the pixel after the highest
               one we just checked.
            */
            p = (q < p) ? O_LENGTH(outline) : q + 1;
        } else
            ++p;
    }
    removeAdjacent(&cornerList, outline, fittingOptsP, exceptionP);

cleanup:  
    return cornerList;
}



static void
makeOutlineOneCurve(pixel_outline_type const outline,
                    curve_list_type *  const curveListP) {
/*----------------------------------------------------------------------------
   Add to *curveListP a single curve that represents the outline 'outline'.

   That curve does not have beginning and ending slope information.
-----------------------------------------------------------------------------*/
    curve * curveP;
    unsigned int pixelSeq;

    curveP = new_curve();

    for (pixelSeq = 0; pixelSeq < O_LENGTH(outline); ++pixelSeq)
        append_pixel(curveP, O_COORDINATE(outline, pixelSeq));
    
    if (outline.open)
        CURVE_CYCLIC(curveP) = false;
    else
        CURVE_CYCLIC(curveP) = true;
    
    /* Make it a one-curve cycle */
    NEXT_CURVE(curveP)     = curveP;
    PREVIOUS_CURVE(curveP) = curveP;

    append_curve(curveListP, curveP);
}



static void
addCurveStartingAtCorner(pixel_outline_type const outline,
                         index_list_type    const cornerList,
                         unsigned int       const cornerSeq,
                         curve_list_type *  const curveListP,
                         curve **           const curCurvePP) {
/*----------------------------------------------------------------------------
   Add to the list *curveListP a new curve that starts at the cornerSeq'th
   corner in outline 'outline' (whose corners are 'cornerList') and
   goes to the next corner (or the end of the outline if no next corner).

   Furthermore, add that curve to the curve chain whose end is pointed
   to by *curCurvePP (NULL means chain is empty).

   Don't include beginning and ending slope information for that curve.
-----------------------------------------------------------------------------*/
    unsigned int const cornerPixelSeq = GET_INDEX(cornerList, cornerSeq);
    
    unsigned int lastPixelSeq;
    curve * curveP;
    unsigned int pixelSeq;
    
    if (cornerSeq + 1 >= cornerList.length)
        /* No more corners, so we go through the end of the outline. */
        lastPixelSeq = O_LENGTH(outline) - 1;
    else
        /* Go through the next corner */
        lastPixelSeq = GET_INDEX(cornerList, cornerSeq + 1);
    
    curveP = new_curve();

    for (pixelSeq = cornerPixelSeq; pixelSeq <= lastPixelSeq; ++pixelSeq)
        append_pixel(curveP, O_COORDINATE(outline, pixelSeq));
    
    append_curve(curveListP, curveP);
    {
        /* Add the new curve to the outline chain */

        curve * const oldCurCurveP = *curCurvePP;

        if (oldCurCurveP) {
            NEXT_CURVE(oldCurCurveP) = curveP;
            PREVIOUS_CURVE(curveP)   = oldCurCurveP;
        }
        *curCurvePP = curveP;
    }
}



static void
divideOutlineWithCorners(pixel_outline_type const outline,
                         index_list_type    const cornerList,
                         curve_list_type *  const curveListP) {
/*----------------------------------------------------------------------------
   Divide the outline 'outline' into curves at the corner points
   'cornerList' and add each curve to *curveListP.

   Each curve contains the corners at each end.

   The last curve is special.  It consists of the pixels (inclusive)
   between the last corner and the end of the outline, and the
   beginning of the outline and the first corner.

   We link the curves in a chain.  If the outline (and therefore the
   curve list) is closed, the chain is a cycle of all the curves.  If
   it is open, the chain is a linear chain of all the curves except
   the last one (the one that goes from the last corner to the first
   corner).

   Assume there is at least one corner.

   The curves do not have beginning and ending slope information.
-----------------------------------------------------------------------------*/
    unsigned int const firstCurveSeq = CURVE_LIST_LENGTH(*curveListP);
        /* Index in curve list of the first curve we add */
    unsigned int cornerSeq;
    curve * curCurveP;
        /* Pointer to the curve we most recently added for this outline.
           Null if none
        */

    assert(cornerList.length > 0);

    curCurveP = NULL;  /* No curves in outline chain yet */

    if (outline.open) {
        /* Start with a curve that contains the points up to the first
           corner
        */
        curve * curveP;
        unsigned int pixelSeq;
        
        curveP = new_curve();

        for (pixelSeq = 0; pixelSeq <= GET_INDEX(cornerList, 0); ++pixelSeq)
            append_pixel(curveP, O_COORDINATE(outline, pixelSeq));

        append_curve(curveListP, curveP);
        curCurveP = curveP;  /* Only curve in outline chain now */
    } else {
        /* We'll pick up the pixels before the first corner at the end */
    }
    /* Add to the list a curve that starts at each corner and goes
       through the following corner, or the end of the outline if
       there is no following corner.  Do it in order of the corners.
    */
    for (cornerSeq = 0; cornerSeq < cornerList.length; ++cornerSeq)
        addCurveStartingAtCorner(outline, cornerList, cornerSeq, curveListP,
                                 &curCurveP);

    if (!outline.open) {
        /* Come around to the start of the curve list -- add the pixels
           before the first corner to the last curve, and chain the last
           curve to the first one.
        */
        curve * const firstCurveP = CURVE_LIST_ELT(*curveListP, firstCurveSeq);

        unsigned int pixelSeq;

        for (pixelSeq = 0; pixelSeq <= GET_INDEX(cornerList, 0); ++pixelSeq)
            append_pixel(curCurveP, O_COORDINATE(outline, pixelSeq));

        NEXT_CURVE(curCurveP)       = firstCurveP;
        PREVIOUS_CURVE(firstCurveP) = curCurveP;
    }
}



static curve_list_array_type
split_at_corners(pixel_outline_list_type const pixel_list,
                 fitting_opts_type *     const fitting_opts,
                 at_exception_type *     const exception) {
/*----------------------------------------------------------------------------
   Find the corners in PIXEL_LIST, the list of points.  (Presumably we
   can't fit a single spline around a corner.)  The general strategy
   is to look through all the points, remembering which we want to
   consider corners.  Then go through that list, producing the
   curve_list.  This is dictated by the fact that PIXEL_LIST does not
   necessarily start on a corner---it just starts at the character's
   first outline pixel, going left-to-right, top-to-bottom.  But we
   want all our splines to start and end on real corners.

   For example, consider the top of a capital `C' (this is in cmss20):
                     x
                     ***********
                  ******************

   PIXEL_LIST will start at the pixel below the `x'.  If we considered
   this pixel a corner, we would wind up matching a very small segment
   from there to the end of the line, probably as a straight line, which
   is certainly not what we want.

   PIXEL_LIST has one element for each closed outline on the character.
   To preserve this information, we return an array of curve_lists, one
   element (which in turn consists of several curves, one between each
   pair of corners) for each element in PIXEL_LIST.

   The curves we return do not have beginning and ending slope
   information.
-----------------------------------------------------------------------------*/
    unsigned outlineSeq;
    curve_list_array_type curve_array;

    curve_array = new_curve_list_array();

    LOG("\nFinding corners:\n");

    for (outlineSeq = 0;
         outlineSeq < O_LIST_LENGTH(pixel_list);
         ++outlineSeq) {

        pixel_outline_type const outline =
            O_LIST_OUTLINE(pixel_list, outlineSeq);

        index_list_type corner_list;
        curve_list_type curve_list;

        curve_list = new_curve_list();

        CURVE_LIST_CLOCKWISE(curve_list) = O_CLOCKWISE(outline);
        curve_list.color = outline.color;
        curve_list.open  = outline.open;

        LOG1("#%u:", outlineSeq);
        
        /* If the outline does not have enough points, we can't do
           anything.  The endpoints of the outlines are automatically
           corners.  We need at least `corner_surround' more pixels on
           either side of a point before it is conceivable that we might
           want another corner.
        */
        if (O_LENGTH(outline) > fitting_opts->corner_surround * 2 + 2)
            corner_list = find_corners(outline, fitting_opts, exception);

        else {
            int const surround = (O_LENGTH(outline) - 3) / 2;
            if (surround >= 2) {
                unsigned int const save_corner_surround =
                    fitting_opts->corner_surround;
                fitting_opts->corner_surround = surround;
                corner_list = find_corners(outline, fitting_opts, exception);
                fitting_opts->corner_surround = save_corner_surround;
            } else {
                corner_list.length = 0;
                corner_list.data = NULL;
            }
        }

        if (corner_list.length == 0)
            /* No corners.  Use all of the pixel outline as the one curve. */
            makeOutlineOneCurve(outline, &curve_list);
        else
            divideOutlineWithCorners(outline, corner_list, &curve_list);
        
        LOG1(" [%u].\n", corner_list.length);
        free_index_list(&corner_list);

        /* And now add the just-completed curve list to the array.  */
        append_curve_list(&curve_array, curve_list);
    }

    return curve_array;
}



static void
removeKnees(curve_list_type const curveList) {
/*----------------------------------------------------------------------------
  Remove the extraneous ``knee'' points before filtering.  Since the
  corners have already been found, we don't need to worry about
  removing a point that should be a corner.
-----------------------------------------------------------------------------*/
    unsigned int curveSeq;
    
    LOG("\nRemoving knees:\n");
    for (curveSeq = 0; curveSeq < curveList.length; ++curveSeq) {
        LOG1("#%u:", curveSeq);
        remove_knee_points(CURVE_LIST_ELT(curveList, curveSeq),
                           CURVE_LIST_CLOCKWISE(curveList));
    }
}
    


static void
computePointWeights(curve_list_type     const curveList,
                    fitting_opts_type * const fittingOptsP,
                    distance_map_type * const distP) {

    unsigned int const height = distP->height;

    unsigned int curveSeq;
    
    for (curveSeq = 0; curveSeq < curveList.length; ++curveSeq) {
        unsigned pointSeq;
        curve_type const curve = CURVE_LIST_ELT(curveList, curveSeq);
        for (pointSeq = 0; pointSeq < CURVE_LENGTH(curve); ++pointSeq) {
            float_coord * const coordP = &CURVE_POINT(curve, pointSeq);
            unsigned int x = coordP->x;
            unsigned int y = height - (unsigned int)coordP->y - 1;
            
            float width, w;

            /* Each (x, y) is a point on the skeleton of the curve, which
               might be offset from the true centerline, where the width
               is maximal.  Therefore, use as the local line width the
               maximum distance over the neighborhood of (x, y). 
            */
            width = distP->d[y][x];  /* initial value */
            if (y - 1 >= 0) {
                if ((w = distP->d[y-1][x]) > width)
                    width = w;
                if (x - 1 >= 0) {
                    if ((w = distP->d[y][x-1]) > width)
                        width = w;
                    if ((w = distP->d[y-1][x-1]) > width)
                        width = w;
                }
                if (x + 1 < distP->width) {
                    if ((w = distP->d[y][x+1]) > width)
                        width = w;
                    if ((w = distP->d[y-1][x+1]) > width)
                        width = w;
                }
            }
            if (y + 1 < height) {
                if ((w = distP->d[y+1][x]) > width)
                    width = w;
                if (x - 1 >= 0 && (w = distP->d[y+1][x-1]) > width)
                    width = w;
                if (x + 1 < distP->width && (w = distP->d[y+1][x+1]) > width)
                    width = w;
            }
            coordP->z = width * (fittingOptsP->width_weight_factor);
        }
    }
}



static void
filterCurves(curve_list_type     const curveList,
             fitting_opts_type * const fittingOptsP) {
             
    unsigned int curveSeq;

    LOG("\nFiltering curves:\n");

    for (curveSeq = 0; curveSeq < curveList.length; ++curveSeq) {
        LOG1("#%u: ", curveSeq);
        filter(CURVE_LIST_ELT(curveList, curveSeq), fittingOptsP);
    }
}



static void
logSplinesForCurve(unsigned int     const curveSeq,
                   spline_list_type const curveSplines) {

    unsigned int splineSeq;

    LOG1("Fitted splines for curve #%u:\n", curveSeq);
    for (splineSeq = 0;
         splineSeq < SPLINE_LIST_LENGTH(curveSplines);
         ++splineSeq) {
        LOG1("  %u: ", splineSeq);
        if (log_file)
            print_spline(log_file, SPLINE_LIST_ELT(curveSplines, splineSeq));
    }
}     
       


static void
change_bad_lines(spline_list_type *        const spline_list,
                 const fitting_opts_type * const fitting_opts) {

/* Unfortunately, we cannot tell in isolation whether a given spline
   should be changed to a line or not.  That can only be known after the
   entire curve has been fit to a list of splines.  (The curve is the
   pixel outline between two corners.)  After subdividing the curve, a
   line may very well fit a portion of the curve just as well as the
   spline---but unless a spline is truly close to being a line, it
   should not be combined with other lines.  */

  unsigned this_spline;
  bool found_cubic = false;
  unsigned length = SPLINE_LIST_LENGTH (*spline_list);

  LOG1 ("\nChecking for bad lines (length %u):\n", length);

  /* First see if there are any splines in the fitted shape.  */
  for (this_spline = 0; this_spline < length; this_spline++)
    {
      if (SPLINE_DEGREE (SPLINE_LIST_ELT (*spline_list, this_spline)) ==
       CUBICTYPE)
        {
          found_cubic = true;
          break;
        }
    }

  /* If so, change lines back to splines (we haven't done anything to
     their control points, so we only have to change the degree) unless
     the spline is close enough to being a line.  */
  if (found_cubic)
    for (this_spline = 0; this_spline < length; this_spline++)
      {
        spline_type s = SPLINE_LIST_ELT (*spline_list, this_spline);

        if (SPLINE_DEGREE (s) == LINEARTYPE)
          {
            LOG1 ("  #%u: ", this_spline);
            if (SPLINE_LINEARITY (s) > fitting_opts->line_reversion_threshold)
              {
                LOG ("reverted, ");
                SPLINE_DEGREE (SPLINE_LIST_ELT (*spline_list, this_spline))
                  = CUBICTYPE;
              }
            LOG1 ("linearity %.3f.\n", SPLINE_LINEARITY (s));
          }
      }
    else
      LOG ("  No lines.\n");
}



static bool
spline_linear_enough(spline_type *             const spline,
                     curve_type                const curve,
                     const fitting_opts_type * const fitting_opts) {

/* Supposing that we have accepted the error, another question arises:
   would we be better off just using a straight line?  */

  float A, B, C;
  unsigned this_point;
  float dist = 0.0, start_end_dist, threshold;

  LOG ("Checking linearity:\n");

  A = END_POINT(*spline).x - START_POINT(*spline).x;
  B = END_POINT(*spline).y - START_POINT(*spline).y;
  C = END_POINT(*spline).z - START_POINT(*spline).z;

  start_end_dist = (float) (SQR(A) + SQR(B) + SQR(C));
  LOG1 ("start_end_distance is %.3f.\n", sqrt(start_end_dist));

  LOG3 ("  Line endpoints are (%.3f, %.3f, %.3f) and ", START_POINT(*spline).x, START_POINT(*spline).y, START_POINT(*spline).z);
  LOG3 ("(%.3f, %.3f, %.3f)\n", END_POINT(*spline).x, END_POINT(*spline).y, END_POINT(*spline).z);

  /* LOG3 ("  Line is %.3fx + %.3fy + %.3f = 0.\n", A, B, C); */

  for (this_point = 0; this_point < CURVE_LENGTH (curve); this_point++)
    {
      float a, b, c, w;
      float t = CURVE_T (curve, this_point);
      float_coord spline_point = evaluate_spline (*spline, t);

      a = spline_point.x - START_POINT(*spline).x;
      b = spline_point.y - START_POINT(*spline).y;
      c = spline_point.z - START_POINT(*spline).z;
      w = (A*a + B*b + C*c) / start_end_dist;

      dist += (float)sqrt(SQR(a-A*w) + SQR(b-B*w) + SQR(c-C*w));
    }
  LOG1 ("  Total distance is %.3f, ", dist);

  dist /= (CURVE_LENGTH (curve) - 1);
  LOG1 ("which is %.3f normalized.\n", dist);

  /* We want reversion of short curves to splines to be more likely than
     reversion of long curves, hence the second division by the curve
     length, for use in `change_bad_lines'.  */
  SPLINE_LINEARITY (*spline) = dist;
  LOG1 ("  Final linearity: %.3f.\n", SPLINE_LINEARITY (*spline));
  if (start_end_dist * (float) 0.5 > fitting_opts->line_threshold)
    threshold = fitting_opts->line_threshold;
  else
    threshold = start_end_dist * (float) 0.5;
  LOG1 ("threshold is %.3f .\n", threshold);
  if (dist < threshold)
    return true;
  else
    return false;
}



/* Forward declaration for recursion */

static spline_list_type *
fitCurve(curve *                   const curveP,
         vector_type               const begSlope,
         vector_type               const endSlope,
         const fitting_opts_type * const fittingOptsP,
         at_exception_type *       const exceptionP);



static spline_list_type *
fitWithLine(curve * const curveP) {
/*----------------------------------------------------------------------------
  Return a list of splines that fit curve *curveP in a very simple way:
  a single spline which is a straight line through the first and last
  points on the curve.

  This simplicity is useful only on a very short curve.
-----------------------------------------------------------------------------*/
    spline_type line;

    LOG("Fitting with straight line:\n");

    SPLINE_DEGREE(line) = LINEARTYPE;
    START_POINT(line)   = CONTROL1(line) = CURVE_POINT(curveP, 0);
    END_POINT(line)     = CONTROL2(line) = LAST_CURVE_POINT(curveP);

    /* Make sure that this line is never changed to a cubic.  */
    SPLINE_LINEARITY(line) = 0;

    if (log_file) {
        LOG("  ");
        print_spline(log_file, line);
    }

    return new_spline_list_with_spline(line);
}



#define B0(t) CUBE ((float) 1.0 - (t))
#define B1(t) ((float) 3.0 * (t) * SQR ((float) 1.0 - (t)))
#define B2(t) ((float) 3.0 * SQR (t) * ((float) 1.0 - (t)))
#define B3(t) CUBE (t)

static spline_type
fitOneSpline(curve *             const curveP, 
             vector_type         const begSlope,
             vector_type         const endSlope,
             at_exception_type * const exceptionP) {
/*----------------------------------------------------------------------------
  Return a spline that fits the points of curve *curveP,
  with slope 'begSlope' at its beginning and 'endSlope' at its end.

  Make it a cubic spline.
-----------------------------------------------------------------------------*/
    /* We already have the start and end points of the spline, so all
      we need are the control points.  And we know in what direction
      each control point is from its respective end point, so all we
      need to figure out is its distance.  (The control point's
      distance from the end point is an indication of how long the
      curve goes in its direction).

      We call the distance from an end point to the associated control
      point "alpha".

      We want to find starting and ending alpha that minimize the
      least-square error in approximating *curveP with the spline.

      How we do that is a complete mystery to me, but the original author
      said to see pp.57--59 of the Phoenix thesis.  I haven't seen that.

      In our expression of the math here, we use a struct with "beg" and
      "end" members where the paper uses a matrix with "1" and "2"
      subscripts, respectively.  A C array is a closer match to a math
      matrix, but we think the struct is easier to read.

      The B?(t) here corresponds to B_i^3(U_i) there.
      The Bernstein polynomials of degree n are defined by
      B_i^n(t) = { n \choose i } t^i (1-t)^{n-i}, i = 0..n

    */
    struct vectorPair {
        vector_type beg;
        vector_type end;
    };
    struct vectorPair tang;

    float X_Cend_det, Cbeg_X_det, C_det;
    spline_type spline;
    vector_type begVector, endVector;
    unsigned i;
    struct vectorPair * A;  /* malloc'ed array */
        /* I don't know the meaning of this array, but it is one entry for
           each point in the curve (A[i] is for the ith point in the curve).
        */
    struct {
        struct { float beg; float end; } beg;
        struct { float beg; float end; } end;
    } C;
    struct { float beg; float end; } X;

    tang.beg = begSlope; tang.end = endSlope;

    MALLOCARRAY_NOFAIL(A, CURVE_LENGTH(curveP));

    BEG_POINT(spline) = CURVE_POINT(curveP, 0);
    END_POINT(spline) = LAST_CURVE_POINT(curveP);
    begVector = make_vector(BEG_POINT(spline));
    endVector = make_vector(END_POINT(spline));

    for (i = 0; i < CURVE_LENGTH(curveP); ++i) {
        A[i].beg = Vmult_scalar(tang.beg, B1(CURVE_T(curveP, i)));
        A[i].end = Vmult_scalar(tang.end, B2(CURVE_T(curveP, i)));
    }

    C.beg.beg = 0.0; C.beg.end = 0.0; C.end.end = 0.0;  /* initial value */

    X.beg = 0.0; X.end = 0.0; /* initial value */

    for (i = 0; i < CURVE_LENGTH(curveP); ++i) {
        struct vectorPair * const AP = &A[i];
        vector_type temp, temp0, temp1, temp2, temp3;

        C.beg.beg += Vdot(AP->beg, AP->beg);
        C.beg.end += Vdot(AP->beg, AP->end);
        /* C.end.beg = Vdot(AP->end, AP->beg) is done outside of loop */
        C.end.end += Vdot(AP->end, AP->end);

        /* Now the right-hand side of the equation in the paper.  */
        temp0 = Vmult_scalar(begVector, B0(CURVE_T(curveP, i)));
        temp1 = Vmult_scalar(begVector, B1(CURVE_T(curveP, i)));
        temp2 = Vmult_scalar(endVector, B2(CURVE_T(curveP, i)));
        temp3 = Vmult_scalar(endVector, B3(CURVE_T(curveP, i)));

        temp = make_vector(
            Vsubtract_point(CURVE_POINT(curveP, i),
                            Vadd(temp0, Vadd(temp1, Vadd(temp2, temp3)))));

        X.beg += Vdot(temp, AP->beg);
        X.end += Vdot(temp, AP->end);
    }
    free(A);

    C.end.beg = C.beg.end;
    
    X_Cend_det  = X.beg * C.end.end - X.end * C.beg.end;
    Cbeg_X_det  = C.beg.beg * X.end - C.beg.end * X.beg;
    C_det = C.beg.beg * C.end.end - C.end.beg * C.beg.end;
    if (C_det == 0.0) {
        LOG("zero determinant of C matrix");
        at_exception_fatal(exceptionP, "zero determinant of C matrix");
    } else {
        struct { float beg; float end; } alpha;  /* constant */
        alpha.beg = X_Cend_det / C_det;
        alpha.end = Cbeg_X_det / C_det;

        CONTROL1(spline) = Vadd_point(BEG_POINT(spline),
                                      Vmult_scalar(tang.beg, alpha.beg));
        CONTROL2(spline) = Vadd_point(END_POINT(spline),
                                      Vmult_scalar(tang.end, alpha.end));
        SPLINE_DEGREE(spline) = CUBICTYPE;
    }        
    return spline;
}



static void
logSplineFit(spline_type const spline) {

    if (SPLINE_DEGREE(spline) == LINEARTYPE)
        LOG("  fitted to line:\n");
    else
        LOG("  fitted to spline:\n");
    
    if (log_file) {
        LOG ("    ");
        print_spline (log_file, spline);
    }
}



static vector_type
findHalfTangentBeg(curve *      const curveP,
                   unsigned int const tangentSurround) {
/*----------------------------------------------------------------------------
  Find the slope in the vicinity of the beginning of the curve
  *curveP.

  To wit, this is the mean slope between the first point on the curve and
  each of the 'tangentSurround' following points, up to half the curve.

  For example, if 'tangentSurround' is 3 and the curve is 10 points
  long, we imagine a line through Point 0 and Point 1, another through
  Point 0 and Point 2, and a third through Point 0 and Point 3.  We
  return the mean of the slopes of those 3 lines.
-----------------------------------------------------------------------------*/
    float_coord const tangentPoint = CURVE_POINT(curveP, 0);
    vector_type const zeroZero = { 0.0, 0.0 };
    unsigned int const surround =
        MIN(CURVE_LENGTH(curveP) / 2, tangentSurround);

    unsigned int p;
    vector_type sum;
    vector_type mean;
    unsigned int n;

    for (p = 0, n = 0, sum = zeroZero; p < surround; ++p) {
        unsigned int const thisIndex = p + 1;
        float_coord  const thisPoint = CURVE_POINT(curveP, thisIndex);

        /* Perhaps we should weight the tangent from `thisPoint' by some
           factor dependent on the distance from the tangent point.
        */
        sum = Vadd(sum, Pdirection(thisPoint, tangentPoint));
        ++n;
    }

    mean = Vmult_scalar(sum, 1.0 / n);

    return mean;
}



static vector_type
findHalfTangentEnd(curve *      const curveP,
                   unsigned int const tangentSurround) {
/*----------------------------------------------------------------------------
  Find the slope in the vicinity of the end of the curve
  *curveP.

  This is analogous to findHalfTangentBeg(), but at the other end of the
  curve.
-----------------------------------------------------------------------------*/
    float_coord const tangentPoint =
        CURVE_POINT(curveP, CURVE_LENGTH(curveP) - 1);
    vector_type const zeroZero = { 0.0, 0.0 };
    unsigned int const surround =
        MIN(CURVE_LENGTH(curveP) / 2, tangentSurround);

    unsigned int p;
    vector_type sum;
    vector_type mean;
    unsigned int n;

    for (p = 0, n = 0, sum = zeroZero; p < surround; ++p) {
        unsigned int const thisIndex = CURVE_LENGTH(curveP) - 1 - p;
        float_coord  const thisPoint = CURVE_POINT(curveP, thisIndex);

        sum = Vadd(sum, Pdirection(tangentPoint, thisPoint));
        ++n;
    }

    mean = Vmult_scalar(sum, 1.0 / n);

    return mean;
}



static vector_type
findHalfTangent(bool         const toStartPoint,
                curve *      const curveP,
                unsigned int const tangentSurround) {

    if (toStartPoint)
        return findHalfTangentBeg(curveP, tangentSurround);
    else
        return findHalfTangentEnd(curveP, tangentSurround);
}



static void
findTangent(curve *       const curveP,
            bool          const toStartPoint,
            curve *       const adjacentCurveP,
            unsigned int  const tangentSurroundArg,
            vector_type * const tangentP) {
/*----------------------------------------------------------------------------
  Find an approximation to the slope of *curveP (i.e. slope of tangent
  line) at an endpoint (the first point if 'toStartPoint' is true,
  else the last).

  If 'adjacentCurveP' is non-null, consider points on the adjacent
  curve to *curveP.  The adjacent curve is *adjacentCurveP.  Adjacent
  means the previous curve in the outline chain for the slope at the
  start point ('toStartPoint' == true), the next curve otherwise.
  If *curveP is cyclic, then it is its own adjacent curve.
  
  It is important to compute an accurate approximation, because the
  control points that we eventually decide upon to fit the curve will
  be placed on the half-lines defined by the slopes and endpoints, and
  we never recompute the tangent after this.
-----------------------------------------------------------------------------*/
    vector_type slope;
    unsigned int tangentSurround;

    LOG2("  tangent to %s of curve %lx: ",
         toStartPoint ? "start" : "end", (unsigned long)curveP);

    tangentSurround = tangentSurroundArg;  /* initial value */
    do {
        slope = findHalfTangent(toStartPoint, curveP, tangentSurround);

        if (adjacentCurveP) {
            vector_type const slopeAdj =
                findHalfTangent(!toStartPoint, adjacentCurveP,
                                tangentSurround);
               
            LOG3("(adjacent curve half tangent (%.3f,%.3f,%.3f)) ",
                 slopeAdj.dx, slopeAdj.dy, slopeAdj.dz);
            slope = Vmult_scalar(Vadd(slope, slopeAdj), 0.5);
        }
        --tangentSurround;
    } while (slope.dx == 0.0 && slope.dy == 0.0);

    *tangentP = slope;
    
    LOG3("(%.3f,%.3f,%.3f).\n",
         tangentP->dx, tangentP->dy, tangentP->dz);
}



static void
findError(curve *             const curveP,
          spline_type         const spline,
          float *             const errorP,
          unsigned int *      const worstPointP,
          at_exception_type * const exceptionP) {
/*----------------------------------------------------------------------------
  Tell how good a fit 'spline' is for *curveP.
  
  Return the error (maximum Euclidian distance between a point on
  *curveP and the corresponding point on 'spline') as *errorP and the
  sequence number of the point on the curve where the error is
  greatest as *worstPointP.

  If there are multiple equally bad points, return an arbitrary one of
  them as *worstPointP.
-----------------------------------------------------------------------------*/
    unsigned int thisPoint;
    float totalError;
    float worstError;
    unsigned int worstPoint;

    assert(CURVE_LENGTH(curveP) > 0);

    totalError = 0.0;  /* initial value */
    worstError = FLT_MIN; /* initial value */
    worstPoint = 0;
        
    for (thisPoint = 0; thisPoint < CURVE_LENGTH(curveP); ++thisPoint) {
        float_coord const curvePoint = CURVE_POINT(curveP, thisPoint);
        float const t = CURVE_T(curveP, thisPoint);
        float_coord const splinePoint = evaluate_spline(spline, t);
        float const thisError = distance(curvePoint, splinePoint);
        if (thisError >= worstError) {
            worstPoint = thisPoint;
            worstError = thisError;
        }
        totalError += thisError;
    }

    if (epsilon_equal(totalError, 0.0))
        LOG("  Every point fits perfectly.\n");
    else {
        LOG5("  Worst error (at (%.3f,%.3f,%.3f), point #%u) was %.3f.\n",
             CURVE_POINT(curveP, worstPoint).x,
             CURVE_POINT(curveP, worstPoint).y,
             CURVE_POINT(curveP, worstPoint).z,
             worstPoint, worstError);
        LOG1("  Total error was %.3f.\n", totalError);
        LOG2("  Average error (over %u points) was %.3f.\n",
                 CURVE_LENGTH(curveP), totalError / CURVE_LENGTH(curveP));
    }
    assert(worstPoint < CURVE_LENGTH(curveP));
    *errorP      = worstError;
    *worstPointP = worstPoint;
}



static void
setInitialParameterValues(curve * const curveP) {
/*----------------------------------------------------------------------------
   Fill in the 't' values in *curveP.

   The t value for point P on a curve is the distance P is along the
   curve from the initial point, normalized so the entire curve is
   length 1.0 (i.e. t of the initial point is 0.0; t of the final
   point is 1.0).

   There are a lot of curves that pass through the points indicated by
   *curveP, but for practical computation of t, we just take the
   piecewise linear locus that runs through all of them.  That means
   we can just step through *curveP, adding up the distance from one
   point to the next to get the t value for each point.

   This is the "chord-length parameterization" method, which is
   described in Plass & Stone.
-----------------------------------------------------------------------------*/
    unsigned int p;

    LOG("\nAssigning initial t values:\n  ");

    CURVE_T(curveP, 0) = 0.0;

    for (p = 1; p < CURVE_LENGTH(curveP); ++p) {
        float_coord const point      = CURVE_POINT(curveP, p);
        float_coord const previous_p = CURVE_POINT(curveP, p - 1);
        float const d = distance(point, previous_p);
        CURVE_T(curveP, p) = CURVE_T(curveP, p - 1) + d;
    }

    assert(LAST_CURVE_T(curveP) != 0.0);

    /* Normalize to a curve length of 1.0 */

    for (p = 1; p < CURVE_LENGTH(curveP); ++p)
        CURVE_T(curveP, p) = CURVE_T(curveP, p) / LAST_CURVE_T(curveP);

    log_entire_curve(curveP);
}



static void
subdivideCurve(curve *                   const curveP,
               unsigned int              const subdivisionIndex,
               const fitting_opts_type * const fittingOptsP,
               curve **                  const leftCurvePP,
               curve **                  const rghtCurvePP,
               vector_type *             const joinSlopeP) {
/*----------------------------------------------------------------------------
  Split curve *curveP into two, at 'subdivisionIndex'.  (Actually,
  leave *curveP alone, but return as *leftCurvePP and *rghtCurvePP
  two new curves that are the pieces).
  
  Return as *joinSlopeP what should be the slope where the subcurves
  join, i.e. the slope of the end of the left subcurve and of the start
  of the right subcurve.

  To be precise, the point with sequence number 'subdivisionIndex'
  becomes the first pixel of the right-hand curve.
-----------------------------------------------------------------------------*/
    curve * leftCurveP;
    curve * rghtCurveP;

    leftCurveP = new_curve();
    rghtCurveP = new_curve();

    LOG4("  Subdividing curve %lx into %lx and %lx at point #%u\n",
         (unsigned long)curveP,
         (unsigned long)leftCurveP, (unsigned long)rghtCurveP,
         subdivisionIndex);

    /* The last point of the left-hand curve will also be the first
       point of the right-hand curve.
    */
    assert(subdivisionIndex < CURVE_LENGTH(curveP));
    CURVE_LENGTH(leftCurveP) = subdivisionIndex + 1;
    CURVE_LENGTH(rghtCurveP) = CURVE_LENGTH(curveP) - subdivisionIndex;

    MALLOCARRAY_NOFAIL(leftCurveP->point_list, CURVE_LENGTH(leftCurveP));
    memcpy(leftCurveP->point_list, &curveP->point_list[0],
           CURVE_LENGTH(leftCurveP) * sizeof(curveP->point_list[0]));

    MALLOCARRAY_NOFAIL(rghtCurveP->point_list, CURVE_LENGTH(rghtCurveP));
    memcpy(rghtCurveP->point_list, &curveP->point_list[subdivisionIndex],
           CURVE_LENGTH(rghtCurveP) * sizeof(curveP->point_list[0]));

    /* We have to set up the two curves before finding the slope at
       the subdivision point.  The slope at that point must be the
       same for both curves, or noticeable bumps will occur in the
       character.  But we want to use information on both sides of the
       point to compute the slope, hence we use adjacentCurveP.
    */
    findTangent(leftCurveP,
                /* toStartPoint: */   false,
                /* adjacentCurveP: */ rghtCurveP,
                fittingOptsP->tangent_surround, joinSlopeP);

    *leftCurvePP = leftCurveP;
    *rghtCurvePP = rghtCurveP;
}



static spline_list_type *
leftRightConcat(const spline_list_type *  const leftSplineListP,
                const spline_list_type *  const rghtSplineListP,
                at_exception_type *       const exceptionP) {
/*----------------------------------------------------------------------------
   Return a spline list which is the concatenation of the spline lists
   obtained by splitting a curve in two and fitting each independently.
   NULL for a spline list pointer means Caller was unable to fit a list
   of splines to that side of the curve.
-----------------------------------------------------------------------------*/
    spline_list_type * retval;
                
    retval = new_spline_list();

    if (leftSplineListP == NULL) {
        LOG("Could not fit spline to left curve.\n");
        at_exception_warning(exceptionP, "Could not fit left spline list");
    } else
        concat_spline_lists(retval, *leftSplineListP);
    
    if (rghtSplineListP == NULL) {
        LOG("Could not fit spline to right curve.\n");
        at_exception_warning(exceptionP, "Could not fit right spline list");
    } else
        concat_spline_lists(retval, *rghtSplineListP);

    return retval;
}



static unsigned int
divisionPoint(curve *      const curveP,
              unsigned int const worstFitPoint) {
/*----------------------------------------------------------------------------
   Return the sequence number of the point at which we should divide
   curve *curveP for the purpose of doing a separate fit of each side,
   assuming the point which least matches a single spline is sequence
   number 'worstFitPoint'.

   We get as close as we can to that while still having at least two
   points on each side.

   Assume the curve is at least 4 points long.

   The return value is the sequence number of the first point of the
   second (right-hand) subcurve.
-----------------------------------------------------------------------------*/
    assert(CURVE_LENGTH(curveP) >= 4);

    return MAX(2, MIN(worstFitPoint, CURVE_LENGTH(curveP) - 2));
}



static spline_list_type *
divideAndFit(curve *                   const curveP,
             vector_type               const begSlope,
             vector_type               const endSlope,
             unsigned int              const subdivisionIndex,
             const fitting_opts_type * const fittingOptsP,
             at_exception_type *       const exceptionP) {
/*----------------------------------------------------------------------------
  Same as fitWithLeastSquares() (i.e. return a list of splines that fit
  the curve *curveP), except assuming no single spline will fit the
  entire curve.

  Divide it into two curves at 'subdivisionIndex' and fit each
  separately to a list of splines.  Return the concatenation of those
  spline lists.

  Assume 'subdivisionIndex' leaves at least two pixels on each side.
-----------------------------------------------------------------------------*/
    spline_list_type * retval;
    curve * leftCurveP;
        /* The beginning (lower indexes) subcurve */
    curve * rghtCurveP;
        /* The other subcurve */
    vector_type joinSlope;
        /* The slope of the end of the left subcurve and start of the right
           subcurve.
        */
    spline_list_type * leftSplineListP;
    
    assert(subdivisionIndex > 1);
    assert(subdivisionIndex < CURVE_LENGTH(curveP)-1);
    subdivideCurve(curveP, subdivisionIndex, fittingOptsP,
                   &leftCurveP, &rghtCurveP, &joinSlope);

    leftSplineListP = fitCurve(leftCurveP, begSlope, joinSlope,
                               fittingOptsP, exceptionP);

    if (!at_exception_got_fatal(exceptionP)) {
        spline_list_type * rghtSplineListP;

        rghtSplineListP = fitCurve(rghtCurveP, joinSlope, endSlope,
                                   fittingOptsP, exceptionP);

        if (!at_exception_got_fatal(exceptionP)) {
            if (leftSplineListP == NULL && rghtSplineListP == NULL)
                retval = NULL;
            else
                retval = leftRightConcat(leftSplineListP, rghtSplineListP,
                                         exceptionP);

            if (rghtSplineListP) {
                free_spline_list(*rghtSplineListP);
                free(rghtSplineListP);
            }
        }
        if (leftSplineListP) {
            free_spline_list(*leftSplineListP);
            free(leftSplineListP);
        }
    }

    free_curve(leftCurveP);
    free_curve(rghtCurveP);

    return retval;
}



static spline_list_type *
fitWithLeastSquares(curve *                   const curveP,
                    vector_type               const begSlope,
                    vector_type               const endSlope,
                    const fitting_opts_type * const fittingOptsP,
                    at_exception_type *       const exceptionP) {
/*----------------------------------------------------------------------------
  The least squares method is well described in Schneider's thesis.
  Briefly, we try to fit the entire curve with one spline.  If that
  fails, we subdivide the curve. 
-----------------------------------------------------------------------------*/
    spline_list_type * retval;
    spline_type spline;
    
    LOG("\nFitting with least squares:\n");
    
    /* Phoenix reduces the number of points with a "linear spline
       technique."  But for fitting letterforms, that is
       inappropriate.  We want all the points we can get.
    */
    
    setInitialParameterValues(curveP);

    if (CURVE_CYCLIC(curveP) && CURVE_LENGTH(curveP) < 4) {
        unsigned i;
        for (i = 0; i < CURVE_LENGTH(curveP); ++i) {
            float_coord const point = CURVE_POINT(curveP, i);
            fprintf(stderr, "point %u = (%f, %f)\n", i, point.x, point.y);
        }
    }

    /* Try a single spline over whole curve */

    spline = fitOneSpline(curveP, begSlope, endSlope, exceptionP);
    if (!at_exception_got_fatal(exceptionP)) {
        float error;
        unsigned int worstPoint;

        logSplineFit(spline);
        
        findError(curveP, spline, &error, &worstPoint, exceptionP);
        assert(worstPoint < CURVE_LENGTH(curveP));

        if (error < fittingOptsP->error_threshold && !CURVE_CYCLIC(curveP)) {
            /* The points were fitted adequately with a spline.  But
               see if the "curve" that was fit should really just be a
               straight line.
            */
            if (spline_linear_enough(&spline, curveP, fittingOptsP)) {
                SPLINE_DEGREE(spline) = LINEARTYPE;
                LOG("Changed to line.\n");
            }
            retval = new_spline_list_with_spline(spline);
            LOG1("Accepted error of %.3f.\n", error);
        } else {
            /* We couldn't fit the curve acceptably with a single spline,
               so divide into two curves and try to fit each separately.
            */
            unsigned int const divIndex = divisionPoint(curveP, worstPoint);
            LOG1("\nSubdividing at point #%u\n", divIndex);
            LOG4("  Worst match point: (%.3f,%.3f), #%u.  Error %.3f\n",
                 CURVE_POINT(curveP, worstPoint).x,
                 CURVE_POINT(curveP, worstPoint).y, worstPoint, error);

            retval = divideAndFit(curveP, begSlope, endSlope, divIndex,
                                  fittingOptsP, exceptionP);
        }
    } else
        retval = NULL; /* quiet compiler warning */

    return retval;
}



static spline_list_type *
fitCurve(curve *                   const curveP,
         vector_type               const begSlope,
         vector_type               const endSlope,
         const fitting_opts_type * const fittingOptsP,
         at_exception_type *       const exceptionP) {
/*----------------------------------------------------------------------------
  Transform a set of locations to a list of splines (the fewer the
  better).  We are guaranteed that *curveP does not contain any corners.
  We return NULL if we cannot fit the points at all.
-----------------------------------------------------------------------------*/
    spline_list_type * fittedSplinesP;

    if (CURVE_LENGTH(curveP) < 2) {
        LOG("Tried to fit curve with fewer than two points");
        at_exception_warning(exceptionP, 
                             "Tried to fit curve with less than two points");
        fittedSplinesP = NULL;
    } else if (CURVE_LENGTH(curveP) < 4)
        fittedSplinesP = fitWithLine(curveP);
    else
        fittedSplinesP =
            fitWithLeastSquares(curveP, begSlope, endSlope, fittingOptsP,
                                exceptionP);

    return fittedSplinesP;
}



static void
fitCurves(curve_list_type           const curveList,
          pixel                     const color,
          const fitting_opts_type * const fittingOptsP,
          spline_list_type *        const splinesP,
          at_exception_type *       const exceptionP) {
          
    spline_list_type curveListSplines;
    unsigned int curveSeq;

    curveListSplines = empty_spline_list();
    
    curveListSplines.open      = curveList.open;
    curveListSplines.clockwise = curveList.clockwise;
    curveListSplines.color     = color;

    for (curveSeq = 0;
         curveSeq < curveList.length && !at_exception_got_fatal(exceptionP);
         ++curveSeq) {

        curve * const curveP = CURVE_LIST_ELT(curveList, curveSeq);

        vector_type begSlope, endSlope;
        spline_list_type * curveSplinesP;

        LOG2("\nFitting curve #%u (%lx):\n", curveSeq, (unsigned long)curveP);

        LOG("Finding tangents:\n");
        findTangent(curveP, /* toStart */ true,
                    CURVE_CYCLIC(curveP) ? curveP : NULL,
                    fittingOptsP->tangent_surround,
                    &begSlope);
        findTangent(curveP, /* toStart */ false,
                    CURVE_CYCLIC(curveP) ? curveP : NULL,
                    fittingOptsP->tangent_surround, &endSlope);

        curveSplinesP = fitCurve(curveP, begSlope, endSlope, fittingOptsP,
                                 exceptionP);
        if (!at_exception_got_fatal(exceptionP)) {
            if (curveSplinesP == NULL) {
                LOG1("Could not fit curve #%u", curveSeq);
                at_exception_warning(exceptionP, "Could not fit curve");
            } else {
                logSplinesForCurve(curveSeq, *curveSplinesP);
                
                /* After fitting, we may need to change some would-be lines
                   back to curves, because they are in a list with other
                   curves.
                */
                change_bad_lines(curveSplinesP, fittingOptsP);
                
                concat_spline_lists(&curveListSplines, *curveSplinesP);
                free_spline_list(*curveSplinesP);
                free(curveSplinesP);
            }
        }
    }
    if (at_exception_got_fatal(exceptionP))
        free_spline_list(curveListSplines);
    else
        *splinesP = curveListSplines;
}
    


static void
logFittedSplines(spline_list_type const curve_list_splines) {

    unsigned int splineSeq;

    LOG("\nFitted splines are:\n");
    for (splineSeq = 0;
         splineSeq < SPLINE_LIST_LENGTH(curve_list_splines);
         ++splineSeq) {
        LOG1("  %u: ", splineSeq);
        print_spline(log_file,
                     SPLINE_LIST_ELT(curve_list_splines, splineSeq));
    }
}



static void
fitCurveList(curve_list_type     const curveList,
             fitting_opts_type * const fittingOptsP,
             distance_map_type * const dist,
             pixel               const color,
             spline_list_type *  const splineListP,
             at_exception_type * const exception) {
/*----------------------------------------------------------------------------
  Fit the list of curves CURVE_LIST to a list of splines, and return
  it.  CURVE_LIST represents a single closed paths, e.g., either the
  inside or outside outline of an `o'.
-----------------------------------------------------------------------------*/
    curve_type curve;
    spline_list_type curveListSplines;

    removeKnees(curveList);

    if (dist != NULL)
        computePointWeights(curveList, fittingOptsP, dist);
    
    /* We filter all the curves in 'curveList' at once; otherwise, we
       would look at an unfiltered curve when computing tangents.
    */
    filterCurves(curveList, fittingOptsP);

    /* Make the first point in the first curve also be the last point in
       the last curve, so the fit to the whole curve list will begin and
       end at the same point.  This may cause slight errors in computing
       the tangents and t values, but it's worth it for the continuity.
       Of course we don't want to do this if the two points are already
       the same, as they are if the curve is cyclic.  (We don't append it
       earlier, in `split_at_corners', because that confuses the
       filtering.)  Finally, we can't append the point if the curve is
       exactly three points long, because we aren't adding any more data,
       and three points isn't enough to determine a spline.  Therefore,
       the fitting will fail.
    */
    curve = CURVE_LIST_ELT(curveList, 0);
    if (CURVE_CYCLIC(curve))
        append_point(curve, CURVE_POINT(curve, 0));

    /* Finally, fit each curve in the list to a list of splines.  */

    fitCurves(curveList, color, fittingOptsP, &curveListSplines, exception);
    if (!at_exception_got_fatal(exception)) {
        if (log_file)
            logFittedSplines(curveListSplines);
        *splineListP = curveListSplines;
    }
}



static void
fitCurvesToSplines(curve_list_array_type    const curveArray,
                   fitting_opts_type *      const fittingOptsP,
                   distance_map_type *      const dist,
                   unsigned short           const width,
                   unsigned short           const height,
                   at_exception_type *      const exception,
                   at_progress_func               notifyProgress, 
                   void *                   const progressData,
                   at_testcancel_func             testCancel,
                   void *                   const testcancelData,
                   spline_list_array_type * const splineListArrayP) {
    
    unsigned splineListSeq;
    bool cancelled;
    spline_list_array_type splineListArray;

    splineListArray = new_spline_list_array();
    splineListArray.centerline          = fittingOptsP->centerline;
    splineListArray.preserve_width      = fittingOptsP->preserve_width;
    splineListArray.width_weight_factor = fittingOptsP->width_weight_factor;
    splineListArray.backgroundSpec      = fittingOptsP->backgroundSpec;
    splineListArray.background_color    = fittingOptsP->background_color;
    /* Set dummy values. Real value is set in upper context. */
    splineListArray.width  = width;
    splineListArray.height = height;
    
    for (splineListSeq = 0, cancelled = false;
         splineListSeq < CURVE_LIST_ARRAY_LENGTH(curveArray) &&
             !at_exception_got_fatal(exception) && !cancelled;
         ++splineListSeq) {

        curve_list_type const curveList =
            CURVE_LIST_ARRAY_ELT(curveArray, splineListSeq);
      
        spline_list_type curveSplineList;

        if (notifyProgress)
            notifyProgress((((float)splineListSeq)/
                            ((float)CURVE_LIST_ARRAY_LENGTH(curveArray) *
                             (float)3.0) + (float)0.333),
                           progressData);
        if (testCancel && testCancel(testcancelData))
            cancelled = true;

        LOG1("\nFitting curve list #%u:\n", splineListSeq);

        fitCurveList(curveList, fittingOptsP, dist, curveList.color,
                     &curveSplineList, exception);
        if (!at_exception_got_fatal(exception))
            append_spline_list(&splineListArray, curveSplineList);
    }
    *splineListArrayP = splineListArray;
}



void
fit_outlines_to_splines(pixel_outline_list_type  const pixelOutlineList,
                        fitting_opts_type *      const fittingOptsP,
                        distance_map_type *      const dist,
                        unsigned short           const width,
                        unsigned short           const height,
                        at_exception_type *      const exception,
                        at_progress_func               notifyProgress, 
                        void *                   const progressData,
                        at_testcancel_func             testCancel,
                        void *                   const testcancelData,
                        spline_list_array_type * const splineListArrayP) {
/*----------------------------------------------------------------------------
   Transform a list of pixels in the outlines of the original character to
   a list of spline lists fitted to those pixels.
-----------------------------------------------------------------------------*/
    curve_list_array_type const curveListArray =
        split_at_corners(pixelOutlineList, fittingOptsP, exception);

    fitCurvesToSplines(curveListArray, fittingOptsP, dist, width, height,
                       exception, notifyProgress, progressData,
                       testCancel, testcancelData, splineListArrayP);

    free_curve_list_array(&curveListArray, notifyProgress, progressData);
    
    flush_log_output();
}



