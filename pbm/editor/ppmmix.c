/*********************************************************************/
/* ppmmix -  mix together two pictures like with a fader             */
/* Frank Neumann, October 1993                                       */
/* V1.2 16.11.1993                                                   */
/*                                                                   */
/*********************************************************************/

#include "ppm.h"

int main(int argc, const char ** argv) {

    FILE * if1P;
    FILE * if2P;
    int argn;
    int rows1, cols1, format1;
    unsigned int row;
    int rows2, cols2, format2;
    pixel *srcrow1, *srcrow2, *destrow;
    pixval maxval1, maxval2;
    double fadefactor;
    long longfactor;
    const char * const usage = "fadefactor ppmfile1 ppmfile2\n        fadefactor: 0.0 = only ppmfile1, 1.0 = only ppmfile2\n";

    /* parse in 'default' parameters */
    pm_proginit(&argc, argv);

    argn = 1;

    /* parse in dim factor */
    if (argn == argc)
        pm_usage(usage);
    if (sscanf(argv[argn], "%lf", &fadefactor) != 1)
        pm_usage(usage);
    if (fadefactor < 0.0 || fadefactor > 1.0)
        pm_error("fade factor must be in the range from 0.0 to 1.0 ");
    ++argn;

    if (argn == argc-2) {
        if1P = pm_openr(argv[argn]);
        ++argn;
        if2P = pm_openr(argv[argn]);
    } else
        pm_usage(usage);

    ppm_readppminit(if1P, &cols1, &rows1, &maxval1, &format1);
    ppm_readppminit(if2P, &cols2, &rows2, &maxval2, &format2);

    if ((cols1 != cols2) || (rows1 != rows2))
        pm_error("image sizes are different!");

    if (maxval1 != maxval2)
        pm_error("images have different maxvalues");

    srcrow1 = ppm_allocrow(cols1);
    srcrow2 = ppm_allocrow(cols2);

    longfactor = (long)(fadefactor * 65536);

    destrow = ppm_allocrow(cols1);

    ppm_writeppminit(stdout, cols1, rows1, maxval1, 0);

    for (row = 0; row < rows1; ++row) {
        unsigned int col;
        ppm_readppmrow(if1P, srcrow1, cols1, maxval1, format1);
        ppm_readppmrow(if2P, srcrow2, cols2, maxval2, format2);

        for (col = 0; col < cols1; ++col) {
            pixel const p1 = srcrow1[col];
            pixval const r1 = PPM_GETR(p1);
            pixval const g1 = PPM_GETG(p1);
            pixval const b1 = PPM_GETB(p1);

            pixel const p2 = srcrow2[col];
            pixval const r2 = PPM_GETR(p2);
            pixval const g2 = PPM_GETG(p2);
            pixval const b2 = PPM_GETB(p2);

            pixval const r = r1 + (((r2 - r1) * longfactor) >> 16);
            pixval const g = g1 + (((g2 - g1) * longfactor) >> 16);
            pixval const b = b1 + (((b2 - b1) * longfactor) >> 16);

            PPM_ASSIGN(destrow[col], r, g, b);
        }

        ppm_writeppmrow(stdout, destrow, cols1, maxval1, 0);
    }

    pm_close(if1P);
    pm_close(if2P);
    ppm_freerow(srcrow1);
    ppm_freerow(srcrow2);
    ppm_freerow(destrow);

    return 0;
}
