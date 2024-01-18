/*********************************************************************
   pgmnoise -  create a PGM with white noise
   Frank Neumann, October 1993
*********************************************************************/

#include "pm_c_util.h"
#include "mallocvar.h"
#include "shhopt.h"
#include "pgm.h"
#include <assert.h>



struct cmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    unsigned int width;
    unsigned int height;
    unsigned int maxval;
    unsigned int randomseed;
    unsigned int randomseedSpec;
};



static void
parseCommandLine(int argc, const char ** const argv,
                 struct cmdlineInfo * const cmdlineP) {
/*----------------------------------------------------------------------------
   Note that the file spec array we return is stored in the storage that
   was passed to us as the argv array.
-----------------------------------------------------------------------------*/
    optEntry * option_def;
        /* Instructions to OptParseOptions3 on how to parse our options.
         */
    optStruct3 opt;
    unsigned int option_def_index;
    unsigned int maxvalSpec;

    MALLOCARRAY_NOFAIL(option_def, 100);

    option_def_index = 0;   /* incremented by OPTENT3 */
    OPTENT3(0,   "randomseed",   OPT_UINT,    &cmdlineP->randomseed,
            &cmdlineP->randomseedSpec,      0);
    OPTENT3(0,   "maxval",       OPT_UINT,    &cmdlineP->maxval,
            &maxvalSpec,                    0);

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = FALSE;  /* We may have parms that are negative numbers */

    pm_optParseOptions3(&argc, (char **)argv, opt, sizeof(opt), 0);
        /* Uses and sets argc, argv, and some of *cmdlineP and others. */
    free(option_def);

    if (maxvalSpec) {
        if (cmdlineP->maxval > PGM_OVERALLMAXVAL)
            pm_error("Maxval too large: %u.  Maximu is %u", 
                     cmdlineP->maxval, PGM_OVERALLMAXVAL);
        else if (cmdlineP->maxval == 0)
            pm_error("Maxval must not be zero");
    } else
        cmdlineP->maxval = PGM_MAXMAXVAL;

    if (argc-1 != 2)
        pm_error("Wrong number of arguments: %u.  "
                 "Arguments are width and height of image, in pixels",
                 argc-1);
    else {
        int const width  = atoi(argv[1]);
        int const height = atoi(argv[2]);
        
        if (width <= 0)
            pm_error("Width must be positive, not %d", width);
        else
            cmdlineP->width = width;

        if (height <= 0)
            pm_error("Height must be positive, not %d", width);
        else
            cmdlineP->height = height;
    }
}



static unsigned int
randPool(unsigned int const digits) {
/*----------------------------------------------------------------------------
  Draw 'digits' bits from pool of random bits.  If the number of random bits
  in pool is insufficient, call rand() and add 31 bits to it.
  
  'digits' must be at most 16.

  We assume that each call to rand() generates 31 bits, or RAND_MAX ==
  2147483647.
  
  The underlying logic is flexible and endian-free.  The above conditions
  can be relaxed.
-----------------------------------------------------------------------------*/
    static unsigned long int hold=0;  /* entropy pool */
    static unsigned int len=0;        /* number of valid bits in pool */

    unsigned int const mask = (1 << digits) - 1;

    unsigned int retval;

    assert(RAND_MAX == 2147483647 && digits <= 16);

    retval = hold;  /* initial value */

    if (len > digits) { /* Enough bits in hold to satisfy request */
        hold >>= digits;
        len   -= digits;
    } else {              /* Load another 31 bits into hold */
        hold    = rand(); 
        retval |= (hold << len);
        hold >>=  (digits - len);
        len = 31 - digits + len;
    }
    return (retval & mask);
}



static void
pgmnoise(FILE *       const ofP,
         unsigned int const cols,
         unsigned int const rows,
         gray         const maxval) {

    bool const usingPool = !(RAND_MAX==2147483647 && (maxval & (maxval+1)));
    unsigned int const bitLen = pm_maxvaltobits(maxval);

    unsigned int row;
    gray * destrow;

    /* If maxval is 2^n-1, we draw exactly n bits from the pool.
       Otherwise call rand() and determine gray value by modulo.

       In the latter case, there is a miniscule skew toward 0 (=black)
       because smaller numbers are produced more frequently by modulo.
       Thus we employ the pool method only when it is certain that no
       skew will ensue.

       To illustrate the point, consider converting the outcome of one
       roll of a fair, six-sided die to 5 values (0 to 4) by N % 5.  The
       probability for values 1, 2, 3, 4 are 1/6, but 0 alone is 2/6.
       Average is 10/6 or 1.6667, compared to 2.0 from an ideal
       generator which produces exactly 5 values.  With two dice
       average improves to 70/36 or 1.9444.

       The more (distinct) dice we roll, or the more binary digits we
       draw, the smaller the skew.
    */

    destrow = pgm_allocrow(cols);

    pgm_writepgminit(ofP, cols, rows, maxval, 0);

    for (row = 0; row < rows; ++row) {
        if (usingPool) {
            unsigned int col;
            for (col = 0; col < cols; ++col)
                destrow[col] = randPool(bitLen);
        } 
        else { 
            unsigned int col;
            for (col = 0; col < cols; ++col)
                destrow[col] = rand() % (maxval + 1); 
        }
        pgm_writepgmrow(ofP, destrow, cols, maxval, 0);
    }

    pgm_freerow(destrow);
}



int
main(int          argc,
     const char * argv[]) {
    
    struct cmdlineInfo cmdline;

    pm_proginit(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    srand(cmdline.randomseedSpec ? cmdline.randomseed : pm_randseed());

    pgmnoise(stdout, cmdline.width, cmdline.height, cmdline.maxval);

    return 0;
}
