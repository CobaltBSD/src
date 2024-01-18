/* This is ppmntsc.c, a program to adjust saturation values in an image
   so they are legal for NTSC or PAL.

   It is derived from the program rlelegal.c, dated June 5, 1995,
   which is described below and propagates that program's copyright.
   The derivation was done by Bryan Henderson on 2000.04.21 to convert
   it from operating on the RLE format to operating on the PPM format
   and to rewrite it in a cleaner style, taking advantage of modern C
   compiler technology.  
*/


/*
 * This software is copyrighted as noted below.  It may be freely copied,
 * modified, and redistributed, provided that the copyright notice is 
 * preserved on all copies.
 * 
 * There is no warranty or other guarantee of fitness for this software,
 * it is provided solely "as is".  Bug reports or fixes may be sent
 * to the author, who may or may not act on them as he desires.
 *
 * You may not include this software in a program or other software product
 * without supplying the source, or without informing the end-user that the 
 * source is available for no extra charge.
 *
 * If you modify this software, you should include a notice giving the
 * name of the person performing the modification, the date of modification,
 * and the reason for such modification.
 */

/* 
 * rlelegal.c - Make RGB colors legal in the YIQ or YUV color systems.
 * 
 * Author:	Wes Barris
 * 		Minnesota Supercomputer Center, Inc.
 * Date:	Fri Oct 15, 1993
 * @Copyright, Research Equipment Inc., d/b/a Minnesota Supercomputer
 * Center, Inc., 1993

 */

#define _BSD_SOURCE 1      /* Make sure strdup() is in string.h */
#define _XOPEN_SOURCE 500  /* Make sure strdup() is in string.h */

#include <stdio.h>
#include <math.h>
#include <string.h>

#include "pm_c_util.h"
#include "ppm.h"
#include "mallocvar.h"
#include "shhopt.h"

enum legalize {RAISE_SAT, LOWER_SAT, ALREADY_LEGAL};
   /* The actions that make a legal pixel */

struct cmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    const char * inputFilename;
    unsigned int verbose;
    unsigned int debug;
    unsigned int pal;
    enum {ALL, LEGAL_ONLY, ILLEGAL_ONLY, CORRECTED_ONLY} output;
};



static void
parseCommandLine(int argc, const char ** argv,
                 struct cmdlineInfo * const cmdlineP) {
/*----------------------------------------------------------------------------
   Note that many of the strings that this function returns in the
   *cmdlineP structure are actually in the supplied argv array.  And
   sometimes, one of these strings is actually just a suffix of an entry
   in argv!
-----------------------------------------------------------------------------*/
    optStruct3 opt;
    optEntry *option_def;
        /* Instructions to OptParseOptions on how to parse our options.
         */
    unsigned int option_def_index;
    unsigned int legalonly, illegalonly, correctedonly;

    MALLOCARRAY(option_def, 100);

    option_def_index = 0;   /* incremented by OPTENTRY */
    OPTENT3('v', "verbose",        OPT_FLAG, NULL,  &cmdlineP->verbose,  0);
    OPTENT3('V', "debug",          OPT_FLAG, NULL,  &cmdlineP->debug,    0);
    OPTENT3('p', "pal",            OPT_FLAG, NULL,  &cmdlineP->pal,      0);
    OPTENT3('l', "legalonly",      OPT_FLAG, NULL,  &legalonly,           0);
    OPTENT3('i', "illegalonly",    OPT_FLAG, NULL,  &illegalonly,         0);
    OPTENT3('c', "correctedonly",  OPT_FLAG, NULL,  &correctedonly,       0);

    opt.opt_table = option_def;
    opt.short_allowed = true;
    opt.allowNegNum = false;

    pm_optParseOptions3(&argc, (char **)argv, opt, sizeof(opt), 0);

    if (argc - 1 == 0)
        cmdlineP->inputFilename = "-";  /* he wants stdin */
    else if (argc - 1 == 1)
        cmdlineP->inputFilename = argv[1];
    else 
        pm_error("Too many arguments.  The only arguments accepted "
                 "are the mask color and optional input file specification");

    if (legalonly + illegalonly + correctedonly > 1)
        pm_error("--legalonly, --illegalonly, and --correctedonly are "
                 "conflicting options.  Specify at most one of these.");
        
    if (legalonly) 
        cmdlineP->output = LEGAL_ONLY;
    else if (illegalonly) 
        cmdlineP->output = ILLEGAL_ONLY;
    else if (correctedonly) 
        cmdlineP->output = CORRECTED_ONLY;
    else 
        cmdlineP->output = ALL;
}



