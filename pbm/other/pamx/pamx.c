/* By Bryan Henderson 2006.03.25 

   Copyright information is in the file COPYRIGHT
*/

#define _XOPEN_SOURCE 500  /* Make sure strdup() is in string.h */
#define _BSD_SOURCE  /* Make sure strdup() is in <string.h> */
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <pbm/util/pm_c_util.h>
#include <pbm/pam.h>
#include <pbm/util/shhopt.h>
#include <pbm/util/mallocvar.h>
#include <pbm/util/nstring.h>
#include <pbm/util/filename.h>

#include "ximageinfo.h"
#include "image.h"
#include "fill.h"
#include "window.h"


struct geometry {
    bool specified;
    const char * string;
    unsigned int width;
    unsigned int height;
};

struct cmdlineInfo {
    const char * inputFileName;
    const char * displayName;  /* NULL if none */
    const char * display;
    const char * title;
    unsigned int fullscreen;
    unsigned int verbose;
    struct geometry geometry;
    const char * foreground;
    const char * background;
    const char * border;
    unsigned int install;
    unsigned int private;
    unsigned int pixmap;
    unsigned int fit;
    unsigned int visualSpec;
    unsigned int visual;
};



static void 
parseCommandLine(int argc, 
                 char ** argv, 
                 struct cmdlineInfo  * const cmdlineP) {
/* --------------------------------------------------------------------------
   Parse program command line described in Unix standard form by argc
   and argv.  Return the information in the options as *cmdlineP.  

   If command line is internally inconsistent (invalid options, etc.),
   issue error message to stderr and abort program.

   Note that the strings we return are stored in the storage that
   was passed to us as the argv array.  We also trash *argv.
--------------------------------------------------------------------------*/
    optEntry *option_def;
        /* Instructions to pm_optParseOptions3 on how to parse our options. */
    optStruct3 opt;
  
    unsigned int option_def_index;

    unsigned int displaySpec, titleSpec, foregroundSpec, backgroundSpec,
        borderSpec, geometrySpec;

    const char * geometryOpt;
    const char * visualOpt;

    MALLOCARRAY_NOFAIL(option_def, 100);

    option_def_index = 0;   /* incremented by OPTENT3 */
    OPTENT3(0, "fullscreen", OPT_FLAG,
            NULL, &cmdlineP->fullscreen,     0);
    OPTENT3(0, "install",    OPT_FLAG,
            NULL, &cmdlineP->install,     0);
    OPTENT3(0, "private",    OPT_FLAG,
            NULL, &cmdlineP->private,     0);
    OPTENT3(0, "fit",        OPT_FLAG,
            NULL, &cmdlineP->fit,     0);
    OPTENT3(0, "pixmap",     OPT_FLAG,
            NULL, &cmdlineP->pixmap,     0);
    OPTENT3(0, "verbose",    OPT_FLAG,
            NULL, &cmdlineP->verbose,     0);
    OPTENT3(0, "display",    OPT_STRING,
            &cmdlineP->display, &displaySpec, 0);
    OPTENT3(0, "title",      OPT_STRING,
            &cmdlineP->title, &titleSpec,     0);
    OPTENT3(0, "foreground", OPT_STRING,
            &cmdlineP->foreground, &foregroundSpec,     0);
    OPTENT3(0, "background", OPT_STRING,
            &cmdlineP->background, &backgroundSpec,     0);
    OPTENT3(0, "border",     OPT_STRING,
            &cmdlineP->border, &borderSpec,     0);
    OPTENT3(0, "geometry",   OPT_STRING,
            &geometryOpt, &geometrySpec,     0);
    OPTENT3(0, "visual",     OPT_STRING,
            &visualOpt, &cmdlineP->visualSpec,     0);

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = FALSE;   /* We have no parms that are negative numbers */
    
    pm_optParseOptions3(&argc, argv, opt, sizeof(opt), 0);
        /* Uses and sets argc, argv, and some of *cmdlineP and others. */

    if (geometrySpec) {
        int rc;

        cmdlineP->geometry.specified = true;
        cmdlineP->geometry.string    = geometryOpt;

        rc = sscanf(geometryOpt, "%ux%u",
                    &cmdlineP->geometry.width, &cmdlineP->geometry.height);

        if (rc != 2)
            pm_error("Geometry value '%s' does not have the form WxH, "
                     "where W and H are natural numbers", geometryOpt);

        if (cmdlineP->geometry.width == 0)
            pm_error("Width in -geometry option is zero");
        if (cmdlineP->geometry.height == 0)
            pm_error("Height in -geometry option is zero");
    } else
        cmdlineP->geometry.specified = false;

    if (!displaySpec)
        cmdlineP->display = NULL;

    if (!titleSpec)
        cmdlineP->title = NULL;

    if (!foregroundSpec)
        cmdlineP->foreground = NULL;

    if (!backgroundSpec)
        cmdlineP->background = NULL;

    if (!borderSpec)
        cmdlineP->border = NULL;

    if (cmdlineP->visualSpec)
        cmdlineP->visual = visualClassFromName(visualOpt);

    if (argc-1 < 1)
        cmdlineP->inputFileName = "-";
    else if (argc-1 == 1)
        cmdlineP->inputFileName = argv[1];
    else
        pm_error("Program takes at most one argument:  input file name");
}



static int
errorHandler(Display *     const disp,
             XErrorEvent * const error) {
/*----------------------------------------------------------------------------
   This is an X error handler
-----------------------------------------------------------------------------*/
    char errortext[BUFSIZ];

    XGetErrorText(disp, error->error_code, errortext, sizeof(errortext));
    pm_error("X Error: %s on resource 0x%x",
             errortext, (unsigned)error->resourceid);
    return 0;
}



