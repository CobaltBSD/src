/*=============================================================================
                               pamvalidate
===============================================================================
  Part of the Netpbm package.

  Copy PAM and PNM (i.e. PBM, PGM, or PPM) images from Standard Input
  to Standard Output.  No output when input is invalid.

  Contributed to the public domain by its author.
=============================================================================*/

#include <string.h>
#include "pm_c_util.h"
#include "pam.h"



int
main(int argc, const char * argv[]) {

    FILE * const tmpfile = pm_tmpfile();
    int        eof;     /* no more images in input stream */
    struct pam inpam;   /* Input PAM image */
    struct pam outpam;  /* Output PAM image */

    pm_proginit(&argc, argv);

    if (argc-1 != 0)
        pm_error("Program takes no arguments.  Input is from Standard Input");

    for (eof = FALSE; !eof; ) {
        pnm_readpaminit(stdin, &inpam, PAM_STRUCT_SIZE(tuple_type));

        outpam = inpam;  /* initial value */
        outpam.file = tmpfile;

        pnm_writepaminit(&outpam);

        if (PNM_FORMAT_TYPE(inpam.format) == PBM_TYPE) {
            /* Fast method for PBM */
            unsigned char * const inrow = pbm_allocrow_packed(inpam.width);

            unsigned int row;

            for (row = 0; row < inpam.height; ++row) {
                pbm_readpbmrow_packed(inpam.file, inrow, inpam.width,
                                      inpam.format);
                pbm_writepbmrow_packed(tmpfile, inrow, inpam.width, 0);
            }
            pbm_freerow(inrow);

        } else {
            /* General case.  Logic works for PBM */
            tuple * const tuplerow = pnm_allocpamrow(&inpam);

            unsigned int row;

            for (row = 0; row < inpam.height; ++row) {
                pnm_readpamrow(&inpam, tuplerow);
                pnm_writepamrow(&outpam, tuplerow);
            }
            pnm_freepamrow(tuplerow);
        }
        pnm_nextimage(stdin, &eof);
    }

    fseek(tmpfile, 0, SEEK_SET);

    while (!feof(tmpfile) && !ferror(tmpfile) && !ferror(stdout)) {
        char buffer[4096];
        size_t bytesReadCt;

        bytesReadCt = fread(buffer, 1, sizeof(buffer), tmpfile);

        if (ferror(tmpfile))
            pm_error("Error reading from temporary file.  "
                     "Incomplete output.  "    
                     "Errno = %s (%d)", strerror(errno), errno);
        else
            fwrite(buffer, 1, bytesReadCt, stdout);
    }
    pm_close(tmpfile);
    pm_close(stdout);

    return 0;
}
