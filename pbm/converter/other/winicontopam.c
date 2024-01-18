#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "netpbm/pm_config.h"
#include "netpbm/pm_c_util.h"
#include "netpbm/mallocvar.h"
#include "netpbm/nstring.h"
#include "netpbm/shhopt.h"
#include "netpbm/pam.h"
#include "netpbm/pm_system.h"

#include "winicon.h"

#define RED   0
#define GRN   1
#define BLU   2
#define ALPHA 3
#define CHANNEL_CHARS "RGBA"



static bool verbose;



struct CmdlineInfo {
    
    const char * inputFileName;
    unsigned int allimages;
    unsigned int imageSpec;
    unsigned int image;
    unsigned int andmasks;
    unsigned int headerdump;
    unsigned int verbose;
};



static void
parseCommandLine(int argc, const char **argv,
                 struct CmdlineInfo * const cmdlineP) {

    optEntry *   option_def;
    unsigned int option_def_index;
    optStruct3   opt3;

    MALLOCARRAY_NOFAIL(option_def, 100);

    option_def_index = 0;

    OPTENT3(0, "allimages",   OPT_FLAG,   NULL,
            &cmdlineP->allimages,         0);
    OPTENT3(0, "image",     OPT_UINT,   &cmdlineP->image,
            &cmdlineP->imageSpec,         0);
    OPTENT3(0, "andmasks",  OPT_FLAG,   NULL,
            &cmdlineP->andmasks,          0);
    OPTENT3(0, "headerdump",   OPT_FLAG,   NULL,
            &cmdlineP->headerdump,        0);
    OPTENT3(0, "verbose",   OPT_FLAG,   NULL,
            &cmdlineP->verbose,           0);

    opt3.opt_table     = option_def;
    opt3.short_allowed = false;
    opt3.allowNegNum   = false;

    pm_optParseOptions3(&argc, (char **)argv, opt3, sizeof(opt3), 0);

    if (cmdlineP->allimages && cmdlineP->imageSpec)
        pm_error("You cannot specify both -allimages and -image");

    if (argc-1 < 1)
        cmdlineP->inputFileName = "-";
    else {
        cmdlineP->inputFileName = argv[1];

        if (argc-1 > 1)
            pm_error("Too many arguments.  The only possible "
                     "non-option argument is the input file name");
    }
        
    free(option_def);
}



static unsigned char const pngHeader[] = PNG_HEADER;



struct File {

    FILE *       fileP;
    const char * name;
    pm_filepos   pos;
    
};



static uint32_t
u8_le(const unsigned char * const buf,
      size_t                const offset) {

    return buf[offset + 0];
}



static uint32_t
u16_le(const unsigned char * const buf,
       size_t                const offset) {

    return
        ((uint32_t)buf[offset + 0] << 0) +
        ((uint32_t)buf[offset + 1] << 8);
}



static uint32_t
u32_le(const unsigned char * const buf,
       size_t                const offset) {

    return 
        ((uint32_t)buf[offset + 0] <<  0) +
        ((uint32_t)buf[offset + 1] <<  8) +
        ((uint32_t)buf[offset + 2] << 16) +
        ((uint32_t)buf[offset + 3] << 24);
}



static uint32_t
s32_le(const unsigned char * const buf,
       size_t                const offset) {

    return 
        ((uint32_t)buf[offset + 0] <<  0) +
        ((uint32_t)buf[offset + 1] <<  8) +
        ((uint32_t)buf[offset + 2] << 16) +
        ((uint32_t)buf[offset + 3] << 24);
}



static uint32_t
u8_be(const unsigned char * const buf,
      size_t                const offset) {

    return buf[offset + 0];
}



static uint32_t
u32_be(const unsigned char * const buf,
       size_t                const offset) {
    
    return 
        ((uint32_t)buf[offset + 0] << 24) +
        ((uint32_t)buf[offset + 1] << 16) +
        ((uint32_t)buf[offset + 2] <<  8) +
        ((uint32_t)buf[offset + 3] <<  0);
}



static uint32_t
u32_xx(const unsigned char * const buf,
       size_t                const offset) {

    uint32_t u32;

    ((uint8_t*) &u32)[0] = buf[offset + 0];
    ((uint8_t*) &u32)[1] = buf[offset + 1];
    ((uint8_t*) &u32)[2] = buf[offset + 2];
    ((uint8_t*) &u32)[3] = buf[offset + 3];

    return (u32);
}



#ifndef LITERAL_FN_DEF_MATCH
static qsort_comparison_fn cmpfn;
#endif

static int
cmpfn(const void * const aP,
      const void * const bP) {

    const struct IconDirEntry * const dirEntryAP = aP;
    const struct IconDirEntry * const dirEntryBP = bP;

    if (dirEntryAP->offset < dirEntryBP->offset)
        return -1;
    else if (dirEntryAP->offset > dirEntryBP->offset)
        return +1;
    else
        return 0;
}