enum usableDepth {DEPTH_1, DEPTH_3};

static void
fillRow(struct pam *     const pamP,
        tuple *          const tuplerow,
        enum usableDepth const depth,
        unsigned char ** const pP) {
/*----------------------------------------------------------------------------
   Add one row to the 24-bit truecolor image data at *pP, and advance
   *pP just past that row.

   Use either the first plane or the first 3 planes of tuplerow[]
   for its contents, according to 'depth'.
-----------------------------------------------------------------------------*/
    unsigned int col;
    
    for (col = 0; col < pamP->width; ++col) {
        /* Truecolor image data has 3 bytes per pixel, one each for
           red, green, and blue.
        */
        unsigned int plane;
        for (plane = 0; plane < 3; ++plane) {
            unsigned int const tuplePlane = depth == DEPTH_3 ? plane : 0;
            *(*pP)++ =
                pnm_scalesample(tuplerow[col][tuplePlane], pamP->maxval, 255);
        }
    }
}



static void
loadPamImage(FILE *   const ifP,
             Image ** const imagePP) {

    struct pam pam;
    Image * imageP;
    unsigned int row;
    tuple * tuplerow;
    unsigned char * p;
    enum usableDepth depth;

    pnm_readpaminit(ifP, &pam, PAM_STRUCT_SIZE(tuple_type));

    if (strncmp(pam.tuple_type, "RGB", 3) == 0) {
        depth = DEPTH_3;
        if (pam.depth < 3)
            pm_error("Invalid depth %u for RGB tuple type.", pam.depth);
    } else
        depth = DEPTH_1;

    imageP = newTrueImage(pam.width, pam.height);

    p = &imageP->data[0];  /* initial value */

    tuplerow = pnm_allocpamrow(&pam);

    for (row = 0; row < pam.height; ++row) {
        pnm_readpamrow(&pam, tuplerow);
        
        /* This semantically wasteful code allows a dumb compiler
           optimizer to recognize that the depth is constant and
           therefore not generate code that checks the depth every
           time it processes a sample.
        */
        switch (depth) {
        case DEPTH_3:
            fillRow(&pam, tuplerow, DEPTH_3, &p);
            break;
        case DEPTH_1:
            fillRow(&pam, tuplerow, DEPTH_1, &p);
            break;
        }
    }
    pnm_freepamrow(tuplerow);

    *imagePP = imageP;
}


#define BACKGROUND_IDX 0
#define FOREGROUND_IDX 1


static void
processImage(Image *            const imageP,
             struct cmdlineInfo const cmdline,
             Display *          const dispP,
             int                const scrn) {
/*----------------------------------------------------------------------------
   Modify image *imageP according to various command line options.
-----------------------------------------------------------------------------*/
    if (imageP->depth <= 1) {
        if (cmdline.background) {
            XColor color;
            XParseColor(dispP, DefaultColormap(dispP, scrn),
                        cmdline.background, &color);
            imageP->rgb.red[BACKGROUND_IDX] = color.red;
            imageP->rgb.grn[BACKGROUND_IDX] = color.green;
            imageP->rgb.blu[BACKGROUND_IDX] = color.blue;
        }
        if (cmdline.foreground) {
            XColor color;
            XParseColor(dispP, DefaultColormap(dispP, scrn),
                        cmdline.foreground, &color);
            imageP->rgb.red[FOREGROUND_IDX] = color.red;
            imageP->rgb.grn[FOREGROUND_IDX] = color.green;
            imageP->rgb.blu[FOREGROUND_IDX] = color.blue;
        }
    }    
}



static void
determineTitle(struct cmdlineInfo const cmdline,
               const char **      const titleP) {
    
    const char * title;
    
    if (cmdline.title)
        title = strdup(cmdline.title);
    else {
        if (streq(cmdline.inputFileName, "-"))
            title = NULL;
        else {
            title = pm_basename(cmdline.inputFileName);
        }
    }
    *titleP = title;
}



int
main(int     argc,
     char ** argv) {

    struct cmdlineInfo cmdline;
    FILE *       ifP;
    Image *      imageP;
    Display *    dispP;           /* display we're sending to */
    int          scrn;           /* screen we're sending to */
    int          retval;
    const char * geometryString;
    const char * title;
    viewer * viewerP;

    pnm_init(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    ifP = pm_openr(cmdline.inputFileName);
    
    dispP = XOpenDisplay(cmdline.display);
    if (!dispP)
        pm_error("Cannot open display '%s'", XDisplayName(cmdline.display));

    scrn = DefaultScreen(dispP);
    XSetErrorHandler(errorHandler);

    geometryString =
        cmdline.geometry.specified ? cmdline.geometry.string : NULL;

    createViewer(&viewerP, dispP, scrn, geometryString, cmdline.fullscreen);

    loadPamImage(ifP, &imageP);

    processImage(imageP, cmdline, dispP, scrn);

    determineTitle(cmdline, &title);

    displayInViewer(viewerP, imageP,
                    cmdline.install, cmdline.private, cmdline.fit,
                    cmdline.pixmap, cmdline.visualSpec, cmdline.visual,
                    title, cmdline.verbose,
                    &retval);

    freeImage(imageP);

    destroyViewer(viewerP);

    if (title)
        pm_strfree(title);

    XCloseDisplay(dispP);

    return retval;
}
