/*----------------------------------------------------------------------------
                              pamcomp
-----------------------------------------------------------------------------
   This program composes two images together, with optional translucence.

   This program is derived from (and replaces) Pnmcomp, whose origin is
   as follows:

       Copyright 1992, David Koblas.                                    
         Permission to use, copy, modify, and distribute this software  
         and its documentation for any purpose and without fee is hereby
         granted, provided that the above copyright notice appear in all
         copies and that both that copyright notice and this permission 
         notice appear in supporting documentation.  This software is   
         provided "as is" without express or implied warranty.          

   No code from the original remains in the present version.  The
   January 2004 version was coded entirely by Bryan Henderson.
   Bryan has contributed his work to the public domain.

   The current version is derived from the January 2004 version, with
   additional work by multiple authors.
-----------------------------------------------------------------------------*/

#define _BSD_SOURCE    /* Make sure strcaseceq() is in nstring.h */
#include <assert.h>
#include <string.h>
#include <math.h>

#include "pm_c_util.h"
#include "mallocvar.h"
#include "nstring.h"
#include "shhopt.h"
#include "pm_gamma.h"
#include "pam.h"

enum horizPos {BEYONDLEFT, LEFT, CENTER, RIGHT, BEYONDRIGHT};
enum vertPos {ABOVE, TOP, MIDDLE, BOTTOM, BELOW};


enum sampleScale {INTENSITY_SAMPLE, GAMMA_SAMPLE};
    /* This indicates a scale for a PAM sample value.  INTENSITY_SAMPLE means
       the value is proportional to light intensity; GAMMA_SAMPLE means the 
       value is gamma-adjusted as defined in the PGM/PPM spec.  In both
       scales, the values are continuous and normalized to the range 0..1.
       
       This scale has no meaning if the PAM is not a visual image.  
    */

enum alphaMix {AM_KEEPUNDER, AM_OVERLAY};
    /* This is a way to combine the alpha channels (transparency/opacity)
       of the underlay and overlay images to form the alpha channel of the
       composed result.

       AM_KEEPUNDER means the alpha for the composed result is identical
       to that of the underlay image.  I.e. the overlay merely modifies the
       color.

       AM_OVERLAY means the result is as if the underlay and overlay images
       are plastic slides and they are taped together to form a composed slide.
       So for one thing, the transparency of the composed image is the product
       of the transparencies of the component images.  But the color is also
       different, because the transparency of the underlaying image affects
       its contribution to the composition.
    */

struct cmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    const char *underlyingFilespec;  /* '-' if stdin */
    const char *overlayFilespec;
    const char *alphaFilespec;
    const char *outputFilespec;  /* '-' if stdout */
    int xoff, yoff;   /* value of xoff, yoff options */
    float opacity;
    unsigned int alphaInvert;
    enum horizPos align;
    enum vertPos valign;
    unsigned int linear;
    unsigned int mixtransparency;
};



