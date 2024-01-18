/*============================================================================
                               pamunlookup
==============================================================================
  Find tuple values from an input image in a lookup table and
  produce a corresponding index image containing table indices.

  The lookup table is a one-row PAM image tuple type the same as the input
  image.  The output index image has the same width and height as the input
  image depth 1, and maxval equal to the width of the lookup image (the
  possible values include one for each column in the lookup image, plus one
  for tuple values that are not in the lookup image).

  By Bryan Henderson, San Jose CA 2015.08.08

============================================================================*/

#include <assert.h>

#include "pm_c_util.h"
#include "mallocvar.h"
#include "shhopt.h"
#include "pm_system.h"
#include "nstring.h"
#include "pam.h"
#include "pammap.h"



struct CmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    const char * inputFileName;
    char *       lookupfile;
};



static void
parseCommandLine(int argc, const char ** const argv,
                 struct CmdlineInfo * const cmdlineP) {
/*----------------------------------------------------------------------------
   Note that the file spec array we return is stored in the storage that
   was passed to us as the argv array.
-----------------------------------------------------------------------------*/
    optEntry * option_def;
        /* Instructions to OptParseOptions2 on how to parse our options.
         */
    optStruct3 opt;

    unsigned int option_def_index;
    
    unsigned int lookupfileSpec;

    MALLOCARRAY_NOFAIL(option_def, 100);

    option_def_index = 0;   /* incremented by OPTENTRY */
    OPTENT3(0, "lookupfile",     OPT_STRING, &cmdlineP->lookupfile,  
            &lookupfileSpec, 0);

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = FALSE;  /* We may have parms that are negative numbers */

    pm_optParseOptions3(&argc, (char **)argv, opt, sizeof(opt), 0);
        /* Uses and sets argc, argv, and some of *cmdlineP and others. */

    if (!lookupfileSpec)
        pm_error("You must specify the -lookupfile option");

    if (argc-1 < 1)
        cmdlineP->inputFileName = "-";
    else
        cmdlineP->inputFileName = argv[1];

    free(option_def);
}        



static void
getLookup(const char * const lookupFileName, 
          tuple ***    const lookupP,
          struct pam * const lookuppamP) {
/*----------------------------------------------------------------------------
   Get the lookup image (the one that maps integers to tuples, e.g. a
   color index / color map / palette) from the file named 
   'lookupFileName'.

   Return the image as *lookupP and *lookuppamP.
-----------------------------------------------------------------------------*/
    FILE *  lookupfileP;

    struct pam inputLookuppam;
    tuple ** inputLookup;

    lookupfileP = pm_openr(lookupFileName);
    inputLookup = pnm_readpam(lookupfileP, 
                              &inputLookuppam, PAM_STRUCT_SIZE(tuple_type));

    pm_close(lookupfileP);
    
    if (inputLookuppam.height != 1)
        pm_error("The lookup table image must be one row.  "
                 "Yours is %u rows.", 
                 inputLookuppam.height);

    *lookupP = inputLookup;
    *lookuppamP = inputLookuppam;
}



static void
makeReverseLookupHash(struct pam * const lookuppamP,
                      tuple **     const lookup,
                      tuplehash *  const hashP) {
/*----------------------------------------------------------------------------
   Create a tuple hash that maps each tuple values in the first row of
   'lookup' to the number of the column in which it appears.

   Abort the program with an error if the same tuple value occurs in two
   columns of the first row.
-----------------------------------------------------------------------------*/
    tuplehash hash;
    unsigned int col;

    hash = pnm_createtuplehash();

    for (col = 0; col < lookuppamP->width; ++col) {
        tuple const thisValue = lookup[0][col];
        
        int found;
        int priorValue;

        pnm_lookuptuple(lookuppamP, hash, thisValue, &found, &priorValue);

        if (found)
            pm_error("Same tuple value occurs in both Column %u and "
                     "Column %u of the lookup image", priorValue, col);
        else {
            int fits;
            pnm_addtotuplehash(lookuppamP, hash, lookup[0][col], col, &fits);

            if (!fits)
                pm_error("Out of memory constructing hash of lookup table");
        }
    }

    *hashP = hash;
}



static void
doUnlookup(struct pam * const inpamP,
           tuplehash    const lookupHash,
           sample       const maxIndex,
           FILE *       const ofP) {

    struct pam outpam;
    unsigned int row;
    tuple * inrow;
    tuple * outrow;

    inrow = pnm_allocpamrow(inpamP);

    outpam.size = sizeof(outpam);
    outpam.len = PAM_STRUCT_SIZE(tuple_type);
    outpam.file = ofP;
    outpam.format = PAM_FORMAT;
    outpam.height = inpamP->height;
    outpam.width = inpamP->width;
    outpam.depth = 1;
    outpam.maxval = maxIndex + 1;  /* +1 for missing color */
    strcpy(outpam.tuple_type, "INDEX");

    pnm_writepaminit(&outpam);

    outrow = pnm_allocpamrow(&outpam);

    for (row = 0; row < inpamP->height; ++row) {
        unsigned int col;
        
        pnm_readpamrow(inpamP, inrow);

        for (col = 0; col < inpamP->width; ++col) {
            int found;
            int index;
            pnm_lookuptuple(inpamP, lookupHash, inrow[col], &found, &index);

            if (found) {
                assert(index <= outpam.maxval);
                outrow[col][0] = index;
            } else
                outrow[col][0] = maxIndex + 1;
        }
        pnm_writepamrow(&outpam, outrow);
    }

    pnm_freepamrow(outrow);
    pnm_freepamrow(inrow);
}



int
main(int argc, const char ** const argv) {

    struct CmdlineInfo cmdline;
    struct pam inpam;
    FILE * ifP;
    struct pam lookuppam;
    tuple ** lookup;

    tuplehash lookupHash;
    
    pm_proginit(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    ifP = pm_openr(cmdline.inputFileName);

    pnm_readpaminit(ifP, &inpam, PAM_STRUCT_SIZE(tuple_type));

    getLookup(cmdline.lookupfile, &lookup, &lookuppam);

    if (inpam.depth != lookuppam.depth)
        pm_error("The lookup image has depth %u, but the input image "
                 "has depth %u.  They must be the same",
                 lookuppam.depth, inpam.depth);
    if (!streq(inpam.tuple_type, lookuppam.tuple_type))
        pm_error("The lookup image has tupel type '%s', "
                 "but the input image "
                 "has tuple type '%s'.  They must be the same",
                 lookuppam.tuple_type, inpam.tuple_type);

    makeReverseLookupHash(&lookuppam, lookup, &lookupHash);

    doUnlookup(&inpam, lookupHash, lookuppam.width-1, stdout);

    pm_close(ifP);

    pnm_destroytuplehash(lookupHash);
    pnm_freepamarray(lookup, &lookuppam);
    
    return 0;
}


