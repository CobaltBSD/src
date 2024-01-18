
/*********************************************************************/
/* ppmshift -  shift lines of a picture left or right by x pixels    */
/* Frank Neumann, October 1993                                       */
/* V1.1 16.11.1993                                                   */
/*                                                                   */
/* version history:                                                  */
/* V1.0    11.10.1993  first version                                 */
/* V1.1    16.11.1993  Rewritten to be NetPBM.programming conforming */
/*********************************************************************/

#include "ppm.h"

/**************************/
/* start of main function */
/**************************/
int
main(int    argc,
     char * argv[]) {

    FILE * ifP;
    unsigned int row;
    int argn, rows, cols, format;
    pixel * srcrow;
    pixel * destrow;
    pixval maxval;
    int shift, nowshift;
    int shiftArg;

    const char * const usage = "shift [ppmfile]\n        shift: maximum number of pixels to shift a line by\n";

    /* parse in 'default' parameters */
    ppm_init(&argc, argv);

    argn = 1;

    /* parse in shift number */
    if (argn == argc)
        pm_usage(usage);
    if (sscanf(argv[argn], "%d", &shiftArg) != 1)
        pm_usage(usage);
    if (shiftArg < 0)
        pm_error("shift factor must be 0 or more");
    ++argn;

    /* parse in filename (if present, stdin otherwise) */
    if (argn != argc)
    {
        ifP = pm_openr(argv[argn]);
        ++argn;
    }
    else
        ifP = stdin;

    if (argn != argc)
        pm_usage(usage);

    /* read first data from file */
    ppm_readppminit(ifP, &cols, &rows, &maxval, &format);

    if (shiftArg > cols) {
        shift = cols;
        pm_message("shift amount is larger than picture width - reset to %d",
                   shift);
    } else
        shift = shiftArg;

    srcrow = ppm_allocrow(cols);

    destrow = ppm_allocrow(cols);

    ppm_writeppminit(stdout, cols, rows, maxval, 0);

    srand(pm_randseed());

    /** now do the shifting **/
    /* the range by which a line is shifted lays in the range from */
    /* -shift/2 .. +shift/2 pixels; however, within this range it is */
    /* randomly chosen */
    for (row = 0; row < rows; ++row) {
        pixel * pP;
        pixel * pP2;

        if (shift != 0)
            nowshift = (rand() % (shift+1)) - ((shift+1) / 2);
        else
            nowshift = 0;

        ppm_readppmrow(ifP, srcrow, cols, maxval, format);

        pP  = &srcrow[0];
        pP2 = &destrow[0];

        /* if the shift value is less than zero, we take the original
           pixel line and copy it into the destination line translated
           to the left by x pixels. The empty pixels on the right end
           of the destination line are filled up with the pixel that
           is the right-most in the original pixel line.
        */
        if (nowshift < 0) {
            unsigned int col;
            pP += abs(nowshift);
            for (col = 0; col < cols; ++col) {
                PPM_ASSIGN(*pP2, PPM_GETR(*pP), PPM_GETG(*pP), PPM_GETB(*pP));
                ++pP2;
                if (col < (cols + nowshift) - 1)
                    ++pP;
            }
        } else {
            unsigned int col;
            /* The shift value is 0 or positive, so fill the first
               <nowshift> pixels of the destination line with the
               first pixel from the source line, and copy the rest of
               the source line to the dest line
            */
            for (col = 0; col < cols; ++col) {
                PPM_ASSIGN(*pP2, PPM_GETR(*pP), PPM_GETG(*pP), PPM_GETB(*pP));
                ++pP2;
                if (col >= nowshift)
                    ++pP;
            }
        }

        ppm_writeppmrow(stdout, destrow, cols, maxval, 0);
    }

    pm_close(ifP);
    ppm_freerow(srcrow);
    ppm_freerow(destrow);

    return 0;
}
