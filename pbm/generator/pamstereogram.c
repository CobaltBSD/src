/* ----------------------------------------------------------------------
 *
 * Create a single image stereogram from a height map.
 * by Scott Pakin <scott+pbm@pakin.org>
 * Adapted to Netbpm conventions by Bryan Henderson.
 * Revised by Scott Pakin.
 *
 * The core of this program is a simple adaptation of the code in
 * "Displaying 3D Images: Algorithms for Single Image Random Dot
 * Stereograms" by Harold W. Thimbleby, Stuart Inglis, and Ian
 * H. Witten in IEEE Computer, 27(10):38-48, October 1994 plus some
 * enhancements presented in "Stereograms: Technical Details" by
 * W. A. Steer at http://www.techmind.org/stereo/stech.html.  See
 * those references for a thorough explanation of what's going on
 * here.
 *
 * ----------------------------------------------------------------------
 *
 * Copyright (C) 2006-2015 Scott Pakin <scott+pbm@pakin.org>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ----------------------------------------------------------------------
 */

#define _ISOC99_SOURCE  /* Make sure strtof() is in <stdlib.h> */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <assert.h>

#include "pm_config.h"
#include "pm_c_util.h"
#include "mallocvar.h"
#include "nstring.h"
#include "shhopt.h"
#include "pam.h"


enum outputType {OUTPUT_BW, OUTPUT_GRAYSCALE, OUTPUT_COLOR};

/* ---------------------------------------------------------------------- */

struct cmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    const char * inputFilespec;  /* '-' if stdin */
    unsigned int verbose;        /* -verbose option */
    unsigned int crosseyed;      /* -crosseyed option */
    unsigned int makemask;       /* -makemask option */
    unsigned int dpi;            /* -dpi option */
    float        eyesep;         /* -eyesep option */
    float        depth;          /* -depth option */
    unsigned int maxvalSpec;     /* -maxval option count */
    unsigned int maxval;         /* -maxval option value */
    unsigned int guidetop;       /* -guidetop option count */
    unsigned int guidebottom;    /* -guidebottom option count */
    unsigned int guidesize;      /* -guidesize option value */
    unsigned int magnifypat;     /* -magnifypat option */
    int xshift;                  /* -xshift option */
    int yshift;                  /* -yshift option */
    const char * patfile;        /* -patfile option.  Null if none */
    const char * texfile;        /* -texfile option.  Null if none */
    const char * bgcolor;        /* -bgcolor option */
    unsigned int smoothing;      /* -smoothing option */
    unsigned int randomseed;     /* -randomseed option */
    unsigned int randomseedSpec; /* -randomseed option count */
    enum outputType outputType;  /* Type of output file */
    unsigned int xbegin;         /* -xbegin option */
    unsigned int xbeginSpec;     /* -xbegin option count */
};



static void
parseNearFarPlanes(const char ** const nearFarPlanes,
                   float *       const nearPlaneP,
                   float *       const farPlaneP) {
/*----------------------------------------------------------------------------
  Parse nearFarPlanes option value into exactly two positive numbers
-----------------------------------------------------------------------------*/
    float nearPlane, farPlane;

    if (nearFarPlanes == NULL || nearFarPlanes[0] == NULL ||
        nearFarPlanes[1] == NULL || nearFarPlanes[2] != NULL)
        pm_error("-planes requires exactly two positive numbers");

    errno = 0;
    nearPlane = strtof(nearFarPlanes[0], NULL);
    if (errno != 0 || nearPlane <= 0.0)
        pm_error("-planes requires exactly two positive numbers");

    farPlane = strtof(nearFarPlanes[1], NULL);
    if (errno != 0 || farPlane <= 0.0)
        pm_error("-planes requires exactly two positive numbers");

    if (nearPlane >= farPlane)
        pm_error("-planes requires the near-plane value "
                 "to be less than the far-plane value");

    *nearPlaneP = nearPlane;
    *farPlaneP  = farPlane;
}



