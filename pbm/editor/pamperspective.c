/*
    pamperspective -- a reverse scanline renderer

    Copyright (C) 2004 by Mark Weyer

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#define _XOPEN_SOURCE 500  /* Make sure strdup() is in string.h */
#define _BSD_SOURCE   /* Make sure strdup is int string.h */

#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "pm_c_util.h"
#include "mallocvar.h"
#include "shhopt.h"
#include "pam.h"

typedef double number;

/* There was no reason for exactly this value of eps.
   For compatibility it should only be decreased in future versions.
*/

#define eps 0.0001


/* Multiple choice types for the command line */

typedef enum {image, pixel_u} unit;
const char *const unit_token[3] = {"image", "pixel", NULL};

typedef enum {lattice, pixel_s} coord_system;
const char *const system_token[3] = {"lattice", "pixel", NULL};

/* Note that 'nearest' is a function in AIX's math.h.  So don't use
   that as a symbol.
*/
typedef enum {interp_nearest, interp_linear} interpolation;
const char *const interpolation_token[3] = {"nearest", "linear", NULL};

typedef enum {free_, fixed} proportion;
const char *const proportion_token[3] = {"free", "fixed", NULL};

const char *const bool_token[7] = {"yes", "true", "on",
                                    "no", "false", "off", NULL};
#define first_false_bool_token 3

/* All command line options that have float (actually number) values.
   We use our own parsing technique for these, to handle width/height
   ratios like 4/3
*/

#define num_float_options 15
const char *const float_option_name[num_float_options][3] = {
  {"upper left x", "upper_left_x", "ulx"},
  {"upper left y", "upper_left_y", "uly"},
  {"upper right x", "upper_right_x", "urx"},
  {"upper right y", "upper_right_y", "ury"},
  {"lower left x", "lower_left_x", "llx"},
  {"lower left y", "lower_left_y", "lly"},
  {"lower right x", "lower_right_x", "lrx"},
  {"lower right y", "lower_right_y", "lry"},
  {NULL, "detail", NULL},
  {NULL, "ratio", NULL},
  {NULL, "margin", NULL},
  {NULL, "top_margin", "tmargin"},
  {NULL, "bottom_margin", "bmargin"},
  {NULL, "left_margin", "lmargin"},
  {NULL, "right_margin", "rmargin"}
};

/* All command line options that have multiple choice values (except bools). */

#define num_enum_options 5
const char *const enum_option_name[num_enum_options] = {
  "input_system", "output_system", "input_unit", "interpolation", "proportion"
};
const char *const *const enum_option_type[num_enum_options] = {
  system_token, system_token, unit_token, interpolation_token, proportion_token
};

/* All command line options that have bool values */

#define num_bool_options 1
const char *const bool_option_name[num_bool_options] = {
  "frame_include"
};


/* A linked list node for --include points */

typedef struct include_point_tag {

  /* How the point is given on the command line (for error messages) */

  const char* specification;

  /* coordinates */

  number xi,yi;

  /* link */

  struct include_point_tag* next;

} include_point;


/* The collection of command line options */

typedef struct {

  /* float options */

  number floats[num_float_options];

  /* enum options */

  int enums[num_enum_options];

  /* bool options */

  bool bools[num_bool_options];

  /* flags */

  unsigned int width_spec, height_spec,
    top_margin_spec, left_margin_spec, right_margin_spec, bottom_margin_spec;

  /* Other stuff */

  int width, height;
  const char* infilename;
  include_point* include_points;

} option;


/* The collection of properties that correspond to the four specified
   vertices 
*/

typedef struct {

  /* 2d (image) coordinates of the 4 vertices */

  number xi_ul, yi_ul,  xi_ur, yi_ur,  xi_ll, yi_ll,  xi_lr, yi_lr;

  /* 3d (world) coordinates of the 4 vertices */

  number xw_ul, yw_ul, zw_ul,  xw_ur, yw_ur, zw_ur,
         xw_ll, yw_ll, zw_ll,  xw_lr, yw_lr, zw_lr;

  /* Originally I planned to include the possibility to move the
     center of projection, that is the pixel the camera "looks at".  It
     turned out, maybe surprisingly, that this does not have any
     effect. So now this center is moved to (0,0).
     
     Another original plan was to correct the output parameters
     depending on the lengths of the paralellograms sides or its
     angles.  This is, however, not possible without knowing something
     like the camera angle or focal length (in pixels).
  */
  
  /* The coefficients for the map from output to world coordinates.

     The actual mapping is
     u,v -> (ax+bx*u+cx*v, ay+by*u+cy*v, az+bz*u+cz*v)
  */     
  number ax,bx,cx, ay,by,cy, az,bz,cz;

} world_data;



typedef struct {
/*----------------------------------------------------------------------------
   A buffer of image input.  This holds a vertical window of the input.
-----------------------------------------------------------------------------*/
    unsigned int numRows;
        /* Height of buffer window */
    unsigned int nextImageRow;
        /* Row number of the next image row that will go into the buffer.
           The 'numRows' rows before (above) that are in the buffer now.
        */
    unsigned int nextBufferRow;
        /* Row number in the physical buffer (index of rows[]) where
           the next row read will go (hence where the oldest/highest
           row in the buffer is now).
        */
    tuple ** rows;
        /* The rows of the window, as a cyclic buffer */
    const struct pam * inpamP;
        /* The image from which we fill the buffer */
} buffer;



typedef void interpolateFn(tuple, number, number);

/*
  The following are like MALLOCARRAY_NOFAIL and MALLOCVAR_NOFAIL,
  but abort (fail) the program instead of killing the process with an
  abort signal.
*/

#define MALLOCARRAY_SAFE(handle,length) \
{ \
  MALLOCARRAY(handle,length); \
  if (handle==NULL) \
    pm_error ("Out of memory."); \
}

#define MALLOCVAR_SAFE(handle) \
{ \
  MALLOCVAR(handle); \
  if (handle==NULL) \
    pm_error ("Out of memory."); \
}