static void
parseCommandLine(int                        argc, 
                 const char **              argv,
                 struct cmdlineInfo * const cmdlineP ) {
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

    char *align, *valign;
    unsigned int xoffSpec, yoffSpec, alignSpec, valignSpec, opacitySpec,
        alphaSpec;

    MALLOCARRAY_NOFAIL(option_def, 100);

    option_def_index = 0;   /* incremented by OPTENT3 */
    OPTENT3(0, "invert",             OPT_FLAG,   NULL,                  
            &cmdlineP->alphaInvert,       0);
    OPTENT3(0, "xoff",               OPT_INT,    &cmdlineP->xoff,       
            &xoffSpec,                    0);
    OPTENT3(0, "yoff",               OPT_INT,    &cmdlineP->yoff,       
            &yoffSpec,                    0);
    OPTENT3(0, "opacity",            OPT_FLOAT,  &cmdlineP->opacity,
            &opacitySpec,                 0);
    OPTENT3(0, "alpha",              OPT_STRING, &cmdlineP->alphaFilespec,
            &alphaSpec,                   0);
    OPTENT3(0, "align",              OPT_STRING, &align,
            &alignSpec,                   0);
    OPTENT3(0, "valign",             OPT_STRING, &valign,
            &valignSpec,                  0);
    OPTENT3(0, "linear",             OPT_FLAG,   NULL,       
            &cmdlineP->linear,            0);
    OPTENT3(0, "mixtransparency",    OPT_FLAG,   NULL,       
            &cmdlineP->mixtransparency,   0);

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = FALSE;  /* We have no parms that are negative numbers */

    pm_optParseOptions3(&argc, (char **)argv, opt, sizeof(opt), 0);
        /* Uses and sets argc, argv, and some of *cmdlineP and others. */


    if (!xoffSpec)
        cmdlineP->xoff = 0;
    if (!yoffSpec)
        cmdlineP->yoff = 0;
    if (!alphaSpec)
        cmdlineP->alphaFilespec = NULL;

    if (alignSpec) {
        if (strcaseeq(align, "BEYONDLEFT"))
            cmdlineP->align = BEYONDLEFT;
        else if (strcaseeq(align, "LEFT"))
            cmdlineP->align = LEFT;
        else if (strcaseeq(align, "CENTER"))
            cmdlineP->align = CENTER;
        else if (strcaseeq(align, "RIGHT"))
            cmdlineP->align = RIGHT;
        else if (strcaseeq(align, "BEYONDRIGHT"))
            cmdlineP->align = BEYONDRIGHT;
        else
            pm_error("Invalid value for align option: '%s'.  Only LEFT, "
                     "RIGHT, CENTER, BEYONDLEFT, and BEYONDRIGHT are valid.", 
                     align);
    } else 
        cmdlineP->align = LEFT;

    if (valignSpec) {
        if (strcaseeq(valign, "ABOVE"))
            cmdlineP->valign = ABOVE;
        else if (strcaseeq(valign, "TOP"))
            cmdlineP->valign = TOP;
        else if (strcaseeq(valign, "MIDDLE"))
            cmdlineP->valign = MIDDLE;
        else if (strcaseeq(valign, "BOTTOM"))
            cmdlineP->valign = BOTTOM;
        else if (strcaseeq(valign, "BELOW"))
            cmdlineP->valign = BELOW;
        else
            pm_error("Invalid value for valign option: '%s'.  Only TOP, "
                     "BOTTOM, MIDDLE, ABOVE, and BELOW are valid.", 
                     align);
    } else 
        cmdlineP->valign = TOP;

    if (!opacitySpec) 
        cmdlineP->opacity = 1.0;

    if (argc-1 < 1)
        pm_error("Need at least one argument: file specification of the "
                 "overlay image.");

    cmdlineP->overlayFilespec = argv[1];

    if (argc-1 >= 2)
        cmdlineP->underlyingFilespec = argv[2];
    else
        cmdlineP->underlyingFilespec = "-";

    if (argc-1 >= 3)
        cmdlineP->outputFilespec = argv[3];
    else
        cmdlineP->outputFilespec = "-";

    if (argc-1 > 3)
        pm_error("Too many arguments.  Only acceptable arguments are: "
                 "overlay image, underlying image, output image");
}




static int
commonFormat(int const formatA,
             int const formatB) {
/*----------------------------------------------------------------------------
   Return a viable format for the result of composing the two formats
   'formatA' and 'formatB'.
-----------------------------------------------------------------------------*/
    int retval;

    int const typeA = PAM_FORMAT_TYPE(formatA);
    int const typeB = PAM_FORMAT_TYPE(formatB);
    
    if (typeA == PAM_TYPE || typeB == PAM_TYPE)
        retval = PAM_FORMAT;
    else if (typeA == PPM_TYPE || typeB == PPM_TYPE)
        retval = PPM_FORMAT;
    else if (typeA == PGM_TYPE || typeB == PGM_TYPE)
        retval = PGM_FORMAT;
    else if (typeA == PBM_TYPE || typeB == PBM_TYPE)
        retval = PBM_FORMAT;
    else {
        /* Results are undefined for this case, so we do a hail Mary. */
        retval = formatA;
    }
    return retval;
}



typedef enum { TT_BLACKANDWHITE, TT_GRAYSCALE, TT_RGB } BaseTupletype;



static BaseTupletype
commonTupletype(const char * const tupletypeA, 
                const char * const tupletypeB) {

    if (strneq(tupletypeA, "RGB", 3) ||
        strneq(tupletypeB, "RGB", 3))
        return TT_RGB;
    else if (strneq(tupletypeA, "GRAYSCALE", 9) ||
             strneq(tupletypeB, "GRAYSCALE", 9))
        return TT_GRAYSCALE;
    else if (strneq(tupletypeA, "BLACKANDWHITE", 13) ||
             strneq(tupletypeB, "BLACKANDWHITE", 13))
        return TT_BLACKANDWHITE;
    else
        /* Results are undefined for this case, so we do a hail Mary. */
        return TT_RGB;
}



