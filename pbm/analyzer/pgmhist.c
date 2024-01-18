/* pgmhist.c - print a histogram of the values in a PGM image
**
** Copyright (C) 1989 by Jef Poskanzer.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
*/

#include <assert.h>
#include <limits.h>

#include "pm_c_util.h"
#include "mallocvar.h"
#include "shhopt.h"
#include "pgm.h"



struct CmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    const char * inputFileName;  /* Filename of input files */
    unsigned int machine;
    unsigned int median;
    unsigned int quartile;
    unsigned int decile;
    unsigned int forensic;
};



static void
parseCommandLine(int argc, const char ** argv,
                 struct CmdlineInfo * const cmdlineP) {
/*----------------------------------------------------------------------------
   Note that the file spec array we return is stored in the storage that
   was passed to us as the argv array.
-----------------------------------------------------------------------------*/
    optStruct3 opt;  /* set by OPTENT3 */
    optEntry * option_def;
    unsigned int option_def_index;

    MALLOCARRAY_NOFAIL(option_def, 100);

    option_def_index = 0;   /* incremented by OPTENT3 */

    OPTENT3(0,   "machine",       OPT_FLAG,  NULL,
            &cmdlineP->machine,             0);
    OPTENT3(0,   "median",        OPT_FLAG,  NULL,
            &cmdlineP->median,              0);
    OPTENT3(0,   "quartile",      OPT_FLAG,  NULL,
            &cmdlineP->quartile,            0);
    OPTENT3(0,   "decile",        OPT_FLAG,  NULL,
            &cmdlineP->decile,              0);
    OPTENT3(0,   "forensic",      OPT_FLAG,  NULL,
            &cmdlineP->forensic,            0);

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = FALSE;  /* We have no parms that are negative numbers */

    pm_optParseOptions3(&argc, (char **)argv, opt, sizeof(opt), 0);
        /* Uses and sets argc, argv, and some of *cmdlineP and others. */

    if (cmdlineP->median + cmdlineP->quartile + cmdlineP->decile > 1)
        pm_error("You may specify only one of -median, -quartile, "
                 "and -decile");

    if (argc-1 == 0)
        cmdlineP->inputFileName = "-";
    else if (argc-1 != 1)
        pm_error("Program takes zero or one argument (filename).  You "
                 "specified %d", argc-1);
    else
        cmdlineP->inputFileName = argv[1];

    free(option_def);
}



static gray
universalMaxval(gray const maxval,
                int  const format) {
/*----------------------------------------------------------------------------
  A maxval that makes it impossible for a pixel to be invalid in an image that
  states it maxval as 'maxval' and has format 'format'.

  E.g. in a one-byte-per-sample image, it's not possible to read a sample
  value greater than 255, so a maxval of 255 makes it impossible for a sample
  to be invalid.

  But: we never go above 65535, which means our maxval isn't entirely
  universal.  If the image is plain PGM, it could contain a pixel that
  exceeds even that.
-----------------------------------------------------------------------------*/
    assert(0 < maxval && maxval < 65536);

    if (format == RPGM_FORMAT) {
        /*  Raw PGM stream has either one or two bytes per pixel, depending
            upon its stated maxval.
        */
        if (maxval > 255)
            return 65535;
        else
            return 255;
    } else if (format == RPBM_FORMAT) {
        /* A Raw PBM stream has one bit per pixel, which libnetpbm renders
           as 0 or 255 when we read it.
        */
        assert(maxval == 255);
        return 255;
    } else {
        /* A plain PGM or PBM stream has essentially unlimited range in the
           tokens that are supposed to be sample values.  We arbitrarily draw
           the line at 65535.
        */
        return 65535;
    }
}