static void
parseCommandLine(int                  argc,
                 const char **        argv,
                 struct cmdlineInfo * cmdlineP ) {
/*----------------------------------------------------------------------------
   Parse program command line described in Unix standard form by argc
   and argv.  Return the information in the options as *cmdlineP.

   If command line is internally inconsistent (invalid options, etc.),
   issue error message to stderr and abort program.

   Note that the strings we return are stored in the storage that
   was passed to us as the argv array.  We also trash *argv.
-----------------------------------------------------------------------------*/
    optEntry *option_def;
        /* Instructions to pm_optParseOptions3 on how to parse our options.
         */
    optStruct3 opt;

    unsigned int option_def_index;

    unsigned int patfileSpec, texfileSpec, dpiSpec, eyesepSpec, depthSpec,
        guidesizeSpec, magnifypatSpec, xshiftSpec, yshiftSpec,
      bgcolorSpec, smoothingSpec, planesSpec;

    unsigned int blackandwhite, grayscale, color;
    const char ** planes;

    MALLOCARRAY_NOFAIL(option_def, 100);

    option_def_index = 0;   /* incremented by OPTENT3 */
    OPTENT3(0, "verbose",         OPT_FLAG,   NULL,
            (unsigned int *)&cmdlineP->verbose,       0);
    OPTENT3(0, "crosseyed",       OPT_FLAG,   NULL,
            &cmdlineP->crosseyed,     0);
    OPTENT3(0, "makemask",        OPT_FLAG,   NULL,
            &cmdlineP->makemask,      0);
    OPTENT3(0, "blackandwhite",   OPT_FLAG,   NULL,
            &blackandwhite,           0);
    OPTENT3(0, "grayscale",       OPT_FLAG,   NULL,
            &grayscale,               0);
    OPTENT3(0, "color",           OPT_FLAG,   NULL,
            &color,                   0);
    OPTENT3(0, "dpi",             OPT_UINT,   &cmdlineP->dpi,
            &dpiSpec,                 0);
    OPTENT3(0, "eyesep",          OPT_FLOAT,  &cmdlineP->eyesep,
            &eyesepSpec,              0);
    OPTENT3(0, "depth",           OPT_FLOAT,  &cmdlineP->depth,
            &depthSpec,               0);
    OPTENT3(0, "maxval",          OPT_UINT,   &cmdlineP->maxval,
            &cmdlineP->maxvalSpec,    0);
    OPTENT3(0, "guidetop",        OPT_FLAG,   NULL,
            &cmdlineP->guidetop,      0);
    OPTENT3(0, "guidebottom",     OPT_FLAG,   NULL,
            &cmdlineP->guidebottom,   0);
    OPTENT3(0, "guidesize",       OPT_UINT,   &cmdlineP->guidesize,
            &guidesizeSpec,           0);
    OPTENT3(0, "magnifypat",      OPT_UINT,   &cmdlineP->magnifypat,
            &magnifypatSpec,          0);
    OPTENT3(0, "xshift",          OPT_INT,    &cmdlineP->xshift,
            &xshiftSpec,              0);
    OPTENT3(0, "yshift",          OPT_INT,    &cmdlineP->yshift,
            &yshiftSpec,              0);
    OPTENT3(0, "patfile",         OPT_STRING, &cmdlineP->patfile,
            &patfileSpec,             0);
    OPTENT3(0, "texfile",         OPT_STRING, &cmdlineP->texfile,
            &texfileSpec,             0);
    OPTENT3(0, "bgcolor",         OPT_STRING, &cmdlineP->bgcolor,
            &bgcolorSpec,             0);
    OPTENT3(0, "randomseed",      OPT_UINT,   &cmdlineP->randomseed,
            &cmdlineP->randomseedSpec, 0);
    OPTENT3(0, "smoothing",       OPT_UINT,   &cmdlineP->smoothing,
            &smoothingSpec,           0);
    OPTENT3(0, "planes",          OPT_STRINGLIST, &planes,
            &planesSpec,              0);
    OPTENT3(0, "xbegin",          OPT_UINT,   &cmdlineP->xbegin,
            &cmdlineP->xbeginSpec,    0);

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = FALSE;  /* We have no parms that are negative numbers */

    pm_optParseOptions3(&argc, (char **)argv, opt, sizeof(opt), 0);
        /* Uses and sets argc, argv, and some of *cmdlineP and others. */

    if (blackandwhite + grayscale + color == 0)
        cmdlineP->outputType = OUTPUT_BW;
    else if (blackandwhite + grayscale + color > 1)
        pm_error("You may specify only one of -blackandwhite, -grayscale, "
                 "and -color");
    else {
        if (blackandwhite)
            cmdlineP->outputType = OUTPUT_BW;
        else if (grayscale)
            cmdlineP->outputType = OUTPUT_GRAYSCALE;
        else {
            assert(color);
            cmdlineP->outputType = OUTPUT_COLOR;
        }
    }
    if (!patfileSpec)
        cmdlineP->patfile = NULL;
    if (!texfileSpec)
        cmdlineP->texfile = NULL;
    if (!bgcolorSpec)
        cmdlineP->bgcolor = NULL;
    if (!smoothingSpec)
        cmdlineP->smoothing = 0;

    if (!dpiSpec)
        cmdlineP->dpi = 100;
    else if (cmdlineP->dpi < 1)
        pm_error("The argument to -dpi must be a positive integer");

    if (!eyesepSpec)
        cmdlineP->eyesep = 2.56;
    else if (cmdlineP->eyesep <= 0.0)
        pm_error("The argument to -eyesep must be a positive number");

    if (!depthSpec)
        cmdlineP->depth = (1.0/3.0);
    else if (cmdlineP->depth < 0.0 || cmdlineP->depth > 1.0)
        pm_error("The argument to -depth must be a number from 0.0 to 1.0");

    if (cmdlineP->maxvalSpec) {
        if (cmdlineP->maxval < 1)
            pm_error("-maxval must be at least 1");
        else if (cmdlineP->maxval > PNM_OVERALLMAXVAL)
            pm_error("-maxval must be at most %u.  You specified %u",
                     PNM_OVERALLMAXVAL, cmdlineP->maxval);
    }
    if (bgcolorSpec && !texfileSpec)
        pm_message("warning: -bgcolor has no effect "
                   "except in conjunction with -texfile");

    if (guidesizeSpec && !(cmdlineP->guidetop || cmdlineP->guidebottom))
        pm_error("-guidesize has no meaning "
                 "without -guidetop or -guidebottom");

    if (!guidesizeSpec)
        cmdlineP->guidesize = 20;

    if (!magnifypatSpec)
        cmdlineP->magnifypat = 1;
    else if (cmdlineP->magnifypat < 1)
        pm_error("The argument to -magnifypat must be a positive integer");

    if (!xshiftSpec)
        cmdlineP->xshift = 0;

    if (!yshiftSpec)
        cmdlineP->yshift = 0;

    if (xshiftSpec && !cmdlineP->patfile)
        pm_error("-xshift is valid only with -patfile");
    if (yshiftSpec && !cmdlineP->patfile)
        pm_error("-yshift is valid only with -patfile");

    if (cmdlineP->makemask && cmdlineP->patfile)
        pm_error("You may not specify both -makemask and -patfile");

    if (cmdlineP->patfile && blackandwhite)
        pm_error("-blackandwhite is not valid with -patfile");
    if (cmdlineP->patfile && grayscale)
        pm_error("-grayscale is not valid with -patfile");
    if (cmdlineP->patfile && color)
        pm_error("-color is not valid with -patfile");
    if (cmdlineP->patfile && cmdlineP->maxvalSpec)
        pm_error("-maxval is not valid with -patfile");

    if (cmdlineP->texfile && blackandwhite)
        pm_error("-blackandwhite is not valid with -texfile");
    if (cmdlineP->texfile && grayscale)
        pm_error("-grayscale is not valid with -texfile");
    if (cmdlineP->texfile && color)
        pm_error("-color is not valid with -texfile");
    if (cmdlineP->texfile && cmdlineP->maxvalSpec)
        pm_error("-maxval is not valid with -texfile");
    if (planesSpec && eyesepSpec)
        pm_error("-planes is not valid with -eyesep");
    if (planesSpec && depthSpec)
        pm_error("-planes is not valid with -depth");

    if (planesSpec) {
        float nearPlane, farPlane;
        parseNearFarPlanes(planes, &nearPlane, &farPlane);
        cmdlineP->eyesep = 2.0*farPlane/cmdlineP->dpi;
        cmdlineP->depth = 2.0*(farPlane-nearPlane) / (2.0*farPlane-nearPlane);
    }

    if (argc-1 < 1)
        cmdlineP->inputFilespec = "-";
    else if (argc-1 == 1)
        cmdlineP->inputFilespec = argv[1];
    else
        pm_error("Too many non-option arguments: %d.  Only argument is "
                 "input file name", argc-1);
}



