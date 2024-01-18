/* 
**
** This library module contains the pamdraw routines.
**
** Copyright (C) 1989, 1991 by Jef Poskanzer.
**
** Modified from ppm to pam by Willem van Schaik, Feb 2011
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
** 
** The character drawing routines are by John Walker
** Copyright (C) 1994 by John Walker, kelvin@fourmilab.ch
*/

#include <assert.h>
#include <stdlib.h>

#include "pm_config.h"
#include "pm_c_util.h"
#include "mallocvar.h"

#include "pam.h"
#include "ppmdfont.h"

#include "pamdraw.h"


struct penpos {
    int x;
    int y;
};

struct rectangle {
    /* ((0,0),(0,0)) means empty. */
    /* 'lr' is guaranteed not to be left of or above 'ul' */
    struct penpos ul;
    struct penpos lr;
};

static struct rectangle const emptyRectangle = {
    {0, 0},
    {0, 0},
};



static pamd_point
makePoint(int const x,
          int const y) {

    return pamd_makePoint(x, y);
}



static pamd_point
middlePoint(pamd_point const a,
            pamd_point const b) {

    pamd_point retval;

    retval.x = (a.x + b.x) / 2;
    retval.y = (a.y + b.y) / 2;

    return retval;
}



static bool
pointsEqual(pamd_point const a,
            pamd_point const b) {

    return a.x == b.x && a.y == b.y;
}



static bool
pointIsWithinBounds(pamd_point   const p,
                    unsigned int const cols,
                    unsigned int const rows) {

    return (p.x >= 0 && p.x < cols && p.y >= 0 && p.y < rows);
}

        

static pamd_point
vectorSum(pamd_point const a,
          pamd_point const b) {

    return makePoint(a.x + b.x, a.y + b.y);
}



static long int const DDA_SCALE = 8192;

#define PAMD_MAXCOORD 32767
/*
  Several factors govern the limit of x, y coordination values.

  The limit must be representable as (signed) int for coordinates to 
  be carried in struct penpos (immediately above).

  The following calculation, done with long ints, must not overflow:
  cy0 = cy0 + (y1 - cy0) * (cols - 1 - cx0) / (x1 - cx0);

  The following must not overflow when DDA_SCALE is set to 8092:
  dy = (y1 - y0) * DDA_SCALE / abs(x1 - x0);

  Overflow conditions for pamd_text are rather complicated, for commands
  come from an external PPMD font file.  See comments below.  
*/



void
pamd_validateCoord(int const c) {

    if (c < -PAMD_MAXCOORD || c > PAMD_MAXCOORD)
        pm_error("Coordinate out of bounds: %d", c);
}



void
pamd_validatePoint(pamd_point const p) {

    if (p.x < -PAMD_MAXCOORD || p.x > PAMD_MAXCOORD)
        pm_error("x coordinate of (%d, %d) out of bounds", p.x, p.y);

    if (p.y < -PAMD_MAXCOORD || p.y > PAMD_MAXCOORD)
        pm_error("y coordinate of (%d, %d) out of bounds", p.x, p.y);
}



static void
drawPoint(pamd_drawproc       drawproc,
          const void *  const clientdata,
          tuple **      const tuples, 
          int           const cols, 
          int           const rows, 
          int           const depth, 
          sample        const maxval, 
          pamd_point    const p) {
/*----------------------------------------------------------------------------
   Draw a single point, assuming that it is within the bounds of the
   image.
-----------------------------------------------------------------------------*/
    int i;

    if (drawproc == PAMD_NULLDRAWPROC) {
        assert(p.x >= 0); assert(p.x < cols);
        assert(p.y >= 0); assert(p.y < rows);

        for (i = 0; i < depth; i++)
            tuples[p.y][p.x][i] = (sample) *((tuple *) clientdata + i);
    } else {
        drawproc(tuples, cols, rows, depth, maxval, p, clientdata);
    }
}



void
pamd_point_drawproc(tuple **     const tuples, 
                    unsigned int const cols, 
                    unsigned int const rows, 
                    unsigned int const depth, 
                    sample       const maxval, 
                    pamd_point   const p,
                    const void * const clientdata) {

    unsigned int i;
    
    if ((p.x >= 0) && (p.x < cols) && (p.y >= 0) && (p.y < rows))
        for (i = 0; i < depth; ++i)
            tuples[p.y][p.x][i] = (sample) *((tuple *) clientdata + i);
}



static void
findRectangleIntersection(struct rectangle   const rect1,
                          struct rectangle   const rect2,
                          struct rectangle * const intersectionP) {
/*----------------------------------------------------------------------------
   Find the intersection between rectangles 'rect1' and 'rect2'.
   Return it as *intersectionP.
-----------------------------------------------------------------------------*/
    struct penpos tentativeUl, tentativeLr;

    tentativeUl.x = MAX(rect1.ul.x, rect2.ul.x);
    tentativeUl.y = MAX(rect1.ul.y, rect2.ul.y);
    tentativeLr.x = MIN(rect1.lr.x, rect2.lr.x);
    tentativeLr.y = MIN(rect1.lr.y, rect2.lr.y);

    if (tentativeLr.x <= tentativeUl.x ||
        tentativeLr.y <= tentativeUl.y) {
        /* No intersection */
        *intersectionP = emptyRectangle;
    } else {
        intersectionP->ul = tentativeUl;
        intersectionP->lr = tentativeLr;
    }
}