static void set_command_line_defaults (option *const options)
{
  options->infilename = "-";
  options->include_points = NULL;
  options->floats[8] = 1.0;             /* --detail               */
  options->floats[9] = 1.0;             /* --ratio                */
  options->floats[10] = 0.0;            /* --margin               */
  options->floats[11] = 0.0;            /* --top_margin           */
  options->floats[12] = 0.0;            /* --bottom_margin        */
  options->floats[13] = 0.0;            /* --left_margin          */
  options->floats[14] = 0.0;            /* --right_margin         */
  options->enums[0] = lattice;          /* --input_system         */
  options->enums[1] = lattice;          /* --output_system        */
  options->enums[2] = pixel_u;          /* --input_unit           */
  options->enums[3] = interp_nearest;   /* --interpolation        */
  options->enums[4] = free_;            /* --proportion           */
  options->bools[0] = TRUE;             /* --frame_include        */
}



static int parse_enum (const char *const text,
                       const char *const *const tokens, const char *const name)
/*----------------------------------------------------------------------------
  Parse an argument given to a multiple choice command line option
-----------------------------------------------------------------------------*/
{
  bool found;
  const char *const * cur_token;
  char* tokenlist;
  int tokenlistlen;
  int value;
  int num_spaces;
  int i;

  /* We find out, whether ^text occurs in ^tokens */

  found = FALSE;
  value = 0;
  while (tokens[value] && !found) {
    if (strcmp (text, tokens[value]))
      value++;
    else
      found = TRUE;
  };

  /* otherwise issue an error */

  if (!found) {
    /* For the error message we want to list the allowed tokens.
       First we have to determine, how much memory we need for that.
    */
    num_spaces = 2;

    tokenlistlen = 0;
    cur_token = tokens;
    while (*cur_token) {
      tokenlistlen += (strlen(*cur_token) + num_spaces);
      cur_token++;
    };
    /* Then we create that list */
    MALLOCARRAY_SAFE(tokenlist, tokenlistlen);
    *tokenlist = 0;
    cur_token = tokens;
    while (*cur_token) {
      for (i=0; i<num_spaces; i++)
    strcat (tokenlist, " ");
      strcat (tokenlist, *cur_token);
      cur_token++;
    };
    /* Finally we issue the error */
    pm_error ("'%s' is not a valid value for --%s.  "
              "Valid values are:  %s", text, name, tokenlist);
    /* pm_error() aborts the program, so there is no memory freeing here. */
  };

  /* If all went well, we return the value associated with the token,
     which happens to be the index where we found the token
  */
  return value;
}



static number
parseFloat(const char * const text) {
/*----------------------------------------------------------------------------
  Parse an argument given to a float command line option.  We cannot
  just call strtod, because we want to parse fractions like "5/3"
-----------------------------------------------------------------------------*/
    bool error;
    char * end;
    number num;
    char * buffer;
    
    buffer = strdup(text);
    if (!buffer)
        pm_error("Out of memory");

    error = FALSE;
    num = strtod(buffer, &end);    /* try strtod anyway */
    switch(*end) {
    case 0:           /* It is a plain number */
        break;
    case '/':         /* It might be a fraction */
        /* (Try to) parse the numerator */
        *end = 0;
        num = strtod(text, &end);
        error = (*end != '\0');
        if (!error) {
            char * const denStart = end + 1;
            number denominator;

            /* Undo the above change */
            *end = '/';
            /* (Try to) parse the denominator */
            denominator = strtod(denStart, &end);
            error = (fabs(denominator) < eps) || (*end != '\0');
            if (!error)
                num /= denominator;
        };
        break;
    default:          /* It is no number format we know */
        error = TRUE;
    };
    if (error)
        pm_error("Invalid number format: %s", text);

    free(buffer);

    return num;
}



static void parse_include_point(char * specification,
                                include_point ** const include_pointsP)
/*----------------------------------------------------------------------------
  Add one point to the front of the linked list of include points
  headed by include_pointsP.

  The point is described by the asciiz string at 'specification'.
----------------------------------------------------------------------------*/
{
  include_point* new_point;
  char* comma_seek;

  MALLOCVAR_SAFE(new_point);
  new_point->specification = specification;
  new_point->next = *include_pointsP;
  *include_pointsP = new_point;

  /* Now we parse the specification */

  for (comma_seek = specification; (*comma_seek != ',') && (*comma_seek != 0);
       comma_seek++);
  if (*comma_seek == 0)
    pm_error ("Invalid format for --include point: '%s'", specification);
  *comma_seek = 0;      /* separate the two parts for parsing purposes */
  new_point->xi = (number) parseFloat(specification);
  new_point->yi = (number) parseFloat(comma_seek+1);
  *comma_seek = ',';
}


static void parse_include_points(const char * const include_opt,
                                 include_point ** const include_pointsP)
/*----------------------------------------------------------------------------
  Process the --include option value include_opt by making a linked list
  of the points it describes (in reverse order).

  Return a pointer to the first element of that linked list as
  *include_pointsP.
----------------------------------------------------------------------------*/
{
    char * cursor;
    char * optWork;
        /* Same as include_opt, except we replace delimiters with nulls
           as we work.
        */

    optWork = strdup(include_opt);
    if (optWork == NULL)
        pm_error("out of memory");

    cursor = &optWork[0];
    while (*cursor != '\0') {
        bool hit_end;
        char * sem_seek;

        for (sem_seek = cursor;
             (*sem_seek != ';') && (*sem_seek != 0);
             sem_seek++);

        hit_end = (*sem_seek == '\0');
            
        *sem_seek = '\0';
        parse_include_point(cursor, include_pointsP);

        if (hit_end)
            cursor = sem_seek;
        else
            cursor = sem_seek+1;
    }
    free(optWork);
}