static unsigned int
separation(double             const dist,
           double             const eyesep,
           unsigned int       const dpi,
           double             const dof /* depth of field */
    ) {
/*----------------------------------------------------------------------------
  Return a separation in pixels which corresponds to a 3-D distance
  between the viewer's eyes and a point on an object.
-----------------------------------------------------------------------------*/
    unsigned int const pixelEyesep = ROUNDU(eyesep * dpi);

    return ROUNDU((1.0 - dof * dist) * pixelEyesep / (2.0 - dof * dist));
}



static void
reportImageParameters(const char * const fileDesc,
                      const struct pam * const pamP) {

    pm_message("%s: tuple type '%s', %d wide x %d high x %d deep, maxval %lu",
               fileDesc, pamP->tuple_type, pamP->width, pamP->height,
               pamP->depth, pamP->maxval);
}



/*----------------------------------------------------------------------------
   Background generators
-----------------------------------------------------------------------------*/

struct outGenerator;

typedef tuple coord2Color(struct outGenerator *, int, int);
    /* A type to use for functions that map a 2-D coordinate to a color. */
typedef void outGenStateTerm(struct outGenerator *);

typedef struct {
    struct pam   pam;
    tuple **     imageData;
    tuple        bgColor;
    bool         replaceBgColor;
        /* replace background color with pattern color */
    unsigned int smoothing;
        /* Number of background-smoothing iterations to perform */
} texState;

typedef struct outGenerator {
    struct pam        pam;
    coord2Color *     getTuple;
        /* Map from a height-map (x,y) coordinate to a tuple */
    outGenStateTerm * terminateState;
    void *            stateP;
    texState *        textureP;
        /* Mapped-texture part of the state of operation.  Null
           means we are doing an ordinary stereogram instead of a
           mapped-texture one.
        */
} outGenerator;



struct randomState {
    /* The state of a randomColor generator. */
    unsigned int magnifypat;
    tuple *      currentRow;
    unsigned int prevy;
};


#ifndef LITERAL_FN_DEF_MATCH
static coord2Color randomColor;
#endif

static tuple
randomColor(outGenerator * const outGenP,
            int            const x,
            int            const y) {
/*----------------------------------------------------------------------------
   Return a random RGB value.
-----------------------------------------------------------------------------*/
    struct randomState * const stateP = outGenP->stateP;

    /* Every time we start a new row, we select a new sequence of random
       colors.
    */
    if (y/stateP->magnifypat != stateP->prevy/stateP->magnifypat) {
        unsigned int const modulus = outGenP->pam.maxval + 1;
        int col;

        for (col = 0; col < outGenP->pam.width; ++col) {
            tuple const thisTuple = stateP->currentRow[col];

            unsigned int plane;

            for (plane = 0; plane < outGenP->pam.depth; ++plane) {
                unsigned int const randval = rand();
                thisTuple[plane] = randval % modulus;
            }
        }
    }

    /* Return the appropriate column from the pregenerated color row. */
    stateP->prevy = y;
    return stateP->currentRow[x/stateP->magnifypat];
}



#ifndef LITERAL_FN_DEF_MATCH
static outGenStateTerm termRandomColor;
#endif

static void
termRandomColor(outGenerator * const outGenP) {

    struct randomState * const stateP = outGenP->stateP;

    pnm_freepamrow(stateP->currentRow);
}



static void
initRandomColor(outGenerator *     const outGenP,
                const struct pam * const inPamP,
                struct cmdlineInfo const cmdline) {

    struct randomState * stateP;

    outGenP->pam.format      = PAM_FORMAT;
    outGenP->pam.plainformat = 0;

    switch (cmdline.outputType) {
    case OUTPUT_BW:
        strcpy(outGenP->pam.tuple_type, PAM_PBM_TUPLETYPE);
        outGenP->pam.maxval = 1;
        outGenP->pam.depth = 1;
        break;
    case OUTPUT_GRAYSCALE:
        strcpy(outGenP->pam.tuple_type, PAM_PGM_TUPLETYPE);
        outGenP->pam.maxval =
            cmdline.maxvalSpec ? cmdline.maxval : inPamP->maxval;
        outGenP->pam.depth = 1;
        break;
    case OUTPUT_COLOR:
        strcpy(outGenP->pam.tuple_type, PAM_PPM_TUPLETYPE);
        outGenP->pam.maxval =
            cmdline.maxvalSpec ? cmdline.maxval : inPamP->maxval;
        outGenP->pam.depth = 3;
        break;
    }

    MALLOCVAR_NOFAIL(stateP);

    stateP->currentRow = pnm_allocpamrow(&outGenP->pam);
    stateP->magnifypat = cmdline.magnifypat;
    stateP->prevy      = (unsigned int)(-cmdline.magnifypat);

    outGenP->stateP         = stateP;
    outGenP->getTuple       = &randomColor;
    outGenP->terminateState = &termRandomColor;
}