static void
dumpIconDir(const struct IconDir * const dirP) {

    unsigned int i;

    pm_message("Type: %u", dirP->type);
    pm_message("Icon directory has %u images:", dirP->count);

    for (i = 0; i < dirP->count; ++i) {
        const struct IconDirEntry * const dirEntryP = &dirP->entries[i];

        pm_message("width: %u", dirEntryP->width);
        pm_message("height: %u", dirEntryP->height);
        pm_message("color count: %u", dirEntryP->color_count);
        pm_message("# color planes: %u", dirEntryP->color_planes);
        pm_message("bits per pixel: %u", dirEntryP->bits_per_pixel);
        pm_message("offset in file of image: %u", dirEntryP->offset);
        pm_message("size of image: %u", dirEntryP->size);
        pm_message("zero field: %u", dirEntryP->zero);
    }
}

            

static struct IconDir *
readIconDir(struct File * const fP,
            bool          const needHeaderDump) {

    struct IconDir head;
    struct IconDir * dirP;
    uint32_t  imageIndex; /* more bits than dir.count */

    pm_readlittleshortu(fP->fileP, &head.zero);
    pm_readlittleshortu(fP->fileP, &head.type);
    pm_readlittleshortu(fP->fileP, &head.count);
    fP->pos += 6;

    if (head.zero != 0 || head.type != ICONDIR_TYPE_ICO)
        pm_error("Not a valid windows icon file");

    MALLOCVAR(dirP);

    if (dirP == NULL)
        pm_error("Could't allocate memory for Icon directory");

    MALLOCARRAY(dirP->entries, head.count);

    if (dirP->entries == NULL)
        pm_error("Could not allocate memory for %u entries in icon directory",
                 head.count);

    dirP->zero           = head.zero;
    dirP->type           = head.type;
    dirP->count          = head.count;
    dirP->entriesAllocCt = head.count;

    for (imageIndex = 0; imageIndex < head.count; ++imageIndex) {
        struct IconDirEntry * const dirEntryP = &dirP->entries[imageIndex];

        unsigned char widthField, heightField;

        unsigned long ul;

        pm_readcharu(fP->fileP, &widthField);
        dirEntryP->width  = (widthField == 0 ? 256 : widthField);

        pm_readcharu(fP->fileP, &heightField);
        dirEntryP->height = (heightField == 0 ? 256 : heightField);
        
        pm_readcharu(fP->fileP, &dirEntryP->color_count);

        pm_readcharu(fP->fileP, &dirEntryP->zero);

        pm_readlittleshortu(fP->fileP, &dirEntryP->color_planes);

        pm_readlittleshortu(fP->fileP, &dirEntryP->bits_per_pixel);

        pm_readlittlelongu(fP->fileP, &ul); dirEntryP->size = ul;

        pm_readlittlelongu(fP->fileP, &ul); dirEntryP->offset = ul;

        fP->pos += 16;

        dirEntryP->index = imageIndex;
    }

    /* The following is paranoia code only:
     
       I've never seen a windows icon file in the wild with having the entries
       in the directory stored in a different order than the images
       themselves.  However, the file format allows for it ...
     */
    qsort(dirP->entries, dirP->count, sizeof(struct IconDirEntry), cmpfn);

    if (verbose) {
        pm_message("%s icon directory (%u image%s):",
                   fP->name,
                   dirP->count, dirP->count == 1 ? "" : "s");
        
        for (imageIndex = 0; imageIndex < dirP->count; ++imageIndex) {
            const struct IconDirEntry * const dirEntryP =
                &dirP->entries[imageIndex];

            uint32_t colorCt;

            if (dirEntryP->bits_per_pixel == 0)
                colorCt = 0;
            else if (dirEntryP->bits_per_pixel >= 32)
                colorCt = 1u << 24;
            else
                colorCt = 1u << dirEntryP->bits_per_pixel;

            if (dirEntryP->color_count != 0 &&
                colorCt > dirEntryP->color_count) {
                colorCt = dirEntryP->color_count;
            }
            pm_message ("%5u: %3u x %3u, %8u colors, %5u bytes",
                        dirEntryP->index,
                        dirEntryP->width,
                        dirEntryP->height,
                        colorCt,
                        dirEntryP->size);
        }
    }

    if (needHeaderDump)
        dumpIconDir(dirP);

    return dirP;
}



static void
freeIconDir(struct IconDir * const dirP) {

    free(dirP->entries);
    free(dirP);
}