static void
parseCommandLine(int argc, const char * argv[],
                 option *  const options) {

  const char* float_text[num_float_options];
  unsigned int float_spec[num_float_options];
  char* enum_text[num_enum_options];
  unsigned int enum_spec[num_enum_options];
  char* bool_text[num_bool_options];
  unsigned int bool_spec[num_bool_options];
  char * include_opt;
  unsigned int include_spec;
  int i,j;
  optStruct3 opt;
  unsigned int option_def_index;
  optEntry* option_def;

  set_command_line_defaults(options);

  /* Let shhopt try its best */

  option_def_index = 0;
  MALLOCARRAY_SAFE(option_def,
    (2*num_float_options + num_enum_options + num_bool_options + 3));
  for (i=0; i<num_float_options; i++)
    for (j=1; j<3; j++)
      if (float_option_name[i][j])
        OPTENT3(0, float_option_name[i][j], OPT_STRING,
                &(float_text[i]), &(float_spec[i]), 0);
  for (i=0; i<num_enum_options; i++)
    OPTENT3(0, enum_option_name[i], OPT_STRING,
            &(enum_text[i]), &(enum_spec[i]), 0);
  for (i=0; i<num_bool_options; i++)
    OPTENT3(0, bool_option_name[i], OPT_STRING,
            &(bool_text[i]), &(bool_spec[i]), 0);
  OPTENT3(0, "width", OPT_INT, &(options->width), &(options->width_spec), 0);
  OPTENT3(0, "height", OPT_INT, &(options->height), &(options->height_spec),
          0);
  OPTENT3(0, "include", OPT_STRING, &include_opt, &include_spec, 0);
  opt.opt_table = option_def;
  opt.short_allowed = FALSE;
  opt.allowNegNum = TRUE;
  pm_optParseOptions3 (&argc, (char **)argv, opt, sizeof(opt), 0);

  /* The non-option arguments are optionally all eight coordinates
     and optionally the input filename
  */

  switch (argc-1) {
  case 1:
    options->infilename = argv[1];
  case 0:
    for (i=0; i<8; i++)
      if (!float_spec[i])
        pm_error ("The %s-coordinate was not specified",
                  float_option_name[i][0]);
    break;
  case 9:
    options->infilename = argv[9];
  case 8:
    for (i=0; i<8; i++) {
      float_text[i] = argv[i+1];
      float_spec[i] = 1;
    };
    break;
  default: pm_error ("Wrong (number of) command line arguments");
  };

  if (include_spec)
      parse_include_points(include_opt, &options->include_points);

  /* Parse float options -- shhopt retrieved them as strings */

  for (i=0; i<num_float_options; i++)
    if (float_spec[i])
      options->floats[i] = parseFloat (float_text[i]);

  /* Parse enum options -- shhopt retrieved them as strings */

  for (i=0; i<num_enum_options; i++)
    if (enum_spec[i])
      options->enums[i] = parse_enum (enum_text[i],enum_option_type[i],
                                      enum_option_name[i]);

  /* Parse bool options -- shhopt retrieved them as strings */

  for (i=0; i<num_bool_options; i++)
    if (bool_spec[i])
      options->bools[i] = (first_false_bool_token >
                           parse_enum (bool_text[i], bool_token,
                                       bool_option_name[i]));

  /* Propagate values where necessary */

  if (float_spec[10])           /* --margin */
    for (i=11; i<15; i++)       /* --top_margin through --right_margin */
      if (!(float_spec[i])) {
        options->floats[i] = options->floats[10];
        float_spec[i]=1;
      };
  options->top_margin_spec = float_spec[11];
  options->bottom_margin_spec = float_spec[12];
  options->left_margin_spec = float_spec[13];
  options->right_margin_spec = float_spec[14];

  /* Clean up */

  free(option_def);
}



static void free_option (option *const options)
{
  include_point* current;
  include_point* dispose;

  current = options->include_points;
  while (current != NULL) {
    dispose = current;
    current = current->next;
    free(dispose);
  };
}



static void init_world (option *const options,
                        const struct pam *const inpam, world_data *const world)
{
  /* constructs xi_ul,...,yi_lr

     Internally we use a pixel coordinate system with pixel units

     This also translates the --include points' coordinates
     into the internal system
  */

  number mult_x, mult_y, add_after;
  int add_before;
  include_point* current_include;

  switch (options->enums[0]) {  /* --input_system */
  case lattice:
    add_after = -0.5;
    add_before = 0;
    break;
  case pixel_s:
    add_after = 0.0;
    add_before = -1;
    break;
  };
  switch (options->enums[2]) {  /* --input_unit */
  case image:
    mult_x = (number)((inpam->width) + add_before);
    mult_y = (number)((inpam->height) + add_before);
    break;
  case pixel_u:
    mult_x = 1.0;
    mult_y = 1.0;
    break;
  };

  world->xi_ul = ((number) options->floats[0]) * mult_x + add_after;
  world->yi_ul = ((number) options->floats[1]) * mult_y + add_after;
  world->xi_ur = ((number) options->floats[2]) * mult_x + add_after;
  world->yi_ur = ((number) options->floats[3]) * mult_y + add_after;
  world->xi_ll = ((number) options->floats[4]) * mult_x + add_after;
  world->yi_ll = ((number) options->floats[5]) * mult_y + add_after;
  world->xi_lr = ((number) options->floats[6]) * mult_x + add_after;
  world->yi_lr = ((number) options->floats[7]) * mult_y + add_after;

  for (current_include = options->include_points; current_include != NULL;
       current_include = current_include->next) {
    current_include->xi = current_include->xi * mult_x + add_after;
    current_include->yi = current_include->yi * mult_y + add_after;
  };
}



static bool solve_3_linear_equations (number* x1, number* x2, number* x3,
                                      number const a11, number const a12,
                                      number const a13, number const b1,
                                      number const a21, number const a22,
                                      number const a23, number const b2,
                                      number const a31, number const a32,
                                      number const a33, number const b3)