struct patternPixelState {
    /* This is the state of a patternPixel generator.*/
    struct pam   patPam;     /* Descriptor of pattern image */
    tuple **     patTuples;  /* Entire image read from the pattern file */
    int xshift;
    int yshift;
    unsigned int magnifypat;
};



#ifndef LITERAL_FN_DEF_MATCH
static coord2Color patternPixel;
#endif

static tuple
patternPixel(outGenerator * const outGenP,
             int            const x,
             int            const y) {
/*----------------------------------------------------------------------------
  Return a pixel from the pattern file.
-----------------------------------------------------------------------------*/
    struct patternPixelState * const stateP = outGenP->stateP;
    struct pam * const patPamP = &stateP->patPam;

    int patx, paty;

    paty = ((y - stateP->yshift) / stateP->magnifypat) % patPamP->height;

    if (paty < 0)
        paty += patPamP->height;

    patx = ((x - stateP->xshift) / stateP->magnifypat) % patPamP->width;

    if (patx < 0)
        patx += patPamP->width;

    return stateP->patTuples[paty][patx];
}



#ifndef LITERAL_FN_DEF_MATCH
static outGenStateTerm termPatternPixel;
#endif

static void
termPatternPixel(outGenerator * const outGenP) {

    struct patternPixelState * const stateP = outGenP->stateP;

    pnm_freepamarray(stateP->patTuples, &stateP->patPam);
}



static void
initPatternPixel(outGenerator *     const outGenP,
                 struct cmdlineInfo const cmdline) {
/*----------------------------------------------------------------------------
   Initialize parts of output generator *outGenP that are based on the
   supplied pattern file, assuming there is one.
-----------------------------------------------------------------------------*/
    struct patternPixelState * stateP;
    FILE * patternFileP;

    MALLOCVAR_NOFAIL(stateP);

    assert(cmdline.patfile);

    patternFileP = pm_openr(cmdline.patfile);

    stateP->patTuples =
        pnm_readpam(patternFileP,
                    &stateP->patPam, PAM_STRUCT_SIZE(tuple_type));

    pm_close(patternFileP);

    stateP->xshift     = cmdline.xshift;
    stateP->yshift     = cmdline.yshift;
    stateP->magnifypat = cmdline.magnifypat;

    outGenP->stateP          = stateP;
    outGenP->getTuple        = &patternPixel;
    outGenP->terminateState  = &termPatternPixel;
    outGenP->pam.format      = stateP->patPam.format;
    outGenP->pam.plainformat = stateP->patPam.plainformat;
    outGenP->pam.depth       = stateP->patPam.depth;
    outGenP->pam.maxval      = stateP->patPam.maxval;
    strcpy(outGenP->pam.tuple_type, stateP->patPam.tuple_type);

    if (cmdline.verbose)
        reportImageParameters("Pattern file", &stateP->patPam);
}



static void
readTextureImage(struct cmdlineInfo const cmdline,
                 const struct pam * const inpamP,
                 const struct pam * const outpamP,
                 texState **        const texturePP) {

    FILE *       textureFileP;
    texState *   textureP;
    struct pam * texPamP;

    MALLOCVAR_NOFAIL(textureP);
    texPamP = &textureP->pam;

    textureFileP = pm_openr(cmdline.texfile);
    textureP->imageData =
        pnm_readpam(textureFileP, texPamP, PAM_STRUCT_SIZE(tuple_type));
    pm_close(textureFileP);

    if (cmdline.bgcolor)
        textureP->bgColor =
            pnm_parsecolor(cmdline.bgcolor, texPamP->maxval);
    else
        textureP->bgColor =
            pnm_backgroundtuple(texPamP, textureP->imageData);
    textureP->replaceBgColor = (cmdline.patfile != NULL);
    textureP->smoothing = cmdline.smoothing;

    if (cmdline.verbose) {
        const char * const colorname =
            pnm_colorname(texPamP, textureP->bgColor, 1);

        reportImageParameters("Texture file", texPamP);
        if (cmdline.bgcolor && strcmp(colorname, cmdline.bgcolor))
            pm_message("Texture background color: %s (%s)",
                       cmdline.bgcolor, colorname);
        else
            pm_message("Texture background color: %s", colorname);
        pm_strfree(colorname);
    }

    if (texPamP->width != inpamP->width || texPamP->height != inpamP->height)
        pm_error("The texture image must have the same width and height "
                 "as the input image");
    if (cmdline.patfile &&
        (!streq(texPamP->tuple_type, outpamP->tuple_type) ||
         texPamP->maxval != outpamP->maxval))
        pm_error("The texture image must be of the same tuple type "
                 "and maxval as the pattern image");

    textureP->pam.file = outpamP->file;

    *texturePP = textureP;
}



static unsigned int
totalGuideHeight(struct cmdlineInfo const cmdline) {

    /* Each pair of guides is cmdline.guidesize high, and we add that much
       white above and below as well, so the total vertical space is three
       times cmdline.giudesize.
    */

    return
        (cmdline.guidetop ? 3 * cmdline.guidesize : 0) +
        (cmdline.guidebottom ? 3 * cmdline.guidesize : 0);
}



