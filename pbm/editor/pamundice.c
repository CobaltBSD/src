/*****************************************************************************
                                  pamundice
******************************************************************************
  Assemble a grid of images into one.

  By Bryan Henderson, San Jose CA 2001.01.31

  Contributed to the public domain.

******************************************************************************/

#include <assert.h>
#include <string.h>

#include "pm_c_util.h"
#include "pam.h"
#include "shhopt.h"
#include "nstring.h"
#include "mallocvar.h"

#define MAXFILENAMELEN 80
    /* Maximum number of characters we accept in filenames */

struct cmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    const char * inputFilePattern;
        /* null-terminated string, max MAXFILENAMELEN-10 characters */
    unsigned int across;
    unsigned int down;
    unsigned int hoverlap; 
    unsigned int voverlap; 
    unsigned int verbose;
};



static void
parseCommandLine(int argc, char ** argv,
                 struct cmdlineInfo * const cmdlineP ) {
/*----------------------------------------------------------------------------
   parse program command line described in Unix standard form by argc
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
    
    unsigned int acrossSpec, downSpec;
    unsigned int hoverlapSpec, voverlapSpec;
    unsigned int option_def_index;

    MALLOCARRAY_NOFAIL(option_def, 100);

    option_def_index = 0;   /* incremented by OPTENT3 */
    OPTENT3(0, "across",      OPT_UINT,    &cmdlineP->across,
            &acrossSpec,                      0);
    OPTENT3(0, "down",        OPT_UINT,    &cmdlineP->down,
            &downSpec,                        0);
    OPTENT3(0, "hoverlap",    OPT_UINT,    &cmdlineP->hoverlap,
            &hoverlapSpec,                    0);
    OPTENT3(0, "voverlap",    OPT_UINT,    &cmdlineP->voverlap,
            &voverlapSpec,                    0);
    OPTENT3(0, "verbose",     OPT_FLAG,    NULL,
            &cmdlineP->verbose,               0);

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = FALSE;  /* We have no parms that are negative numbers */

    pm_optParseOptions3( &argc, argv, opt, sizeof(opt), 0 );
        /* Uses and sets argc, argv, and some of *cmdline_p and others. */

    if (!acrossSpec)
        cmdlineP->across = 1;
    
    if (!downSpec)
        cmdlineP->down = 1;

    if (!hoverlapSpec)
        cmdlineP->hoverlap = 0;

    if (!voverlapSpec)
        cmdlineP->voverlap = 0;

    if (argc-1 < 1)
        pm_error("You must specify one argument: the input file name "
                 "pattern (e.g. 'myimage%%2a%%2d.pnm')");
    else {
        cmdlineP->inputFilePattern = argv[1];

        if (argc-1 > 1)
            pm_error("Progam takes at most one parameter: input file name.  "
                     "You specified %u", argc-1);
    }
}



/*------------------ string buffer -----------------------------------*/
struct buffer {
    char * string;
    unsigned int allocSize;
    unsigned int length;
};


static void
buffer_init(struct buffer * const bufferP) {

    bufferP->length = 0;
    bufferP->allocSize = 1024;
    MALLOCARRAY(bufferP->string, bufferP->allocSize);

    if (bufferP->string == NULL)
        pm_error("Out of memory allocating buffer to compute file name");
}



static void
buffer_term(struct buffer * const bufferP) {
    
    free(bufferP->string);
}



static void
buffer_addChar(struct buffer * const bufferP,
               char            const newChar) {

    if (bufferP->length + 1 + 1 > bufferP->allocSize)
        pm_error("Ridiculously long input file name.");
    else {
        bufferP->string[bufferP->length++] = newChar;
        bufferP->string[bufferP->length] = '\0';
    }
}



static void
buffer_addString(struct buffer * const bufferP,
                 const char *    const newString) {

    if (bufferP->length + 1 + strlen(newString) > bufferP->allocSize)
        pm_error("Ridiculously long input file name.");
    else {
        strcat(&bufferP->string[bufferP->length], newString);
        bufferP->length += strlen(newString);
    }
}
/*------------------ end of string buffer ----------------------------*/