/*----------------------------------------------------------------------------
  The three equations are
    a11*x1 + a12*x2 + a13*x3 = b1
    a21*x1 + a22*x2 + a23*x3 = b2
    a31*x1 + a32*x2 + a33*x3 = b3
  The return value is whether the system is solvable
----------------------------------------------------------------------------*/
{
  number c11,c12,d1,c21,c22,d2,e,f;
  int pivot;

  /* We do Gaussian elimination.
     Whenever we find the system to be unsolvable, we just return FALSE.
     In this specific case it makes the code clearer.
  */

  if (fabs(a11)<fabs(a21))
    if (fabs(a21)<fabs(a31))
      pivot=3;
    else
      pivot=2;
  else
    if (fabs(a11)<fabs(a31))
      pivot=3;
    else
      pivot=1;

  switch (pivot) {
  case 1:
    if (fabs(a11)<eps) return FALSE;
    c11 = a22-a12*a21/a11;
    c12 = a23-a13*a21/a11;
    d1 =   b2- b1*a21/a11;
    c21 = a32-a12*a31/a11;
    c22 = a33-a13*a31/a11;
    d2 =   b3- b1*a31/a11;
    break;
  case 2:
    if (fabs(a21)<eps) return FALSE;
    c11 = a12-a22*a11/a21;
    c12 = a13-a23*a11/a21;
    d1 =   b1- b2*a11/a21;
    c21 = a32-a22*a31/a21;
    c22 = a33-a23*a31/a21;
    d2 =   b3- b2*a31/a21;
    break;
  case 3:
    if (fabs(a31)<eps) return FALSE;
    c11 = a12-a32*a11/a31;
    c12 = a13-a33*a11/a31;
    d1 =   b1- b3*a11/a31;
    c21 = a22-a32*a21/a31;
    c22 = a23-a33*a21/a31;
    d2 =   b2- b3*a21/a31;
    break;
  }

  /* Now we have a subsystem:
       c11*x2 + c12*x3 = d1
       c21*x2 + c22*x3 = d2
  */

  if (fabs(c11)>fabs(c21)) {
    if (fabs(c11)<eps) return FALSE;
    e = c22-c12*c21/c11;
    f =  d2- d1*c21/c11;
    /* Now we have a single equation e*x3=f */
    if (fabs(e)<eps) return FALSE;
    *x3 = f/e;
    *x2 = (d1-c12*(*x3))/c11;
  }
  else {
    if (fabs(c21)<eps) return FALSE;
    e = c12-c22*c11/c21;
    f =  d1- d2*c11/c21;
    /* Now we have a single equation e*x3=f */
    if (fabs(e)<eps) return FALSE;
    *x3 = f/e;
    *x2 = (d2-c22*(*x3))/c21;
  };

  switch (pivot) {
  case 1:
    *x1 = (b1-a13*(*x3)-a12*(*x2))/a11;
    break;
  case 2:
    *x1 = (b2-a23*(*x3)-a22*(*x2))/a21;
    break;
  case 3:
    *x1 = (b3-a33*(*x3)-a32*(*x2))/a31;
    break;
  };

  return TRUE;
}


static void determine_world_parallelogram (world_data *const world,
                                           const option *const options)