static void
determineOutputTupleType(BaseTupletype const baseTupletype,
                         bool          const underlayHaveOpacity,
                         char *        const tupleType,
                         size_t        const size) {

    char buffer[80];

    switch (baseTupletype) {
    case TT_BLACKANDWHITE:
        STRSCPY(buffer, "RGB");
        break;
    case TT_GRAYSCALE:
        STRSCPY(buffer, "GRAYSCALE");
        break;
    case TT_RGB:
        STRSCPY(buffer, "RGB");
        break;
    }

    if (underlayHaveOpacity)
        STRSCAT(buffer, "_ALPHA");

    strncpy(tupleType, buffer, size);
}



static void
determineOutputType(const struct pam * const underlayPamP,
                    const struct pam * const overlayPamP,
                    struct pam *       const composedPamP) {

    BaseTupletype const baseTupletype =
        commonTupletype(underlayPamP->tuple_type, overlayPamP->tuple_type);

    composedPamP->height = underlayPamP->height;
    composedPamP->width  = underlayPamP->width;

    composedPamP->format = commonFormat(underlayPamP->format, 
                                        overlayPamP->format);
    composedPamP->plainformat = FALSE;

    composedPamP->maxval = pm_lcm(underlayPamP->maxval, overlayPamP->maxval, 
                                  1, PNM_OVERALLMAXVAL);

    composedPamP->visual = true;
    composedPamP->color_depth = (baseTupletype == TT_RGB ? 3 : 1);
    composedPamP->have_opacity = underlayPamP->have_opacity;
    composedPamP->opacity_plane = (baseTupletype == TT_RGB ? 3 : 1);

    composedPamP->depth =
        (baseTupletype == TT_RGB ? 3 : 1) +
        (underlayPamP->have_opacity ? 1 : 0);

    determineOutputTupleType(baseTupletype, underlayPamP->have_opacity,
                             composedPamP->tuple_type,
                             sizeof(composedPamP->tuple_type));
}



static void
warnOutOfFrame(int const originLeft,
               int const originTop, 
               int const overCols,
               int const overRows,
               int const underCols,
               int const underRows) {

    if (originLeft >= underCols)
        pm_message("WARNING: the overlay is entirely off the right edge "
                   "of the underlying image.  "
                   "It will not be visible in the result.  The horizontal "
                   "overlay position you selected is %d, "
                   "and the underlying image "
                   "is only %d pixels wide.", originLeft, underCols );
    else if (originLeft + overCols <= 0)
        pm_message("WARNING: the overlay is entirely off the left edge "
                   "of the underlying image.  "
                   "It will not be visible in the result.  The horizontal "
                   "overlay position you selected is %d and the overlay is "
                   "only %d pixels wide.", originLeft, overCols);
    else if (originTop >= underRows)
        pm_message("WARNING: the overlay is entirely off the bottom edge "
                   "of the underlying image.  "
                   "It will not be visible in the result.  The vertical "
                   "overlay position you selected is %d, "
                   "and the underlying image "
                   "is only %d pixels high.", originTop, underRows );
    else if (originTop + overRows <= 0)
        pm_message("WARNING: the overlay is entirely off the top edge "
                   "of the underlying image.  "
                   "It will not be visible in the result.  The vertical "
                   "overlay position you selected is %d and the overlay is "
                   "only %d pixels high.", originTop, overRows);
}



static void
validateComputableHeight(int const originTop, 
                         int const overRows) {

    if (originTop < 0) {
        if (originTop < -INT_MAX)
            pm_error("Overlay starts too far above the underlay image to be "
                     "computable.  Overlay can be at most %d rows above "
                     "the underlay.", INT_MAX);
    } else {
        if (INT_MAX - originTop <= overRows)
            pm_error("Too many total rows involved to be computable.  "
                     "You must have a shorter overlay image or compose it "
                     "higher on the underlay image.");
    }
}