/*------------------ computeInputFileName ----------------------------*/
static unsigned int
digitValue(char const digitChar) {

    return digitChar - '0';
}



static void
getPrecision(const char *   const pattern,
             unsigned int   const startInCursor,
             unsigned int * const precisionP,
             unsigned int * const newInCursorP) {

    unsigned int precision;
    unsigned int inCursor;

    inCursor = startInCursor;  /* Start right after the '%' */

    precision = 0;
                
    while (isdigit(pattern[inCursor])) {
        precision = 10 * precision + digitValue(pattern[inCursor]);
        ++inCursor;
    }

    if (precision == 0)
        pm_error("Zero (or no) precision in substitution "
                 "specification in file name pattern '%s'.  "
                 "A proper substitution specification is like "
                 "'%%3a'.", pattern);

    *precisionP = precision;
    *newInCursorP = inCursor;
}



static void
doSubstitution(const char *    const pattern,
               unsigned int    const startInCursor,
               unsigned int    const rank,
               unsigned int    const file,
               struct buffer * const bufferP,
               unsigned int *  const newInCursorP) {

    unsigned int inCursor;

    inCursor = startInCursor;  /* Start right after the '%' */

    if (pattern[inCursor] == '%') {
        buffer_addChar(bufferP, '%');
        ++inCursor;
    } else {
        unsigned int precision;
        
        getPrecision(pattern, inCursor, &precision, &inCursor);

        if (pattern[inCursor] == '\0')
            pm_error("No format character follows '%%' in input "
                     "file name pattern '%s'.  A proper substitution "
                     "specification is like '%%3a'", pattern);
        else {
            const char * substString;
            const char * desc;

            switch (pattern[inCursor]) {
            case 'a':
                pm_asprintf(&substString, "%0*u", precision, file);
                pm_asprintf(&desc, "file (across)");
                break;
            case 'd':
                pm_asprintf(&substString, "%0*u", precision, rank);
                pm_asprintf(&desc, "rank (down)");
                break;
            default:
                pm_error("Unknown format specifier '%c' in input file "
                         "pattern '%s'.  Recognized format specifier s are "
                         "'%%a' (across) and '%%d (down)'",
                         pattern[inCursor], pattern);
            }
            if (strlen(substString) > precision)
                pm_error("%s number %u is wider than "
                         "the %u characters specified in the "
                         "input file pattern",
                         desc, (unsigned)strlen(substString), precision);
            else
                buffer_addString(bufferP, substString);
            
            pm_strfree(desc);
            pm_strfree(substString);

            ++inCursor;
        }
    }
    *newInCursorP = inCursor;
}



static void
computeInputFileName(const char *  const pattern,
                     unsigned int  const rank,
                     unsigned int  const file,
                     const char ** const fileNameP) {

    struct buffer buffer;
    unsigned int inCursor, outCursor;

    buffer_init(&buffer);

    inCursor = 0;
    outCursor = 0;

    while (pattern[inCursor] != '\0') {
        if (pattern[inCursor] == '%') {
            ++inCursor;

            doSubstitution(pattern, inCursor, rank, file, &buffer, &inCursor);

        } else
            buffer_addChar(&buffer, pattern[inCursor++]);
    }

    pm_asprintf(fileNameP, "%s", buffer.string);

    buffer_term(&buffer);
}
/*------------------ end of computeInputFileName ------------------------*/