static void
buildHistogram(FILE *               const ifP,
               int                  const format,
               unsigned int         const cols,
               unsigned int         const rows,
               gray                 const mmaxval,
               unsigned long int ** const histP) {
/*----------------------------------------------------------------------------
   Compute the histogram of sample values in the input stream *ifP as *histP,
   in newly malloced storage.

   Assume the image maxval is 'mmaxval'.  Assume *ifP is positioned to the
   start of the raster.
-----------------------------------------------------------------------------*/
    gray * grayrow;
    unsigned int row;
    unsigned int i;
    unsigned long int * hist;  /* malloc'ed array */

    grayrow = pgm_allocrow(cols);

    MALLOCARRAY(hist, mmaxval + 1);
    if (hist == NULL)
        pm_error("out of memory");

    for (i = 0; i <= mmaxval; ++i)
        hist[i] = 0;

    for (row = 0; row < rows; ++row) {
        unsigned int col;

        pgm_readpgmrow(ifP, grayrow, cols, mmaxval, format);

        for (col = 0; col < cols; ++col) {
            /* Because total pixels in image is limited: */
            assert (hist[grayrow[col]] < INT_MAX);

            ++hist[grayrow[col]];
        }
    }
    pgm_freerow(grayrow);

    *histP = hist;
}



static void
findQuantiles(unsigned int      const n,
              unsigned long int const hist[],
              unsigned long int const totalCt,
              gray              const mmaxval,
              gray *            const quantile) {
/*----------------------------------------------------------------------------
   Find the order-n quantiles (e.g. n == 4 means quartiles) of the pixel
   sample values, given that hist[] is the histogram of them (hist[N] is the
   number of pixels that have sample value N).

   'mmaxval' is the highest index in hist[] (so its size is 'mmaxval' + 1,
   and there are no pixels greater than 'mmaxval' in the image).

   We return the ith quantile as quantile[i].  For example, for quartiles,
   quantile[3] is the least sample value for which at least 3/4 of the pixels
   are less than or equal to it.

   quantile[] must be allocated at least to size 'n'.

   'n' must not be more than 100.
-----------------------------------------------------------------------------*/
    unsigned int quantSeq;
        /* 0 is first quantile, 1 is second quantile, etc. */

    gray sampleVal;
        /* As we increment through all the possible sample values, this
           is the one we're considering now.
        */
    unsigned int cumCt;
        /* The number of pixels that have sample value 'sampleVal' or less. */

    assert(n > 1 && n <= 100);

    sampleVal = 0;    /* initial value */
    cumCt = hist[0];  /* initial value */

    for (quantSeq = 1; quantSeq <= n; ++quantSeq) {
        unsigned long int const q = totalCt / n; 
        unsigned long int const r = totalCt % n;  
        unsigned long int const quantCt = q*quantSeq + (r*quantSeq + n - 1)/n;
       /* This is how many pixels are (ignoring quantization) in the
          quantile.  E.g. for the 3rd quartile, it is 3/4 of the pixels
          in the image.

          This is equivalent to (float) totalCt * quantSeq / n rounded
          upwards.  We use the int version in spite of complexities
          for preventing overflow for slight innacuracies in floating
          point arithmetic causes problems when used as loop counter
          and array index.
       */
        assert(quantCt <= totalCt);

        /* at sampleVal == mmaxval, cumCt == totalCt, so because
           quantCt <= 'totalCt', 'sampleVal' cannot go above mmaxval.
        */

        while (cumCt < quantCt) {
            ++sampleVal;
            cumCt += hist[sampleVal];
        }

        assert(sampleVal <= mmaxval);

        /* 'sampleVal' is the lowest sample value for which at least 'quantCt'
           pixels have that sample value or less.  'cumCt' is the number
           of pixels that have sample value 'sampleVal' or less.
        */
        quantile[quantSeq-1] = sampleVal;
    }
}