/*----------------------------------------------------------------------------
  Construct xw_ul,...,zw_lr from xi_ul,...,yi_lr
     
  This is a solution of a linear equation system.
  
  We first solve 4 equations for 4 variables (the 4 z-coordinates):
  Each z-coordinate determines the corresponding x- and y-coordinates
  in a linear fashion, where the coefficients are taken from the image
  coordinates.  This corresponds to the fact that a point of an image
  determines a line in the world.
  
  3 equations state that the 4 points form a parallelogram.  The 4th
  equation is for normalization and states that the center of the
  parallelogram has a z-coordinate of 1.
-----------------------------------------------------------------------------*/
{
  number dx1,dx2,dx3,dx4,dx5, dy1,dy2,dy3,dy4,dy5;
  number det;
  number xw_ul,yw_ul,zw_ul, xw_ur,yw_ur,zw_ur,
         xw_ll,yw_ll,zw_ll, xw_lr,yw_lr,zw_lr;
  number top_margin, left_margin, right_margin, bottom_margin;
  include_point* current_include;
  number include_xo, include_yo, include_zw;
  bool solvable, margin_spec;

  dx1 = world->xi_lr - world->xi_ul;  /* d1 is the image diagonal ul -> lr */
  dy1 = world->yi_lr - world->yi_ul;
  dx2 = world->xi_ur - world->xi_ll;  /* d2 is the image diagonal ll -> ur */
  dy2 = world->yi_ur - world->yi_ll;
  dx3 = world->xi_ur - world->xi_ul;  /* d3 is the image side ul -> ur */
  dy3 = world->yi_ur - world->yi_ul;
  dx4 = world->xi_ul - world->xi_ll;  /* d4 is the image side ll -> ul */
  dy4 = world->yi_ul - world->yi_ll;
  dx5 = world->xi_ur - world->xi_lr;  /* d5 is the image side lr -> ur */
  dy5 = world->yi_ur - world->yi_lr;

  det = dx2*dy1 - dx1*dy2;

  /* A determinant of 0 is really bad: It means that that diagonals in the
     image are parallel (or of zero length)
  */

  if ((-eps<det) && (det<eps))
    pm_error ("The specified vertices are degenerated.  "
              "Maybe they were given in the wrong order?");

  zw_ul = 2.0*(dx5*dy2-dx2*dy5)/det;
  zw_ur = 2.0*(dx4*dy1-dx1*dy4)/det;
  zw_ll = 2.0*(dx3*dy1-dx1*dy3)/det;
  zw_lr = 2.0*(dx2*dy3-dx3*dy2)/det;

  /* A zero or negative value for some z means that three of the points
     lie on a line in the image or that the four points do not define
     a convex shape.  We have to forbid this in order to prevent divisions
     by zero later on
  */

  if ((zw_ul<eps) || (zw_ur<eps) || (zw_ll<eps) || (zw_lr<eps))
    pm_error ("The specified vertices are degenerated.  "
              "Maybe they were given in the wrong order?");

  xw_ul = world->xi_ul * zw_ul;
  yw_ul = world->yi_ul * zw_ul;
  xw_ur = world->xi_ur * zw_ur;
  yw_ur = world->yi_ur * zw_ur;
  xw_ll = world->xi_ll * zw_ll;
  yw_ll = world->yi_ll * zw_ll;
  xw_lr = world->xi_lr * zw_lr;
  yw_lr = world->yi_lr * zw_lr;

  /* Now we introduce the margin. There are several ways the margin can be
     defined. margin_spec keeps track of wether one of them has yet been
     used. As long as margin_spec==FALSE, the variables top_margin to
     bottom_margin are not initialized! */

  if (options->bools[0]) {      /* --frame_include */
    top_margin = 0.0;
    left_margin = 0.0;
    right_margin = 0.0;
    bottom_margin = 0.0;
    margin_spec = TRUE;
  } else
    margin_spec = FALSE;

  for (current_include = options->include_points; current_include != NULL;
       current_include = current_include->next) {
    solvable = solve_3_linear_equations(&include_xo, &include_yo, &include_zw,
      xw_ul-xw_ur, xw_ul-xw_ll, current_include->xi, xw_ul,
      yw_ul-yw_ur, yw_ul-yw_ll, current_include->yi, yw_ul,
      zw_ul-zw_ur, zw_ul-zw_ll, 1.0, zw_ul);
    if (!solvable)
      pm_error ("The --include point %s lies on the horizon.",
                current_include->specification);
    if (include_zw<0.0)
      pm_error ("The --include point %s lies beyond the horizon.",
                current_include->specification);
    if (margin_spec) {
      top_margin = MAX(top_margin, -include_yo);
      left_margin = MAX(left_margin, -include_xo);
      right_margin = MAX(right_margin, include_xo-1.0);
      bottom_margin = MAX(bottom_margin, include_yo-1.0);
    } else {
      top_margin = -include_yo;
      left_margin = -include_xo;
      right_margin = include_xo-1.0;
      bottom_margin = include_yo-1.0;
      margin_spec = TRUE;
    };
  }

  if (margin_spec) {    /* the margin is there. --top_margin and such can
                           still enlarge it */
    if (options->top_margin_spec)
      top_margin = MAX(top_margin, options->floats[11]);
    if (options->left_margin_spec)
      left_margin = MAX(left_margin, options->floats[13]);
    if (options->right_margin_spec)
      right_margin = MAX(right_margin, options->floats[14]);
    if (options->bottom_margin_spec)
      bottom_margin = MAX(bottom_margin, options->floats[12]);
  } else                /* the margin is not yet there. --top_margin and
                           such can remedy this only if all of them are
                           given */
    if ((options->top_margin_spec) && (options->left_margin_spec) &&
        (options->right_margin_spec) && (options->bottom_margin_spec)) {
      top_margin = options->floats[11];
      left_margin = options->floats[13];
      right_margin = options->floats[14];
      bottom_margin = options->floats[12];
    } else              /* the margin finally is not there */
      pm_error ("No frame specified. "
                "Use --frame_include=yes or --include or --margin.");

  world->xw_ul = xw_ul
    - top_margin * (xw_ll-xw_ul)
    - left_margin * (xw_ur-xw_ul);
  world->yw_ul = yw_ul
    - top_margin * (yw_ll-yw_ul)
    - left_margin * (yw_ur-yw_ul);
  world->zw_ul = zw_ul
    - top_margin * (zw_ll-zw_ul)
    - left_margin * (zw_ur-zw_ul);
  world->xw_ur = xw_ur
    - top_margin * (xw_lr-xw_ur)
    - right_margin * (xw_ul-xw_ur);
  world->yw_ur = yw_ur
    - top_margin * (yw_lr-yw_ur)
    - right_margin * (yw_ul-yw_ur);
  world->zw_ur = zw_ur
    - top_margin * (zw_lr-zw_ur)
    - right_margin * (zw_ul-zw_ur);
  world->xw_ll = xw_ll
    - bottom_margin * (xw_ul-xw_ll)
    - left_margin * (xw_lr-xw_ll);
  world->yw_ll = yw_ll
    - bottom_margin * (yw_ul-yw_ll)
    - left_margin * (yw_lr-yw_ll);
  world->zw_ll = zw_ll
    - bottom_margin * (zw_ul-zw_ll)
    - left_margin * (zw_lr-zw_ll);
  world->xw_lr = xw_lr
    - bottom_margin * (xw_ur-xw_lr)
    - right_margin * (xw_ll-xw_lr);
  world->yw_lr = yw_lr
    - bottom_margin * (yw_ur-yw_lr)
    - right_margin * (yw_ll-yw_lr);
  world->zw_lr = zw_lr
    - bottom_margin * (zw_ur-zw_lr)
    - right_margin * (zw_ll-zw_lr);

  /* Again we have to forbid nonpositive z */

  if ((world->zw_ul<eps) || (world->zw_ur<eps) ||
       (world->zw_ll<eps) || (world->zw_lr<eps))
    pm_error ("The specified margin is too large.");

}



static unsigned int
distance(unsigned int const a,
         unsigned int const b) {

    return a > b ? a - b : b - a;
}



static number norm_vector (number const x1, number const y1, number const z1,
                           number const x2, number const y2, number const z2)
/*----------------------------------------------------------------------------
  Two 3D vertices p1 and p2 are given by their coordinates.
  A linear movement from p1 to p2, parameterized by the interval [0,1],
  is projected to the input image. The function returns the norm of
  the derivative of this overall movement at time 0, that is at p1.
  The norm uses the max metric.
-----------------------------------------------------------------------------*/
{
  number dx,dy;

  dx = (x2-x1)/z1 - (z2-z1)*x1/(z1*z1);
  dy = (y2-y1)/z1 - (z2-z1)*y1/(z1*z1);

  return MAX (fabs(dx), fabs(dy));
}



