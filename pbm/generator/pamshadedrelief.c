/*=============================================================================
                               pamshaderelief
===============================================================================
  Generate a shaded relief image of terrain, given a terrain map - a two
  dimensional map of elevations.  A shaded relief image is an image of
  what terrain with the given elevations would look like illuminated by
  oblique light.

  The input array is a one-channel PAM image.  The sample values are
  elevations of terrain.
  
  This is derived from John Walker's 'pgmcrater' which not only does this
  shading, but first generates a terrain map of fractal craters on which to
  run it.


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

/* Modifications by Arjen Bax, 2001-06-21: Remove black vertical line at right
   edge.
*/

#define _XOPEN_SOURCE   /* get M_PI in math.h */

#include <assert.h>
#include <math.h>

#include "pm_c_util.h"
#include "mallocvar.h"
#include "nstring.h"
#include "shhopt.h"
#include "pam.h"



struct CmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    const char * inputFileName;
    float        gamma;
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

    unsigned int gammaSpec;

    MALLOCARRAY_NOFAIL(option_def, 100);

    option_def_index = 0;   /* incremented by OPTENT3 */
    OPTENT3(0,   "gamma",    OPT_FLOAT,   &cmdlineP->gamma,
            &gammaSpec,       0);

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = FALSE;  /* We may have parms that are negative numbers */

    pm_optParseOptions3(&argc, (char **)argv, opt, sizeof(opt), 0);
        /* Uses and sets argc, argv, and some of *cmdlineP and others. */

    if (!gammaSpec)
        cmdlineP->gamma = 1.0;

    if (cmdlineP->gamma <= 0.0)
        pm_error("gamma correction must be greater than 0");

    if (argc-1 == 0) 
        cmdlineP->inputFileName = "-";
    else if (argc-1 != 1)
        pm_error("Program takes zero or one argument (filename).  You "
                 "specified %u", argc-1);
    else
        cmdlineP->inputFileName = argv[1];

    free(option_def);
}



/* Definitions for obtaining random numbers. */

/*  Display parameters  */

static double const ImageGamma = 0.5;     /* Inherent gamma of mapped image */
static int    const slopemin   = -52;
static int    const slopemax   = 52;



static void
generateSlopeGrayMap(sample * const slopeGrayMap,
                     double   const dgamma) {
/*----------------------------------------------------------------------------
   Map each possible slope to the brightness that terrain with that
   left-to-right slope should have in the shaded relief.

   The brightness is what would result from light incident from the left
   falling on the terrain.
-----------------------------------------------------------------------------*/
    double const gamma = dgamma * ImageGamma;

    int i;

    for (i = slopemin; i <= 0; ++i) {   /* Negative, downhill, dark */
        slopeGrayMap[i - slopemin] =
            128 - 127.0 * pow(sin((M_PI / 2) * i / slopemin), gamma);
    }
    for (i = 0; i <= slopemax; ++i) {   /* Positive, uphill, bright */
        slopeGrayMap[i - slopemin] =
            128 + 127.0 * pow(sin((M_PI / 2) * i / slopemax), gamma);
    }

    /* Confused?   OK,  we're using the  left-to-right slope to
       calculate a shade based on the sine of  the  angle  with
       respect  to the vertical (light incident from the left).
       Then, with one exponentiation, we account for  both  the
       inherent   gamma   of   the   image  (ad-hoc),  and  the
       user-specified display gamma, using the identity:
       (x^y)^z = (x^(y*z))
    */
}



static gray
brightnessOfSlope(int      const slope,
                  sample * const slopeGrayMap) {

    return slopeGrayMap[MIN(MAX(slopemin, slope), slopemax) - slopemin];
}



static void
writeShadedRelief(struct pam * const terrainPamP,
                  tuple **     const terrain,
                  double       const dgamma,
                  FILE *       const ofP) {

    unsigned int row;
    tuple * outrow;
    sample * slopeGrayMap; /* Slope to gray value map */
    struct pam outpam;

    outpam.size   = sizeof(outpam);
    outpam.len    = PAM_STRUCT_SIZE(tuple_type);
    outpam.file   = ofP;
    outpam.format = PAM_FORMAT;
    outpam.height = terrainPamP->height;
    outpam.width  = terrainPamP->width;
    outpam.depth  = 1;
    outpam.maxval = 255;
    outpam.bytes_per_sample = 1;
    STRSCPY(outpam.tuple_type, "GRAYSCALE");

    outrow = pnm_allocpamrow(&outpam);

    pnm_writepaminit(&outpam);

    MALLOCARRAY(slopeGrayMap, slopemax - slopemin + 1);

    generateSlopeGrayMap(slopeGrayMap, dgamma);

    for (row = 0; row < terrainPamP->height; ++row) {
        unsigned int col;

        for (col = 0; col < terrainPamP->width - 1; ++col) {
            int const slope = terrain[row][col+1][0] - terrain[row][col][0];
            outrow[col][0] = brightnessOfSlope(slope, slopeGrayMap);
        }
        {
            /* Wrap around to determine shade of pixel on right edge */
            int const slope = 
                terrain[row][0][0] - terrain[row][outpam.width-1][0];
            outrow[outpam.width - 1][0] =
                brightnessOfSlope(slope, slopeGrayMap);
        }
        pnm_writepamrow(&outpam, outrow);
    }

    free(slopeGrayMap);
    pnm_freepamrow(outrow);
}



static void
readTerrain(FILE *       const ifP,
            struct pam * const pamP,
            tuple ***    const tuplesP) {

    *tuplesP = pnm_readpam(ifP, pamP, PAM_STRUCT_SIZE(tuple_type));
}
            
            

int
main(int argc, const char ** argv) {

    struct CmdlineInfo cmdline;
    FILE * ifP;
    struct pam terrainPam;
    tuple ** terrain;
        /* Array of elevations */

    pm_proginit(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    ifP = pm_openr(cmdline.inputFileName);

    readTerrain(ifP, &terrainPam, &terrain);

    writeShadedRelief(&terrainPam, terrain, cmdline.gamma, stdout);
    
    return 0;
}