static void
createoutputGenerator(struct cmdlineInfo const cmdline,
                      const struct pam * const inPamP,
                      outGenerator **    const outputGeneratorPP) {

    outGenerator * outGenP;

    MALLOCVAR_NOFAIL(outGenP);

    outGenP->pam.size   = sizeof(struct pam);
    outGenP->pam.len    = PAM_STRUCT_SIZE(tuple_type);
    outGenP->pam.file   = stdout;
    outGenP->pam.height = inPamP->height + totalGuideHeight(cmdline);
    outGenP->pam.width  = inPamP->width;

    if (cmdline.patfile) {
        /* Background pixels should come from the pattern file. */

        initPatternPixel(outGenP, cmdline);
    } else {
        /* Background pixels should be generated randomly */

        initRandomColor(outGenP, inPamP, cmdline);
    }

    outGenP->pam.bytes_per_sample = pnm_bytespersample(outGenP->pam.maxval);

    if (cmdline.texfile) {
        readTextureImage(cmdline, inPamP, &outGenP->pam, &outGenP->textureP);
        outGenP->pam = outGenP->textureP->pam;
    } else
        outGenP->textureP = NULL;

    *outputGeneratorPP = outGenP;
}



static void
destroyoutputGenerator(outGenerator * const outputGeneratorP) {

    outputGeneratorP->terminateState(outputGeneratorP);
    free(outputGeneratorP);
}


/* End of background generators */

/* ---------------------------------------------------------------------- */


static void
makeWhiteRow(const struct pam * const pamP,
             tuple *            const tuplerow) {

    unsigned int col;

    for (col = 0; col < pamP->width; ++col) {
        unsigned int plane;
        for (plane = 0; plane < pamP->depth; ++plane)
            tuplerow[col][plane] = pamP->maxval;
    }
}



static void
writeRowCopies(const struct pam *  const outPamP,
               const tuple *       const outrow,
               unsigned int        const copyCount) {

    unsigned int i;

    for (i = 0; i < copyCount; ++i)
        pnm_writepamrow(outPamP, outrow);
}



static void
writeWhiteRows(const struct pam * const outPamP,
               unsigned int       const count) {

    tuple * outrow;             /* One row of output data */

    outrow = pnm_allocpamrow(outPamP);

    makeWhiteRow(outPamP, outrow);

    writeRowCopies(outPamP, outrow, count);

    pnm_freerow(outrow);
}



static void
drawguides(unsigned int       const guidesize,
           const struct pam * const outPamP,
           double             const eyesep,
           unsigned int       const dpi,
           double             const depthOfField) {
/*----------------------------------------------------------------------------
   Draw a pair of guide boxes, left and right.
-----------------------------------------------------------------------------*/
    unsigned int const far = separation(0, eyesep, dpi, depthOfField);
        /* Space between the two guide boxes. */
    unsigned int const width = outPamP->width;  /* Width of the output image */

    tuple * outrow;             /* One row of output data */
    tuple blackTuple;
    unsigned int col;

    pnm_createBlackTuple(outPamP, &blackTuple);

    outrow = pnm_allocpamrow(outPamP);

    /* Put some white rows before the guides */
    writeWhiteRows(outPamP, guidesize);

    /* Initialize the row buffer to white */
    makeWhiteRow(outPamP, outrow);

    if (far > width + guidesize)
        pm_message("warning: the guide boxes are completely out of bounds "
                   "at %u DPI", dpi);
    else {
        unsigned int leftBeg, leftEnd, rightBeg, rightEnd;

        assert(far <= width + guidesize);
        leftEnd  = (width - far + guidesize)/2;
        assert(guidesize <= width + far);
        rightBeg = (width + far - guidesize)/2;

        if (far + guidesize > width) {
            pm_message("warning: the guide boxes are partially out of bounds "
                       "at %u DPI", dpi);

            leftBeg  = 0;
            rightEnd = width;
        } else {
            assert(far + guidesize <= width);
            leftBeg  = (width - far - guidesize)/2;
            rightEnd = (width + far + guidesize)/2;
        }

        /* Draw the left guide black in the buffer */
        assert(leftEnd < outPamP->width);
        for (col = leftBeg; col < leftEnd; ++col)
            pnm_assigntuple(outPamP, outrow[col], blackTuple);

        /* Draw the right guide black in the buffer */
        assert(rightEnd <= outPamP->width);
        for (col = rightBeg; col < rightEnd; ++col)
            pnm_assigntuple(outPamP, outrow[col], blackTuple);
    }
    /* Write out the guide rows */

    writeRowCopies(outPamP, outrow, guidesize);

    /* Put some white rows after the guides */
    writeWhiteRows(outPamP, guidesize);

    pnm_freerow(outrow);
}



static void
makeStereoRow(const struct pam * const inPamP,
              tuple *            const inRow,
              unsigned int *     const sameL,
              unsigned int *     const sameR,
              double             const depthOfField,
              double             const eyesep,
              unsigned int       const dpi,
              unsigned int       const optWidth,
              unsigned int       const smoothing) {

/* Given a row of the depth map, compute the sameL and sameR arrays,
 * which indicate for each pixel which pixel to its left and right it
 * should be colored the same as.
 */
#define Z(X) (inRow[X][0]/(double)inPamP->maxval)

    unsigned int col;

    for (col = 0; col < inPamP->width; ++col) {
        sameL[col] = col;
        sameR[col] = col;
    }

    for (col = 0; col < inPamP->width; ++col) {
        unsigned int const sep = separation(Z(col), eyesep, dpi, depthOfField);
        int const left = col - sep/2;
        int const right = left + sep;

        if (left >= 0 && right < inPamP->width) {
            bool isVisible;
        
            if (sameL[right] != right) {
                /* Right point already linked */
                if (sameL[right] < left) {
                    /* Deeper than current */
                    sameR[sameL[right]] = sameL[right];  /* Break old links. */
                    sameL[right] = right;
                    isVisible = TRUE;
                } else
                    isVisible = FALSE;
            } else
                isVisible = TRUE;

            if (sameR[left] != left) {
                /* Left point already linked */
                if (sameR[left] > right) {
                    /* Deeper than current */
                    sameL[sameR[left]] = sameR[left];  /* Break old links. */
                    sameR[left] = left;
                    isVisible = TRUE;
                } else
                    isVisible = FALSE;
            } else
                isVisible = TRUE;

            if (isVisible) {
                /* Make a link. */
                sameL[right] = left;
                sameR[left] = right;
            }
        }
    }

    /* If smoothing is enabled, replace each non-duplicate pixel with
       the pixel adjacent to its right neighbor.
    */
    if (smoothing > 0) {
        int const baseCol = inPamP->width - optWidth - 1;

        int col;

        for (col = inPamP->width - 1; col >= 0; --col)
            sameR[col] = sameR[sameR[col]];
        for (col = baseCol; col >= 0; --col) {
            if (sameR[col] == col)
                sameR[col] = sameR[col+1] - 1;
        }
    }
}