static const unsigned char *
readImage(struct File *         const fP,
          struct IconDirEntry * const dirEntryP) {

    size_t rc;
    unsigned char * image;
    uint32_t skippedCt;

    /*  Don't try to read an image that is smaller than the
        BITMAPINFOHEADER of BMP images (40 bytes).
     
        PNG compressed images can't be smaller than that either, as the
        PNG header plus the mandantory IHDR and IEND chunks already take
        8 + 25 + 12 = 35 bytes, and there is to be a IDAT chunk too.
     */
    if (dirEntryP->size < 40) {
        pm_error("image %2u: format violation: too small as an image.",
                  dirEntryP->index);
    }
    if ((pm_filepos) dirEntryP->offset < fP->pos)
        pm_error("image %2u: format violation: invalid offset.",
                 dirEntryP->index);

    /* The following is paranoia code only:
     
       I've never seen a windows icon file in the wild with gaps between
       the images, but the file format allows for it, and Microsoft
       expects the user to fseek() to the start of each image.
     */
    skippedCt = 0;

    while ((pm_filepos) dirEntryP->offset > fP->pos) {
        if (getc(fP->fileP) == EOF) {
            pm_error("seeking to image %u: unexpected EOF", dirEntryP->index);
        }
        ++fP->pos;
        ++skippedCt;
    }

    /*  The additional four bytes are for purify and friends, as the
        routines reading BMP XOR and AND masks might read (but not
        evaluate) some bytes beyond the image data.
     */
    image = malloc(dirEntryP->size + sizeof(uint32_t));
    if (image == NULL)
        pm_error("out of memory.");

    rc = fread (image, 1, dirEntryP->size, fP->fileP);
    if (rc != dirEntryP->size) {
        pm_error("reading image %2u: unexpected EOF", dirEntryP->index);
    }
    fP->pos += dirEntryP->size;

    return image;
}



static uint8_t
getIdx1(const unsigned char * const bitmap,
        uint32_t              const offset,
        int16_t               const col) {

    return u8_le(bitmap, offset + (col >> 3)) >> (7 - (col & 0x07)) & 0x1;
}



static uint8_t
getIdx4(const unsigned char * const bitmap,
        uint32_t              const offset,
        int16_t               const col) {

    if ((col & 1) == 0x0000)
        return u8_le(bitmap, offset + (col >> 1)) >> 4 & 0x0F;
    else
        return u8_le(bitmap, offset + (col >> 1)) >> 0 & 0x0F;
}



static uint8_t
getIdx8(const unsigned char * const bitmap,
        uint32_t              const offset,
        int16_t               const col) {

    return u8_le(bitmap, offset + col);
}



typedef unsigned char PaletteEntry[4];



static void
dumpPalette(const PaletteEntry * const palette,
            unsigned int         const colorCt) {

    unsigned int i;

    for (i = 0; i < colorCt; ++i) {
        pm_message("Color %u: (%u, %u, %u)",
                   i, palette[i][2], palette[i][1], palette[i][0]);
    }
}



static void
readXorPalette(struct BitmapInfoHeader * const hdrP,
               const unsigned char *     const bitmap,
               uint32_t                  const maxSize,
               tuple **                  const tuples,
               uint16_t                  const index,
               bool                      const needHeaderDump,
               uint32_t *                const bytesConsumedP) {

    uint32_t paletteSize;

    int16_t     row;
    const PaletteEntry * palette;
    uint32_t    truncatedXorSize;
    uint32_t    bytesConsumed;
    uint32_t    bytesPerRow;
    const unsigned char * bitmapCursor;
    uint32_t sizeRemaining;
  
    uint8_t (*getIdx) (const unsigned char * bitmap,
                       uint32_t rowOffset,
                       int16_t col);
  
    if (hdrP->compression_method != BI_RGB)
        pm_error("image %2u: invalid compression method %u.",
                 index, hdrP->compression_method);

    assert(hdrP->bits_per_pixel < 16);

    switch (hdrP->bits_per_pixel) {
    case 1:
        if (hdrP->colors_in_palette == 0)
            hdrP->colors_in_palette = 2;
        getIdx = getIdx1;
        break;

    case 4:
        if (hdrP->colors_in_palette == 0)
            hdrP->colors_in_palette = 16;
        getIdx = getIdx4;
        break;

    case 8:
        if (hdrP->colors_in_palette == 0)
            hdrP->colors_in_palette = 256;
        getIdx = getIdx8;
        break;

    default:
        pm_error("image %2u: "
                 "bits per pixel is a value we don't understand: %u",
                  index, hdrP->bits_per_pixel);
        getIdx = NULL;
    }

    bitmapCursor = &bitmap[0];  /* initial value */
    sizeRemaining = maxSize;    /* initial value */
    bytesConsumed = 0;          /* initial value */

    paletteSize = hdrP->colors_in_palette * 4;

    if (sizeRemaining < paletteSize)
        pm_error("image %2u: "
                 "reading palette: image truncated.", index);
    
    palette = (const PaletteEntry *) bitmapCursor;

    if (needHeaderDump)
        dumpPalette(palette, hdrP->colors_in_palette);

    bitmapCursor  += paletteSize;
    sizeRemaining -= paletteSize;
    bytesConsumed += paletteSize;

    {
        uint32_t const xorSize = (uint32_t)
            (((hdrP->bits_per_pixel * hdrP->bm_width + 31) / 32)
             * 4 * hdrP->bm_height / 2);

        if (sizeRemaining < xorSize) {
            pm_message("image %2u: "
                       "reading XOR mask: image truncated.", index);
            truncatedXorSize = sizeRemaining;
        } else
            truncatedXorSize = xorSize;
    }

    bytesPerRow = ((hdrP->bits_per_pixel * hdrP->bm_width + 31) / 32) * 4;

    for (row = 0; hdrP->bm_height / 2 > row; ++row) {
        uint32_t rowOffset;

        if (hdrP->top_down)
            rowOffset = row * bytesPerRow;
        else
            rowOffset = (hdrP->bm_height / 2 - row - 1) * bytesPerRow;

        if (rowOffset + bytesPerRow <= truncatedXorSize) {
            int16_t col;
            for (col = 0; hdrP->bm_width > col; ++col) {
                uint8_t const idx = getIdx(bitmapCursor, rowOffset, col);

                if (idx > hdrP->colors_in_palette)
                    pm_error("invalid palette index in row %u, column %u.",
                             row, col);

                /*  The palette is an array of little-endian 32-bit values,
                    where the RGB value is encoded as follows:
                 
                    red:   bits 2^16..2^23
                    green: bits 2^8 ..2^15
                    blue:  bits 2^0 ..2^7
                 */
                tuples[row][col][PAM_RED_PLANE] = palette[idx][2];
                tuples[row][col][PAM_GRN_PLANE] = palette[idx][1];
                tuples[row][col][PAM_BLU_PLANE] = palette[idx][0];
            }
        }
    }

    bitmapCursor  += truncatedXorSize;
    sizeRemaining -= truncatedXorSize;
    bytesConsumed += truncatedXorSize;

    *bytesConsumedP = bytesConsumed;
}



