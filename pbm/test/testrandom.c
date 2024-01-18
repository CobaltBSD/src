/*=============================================================================
                                   testrandom
===============================================================================
  Test for the random number generator type by generating 5 values with rand()
  and comparing them against values in a table.

  Currently only recognizes ISO glibc rand().

  Options:
    -q : quiet mode
    -v : verbose mode : Use to generate values for new table 

  This is a self-contained program which does not require any libnetpbm
  functions.
=============================================================================*/
#include <stdio.h>
#include <stdlib.h>

/* Exit values */
#define EXIT_ERROR 1
#define EXIT_UNKNOWN 80
#define ISO_GLIBC 81
/* 82-90: reserved */

typedef enum {QUIET=0, NORMAL=1, VERBOSE=2} VerbosityLevel;

/* On some Sun systems RAND_MAX is not defined */
#ifndef RAND_MAX
#define RAND_MAX 0
#endif

#define SEED 3791

static struct { 
    int          const type;
        /* Exit value for this rand() function  */
    int          const randMax;
        /* Usually 0x7fffffff, sometimes 0x7fff */
        /* Other values are possible; 0 means undefined */
    unsigned int const res[5];
        /* Sample values returned from our tests */
    const char * const name;
        /* Name for this rand() function */
} rTable[2] = {
    { ISO_GLIBC,  /* glibc rand() */ 
      0x7fffffff, /* 31 bits */ 
      { 217313873, 969144303, 1757357552, 1096307597, 818311031 },
      "ISO C glibc rand() or equivalent" },
    
    /* Insert additional entries here */
    
    { 0,   /* terminating code */
      0,
      {0, 0, 0, 0, 0}, NULL  /* unknown type */}
};



static void
parseCommandLine(int              const argc,
                 const char *     const argv[],
                 VerbosityLevel * const verbosityP) {

    *verbosityP = NORMAL; /* Initial value */

    if (argc == 2) {
        if (argv[1][0] == '-' && argv[1][2] == '\0') {
            switch ( argv[1][1] ) {
            case 'v' : *verbosityP = VERBOSE; break;
            case 'q' : *verbosityP = QUIET  ; break;
            default :  fprintf (stderr,
                                "Error: Unrecognized argument: %s\n", argv[1]);
                exit (EXIT_ERROR);
            }
        } 
    }
    if (argc > 2 ) {
        fprintf (stderr, "Error: Too many arguments.\n");
        exit (EXIT_ERROR);
    }
}



int
main(int const argc, const char * const argv[]) {

    unsigned int i;
    unsigned int res[5];
    VerbosityLevel verbosity;

    parseCommandLine(argc, argv, &verbosity);

    if (verbosity == VERBOSE) {
        if (RAND_MAX > 0)
            fprintf(stderr, "RAND_MAX = 0x%x (%d)\n", RAND_MAX, RAND_MAX);
        else
            fprintf(stderr, "RAND_MAX is undefined\n");
    }

    /* Set seed for pseudo-random number generator */
    if (verbosity == VERBOSE)
        fprintf(stderr, "Generating samples. Seed=%u\n", SEED);

    srand(SEED);

    /*  Generate five samples and store in array res[] */
    for (i = 0; i < 5; ++i) {
        res[i] = rand();
        if (verbosity == VERBOSE)
            fprintf (stderr, "%d\n",res[i]);
    }

    /*  Look for a match in table */
    for (i = 0; rTable[i].type != 0; ++i) {
        if (rTable[i].randMax == RAND_MAX && rTable[i].res[0] == res[0] &&
            rTable[i].res[1] == res[1] &&    rTable[i].res[2] == res[2] &&
            rTable[i].res[3] == res[3] &&    rTable[i].res[4] == res[4]) {
            if (verbosity != QUIET)
                fprintf(stderr,
                        "Random number generator is %s.\n", rTable[i].name);

            exit(rTable[i].type);
        }
    }
    /* No matches */
    if (verbosity != QUIET)   
        fprintf(stderr, "Random number generator is of unknown type.\n");
    exit(EXIT_UNKNOWN);
}