static void 
rgbtoyiq(const int r, const int g, const int b, 
         double * const y_p, 
         double * const i_p, 
         double * const q_p) {
    
    *y_p = .299*(r/255.0) + .587*(g/255.0) + .114*(b/255.0);
    *i_p = .596*(r/255.0) - .274*(g/255.0) - .322*(b/255.0);
    *q_p = .211*(r/255.0) - .523*(g/255.0) + .312*(b/255.0);
}



static void 
yiqtorgb(const double y, const double i, const double q, 
         int * const r_p, int * const g_p, int * const b_p) {
    *r_p = 255.0*(1.00*y + .9562*i + .6214*q);
    *g_p = 255.0*(1.00*y - .2727*i - .6468*q);
    *b_p = 255.0*(1.00*y -1.1037*i +1.7006*q);
}



static void 
rgbtoyuv(const int r, const int g, const int b, 
         double * const y_p, 
         double * const u_p, 
         double * const v_p) {
    *y_p =  .299*(r/255.0) + .587*(g/255.0) + .114*(b/255.0);
    *u_p = -.147*(r/255.0) - .289*(g/255.0) + .437*(b/255.0);
    *v_p =  .615*(r/255.0) - .515*(g/255.0) - .100*(b/255.0);
}



static void 
yuvtorgb(const double y, const double u, const double v, 
         int * const r_p, int * const g_p, int * const b_p) {
    
    *r_p = 255.0*(1.00*y + .0000*u +1.1398*v);
    *g_p = 255.0*(1.00*y - .3938*u - .5805*v);
    *b_p = 255.0*(1.00*y +2.0279*u + .0000*v);
}



static void
makeLegalYiq(double          const y,
             double          const i,
             double          const q, 
             double *        const yNewP, 
             double *        const iNewP, 
             double *        const qNewP,
             enum legalize * const actionP) {
    
    double satOld, satNew;
    /*
     * I and Q are legs of a right triangle.  Saturation is the hypotenuse.
     */
    satOld = sqrt(SQR(i) + SQR(q));
    if (y+satOld > 1.0) {
        const double diff = 0.5*((y + satOld) - 1.0);
        *yNewP = y - diff;
        satNew = 1.0 - *yNewP;
        *iNewP = i * (satNew/satOld);
        *qNewP = q * (satNew/satOld);
        *actionP = LOWER_SAT;
    } else if (y - satOld <= -0.251) {
        const double diff = 0.5*((satOld - y) - 0.251);
        *yNewP = y + diff;
        satNew = 0.250 + *yNewP;
        *iNewP = i * (satNew/satOld);
        *qNewP = q * (satNew/satOld);
        *actionP = RAISE_SAT;
    } else {
        *yNewP = y;
        *iNewP = i;
        *qNewP = q;
        *actionP = ALREADY_LEGAL;
    }
}



static void
make_legal_yuv(const double y, const double u, const double v, 
               double * const y_new_p, 
               double * const u_new_p, 
               double * const v_new_p,
               enum legalize * const action_p
    ) {
    
    double sat_old, sat_new;
    /*
     * U and V are legs of a right triangle.  Saturation is the hypotenuse.
     */
    sat_old = sqrt(u*u + v*v);
    if (y+sat_old >= 1.334) {
        const double diff = 0.5*((y+sat_old) - 1.334);
        *y_new_p = y - diff;
        sat_new = 1.333 - *y_new_p;
        *u_new_p = u*(sat_new/sat_old);
        *v_new_p = v*(sat_new/sat_old);
        *action_p = LOWER_SAT;
    } else if (y-sat_old <= -0.339) {
        const double diff = 0.5*((sat_old-y) - 0.339);
        *y_new_p = y + diff;
        sat_new = 0.338 + *y_new_p;
        *u_new_p = u*(sat_new/sat_old);
        *v_new_p = v*(sat_new/sat_old);
        *action_p = RAISE_SAT;
    } else {
        *u_new_p = u;
        *v_new_p = v;
        *action_p = ALREADY_LEGAL;
    }
    return;
}