static void
getCommonInfo(const char *   const inputFilePattern,
              int *          const formatP,
              unsigned int * const depthP,
              sample *       const maxvalP,
              char *         const tupleType) {
/*----------------------------------------------------------------------------
   Get from the top left input image all the information which is common
   among all input images and the output image.  I.e. everything except
   width and height.
-----------------------------------------------------------------------------*/
    const char * fileName;
        /* Name of top left input image */
    FILE * ifP;
        /* Top left input image stream */
    struct pam inpam00;
        /* Description of top left input image */

    computeInputFileName(inputFilePattern, 0, 0, &fileName);

    ifP = pm_openr(fileName);

    pnm_readpaminit(ifP, &inpam00, PAM_STRUCT_SIZE(tuple_type));

    *formatP = inpam00.format;
    *depthP  = inpam00.depth;
    *maxvalP = inpam00.maxval;
    strcpy(tupleType, inpam00.tuple_type);

    pm_close(ifP);

    pm_strfree(fileName);
}



static FILE *
openInputImage(const char * const inputFilePattern,
               unsigned int const rank,
               unsigned int const file) {

    FILE * retval;
    const char * fileName;
        
    computeInputFileName(inputFilePattern, rank, file, &fileName);

    retval = pm_openr(fileName);
    
    pm_strfree(fileName);

    return retval;
}

               

static void
getImageInfo(const char * const inputFilePattern,
             unsigned int const rank,
             unsigned int const file,
             struct pam * const pamP) {

    FILE * ifP;

    ifP = openInputImage(inputFilePattern, rank, file);

    pnm_readpaminit(ifP, pamP, PAM_STRUCT_SIZE(tuple_type));

    pm_close(ifP);
    pamP->file = NULL;  /* for robustness */
}



static void
getOutputWidth(const char * const inputFilePattern,
               unsigned int const nFile,
               unsigned int const hoverlap,
               int *        const widthP) {
/*----------------------------------------------------------------------------
   Get the output width by adding up the widths of all 'nFile' images of
   the top rank, and allowing for overlap of 'hoverlap' pixels.
-----------------------------------------------------------------------------*/
    unsigned int totalWidth;
    unsigned int file;

    for (file = 0, totalWidth = 0; file < nFile; ++file) {
        struct pam inpam;

        getImageInfo(inputFilePattern, 0, file, &inpam);

        if (inpam.width < hoverlap)
            pm_error("Rank 0, file %u image has width %u, "
                     "which is less than the horizontal overlap of %u pixels",
                     file, inpam.width, hoverlap);
        else {
            totalWidth += inpam.width;

            if (file < nFile-1)
                totalWidth -= hoverlap;
        }
    }
    *widthP = totalWidth;
}



static void
getOutputHeight(const char *  const inputFilePattern,
                unsigned int  const nRank,
                unsigned int  const voverlap,
                int *         const heightP) {
/*----------------------------------------------------------------------------
   Get the output height by adding up the widths of all 'nRank' images of
   the left file, and allowing for overlap of 'voverlap' pixels.
-----------------------------------------------------------------------------*/
    unsigned int totalHeight;
    unsigned int rank;

    for (rank = 0, totalHeight = 0; rank < nRank; ++rank) {
        struct pam inpam;

        getImageInfo(inputFilePattern, rank, 0, &inpam);

        if (inpam.height < voverlap)
            pm_error("Rank %u, file 0 image has height %u, "
                     "which is less than the vertical overlap of %u pixels",
                     rank, inpam.height, voverlap);
        
        totalHeight += inpam.height;
        
        if (rank < nRank-1)
            totalHeight -= voverlap;
    }
    *heightP = totalHeight;
}