void
pamd_filledrectangle(tuple **      const tuples, 
                     int           const cols, 
                     int           const rows, 
                     int           const depth, 
                     sample        const maxval, 
                     int           const left, 
                     int           const top, 
                     int           const width, 
                     int           const height, 
                     pamd_drawproc       drawProc,
                     const void *  const clientdata) {

    struct rectangle image, request, intersection;
    unsigned int row;

    if (width < 0)
        pm_error("negative width %d passed to pamd_filledrectanglep", width);
    if (height < 0)
        pm_error("negative height %d passed to pamd_filledrectanglep", height);
    if (cols < 0)
        pm_error("negative image width %d passed to pamd_filledrectanglep",
                 cols);
    if (rows < 0)
        pm_error("negative image height %d passed to pamd_filledrectanglep",
                 rows);

    request.ul.x = left;
    request.ul.y = top;
    request.lr.x = left + width;
    request.lr.y = top + height;

    image.ul.x = 0;
    image.ul.y = 0;
    image.lr.x = cols;
    image.lr.y = rows;

    findRectangleIntersection(image, request, &intersection);

    /* Draw. */
    for (row = intersection.ul.y; row < intersection.lr.y; ++row) {
        unsigned int col;
        for (col = intersection.ul.x; col < intersection.lr.x; ++col)
            drawPoint(drawProc, clientdata,
                      tuples, cols, rows, depth, maxval, makePoint(col, row));
    }
}



/* Outline drawing stuff. */

static int linetype = PAMD_LINETYPE_NORMAL;



int
pamd_setlinetype(int const type) {

    int old;

    old = linetype;
    linetype = type;
    return old;
}


static bool lineclip = TRUE;



int
pamd_setlineclip(int const newSetting) {

    bool previousSetting;

    previousSetting = lineclip;

    lineclip = newSetting;

    return previousSetting;
}



static void
clipEnd0(pamd_point   const p0,
         pamd_point   const p1,
         int          const cols,
         int          const rows,
         pamd_point * const c0P,
         bool *       const noLineP) {
/*----------------------------------------------------------------------------
   Given a line that goes from p0 to p1, where any of these coordinates may be
   anywhere in space -- not just in the frame, clip the p0 end to bring it
   into the frame.  Return the clipped-to location as *c0P.

   Iff this is not possible because the entire line described is
   outside the frame, return *nolineP == true.

   The frame is 'cols' columns starting at 0, by 'rows' rows starting
   at 0.
-----------------------------------------------------------------------------*/
    pamd_point c0;
    bool noLine;

    c0 = p0;         /* initial value */
    noLine = FALSE;  /* initial value */

    /* Clip End 0 of the line horizontally */
    if (c0.x < 0) {
        if (p1.x < 0)
            noLine = TRUE;
        else {
            c0.y = c0.y + (p1.y - c0.y) * (-c0.x) / (p1.x - c0.x);
            c0.x = 0;
        }
    } else if (c0.x >= cols) {
        if (p1.x >= cols)
            noLine = TRUE;
        else {
            c0.y = c0.y + (p1.y - c0.y) * (cols - 1 - c0.x) / (p1.x - c0.x);
            c0.x = cols - 1;
        }
    }

    /* Clip End 0 of the line vertically */
    if (c0.y < 0) {
        if (p1.y < 0)
            noLine = TRUE;
        else {
            c0.x = c0.x + (p1.x - c0.x) * (-c0.y) / (p1.y - c0.y);
            c0.y = 0;
        }
    } else if (c0.y >= rows) {
        if (p1.y >= rows)
            noLine = TRUE;
        else {
            c0.x = c0.x + (p1.x - c0.x) * (rows - 1 - c0.y) / (p1.y - c0.y);
            c0.y = rows - 1;
        }
    }

    /* Clipping vertically may have moved the endpoint out of frame
       horizontally.  If so, we know the other endpoint is also out of
       frame horizontally and the line misses the frame entirely.
    */
    if (c0.x < 0 || c0.x >= cols) {
        assert(p1.x < 0 || p1.x >= cols);
        noLine = TRUE;
    }
    *c0P = c0;
    *noLineP = noLine;
}



static void
clipEnd1(pamd_point   const p0,
         pamd_point   const p1,
         int          const cols,
         int          const rows,
         pamd_point * const c1P) {
/*----------------------------------------------------------------------------
   Given a line that goes from p0 to p1, where p0 is within the frame, but p1
   can be anywhere in space, clip the p1 end to bring it into the frame.
   Return the clipped-to location as *c1P.

   This is guaranteed to be possible, since we already know at least one point
   (i.e. p0) is in the frame.

   The frame is 'cols' columns starting at 0, by 'rows' rows starting
   at 0.
-----------------------------------------------------------------------------*/
    pamd_point c1;
        /* The current clipped location of p1; we clip it multile times
           to get the final location.
        */
    /* p0 is in the frame: */
    assert(p0.x >= 0 && p0.x < cols);
    assert(p0.y >= 0 && p0.y < rows);
    
    /* Clip End 1 of the line horizontally */
    c1 = p1;  /* initial value */
    
    if (c1.x < 0) {
        /* We know the line isn't vertical, since End 0 is in the frame
           and End 1 is left of frame.
        */
        c1.y = c1.y + (p0.y - c1.y) * (-c1.x) / (p0.x - c1.x);
        c1.x = 0;
    } else if (c1.x >= cols) {
        /* We know the line isn't vertical, since End 0 is in the frame
           and End 1 is right of frame.
        */
        c1.y = c1.y + (p0.y - c1.y) * (cols - 1 - c1.x) / (p0.x - c1.x);
        c1.x = cols - 1;
    }
    
    /* Clip End 1 of the line vertically */
    if (c1.y < 0) {
        /* We know the line isn't horizontal, since End 0 is in the frame
           and End 1 is above frame.
        */
        c1.x = c1.x + (p0.x - c1.x) * (-c1.y) / (p0.y - c1.y);
        c1.y = 0;
    } else if (c1.y >= rows) {
        /* We know the line isn't horizontal, since End 0 is in the frame
           and End 1 is below frame.
        */
        c1.x = c1.x + (p0.x - c1.x) * (rows - 1 - c1.y) / (p0.y - c1.y);
        c1.y = rows - 1;
    }

    *c1P = c1;
}