static void
make_legal_yiq_i(const int r_in, const int g_in, const int b_in, 
                 int * const r_out_p, 
                 int * const g_out_p, 
                 int * const b_out_p,
                 enum legalize * const action_p
    ) {
    
    double y, i, q;
    double y_new, i_new, q_new;
    /*
     * Convert to YIQ and compute the new saturation.
     */
    rgbtoyiq(r_in, g_in, b_in, &y, &i, &q);
    makeLegalYiq(y, i, q, &y_new, &i_new, &q_new, action_p);
    if (*action_p != ALREADY_LEGAL)
        /*
         * Given the new I and Q, compute new RGB values.
        */
        yiqtorgb(y_new, i_new, q_new, r_out_p, g_out_p, b_out_p);
    else {
        *r_out_p = r_in;
        *g_out_p = g_in;
        *b_out_p = b_in;
      }
    return;
}



static void
make_legal_yuv_i(const int r_in, const int g_in, const int b_in, 
                 int * const r_out_p, 
                 int * const g_out_p, 
                 int * const b_out_p,
                 enum legalize * const action_p
    ){
    
    double y, u, v;
    double y_new, u_new, v_new;  
    /*
     * Convert to YUV and compute the new saturation.
     */
    rgbtoyuv(r_in, g_in, b_in, &y, &u, &v);
    make_legal_yuv(y, u, v, &y_new, &u_new, &v_new, action_p);
    if (*action_p != ALREADY_LEGAL)
        /*
         * Given the new U and V, compute new RGB values.
         */
        yuvtorgb(y_new, u_new, v_new, r_out_p, g_out_p, b_out_p);
    else {
        *r_out_p = r_in;
        *g_out_p = g_in;
        *b_out_p = b_in;
    }
    return;
}



static void 
make_legal_yiq_b(const pixel input,
                 pixel * const output_p,
                 enum legalize * const action_p) {


    int ir_in, ig_in, ib_in;
    int ir_out, ig_out, ib_out;
    
    ir_in = (int)PPM_GETR(input);
    ig_in = (int)PPM_GETG(input);
    ib_in = (int)PPM_GETB(input);

    make_legal_yiq_i(ir_in, ig_in, ib_in, &ir_out, &ig_out, &ib_out, action_p);

    PPM_ASSIGN(*output_p, ir_out, ig_out, ib_out);

    return;
}



static void 
make_legal_yuv_b(const pixel input,
                 pixel * const output_p,
                 enum legalize * const action_p) {

    int ir_in, ig_in, ib_in;
    int ir_out, ig_out, ib_out;
    
    ir_in = (int)PPM_GETR(input);
    ig_in = (int)PPM_GETG(input);
    ib_in = (int)PPM_GETB(input);
    make_legal_yuv_i(ir_in, ig_in, ib_in, &ir_out, &ig_out, &ib_out, action_p);

    PPM_ASSIGN(*output_p, ir_out, ig_out, ib_out);

    return;
}



static void 
reportMapping(pixel const oldPixel,
              pixel const newPixel) {
/*----------------------------------------------------------------------------
  Assuming oldPixel and newPixel are input and output pixels,
  tell the user that we changed a pixel to make it legal, if in fact we
  did and it isn't the same change that we just reported.
-----------------------------------------------------------------------------*/
    static pixel lastChangedPixel;
    static bool firstTime = true;

    if (!PPM_EQUAL(oldPixel, newPixel) && 
        (firstTime || PPM_EQUAL(oldPixel, lastChangedPixel))) {
        pm_message("Mapping %u %u %u -> %u %u %u\n",
                   PPM_GETR(oldPixel),
                   PPM_GETG(oldPixel),
                   PPM_GETB(oldPixel),
                   PPM_GETR(newPixel),
                   PPM_GETG(newPixel),
                   PPM_GETB(newPixel)
            );

        lastChangedPixel = oldPixel;
        firstTime = false;
    }    
}