static void
countCumulative(unsigned long int    const hist[],
                gray                 const mmaxval,
                unsigned long int    const totalPixelCt,
                unsigned long int ** const rcountP) {
/*----------------------------------------------------------------------------
   From the histogram hist[] (hist[N] is the number of pixels of sample
   value N), compute the cumulative distribution *rcountP ((*rcountP)[N]
   is the number of pixels of sample value N or higher).

   *rcountP is newly malloced memory.
-----------------------------------------------------------------------------*/
    unsigned long int * rcount;
    unsigned long int cumCount;
    int i;

    MALLOCARRAY(rcount, mmaxval + 1);
    if (rcount == NULL)
        pm_error("out of memory");

    for (i = mmaxval, cumCount = 0; i >= 0; --i) {
        /* Because total pixels in image is limited: */
        assert(ULONG_MAX - hist[i] >= cumCount);

        cumCount += hist[i];
        rcount[i] = cumCount;
    }

    *rcountP = rcount;
}



static void
reportHistHumanFriendly(unsigned long int const hist[],
                        unsigned long int const rcount[],
                        gray              const maxval) {

    unsigned long int const totalPixelCt = rcount[0];

    unsigned int cumCount;
    unsigned int i;

    printf("value  count  b%%     w%%   \n");
    printf("-----  -----  ------  ------\n");

    for (i = 0, cumCount = 0; i <= maxval; ++i) {
        if (hist[i] > 0) {
            cumCount += hist[i];
            printf(
                "%5d  %5ld  %5.3g%%  %5.3g%%\n", i, hist[i],
                (float) cumCount * 100.0 / totalPixelCt,
                (float) rcount[i] * 100.0 / totalPixelCt);
        }
    }
}


static void
reportHistForensicHumanFriendly(unsigned long int const hist[],
                                unsigned long int const rcount[],
                                gray              const maxval,
                                gray              const mmaxval) {

    unsigned long int const totalPixelCt = rcount[0];

    unsigned long int cumCount;
    unsigned int i;

    printf("value  count  b%%     w%%   \n");
    printf("-----  -----  ------  ------\n");

    for (i = 0, cumCount = 0; i <= maxval; ++i) {
        if (hist[i] > 0) {
            cumCount += hist[i];
            printf(
                "%5d  %5ld  %5.3g%%  %5.3g%%\n", i, hist[i],
                (float) cumCount * 100.0 / totalPixelCt,
                (float) rcount[i] * 100.0 / totalPixelCt);
        }
    }
    if (totalPixelCt > cumCount) {
        printf("-----  -----\n");

        for (i = maxval; i <= mmaxval; ++i) {
            if (hist[i] > 0) {
                cumCount += hist[i];
                printf(
                    "%5d  %5ld  %5.3g%%  %5.3g%%\n", i, hist[i],
                    (float) cumCount * 100.0 / totalPixelCt,
                    (float) rcount[i] * 100.0 / totalPixelCt);
            }
        }
    }
}



static void
reportHistMachineFriendly(unsigned long int const hist[],
                          gray              const maxval) {

    unsigned int i;

    for (i = 0; i <= maxval; ++i) {
        printf("%u %lu\n", i, hist[i]);
    }
}



static void
reportQuantilesMachineFriendly(gray         const quantile[],
                               unsigned int const n) {

    unsigned int i;

    for (i = 0; i < n; ++i)
        printf("%u\n", quantile[i]);
}



static void
reportMedianHumanFriendly(gray const median) {

    printf("Median: %5u\n", median);
}



static void
reportQuartilesHumanFriendly(gray const quartile[]) {

    unsigned int i;

    printf("Quartiles:\n");

    printf("Q    Value\n");
    printf("---- -----\n");

    for (i = 1; i <= 4; ++i)
        printf("%3u%% %5u\n", 25*i, quartile[i-1]);
}



static void
reportDecilesHumanFriendly(gray const decile[]) {

    unsigned int i;

    printf("Deciles:\n");

    printf("Q    Value\n");
    printf("---  -----\n");

    for (i = 1; i <= 10; ++i)
        printf("%3u%% %5u\n", 10*i, decile[i-1]);
}