static void
clipLine(pamd_point   const p0,
         pamd_point   const p1,
         int          const cols,
         int          const rows,
         pamd_point * const c0P,
         pamd_point * const c1P,
         bool *       const noLineP) {
/*----------------------------------------------------------------------------
   Clip the line that goes from p0 to p1 so that none of it is outside the
   boundaries of the raster with width 'cols' and height 'rows'

   The clipped line goes from *c0P to *c1P.

   But if the entire line is outside the boundaries (i.e. we clip the
   entire line), return *noLineP true and the other values undefined.
-----------------------------------------------------------------------------*/
    pamd_point c0, c1;
        /* The line we successively modify.  Starts out as the input
           line and ends up as the output line.
        */
    bool noLine;

    clipEnd0(p0, p1, cols, rows, &c0, &noLine);

    if (!noLine) {
        /* p0 is in the frame: */
        assert(c0.x >= 0 && c0.x < cols);
        assert(c0.y >= 0 && c0.y < rows);

        clipEnd1(c0, p1, cols, rows, &c1);
    }

    *c0P = c0;
    *c1P = c1;
    *noLineP = noLine;
}



static void
drawShallowLine(pamd_drawproc       drawProc,
                const void *  const clientdata,
                tuple **      const tuples, 
                int           const cols, 
                int           const rows, 
                int           const depth, 
                sample        const maxval, 
                pamd_point    const p0,
                pamd_point    const p1) {
/*----------------------------------------------------------------------------
   Draw a line that is more horizontal than vertical.

   Don't clip.

   Assume the line has distinct start and end points (i.e. it's at least
   two points).
-----------------------------------------------------------------------------*/
    /* Loop over X domain. */
    long dy, srow;
    int dx, col, row, prevrow;

    if (p1.x > p0.x)
        dx = 1;
    else
        dx = -1;
    dy = (p1.y - p0.y) * DDA_SCALE / abs(p1.x - p0.x);
    prevrow = row = p0.y;
    srow = row * DDA_SCALE + DDA_SCALE / 2;
    col = p0.x;
    for ( ; ; ) {
        if (linetype == PAMD_LINETYPE_NODIAGS && row != prevrow) {
            drawPoint(drawProc, clientdata,
                      tuples, cols, rows, depth, maxval,
                      makePoint(col, prevrow));
            prevrow = row;
        }
        drawPoint(drawProc, clientdata, tuples, cols, rows, depth, maxval,
                  makePoint(col, row));
        if (col == p1.x)
            break;
        srow += dy;
        row = srow / DDA_SCALE;
        col += dx;
    }
}



static void
drawSteepLine(pamd_drawproc       drawProc,
              const void *  const clientdata,
              tuple **      const tuples, 
              int           const cols, 
              int           const rows, 
              int           const depth,
              sample        const maxval, 
              pamd_point    const p0,
              pamd_point    const p1) {
/*----------------------------------------------------------------------------
   Draw a line that is more vertical than horizontal.

   Don't clip.

   Assume the line has distinct start and end points (i.e. it's at least
   two points).
-----------------------------------------------------------------------------*/
    /* Loop over Y domain. */

    long dx, scol;
    int dy, col, row, prevcol;

    if (p1.y > p0.y)
        dy = 1;
    else
        dy = -1;
    dx = (p1.x - p0.x) * DDA_SCALE / abs(p1.y - p0.y);
    row = p0.y;
    prevcol = col = p0.x;
    scol = col * DDA_SCALE + DDA_SCALE / 2;
    for ( ; ; ) {
        if (linetype == PAMD_LINETYPE_NODIAGS && col != prevcol) {
            drawPoint(drawProc, clientdata,
                      tuples, cols, rows, depth, maxval,
                      makePoint(prevcol, row));
            prevcol = col;
        }
        drawPoint(drawProc, clientdata, tuples, cols, rows, depth, maxval,
                  makePoint(col, row));
        if (row == p1.y)
            break;
        row += dy;
        scol += dx;
        col = scol / DDA_SCALE;
    }
}



void
pamd_line(tuple **      const tuples, 
          int           const cols, 
          int           const rows, 
          int           const depth, 
          sample        const maxval, 
          pamd_point    const p0,
          pamd_point    const p1,
          pamd_drawproc       drawProc,
          const void *  const clientdata) {

    pamd_point c0, c1;
    bool noLine;  /* There's no line left after clipping */

    pamd_validateCoord(cols);
    pamd_validateCoord(rows);
    pamd_validatePoint(p0);
    pamd_validatePoint(p1);

    if (lineclip) {
        clipLine(p0, p1, cols, rows, &c0, &c1, &noLine);
    } else {
        c0 = p0;
        c1 = p1;
        noLine = FALSE;
    }

    if (noLine) {
        /* Nothing to draw */
    } else if (pointsEqual(c0, c1)) {
        /* This line is just a point.  Because there aren't two
           distinct endpoints, we have a special case.
        */
        drawPoint(drawProc, clientdata, tuples, cols, rows, depth, maxval, c0);
    } else {
        /* Draw, using a simple DDA. */
        if (abs(c1.x - c0.x) > abs(c1.y - c0.y))
            drawShallowLine(drawProc, clientdata, tuples, cols, rows,
                            depth, maxval, c0, c1);
        else
            drawSteepLine(drawProc, clientdata, tuples, cols, rows,
                          depth, maxval, c0, c1);
    }
}