static void
readXorBitfields(struct BitmapInfoHeader * const hdrP,
                 const unsigned char *     const bitmap,
                 uint32_t                  const maxSize,
                 tuple **                  const tuples,
                 uint16_t                  const index,
                 bool *                    const haveAlphaP,
                 uint32_t *                const bytesConsumedP) {

    uint32_t   bitfields[4];
    uint8_t    shift    [4];
    sample     maxval   [4];

    int16_t      row;
    uint32_t     bytesConsumed;
    uint32_t     bytesPerSample;
    uint32_t     bytesPerRow;
    const unsigned char * bitmapCursor;
    uint32_t     sizeRemaining;
    uint32_t     truncatedXorSize;

    static uint8_t alphas [256];
    bool         allOpaque;
    bool         allTransparent;

    bytesConsumed = 0;

    if (hdrP->compression_method != BI_RGB
        && hdrP->compression_method != BI_BITFIELDS)
        pm_error("image %2u: invalid compression method %u.",
                 index, hdrP->compression_method);

    assert(hdrP->bits_per_pixel >= 16);

    switch (hdrP->bits_per_pixel) {
    case 16:
        bytesPerSample = 2;
        bitfields[RED]   = 0x7C00;
        bitfields[GRN]   = 0x03E0;
        bitfields[BLU]   = 0x001F;
        bitfields[ALPHA] = 0x0000;
        break;

    case 24:
        bytesPerSample = 3;
        bitfields[RED]   = 0xFF0000;
        bitfields[GRN]   = 0x00FF00;
        bitfields[BLU]   = 0x0000FF;
        bitfields[ALPHA] = 0x000000;
        break;

    case 32:
        bytesPerSample = 4;
        bitfields[RED]   = 0x00FF0000;
        bitfields[GRN]   = 0x0000FF00;
        bitfields[BLU]   = 0x000000FF;
        bitfields[ALPHA] = 0xFF000000;
        break;

    default:
        pm_error("image %2u: bits per pixel is one we don't understand: %u.",
                 index, hdrP->bits_per_pixel);
        bytesPerSample = 0;
    }

    bitmapCursor = &bitmap[0]; /* initial value */
    sizeRemaining = maxSize;  /* initial value */

    /*  read bit fields from image data  */
    if (hdrP->compression_method == BI_BITFIELDS) {
        if (sizeRemaining < 12)
            pm_error("image %2u: "
                     "reading bit fields: image truncated.", index);

        bitfields[RED]   = u32_le(bitmapCursor, 0);
        bitfields[GRN]   = u32_le(bitmapCursor, 4);
        bitfields[BLU]   = u32_le(bitmapCursor, 8);
        bitfields[ALPHA] = 0;

        bitmapCursor  += 12;
        sizeRemaining -= 12;
        bytesConsumed += 12;
    }

    /*  determine shift and maxval from bit field for each channel */
    {
        unsigned int i;

        for (i = 0; 4 > i; ++i) {
            if (bitfields[i] == 0) {
                maxval[i] = 1;
                shift [i] = 0;
            } else {
                unsigned int j;

                maxval[i] = bitfields[i];

                for (j = 0; 32 > j; ++j) {
                    if ((maxval[i] & 0x1) != 0)
                        break;
                    maxval[i] >>= 1;
                }
                shift[i] = j;
            }

        }
    }

    /*  read the XOR mask */
    {
        uint32_t const xorSize = (uint32_t)
            (((hdrP->bits_per_pixel * hdrP->bm_width + 31) / 32)
             * 4 * hdrP->bm_height / 2);

        if (sizeRemaining < xorSize) {
            pm_message("image %2u: "
                       "reading XOR mask: image truncated.", index);
            truncatedXorSize = sizeRemaining;
        } else
            truncatedXorSize = xorSize;
    }

    bytesPerRow = ((hdrP->bits_per_pixel * hdrP->bm_width + 31) / 32) * 4;
    MEMSZERO(alphas);

    for (row = 0, allOpaque = true, allTransparent = true;
         hdrP->bm_height / 2 > row;
         ++row) {

        uint32_t offset;

        if (hdrP->top_down)
            offset = row * bytesPerRow;
        else
            offset = (hdrP->bm_height / 2 - row - 1) * bytesPerRow;

        if (offset + bytesPerRow <= truncatedXorSize) {
            unsigned int col;
            for (col = 0; col < hdrP->bm_width; ++col) {
                uint32_t const pixel = u32_le(bitmapCursor, offset);
                offset += bytesPerSample;

                tuples[row][col][PAM_RED_PLANE] =
                    pnm_scalesample((pixel & bitfields[RED]) >> shift[RED],
                                    maxval[RED], 255);
                tuples[row][col][PAM_GRN_PLANE] =
                    pnm_scalesample((pixel & bitfields[GRN]) >> shift[GRN],
                                    maxval[GRN], 255);
                tuples [row][col][PAM_BLU_PLANE]
                    = pnm_scalesample((pixel & bitfields[BLU]) >> shift[BLU],
                                      maxval[BLU], 255);

                if (bitfields [ALPHA] != 0) {
                    tuples[row][col][PAM_TRN_PLANE]
                        = pnm_scalesample(
                            (pixel & bitfields[ALPHA]) >> shift[ALPHA],
                            maxval[ALPHA], 255);

                    if (tuples[row][col][PAM_TRN_PLANE] != 0)
                        allTransparent = false;

                    if (tuples [row][col][PAM_TRN_PLANE] != 255)
                        allOpaque = false;

                    alphas[tuples[row][col][PAM_TRN_PLANE]] = !0;
                }
            }
        }
    }

    bitmapCursor  += truncatedXorSize;
    sizeRemaining -= truncatedXorSize;
    bytesConsumed += truncatedXorSize;

    /*  A fully transparent alpha channel (all zero) in XOR mask is
        defined to be void by Microsoft, and a fully opaque alpha
        channel (all maxval) is trivial and will be dropped.
    */
    *haveAlphaP = !allTransparent && !allOpaque;

    if (!allTransparent && verbose) {
        unsigned int i;
        unsigned int c;

        for (i = 0, c = 0; 256 > i; ++i) {
            if (alphas[i] != 0)
                ++c;
        }
        pm_message("image %2u: %u distinct transparency value%s",
                   index, c, (c == 1) ? "": "s");
    }
    *bytesConsumedP = bytesConsumed;
}



