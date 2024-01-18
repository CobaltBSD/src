/* This is a backward compatibility interface to Pamtogif.

   Pamtogif replaced Ppmtogif in Netpbm 10.37 (December 2006).

   The only significant ways Pamtogif are not backward compatible with
   old Ppmtogif are:

     - Pamtogif does not have a -alpha option.

     - Pamtogif requires a user-specififed map file (-mapfile) to
       match the input in depth.
*/
#define _BSD_SOURCE   /* Make sure strdup() is in string.h */
#define _XOPEN_SOURCE 500  /* Make sure strdup() is in string.h */

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#include "pm_c_util.h"
#include "mallocvar.h"
#include "shhopt.h"
#include "nstring.h"
#include "pam.h"



static const char *
dirname(const char * const fileName) {

    char * buffer;
    char * slashPos;

    buffer = strdup(fileName);

    slashPos = strchr(buffer, '/');

    if (slashPos)
        *slashPos = '\0';

    return buffer;
}



struct cmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    const char *inputFileName;  /* Name of input file */
    const char *alpha_filespec; /* Filespec of alpha file; NULL if none */
    const char *alphacolor;     /* -alphacolor option value or default */
    unsigned int interlace;     /* -interlace option value */
    unsigned int sort;          /* -sort option value */
    const char *mapfile;        /* -mapfile option value.  NULL if none. */
    const char *transparent;    /* -transparent option value.  NULL if none. */
    const char *comment;        /* -comment option value; NULL if none */
    unsigned int nolzw;         /* -nolzw option */
    unsigned int verbose;
};


static void
handleLatex2htmlHack(void) {
/*----------------------------------------------------------------------------
  This program used to put out a "usage" message when it saw an option
  it didn't understand.  Latex2html's configure program does a
  ppmtogif -h (-h was never a valid option) to elicit that message and
  then parses the message to see if it includes the strings
  "-interlace" and "-transparent".  That way it knows if the
  'ppmtogif' program it found has those options or not.  I don't think
  any 'ppmtogif' you're likely to find today lacks those options, but
  latex2html checks anyway, and we don't want it to conclude that we
  don't have them.

  So we issue a special error message just to trick latex2html into
  deciding that we have -interlace and -transparent options.  The function
  is not documented in the man page.  We would like to see Latex2html 
  either stop checking or check like configure programs usually do -- 
  try the option and see if you get success or failure.

  -Bryan 2001.11.14
-----------------------------------------------------------------------------*/
     pm_error("latex2html, you should just try the -interlace and "
              "-transparent options to see if they work instead of "
              "expecting a 'usage' message from -h");
}



static void
parseCommandLine(int argc, const char ** argv,
                 struct cmdlineInfo * const cmdlineP) {
/*----------------------------------------------------------------------------
   Parse the program arguments (given by argc and argv) into a form
   the program can deal with more easily -- a cmdline_info structure.
   If the syntax is invalid, issue a message and exit the program via
   pm_error().

   Note that the file spec array we return is stored in the storage that
   was passed to us as the argv array.
-----------------------------------------------------------------------------*/
    optEntry * option_def;  /* malloc'ed */
    optStruct3 opt;  /* set by OPTENT3 */
    unsigned int option_def_index;

    unsigned int latex2htmlhack;

    MALLOCARRAY_NOFAIL(option_def, 100);

    option_def_index = 0;   /* incremented by OPTENT3 */
    OPTENT3(0,   "interlace",   OPT_FLAG,   
            NULL,                       &cmdlineP->interlace, 0);
    OPTENT3(0,   "sort",        OPT_FLAG,   
            NULL,                       &cmdlineP->sort, 0);
    OPTENT3(0,   "nolzw",       OPT_FLAG,   
            NULL,                       &cmdlineP->nolzw, 0);
    OPTENT3(0,   "mapfile",     OPT_STRING, 
            &cmdlineP->mapfile,        NULL, 0);
    OPTENT3(0,   "transparent", OPT_STRING, 
            &cmdlineP->transparent,    NULL, 0);
    OPTENT3(0,   "comment",     OPT_STRING, 
            &cmdlineP->comment,        NULL, 0);
    OPTENT3(0,   "alpha",       OPT_STRING, 
            &cmdlineP->alpha_filespec, NULL, 0);
    OPTENT3(0,   "alphacolor",  OPT_STRING, 
            &cmdlineP->alphacolor,     NULL, 0);
    OPTENT3(0,   "h",           OPT_FLAG, 
            NULL,                       &latex2htmlhack, 0);
    OPTENT3(0,   "verbose",     OPT_FLAG, 
            NULL,                       &cmdlineP->verbose, 0);
    
    /* Set the defaults */
    cmdlineP->mapfile = NULL;
    cmdlineP->transparent = NULL;  /* no transparency */
    cmdlineP->comment = NULL;      /* no comment */
    cmdlineP->alpha_filespec = NULL;      /* no alpha file */
    cmdlineP->alphacolor = "rgb:0/0/0";      
        /* We could say "black" here, but then we depend on the color names
           database existing.
        */

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = FALSE;  /* We have no parms that are negative numbers */

    pm_optParseOptions3(&argc, (char **)argv, opt, sizeof(opt), 0);
        /* Uses and sets argc, argv, and some of *cmdlineP and others. */

    if (latex2htmlhack) 
        handleLatex2htmlHack();

    if (argc-1 == 0) 
        cmdlineP->inputFileName = "-";
    else if (argc-1 != 1)
        pm_error("Program takes zero or one argument (filename).  You "
                 "specified %d", argc-1);
    else
        cmdlineP->inputFileName = argv[1];

    if (cmdlineP->alpha_filespec && cmdlineP->transparent)
        pm_error("You cannot specify both -alpha and -transparent.");
}