static number norm_side (number const x1, number const y1, number const z1,
                         number const x2, number const y2, number const z2)
/*----------------------------------------------------------------------------
  This is similar to norm_vector. But now the norm of the derivative
  is computed at both endpoints of the movement and the maximum is
  returned.
  
  Why do we do this? The return value n is in fact the maximum of the
  norm of the derivative ALONG the movement. So we know that if we
  divide the movement into at least n steps, we will encounter every
  x- and every y-coordinate of the input image between the two points.
  This is our notion of losslessness with --detail=1.
-----------------------------------------------------------------------------*/
{
  return MAX (norm_vector(x1,y1,z1,x2,y2,z2),
              norm_vector(x2,y2,z2,x1,y1,z1));
}



static void determine_output_width_and_height (const world_data *const world,
                                               option *const options)
{
  number du,dv;
  int xsteps,ysteps,width,height;

  /* Determine the number of steps for losslessness */

  du = MAX (norm_side(world->xw_ul, world->yw_ul, world->zw_ul,
                      world->xw_ur, world->yw_ur, world->zw_ur),
            norm_side(world->xw_ll, world->yw_ll, world->zw_ll,
                      world->xw_lr, world->yw_lr, world->zw_lr));
  dv = MAX (norm_side(world->xw_ul, world->yw_ul, world->zw_ul,
                      world->xw_ll, world->yw_ll, world->zw_ll),
            norm_side(world->xw_ur, world->yw_ur, world->zw_ur,
                      world->xw_lr, world->yw_lr, world->zw_lr));
  xsteps = ceil(du*options->floats[8]);  /* option->floats[8] is --detail */
  ysteps = ceil(dv*options->floats[8]);

  /* Turn the numbers of steps into width and height */

  switch (options->enums[1]) {  /* --output_system */
  case lattice:
    width = xsteps;
    height = ysteps;
    break;
  case pixel_s:
    width = xsteps+1;
    height = ysteps+1;
    break;
  };

  /* Correct the proportion of width and height by increasing one of them */

  switch (options->enums[4]) {  /* --proportion */
  case free_:   /* no correction at all */
    break;
  case fixed:   /* correction now */
    /* options->floats[9] is --ratio */
    width = MAX (floor(0.5 + ((number)height) * options->floats[9]),
                 width);
    height = MAX (floor(0.5 + ((number)width) / options->floats[9]),
                  height);
    break;
  };

  /* Override anything we have by the specified width and height */

  if (!(options->width_spec))
    options->width=width;
  if (!(options->height_spec))
    options->height=height;
}



static void determine_coefficients_lattice (world_data *const world,
                                            const option *const options)
/*----------------------------------------------------------------------------
  Constructs ax,...,cz from xw_ul,...,zw_lr
     
  The calculations assume lattice coordinates, that is the point ul
  corresponds to the upper left corner of the pixel (0,0) and the
  point lr corresponds to the lower left corner of the pixel
  (width-1,height-1)
-----------------------------------------------------------------------------*/
{
  number width,height;

  width = (number) options->width;
  height = (number) options->height;

  world->bx = (world->xw_ur - world->xw_ul)/width;
  world->cx = (world->xw_ll - world->xw_ul)/height;
  world->by = (world->yw_ur - world->yw_ul)/width;
  world->cy = (world->yw_ll - world->yw_ul)/height;
  world->bz = (world->zw_ur - world->zw_ul)/width;
  world->cz = (world->zw_ll - world->zw_ul)/height;

  world->ax = world->xw_ul + world->bx/2.0 + world->cx/2.0;
  world->ay = world->yw_ul + world->by/2.0 + world->cy/2.0;
  world->az = world->zw_ul + world->bz/2.0 + world->cz/2.0;
}



static void determine_coefficients_pixel (world_data *const world,
                                          const option *const options)
/*----------------------------------------------------------------------------
  Constructs ax,...,cz from xw_ul,...,zw_lr
     
  The calculations assume pixel coordinates, that is the point ul
  corresponds to the center of the pixel (0,0) and the point lr
  corresponds to the center of the pixel (width-1,height-1)
-----------------------------------------------------------------------------*/
{
  number width,height;

  if (options->width == 1)
    pm_error ("You specified 'pixel' as output coordinate model "
              "and a width of 1.  These things don't mix.");
  if (options->height == 1)
    pm_error ("You specified 'pixel' as output coordinate model "
              "and a height of 1.  These things don't mix.");

  width = (number) (options->width-1);
  height = (number) (options->height-1);

  world->bx = (world->xw_ur - world->xw_ul)/width;
  world->cx = (world->xw_ll - world->xw_ul)/height;
  world->by = (world->yw_ur - world->yw_ul)/width;
  world->cy = (world->yw_ll - world->yw_ul)/height;
  world->bz = (world->zw_ur - world->zw_ul)/width;
  world->cz = (world->zw_ll - world->zw_ul)/height;

  world->ax = world->xw_ul;
  world->ay = world->yw_ul;
  world->az = world->zw_ul;
}



static void
outpixelToInPos(int                const outCol,
                int                const outRow, 
                number *           const inColP,
                number *           const inRowP,
                const world_data * const worldP) {
/*----------------------------------------------------------------------------
   For a pixel of the output image at Column 'outCol', row 'outRow',
   determine the position in the input image that corresponds to the
   center of that pixel.

   This position is not a pixel position -- it's a position in
   continuous space, for example Row 9.2, Column 0.1.  And it isn't
   necessarily within the input image, for example Column 600 even though
   the input image is only 500 pixels wide, and a coordinate might even
   be negative.
-----------------------------------------------------------------------------*/
    number const outColF = (number) outCol;
    number const outRowF = (number) outRow;

    number const xw = worldP->ax + worldP->bx * outColF + worldP->cx * outRowF;
    number const yw = worldP->ay + worldP->by * outColF + worldP->cy * outRowF;
    number const zw = worldP->az + worldP->bz * outColF + worldP->cz * outRowF;

    *inColP = xw/zw;
    *inRowP = yw/zw;
}