static void
computeOverlayPosition(int                const underCols, 
                       int                const underRows,
                       int                const overCols, 
                       int                const overRows,
                       struct cmdlineInfo const cmdline, 
                       int *              const originLeftP,
                       int *              const originTopP) {
/*----------------------------------------------------------------------------
   Determine where to overlay the overlay image, based on the options the
   user specified and the realities of the image dimensions.

   The origin may be outside the underlying image (so e.g. *originLeftP may
   be negative or > image width).  That means not all of the overlay image
   actually gets used.  In fact, there may be no overlap at all.

   But we insist that the span from the topmost row of the two images
   to the bottommost row be less than INT_MAX so that Caller can
   use an integer for a row number in the combination.
-----------------------------------------------------------------------------*/
    int xalign, yalign;

    switch (cmdline.align) {
    case BEYONDLEFT:  xalign = -overCols;              break;
    case LEFT:        xalign = 0;                      break;
    case CENTER:      xalign = (underCols-overCols)/2; break;
    case RIGHT:       xalign = underCols - overCols;   break;
    case BEYONDRIGHT: xalign = underCols;              break;
    }
    switch (cmdline.valign) {
    case ABOVE:       yalign = -overRows;              break;
    case TOP:         yalign = 0;                      break;
    case MIDDLE:      yalign = (underRows-overRows)/2; break;
    case BOTTOM:      yalign = underRows - overRows;   break;
    case BELOW:       yalign = underRows;              break;
    }
    *originLeftP = xalign + cmdline.xoff;
    *originTopP  = yalign + cmdline.yoff;

    validateComputableHeight(*originTopP, overRows);

    warnOutOfFrame(*originLeftP, *originTopP, 
                   overCols, overRows, underCols, underRows);    
}



/*----------------------------------------------------------------------------
   COMPOSING TRANSPARENT PIXELS - AM_OVERLAY

   There are various interpretations of composing transparent pixels, which
   you can see in the definition of enum alphaMix.

   For AM_OVERLAY, which means the result is as if the underlaying and
   overlaying images are plastic slides and we taped them together to make a
   composed plastic slide, the calculations go as follows.

   U means color of underlay pixel
   O means color of overlay pixel
   C means color of composed pixel
   X is a variable, standing for U, O, or C
   X_T means transparency of the X pixel
   X_O means opacity of the X pixel

   Opacity and transparency are fractions in [0,1] and are complements:

     X_T = 1 - X_O

   We consider a further composed image, where in the future someone projects
   another image (the background image) through our composed slide.  The
   opacity and color of our composed image must be such that the light
   emerging (the result image) is the same as if it travelled serially through
   the underlaying and overlaying slide.

   The transparency of each slide is the fraction of light that gets
   through that slide, so the transparency of the composed slide is the
   product of the underlay and overlay transparencies.

       C_T = U_T * O_T

   The composed transparency determines the distribution of background and
   composed image in the result.  We have to choose the composed color such
   that the result of combining it thus with the background image is the same
   as the result of combining the background image with the underlay image
   (distributed according to the underlay transparency), then combining that
   with the overlay image (distributed according to the overlay transparency).

       C = (O_T * U_O * U + O_O * O) / C_O   if C_O != 0

   But this is meaningless if both components are fully transparent, which
   means composed image opacity (C_O) is zero.  In that case, the composed
   color is irrelevant to the result image and we can choose whatever color
   is most likely to be convenient in applications that don't use the
   transparency of the composed image.  We choose the pure underlay color.

       C = U   if C_O = 0

   function composeComponents() computes the above formula.

-----------------------------------------------------------------------------*/



static sample
composeComponents(sample           const compA, 
                  sample           const compB,
                  float            const distrib,
                  float            const bFactor,
                  float            const composedFactor,
                  sample           const maxval,
                  enum sampleScale const sampleScale) {
/*----------------------------------------------------------------------------
  Compose a single color component of each of two pixels, with 'distrib' being
  the fraction of 'compA' in the result, 1-distrib the fraction of 'compB'.

  Note that this function is not useful for an opacity component.

  'sampleScale' tells in what domain the 'distrib' fraction applies:
  brightness or light intensity (gamma-adjusted or not).

  'bFactor' is a factor in [0,1] to apply to 'compB' first.

  'composedFactor' is a factor to apply to the result.

  See above for explanation of why 'bFactor' and 'composedFactor' are
  useful.

  The inputs and result are based on a maxval of 'maxval'.
  
  Note that while 'distrib' in the straightforward case is always in
  [0,1], it can in fact be negative or greater than 1.  We clip the
  result as required to return a legal sample value.
-----------------------------------------------------------------------------*/
    sample retval;

    if (fabs(distrib) > .999 && bFactor > .999 && composedFactor > .999)
        /* Fast path for common case */
        retval = compA;
    else {
        if (sampleScale == INTENSITY_SAMPLE) {
            sample const mix = 
                ROUNDU(compA * distrib + compB * bFactor *(1.0 - distrib));
            retval = MIN(maxval, MAX(0, mix));
        } else {
            float const compANormalized = (float)compA/maxval;
            float const compBNormalized = (float)compB/maxval;
            float const compALinear = pm_ungamma709(compANormalized);
            float const compBLinear = pm_ungamma709(compBNormalized);
            float const compBLinearAdj = compBLinear * bFactor;
            float const mix = 
                compALinear * distrib + compBLinearAdj * (1.0 - distrib)
                * composedFactor;
            sample const sampleValue = ROUNDU(pm_gamma709(mix) * maxval);
            retval = MIN(maxval, MAX(0, sampleValue));
        }
    }
    return retval;
}