static void
readAnd(struct BitmapInfoHeader * const hdrP,
        const unsigned char *     const bitmap,
        uint32_t                  const maxSize,
        tuple **                  const tuples,
        uint16_t                  const index,
        unsigned int              const plane,
        sample                    const maxval) {

    int16_t  row;
    uint32_t bytesConsumed;
    uint32_t bytesPerRow;
    uint32_t sizeRemaining;
    uint32_t truncatedAndSize;

    sizeRemaining = maxSize;  /* initial value */
    bytesConsumed = 0;  /* initial value */

    {
        uint32_t const andSize = (uint32_t)
            (((1 * hdrP->bm_width + 31) / 32) * 4 * hdrP->bm_height / 2);

        if (sizeRemaining < andSize) {
            pm_message ("image %2u: "
                        "Input image ends %u bytes into the %u-byte "
                        "AND mask.  Implying remainder of mask",
                        index, sizeRemaining, andSize);
            truncatedAndSize = sizeRemaining;
        } else
            truncatedAndSize = andSize;
    }

    bytesPerRow = ((1 * hdrP->bm_width + 31) / 32) * 4;

    for (row = 0; row < hdrP->bm_height / 2; ++row) {
        uint32_t offset;

        if (hdrP->top_down)
            offset = row * bytesPerRow;
        else
            offset = (hdrP->bm_height / 2 - row - 1) * bytesPerRow;

        if (offset + bytesPerRow <= sizeRemaining) {
            unsigned int col;
            
            for (col = 0; col < hdrP->bm_width; ++col) {
                tuples[row][col][plane] =
                    ((u8_le(bitmap, offset + col/8)
                      & (1 << (7 - (col & 0x7)))) == 0x00) ?
                    maxval : 0
                ;
            }
        }
    }
    sizeRemaining -= truncatedAndSize;
    bytesConsumed += truncatedAndSize;
}