static unsigned int
distanceFromLine(pamd_point const p,
                 pamd_point const l0,
                 pamd_point const l1) {
/*----------------------------------------------------------------------------
  Compute, sort of, the distance between point 'p' and the line through
  'l0' and 'l1'.

  I don't really know the signficance of this measurement.
-----------------------------------------------------------------------------*/

    pamd_point const middle = middlePoint(l0, l1);

    return (abs(p.x - middle.x) + abs(p.y - middle.y));
}



void
pamd_spline3(tuple **      const tuples, 
             int           const cols, 
             int           const rows, 
             int           const depth, 
             sample        const maxval, 
             pamd_point    const p0,
             pamd_point    const ctl,
             pamd_point    const p1,
             pamd_drawproc       drawProc,
             const void *  const clientdata) {

    static unsigned int const splineThresh = 3;
        /* The limit of recursion */

    if (distanceFromLine(ctl, p0, p1) <= splineThresh) {
        /* The control point is pretty close to the straight line that
           joins the endpoints, so we'll just draw a straight line.
        */
        pamd_line(
            tuples, cols, rows, depth, maxval, p0, p1, drawProc, clientdata);
    } else {
        /* We want some curvature, so pick a point (b) sort of between the
           two endpoints and the control point and then draw a spline
           between each of the endpoints and (b):
        */
        pamd_point const a = middlePoint(p0, ctl);
        pamd_point const c = middlePoint(ctl, p1);
        pamd_point const b = middlePoint(a, c);

        pamd_spline3(
            tuples, cols, rows, depth, maxval, p0, a, b, drawProc, clientdata);

        pamd_spline3(
            tuples, cols, rows, depth, maxval, b, c, p1, drawProc, clientdata);
    }
}



void
pamd_polyspline(tuple **      const tuples, 
                unsigned int  const cols, 
                unsigned int  const rows, 
                unsigned int  const depth, 
                sample        const maxval, 
                pamd_point    const p0,
                unsigned int  const nc,
                pamd_point *  const c,
                pamd_point    const p1,
                pamd_drawproc       drawProc,
                const void *  const clientdata) {

    pamd_point p;
    
    unsigned int i;

    assert(nc > 0);

    p = p0;
    for (i = 0; i < nc - 1; ++i) {
        pamd_point const n = middlePoint(c[i], c[i+1]);
        pamd_spline3(
            tuples, cols, rows, depth, maxval, p, c[i], n,
            drawProc, clientdata);
        p = n;
    }
    pamd_spline3(
        tuples, cols, rows, depth, maxval, p, c[nc - 1], p1,
        drawProc, clientdata);
}



void
pamd_spline4(tuple **      const tuples, 
             unsigned int  const cols, 
             unsigned int  const rows, 
             unsigned int  const depth, 
             sample        const maxval, 
             pamd_point    const endPt0,
             pamd_point    const endPt1,
             pamd_point    const ctlPt0,
             pamd_point    const ctlPt1,
             pamd_drawproc       drawproc,
             const void *  const clientdata) {
/*----------------------------------------------------------------------------
   Draw a cubic spline from 'endPt0' to 'endPt1', using 'ctlPt0' and
   'ctlPt1' as control points in the classic way: a line through
   'endPt0' and 'ctlPt0' is tangent to the curve at 'entPt0' and the
   length of that line controls "enthusiasm," whatever that is.
   Same for 'endPt1' and 'ctlPt1'.
-----------------------------------------------------------------------------*/

    pm_error("pamd_spline4() has not been written yet!");

}



void
pamd_circle(tuple **      const tuples, 
            unsigned int  const cols, 
            unsigned int  const rows, 
            unsigned int  const depth, 
            sample        const maxval, 
            pamd_point    const center,
            unsigned int  const radius, 
            pamd_drawproc       drawProc,
            const void *  const clientData) {
/*----------------------------------------------------------------------------
  If lineclip mode is on, draw only points within the image.
  If lineclip is off, "draw" all points (by designated drawproc).  Note
  that the drawproc can't actually draw a point outside the image, but
  it might maintain state that is affected by imaginary points outside
  the image.

  Initial point is 3 o'clock. 
-----------------------------------------------------------------------------*/
    if (radius >= DDA_SCALE)
        pm_error("Error drawing circle.  Radius %d is too large.", radius);

    pamd_validateCoord(center.x + radius);
    pamd_validateCoord(center.y + radius);
    pamd_validateCoord(center.x - radius);
    pamd_validateCoord(center.y - radius);

    if (radius > 0) {
        long const e = DDA_SCALE / radius;

        pamd_point const p0 = makePoint(radius, 0);  /* 3 o'clock */
            /* The starting point around the circle, assuming (0, 0) center */
        pamd_point p;
            /* Current drawing position in the circle, assuming (0,0) center */
        bool onFirstPoint;
        bool prevPointExists;
        pamd_point prevPoint;
            /* Previous drawing position, assuming (0, 0) center*/
        long sx, sy;  /* 'p', scaled by DDA_SCALE */

        p = p0;

        sx = p.x * DDA_SCALE + DDA_SCALE / 2;
        sy = p.y * DDA_SCALE + DDA_SCALE / 2;

        onFirstPoint = TRUE;
        prevPointExists = FALSE;

        while (onFirstPoint || !pointsEqual(p, p0)) {
            if (prevPointExists && pointsEqual(p, prevPoint)) {
                /* We're on the same point we were on last time (we moved less
                   than a point's worth).  Just keep moving.
                */
            } else {
                pamd_point const imagePoint = vectorSum(center,p);
                if (!lineclip || pointIsWithinBounds(imagePoint, cols, rows))
                    drawPoint(drawProc, clientData,
                              tuples, cols, rows, depth, maxval, imagePoint);

                prevPoint = p;
                prevPointExists = TRUE;
            }

            if (!pointsEqual(p, p0))
                onFirstPoint = FALSE;

            sx += e * sy / DDA_SCALE;
            sy -= e * sx / DDA_SCALE;
            p = makePoint(sx / DDA_SCALE, sy / DDA_SCALE);
        }
    }
}