static sample
composedOpacity(tuple         const uTuple,
                struct pam *  const uPamP,
                tuple         const oTuple,
                struct pam *  const oPamP,
                struct pam *  const cPamP,
                enum alphaMix const alphaMix) {

    sample retval;

    assert(uPamP->have_opacity);

    switch (alphaMix) {
    case AM_OVERLAY: {
        /* output transparency is product of two input transparencies */
        float const underlayTrans =
            1.0 - ((float)uTuple[uPamP->opacity_plane]/uPamP->maxval);
        float const overlayTrans =
            1.0 - ((float)oTuple[oPamP->opacity_plane]/oPamP->maxval);
        float const composedTrans = underlayTrans * overlayTrans;
        sample const sampleValue =  (1.0 - composedTrans) * cPamP->maxval;
        retval = MIN(cPamP->maxval, MAX(0, sampleValue));
    } break;
    case AM_KEEPUNDER:
        retval = uTuple[uPamP->opacity_plane];
        break;
    }
    return retval;
}



static void
overlayPixel(tuple            const overlayTuple,
             struct pam *     const overlayPamP,
             tuple            const underlayTuple,
             struct pam *     const underlayPamP,
             tuplen           const alphaTuplen,
             bool             const invertAlpha,
             tuple            const composedTuple,
             struct pam *     const composedPamP,
             float            const masterOpacity,
             enum sampleScale const sampleScale,
             enum alphaMix    const alphaMix) {
/*----------------------------------------------------------------------------
   Generate the result of overlaying one pixel with another, taking opacity
   into account, viz overlaying 'underlayTuple' with 'overlayTuple'.
   'overlayPamP' and 'underlayPamP', respectively, describe those tuples.

   We always assume the underlay pixel is opaque.

   We use the following declarations of the opacity of the overlay pixel in
   deciding how much of the underlay pixel should show through.  The product
   of all the indicated opacity factors is the overall opacity factor, where
   an opacity factor is a real number from 0 to 1 and 1 means none of the
   underlay pixel shows through and 0 means the overlay pixel is invisible and
   the underlay pixel shows through in full force.

     if *overlayPamP may indicate that 'overlayTuple' has an opacity component.

     'alphaTuplen' is a normalized tuple whose first sample is the opacity
     factor, except that iff 'invertAlpha' is true, it is a transparency
     factor instead (opacity = 1 - transparency).

     'masterOpacity' is a direct opacity factor

   'sampleScale' tells whether the samples in the tuples are proportional
   to brightness or light intensity (gamma-adjusted or not).  Opacity
   factors apply to brightness (.5 means half the brightness of the result
   comes from the underlay pixel, half comes from the overlay).

   'alphaMix' tells how to determine the opacity of the result pixel.

   Return the result as 'composedTuple', which has the form described by
   'composedPamP'.
-----------------------------------------------------------------------------*/
    float overlayWeight;
    float underlayWeight;
        /* Part of formula for AM_OVERLAY -- see explanation above */
    float composedWeight;
        /* Part of formula for AM_OVERLAY -- see explanation above */

    overlayWeight = masterOpacity;  /* initial value */
    
    if (overlayPamP->have_opacity)
        overlayWeight *= (float)
            overlayTuple[overlayPamP->opacity_plane] / overlayPamP->maxval;
    
    if (alphaTuplen) {
        float const alphaval = 
            invertAlpha ? (1.0 - alphaTuplen[0]) : alphaTuplen[0];
        overlayWeight *= alphaval;
    }

    if (underlayPamP->have_opacity && alphaMix == AM_OVERLAY) {
        struct pam * const uPamP = underlayPamP;
        struct pam * const oPamP = overlayPamP;
        sample const uOpacity = underlayTuple[uPamP->opacity_plane];
        sample const oOpacity = overlayTuple[oPamP->opacity_plane];
        sample const uMaxval = uPamP->maxval;
        sample const oMaxval = oPamP->maxval;
        float  const uOpacityN = uOpacity / uMaxval;
        float  const oOpacityN = oOpacity / oMaxval;
        float  const composedTrans = (1.0 - uOpacityN) * (1.0 * oOpacityN);
        
        if (composedTrans > .999) {
            underlayWeight = 1.0;
            composedWeight = 1.0;
        } else {
            underlayWeight = uOpacityN;
            composedWeight = 1.0 / (1.0 - composedTrans);
        }
    } else {
        underlayWeight = 1.0;
        composedWeight = 1.0;
    }
    {
        unsigned int plane;
        
        for (plane = 0; plane < composedPamP->color_depth; ++plane)
            composedTuple[plane] = 
                composeComponents(overlayTuple[plane], underlayTuple[plane], 
                                  overlayWeight, underlayWeight,
                                  composedWeight,
                                  composedPamP->maxval,
                                  sampleScale);

        if (composedPamP->have_opacity)
            composedTuple[composedPamP->opacity_plane] =
                composedOpacity(underlayTuple, underlayPamP,
                                overlayTuple, overlayPamP,
                                composedPamP, alphaMix);
    }
}