static void
dumpBmpHeader(struct BitmapInfoHeader const hdr,
              unsigned int            const imageIndex) {

    pm_message("BMP header for Image %u:", imageIndex);

    pm_message("header size: %u", hdr.header_size);
    pm_message("bitmap width: %u", hdr.bm_width);
    pm_message("bitmap height * 2: %u", hdr.bm_height);
    pm_message("row order: %s", hdr.top_down ? "top down" : "bottom up");
    pm_message("# color planes: %u", hdr.color_planes);
    pm_message("bits per pixel: %u", hdr.bits_per_pixel);
    pm_message("image size: %u", hdr.image_size);
    pm_message("horizontal resolution: %u", hdr.horizontal_resolution);
    pm_message("vertical resolution: %u", hdr.vertical_resolution);
    pm_message("# colors in palette: %u", hdr.colors_in_palette);
    pm_message("# important colors: %u", hdr.important_colors);
}



static void
readBmpHeader(const unsigned char *     const image,
              uint32_t                  const size,
              unsigned int              const imageIndex,
              bool                      const needHeaderDump,
              struct BitmapInfoHeader * const hdrP) {

    /*  BITMAPINFOHEADER structure */

    if (size < 40)
        pm_error("image %2u: reading BITMAPINFOHEADER: not enough data.",
                 imageIndex);

    hdrP->header_size           = u32_le(image,  0);
    hdrP->bm_width              = s32_le(image,  4);
    hdrP->bm_height             = s32_le(image,  8);
    hdrP->color_planes          = u16_le(image, 12);
    hdrP->bits_per_pixel        = u16_le(image, 14);
    hdrP->compression_method    = u32_le(image, 16);
    hdrP->image_size            = u32_le(image, 20);
    hdrP->horizontal_resolution = s32_le(image, 24);
    hdrP->vertical_resolution   = s32_le(image, 28);
    hdrP->colors_in_palette     = u32_le(image, 32);
    hdrP->important_colors      = u32_le(image, 36);

    if (hdrP->bm_height > 0) {
        hdrP->top_down = false;
    } else {
        hdrP->top_down   = true;
        hdrP->bm_height *= -1;
    }

    if (hdrP->header_size < 36
        || hdrP->bm_width == 0 || hdrP->bm_height == 0
        || (hdrP->bm_height & 1) != 0x0000) {
        pm_error("image %2u: format violation: invalid BMP header.",
                 imageIndex);
    }

    if (needHeaderDump)
        dumpBmpHeader(*hdrP, imageIndex);
}



static void
readXorMask(struct BitmapInfoHeader * const hdrP,
            const unsigned char *     const imageCursor,
            uint32_t                  const imageSize,
            tuple **                  const tuples,
            uint16_t                  const index,
            bool                      const needHeaderDump,
            bool *                    const haveAlphaP,
            uint32_t *                const bytesConsumedP) {
/*----------------------------------------------------------------------------
   Read the so-called XOR mask (for non-monochrome images, this is the
   color pixmap)
-----------------------------------------------------------------------------*/
    /*  preset the PAM with fully opaque black (just in case the image
        is truncated and not all pixels are filled in below).
    */
    {
        unsigned int row;

        for (row = 0; row < hdrP->bm_height / 2; ++row) {
            unsigned int col;
            for (col = 0; col < hdrP->bm_width; ++col) {
                tuples[row][col][PAM_RED_PLANE] = 0;
                tuples[row][col][PAM_GRN_PLANE] = 0;
                tuples[row][col][PAM_BLU_PLANE] = 0;
                tuples[row][col][PAM_TRN_PLANE] = 255;
            }
        }
    }

    if (hdrP->bits_per_pixel < 16) {
        readXorPalette(hdrP, imageCursor, imageSize, tuples, index,
                       needHeaderDump,
                       bytesConsumedP);
        *haveAlphaP = false;
    } else
        readXorBitfields(hdrP, imageCursor, imageSize, tuples, index,
                         haveAlphaP, bytesConsumedP);
}



static void
reportImage(unsigned int            const imageIndex,
            struct BitmapInfoHeader const hdr,
            bool                    const haveAlpha) {

    const char * const style = 
        haveAlpha ? "RGB +alpha" :
        hdr.bits_per_pixel < 16 ? "RGB/palette" :
        "RGB"
        ;

    pm_message("image %2u: "
               "BMP %3u x %3u x %2u (%s)",
               imageIndex,
               hdr.bm_width, hdr.bm_height / 2, hdr.bits_per_pixel,
               style);
}