/* Arbitrary fill stuff. */

typedef struct {
    pamd_point point;
    int edge;
} coord;

typedef struct fillState {
    int n;
        /* Number of elements in 'coords' */
    int size;
    int curedge;
    int segstart;
    int ydir;
    int startydir;
    coord * coords;
} fillState;

typedef struct fillobj {

    /* The only reason we have a struct fillState separate from
       struct fillobj is that the drawproc interface is defined to
       have drawing not modify the fillobj, i.e. it passed
       const fillobj * to the drawing program.
    */
    struct fillState * stateP;
} fillobj;

#define SOME 1000

static int oldclip;



struct fillobj *
pamd_fill_create(void) {

    fillobj * fillObjP;
    struct fillState * stateP;

    MALLOCVAR(fillObjP);
    if (fillObjP == NULL)
        pm_error("out of memory allocating a fillhandle");

    MALLOCVAR(stateP);
    if (stateP == NULL)
        pm_error("out of memory allocating a fillhandle");

    stateP->n = 0;
    stateP->size = SOME;
    MALLOCARRAY(stateP->coords, stateP->size);
    if (stateP->coords == NULL)
        pm_error("out of memory allocating a fillhandle");
    stateP->curedge = 0;

    fillObjP->stateP = stateP;
    
    /* Turn off line clipping. */
    /* UGGH! We must eliminate this global variable */
    oldclip = pamd_setlineclip(0);
    
    return fillObjP;
}



void
pamd_fill_destroy(struct fillobj * const fillObjP) {

    free(fillObjP->stateP->coords);
    free(fillObjP->stateP);
    free(fillObjP);
}



static void
addCoord(struct fillState *  const stateP,
         pamd_point const point) {

    stateP->coords[stateP->n].point = point;
    stateP->coords[stateP->n].edge = stateP->curedge;

    ++stateP->n;
}



static void
startNewSegment(struct fillState * const stateP) {
/*----------------------------------------------------------------------------
   Close off the segment we're currently building and start a new one.
-----------------------------------------------------------------------------*/
    if (stateP->startydir != 0 && stateP->ydir != 0) {
        /* There's stuff in the current segment.  */
        if (stateP->startydir == stateP->ydir) {
            /* Oops, first edge and last edge of current segment are the same.
               Change all points in the first edge to be in the last.
            */
            int const firstEdge = stateP->coords[stateP->segstart].edge;
            int const lastEdge  = stateP->coords[stateP->n - 1].edge;
            coord * const segStartCoordP = &stateP->coords[stateP->segstart];
            coord * const segEndCoordP   = &stateP->coords[stateP->n];

            coord * fcP;

            for (fcP = segStartCoordP;
                 fcP < segEndCoordP && fcP->edge == firstEdge;
                 ++fcP)
                fcP->edge = lastEdge;
        }
    }
    /* And start new segment. */
    ++stateP->curedge;
    stateP->segstart  = stateP->n;
    stateP->ydir      = 0;
    stateP->startydir = 0;
}



static void
continueSegment(struct fillState * const stateP,
                int                const dy) {
/*----------------------------------------------------------------------------
   'dy' is how much the current point is above the previous one.
-----------------------------------------------------------------------------*/
    if (dy != 0) {
        if (stateP->ydir != 0 && stateP->ydir != dy) {
            /* Direction changed.  Insert a fake coord, old
               position but new edge number.
            */
            ++stateP->curedge;
            addCoord(stateP, stateP->coords[stateP->n - 1].point);
        }
        stateP->ydir = dy;
        if (stateP->startydir == 0)
            stateP->startydir = dy;
    }
}



/* pamd_fill_drawproc() is a drawproc that turns an outline drawing function
   into a filled shape function.  This is a somewhat off-label application of
   a drawproc:  A drawproc is intended just to draw a point.  So e.g. you
   might draw a circle with a fat brush by calling pamd_circle with a drawproc
   that draws a point as a 10-tuple disk.

   But pamd_fill_drawproc() just draws a point the trivial way: as one tuple.
   However, it tracks every point that is drawn in a form that a subsequent
   pamd_fill() call can use to to fill in the shape drawn, assuming it turns
   out to be a closed shape.
*/