static int
outpixelToInRow(int                const outCol,
                int                const outRow,
                const world_data * const worldP) {

    number xi, yi;

    outpixelToInPos(outCol, outRow, &xi, &yi, worldP);

    return (int) yi;
}



static int
boundedRow(int                const unboundedRow,
           const struct pam * const outpamP) {

    return MIN(MAX(0, unboundedRow), outpamP->height-1);
}



#if 0
/* This is the original calculation of window height.  It's
   mysterious, and doesn't work.  It looks like it basically wants to
   take the greater of vertical displacement of the top edge of the
   input quadrilateral and that of the bottom edge.  In simple
   scenarios, that is in fact what it does, and I can see how those
   edges might be where the most stretching takes place.  However, it
   the calculation is obviously more complex than that.

   It doesn't work because the actual image generation produces rows
   in the middle that are derived from lines in the input quadrilateral
   with greater slope than either the top or bottom edge.  I.e. to
   compute one output row, it needs more rows of input than this 
   calculation provides.

   I don't know if that means the computation of the output is wrong
   or the computation of the window height is wrong.  The code is too
   opaque.  But just to make a viable computation, I replaced the
   window height calculation with the brute force computation you
   see below: it determines the vertical displacement of every line
   of the input quadrilateral that is used to generate an output row
   and takes the greatest of them for the window height.

   - Bryan Henderson 08.07.27.
*/
   

static unsigned int
windowHeight(const world_data * const worldP,
             const struct pam * const inpamP,
             const struct pam * const outpamP,
             const option *     const optionsP) {

    unsigned int numRows;
    int yul, yur, yll, ylr, y_min;

    yul = outpixelToInRow(0, 0, worldP);
    yur = outpixelToInRow(outpamP->width-1, 0, worldP);
    yll = outpixelToInRow(0, outpamP->height-1, worldP);
    ylr = outpixelToInRow(outpamP->width-1, outpamP->height-1, worldP);
    
    y_min = MIN(MIN(yul, yur), MIN(yll, ylr));
    numRows = MAX(MAX(diff(yul, yur),
                      diff(yll, ylr)),
                  MAX(diff(boundedRow(yul, outpamP),
                           boundedRow(y_min, outpamP)),
                      diff(boundedRow(yur, outpamP),
                           boundedRow(y_min, outpamP))))
        + 2;
    switch (optionsP->enums[3]) {  /* --interpolation */
    case interp_nearest:
        break;
    case interp_linear:
        numRows += 1;
        break;
    }
    if (numRows > inpamP->height)
        numRows = inpamP->height;

    return numRows;
}
#endif



static unsigned int
windowHeight(const world_data * const worldP,
             const struct pam * const inpamP,
             const struct pam * const outpamP,
             const option *     const optionsP) {

    unsigned int outRow;
    unsigned int maxRowWindowHeight;
    
    maxRowWindowHeight = 1;  /* initial value */

    for (outRow = 0; outRow < outpamP->height; ++outRow) {
        unsigned int const leftCol = 0;
        unsigned int const rghtCol = outpamP->width - 1;
        unsigned int const leftInRow =
            boundedRow(outpixelToInRow(leftCol, outRow, worldP), outpamP);
        unsigned int const rghtInRow =
            boundedRow(outpixelToInRow(rghtCol, outRow, worldP), outpamP);
        
        unsigned int const rowWindowHeight = distance(leftInRow, rghtInRow);

        maxRowWindowHeight = MAX(maxRowWindowHeight, rowWindowHeight);
    }
    
    /* We add 2 for rounding */

    return maxRowWindowHeight + 2;
}



static void
buffer_init(buffer *           const bufferP,
            const world_data * const worldP,
            const option *     const optionsP,
            const struct pam * const inpamP,
            const struct pam * const outpamP) {

    unsigned int const numRows =
        windowHeight(worldP, inpamP, outpamP, optionsP);

    unsigned int row;

    MALLOCARRAY_SAFE(bufferP->rows, numRows);

    for (row = 0; row < numRows; ++row) {
        bufferP->rows[row] = pnm_allocpamrow(inpamP);
        pnm_readpamrow(inpamP, bufferP->rows[row]);
    }

    bufferP->nextImageRow  = numRows;
    bufferP->nextBufferRow = 0;
    bufferP->numRows       = numRows;

    bufferP->inpamP = inpamP;
}



static const tuple *
buffer_getRow(buffer *     const bufferP,
              unsigned int const imageRow) {
/*----------------------------------------------------------------------------
   Return row 'imageRow' of an image.

   The return value is a pointer into storage that belongs to *bufferP.

   *bufferP remembers only a window of the image, and the window
   cannot move up, so 'imageRow' cannot be higher in the image than
   the lowest row read so far through *bufferP plus *bufferP's maximum
   window height.  We assume that.
-----------------------------------------------------------------------------*/
    unsigned int bufferRow;
        /* The row of the buffer that holds row 'imageRow' of the image */
    unsigned int n;
        /* Number of rows our row is before the bottom of the window */

    assert(imageRow >= bufferP->nextImageRow - bufferP->numRows);
        /* The requested row is not one that's already been bumped out
           of the buffer.
        */

    while (imageRow >= bufferP->nextImageRow) {
        pnm_readpamrow(bufferP->inpamP, bufferP->rows[bufferP->nextBufferRow]);

        ++bufferP->nextBufferRow;
        if (bufferP->nextBufferRow == bufferP->numRows)
            bufferP->nextBufferRow = 0;

        ++bufferP->nextImageRow;
    }

    n = bufferP->nextImageRow - imageRow;

    assert(n <= bufferP->numRows);
    
    if (n <= bufferP->nextBufferRow)
        bufferRow = bufferP->nextBufferRow - n;
    else
        bufferRow = bufferP->nextBufferRow + bufferP->numRows - n;

    assert(bufferRow < bufferP->numRows);

    return bufferP->rows[bufferRow];
}