static void
convertOneImage(FILE *             const ifP,
                struct cmdlineInfo const cmdline, 
                unsigned int *     const hiCountP,
                unsigned int *     const loCountP) {

    /* Parameters of input image: */
    int rows, cols;
    pixval maxval;
    int format;

    ppm_readppminit(ifP, &cols, &rows, &maxval, &format);
    ppm_writeppminit(stdout, cols, rows, maxval, 0);
    {
        pixel * const inputRow = ppm_allocrow(cols);
        pixel * const outputRow = ppm_allocrow(cols);

        pixel lastIllegalPixel;
            /* Value of the illegal pixel we most recently processed */
        pixel black;
            /* A constant - black pixel */

        PPM_ASSIGN(black, 0, 0, 0);

        PPM_ASSIGN(lastIllegalPixel, 0, 0, 0);  /* initial value */
        {
            unsigned int row;

            *hiCountP = 0; *loCountP = 0;  /* initial values */

            for (row = 0; row < rows; ++row) {
                unsigned int col;
                ppm_readppmrow(ifP, inputRow, cols, maxval, format);
                for (col = 0; col < cols; ++col) {
                    pixel corrected;
                        /* Corrected or would-be corrected value for pixel */
                    enum legalize action;
                        /* What action was used to make pixel legal */
                    if (cmdline.pal)
                        make_legal_yuv_b(inputRow[col],
                                         &corrected,
                                         &action);
                    else
                        make_legal_yiq_b(inputRow[col],
                                         &corrected,
                                         &action);
                        
                    if (action == LOWER_SAT) 
                        ++*hiCountP;
                    if (action == RAISE_SAT)
                        ++*loCountP;
                    if (cmdline.debug)
                        reportMapping(inputRow[col], corrected);
                    switch (cmdline.output) {
                    case ALL:
                        outputRow[col] = corrected;
                        break;
                    case LEGAL_ONLY:
                        outputRow[col] = (action == ALREADY_LEGAL) ?
                            inputRow[col] : black;
                        break;
                    case ILLEGAL_ONLY:
                        outputRow[col] = (action != ALREADY_LEGAL) ?
                            inputRow[col] : black;
                        break;
                    case CORRECTED_ONLY:
                        outputRow[col] = (action != ALREADY_LEGAL) ?
                            corrected : black;
                        break;
                    }
                }
                ppm_writeppmrow(stdout, outputRow, cols, maxval, 0);
            }
        }
        ppm_freerow(outputRow);
        ppm_freerow(inputRow);
    }
}



int
main(int argc, const char **argv) {
    
    struct cmdlineInfo cmdline;
    FILE * ifP;
    unsigned int totalHiCount, totalLoCount;
    unsigned int imageCount;

    int eof;

    pm_proginit(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    ifP = pm_openr(cmdline.inputFilename);
    
    imageCount = 0;    /* initial value */
    totalHiCount = 0;  /* initial value */
    totalLoCount = 0;  /* initial value */

    eof = false;
    while (!eof) {
        unsigned int hiCount, loCount;

        convertOneImage(ifP, cmdline, &hiCount, &loCount);

        ++imageCount;
        totalHiCount += hiCount;
        totalLoCount += loCount;

        ppm_nextimage(ifP, &eof);
    }


	if (cmdline.verbose) {
        pm_message("%u images processed.", imageCount);
        pm_message("%u pixels were above the saturation limit.", 
                   totalHiCount);
        pm_message("%u pixels were below the saturation limit.", 
                   totalLoCount);
    }
    
    pm_close(ifP);

    return 0;
}