static void
makeMaskRow(const struct pam *   const outPamP,
            unsigned int         const xbegin,
            const unsigned int * const sameL,
            const unsigned int * const sameR,
            const tuple *        const outRow) {
    int col;

    for (col = (int)xbegin; col < outPamP->width; ++col) {
        bool const duplicate = (sameL[col] != col && sameL[col] >= xbegin);

        unsigned int plane;

        for (plane = 0; plane < outPamP->depth; ++plane)
            outRow[col][plane] = duplicate ? outPamP->maxval : 0;
    }

    for (col = (int)xbegin - 1; col >= 0; --col) {
        bool const duplicate = (sameR[col] != col);

        unsigned int plane;

        for (plane = 0; plane < outPamP->depth; ++plane)
            outRow[col][plane] = duplicate ? outPamP->maxval : 0;
    }
}



static void
computeFixedPoint(const unsigned int * const same,
                  unsigned int *       const sameFp,
                  unsigned int         const width) {
/*----------------------------------------------------------------------------
  Compute the fixed point of same[] (i.e., sameFp[x] is
  same[same[same[...[same[x]]...]]]).
-----------------------------------------------------------------------------*/
    int col;

    for (col = width-1; col >= 0; --col) {
        if (same[col] != col)
            sameFp[col] = sameFp[same[col]];
        else {
            if (col < width-1)
                sameFp[col] = sameFp[col + 1] - 1;
            else
                sameFp[col] = col;
        }
    }
}



static void
averageFromPattern(struct pam *         const pamP,
                   tuple                const bgColor,
                   const tuple *        const textureRow,
                   const unsigned int * const same,
                   unsigned int *       const sameFp,
                   const tuple *        const outRow,
                   unsigned int *       const tuplesInCol) {
/*----------------------------------------------------------------------------
  Average the color of each non-background pattern tuple to every column that
  should have the same color.
-----------------------------------------------------------------------------*/
    int col;

    /* Initialize the tuple sums to zero. */

    for (col = 0; col < pamP->width; ++col) {
        unsigned int plane;
        for (plane = 0; plane < pamP->depth; ++plane)
            outRow[col][plane] = 0;
        tuplesInCol[col] = 0;
    }

    /* Accumulate the color of each non-background pattern tuple to
       every column that should have the same color.
    */
    for (col = pamP->width-1; col >= 0; --col) {
        tuple const onetuple = textureRow[(col+same[col])/2];
        unsigned int const targetcol = sameFp[col];
        int eqcol;

        if (!pnm_tupleequal(pamP, onetuple, bgColor)) {
            for (eqcol = pamP->width-1; eqcol >= 0; --eqcol) {
                if (sameFp[eqcol] == targetcol) {
                    unsigned int plane;
                    for (plane = 0; plane < pamP->depth; ++plane)
                        outRow[eqcol][plane] += onetuple[plane];
                    tuplesInCol[eqcol]++;
                }
            }
        }
    }
    /* Take the average of all colors associated with each column.
       Tuples that can be any color are assigned the same color as was
       previously assigned to their fixed-point column.
    */
    for (col = 0; col < pamP->width; ++col) {
        if (tuplesInCol[col] > 0) {
            unsigned int plane;
            for (plane = 0; plane < pamP->depth; ++plane)
                outRow[col][plane] /= tuplesInCol[col];
        } else
            pnm_assigntuple(pamP, outRow[col], bgColor);
    }
}



static void
smoothOutSpeckles(struct pam *   const pamP,
                  tuple          const bgColor,
                  unsigned int   const smoothing,
                  unsigned int * const tuplesInCol,
                  tuple *        const rowBuffer,
                  const tuple *  const outRow) {
/*----------------------------------------------------------------------------
  Smooth out small speckles of the background color lying between other
  colors.
-----------------------------------------------------------------------------*/
    unsigned int i;

    for (i = 0; i < smoothing; ++i) {
        int col;
        tuple * const scratchrow = rowBuffer;
        for (col = pamP->width-2; col >= 1; --col) {
            if (tuplesInCol[col] == 0) {
                /* Replace a background tuple with the average of its
                   left and right neighbors.
                */
                unsigned int plane;
                for (plane = 0; plane < pamP->depth; ++plane)
                    scratchrow[col][plane] = 0;
                if (!pnm_tupleequal(pamP, outRow[col-1], bgColor)) {
                    for (plane = 0; plane < pamP->depth; ++plane)
                        scratchrow[col][plane] += outRow[col-1][plane];
                    ++tuplesInCol[col];
                }
                if (!pnm_tupleequal(pamP, outRow[col+1], bgColor)) {
                    for (plane = 0; plane < pamP->depth; ++plane)
                        scratchrow[col][plane] += outRow[col+1][plane];
                    ++tuplesInCol[col];
                }
                if (tuplesInCol[col] > 0)
                    for (plane = 0; plane < pamP->depth; ++plane)
                        scratchrow[col][plane] /= tuplesInCol[col];
                else
                    pnm_assigntuple(pamP, scratchrow[col], outRow[col]);
            } else
                pnm_assigntuple(pamP, scratchrow[col], outRow[col]);
        }
        for (col = 1; col < pamP->width-1; ++col)
            pnm_assigntuple(pamP, outRow[col], scratchrow[col]);
    }
}