static void
buffer_term(buffer * const bufferP) {

    unsigned int i;

    /* We have to read through the end of the input image even if we
       didn't use all the rows, because if the input is a pipe, the
       guy writing into the pipe may require all the data to go
       through.
    */

    while (bufferP->nextImageRow < bufferP->inpamP->height) {
        pnm_readpamrow(bufferP->inpamP, bufferP->rows[0]);
        ++bufferP->nextImageRow;
    }

    for (i = 0; i < bufferP->numRows; ++i)
        pnm_freepamrow(bufferP->rows[i]);
    
    free(bufferP->rows);
}




struct interpContext {
    tuple background;
    buffer* indata;
    int width,height,depth;
};

/* The following is global for speed reasons.
   In this way it does not have to be passed to each call of the
   interpolation functions

   Think of this as Sch&ouml;nfinkeling (aka Currying).
*/

static struct interpContext ictx;

static void
init_interpolation_global_vars(buffer *           const inbufferP,
                               const struct pam * const inpamP,
                               const struct pam * const outpamP) {

    pnm_createBlackTuple(outpamP, &ictx.background);
    ictx.indata = inbufferP;
    ictx.width  = inpamP->width;
    ictx.height = inpamP->height;
    ictx.depth  = outpamP->depth;
}



static void
clean_interpolation_global_vars(void) {

    free(ictx.background);
}



/* These functions perform the interpolation */

static tuple
getPixel(int const col,
         int const row) {
/*----------------------------------------------------------------------------
   Get the pixel at Row 'row', Column 'col' of the image which is the
   context of the interpolation in which we are called.

   Consider the image to go on forever in all directions (even negative
   column/row numbers), being the background color everywhere outside
   the actual image.
-----------------------------------------------------------------------------*/
    if ((col < 0) || (col >= ictx.width) || (row < 0) || (row >= ictx.height))
        return ictx.background;
    else
        return buffer_getRow(ictx.indata, row)[col];
}



static void
takeNearest(tuple  const dest,
            number const x,
            number const y) {

    int   const xx = (int)floor(x+0.5);
    int   const yy = (int)floor(y+0.5);
    tuple const p  = getPixel(xx, yy);

    unsigned int entry;

    for (entry = 0; entry < ictx.depth; ++entry) {
        dest[entry] = p[entry];
    }
}



static void
linearInterpolation(tuple  const dest, 
                    number const x,
                    number const y) {

    int    const xx = (int)floor(x);
    int    const yy = (int)floor(y);
    number const xf = x - (number)xx;
    number const yf = y - (number)yy;
    tuple  const p1 = getPixel(xx, yy);
    tuple  const p2 = getPixel(xx+1, yy);
    tuple  const p3 = getPixel(xx, yy+1);
    tuple  const p4 = getPixel(xx+1, yy+1);
    number const a  = (1.0-xf) * (1.0-yf);
    number const b  = xf * (1.0-yf);
    number const c  = (1.0-xf) * yf;
    number const d  = xf * yf;

    unsigned int entry;

    for (entry=0; entry < ictx.depth; ++entry) {
        dest[entry] = floor(
            a * (number) p1[entry] +
            b * (number) p2[entry] +
            c * (number) p3[entry] +
            d * (number) p4[entry] +
            0.5);
    }
}



static void
perspective(struct pam * const outpamP,
            world_data * const worldP,
            interpolateFn *    interpolater) {

    tuple * outrow;
    unsigned int row;

    outrow = pnm_allocpamrow(outpamP);

    for (row = 0; row < outpamP->height; ++row) {
        unsigned int col;

        for (col = 0; col < outpamP->width; ++col) {
            number xi, yi;
            outpixelToInPos(col, row, &xi, &yi, worldP);
            interpolater(outrow[col], xi, yi);
        }
        pnm_writepamrow(outpamP, outrow);
    }
    pnm_freepamrow(outrow);
}



int
main(int argc, const char * argv[]) {

    FILE * ifP;
    struct pam inpam;
    buffer inbuffer;
    struct pam outpam;
    option options;
    world_data world;
    interpolateFn * interpolater;

    pm_proginit(&argc, argv);

    parseCommandLine(argc, argv, &options);

    ifP = pm_openr(options.infilename);

    pnm_readpaminit(ifP, &inpam, PAM_STRUCT_SIZE(tuple_type));

    /* Our own initializations */

    init_world(&options, &inpam, &world);
    determine_world_parallelogram(&world, &options);
    determine_output_width_and_height(&world, &options);
    switch (options.enums[1]) {   /* --output_system */
    case lattice:
        determine_coefficients_lattice(&world, &options);
        break;
    case pixel_s:
        determine_coefficients_pixel(&world, &options);
        break;
    };

    outpam.size             = sizeof(outpam);
    outpam.len              = PAM_STRUCT_SIZE(bytes_per_sample);
    outpam.file             = stdout;
    outpam.format           = inpam.format;
    outpam.plainformat      = FALSE;
    outpam.height           = options.height;
    outpam.width            = options.width;
    outpam.depth            = inpam.depth;
    outpam.maxval           = inpam.maxval;
    outpam.bytes_per_sample = inpam.bytes_per_sample;
    pnm_writepaminit(&outpam);

    /* Initialize the actual calculation */

    buffer_init(&inbuffer, &world, &options, &inpam, &outpam);
    init_interpolation_global_vars(&inbuffer, &inpam, &outpam);
    switch (options.enums[3]) {   /* --interpolation */
    case interp_nearest:
        interpolater = takeNearest;
        break;
    case interp_linear:
        interpolater = linearInterpolation;
        break;
    };

    perspective(&outpam, &world, interpolater);

    clean_interpolation_global_vars();
    buffer_term(&inbuffer);
    free_option(&options);
    pm_close(ifP);
    pm_close(stdout);

    return 0;
}
