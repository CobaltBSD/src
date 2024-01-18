/***************************************************************************
                                pbmpage

  This program produces a printed page test pattern in PBM format.

  This was adapted from Tim Norman's 'pbmtpg' program, part of his
  'pbm2ppa' package, by Bryan Henderson on 2000.05.01.  The only
  change was to make it use the Netpbm libraries to generate the
  output.

  For copyright and licensing information, see the pbmtoppa program,
  which was also derived from the same package.
****************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

#include "pm_c_util.h"
#include "pbm.h"

/* US is 8.5 in by 11 in */

#define USWIDTH  (5100)
#define USHEIGHT (6600)

/* A4 is 210 mm by 297 mm == 8.27 in by 11.69 in */

#define A4WIDTH  (4960)
#define A4HEIGHT (7016)


struct bitmap {
    unsigned int Width;      /* width and height in 600ths of an inch */
    unsigned int Height;
    bit ** bitmap;
};

static struct bitmap bitmap;



static void
setpixel(unsigned int const x,
         unsigned int const y,
         unsigned int const c) {

    char const bitmask = 128 >> (x % 8);

    if (x < 0 || x >= bitmap.Width)
        return;
    if (y < 0 || y >= bitmap.Height)
        return;

    if (c)
        bitmap.bitmap[y][x/8] |= bitmask;
    else
        bitmap.bitmap[y][x/8] &= ~bitmask;
}



static void 
setplus(unsigned int const x,
        unsigned int const y,
        unsigned int const s) {
/*----------------------------------------------------------------------------
   Draw a black plus sign centered at (x,y) with arms 's' pixels long.  
   Leave the exact center of the plus white.
-----------------------------------------------------------------------------*/
    unsigned int i;

    for (i = 0; i < s; ++i) {
        setpixel(x+i, y,   1);
        setpixel(x-i, y,   1);
        setpixel(x,   y+i, 1);
        setpixel(x,   y-i, 1);
    }
}



static void 
setblock(unsigned int const x,
         unsigned int const y,
         unsigned int const s) {

    unsigned int i;

    for (i = 0; i < s; ++i) {
        unsigned int j;

        for (j = 0; j < s; ++j)
            setpixel(x+i, y+j, 1);
    }
}



static void 
setchar(unsigned int const x,
        unsigned int const y,
        char         const c) {

    static char const charmap[10][5]= { { 0x3e, 0x41, 0x41, 0x41, 0x3e },
                                        { 0x00, 0x42, 0x7f, 0x40, 0x00 },
                                        { 0x42, 0x61, 0x51, 0x49, 0x46 },
                                        { 0x22, 0x41, 0x49, 0x49, 0x36 },
                                        { 0x18, 0x14, 0x12, 0x7f, 0x10 },
                                        { 0x27, 0x45, 0x45, 0x45, 0x39 },
                                        { 0x3e, 0x49, 0x49, 0x49, 0x32 },
                                        { 0x01, 0x01, 0x61, 0x19, 0x07 },
                                        { 0x36, 0x49, 0x49, 0x49, 0x36 },
                                        { 0x26, 0x49, 0x49, 0x49, 0x3e } };
    
    if (c <= '9' && c >= '0') {
        unsigned int xo;

        for (xo = 0; xo < 5; ++xo) {
            unsigned int yo;

            for (yo = 0; yo < 8; ++yo) {
                if ((charmap[c-'0'][xo] >> yo) & 0x01)
                    setblock(x + xo*3, y + yo*3, 3);
            }
        }
    }
}



static void 
setstring(unsigned int const x,
          unsigned int const y,
          const char * const s) {

    const char * p;
    unsigned int xo;

    for (xo = 0, p = s; *p; xo += 21, ++p)
        setchar(x + xo, y, *p);
}