static void
openPnmremapStream(const char * const inputFileName,
                   const char * const mapFileName,
                   bool         const verbose,
                   FILE **      const pnmremapPipeP) {
/*----------------------------------------------------------------------------
   Create a process to run the image in file inputFileName[] through
   Pnmremap, remapping it to the colors in mapFileName[].  Have it
   write its output to a pipe and return as *pnmremapPipeP the other
   end of that pipe.
-----------------------------------------------------------------------------*/
    FILE * pnmremapPipe;
    const char * pnmremapCommand;

    assert(inputFileName != NULL);
    assert(mapFileName != NULL);

    pm_asprintf(&pnmremapCommand, "pnmremap -mapfile='%s' %s",
                mapFileName, inputFileName);

    if (verbose)
        pm_message("Preprocessing Pamtogif input with shell command '%s'",
                   pnmremapCommand);

    pnmremapPipe = popen(pnmremapCommand, "r");

    if (pnmremapPipe == NULL)
        pm_error("Shell command '%s', via popen(), to prepare the input "
                 "for Pamtogif, failed.", pnmremapCommand);
    else
        *pnmremapPipeP = pnmremapPipe;

    pm_strfree(pnmremapCommand);
}



static const char *
pamtogifCommand(const char *       const arg0,
                struct cmdlineInfo const cmdline) {

    const char * const pamtogifName = "pamtogif";

    const char * retval;

    const char * commandVerb;
    const char * transparentOpt;
    const char * commentOpt;

    if (strchr(arg0, '/')) {
        const char * const arg0DirName = dirname(arg0);
        const char * progName;

        struct stat statbuf;

        pm_asprintf(&progName, "%s/%s", arg0DirName, pamtogifName);

        if (stat(progName, &statbuf) == 0)
            commandVerb = progName;
        else
            commandVerb = strdup(pamtogifName);

        pm_strfree(arg0DirName);
    } else
        commandVerb = strdup(pamtogifName);

    if (cmdline.transparent)
        pm_asprintf(&transparentOpt, "-transparent=%s", cmdline.transparent);
    else
        transparentOpt = strdup("");

    if (cmdline.comment)
        pm_asprintf(&commentOpt, "-comment=%s", cmdline.comment);
    else
        commentOpt = strdup("");

    pm_asprintf(&retval, "%s - -alphacolor=%s %s %s %s %s %s %s",
                commandVerb,
                cmdline.alphacolor,
                cmdline.interlace ? "-interlace" : "",
                cmdline.sort ? "-sort" : "",
                transparentOpt,
                commentOpt,
                cmdline.nolzw ? "-nolzw" : "",
                cmdline.verbose ? "-verbose" : "");
    
    pm_strfree(transparentOpt);
    pm_strfree(commentOpt);

    return retval;
}



