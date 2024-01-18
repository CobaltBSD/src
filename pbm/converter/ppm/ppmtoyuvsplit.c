/* ppmtoyuvsplit.c - convert a portable pixmap into 3 raw files:
** - basename.Y : The Luminance chunk at the size of the Image
** - basename.U : The Chrominance chunk U at 1/4
** - basename.V : The Chrominance chunk V at 1/4
** The subsampled U and V values are made by arithmetic mean.
**
** The produced YUV triples are scaled again
** to fit into the smaller range of values for this standard.
**
** by A.Beck
** Internet: Andre_Beck@IRS.Inf.TU-Dresden.de
**
** Based on ppmtoyuv.c
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
*/

/* ALPHA Kludge by Franky */

#ifdef __alpha
#define myLONG int
#else
#define myLONG long
#endif

#include <string.h>
#include "nstring.h"
#include "ppm.h"



struct FileNameSet {
    const char * u;
    const char * v;
    const char * y;
};



static void
makeOutputFileName(const char *         const baseName,
                   struct FileNameSet * const fnameP) {

    pm_asprintf(&fnameP->u, "%s.U", baseName);
    pm_asprintf(&fnameP->v, "%s.V", baseName);
    pm_asprintf(&fnameP->y, "%s.Y", baseName);
}



static void
termFileNameSet(struct FileNameSet const fname) {

    pm_strfree(fname.u);
    pm_strfree(fname.v);
    pm_strfree(fname.y);
}



int
main(int argc, const char ** argv) {

    FILE * ifP;
    FILE *vf, *uf, *yf;
    pixel *pixelrow1, *pixelrow2;
    int rows, cols;
    int format;
    unsigned int row;
    pixval maxval;
    unsigned char *y1buf, *y2buf, *ubuf, *vbuf;
    struct FileNameSet fname;
        /* Output file names - .U, .V, .Y */

    pm_proginit(&argc, argv);

    if ((argc-1 > 2) || (argc-1 < 1))
        pm_error("Wrong number of arguments: %u.  "
                 "Arguments are basename for output files "
                 "and optional input file name", argc-1);

    if (argc-1 == 2)
        ifP = pm_openr(argv[2]);
    else
        ifP = stdin;

    makeOutputFileName(argv[1], &fname);

    uf = pm_openw(fname.u);
    vf = pm_openw(fname.v);
    yf = pm_openw(fname.y);

    termFileNameSet(fname);

    ppm_readppminit(ifP, &cols, &rows, &maxval, &format);

    if (cols % 2 == 1)
        pm_message("Warning: odd columns count %u, excess ignored", cols);

    if (rows % 2 == 1)
        pm_message("Warning: odd rows count %u, excess ignored", rows);

    pixelrow1 = ((pixel*) pm_allocrow(cols, sizeof(pixel)));
    pixelrow2 = ((pixel*) pm_allocrow(cols, sizeof(pixel)));

    y1buf = (unsigned char *) pm_allocrow(cols, 1);
    y2buf = (unsigned char *) pm_allocrow(cols, 1);
    ubuf = (unsigned char *) pm_allocrow(cols, 1);
    vbuf = (unsigned char *) pm_allocrow(cols, 1);

    for (row = 0; row < (rows & ~1); row += 2) {
        unsigned char *y1ptr, *y2ptr, *uptr, *vptr;
        pixel *pP1, *pP2;
        unsigned int col;

        ppm_readppmrow(ifP, pixelrow1, cols, maxval, format);
        ppm_readppmrow(ifP, pixelrow2, cols, maxval, format);

        pP1 = &pixelrow1[0]; pP2 = &pixelrow2[0];
        y1ptr = y1buf; y2ptr = y2buf; vptr = vbuf; uptr = ubuf;

        for (col = 0 ; col < (cols & ~1); col += 2) {
            pixval r0,g0,b0,r1,g1,b1,r2,g2,b2,r3,g3,b3;
            myLONG u, v, y0, y1, y2, y3, u0, u1, u2, u3, v0, v1, v2, v3;

            /* first pixel */
            r0 = PPM_GETR(*pP1);
            g0 = PPM_GETG(*pP1);
            b0 = PPM_GETB(*pP1);
            pP1++;
            /* 2nd pixel */
            r1 = PPM_GETR(*pP1);
            g1 = PPM_GETG(*pP1);
            b1 = PPM_GETB(*pP1);
            pP1++;
            /* 3rd pixel */
            r2 = PPM_GETR(*pP2);
            g2 = PPM_GETG(*pP2);
            b2 = PPM_GETB(*pP2);
            pP2++;
            /* 4th pixel */
            r3 = PPM_GETR(*pP2);
            g3 = PPM_GETG(*pP2);
            b3 = PPM_GETB(*pP2);
            pP2++;


            /* The JFIF RGB to YUV Matrix for $00010000 = 1.0

               [Y]   [19595   38469    7471][R]
               [U] = [-11056  -21712  32768][G]
               [V]   [32768   -27440  -5328][B]

            */

            y0 =  19595 * r0 + 38469 * g0 +  7471 * b0;
            u0 = -11056 * r0 - 21712 * g0 + 32768 * b0;
            v0 =  32768 * r0 - 27440 * g0 -  5328 * b0;

            y1 =  19595 * r1 + 38469 * g1 +  7471 * b1;
            u1 = -11056 * r1 - 21712 * g1 + 32768 * b1;
            v1 =  32768 * r1 - 27440 * g1 -  5328 * b1;

            y2 =  19595 * r2 + 38469 * g2 +  7471 * b2;
            u2 = -11056 * r2 - 21712 * g2 + 32768 * b2;
            v2 =  32768 * r2 - 27440 * g2 -  5328 * b2;

            y3 =  19595 * r3 + 38469 * g3 +  7471 * b3;
            u3 = -11056 * r3 - 21712 * g3 + 32768 * b3;
            v3 =  32768 * r3 - 27440 * g3 -  5328 * b3;

            /* mean the chroma for subsampling */

            u  = (u0+u1+u2+u3)>>2;
            v  = (v0+v1+v2+v3)>>2;

            y0 = (y0 * 219)/255 + 1048576;
            y1 = (y1 * 219)/255 + 1048576;
            y2 = (y2 * 219)/255 + 1048576;
            y3 = (y3 * 219)/255 + 1048576;

            u  = (u * 224)/255 ;
            v  = (v * 224)/255 ;

            *y1ptr++  = (y0 >> 16) ;
            *y1ptr++  = (y1 >> 16) ;
            *y2ptr++  = (y2 >> 16) ;
            *y2ptr++  = (y3 >> 16) ;


            *uptr++   = (u >> 16)+128 ;
            *vptr++   = (v >> 16)+128 ;

        }
        fwrite(y1buf, (cols & ~1), 1, yf);
        fwrite(y2buf, (cols & ~1), 1, yf);
        fwrite(ubuf, cols/2, 1, uf);
        fwrite(vbuf, cols/2, 1, vf);
    }

    pm_close(ifP);
    fclose(yf);
    fclose(uf);
    fclose(vf);
    return 0;
}