static void
adaptRowFormat(struct pam * const inpamP,
               struct pam * const outpamP,
               tuple *      const tuplerow) {
/*----------------------------------------------------------------------------
   Convert the row in 'tuplerow', which is in a format described by
   *inpamP, to the format described by *outpamP.

   'tuplerow' must have enough allocated depth to do this.
-----------------------------------------------------------------------------*/
    assert(outpamP->visual);
    assert(inpamP->visual);

    pnm_scaletuplerow(inpamP, tuplerow, tuplerow, outpamP->maxval);

    if (outpamP->color_depth == 3) {
        if (outpamP->have_opacity)
            pnm_makerowrgba(inpamP, tuplerow);
        else
            pnm_makerowrgb(inpamP, tuplerow);
    } else {
        if (outpamP->have_opacity)
            pnm_addopacityrow(inpamP, tuplerow);
    }
}



static void
composeRow(int              const originleft, 
           struct pam *     const underlayPamP,
           struct pam *     const overlayPamP,
           bool             const invertAlpha,
           float            const masterOpacity,
           struct pam *     const composedPamP,
           enum sampleScale const sampleScale,
           enum alphaMix    const alphaMix,
           const tuple *    const underlayTuplerow,
           const tuple *    const overlayTuplerow,
           const tuplen *   const alphaTuplerown,
           tuple *          const composedTuplerow) {
/*----------------------------------------------------------------------------
   Create a row of tuples ('composedTupleRow') which is the composition of
   row 'overlayTupleRow' laid over row 'underlayTupleRow', starting at
   column 'originLeft'.

   *underlayPamP and *overlayPamP describe the respective tuple rows.
-----------------------------------------------------------------------------*/
    unsigned int col;

    for (col = 0; col < composedPamP->width; ++col) {
        int const ovlcol = col - originleft;

        if (ovlcol >= 0 && ovlcol < overlayPamP->width) {
            tuplen const alphaTuplen = 
                alphaTuplerown ? alphaTuplerown[ovlcol] : NULL;

            overlayPixel(overlayTuplerow[ovlcol], overlayPamP,
                         underlayTuplerow[col], underlayPamP,
                         alphaTuplen, invertAlpha,
                         composedTuplerow[col], composedPamP,
                         masterOpacity, sampleScale, alphaMix);
        } else
            /* Overlay image does not touch this column. */
            pnm_assigntuple(composedPamP, composedTuplerow[col],
                            underlayTuplerow[col]);
    }
}