static void
convertBmp(const unsigned char * const image,
           FILE *                const ofP,
           struct IconDirEntry * const dirEntryP,
           bool                  const needHeaderDump,
           bool                  const wantAndMaskPlane) {
    
    struct BitmapInfoHeader hdr;
    uint32_t                offset;
    bool                    haveAlpha;
    uint32_t                xorByteCt;

    struct pam outpam;
    tuple **   tuples;

    readBmpHeader(image, dirEntryP->size, dirEntryP->index, needHeaderDump,
                  &hdr);

    offset = hdr.header_size;  /* Start after header */

    if ((dirEntryP->width != hdr.bm_width)
        || (dirEntryP->height != hdr.bm_height / 2)) {
        pm_message("image %2u: "
                   "mismatch in header and image dimensions "
                   "(%u x %u vs. %u x %u)",
                   dirEntryP->index,
                   dirEntryP->width,
                   dirEntryP->height,
                   hdr.bm_width,
                   hdr.bm_height / 2);
    }

    if ((dirEntryP->bits_per_pixel != 0)
        && (dirEntryP->bits_per_pixel != hdr.bits_per_pixel)) {
        pm_message("image %2u "
                   "mismatch in header and image bpp value"
                   "(%u vs. %u)",
                   dirEntryP->index,
                   dirEntryP->bits_per_pixel,
                   hdr.bits_per_pixel);
    }

    outpam.size   = sizeof(struct pam);
    outpam.len    = PAM_STRUCT_SIZE(allocation_depth);
    outpam.file   = ofP;
    outpam.format = PAM_FORMAT;
    outpam.width  = hdr.bm_width;
    outpam.height = hdr.bm_height / 2;
    outpam.maxval = 255;
    outpam.allocation_depth = 5;
    outpam.depth  = 0;
        /* Just for tuple array allocation; we set the value for the actual
           output image below.
        */

    tuples = pnm_allocpamarray(&outpam);

    readXorMask(&hdr, &image[offset], 
                dirEntryP->size - offset,
                tuples, dirEntryP->index, needHeaderDump,
                &haveAlpha, &xorByteCt);

    offset += xorByteCt;

    {
        /* If there is no alpha channel in XOR mask, store the AND mask to
           the transparency plane.  Else, here are two transparency
           maps. If requested, store the AND mask to a fifth PAM plane
        */
        bool haveAnd;
        unsigned int andPlane;

        if (!haveAlpha) {
            haveAnd = true;
            andPlane = PAM_TRN_PLANE;
            strcpy (outpam.tuple_type, "RGB_ALPHA");
            outpam.depth  = 4;
        } else if (wantAndMaskPlane) {
            haveAnd = true;
            andPlane = PAM_TRN_PLANE + 1;
            outpam.depth  = 5;
            strcpy(outpam.tuple_type, "RGB_ALPHA_ANDMASK");
        } else {
            haveAnd = false;
            strcpy (outpam.tuple_type, "RGB_ALPHA");
            outpam.depth  = 4;
        }
        if (haveAnd) {
            readAnd(&hdr, &image[offset], dirEntryP->size - offset,
                    tuples, dirEntryP->index, andPlane, outpam.maxval);
        }
    }
    pnm_writepam(&outpam, tuples);
    pnm_freepamarray(tuples, &outpam);

    reportImage(dirEntryP->index, hdr, haveAlpha);
}



static void
reportPngInfo(const unsigned char * const image,
              struct IconDirEntry * const dirEntryP) {
    
    struct PngIhdr ihdr;

    ihdr.length      = u32_be (image, sizeof(pngHeader)  +0);
    ihdr.signature   = u32_xx (image, sizeof(pngHeader)  +4);
    ihdr.width       = u32_be (image, sizeof(pngHeader)  +8);
    ihdr.height      = u32_be (image, sizeof(pngHeader) +12);
    ihdr.bit_depth   = u8_be  (image, sizeof(pngHeader) +16);
    ihdr.color_type  = u8_be  (image, sizeof(pngHeader) +17);
    ihdr.compression = u8_be  (image, sizeof(pngHeader) +18);
    ihdr.filter      = u8_be  (image, sizeof(pngHeader) +19);
    ihdr.interlace   = u8_be  (image, sizeof(pngHeader) +20);

    if ((ihdr.length != 13)
        || ihdr.signature != *(uint32_t*)"IHDR") {
        pm_message("image %2u: PNG (uncommonly formatted)",
                   dirEntryP->index);
    } else {
        uint32_t depth;
        const char * colorType;

        switch (ihdr.color_type) {
        case 0:
            colorType = "grayscale";
            depth     = ihdr.bit_depth;
            break;

        case 2:
            colorType = "RGB";
            depth     = ihdr.bit_depth * 3;
            break;

        case 3:
            colorType = "RGB/palette";
            depth     = 8;
            break;

        case 4:
            colorType = "grayscale + alpha";
            depth     = ihdr.bit_depth * 2;
            break;

        case 6:
            colorType = "RGB + alpha";
            depth     = ihdr.bit_depth * 4;
            break;

        default:
            colorType = "unknown color system";
            depth     = 0;
            break;
        }
        pm_message("image %2u: PNG %3u x %3u x %2u (%s)",
                   dirEntryP->index,
                   ihdr.width, ihdr.height, depth, colorType);

        if ((dirEntryP->width != ihdr.width)
            || (dirEntryP->height != ihdr.height)) {
            pm_message("image %2u:"
                       " mismatch in header and image dimensions"
                       " (%u x %u vs %u x %u)",
                       dirEntryP->index, dirEntryP->width, dirEntryP->height,
                       ihdr.width, ihdr.height);
        }
        /* Mismatch between dirEntryP->bits_per_pixel and 'depth' is
           normal, because the creator of the winicon file doesn't necessarily
           know the true color resolution.
        */
    }
}