static void 
setCG(unsigned int const x,
      unsigned int const y) {

    unsigned int xo;

    for (xo = 0; xo <= 50; ++xo)   {
        unsigned int const yo = sqrt(SQR(50.0) - SQR(xo));

        unsigned int zo;

        setpixel(x + xo, y + yo, 1);
        setpixel(x+yo,   y + xo, 1);
        setpixel(x-1-xo, y-1-yo, 1);
        setpixel(x-1-yo, y-1-xo, 1);
        setpixel(x+xo,   y-1-yo, 1);
        setpixel(x-1-xo, y+yo,   1);

        for(zo = 0; zo < yo; ++zo) {
            setpixel(x + xo, y-1-zo, 1);
            setpixel(x-1-xo, y+zo,   1);
        }
    }
}



static void
outputPbm(FILE *        const ofP,
          struct bitmap const bitmap) {
/*----------------------------------------------------------------------------
  Create a pbm file containing the image from the global variable bitmap[].
-----------------------------------------------------------------------------*/
    int const forceplain = 0;

    unsigned int row;
    
    pbm_writepbminit(ofP, bitmap.Width, bitmap.Height, forceplain);
    
    for (row = 0; row < bitmap.Height; ++row) {
        pbm_writepbmrow_packed(ofP, bitmap.bitmap[row],
                               bitmap.Width, forceplain); 
    }
}



static void
framePerimeter(unsigned int const Width, 
               unsigned int const Height) {

    unsigned int x, y;

    /* Top edge */
    for (x = 0; x < Width; ++x)
        setpixel(x, 0, 1);

    /* Bottom edge */
    for (x = 0; x < Width; ++x)
        setpixel(x, Height-1, 1);

    /* Left edge */
    for (y = 0; y < Height; ++y)
        setpixel(0, y, 1);

    /* Right edge */
    for (y = 0; y < Height; ++y)
        setpixel(Width-1, y, 1);
}



int 
main(int argc, const char** argv) {

    int TP;
    unsigned int x, y;
    char buf[128];
    /* width and height in 600ths of an inch */
    unsigned int Width;
    unsigned int Height;

    pm_proginit(&argc, argv);

    if (argc > 1 && strcmp(argv[1], "-a4") == 0) {
        Width  = A4WIDTH;
        Height = A4HEIGHT;
        --argc;
        ++argv;
    } else {
        Width  = USWIDTH;
        Height = USHEIGHT;
    }

    if (argc > 1)
        TP = atoi(argv[1]);
    else
        TP = 1;

    bitmap.Width  = Width;
    bitmap.Height = Height;
    bitmap.bitmap = pbm_allocarray_packed(Width, bitmap.Height);

    for (y = 0; y < bitmap.Height; ++y) {
        unsigned int x;
        for (x = 0; x < pbm_packed_bytes(bitmap.Width); ++x) 
            bitmap.bitmap[y][x] = 0x00; 
    }

    switch (TP) {
    case 1:
        framePerimeter(Width, Height);
        for (x = 0; x < Width; x += 100) {
            unsigned int y;
            for(y = 0; y < Height; y += 100)
                setplus(x, y, 4);
        }
        for(x = 0; x < Width; x += 100) {
            sprintf(buf,"%d", x);
            setstring(x + 3, (Height/200) * 100 + 3, buf);
        }
        for (y = 0; y < Height; y += 100) {
            sprintf(buf, "%d", y);
            setstring((Width/200) * 100 + 3, y + 3, buf);
        }
        for (x = 0; x < Width; x += 10)
            for (y = 0; y < Height; y += 100)
                setplus(x, y, ((x%100) == 50) ? 2 : 1);
        for (x = 0; x < Width; x += 100) {
            unsigned int y;
            for (y = 0; y < Height; y += 10)
                setplus(x, y, ((y%100) == 50) ? 2 : 1);
        }
        setCG(Width/2, Height/2);
        break;
    case 2:
        for (y = 0; y < 300; ++y)
            setpixel(Width/2, Height/2-y, 1);
        break;
    case 3:
        for (y = 0; y < 300; ++y) {
            setpixel(y, y, 1);
            setpixel(Width-1-y, Height-1-y, 1);
        }
        break;
    default:
        pm_error("unknown test pattern (%d)", TP);
    }

    outputPbm(stdout, bitmap);

    pbm_freearray(bitmap.bitmap, Height);

    pm_close(stdout);

    return 0;
}
