#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <pbm/util/pm_c_util.h>
#include <pbm/util/shhopt.h>
#include <pbm/util/mallocvar.h>
#include <pbm/pam.h>



struct CmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    unsigned int width;
    unsigned int height;
    unsigned int maxval;
    float sigma;
    const char * tupletype;
};



static void
parseCommandLine(int argc, const char ** argv,
                 struct CmdlineInfo * const cmdlineP) {
/*----------------------------------------------------------------------------
  Convert program invocation arguments (argc,argv) into a format the 
  program can use easily, struct cmdlineInfo.  Validate arguments along
  the way and exit program with message if invalid.

  Note that some string information we return as *cmdlineP is in the storage 
  argv[] points to.
-----------------------------------------------------------------------------*/
    optEntry *option_def;
        /* Instructions to OptParseOptions2 on how to parse our options.
         */
    optStruct3 opt;

    unsigned int tupletypeSpec, maxvalSpec, sigmaSpec;
    unsigned int option_def_index;

    MALLOCARRAY_NOFAIL(option_def, 100);

    option_def_index = 0;   /* incremented by OPTENTRY */
    OPTENT3(0,   "tupletype",  OPT_STRING, &cmdlineP->tupletype, 
            &tupletypeSpec,     0);
    OPTENT3(0,   "maxval",     OPT_UINT,   &cmdlineP->maxval, 
            &maxvalSpec,        0);
    OPTENT3(0,   "sigma",      OPT_FLOAT,  &cmdlineP->sigma, 
            &sigmaSpec,        0);

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = FALSE;  /* We have no parms that are negative numbers */

    pm_optParseOptions3(&argc, (char **)argv, opt, sizeof(opt), 0);
        /* Uses and sets argc, argv, and some of *cmdlineP and others. */

    if (!tupletypeSpec)
        cmdlineP->tupletype = "";
    else {
        struct pam pam;
        if (strlen(cmdlineP->tupletype)+1 > sizeof(pam.tuple_type))
            pm_error("The tuple type you specified is too long.  "
                     "Maximum %u characters.",
                     (unsigned)sizeof(pam.tuple_type)-1);
    }        

    if (!sigmaSpec)
        pm_error("You must specify the -sigma option.");
    else if (cmdlineP->sigma <= 0.0)
        pm_error("-sigma must be positive.  You specified %f", 
                 cmdlineP->sigma);

    if (!maxvalSpec)
        cmdlineP->maxval = PNM_MAXMAXVAL;
    else {
        if (cmdlineP->maxval > PNM_OVERALLMAXVAL)
            pm_error("The maxval you specified (%u) is too big.  "
                     "Maximum is %u", cmdlineP->maxval, PNM_OVERALLMAXVAL);
        if (cmdlineP->maxval < 1)
            pm_error("-maxval must be at least 1");
    }    

    if (argc-1 < 2)
        pm_error("Need two arguments: width and height.");
    else if (argc-1 > 2)
        pm_error("Only two arguments allowed: width and height.  "
                 "You specified %d", argc-1);
    else {
        cmdlineP->width = atoi(argv[1]);
        cmdlineP->height = atoi(argv[2]);
        if (cmdlineP->width <= 0)
            pm_error("width argument must be a positive number.  You "
                     "specified '%s'", argv[1]);
        if (cmdlineP->height <= 0)
            pm_error("height argument must be a positive number.  You "
                     "specified '%s'", argv[2]);
    }
    free(option_def);
}



static double
distFromCenter(struct pam * const pamP,
               int          const col,
               int          const row) {

    return sqrt(SQR(0.5 + col - (double)pamP->width/2) +
                SQR(0.5 + row - (double)pamP->height/2));
}



static double
gauss(double const arg,
      double const sigma) {
/*----------------------------------------------------------------------------
   Compute the value of the gaussian function with sigma parameter 'sigma'
   and mu parameter zero of argument 'arg'.
-----------------------------------------------------------------------------*/
    double const pi = 3.14159;
    double const coefficient = 1 / (sigma * sqrt(2*pi));
    double const exponent = - SQR(arg-0) / (2 * SQR(sigma));

    return coefficient * exp(exponent);
}



static double
imageNormalizer(struct pam * const pamP,
                double       const sigma) {
/*----------------------------------------------------------------------------
   Compute the value that has to be multiplied by the value of the 
   one-dimensional gaussian function of the distance from center in
   order to get the value for a normalized two-dimensional gaussian
   function.  Normalized here means that the volume under the whole
   curve is 1, just as the area under a whole one-dimensional gaussian
   function is 1.
-----------------------------------------------------------------------------*/
    double volume;

    unsigned int row;

    volume = 0.0;   /* initial value */

    for (row = 0; row < pamP->height; ++row) {
        unsigned int col;
        for (col = 0; col < pamP->width; ++col)
            volume += gauss(distFromCenter(pamP, col, row), sigma);
    }
    return 1.0 / volume;
}



int
main(int argc, const char **argv) {

    struct CmdlineInfo cmdline;
    struct pam pam;
    int row;
    double normalizer;
    tuplen * tuplerown;
    
    pm_proginit(&argc, argv);
   
    parseCommandLine(argc, argv, &cmdline);

    pam.size        = sizeof(pam);
    pam.len         = PAM_STRUCT_SIZE(tuple_type);
    pam.file        = stdout;
    pam.format      = PAM_FORMAT;
    pam.plainformat = 0;
    pam.width       = cmdline.width;
    pam.height      = cmdline.height;
    pam.depth       = 1;
    pam.maxval      = cmdline.maxval;
    strcpy(pam.tuple_type, cmdline.tupletype);

    normalizer = imageNormalizer(&pam, cmdline.sigma);
    
    pnm_writepaminit(&pam);
   
    tuplerown = pnm_allocpamrown(&pam);

    for (row = 0; row < pam.height; ++row) {
        int col;
        for (col = 0; col < pam.width; ++col) {
            double const gauss1 = gauss(distFromCenter(&pam, col, row),
                                        cmdline.sigma);

            tuplerown[col][0] = gauss1 * normalizer;
        }
        pnm_writepamrown(&pam, tuplerown);
    }
    
    pnm_freepamrown(tuplerown);

    return 0;
}
