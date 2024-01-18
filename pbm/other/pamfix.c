/*============================================================================
                                 pamfix
==============================================================================
  Salvage a Netpbm image that is corrupted in certain ways.

  By Bryan Henderson, January 2007.

  Contributed to the public domain by its author.
============================================================================*/

#include <setjmp.h>

#include "pm_c_util.h"
#include "pam.h"
#include "shhopt.h"
#include "mallocvar.h"

struct cmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    const char * inputFileName;   /* File name of input file */
    unsigned int verbose;
    unsigned int truncate;
    unsigned int changemaxval;
    unsigned int clip;
};



static void
parseCommandLine(int argc, char ** const argv,
                 struct cmdlineInfo * const cmdlineP) {
/*----------------------------------------------------------------------------
   Note that the file spec array we return is stored in the storage that
   was passed to us as the argv array.
-----------------------------------------------------------------------------*/
    optEntry * option_def;

    optStruct3 opt;

    unsigned int option_def_index;

    MALLOCARRAY(option_def, 100);

    option_def_index = 0;   /* incremented by OPTENTRY */

    OPTENT3(0, "verbose",      OPT_FLAG, NULL, &cmdlineP->verbose,      0);
    OPTENT3(0, "truncate",     OPT_FLAG, NULL, &cmdlineP->truncate,     0);
    OPTENT3(0, "changemaxval", OPT_FLAG, NULL, &cmdlineP->changemaxval, 0);
    OPTENT3(0, "clip",         OPT_FLAG, NULL, &cmdlineP->clip,         0);

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = FALSE;  /* We don't parms that are negative numbers */

    pm_optParseOptions3(&argc, argv, opt, sizeof(opt), 0);
        /* Uses and sets argc, argv, and some of *cmdlineP and others. */
    free(option_def);

    if (argc-1 == 0) 
        cmdlineP->inputFileName = "-";
    else if (argc-1 != 1)
        pm_error("Program takes zero or one argument (filename).  You "
                 "specified %d", argc-1);
    else
        cmdlineP->inputFileName = argv[1];

    if (cmdlineP->changemaxval && cmdlineP->clip)
        pm_error("You cannot specify both -changemaxval and -clip");
}



static unsigned int readErrRow;
static bool readErrVerbose;

static pm_usererrormsgfn handleRowErrMsg;

static void
handleRowErrMsg(const char * const msg) {
    if (readErrVerbose)
        pm_message("Error reading row %u: %s", readErrRow, msg);
}


static sample
highestSampleInRow(const struct pam * const pamP,
                   tuple *            const tuplerow) {

    unsigned int col;
    sample highestSoFar;

    for (col = 0, highestSoFar = 0; col < pamP->width; ++col) {
        unsigned int plane;
        for (plane = 0; plane < pamP->depth; ++plane)
            highestSoFar = MAX(highestSoFar, tuplerow[col][plane]);
    }
    return highestSoFar;
}



static void
analyzeRaster(const struct pam * const pamP,
              unsigned int *     const goodRowCountP,
              sample *           const highestSampleP,
              bool               const mustAbortOnReadError,
              bool               const verbose) {
/*----------------------------------------------------------------------------
   Go through the raster at which the stream described by *tweakedPamP is
   presently positioned and count how many rows can be successfully read
   (including validating the samples against pamP->maxval) and determine the
   highest sample value in those rows.

   Leave the stream positioned arbitrarily.
-----------------------------------------------------------------------------*/
    tuple * tuplerow;
    unsigned int row;
    jmp_buf jmpbuf;
    int rc;
    
    tuplerow = pnm_allocpamrow(pamP);

    pm_setusererrormsgfn(handleRowErrMsg);

    rc = setjmp(jmpbuf);
    if (rc == 0) {
        pm_setjmpbuf(&jmpbuf);

        readErrVerbose  = mustAbortOnReadError || verbose;
        *goodRowCountP  = 0;  /* initial value */
        *highestSampleP = 0;  /* initial value */

        for (row = 0; row < pamP->height; ++row) {
            readErrRow = row;
            pnm_readpamrow(pamP, tuplerow);
            /* The above does not return if it can't read the next row from
               the file.  Instead, it longjmps out of this loop.

               Update return stats now in case the next iteration longjmps out.
            */
            *highestSampleP =
                MAX(*highestSampleP,
                    highestSampleInRow(pamP, tuplerow));
            ++*goodRowCountP;
        }
    } else {
        /* pnm_readpamrow() encountered an error and longjmped */
        if (mustAbortOnReadError) {
            /* handleRowErrMsg() has issued the error message */
            exit(1);
        }
    }
    pm_setjmpbuf(NULL);

    pm_setusererrormsgfn(NULL);

    pnm_freepamrow(tuplerow);
}