static void
determineInputAdaptations(const struct pam * const underlayPamP,
                          const struct pam * const overlayPamP,
                          const struct pam * const composedPamP,
                          struct pam *       const adaptUnderlayPamP,
                          struct pam *       const adaptOverlayPamP) {
/*----------------------------------------------------------------------------
   For easy of computation, this program reads a tuple row from one of the
   input files, then transforms it something similar to the format of the
   eventual output tuple row.  E.g. if the input is grayscale and the
   output color, it converts the depth 1 row read from the file to a depth
   3 row for use in computations.

   This function determines what the result of that transformation should be.
   It's not as simple as it sounds because of opacity.  The overlay may have
   an opacity plane that has to be kept for the computations, while the output
   has no opacity plane.

   Our output PAMs are meaningless except in the fields that pertain to a
   row of tuples.  E.g. the file descriptor and image height members are
   meaningless.
-----------------------------------------------------------------------------*/
    /* We make the underlay row identical to the composed (output) row,
       except for its width.
    */

    *adaptUnderlayPamP = *composedPamP;
    adaptUnderlayPamP->width = underlayPamP->width;

    /* Same for the overlay row, except that it retains is original
       opacity.
    */

    adaptOverlayPamP->width = overlayPamP->width;
    adaptOverlayPamP->tuple_type[0] = '\0';  /* a hack; this doesn't matter */
    adaptOverlayPamP->visual = true;
    adaptOverlayPamP->color_depth = composedPamP->color_depth;
    adaptOverlayPamP->have_opacity = overlayPamP->have_opacity;
    adaptOverlayPamP->opacity_plane = composedPamP->color_depth;
    adaptOverlayPamP->depth =
        composedPamP->color_depth +
        (overlayPamP->have_opacity ? 1 : 0);
    adaptOverlayPamP->maxval = composedPamP->maxval;
    adaptOverlayPamP->bytes_per_sample = composedPamP->bytes_per_sample;
    adaptOverlayPamP->allocation_depth = overlayPamP->allocation_depth;
}



static void
composite(int          const originleft, 
          int          const origintop, 
          struct pam * const underlayPamP,
          struct pam * const overlayPamP,
          struct pam * const alphaPamP,
          bool         const invertAlpha,
          float        const masterOpacity,
          struct pam * const composedPamP,
          bool         const assumeLinear,
          bool         const mixTransparency) {
/*----------------------------------------------------------------------------
   Overlay the overlay image in the array 'overlayImage', described by
   *overlayPamP, onto the underlying image from the input image file
   as described by *underlayPamP, output the composite to the image
   file as described by *composedPamP.

   Apply the overlay image with transparency described by the array
   'alpha' and *alphaPamP.

   The underlying image is positioned after its header.

   'originleft' and 'origintop' are the coordinates in the underlying
   image plane where the top left corner of the overlay image is to
   go.  It is not necessarily inside the underlying image (in fact,
   may be negative).  Only the part of the overlay that actually
   intersects the underlying image, if any, gets into the output.

   We assume that the span from the topmost row of the two images to
   the bottommost row is less than INT_MAX.
-----------------------------------------------------------------------------*/
    enum sampleScale const sampleScale = 
        assumeLinear ? INTENSITY_SAMPLE : GAMMA_SAMPLE;
    enum alphaMix const alphaMix =
        mixTransparency ? AM_OVERLAY : AM_KEEPUNDER;

    int underlayRow;  /* NB may be negative */
    int overlayRow;   /* NB may be negative */
    tuple * composedTuplerow;
    tuple * underlayTuplerow;
    struct pam adaptUnderlayPam;
    tuple * overlayTuplerow;
    struct pam adaptOverlayPam;
    tuplen * alphaTuplerown;

    composedTuplerow = pnm_allocpamrow(composedPamP);
    underlayTuplerow = pnm_allocpamrow(underlayPamP);
    overlayTuplerow  = pnm_allocpamrow(overlayPamP);
    if (alphaPamP)
        alphaTuplerown = pnm_allocpamrown(alphaPamP);
    else
        alphaTuplerown = NULL;

    determineInputAdaptations(underlayPamP, overlayPamP, composedPamP,
                              &adaptUnderlayPam, &adaptOverlayPam);

    pnm_writepaminit(composedPamP);

    assert(INT_MAX - overlayPamP->height > origintop); /* arg constraint */

    for (underlayRow = MIN(0, origintop), overlayRow = MIN(0, -origintop);
         underlayRow < MAX(underlayPamP->height, 
                           origintop + overlayPamP->height);
         ++underlayRow, ++overlayRow) {

        if (overlayRow >= 0 && overlayRow < overlayPamP->height) {
            pnm_readpamrow(overlayPamP, overlayTuplerow);
            adaptRowFormat(overlayPamP, &adaptOverlayPam, overlayTuplerow);
            if (alphaPamP)
                pnm_readpamrown(alphaPamP, alphaTuplerown);
        }
        if (underlayRow >= 0 && underlayRow < underlayPamP->height) {
            pnm_readpamrow(underlayPamP, underlayTuplerow);
            adaptRowFormat(underlayPamP, &adaptUnderlayPam, underlayTuplerow);
            if (underlayRow < origintop || 
                underlayRow >= origintop + overlayPamP->height) {
            
                /* Overlay image does not touch this underlay row. */

                pnm_writepamrow(composedPamP, underlayTuplerow);
            } else {
                composeRow(originleft, &adaptUnderlayPam, &adaptOverlayPam,
                           invertAlpha, masterOpacity, 
                           composedPamP, sampleScale, alphaMix,
                           underlayTuplerow, overlayTuplerow, alphaTuplerown,
                           composedTuplerow);
                
                pnm_writepamrow(composedPamP, composedTuplerow);
            }
        }
    }
    pnm_freepamrow(composedTuplerow);
    pnm_freepamrow(underlayTuplerow);
    pnm_freepamrow(overlayTuplerow);
    if (alphaPamP)
        pnm_freepamrown(alphaTuplerown);
}



