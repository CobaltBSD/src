/*
   Functions to allocate and deallocate structures and structure data
 
   By Jim Frost 1989.09.29, Bryan Henderson 2006.03.25.
 
   See COPYRIGHT file for copyright information.
*/

#include <assert.h>

#include <pbm/util/pm_c_util.h>
#include <pbm/util/mallocvar.h>
#include <pbm/util/nstring.h>
#include <pbm/pam.h>
#include "image.h"



/* this table is useful for quick conversions between depth and ncolors */

static unsigned long const DepthToColorsTable[] = {
  /*  0 */ 1,
  /*  1 */ 2,
  /*  2 */ 4,
  /*  3 */ 8,
  /*  4 */ 16,
  /*  5 */ 32,
  /*  6 */ 64,
  /*  7 */ 128,
  /*  8 */ 256,
  /*  9 */ 512,
  /* 10 */ 1024,
  /* 11 */ 2048,
  /* 12 */ 4096,
  /* 13 */ 8192,
  /* 14 */ 16384,
  /* 15 */ 32768,
  /* 16 */ 65536,
  /* 17 */ 131072,
  /* 18 */ 262144,
  /* 19 */ 524288,
  /* 20 */ 1048576,
  /* 21 */ 2097152,
  /* 22 */ 4194304,
  /* 23 */ 8388608,
  /* 24 */ 16777216,
  /* 25 */ 33554432,
  /* 26 */ 67108864,
  /* 27 */ 134217728,
  /* 28 */ 268435456,
  /* 29 */ 536870912,
  /* 30 */ 1073741824,
  /* 31 */ 2147483648u,
  /* 32 */ 2147483648u /* bigger than unsigned int; this is good enough */
};



unsigned int
depthToColors(unsigned int const depth) {
    return DepthToColorsTable[MIN(depth,32)];
}



unsigned long
colorsToDepth(unsigned long const ncolors) {

    unsigned long a;

    for (a = 0; (a < 32) && (DepthToColorsTable[a] < ncolors); ++a)
        /* EMPTY */
        ;
    return a ;
}



void
assertGoodImage(Image * const imageP) {

    assert(imageP != NULL);

    switch (imageP->type) {
    case IBITMAP:
    case IRGB:
    case ITRUE:
        break;
    default:
        assert(FALSE);  /* can't be */
    }
}



static void
newRGBMapData(RGBMap *     const rgbP,
              unsigned int const size) {

    rgbP->used = 0;
    rgbP->size = size;
    rgbP->compressed = FALSE;
    MALLOCARRAY(rgbP->red, size);
    MALLOCARRAY(rgbP->grn, size);
    MALLOCARRAY(rgbP->blu, size);

    if (rgbP->red == NULL || rgbP->grn == NULL || rgbP->blu == NULL)
        pm_error("Out of memory allocating %u pixels", size);
}



static void
freeRGBMapData(RGBMap * const rgbP) {

    free(rgbP->red);
    free(rgbP->grn);
    free(rgbP->blu);
}



Image *
newBitImage(unsigned int const width,
            unsigned int const height) {

    unsigned int const linelen = (width + 7) / 8;

    Image * imageP;

    MALLOCVAR_NOFAIL(imageP);

    imageP->type = IBITMAP;
    newRGBMapData(&imageP->rgb, 2);
    imageP->rgb.red[0] = imageP->rgb.grn[0] = imageP->rgb.blu[0] = 65535;
    imageP->rgb.red[1] = imageP->rgb.grn[1] = imageP->rgb.blu[1] = 0;
    imageP->rgb.used = 2;
    imageP->width = width;
    imageP->height = height;
    imageP->depth = 1;

    if (UINT_MAX / linelen < height)
        pm_error("Image dimensions too big to compute: %u x %u",
                 linelen, height);
    MALLOCARRAY(imageP->data, linelen * height);

    if (imageP->data == NULL)
        pm_error("Out of memory allocating array of %u x %u", linelen, height);

    return imageP;
}



Image *
newRGBImage(unsigned int const width,
            unsigned int const height,
            unsigned int const depth) {
    
    unsigned int const pixlen = depth > 0 ? (depth + 7) / 8 : 1;
        /* Special case for "zero" depth image, which is sometimes
           interpreted as "one color"
        */
    unsigned int const numcolors = depthToColors(depth);

    Image * imageP;
    
    MALLOCVAR_NOFAIL(imageP);
    imageP->type   = IRGB;
    newRGBMapData(&imageP->rgb, numcolors);
    imageP->width  = width;
    imageP->height = height;
    imageP->depth  = depth;
    imageP->pixlen = pixlen;

    if (UINT_MAX / width / height < pixlen)
        pm_error("Image dimensions %u x %u x %u are too big to compute.",
                 width, height, pixlen);
    MALLOCARRAY(imageP->data, width * height * pixlen);
    if (imageP->data == NULL)
        pm_error("Unable to allocate %u x %u x %u raster array",
                 width, height, pixlen);

    return imageP;
}



Image *
newTrueImage(unsigned int const width,
             unsigned int const height) {

    unsigned int const pixlen = 3;
    
    Image * imageP;

    MALLOCVAR_NOFAIL(imageP);
    imageP->type     = ITRUE;
    imageP->rgb.used = 0;
    imageP->rgb.size = 0;
    imageP->width    = width;
    imageP->height   = height;
    imageP->depth    = 24;
    imageP->pixlen   = 3;

    if (UINT_MAX / width / height < pixlen)
        pm_error("Image dimensions %u x %u x %u are too big to compute.",
                 width, height, pixlen);
    MALLOCARRAY(imageP->data, width * height * pixlen);
    if (imageP->data == NULL)
        pm_error("Unable to allocate %u x %u x %u raster array",
                 width, height, pixlen);

    return imageP;
}



static void
freeImageData(Image * const imageP) {

    if (!TRUEP(imageP))
        freeRGBMapData(&imageP->rgb);
    free(imageP->data);
}



void
freeImage(Image * const imageP) {

    assertGoodImage(imageP);

    freeImageData(imageP);

    imageP->type = IBAD;

    free(imageP);
}
