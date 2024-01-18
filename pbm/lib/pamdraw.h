/* pamdraw.h - header file for simple drawing routines in libnetpbm.
**
** Simple, yes, and also fairly slow if the truth be told; but also very
** flexible and powerful.
**
** The two basic concepts are the drawproc and clientdata.  All the drawing
** routines take a drawproc that does the actual drawing.  A drawproc draws
** a single point, and it looks like this:
*/

#include "pm_config.h"

#ifdef __cplusplus
extern "C" {
#endif
#if 0
} /* to fake out automatic code indenters */
#endif


typedef struct {
    int x;
    int y;
} pamd_point;

static __inline__ pamd_point
pamd_makePoint(int const x,
               int const y) {

    pamd_point p;

    p.x = x;
    p.y = y;

    return p;
}

void
pamd_validateCoord(int const c);

void
pamd_validatePoint(pamd_point const p);

typedef enum {
    PAMD_PATHLEG_LINE
} pamd_pathlegtype;

struct pamd_linelegparms {
    pamd_point end;
};

typedef struct {
/*----------------------------------------------------------------------------
   A leg of a pamd_path.
-----------------------------------------------------------------------------*/
    pamd_pathlegtype type;
    union {
        struct pamd_linelegparms linelegparms;
    } u;
} pamd_pathleg;

typedef struct {
/*----------------------------------------------------------------------------
   A closed path
-----------------------------------------------------------------------------*/
    unsigned int version;
        /* Must be zero.  For future expansion. */
    pamd_point   begPoint;  
    unsigned int legCount;
        /* Number of legs in the path; i.e. size of 'legs' array */
    size_t       legSize;
        /* Size of storage occupied by one pamd_pathleg.  I.e.
           sizeof(pamd_pathleg).  Used for
           binary backward compatibility between callers and libpamd
           as the definition of pamd_pathleg changes.
        */
    pamd_pathleg * legs;
} pamd_path;



typedef void pamd_drawproc(tuple **, unsigned int, unsigned int, unsigned int,
                           sample, pamd_point, const void *);

pamd_drawproc pamd_point_drawproc;

/*
** So, you call a drawing routine, e.g. pamd_line(), and pass it a drawproc;
** it calls the drawproc for each point it wants to draw.  Why so complicated?
** Because you can define your own drawprocs to do more interesting things than
** simply draw the point.  For example, you could make one that calls back into
** another drawing routine, say pamd_circle() to draw a circle at each point
** of a line.
**
** Slow?  Well sure, we're talking results here, not realtime.  You can do
** tricks with this arrangement that you couldn't even think of before.
** Still, to speed things up for the 90% case you can use this:
*/
#define PAMD_NULLDRAWPROC NULL
/*
** Just like pamd_point_drawproc() it simply draws the point, but it's done
** inline, and clipping is assumed to be handled at a higher level.
**
** Now, what about clientdata.  Well, it's an arbitrary pointer, and can
** mean something different to each different drawproc.  For the above two
** drawprocs, clientdata should be a pointer to a tuple holding the color
** to be drawn.  Other drawprocs can use it to point to something else,
** e.g. some structure to be modified, or they can ignore it.
*/


/* Outline drawing routines.  Lines, splines, circles, etc. */

int 
pamd_setlinetype(int const type);

#define PAMD_LINETYPE_NORMAL 0
#define PAMD_LINETYPE_NODIAGS 1
/* If you set NODIAGS, all tuples drawn by pamd_line() will be 4-connected
** instead of 8-connected; in other words, no diagonals.  This is useful
** for some applications, for example when you draw many parallel lines
** and you want them to fit together without gaps.
*/

int
pamd_setlineclip(int const clip);

#define pamd_setlineclipping(x)     pamd_setlineclip(x)
/* Normally, pamd_line() clips to the edges of the pixmap.  You can use this
** routine to disable the clipping, for example if you are using a drawproc
** that wants to do its own clipping.
*/