void
pamd_fill_drawproc(tuple **     const tuples, 
                   unsigned int const cols, 
                   unsigned int const rows, 
                   unsigned int const depth, 
                   sample       const maxval, 
                   pamd_point   const p,
                   const void * const clientdata) {

    const fillobj *    const fillObjP = clientdata;
    struct fillState * const stateP   = fillObjP->stateP;

    /* Make room for two more coords, the max we might add. */
    if (stateP->n + 2 > stateP->size) {
        stateP->size += SOME;
        REALLOCARRAY(stateP->coords, stateP->size);
        if (stateP->coords == NULL)
            pm_error("out of memory enlarging a fillhandle");
    }

    if (stateP->n == 0) {
        /* Start first segment. */
        stateP->segstart = stateP->n;
        stateP->ydir = 0;
        stateP->startydir = 0;
        addCoord(stateP, p);
    } else {
        pamd_point const prevPoint = stateP->coords[stateP->n - 1].point;
        int const dx = p.x - prevPoint.x;
        int const dy = p.y - prevPoint.y;

        if (dx == 0 && dy == 0) {
            /* These are the same coords we had last time; don't bother */
        } else {
            if (abs(dx) > 1 || abs(dy) > 1)
                startNewSegment(stateP);
            else
                continueSegment(stateP, dy);

            addCoord(stateP, p);
        }
    }
}



#ifndef LITERAL_FN_DEF_MATCH
static qsort_comparison_fn yxCompare;
#endif

static int
yxCompare(const void * const c1Arg,
          const void * const c2Arg) {

    const coord * const c1P = c1Arg;
    const coord * const c2P = c2Arg;

    pamd_point const p1 = c1P->point;
    pamd_point const p2 = c2P->point;

    int retval;
    
    if (p1.y > p2.y)
        retval = 1;
    else if (p1.y < p2.y)
        retval = -1;
    else if (p1.x > p2.x)
        retval = 1;
    else if (p1.x < p2.x)
        retval = -1;
    else
        retval = 0;

    return retval;
}



void
pamd_fill(tuple **         const tuples, 
          int              const cols, 
          int              const rows, 
          int              const depth, 
          sample           const maxval, 
          struct fillobj * const fillObjP,
          pamd_drawproc          drawProc,
          const void *     const clientdata) {
    
    struct fillState * const fh = fillObjP->stateP;

    int pedge;
    int i, edge, lx, rx, py;
    coord * cp;
    bool eq;
    bool leftside;

    /* Close off final segment. */
    if (fh->n > 0 && fh->startydir != 0 && fh->ydir != 0) {
        if (fh->startydir == fh->ydir) {
            /* Oops, first edge and last edge are the same. */
            coord * fcp;
            const coord * const fcpLast = & (fh->coords[fh->n - 1]);
            int lastedge, oldedge;

            lastedge = fh->coords[fh->n - 1].edge;
            fcp = &(fh->coords[fh->segstart]);
            oldedge = fcp->edge;
            for ( ; fcp<=fcpLast && fcp->edge == oldedge; ++fcp )
                fcp->edge = lastedge;
        }
    }
    /* Restore clipping now. */
    pamd_setlineclip(oldclip);

    /* Sort the coords by Y, secondarily by X. */
    qsort((char*) fh->coords, fh->n, sizeof(coord), yxCompare);

    /* Find equal coords with different edge numbers, and swap if necessary. */
    edge = -1;
    for (i = 0; i < fh->n; ++i) {
        cp = &fh->coords[i];
        if (i > 1 && eq && cp->edge != edge && cp->edge == pedge) {
            /* Swap .-1 and .-2. */
            coord t;

            t = fh->coords[i-1];
            fh->coords[i-1] = fh->coords[i-2];
            fh->coords[i-2] = t;
        }
        if (i > 0) {
            if (cp->point.x == lx && cp->point.y == py) {
                eq = TRUE;
                if (cp->edge != edge && cp->edge == pedge) {
                    /* Swap . and .-1. */
                    coord t;

                    t = *cp;
                    *cp = fh->coords[i-1];
                    fh->coords[i-1] = t;
                }
            } else
                eq = FALSE;
        }
        lx    = cp->point.x;
        py    = cp->point.y;
        pedge = edge;
        edge  = cp->edge;
    }

    /* Ok, now run through the coords filling spans. */
    for (i = 0; i < fh->n; ++i) {
        cp = &fh->coords[i];
        if (i == 0) {
            lx       = rx = cp->point.x;
            py       = cp->point.y;
            edge     = cp->edge;
            leftside = TRUE;
        } else {
            if (cp->point.y != py) {
                /* Row changed.  Emit old span and start a new one. */
                pamd_filledrectangle(
                    tuples, cols, rows, depth, maxval, lx, py, rx - lx + 1, 1,
                    drawProc, clientdata);
                lx       = rx = cp->point.x;
                py       = cp->point.y;
                edge     = cp->edge;
                leftside = TRUE;
            } else {
                if (cp->edge == edge) {
                    /* Continuation of side. */
                    rx = cp->point.x;
                } else {
                    /* Edge changed.  Is it a span? */
                    if (leftside) {
                        rx       = cp->point.x;
                        leftside = FALSE;
                    } else {
                        /* Got a span to fill. */
                        pamd_filledrectangle(
                            tuples, cols, rows, depth, maxval,
                            lx, py, rx - lx + 1, 1, drawProc, clientdata);
                        lx       = rx = cp->point.x;
                        leftside = TRUE;
                    }
                    edge = cp->edge;
                }
            }
        }
    }
}



/* Table used to look up sine of angles from 0 through 90 degrees.
   The value returned is the sine * 65536.  Symmetry is used to
   obtain sine and cosine for arbitrary angles using this table. */

