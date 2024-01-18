/*=============================================================================
                               pamcrater
===============================================================================
  Fractal cratering

  This is derived from John Walker's 'pgmcrater' which not only creates
  the terrain map as this program does, but then does a relief filter to
  convert it to a shaded visual image.

  The  algorithm  used  to  determine crater size is as described on
  pages 31 and 32 of:

  Peitgen, H.-O., and Saupe, D. eds., The Science Of Fractal
      Images, New York: Springer Verlag, 1988.

  The  mathematical  technique  used  to calculate crater radii that
  obey the proper area law distribution from a uniformly distributed
  pseudorandom sequence was developed by Rudy Rucker.

  The original program carried this attribution and license:

       Designed and implemented in November of 1989 by:

        John Walker
        Autodesk SA
        Avenue des Champs-Montants 14b
        CH-2074 MARIN
        Switzerland
        Usenet: kelvin@Autodesk.com
        Fax:    038/33 88 15
        Voice:  038/33 76 33

  Permission  to  use, copy, modify, and distribute this software and
  its documentation  for  any  purpose  and  without  fee  is  hereby
  granted,  without any conditions or restrictions.  This software is
  provided "as is" without express or implied warranty.

=============================================================================*/

/* Modifications by Arjen Bax, 2001-06-21: Remove black vertical line at
   right edge. Make craters wrap around the image (enables tiling of image).
 */

#define _XOPEN_SOURCE   /* get M_PI in math.h */

#include <assert.h>
#include <math.h>

#include "pm_c_util.h"
#include "mallocvar.h"
#include "shhopt.h"
#include "nstring.h"
#include "pam.h"


struct CmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    unsigned int number;
    unsigned int height;
    unsigned int width;
    unsigned int randomseedSpec;
    unsigned int randomseed;
    unsigned int verbose;
    unsigned int test;
    unsigned int radius;
    int          offset;
};



static void
parseCommandLine(int argc, const char ** const argv,
                 struct CmdlineInfo * const cmdlineP) {
/*----------------------------------------------------------------------------
   Note that the file spec array we return is stored in the storage that
   was passed to us as the argv array.
-----------------------------------------------------------------------------*/
    optEntry * option_def;
        /* Instructions to OptParseOptions3 on how to parse our options.
         */
    optStruct3 opt;
    unsigned int option_def_index;

    unsigned int numberSpec, heightSpec, widthSpec, radiusSpec, offsetSpec;

    MALLOCARRAY_NOFAIL(option_def, 100);

    option_def_index = 0;   /* incremented by OPTENT3 */
    OPTENT3(0,   "number",     OPT_UINT,    &cmdlineP->number,
            &numberSpec,                 0);
    OPTENT3(0,   "height",     OPT_UINT,    &cmdlineP->height,
            &heightSpec,                 0);
    OPTENT3(0,   "width",      OPT_UINT,    &cmdlineP->width,
            &widthSpec,                  0);
    OPTENT3(0,   "randomseed", OPT_UINT,    &cmdlineP->randomseed,
            &cmdlineP->randomseedSpec,   0);
    OPTENT3(0,   "verbose",    OPT_FLAG,    NULL,
            &cmdlineP->verbose,          0);
    OPTENT3(0,   "test",       OPT_FLAG,    NULL,
            &cmdlineP->test,       0);
    OPTENT3(0,   "radius",     OPT_UINT,    &cmdlineP->radius,
            &radiusSpec,           0);
    OPTENT3(0,   "offset",     OPT_INT,     &cmdlineP->offset,
            &offsetSpec,           0);

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = FALSE;  /* We may have parms that are negative numbers */

    pm_optParseOptions3(&argc, (char **)argv, opt, sizeof(opt), 0);
        /* Uses and sets argc, argv, and some of *cmdlineP and others. */

    if (argc-1 > 0)
        pm_error("There are no non-option arguments.  You specified %u",
                 argc-1);

    if (!heightSpec)
        cmdlineP->height = 256;

    if (cmdlineP->height == 0)
        pm_error("-height must be positive");

    if (!widthSpec)
        cmdlineP->width = 256;

    if (cmdlineP->width == 0)
        pm_error("-width must be positive");

    if (!offsetSpec)
        cmdlineP->offset=0;

    if (cmdlineP->test) {
        if (!radiusSpec)
            pm_error("With -test, you must specify -radius");
        else {
            if(MAX(cmdlineP->height, cmdlineP->width) * 2 < cmdlineP->radius)
                pm_error("Radius (%u) too large", cmdlineP->radius);

            if (numberSpec)
                pm_error("-number is meaningless with -test");

            if (cmdlineP->randomseedSpec)
                pm_error("-randomseed is meaningless with -test");
        }
    } else {
        if (radiusSpec)
            pm_error("-radius is meaningful only with -test");

        if (offsetSpec)
            pm_error("-offset is meaningful only with -test");

        if (!numberSpec)
            cmdlineP->number = 50000;

        if (cmdlineP->number == 0)
            pm_error("-number must be positive");
    }
    free(option_def);
}