static void
initAlphaFile(struct cmdlineInfo const cmdline,
              struct pam *       const overlayPamP,
              FILE **            const filePP,
              struct pam *       const pamP) {

    FILE * fileP;
    
    if (cmdline.alphaFilespec) {
        fileP = pm_openr(cmdline.alphaFilespec);
        pamP->comment_p = NULL;
        pnm_readpaminit(fileP, pamP, PAM_STRUCT_SIZE(opacity_plane));

        if (overlayPamP->width != pamP->width || 
            overlayPamP->height != pamP->height)
            pm_error("Opacity map and overlay image are not the same size");
    } else
        fileP = NULL;

    *filePP = fileP;
}



int
main(int argc, const char *argv[]) {

    struct cmdlineInfo cmdline;
    FILE * underlayFileP;
    FILE * overlayFileP;
    FILE * alphaFileP;
    struct pam underlayPam;
    struct pam overlayPam;
    struct pam alphaPam;
    struct pam composedPam;
    int originLeft, originTop;

    pm_proginit(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    overlayFileP = pm_openr(cmdline.overlayFilespec);

    overlayPam.comment_p = NULL;
    pnm_readpaminit(overlayFileP, &overlayPam, 
                    PAM_STRUCT_SIZE(opacity_plane));

    if (overlayPam.len < PAM_STRUCT_SIZE(opacity_plane))
        pm_error("Libnetpbm is too old.  This program requires libnetpbm from "
                 "Netpbm 10.56 (September 2011) or newer");

    if (!overlayPam.visual)
        pm_error("Overlay image has tuple type '%s', which is not a "
                 "standard visual type.  We don't know how to compose.",
                 overlayPam.tuple_type);

    initAlphaFile(cmdline, &overlayPam, &alphaFileP, &alphaPam);

    underlayFileP = pm_openr(cmdline.underlyingFilespec);

    underlayPam.comment_p = NULL;
    pnm_readpaminit(underlayFileP, &underlayPam, 
                    PAM_STRUCT_SIZE(opacity_plane));

    assert(underlayPam.len >= PAM_STRUCT_SIZE(opacity_plane));

    if (!overlayPam.visual)
        pm_error("Overlay image has tuple type '%s', which is not a "
                 "standard visual type.  We don't know how to compose.",
                 overlayPam.tuple_type);
    
    computeOverlayPosition(underlayPam.width, underlayPam.height, 
                           overlayPam.width,  overlayPam.height,
                           cmdline, &originLeft, &originTop);

    composedPam.size             = PAM_STRUCT_SIZE(opacity_plane);
    composedPam.len              = PAM_STRUCT_SIZE(allocation_depth);
    composedPam.allocation_depth = 0;
    composedPam.file             = pm_openw(cmdline.outputFilespec);
    composedPam.comment_p        = NULL;

    determineOutputType(&underlayPam, &overlayPam, &composedPam);

    pnm_setminallocationdepth(&underlayPam, composedPam.depth);
    pnm_setminallocationdepth(&overlayPam,  composedPam.depth);
    
    composite(originLeft, originTop,
              &underlayPam, &overlayPam, alphaFileP ? &alphaPam : NULL,
              cmdline.alphaInvert, cmdline.opacity,
              &composedPam, cmdline.linear, cmdline.mixtransparency);

    if (alphaFileP)
        pm_close(alphaFileP);
    pm_close(overlayFileP);
    pm_close(underlayFileP);
    pm_close(composedPam.file);

    /* If the program failed, it previously aborted with nonzero completion
       code, via various function calls.
    */
    return 0;
}