static long sintab[] = {
    0, 1143, 2287, 3429, 4571, 5711, 6850, 7986, 9120, 10252, 11380,
    12504, 13625, 14742, 15854, 16961, 18064, 19160, 20251, 21336,
    22414, 23486, 24550, 25606, 26655, 27696, 28729, 29752, 30767,
    31772, 32768, 33753, 34728, 35693, 36647, 37589, 38521, 39440,
    40347, 41243, 42125, 42995, 43852, 44695, 45525, 46340, 47142,
    47929, 48702, 49460, 50203, 50931, 51643, 52339, 53019, 53683,
    54331, 54963, 55577, 56175, 56755, 57319, 57864, 58393, 58903,
    59395, 59870, 60326, 60763, 61183, 61583, 61965, 62328, 62672,
    62997, 63302, 63589, 63856, 64103, 64331, 64540, 64729, 64898,
    65047, 65176, 65286, 65376, 65446, 65496, 65526, 65536
};

static int extleft, exttop, extright, extbottom;  /* To accumulate extents */



/* LINTLIBRARY */

static long
isin(int const argDeg) {
/*----------------------------------------------------------------------------
    Return sine of an angle in integral degrees.  The value returned is 65536
    times the sine.
-----------------------------------------------------------------------------*/

    int deg360;
        /* The argument reduced to the range 0-360 degrees */

    if (argDeg < 0) {
        deg360 = (360 - ((- argDeg) % 360)) % 360;
    } else if (argDeg >= 360) {
        deg360 = argDeg % 360;
    } else
        deg360 = argDeg;

    /* Now look up from table according to quadrant. */

    if (deg360 <= 90) {
        return sintab[deg360];
    } else if (deg360 <= 180) {
        return sintab[180 - deg360];
    } else if (deg360 <= 270) {
        return -sintab[deg360 - 180];
    }
    return -sintab[360 - deg360];
}



static long
icos(int const deg) {
/*----------------------------------------------------------------------------
  Return cosine of an angle in integral degrees.  The value returned is 65536
  times the cosine
-----------------------------------------------------------------------------*/
    return isin(deg + 90);
}  



static int
twosCompByteValue(unsigned char const c) {
/*----------------------------------------------------------------------------
   E.g. if 'c' is 0x5, return 5.  If 'c' is 0xF0, return -16.
-----------------------------------------------------------------------------*/
    return (char)c;
}



static int
glyphSkipBefore(const struct ppmd_glyph * const glyphP) {

    return twosCompByteValue(glyphP->header.skipBefore);
}



static int
glyphWidth(const struct ppmd_glyph * const glyphP) {

    return twosCompByteValue(glyphP->header.skipAfter) -
        twosCompByteValue(glyphP->header.skipBefore);
}


static pamd_point
commandPoint(const struct ppmd_glyphCommand * const commandP) {
/*----------------------------------------------------------------------------
   Return the point which is the argument of glyph drawing command
   *commandP.  The origin of the coordinate system for this point
   is the center of the glyph cell and the scale is the scale of the
   font, so (-10, -10) means the upper left corner of the glyph cell.
-----------------------------------------------------------------------------*/
    return makePoint(twosCompByteValue(commandP->x),
                     twosCompByteValue(commandP->y));
}

#define Scalef 21       /* Font design size */
#define Descend 9       /* Descender offset */


static pamd_point
textPosFromFontPos(pamd_point   const fontPos,
                   pamd_point   const textBoxOrigin,
                   pamd_point   const center,
                   pamd_point   const glyphOrigin,
                   unsigned int const height,
                   long         const rotcos,
                   long         const rotsin) {
/*----------------------------------------------------------------------------
   'fontPos' is a position within a glyph as told by the font definition.
   It is relative to the center of the glyph, in units of font tuples
   (1/21 of a glyph cell).

   We return the position on the canvas of that point.

   That takes into account where in the text box we are, where the text box
   is on the canvas, the size of the characters, and the rotation of the
   text box.
-----------------------------------------------------------------------------*/
    pamd_point const ptl = vectorSum(center, fontPos);
        /* Position relative to the top left of the standard glyph cell */

    pamd_point const pl = vectorSum(glyphOrigin, ptl);
        /* Position relative to the top left of the whole text box,
           assuming the text box is horizontal and has font scale.
        */
    
    pamd_point const ps = makePoint((pl.x * (int)height) / Scalef,
                                    (pl.y * (int)height) / Scalef);
         /* Same as above, but with the text box its actual size */

    pamd_point const retval =
        makePoint(textBoxOrigin.x +
                  (ps.x * rotcos - (ps.y-(int)height) * rotsin) / 65536,
                  textBoxOrigin.y +
                  (ps.x * rotsin + (ps.y-(int)height) * rotcos) / 65536);

    pamd_validatePoint(retval);

    return retval;
}