static void
feedPamtogifNoAlpha(struct pam * const inPamP,
                    FILE *       const pipeToPamtogif) {
    
    unsigned int row;
    struct pam outPam;
    tuple * tuplerow;

    tuplerow = pnm_allocpamrow(inPamP);

    outPam = *inPamP;
    outPam.file = pipeToPamtogif;
    
    pnm_writepaminit(&outPam);

    for (row = 0; row < inPamP->height; ++row) {
        pnm_readpamrow(inPamP, tuplerow);

        pnm_writepamrow(&outPam, tuplerow);
    }
    pnm_freepamrow(tuplerow);
}



static void
copyRasterWithAlpha(struct pam * const inPamP,
                    struct pam * const alphaPamP,
                    struct pam * const outPamP,
                    unsigned int const alphaPlane) {

    tuple * tuplerow;
    tuple * alpharow;
    unsigned int row;

    inPamP->allocation_depth = outPamP->depth;

    tuplerow = pnm_allocpamrow(inPamP);
    alpharow = pnm_allocpamrow(alphaPamP);

    for (row = 0; row < inPamP->height; ++row) {
        unsigned int col;
            
        pnm_readpamrow(inPamP, tuplerow);
        pnm_readpamrow(alphaPamP, alpharow);

        for (col = 0; col < inPamP->width; ++col) {
            tuplerow[col][alphaPlane] = pnm_scalesample(alpharow[col][0],
                                                        alphaPamP->maxval,
                                                        inPamP->maxval);
        }
        pnm_writepamrow(outPamP, tuplerow);
    }
    pnm_freepamrow(alpharow);
    pnm_freepamrow(tuplerow);
}



static void
feedPamtogifWithAlpha(struct pam * const inPamP,
                      struct pam * const alphaPamP,
                      FILE *       const pipeToPamtogif) {

    unsigned int alphaPlane;
    struct pam outPam;

    if (inPamP->width != alphaPamP->width ||
        inPamP->height != alphaPamP->height)
        pm_error("-alpha image dimensions (%u w x %u h) do not match "
                 "the input image dimensions (%u x %u)",
                 alphaPamP->width, alphaPamP->height,
                 inPamP->width, inPamP->height);

    outPam = *inPamP;
    outPam.file        = pipeToPamtogif;
    outPam.format      = PAM_FORMAT;
    outPam.plainformat = 0;

    if (inPamP->depth == 1) {
        alphaPlane = 1;
        strcpy(outPam.tuple_type, "GRAYSCALE_ALPHA");
    } else if (inPamP->depth == 3) {
        alphaPlane = 3;
        strcpy(outPam.tuple_type, "RGB_ALPHA");
    }
    outPam.depth = alphaPlane + 1;

    pnm_writepaminit(&outPam);

    copyRasterWithAlpha(inPamP, alphaPamP, &outPam, alphaPlane);
}



static void
feedPamtogif(struct pam * const inPamP,
             const char * const alphaFilespec,
             FILE *       const pipeToPamtogif) {
    
    if (alphaFilespec) {
        FILE * afP;
        struct pam alphaPam;
        afP = pm_openr(alphaFilespec);
        pnm_readpaminit(afP, &alphaPam, PAM_STRUCT_SIZE(tuple_type));
        feedPamtogifWithAlpha(inPamP, &alphaPam, pipeToPamtogif);
        pm_close(afP);
    } else
        feedPamtogifNoAlpha(inPamP, pipeToPamtogif);
}



int
main(int           argc,
     const char ** argv) {

    struct cmdlineInfo cmdline;
    FILE * ifP;
    struct pam inPam;
    const char * command;
    FILE * pipeToPamtogif;
    int rc;

    pm_proginit(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    if (cmdline.mapfile)
        openPnmremapStream(cmdline.inputFileName, cmdline.mapfile,
                           cmdline.verbose, &ifP);
    else
        ifP = pm_openr(cmdline.inputFileName);
        
    command = pamtogifCommand(argv[0], cmdline);

    if (cmdline.verbose)
        pm_message("Executing shell command '%s'", command);
    
    pipeToPamtogif = popen(command, "w");

    if (pipeToPamtogif == NULL)
        pm_error("Shell command '%s', via popen(), failed.", command);

    pnm_readpaminit(ifP, &inPam, PAM_STRUCT_SIZE(allocation_depth));

    feedPamtogif(&inPam, cmdline.alpha_filespec, pipeToPamtogif);

    rc = pclose(pipeToPamtogif);

    if (rc != 0)
        pm_error("Pamtogif process failed.  pclose() failed.");

    pm_strfree(command);

    pm_close(ifP);
    pm_close(stdout);

    return 0;
}