static double const arand       = 32767.0;  /* Random number parameters */
static double const CdepthPower = 1.5;      /* Crater depth power factor */
static double const DepthBias2  = 0.5;      /* Square of depth bias */



static double const
cast(double const high) {
/*----------------------------------------------------------------------------
   A random number in the range [0, 'high'].
-----------------------------------------------------------------------------*/
    return high * ((rand() & 0x7FFF) / arand);
}



static unsigned int
mod(int          const t,
    unsigned int const n) {

    /* This is used to transform coordinates beyond bounds into ones
       within: craters "wrap around" the edges.  This enables tiling
       of the image.

       Produces strange effects when crater radius is very large compared
       to image size.
    */

    int m;

    m = t % (int)n;

    if (m < 0)
        m += n;

    return m;
}



static sample *
terrainModP(struct pam * const pamP,
            tuple **     const terrain,
            int          const x,
            int          const y) {
/*----------------------------------------------------------------------------
   A pointer to the sample in 'terrain' of an image described by *pamP that is
   at Column 'x' of Row 'y', but modulus the image size.

   So e.g. if the image is 10 x 10 and 'x' and 'y' are both 12, our value
   would be a pointer to the sample at Column 2 or Row 2.  If they are both
   -1, we would point to Column 9, Row 9.
-----------------------------------------------------------------------------*/
    return &terrain[mod(y, pamP->height)][mod(x, pamP->width)][0];
}




static sample
terrainMod(struct pam * const pamP,
           tuple **     const terrain,
           int          const x,
           int          const y) {
/*----------------------------------------------------------------------------
   The value of the sample in 'terrain' of an image described by *pamP that is
   at Column 'x' of Row 'y', but modulus the image size.

   So e.g. if the image is 10 x 10 and 'x' and 'y' are both 12, our value
   would be the value of the sample at Column 2 or Row 2.  If they are both
   -1, we would return Column 9, Row 9.
-----------------------------------------------------------------------------*/
    return *terrainModP(pamP, terrain, x, y);
}



static void
setElev(struct pam * const pamP,
        tuple **     const terrain,
        int          const cx,
        int          const cy,
        unsigned int const elevation) {

    *terrainModP(pamP, terrain, cx, cy) = MIN(pamP->maxval, elevation);
}



static void
smallCrater(struct pam * const pamP,
            tuple **     const terrain,
            int          const cx,
            int          const cy,
            double       const radius) {
/*----------------------------------------------------------------------------
   Generate a crater with a special method for tiny craters.

   Center the crater at Column 'cx', Row 'cy'; wrap as necessary to get them
   on the canvas.  These might even be negative.
-----------------------------------------------------------------------------*/
    int y;
    unsigned int amptot;
    unsigned int npatch;

    assert(radius < 3);

    /* Set pixel to the average of its Moore neighborhood. */

    for (y = cy - 1, amptot = 0, npatch = 0; y <= cy + 1; ++y) {
        int x;
        for (x = cx - 1; x <= cx + 1; ++x) {
            amptot += terrainMod(pamP, terrain, x, y);
            ++npatch;
        }
    }
    {
        unsigned int const axelev = amptot / npatch;
            /* The mean elevation of the Moore neighborhood (9 pixels
               centered on the crater location).
            */
        
        /* Perturb the mean elevation by a small random factor. */

        int const x = radius >= 1 ? ((rand() >> 8) & 0x3) - 1 : 0;

        assert(axelev > 0);

        setElev(pamP, terrain, cx, cy, axelev + x);
    }
}



static unsigned int
meanElev(struct pam * const pamP,
         tuple **     const terrain,
         int          const cx,
         int          const cy,
         double       const radius) {
/*----------------------------------------------------------------------------
   The mean elevation in 'terrain', which is described by *pamP, within
   'radius' pixels vertically and horizontally of (cx, cy).

   We assume the area is a fraction the whole 'terrain'.
-----------------------------------------------------------------------------*/
    unsigned int amptot;
    unsigned int npatch;
    int y;

    for (y = cy - radius, amptot = 0, npatch = 0; y <= cy + radius; ++y) {
        int x;
        for (x = cx - radius; x <= cx + radius; ++x) {
            amptot += terrainMod(pamP, terrain, x, y);
            ++npatch;
        }
    }
    assert(npatch > 0);

    return amptot / npatch;
}