static void
drawGlyph(const struct ppmd_glyph * const glyphP,
          pamd_point                const glyphOrigin,
          tuple **                  const tuples,
          unsigned int              const cols,
          unsigned int              const rows,
          unsigned int              const depth,
          sample                    const maxval,
          int                       const height,
          pamd_point                const textBoxOrigin,
          long                      const rotcos,
          long                      const rotsin,
          pamd_drawproc                   drawProc,
          const void *              const clientdata,
          unsigned int *            const cursorAdvanceP
    ) {
/*----------------------------------------------------------------------------
  'glyphOrigin' is the position relative to the upper left corner of the text
  box of the upper left corner of this glyph cell.  It is in units of font
  tuples (so you have to scale it by the font size to actual distance on
  the canvas).

  We return as *cursorAdvanceP the amount to the right of this glyph cell
  the next glyph cell on the line (if any) should be.

  The actual glyph cell may be a little to the left of the nominal position
  because of kerning.  The font says how much to shift the cell left.

  'textBoxOrigin' is the left end of the baseline of the top line in the
  text box, in the coordinate system of the canvas.  'rotcos' and 'rotsin'
  tell how that text box is rotated with respect to the horizontal on the
  canvas.
  
  'height' is the height in canvas tuples of a glyph.  This is a scale factor
  to convert font coordinates to canvas coordinates.
-----------------------------------------------------------------------------*/
    pamd_point const center = makePoint(-glyphSkipBefore(glyphP), Scalef/2);
        /* This is what you have to add to the coordinates in a glyph
           command, which are relative to the center of the glyph, to get
           coordinates relative to the upper left corner of the glyph
        */
    pamd_point p;
        /* Current drawing position within the glyph.  Origin is the top
           left of the glyph cell.  Units are font tuples.
        */
    unsigned int commandNum;

    p = textPosFromFontPos(makePoint(0, 0),
                           textBoxOrigin,
                           center,
                           glyphOrigin,
                           height,
                           rotcos, rotsin);   /* initial value */

    for (commandNum = 0;
         commandNum < glyphP->header.commandCount;
         ++commandNum) {

        const struct ppmd_glyphCommand * const commandP =
            &glyphP->commandList[commandNum];

        switch (commandP->verb) {
        case CMD_NOOP:
            break;
        case CMD_DRAWLINE:
        {
            pamd_point const n = textPosFromFontPos(commandPoint(commandP),
                                                    textBoxOrigin,
                                                    center,
                                                    glyphOrigin,
                                                    height,
                                                    rotcos, rotsin);
                                                    
            pamd_line(tuples, cols, rows, depth, maxval, p, n,
                      drawProc, clientdata);

            p = n;
        }
        break;
        case CMD_MOVEPEN:
            p = textPosFromFontPos(commandPoint(commandP),
                                   textBoxOrigin,
                                   center,
                                   glyphOrigin,
                                   height,
                                   rotcos, rotsin);
            break;
        }
    }
    *cursorAdvanceP = glyphWidth(glyphP);
}



void
pamd_text(tuple**       const tuples, 
          int           const cols, 
          int           const rows, 
          int           const depth, 
          sample        const maxval, 
          pamd_point    const pos,
          int           const height, 
          int           const angle, 
          const char *  const sArg, 
          pamd_drawproc       drawProc,
          const void *  const clientdata) {
/*----------------------------------------------------------------------------
   Draw the zero-terminated string 'sArg', with its baseline starting at point
   'pos', inclined by 'angle' degrees to the X axis, with letters 'height'
   tuples high (descenders will extend below the baseline).  We pass the
   supplied drawproc and clientdata to pamd_linep, which performs the actual
   drawing.

   There may be multiple lines of text.  The baseline of the topmost line
   starts at 'pos'.
-----------------------------------------------------------------------------*/
    const struct ppmd_font * const fontP = ppmd_get_font();

    long rotsin, rotcos;
    pamd_point p;
    const char * s;

    pamd_validatePoint(pos);

    p = makePoint(0, 0);
    rotsin = isin(-angle);
    rotcos = icos(-angle);

    for (s = &sArg[0]; *s; ) {
        unsigned char const ch = *s++;

        if (ch >= fontP->header.firstCodePoint &&
            ch < fontP->header.firstCodePoint + fontP->header.characterCount) {

            const struct ppmd_glyph * const glyphP =
                &fontP->glyphTable[ch - fontP->header.firstCodePoint];

            unsigned int cursorAdvance;

            pamd_validatePoint(p); 

            drawGlyph(glyphP, p, tuples, cols, rows, depth, maxval,
                      height, pos, rotcos, rotsin,
                      drawProc, clientdata, &cursorAdvance);
            p.x += cursorAdvance;
        } else if (ch == '\n') {
            /* Move to the left edge of the next line down */
            p.y += Scalef + Descend;
            p.x = 0;
        }
    }
}



#ifndef LITERAL_FN_DEF_MATCH
static pamd_drawproc extetnsDrawproc;
#endif

static void 
extentsDrawproc(tuple**      const tuples, 
                unsigned int const cols, 
                unsigned int const rows,
                unsigned int const depth,
                sample       const maxval, 
                pamd_point   const p,
                const void * const clientdata) {
/*----------------------------------------------------------------------------
    Drawproc which just accumulates the extents rectangle bounding the
    text.
-----------------------------------------------------------------------------*/
    extleft   = MIN(extleft,   p.x);
    exttop    = MIN(exttop,    p.y);
    extright  = MAX(extright,  p.x);
    extbottom = MAX(extbottom, p.y);
}



void
pamd_text_box(int          const height, 
              int          const angle, 
              const char * const s, 
              int *        const leftP, 
              int *        const topP, 
              int *        const rightP, 
              int *        const bottomP) {
/*----------------------------------------------------------------------------
  Calculate extents rectangle for a given piece of text.  For most
  applications where extents are needed, angle should be zero to obtain the
  unrotated extents.  If you need the extents box for post-rotation text,
  however, you can set angle nonzero and it will be calculated correctly.
-----------------------------------------------------------------------------*/
    extleft   =  32767;
    exttop    =  32767;
    extright  = -32767;
    extbottom = -32767;

    pamd_text(NULL, 32767, 32767, 255, 255, makePoint(1000, 1000),
              height, angle, s, 
              extentsDrawproc, NULL);

    *leftP   = extleft   - 1000; 
    *topP    = exttop    - 1000;
    *rightP  = extright  - 1000;
    *bottomP = extbottom - 1000;
}



