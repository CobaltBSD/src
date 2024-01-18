#include "pm_c_util.h"
#include "mallocvar.h"
#include "nstring.h"
#include "shhopt.h"
#include "pam.h"

struct cmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    const char * inputFileName;  
    unsigned int verbose;
};



static void
parseCommandLine(int argc, char ** const argv,
                 struct cmdlineInfo * const cmdlineP) {
/*----------------------------------------------------------------------------
   Note that the file spec array we return is stored in the storage that
   was passed to us as the argv array.
-----------------------------------------------------------------------------*/
    optEntry *option_def;
        /* Instructions to OptParseOptions2 on how to parse our options.
         */
    optStruct3 opt;

    unsigned int option_def_index;

    MALLOCARRAY_NOFAIL(option_def, 100);

    option_def_index = 0;   /* incremented by OPTENTRY */
    OPTENT3(0, "verbose",    OPT_FLAG,   NULL, &cmdlineP->verbose,        0);

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = FALSE;  /* We have no parms that are negative numbers */

    pm_optParseOptions3(&argc, argv, opt, sizeof(opt), 0);
        /* Uses and sets argc, argv, and some of *cmdlineP and others. */

    if (argc-1 < 1)
        cmdlineP->inputFileName = "-";
    else {
        cmdlineP->inputFileName = argv[1];
        if (argc-1 > 1)
            pm_error("There is at most one argument:  input file name.  "
                     "You specified %d", argc-1);
    }
}        



static void
initOutpam(const struct pam * const inpamP,
           struct pam *       const outpamP) {

    outpamP->file             = stdout;
    outpamP->format           = PAM_FORMAT;
    outpamP->plainformat      = 0;
    outpamP->width            = inpamP->width;
    outpamP->height           = inpamP->height;
    outpamP->depth            = 1;
    outpamP->maxval           = 1;
    outpamP->bytes_per_sample = pnm_bytespersample(outpamP->maxval);
    outpamP->len              = PAM_STRUCT_SIZE(bytes_per_sample);
    outpamP->size             = sizeof(*outpamP);
}



static void
allocateOutputPointerRow(unsigned int const width,
                         tuple **     const tuplerowP) {

    MALLOCARRAY(*tuplerowP, width);

    if (*tuplerowP == NULL)
        pm_error("Could not allocate a %u-column tuple pointer array", width);
}



static void
createWhiteTuple(const struct pam * const pamP, 
                 tuple *            const whiteTupleP) {
/*----------------------------------------------------------------------------
   Create a "white" tuple.  By that we mean a tuple all of whose elements
   are zero.  If it's an RGB, grayscale, or b&w pixel, that means it's black.
-----------------------------------------------------------------------------*/
    tuple whiteTuple;
    unsigned int plane;

    whiteTuple = pnm_allocpamtuple(pamP);

    for (plane = 0; plane < pamP->depth; ++plane)
        whiteTuple[plane] = pamP->maxval;

    *whiteTupleP = whiteTuple;
}



static void
selectBackground(struct pam * const pamP,
                 tuple        const ul,
                 tuple        const ur,
                 tuple        const lr,
                 tuple        const ll,
                 tuple *      const bgColorP) {

    tuple bg;  /* Reference to one of ul, ur, ll, lr */

    if (pnm_tupleequal(pamP, ul, ur) &&
        (pnm_tupleequal(pamP, ul, ll) ||
         pnm_tupleequal(pamP, ul, lr)))
        bg = ul;
    else if (pnm_tupleequal(pamP, ll, lr) &&
             pnm_tupleequal(pamP, lr, ul))
        bg = ll;
    else {
        /* No 3 corners are same color; look for 2 corners */
        if (pnm_tupleequal(pamP, ul, ur))  /* top edge */
            bg = ul;
        else if (pnm_tupleequal(pamP, ul, ll)) /* left edge */
            bg = ul;
        else if (pnm_tupleequal(pamP, ur, lr)) /* right edge */
            bg = ur;
        else if (pnm_tupleequal(pamP, ll, lr)) /* bottom edge */
            bg = ll;
        else {
            /* No two corners are same color; just use upper left corner */
            bg = ul;
        }
    }
    
    *bgColorP = pnm_allocpamtuple(pamP);
    pnm_assigntuple(pamP, *bgColorP, bg);
}