static void
convertPng(const unsigned char * const image,
           FILE *                const ofP,
           struct IconDirEntry * const dirEntryP) {

    struct bufferDesc imageBuffer;

    reportPngInfo(image, dirEntryP);

    imageBuffer.size = dirEntryP->size;
    imageBuffer.buffer = (unsigned char *)image;

    fflush (stdout);
    pm_system(pm_feed_from_memory, &imageBuffer,
              NULL /* stdout accepter */, NULL,
              "pngtopam -alphapam");
}



static uint32_t
bestImage(struct IconDir * const dirP) {

    uint32_t imageIndex;
    uint32_t bestPixelCt;
    uint32_t bestColorCt;
    uint16_t best;

    bestPixelCt = 0;  /* initial value */
    bestColorCt = 0;  /* initial value */
    best        = 0;  /* initial value */
    
    for (imageIndex = 0; dirP->count > imageIndex; ++imageIndex) {
        struct IconDirEntry * const dirEntryP = &dirP->entries[imageIndex];

        uint32_t const pixelCt = dirEntryP->width * dirEntryP->height;

        uint32_t colorCt;

        /*  32-bit icons have 24 bit color information only.
         
            Since NT 5.1 (aka WinXP), it is allowed to place 8-bit
            transparency information in the remaining bits (to check,
            you have to read all these bits in the image!), so I prefer
            32-bit images over 24-bit images (which violate the
            spec. anyway).
        */
        if (dirEntryP->bits_per_pixel > 24)
            colorCt = 1u << 25;
        else
            colorCt = 1u << dirEntryP->bits_per_pixel;

        if (dirEntryP->color_count != 0 && colorCt > dirEntryP->color_count)
            colorCt = dirEntryP->color_count;

        if ((pixelCt > bestPixelCt)
            || ((pixelCt == bestPixelCt) && (colorCt > bestColorCt))) {
            /* This is a new best */
            bestPixelCt = pixelCt;
            bestColorCt = colorCt;
            best        = imageIndex;
        }
    }
    return best;
}



static void
convertImage(struct File *         const icoP,
             struct IconDirEntry * const dirEntryP,
             FILE *                const ofP,
             bool                  const needHeaderDump,
             bool                  const wantAndMaskPlane) {

    const unsigned char * image;  /* malloced */

    image = readImage(icoP, dirEntryP);

    if (MEMEQ(image, pngHeader, sizeof (pngHeader)))
        convertPng(image, ofP, dirEntryP);
    else
        convertBmp(image, ofP, dirEntryP, needHeaderDump, wantAndMaskPlane);

    free((void *)image);
}



int
main (int argc, const char *argv []) {

    struct File ico;
    struct IconDir * dirP;
    struct CmdlineInfo cmdline;

    pm_proginit (&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    verbose = cmdline.verbose;

    ico.name =
        streq(cmdline.inputFileName, "-") ?  "<stdin>" : cmdline.inputFileName;
    ico.pos   = 0;
    ico.fileP = pm_openr(cmdline.inputFileName);

    dirP = readIconDir(&ico, cmdline.headerdump);

    if (cmdline.allimages) {
        unsigned int i;
        for (i = 0; i < dirP->count; ++i)
            convertImage(&ico, &dirP->entries[i], stdout,
                         cmdline.headerdump, cmdline.andmasks);
    } else if (cmdline.imageSpec) {
        unsigned int i;
        bool found;
        for (i = 0, found = false; i < dirP->count; ++i) {
            if (dirP->entries[i].index == cmdline.image) {
                found = true;
                convertImage(&ico, &dirP->entries[i], stdout,
                             cmdline.headerdump, cmdline.andmasks);
            }
        }
        if (!found)
            pm_error("no image index %u in.input", cmdline.image);
    } else {
        convertImage(&ico, &dirP->entries[bestImage(dirP)], stdout,
                     cmdline.headerdump, cmdline.andmasks);
    }
    
    freeIconDir(dirP);

    if (ico.fileP != stdin)
        pm_close(ico.fileP);

    return 0;
}