static void
initOutpam(const char * const inputFilePattern,
           unsigned int const nFile,
           unsigned int const nRank,
           unsigned int const hoverlap,
           unsigned int const voverlap,
           FILE *       const ofP,
           bool         const verbose,
           struct pam * const outpamP) {
/*----------------------------------------------------------------------------
   Figure out the attributes of the output image and return them as
   *outpamP.

   Do this by examining the top rank and left file of the input images,
   which are in files named by 'inputFilePattern', 'nFile', and 'nRank'.

   In computing dimensions, assume 'hoverlap' pixels of horizontal
   overlap and 'voverlap' pixels of vertical overlap.

   We overlook any inconsistencies among the images.  E.g. if two images
   have different depths, we just return one of them.  If two images in
   the top rank have different heights, we use just one of them.

   Therefore, Caller must check all the input images to make sure they are
   consistent with the information we return.
-----------------------------------------------------------------------------*/
    assert(nFile >= 1);
    assert(nRank >= 1);

    outpamP->size        = sizeof(*outpamP);
    outpamP->len         = PAM_STRUCT_SIZE(tuple_type);
    outpamP->file        = ofP;
    outpamP->plainformat = 0;
    
    getCommonInfo(inputFilePattern, &outpamP->format, &outpamP->depth,
                  &outpamP->maxval, outpamP->tuple_type);

    getOutputWidth(inputFilePattern, nFile, hoverlap, &outpamP->width);

    getOutputHeight(inputFilePattern, nRank, voverlap, &outpamP->height);

    if (verbose) {
        pm_message("Output width = %u pixels", outpamP->width);
        pm_message("Output height = %u pixels", outpamP->height);
    }
}



static void
openInStreams(struct pam         inpam[],
              unsigned int const rank,
              unsigned int const fileCount,
              char         const inputFilePattern[]) {
/*----------------------------------------------------------------------------
   Open the input files for a single horizontal slice (there's one file
   for each vertical slice) and read the Netpbm headers from them.  Return
   the pam structures to describe each as inpam[].

   Open the files for horizontal slice number 'rank', assuming there are
   'fileCount' vertical slices (so open 'fileCount' files).  Use
   inputFilePattern[] with each rank and file number to compute the name of
   each file.
-----------------------------------------------------------------------------*/
    unsigned int file;

    for (file = 0; file < fileCount; ++file) {
        FILE * const ifP = openInputImage(inputFilePattern, rank, file);

        pnm_readpaminit(ifP, &inpam[file], PAM_STRUCT_SIZE(tuple_type));
    }        
}



static void
closeInFiles(struct pam         pam[],
             unsigned int const fileCount) {
/*----------------------------------------------------------------------------
   Close the 'fileCount' input file streams represented by pam[].
-----------------------------------------------------------------------------*/
    unsigned int file;
    
    for (file = 0; file < fileCount; ++file)
        pm_close(pam[file].file);
}



static void
assembleRow(tuple              outputRow[], 
            struct pam         inpam[], 
            unsigned int const fileCount,
            unsigned int const hOverlap) {
/*----------------------------------------------------------------------------
   Assemble the row outputRow[] from the 'fileCount' input files
   described out inpam[].

   'hOverlap', which is meaningful only when fileCount is greater than 1,
   is the amount by which files overlap each other.  We assume every
   input image is at least that wide.

   We assume that outputRow[] is allocated wide enough to contain the
   entire assembly.
-----------------------------------------------------------------------------*/
    tuple * inputRow;
    unsigned int file;

    for (file = 0, inputRow = &outputRow[0]; 
         file < fileCount; 
         ++file) {

        unsigned int const overlap = file == fileCount - 1 ? 0 : hOverlap;

        assert(hOverlap <= inpam[file].width);

        pnm_readpamrow(&inpam[file], inputRow);

        inputRow += inpam[file].width - overlap;
    }
}



static void
allocInpam(unsigned int  const rankCount,
           struct pam ** const inpamArrayP) {

    struct pam * inpamArray;

    MALLOCARRAY(inpamArray, rankCount);

    if (inpamArray == NULL)
        pm_error("Unable to allocate array for %u input pam structures.",
                 rankCount);

    *inpamArrayP = inpamArray;
}