static void
determineBackgroundColor(struct pam * const pamP,
                         bool         const verbose,
                         tuple *      const bgColorP) {
/*----------------------------------------------------------------------------
   Determine what color is the background color of the image in the
   file represented by *pamP.

   Expect the file to be positioned to the start of the raster, and leave
   it positioned arbitrarily.
-----------------------------------------------------------------------------*/
    unsigned int row;
    tuple * tuplerow;
    tuple ul, ur, ll, lr;
        /* Color of upper left, upper right, lower left, lower right */

    tuplerow  = pnm_allocpamrow(pamP);
    ul = pnm_allocpamtuple(pamP);
    ur = pnm_allocpamtuple(pamP);
    ll = pnm_allocpamtuple(pamP);
    lr = pnm_allocpamtuple(pamP);

    pnm_readpamrow(pamP, tuplerow);

    pnm_assigntuple(pamP, ul, tuplerow[0]);
    pnm_assigntuple(pamP, ur, tuplerow[pamP->width-1]);

    for (row = 1; row < pamP->height; ++row)
        pnm_readpamrow(pamP, tuplerow);

    pnm_assigntuple(pamP, ll, tuplerow[0]);
    pnm_assigntuple(pamP, lr, tuplerow[pamP->width-1]);

    selectBackground(pamP, ul, ur, ll, lr, bgColorP);

    if (verbose) {
        int const hexokTrue = 1;
        const char * const colorname =
            pnm_colorname(pamP, *bgColorP, hexokTrue);
        pm_message("Background color is %s", colorname);

        pm_strfree(colorname);
    }

    pnm_freepamtuple(lr);
    pnm_freepamtuple(ll);
    pnm_freepamtuple(ur);
    pnm_freepamtuple(ul);
    pnm_freepamrow(tuplerow);
}


static unsigned char const PT_UNKNOWN = 0;
static unsigned char const PT_BG      = 1;
static unsigned char const PT_FG      = 2;


static unsigned char **
newPi(unsigned int const width,
      unsigned int const height) {

    unsigned char ** pi;
    unsigned int row;

    MALLOCARRAY(pi, height);
    if (pi == NULL)
        pm_error("Out of memory allocating %u row pointers", height);
    for (row = 0; row < height; ++row) {
        MALLOCARRAY(pi[row], width);
        if (pi[row] == NULL)
            pm_error("Out of memory allocating row %u", row);
    }
    return pi;
}



static void
destroyPi(const unsigned char *const * const pi,
          unsigned int                 const height) {

    unsigned int row;

    for (row = 0; row < height; ++row)
        free((void*)pi[row]);

    free((void*)pi);
}



static void
initPi(unsigned char **   const pi,
       const struct pam * const pamP,
       tuple              const backgroundColor) {
/*----------------------------------------------------------------------------
  Set the initial info about every pixel in pi[][].

  Read through the image in the file described by *inpamP and set each
  pixel which is not of background color, and therefore obviously
  foreground, to type PT_FG.  Set every other pixel to PT_UNKNOWN.
-----------------------------------------------------------------------------*/
    tuple * tuplerow;
    unsigned int row;

    tuplerow  = pnm_allocpamrow(pamP);

    for (row = 0; row < pamP->height; ++row) {
        unsigned int col;

        pnm_readpamrow(pamP, tuplerow);

        for (col = 0; col < pamP->width; ++col) {
            pi[row][col] =
                pnm_tupleequal(pamP, tuplerow[col], backgroundColor) ?
                PT_UNKNOWN : PT_FG;
        }
    }
    pnm_freepamrow(tuplerow);
}



static void
setEdges(unsigned char ** const pi,
         unsigned int     const width,
         unsigned int     const height) {
/*----------------------------------------------------------------------------
  Do the four edges.

  Anything of background color in an edge is background.  Pixel type
  PT_UNKNOWN implies background color, so we change all PT_UNKNOWN pixels
  to PT_BG.
-----------------------------------------------------------------------------*/
    unsigned int row, col;

    for (col = 0; col < width; ++col) {
        if (pi[0][col] == PT_UNKNOWN)
            pi[0][col] = PT_BG;

        if (pi[height-1][col] == PT_UNKNOWN)
            pi[height-1][col] = PT_BG;
    }
    for (row = 0; row < height; ++row) {
        if (pi[row][0] == PT_UNKNOWN)
            pi[row][0] = PT_BG;

        if (pi[row][width-1] == PT_UNKNOWN)
            pi[row][width-1] = PT_BG;
    }
}



static void
expandBackgroundHoriz(unsigned char ** const pi,
                      unsigned int     const width,
                      unsigned int     const height,
                      bool *           const expandedP) {
/*----------------------------------------------------------------------------
   In every row, expand the background rightward from any known background
   pixel through all consecutive unknown pixels.

   Then do the same thing leftward.

   Iff we managed to expand the background at all, return *expandedP == TRUE.
-----------------------------------------------------------------------------*/
    unsigned int row;
    bool expanded;

    for (row = 1, expanded = FALSE; row < height-1; ++row) {
        int col;

        for (col = 1; col < width - 1; ++col) {
            if (pi[row][col] == PT_UNKNOWN && pi[row][col-1] == PT_BG) {
                expanded = TRUE;
                /* Set the whole consecutive row of unknown to background */
                for (; pi[row][col] == PT_UNKNOWN && col < width - 1; ++col)
                    pi[row][col] = PT_BG;
            }
        }

        for (col = width-2; col > 0; --col) {
            if (pi[row][col] == PT_UNKNOWN && pi[row][col+1] == PT_BG) {
                expanded = TRUE;
                /* Set the whole consecutive row of unknown to background */
                for (; pi[row][col] == PT_UNKNOWN && col > 0; --col)
                    pi[row][col] = PT_BG;
            }
        }
    }
    *expandedP = expanded;
}