void
pamd_line(tuple **      const tuples, 
          int           const cols, 
          int           const rows, 
          int           const depth, 
          sample        const maxval, 
          pamd_point    const p0,
          pamd_point    const p1,
          pamd_drawproc       drawProc,
          const void *  const clientdata);

    /* Draws a line from p0 to p1.  */

void
pamd_spline3(tuple **      const tuples, 
             int           const cols, 
             int           const rows, 
             int           const depth, 
             sample        const maxval, 
             pamd_point    const p0,
             pamd_point    const p1,
             pamd_point    const p2,
             pamd_drawproc       drawProc,
             const void *  const clientdata);

    /* Draws a three-point spline from p0 to p2, with p1
       as the control point.  All drawing is done via pamd_line(),
       so the routines that control it control pamd_spline3p() as well. 
    */

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
                const void *  const clientdata);

    /* Draws a bunch of splines end to end.  p0 and p1 are the initial and
       final points, and the c[] are the intermediate control points.  nc is
       the number of these control points.
    */

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
             pamd_drawproc       drawProc,
             const void *  const clientdata);

void
pamd_circle(tuple **      const tuples, 
            unsigned int  const cols, 
            unsigned int  const rows, 
            unsigned int  const depth, 
            sample        const maxval, 
            pamd_point    const center,
            unsigned int  const radius, 
            pamd_drawproc       drawProc,
            const void *  const clientData);
    /* Draws a circle centered at 'center' with radius 'radius' */

/* Simple filling routines.  */

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
                     const void *  const clientdata);
    /* Fills in the rectangle [left, top, width, height]. */


void
pamd_fill_path(tuple **      const tuples, 
               int           const cols, 
               int           const rows, 
               int           const depth, 
               sample        const maxval,
               pamd_path *   const pathP,
               tuple         const color);
    /* Fills in a closed path.  Not much different from pamd_fill(),
       but with a different interface.
    */


/* Arbitrary filling routines.  With these you can fill any outline that
** you can draw with the outline routines.
*/

struct fillobj;

struct fillobj *
pamd_fill_create(void);
    /* Returns a blank fillhandle. */

void
pamd_fill_destroy(struct fillobj * fillObjP);

void
pamd_fill_drawproc(tuple **     const tuples, 
                   unsigned int const cols, 
                   unsigned int const rows, 
                   unsigned int const depth, 
                   sample       const maxval, 
                   pamd_point   const p,
                   const void * const clientdata);
    /* Use this drawproc to trace the outline you want filled.  Use
       the fillhandle as the clientdata.
    */

void
pamd_fill(tuple **         const tuples, 
          int              const cols, 
          int              const rows, 
          int              const depth, 
          sample           const maxval, 
          struct fillobj * const fillObjP,
          pamd_drawproc          drawProc,
          const void *     const clientdata);

    /* Once you've traced the outline, give the fillhandle to this routine to
       do the actual drawing.  As usual, it takes a drawproc and clientdata;
       you could define drawprocs to do stipple fills and such.
    */

/* Text drawing routines. */

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
          const void *  const clientdata);

    /* Draws the null-terminated string 's' left justified at the point ('x',
       'y').  The text will be 'height' tuples high and will be aligned on a
       baseline inclined 'angle' degrees with the X axis.  The supplied
       drawproc and clientdata are passed to pamd_line() which performs the
       actual drawing.
    */

void
pamd_text_box(int          const height, 
              int          const angle, 
              const char * const s, 
              int *        const leftP, 
              int *        const topP, 
              int *        const rightP, 
              int *        const bottomP);
    /* Calculates the extents box for text drawn by pamd_text with the given
       string, size, and orientation.  Most extent box calculations should use
       an angle specification of zero to calculate the unrotated box enclosing
       the text.  If you need the extents of rotated text, however, you can
       call pamd_text_box with a nonzero angle.
    */

#ifdef __cplusplus
}
#endif