static void
replaceRemainingBackgroundWithPattern(outGenerator *       const outGenP,
                                      const unsigned int * const same,
                                      unsigned int         const row,
                                      const tuple *        const outRow) {

    const struct pam * const pamP = &outGenP->pam;
    tuple const bgColor = outGenP->textureP->bgColor;

    if (outGenP->textureP->replaceBgColor) {
        int col;
        for (col = outGenP->pam.width-1; col >= 0; --col) {
            if (pnm_tupleequal(pamP, outRow[col], bgColor)) {
                bool const duplicate = (same[col] != col);

                tuple newtuple;

                if (duplicate) {
                    assert(same[col] > col);
                    assert(same[col] < outGenP->pam.width);

                    newtuple = outRow[same[col]];
                } else
                    newtuple = outGenP->getTuple(outGenP, col, row);

                pnm_assigntuple(pamP, outRow[col], newtuple);
            }
        }
    }
}



static void
makeImageRowMts(outGenerator *       const outGenP,
                unsigned int         const row,
                const unsigned int * const same,
                unsigned int *       const sameFp,
                tuple *              const rowBuffer,
                const tuple *        const outRow) {
/*----------------------------------------------------------------------------
  Make a row of a mapped-texture stereogram.
-----------------------------------------------------------------------------*/
    unsigned int * tuplesInCol;
        /* tuplesInCol[C] is the number of tuples averaged together to make
           Column C.
        */
    MALLOCARRAY(tuplesInCol, outGenP->pam.width);
    if (tuplesInCol == NULL)
        pm_error("Unable to allocate space for \"tuplesInCol\" array.");

    assert(outGenP->textureP);
    /* This is an original algorithm by Scott Pakin. */

    /*
      Compute the fixed point of same[] (i.e., sameFp[x] is
      same[same[same[...[same[x]]...]]]).
    */
    computeFixedPoint(same, sameFp, outGenP->pam.width);

    /* Average the color of each non-background pattern tuple to
       every column that should have the same color.
    */

    averageFromPattern(&outGenP->pam, outGenP->textureP->bgColor,
                       outGenP->textureP->imageData[row],
                       same, sameFp,
                       outRow, tuplesInCol);

    /* Smooth out small speckles of the background color lying between
       other colors.
    */
    smoothOutSpeckles(&outGenP->pam, outGenP->textureP->bgColor,
                      outGenP->textureP->smoothing,
                      tuplesInCol, rowBuffer, outRow);

    /* Replace any remaining background tuples with a pattern tuple. */

    replaceRemainingBackgroundWithPattern(outGenP, same, row, outRow);

    free(tuplesInCol);
}



static void
makeImageRow(outGenerator *       const outGenP,
             unsigned int         const row,
             unsigned int         const optWidth,
             unsigned int         const xbegin,
             const unsigned int * const sameL,
             const unsigned int * const sameR,
             const tuple *        const outRow) {
/*----------------------------------------------------------------------------
  sameR[N] is one of two things:

  sameR[N] == N means to generate a value for Column N independent of
  other columns in the row.

  sameR[N] > N means Column N should be identical to Column sameR[N].

  sameR[N] < N is not allowed.

  sameL[N] is one of two things:

  sameL[N] == N means to generate a value for Column N independent of
  other columns in the row.

  sameL[N] < N means Column N should be identical to Column sameL[N].

  sameL[N] > N is not allowed.
-----------------------------------------------------------------------------*/
    int col;
    int lastLinked;

    for (col = (int)xbegin, lastLinked = INT_MIN;
         col < outGenP->pam.width;
         ++col) {

        tuple newtuple;

        if (sameL[col] == col || sameL[col] < (int)xbegin) {
            if (lastLinked == col - 1)
                newtuple = outRow[col - 1];
            else
                newtuple = outGenP->getTuple(outGenP, col, row);
        } else {
          newtuple = outRow[sameL[col]];
          lastLinked = col;
              /* Keep track of the last pixel to be constrained. */
        }
        pnm_assigntuple(&outGenP->pam, outRow[col], newtuple);
    }

    for (col = (int)xbegin - 1, lastLinked = INT_MIN; col >= 0; --col) {
        tuple newtuple;

        if (sameR[col] == col) {
            if (lastLinked == col + 1)
                newtuple = outRow[col + 1];
            else
                newtuple = outGenP->getTuple(outGenP, col, row);
        } else {
            newtuple = outRow[sameR[col]];
            lastLinked = col;
                /* Keep track of the last pixel to be constrained. */
        }
        pnm_assigntuple(&outGenP->pam, outRow[col], newtuple);
    }
}



static void
invertHeightRow(const struct pam * const heightPamP,
                tuple *            const tupleRow) {

    int col;

    for (col = 0; col < heightPamP->width; ++col)
        tupleRow[col][0] = heightPamP->maxval - tupleRow[col][0];
}