static void
expandBackgroundVert(unsigned char ** const pi,
                     unsigned int     const width,
                     unsigned int     const height,
                     bool *           const expandedP) {
/*----------------------------------------------------------------------------
   In every column, expand the background downward from any known background
   pixel through all consecutive unknown pixels.

   Then do the same thing upward.

   Iff we managed to expand the background at all, return *expandedP == TRUE.
-----------------------------------------------------------------------------*/
    unsigned int col;
    bool expanded;

    for (col = 1, expanded = FALSE; col < width-1; ++col) {
        int row;

        for (row = 1; row < height - 1; ++row) {
            if (pi[row][col] == PT_UNKNOWN && pi[row-1][col] == PT_BG) {
                expanded = TRUE;
                /* Set the whole consecutive col of unknown to background */
                for (; pi[row][col] == PT_UNKNOWN && row < height - 1; ++row)
                    pi[row][col] = PT_BG;
            }
        }

        for (row = height-2; row > 0; --row) {
            if (pi[row][col] == PT_UNKNOWN && pi[row+1][col] == PT_BG) {
                expanded = TRUE;
                /* Set the whole consecutive col of unknown to background */
                for (; pi[row][col] == PT_UNKNOWN && row > 0; --row)
                    pi[row][col] = PT_BG;
            }
        }
    }
    *expandedP = expanded;
}



static void
findBackgroundPixels(struct pam *                   const inpamP,
                     tuple                          const backgroundColor,
                     bool                           const verbose,
                     const unsigned char * const ** const piP) {
/*----------------------------------------------------------------------------
   Figure out which pixels of the image are background.  Read the
   image from the input file described by *inpamP (positioned now to
   the start of the raster) and generate the matrix *piP telling which
   pixels are background and which are foreground, given that the
   background color is 'backgroundColor'.

   Note that it isn't as simple as finding which pixels are of color
   'backgroundColor'.  They have to be part of a contiguous region that
   touches one of the 4 edges of the image.

   In the matrix we return, there is one element for each pixel in the
   image, and it has value PT_BG or PT_FG.
-----------------------------------------------------------------------------*/
    unsigned char ** pi;
    bool backgroundComplete;
    unsigned int passes;

    pi = newPi(inpamP->width, inpamP->height);

    initPi(pi, inpamP, backgroundColor);

    setEdges(pi, inpamP->width, inpamP->height);

    backgroundComplete = FALSE;
    passes = 0;
    
    while (!backgroundComplete) {
        bool expandedHoriz, expandedVert;

        expandBackgroundHoriz(pi, inpamP->width, inpamP->height,
                              &expandedHoriz);
    
        expandBackgroundVert(pi, inpamP->width, inpamP->height,
                             &expandedVert);

        backgroundComplete = !expandedHoriz && !expandedVert;

        ++passes;
    }

    if (verbose)
        pm_message("Background found in %u passes", passes);

    *piP = (const unsigned char * const *)pi;
}

                     

static void
writeOutput(const struct pam *            const inpamP,
            const unsigned char * const * const pi) {

    tuple black, white;
    tuple * outputTuplerow;
        /* This is not a normal tuplerow; it is just pointers to either
           'black' or 'white'
        */
    unsigned int row;
    struct pam outpam;

    initOutpam(inpamP, &outpam);

    allocateOutputPointerRow(outpam.width, &outputTuplerow);
    pnm_createBlackTuple(&outpam, &black);
    createWhiteTuple(&outpam, &white);

    pnm_writepaminit(&outpam);

    for (row = 0; row < outpam.height; ++row) {
        unsigned int col;
        for (col = 0; col < outpam.width; ++col)
            outputTuplerow[col] = pi[row][col] == PT_BG ? white : black;

        pnm_writepamrow(&outpam, outputTuplerow);
    }
    pnm_freepamtuple(white);
    pnm_freepamtuple(black);
    free(outputTuplerow);
}



int
main(int argc, char *argv[]) {

    struct cmdlineInfo cmdline;
    struct pam inpam;
    FILE * ifP;
    pm_filepos rasterpos;
    tuple backgroundColor;
    const unsigned char * const * pi;
    
    pnm_init(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    ifP = pm_openr_seekable(cmdline.inputFileName);

    pnm_readpaminit(ifP, &inpam, PAM_STRUCT_SIZE(tuple_type));

    pm_tell2(ifP, &rasterpos, sizeof(rasterpos));

    determineBackgroundColor(&inpam, cmdline.verbose, &backgroundColor);

    pm_seek2(ifP, &rasterpos, sizeof(rasterpos));

    findBackgroundPixels(&inpam, backgroundColor, cmdline.verbose, &pi);

    writeOutput(&inpam, pi);

    destroyPi(pi, inpam.height);

    pm_close(ifP);

    pnm_freepamtuple(backgroundColor);
    
    return 0;
}