static void
verifyRankFileAttributes(struct pam *       const inpam,
                         unsigned int       const nFile,
                         const struct pam * const outpamP,
                         unsigned int       const hoverlap,
                         unsigned int       const rank) {
/*----------------------------------------------------------------------------
   Verify that the 'nFile' images that make up a rank, which are described
   by inpam[], are consistent with the properties of the assembled image
   *outpamP.

   I.e. verify that each image has the depth, maxval, format, and tuple
   type of *outpamP and their total width is the width given by
   *outpamP.

   Also verify that every image has the same height.

   Abort the program if verification fails.
-----------------------------------------------------------------------------*/
    unsigned int file;
    unsigned int totalWidth;

    for (file = 0, totalWidth = 0; file < nFile; ++file) {
        struct pam * const inpamP = &inpam[file];

        if (inpamP->depth != outpamP->depth)
            pm_error("Rank %u, File %u image has depth %u, "
                     "which differs from others (%u)",
                     rank, file, inpamP->depth, outpamP->depth);
        else if (inpamP->maxval != outpamP->maxval)
            pm_error("Rank %u, File %u image has maxval %lu, "
                     "which differs from others (%lu)",
                     rank, file, inpamP->maxval, outpamP->maxval);
        else if (inpamP->format != outpamP->format)
            pm_error("Rank %u, File %u image has format 0x%x, "
                     "which differs from others (0x%x)",
                     rank, file, inpamP->format, outpamP->format);
        else if (!streq(inpamP->tuple_type, outpamP->tuple_type))
            pm_error("Rank %u, File %u image has tuple type '%s', "
                     "which differs from others ('%s')",
                     rank, file, inpamP->tuple_type, outpamP->tuple_type);

        else if (inpamP->height != inpam[0].height)
            pm_error("Rank %u, File %u image has height %u, "
                     "which differs from that of File 0 in the same rank (%u)",
                     rank, file, inpamP->height, inpam[0].height);
        else {
            totalWidth += inpamP->width;
        
            if (file < nFile-1)
                totalWidth -= hoverlap;
        }
    }

    if (totalWidth != outpamP->width)
        pm_error("Rank %u has a total width (%u) different from that of "
                 "other ranks (%u)", rank, totalWidth, outpamP->width);
}



static void
assembleTiles(struct pam * const outpamP,
              const char * const inputFilePattern,
              unsigned int const nFile,
              unsigned int const nRank,
              unsigned int const hoverlap,
              unsigned int const voverlap,
              struct pam         inpam[],
              tuple *      const tuplerow) {

    unsigned int rank;
        /* Number of the current rank (horizontal slice).  Ranks are numbered
           sequentially starting at 0.
        */
    
    for (rank = 0; rank < nRank; ++rank) {
        unsigned int row;
        unsigned int rankHeight;

        openInStreams(inpam, rank, nFile, inputFilePattern);

        verifyRankFileAttributes(inpam, nFile, outpamP, hoverlap, rank);

        rankHeight = inpam[0].height - (rank == nRank-1 ? 0 : voverlap);

        for (row = 0; row < rankHeight; ++row) {
            assembleRow(tuplerow, inpam, nFile, hoverlap);

            pnm_writepamrow(outpamP, tuplerow);
        }
        closeInFiles(inpam, nFile);
    }
}



int
main(int argc, char ** argv) {

    struct cmdlineInfo cmdline;
    struct pam outpam;
    struct pam * inpam;
        /* malloc'ed.  inpam[x] is the pam structure that controls the
           current rank of file x. 
        */
    tuple * tuplerow;

    pnm_init(&argc, argv);
    
    parseCommandLine(argc, argv, &cmdline);
        
    allocInpam(cmdline.across, &inpam);

    initOutpam(cmdline.inputFilePattern, cmdline.across, cmdline.down,
               cmdline.hoverlap, cmdline.voverlap, stdout, cmdline.verbose,
               &outpam);
    
    tuplerow = pnm_allocpamrow(&outpam);

    pnm_writepaminit(&outpam);

    assembleTiles(&outpam,
                  cmdline.inputFilePattern, cmdline.across, cmdline.down,
                  cmdline.hoverlap, cmdline.voverlap, inpam, tuplerow);

    pnm_freepamrow(tuplerow);

    free(inpam);

    return 0;
}