static void
normalCrater(struct pam * const pamP,
             tuple **     const terrain,
             int          const cx,
             int          const cy,
             double       const radius) {
/*----------------------------------------------------------------------------
   Generate a regular (not tiny) crater.

   Generate an impact feature of the correct size and shape.
----------------------------------------------------------------------------*/
    int    const impactRadius = (int) MAX(2, (radius / 3));
    int    const craterRadius = (int) radius;
    double const rollmin      = 0.9;

    int y;

    unsigned int const axelev = meanElev(pamP, terrain, cx, cy, impactRadius);
        /* The mean elevation of the impact area, before impact */

    for (y = cy - craterRadius; y <= cy + craterRadius; ++y) {
        int const dysq = SQR(cy - y);

        int x;

        for (x = cx - craterRadius; x <= cx + craterRadius; ++x) {
            int  const dxsq = SQR(cx - x);
            double const cd = (dxsq + dysq) / (double) SQR(craterRadius);
            double const cd2 = cd * 2.25;
            double const tcz = sqrt(DepthBias2) - sqrt(fabs(1 - cd2));
            double cz;
            double roll;

            cz = MAX((cd2 > 1) ? 0.0 : -10, tcz);  /* Initial value */

            cz *= pow(craterRadius, CdepthPower);
            if (dysq == 0 && dxsq == 0 && ((int) cz) == 0) {
                cz = cz < 0 ? -1 : 1;
            }

            roll = (((1 / (1 - MIN(rollmin, cd))) /
                     (1 / (1 - rollmin))) - (1 - rollmin)) / rollmin;

            {
                unsigned int av;
                av = (axelev + cz) * (1 - roll) +
                    (terrainMod(pamP, terrain, x, y) + cz) * roll;
                av = MAX(1000, MIN(64000, av));
                
                setElev(pamP, terrain, x, y, av);
            }
        }
    }
}



/* We should also have largeCrater() */



static void
plopCrater(struct pam * const pamP,
           tuple **     const terrain,
           int          const cx,
           int          const cy,
           double       const radius,
           bool         const verbose) {

    if (verbose && pm_have_float_format())
        pm_message("Plopping crater at (%4d, %4d) with radius %g",
                   cx, cy, radius);

    if (radius < 3)
        smallCrater (pamP, terrain, cx, cy, radius);
    else
        normalCrater(pamP, terrain, cx, cy, radius);
}



static void
initCanvas(unsigned int const width,
           unsigned int const height,
           struct pam * const pamP,
           tuple ***    const terrainP) {
/*----------------------------------------------------------------------------
   Initialize the output image to a flat area of middle elevation.
-----------------------------------------------------------------------------*/
    tuple ** terrain;    /* elevation array */
    unsigned int row;

    pamP->size   = sizeof(*pamP);
    pamP->len    = PAM_STRUCT_SIZE(tuple_type);
    pamP->file   = stdout;
    pamP->format = PAM_FORMAT;
    pamP->height = height;
    pamP->width  = width;
    pamP->depth  = 1;
    pamP->maxval = 65535;
    pamP->bytes_per_sample = 2;
    STRSCPY(pamP->tuple_type, "elevation");

    terrain = pnm_allocpamarray(pamP);

    for (row = 0; row < pamP->height; ++row) {
        unsigned int col;
        for (col = 0; col < pamP->width; ++col)
            terrain[row][col][0] = pamP->maxval / 2;
    }
    *terrainP = terrain;
}



static void
genCraters(struct CmdlineInfo const cmdline) {
/*----------------------------------------------------------------------------
   Generate cratered terrain
-----------------------------------------------------------------------------*/
    tuple ** terrain;    /* elevation array */
    struct pam pam;

    /* Allocate the elevation array and initialize it to mean surface
       elevation.
    */

    initCanvas(cmdline.width, cmdline.height, &pam, &terrain);

    if (cmdline.test)
        plopCrater(&pam, terrain,
                   pam.width/2 + cmdline.offset,
                   pam.height/2 + cmdline.offset,
                   (double) cmdline.radius, cmdline.verbose);
    else {
        unsigned int const ncraters = cmdline.number; /* num of craters */
        unsigned int l;

        for (l = 0; l < ncraters; ++l) {
            int const cx = cast((double) pam.width  - 1);
            int const cy = cast((double) pam.height - 1);

            /* Thanks, Rudy, for this equation that maps the uniformly
               distributed numbers from cast() into an area-law distribution
               as observed on cratered bodies.

               Produces values within the interval:
               0.56419 <= radius <= 56.419
            */
            double const radius = sqrt(1 / (M_PI * (1 - cast(0.9999))));

            plopCrater(&pam, terrain, cx, cy, radius, cmdline.verbose);

            if (((l + 1) % 100000) == 0)
                pm_message("%u craters generated of %u (%u%% done)",
                           l + 1, ncraters, ((l + 1) * 100) / ncraters);
        }
    }

    pnm_writepam(&pam, terrain);

    pnm_freepamarray(terrain, &pam);

    pm_close(stdout);
}



int
main(int argc, const char ** argv) {

    struct CmdlineInfo cmdline;

    pm_proginit(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    srand(cmdline.randomseedSpec ? cmdline.randomseed : pm_randseed());

    genCraters(cmdline);

    return 0;
}