static void
makeImageRows(const struct pam * const inPamP,
              outGenerator *     const outputGeneratorP,
              double             const depthOfField,
              double             const eyesep,
              unsigned int       const dpi,
              bool               const crossEyed,
              bool               const makeMask,
              unsigned int       const magnifypat,
              unsigned int       const smoothing,
              unsigned int       const xbegin) {

    tuple * inRow;     /* One row of pixels read from the height-map file */
    tuple * outRow;    /* One row of pixels to write to the height-map file */
    unsigned int * sameR;
        /* Malloced array: sameR[N] is the column number of a pixel to the
           right forced to have the same color as the one in column N
        */
    unsigned int * sameL;
        /* Malloced array: sameL[N] is the column number of a pixel to the
           left forced to have the same color as the one in column N
        */
    unsigned int * sameRfp;
        /* Malloced array: Fixed point of sameR[] */
    tuple * rowBuffer;     /* Scratch row needed for texture manipulation */
    unsigned int row;      /* Current row in the input and output files */

    inRow = pnm_allocpamrow(inPamP);
    outRow = pnm_allocpamrow(&outputGeneratorP->pam);
    MALLOCARRAY(sameR, inPamP->width);
    if (sameR == NULL)
        pm_error("Unable to allocate space for \"sameR\" array.");
    MALLOCARRAY(sameL, inPamP->width);
    if (sameL == NULL)
        pm_error("Unable to allocate space for \"sameL\" array.");

    MALLOCARRAY(sameRfp, inPamP->width);
    if (sameRfp == NULL)
        pm_error("Unable to allocate space for \"sameRfp\" array.");
    rowBuffer = pnm_allocpamrow(&outputGeneratorP->pam);

    for (row = 0; row < inPamP->height; ++row) {
        pnm_readpamrow(inPamP, inRow);
        if (crossEyed)
            /* Invert heights for cross-eyed (as opposed to wall-eyed)
               people.
            */
            invertHeightRow(inPamP, inRow);

        /* Determine color constraints. */
        makeStereoRow(inPamP, inRow, sameL, sameR, depthOfField, eyesep, dpi,
                      ROUNDU(eyesep * dpi)/(magnifypat * 2),
                      smoothing);

        if (makeMask)
            makeMaskRow(&outputGeneratorP->pam, xbegin, sameL, sameR, outRow);
        else {
            if (outputGeneratorP->textureP)
                makeImageRowMts(outputGeneratorP, row, sameR, sameRfp,
                                rowBuffer, outRow);
            else
                makeImageRow(outputGeneratorP, row,
                             ROUNDU(eyesep * dpi)/(magnifypat * 2),
                             xbegin, sameL, sameR, outRow);
        }
        /* Write the resulting row. */
        pnm_writepamrow(&outputGeneratorP->pam, outRow);
    }

    pnm_freepamrow(rowBuffer);
    free(sameRfp);
    free(sameL);
    free(sameR);
    pnm_freepamrow(outRow);
    pnm_freepamrow(inRow);
}



static void
produceStereogram(FILE *             const ifP,
                  struct cmdlineInfo const cmdline) {

    struct pam inPam;    /* PAM information for the height-map file */
    outGenerator * outputGeneratorP;
        /* Handle of an object that generates background pixels */
    unsigned int xbegin;
        /* x coordinate separating left-to-right from right-to-left coloring */

    pnm_readpaminit(ifP, &inPam, PAM_STRUCT_SIZE(tuple_type));

    createoutputGenerator(cmdline, &inPam, &outputGeneratorP);

    if (cmdline.verbose) {
        reportImageParameters("Input (height map) file", &inPam);
        if (inPam.depth > 1)
            pm_message("Ignoring all but the first plane of input.");
        reportImageParameters("Output (stereogram) file",
                              &outputGeneratorP->pam);
    }

    pnm_writepaminit(&outputGeneratorP->pam);

    if (cmdline.xbeginSpec == 0)
        xbegin = outputGeneratorP->pam.width/2;
    else {
        xbegin = cmdline.xbegin;
        if (xbegin >= outputGeneratorP->pam.width)
            pm_error("-xbegin must be less than the image width (%d)",
                     outputGeneratorP->pam.width);
    }

    if (cmdline.guidetop)
        drawguides(cmdline.guidesize, &outputGeneratorP->pam,
                   cmdline.eyesep,
                   cmdline.dpi, cmdline.depth);

    makeImageRows(&inPam, outputGeneratorP,
                  cmdline.depth, cmdline.eyesep, cmdline.dpi,
                  cmdline.crosseyed, cmdline.makemask, cmdline.magnifypat,
                  cmdline.smoothing, xbegin);

    if (cmdline.guidebottom)
        drawguides(cmdline.guidesize, &outputGeneratorP->pam,
                   cmdline.eyesep, cmdline.dpi, cmdline.depth);

    if (cmdline.texfile) {
        pnm_freepamarray(outputGeneratorP->textureP->imageData,
                         &outputGeneratorP->textureP->pam);
        free(outputGeneratorP->textureP);
    }
    destroyoutputGenerator(outputGeneratorP);
}



static void
reportParameters(struct cmdlineInfo const cmdline) {

    unsigned int const pixelEyesep =
        ROUNDU(cmdline.eyesep * cmdline.dpi);
    unsigned int const sep0 =
        separation(0, cmdline.eyesep, cmdline.dpi, cmdline.depth);
    unsigned int const sep1 =
        separation(1, cmdline.eyesep, cmdline.dpi, cmdline.depth);

    pm_message("Eye separation: %.4g inch * %d DPI = %u pixels",
               cmdline.eyesep, cmdline.dpi, pixelEyesep);

    if (cmdline.magnifypat > 1)
        pm_message("Background magnification: %uX * %uX",
                   cmdline.magnifypat, cmdline.magnifypat);
    pm_message("\"Optimal\" (far) pattern width: %u / (%u * 2) = %u pixels",
               pixelEyesep, cmdline.magnifypat,
               pixelEyesep/(cmdline.magnifypat * 2));
    pm_message("Near pattern width: %u / %u = %u pixels",
               sep1, cmdline.magnifypat, sep1 / cmdline.magnifypat);
    pm_message("Unique 3-D depth levels possible: %u", sep0 - sep1 + 1);
    if (cmdline.patfile && (cmdline.xshift || cmdline.yshift))
        pm_message("Pattern shift: (%d, %d)", cmdline.xshift, cmdline.yshift);
}



int
main(int argc, const char *argv[]) {

    struct cmdlineInfo cmdline;      /* Parsed command line */
    FILE * ifP;

    pm_proginit(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    if (cmdline.verbose)
        reportParameters(cmdline);

    srand(cmdline.randomseedSpec ? cmdline.randomseed : pm_randseed());

    ifP = pm_openr(cmdline.inputFilespec);

    /* Produce a stereogram. */
    produceStereogram(ifP, cmdline);

    pm_close(ifP);

    return 0;
}



