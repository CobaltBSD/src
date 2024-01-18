/*********************************************************************/
/* ppmspread -  randomly displace a PPM's pixels by a certain amount */
/* Frank Neumann, October 1993                                       */
/* V1.1 16.11.1993                                                   */
/*                                                                   */
/* version history:                                                  */
/* V1.0 12.10.1993    first version                                  */
/* V1.1 16.11.1993    Rewritten to be NetPBM.programming conforming  */
/*********************************************************************/

#include <string.h>

#include "ppm.h"



int
main(int    argc,
     char * argv[]) {

    FILE * ifP;
    int argn, rows, cols;
    unsigned int row;
    pixel ** destarray, ** srcarray;
    pixel * pP;
    pixel * pP2;
    pixval maxval;
    pixval r1, g1, b1;
    int amount;
    const char * const usage = "amount [ppmfile]\n        amount: # of pixels to displace a pixel by at most\n";

    /* parse in 'default' parameters */
    ppm_init(&argc, argv);

    argn = 1;

    /* parse in amount & seed */
    if (argn == argc)
        pm_usage(usage);
    if (sscanf(argv[argn], "%d", &amount) != 1)
        pm_usage(usage);
    if (amount < 0)
        pm_error("amount should be a positive number");
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

    srcarray = ppm_readppm(ifP, &cols, &rows, &maxval);

    destarray = ppm_allocarray(cols, rows);

    /* clear out the buffer */
    for (row = 0; row < rows; ++row)
        memset(destarray[row], 0, cols * sizeof(pixel));

    srand(pm_randseed());

    /* start displacing pixels */
    for (row = 0; row < rows; ++row) {
        unsigned int col;
        pP = &srcarray[row][0];

        for (col = 0; col < cols; ++col) {
            int const xdis = (rand() % (amount+1)) - ((amount+1) / 2);
            int const ydis = (rand() % (amount+1)) - ((amount+1) / 2);

            int const xnew = col + xdis;
            int const ynew = row + ydis;

            /* only set the displaced pixel if it's within the bounds
               of the image
            */
            if (xnew >= 0 && xnew < cols && ynew >= 0 && ynew < rows) {
                /* displacing a pixel is accomplished by swapping it
                   with another pixel in its vicinity - so, first
                   store other pixel's RGB
                */
                pP2 = &srcarray[ynew][xnew];
                r1 = PPM_GETR(*pP2);
                g1 = PPM_GETG(*pP2);
                b1 = PPM_GETB(*pP2);
                /* set second pixel to new value */
                pP2 = &destarray[ynew][xnew];
                PPM_ASSIGN(*pP2, PPM_GETR(*pP), PPM_GETG(*pP), PPM_GETB(*pP));
                
                /* now, set first pixel to (old) value of second */
                pP2 = &destarray[row][col];
                PPM_ASSIGN(*pP2, r1, g1, b1);
            } else {
                /* displaced pixel is out of bounds; leave the old
                   pixel there
                */
                pP2 = &destarray[row][col];
                PPM_ASSIGN(*pP2, PPM_GETR(*pP), PPM_GETG(*pP), PPM_GETB(*pP));
            }
            ++pP;
        }
    }

    ppm_writeppm(stdout, destarray, cols, rows, maxval, 0);

    pm_close(ifP);
    ppm_freearray(srcarray, rows);
    ppm_freearray(destarray, rows);

    return 0;
}