static void
summarizeInvalidPixels(unsigned long int const hist[],
                       unsigned long int const rcount[],
                       gray              const mmaxval,
                       gray              const maxval) {
/*----------------------------------------------------------------------------
  Print total count of valid and invalid pixels, if there are any
  invalid ones.
-----------------------------------------------------------------------------*/
    unsigned long int const invalidPixelCt = 
        mmaxval > maxval ? rcount[maxval+1] : 0;

    if (invalidPixelCt > 0) {
        unsigned long int const totalPixelCt = rcount[0];
        unsigned long int const validPixelCt = totalPixelCt - invalidPixelCt;

        printf("\n");
        printf("** Image stream contains invalid sample values "
               "(above maxval %u)\n", maxval);
        printf("Valid sample values:   %lu (%5.4g%%)\n",
               validPixelCt,   (float)validPixelCt / totalPixelCt * 100.0);
        printf("Invalid sample values: %lu (%5.4g%%)\n",
               invalidPixelCt, (float)invalidPixelCt / totalPixelCt * 100.0);
    }
}



static void
reportFromHistogram(const unsigned long int * const hist,
                    gray                      const mmaxval,
                    gray                      const maxval,
                    unsigned long int         const totalPixelCt,
                    struct CmdlineInfo        const cmdline) {
/*----------------------------------------------------------------------------
   Analyze histogram 'hist', which has 'mmaxval' buckets, and report
   what we find.

   'maxval' is the maxval that the image states (but note that we tolerate
   invalid sample values greater than maxval, which could be as high as
   'mmaxval').

   'cmdline' tells what kind of reporting to do.
-----------------------------------------------------------------------------*/

    if (cmdline.median) {
        gray median[2];
        findQuantiles(2, hist, totalPixelCt, mmaxval, median);
        if (cmdline.machine)
            reportQuantilesMachineFriendly(median, 1);
        else
            reportMedianHumanFriendly(median[0]);
    } else if (cmdline.quartile) {
        gray quartile[4];
        findQuantiles(4, hist, totalPixelCt, mmaxval, quartile);
        if (cmdline.machine)
            reportQuantilesMachineFriendly(quartile, 4);
        else
            reportQuartilesHumanFriendly(quartile);
    } else if (cmdline.decile) {
        gray decile[10];
        findQuantiles(10, hist, totalPixelCt, mmaxval, decile);
        if (cmdline.machine)
            reportQuantilesMachineFriendly(decile, 10);
        else
            reportDecilesHumanFriendly(decile);
    } else {
        if (cmdline.machine)
            reportHistMachineFriendly(hist, mmaxval);
        else {
            unsigned long int * rcount; /* malloc'ed array */
            countCumulative(hist, mmaxval, totalPixelCt, &rcount);
            if (cmdline.forensic)
                reportHistForensicHumanFriendly(hist, rcount, maxval, mmaxval);
            else
                reportHistHumanFriendly(hist, rcount, maxval);

            summarizeInvalidPixels(hist, rcount, mmaxval, maxval);

            free(rcount);
        }
    }
}



int
main(int argc, const char ** argv) {

    struct CmdlineInfo cmdline;
    FILE * ifP;
    int rows, cols;
    int format;
    gray maxval;
        /* Stated maxval of the image */
    gray mmaxval;
        /* Maxval we assume, which may be greater than the stated maxval
           so that we can process invalid pixels in the image that exceed
           the maxval.
        */
    unsigned long int totalPixelCt;
    unsigned long int * hist;   /* malloc'ed array */

    pm_proginit(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    ifP = pm_openr(cmdline.inputFileName);

    pgm_readpgminit(ifP, &cols, &rows, &maxval, &format);

    if (ULONG_MAX / cols < rows)
        pm_error("Too many pixels (%u x %u) in image.  "
                 "Maximum computable is %lu",
                 cols, rows, ULONG_MAX);

    totalPixelCt = cols * rows;

    mmaxval = cmdline.forensic ? universalMaxval(maxval, format) : maxval;

    buildHistogram(ifP, format, cols, rows, mmaxval, &hist);

    reportFromHistogram(hist, mmaxval, maxval, totalPixelCt, cmdline);

    free(hist);
    pm_close(ifP);

    return 0;
}