static void
clipPamRow(const struct pam * const pamP,
           tuple *            const tuplerow,
           unsigned int       const row,
           bool               const verbose) {
/*----------------------------------------------------------------------------
   Clip every sample value in tuplerow[] to the maxval.

   If 'verbose' is true, issue messages about every clipping, indicating it
   is in row 'row'.
-----------------------------------------------------------------------------*/
    unsigned int col;

    for (col = 0; col < pamP->width; ++col) {
        unsigned int plane;
        for (plane = 0; plane < pamP->depth; ++plane) {
            if (tuplerow[col][plane] > pamP->maxval) {
                if (verbose) 
                    pm_message("Clipping: Row %u Col %u Plane %u.  "
                               "Sample value %lu exceeds the "
                               "image maxval of %lu",
                               row, col, plane, tuplerow[col][plane],
                               pamP->maxval);
	            tuplerow[col][plane] = pamP->maxval;
            }
        }
    }
}



static void
copyGoodRows(const struct pam * const inpamP,
             const struct pam * const outpamP,
             bool               const verbose) {
/*----------------------------------------------------------------------------
  Copy the raster of the input stream described by *inpamP to the output
  stream described by *outpamP.  Copy only as many rows as *outpamP allows;
  assume *outpamP specifies at most the number of rows of input.
-----------------------------------------------------------------------------*/
    tuple * tuplerow;
    unsigned int row;

    tuplerow = pnm_allocpamrow(inpamP);

    for (row = 0; row < outpamP->height; ++row) {
        pnm_readpamrow(inpamP, tuplerow);
        clipPamRow(outpamP, tuplerow, row, verbose);
        pnm_writepamrow(outpamP, tuplerow);
    }
    
    pnm_freepamrow(tuplerow);
}



int
main(int argc, char * argv[]) {
    struct cmdlineInfo cmdline;
    struct pam inpam;
    struct pam outpam;
    struct pam tweakedPam;
    FILE * ifP;
    pm_filepos rasterPos;
    unsigned int goodRowCount;
    sample highestSample;

    pnm_init(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    ifP = pm_openr_seekable(cmdline.inputFileName);

    pnm_readpaminit(ifP, &inpam, PAM_STRUCT_SIZE(tuple_type));

    pm_tell2(ifP, &rasterPos, sizeof(rasterPos));

    /* Tweak maxval to circumvent out-of-bounds sample value check
       in libpam.  See function validatePamRow() in libpamread.c .

       Ideally we would like to set tweaked-maxval higher for the
       plain (text) formats.  We make a compromise to keep things
       simple.
    */

    tweakedPam = inpam;  /* initial value */

    if ((cmdline.clip || cmdline.changemaxval)
        && PNM_FORMAT_TYPE(inpam.format) != PBM_TYPE)
        tweakedPam.maxval =
            (((sample) 1) << tweakedPam.bytes_per_sample * 8) - 1;

    analyzeRaster(&tweakedPam, &goodRowCount, &highestSample,
                  !cmdline.truncate, cmdline.verbose);

    if (goodRowCount == 0)
        pm_error("Cannot read a single row from the image%s",
                 cmdline.verbose ? "" : ".  Use -verbose to find out why");

    if (goodRowCount < inpam.height)
        pm_message("Copying %u good rows; %u bottom rows missing%s",
                   goodRowCount, inpam.height - goodRowCount,
                   cmdline.verbose ? "" : ".  Use -verbose to find out why");

    pm_seek2(ifP, &rasterPos, sizeof(rasterPos));

    outpam = inpam;  /* initial value */

    outpam.file = stdout;
    outpam.height = goodRowCount;
    if (cmdline.changemaxval && highestSample > outpam.maxval) {
        pm_message("Raising maxval from %lu to %lu to legitimize "
                   "all sample values",
                    outpam.maxval, highestSample);
        outpam.maxval = highestSample;
    }

    pnm_writepaminit(&outpam);

    copyGoodRows(&tweakedPam, &outpam, cmdline.verbose);

    pm_close(inpam.file);
    
    return 0;
}



