/*=============================================================================
                               pamtopam
===============================================================================
  Part of the Netpbm package.

  Copy PAM and PNM (i.e. PBM, PGM, or PPM) images from Standard Input
  to Standard Output (while converting PNM images to PAM)

  By Paul Bolle October 2007.

  Contributed to the public domain by its author.
=============================================================================*/

#include "pm_c_util.h"
#include "pam.h"

int
main(int argc, const char * argv[]) {

    int        eof;     /* no more images in input stream */
    struct pam inpam;   /* Input PAM image */
    struct pam outpam;  /* Output PAM image */

    pm_proginit(&argc, argv);

    if (argc-1 != 0)
        pm_error("Program takes no arguments.  Input is from Standard Input");

    eof = FALSE;
    while (!eof) {
        pnm_readpaminit(stdin, &inpam, PAM_STRUCT_SIZE(tuple_type));

        outpam = inpam;
        outpam.file = stdout;
        outpam.format = PAM_FORMAT;

        pnm_writepaminit(&outpam);

        {
            tuple * tuplerow;

            tuplerow = pnm_allocpamrow(&inpam);
            {
                unsigned int row;

                for (row = 0; row < inpam.height; ++row) {
                    pnm_readpamrow(&inpam, tuplerow);
                    pnm_writepamrow(&outpam, tuplerow);
                }
            }
            pnm_freepamrow(tuplerow);
        }
        pnm_nextimage(stdin, &eof);
    }

    return 0;
}
