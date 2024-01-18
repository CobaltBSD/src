/******************************************************************************
                               pamexec
*******************************************************************************
  Split a Netpbm format input file into multiple Netpbm format output streams
  with one image per output stream and pipe this into the specified command.

  By Bryan Henderson, Olympia WA; June 2000
  and Michael Pot, New Zealand, August 2011

  Contributed to the public domain by its authors.

******************************************************************************/

#define _BSD_SOURCE 1      /* Make sure strdup() is in string.h */
#define _XOPEN_SOURCE 500  /* Make sure strdup() is in string.h */

#include <string.h>
#include <stdio.h>
#include <errno.h>

#include "pm_c_util.h"
#include "shhopt.h"
#include "nstring.h"
#include "mallocvar.h"
#include "pam.h"

struct cmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    const char * command;
    const char * inputFileName;
    unsigned int debug;
    unsigned int check;
};




static void
parseCommandLine(int argc, const char ** argv,
                 struct cmdlineInfo * const cmdlineP) {
/*----------------------------------------------------------------------------
   Note that the pointers we place into *cmdlineP are sometimes to storage
   in the argv array.
-----------------------------------------------------------------------------*/
    optEntry *option_def;
        /* Instructions to OptParseOptions3 on how to parse our options.
         */
    optStruct3 opt;

    unsigned int option_def_index;

    MALLOCARRAY_NOFAIL(option_def, 100);

    option_def_index = 0;   /* incremented by OPTENT3 */
    OPTENT3(0,   "debug",   OPT_FLAG,   NULL,         &cmdlineP->debug, 0);
    OPTENT3(0,   "check",   OPT_FLAG,   NULL,         &cmdlineP->check, 0);

    opt.opt_table = option_def;
    opt.short_allowed = FALSE; /* We have no short (old-fashioned) options */
    opt.allowNegNum = FALSE;   /* We have no parms that are negative numbers */

    pm_optParseOptions3(&argc, (char **)argv, opt, sizeof(opt), 0);
        /* Uses and sets argc, argv, and some of *cmdlineP and others. */

    if (argc-1 < 1) 
        pm_error("You must specify at least one argument: the shell command "
                 "to execute");
    else {
        cmdlineP->command = argv[1];

        if (argc-1 < 2)
            cmdlineP->inputFileName = "-";
        else {
            cmdlineP->inputFileName = argv[2];

            if (argc-1 > 2)
                pm_error("Too many arguments.  There are at most two: "
                         "command and input file name");
        }
    }
}



static void
pipeOneImage(FILE * const infileP,
             FILE * const outfileP) {

    struct pam inpam;
    struct pam outpam;
    enum pm_check_code checkRetval;
    
    unsigned int row;
    tuple * tuplerow;

    pnm_readpaminit(infileP, &inpam, PAM_STRUCT_SIZE(tuple_type));

    pnm_checkpam(&inpam, PM_CHECK_BASIC, &checkRetval);

    outpam = inpam;
    outpam.file = outfileP;

    pnm_writepaminit(&outpam);

    tuplerow = pnm_allocpamrow(&inpam);

    for (row = 0; row < inpam.height; ++row) {
        pnm_readpamrow(&inpam, tuplerow);
        pnm_writepamrow(&outpam, tuplerow);
    }

    pnm_freepamrow(tuplerow);
}



static void
doOneImage(FILE *        const ifP,
           const char *  const command,
           bool          const check,
           const char ** const errorP) {
/*----------------------------------------------------------------------------
   Run command 'command' on the next image in stream *ifP.

   Return as *errorP a text explanation of how we failed, or NULL if we
   didn't.
-----------------------------------------------------------------------------*/
    FILE * ofP;

    ofP = popen(command, "w");

    if (ofP == NULL)
        pm_asprintf(errorP, 
                    "Failed to start shell to run command '%s'.  "
                    "errno = %d (%s)",
                    command, errno, strerror(errno));
    else {
        int rc;

        pipeOneImage(ifP, ofP);
            
        rc = pclose(ofP);

        if (check && rc != 0)
            pm_asprintf(errorP, "Command '%s' terminated abnormally "
                        "or with nonzero exit status", command);
        else
            *errorP = NULL;
    }
}



int
main(int argc, const char *argv[]) {

    struct cmdlineInfo cmdline;

    FILE *       ifP;         /* Input file pointer */
    int          eof;         /* No more images in input */
    unsigned int imageSeq;
        /* Sequence number of current image in input file.  First = 0.
           (Useful for tracking down problems).
        */

    pm_proginit(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);
    
    ifP = pm_openr(cmdline.inputFileName);

    for (eof = FALSE, imageSeq = 0; !eof; ++imageSeq) {
        const char * error;
        
        doOneImage(ifP, cmdline.command, cmdline.check, &error);

        if (error) {
            pm_error("Failed on image %u: %s", imageSeq, error);
            pm_strfree(error);
        }

        pnm_nextimage(ifP, &eof);
    }
    pm_close(ifP);
    
    return 0;
}



