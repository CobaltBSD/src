#define _POSIX_SOURCE   /* Make sure fdopen() is in <stdio.h> */
#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "netpbm/pm_config.h"
#include "netpbm/pm_c_util.h"
#include "netpbm/mallocvar.h"
#include "netpbm/nstring.h"
#include "netpbm/shhopt.h"
#include "netpbm/pm_system.h"
#include "netpbm/pam.h"
#include "winicon.h"



struct CmdlineInfo {
    const char * inputFileName;
    unsigned int verbose;
    int          pngthreshold;
    unsigned int truetransparent;
};



static void
parseCommandLine(int argc, const char **argv,
                 struct CmdlineInfo * const cmdlineP) {

    optEntry *   option_def;
    unsigned int option_def_index;
    optStruct3   opt3;
    unsigned int pngthresholdSpec;

    MALLOCARRAY_NOFAIL(option_def, 100);

    option_def_index = 0;

    OPTENT3(0, "verbose",         OPT_FLAG, NULL,
            &cmdlineP->verbose,         0);
    OPTENT3(0, "pngthreshold",    OPT_UINT, &cmdlineP->pngthreshold,
            &pngthresholdSpec,          0);
    OPTENT3(0, "truetransparent", OPT_FLAG, NULL,
            &cmdlineP->truetransparent, 0);

    opt3.opt_table     = option_def;
    opt3.short_allowed = false;
    opt3.allowNegNum   = false;

    pm_optParseOptions3(&argc, (char **)argv, opt3, sizeof(opt3), 0);

    if (pngthresholdSpec) {
        if (UINT_MAX / cmdlineP->pngthreshold < cmdlineP->pngthreshold)
            pm_error("-pngthreshold is too large: %u", cmdlineP->pngthreshold);
    } else
        cmdlineP->pngthreshold = 128;

    if (argc-1 > 0) {
        cmdlineP->inputFileName = argv[1];

        if (argc-1 > 1)
            pm_error("Too many arguments: %u.  The only non-option "
                     "argument is the optional input file name", argc-1);
    } else
        cmdlineP->inputFileName = "-";

    free(option_def);
}



static bool verbose;

static unsigned char const pngHeader[] = PNG_HEADER;



struct Palette {
    sample color[256][3];
    unsigned int colorCt;
        /* Number of colors in color[][] */
    bool tooManyColors;
        /* There are too many colors for a BMP palette (more than 256); only
           the first 256 are in color[][]
        */
};



static struct IconDir *
newIconDir() {

    struct IconDir * dirP;

    MALLOCVAR_NOFAIL(dirP);

    dirP->zero           = 0;
    dirP->type           = ICONDIR_TYPE_ICO;
    dirP->count          = 0;

    dirP->entriesAllocCt = 0;
    dirP->entries        = NULL;

    return dirP;
}



static void
freeIconDir(struct IconDir * const dirP) {
    if (dirP->entries)
        free(dirP->entries);

    free(dirP);
}



static void
addToDirectory(struct IconDirEntry * const dirEntryP,
               struct IconDir *      const dirP) {
/*----------------------------------------------------------------------------
  Add an icon to the icon directory.
-----------------------------------------------------------------------------*/
    if (dirP->count + 1 > dirP->entriesAllocCt) {
        /* Out of space in dirP->entries[].  Expand. */

        dirP->entriesAllocCt += 8;

        REALLOCARRAY(dirP->entries, dirP->entriesAllocCt);

        if (!dirP->entries)
            pm_error("Unable to get memory for %u entries "
                     "in the Icon directory.", dirP->entriesAllocCt);
    }

    dirP->entries[dirP->count++] = *dirEntryP;
}



typedef void (GetPixelFn) (tuple **     const tuples,
                           unsigned int const col,
                           unsigned int const row,
                           sample *     const pixel);



static GetPixelFn get_grayscalePixel;

static void
get_grayscalePixel(tuple **     const tuples,
                   unsigned int const col,
                   unsigned int const row,
                   sample *     const pixel) {
/*----------------------------------------------------------------------------
   Get a pixel from a grayscale PAM
-----------------------------------------------------------------------------*/
    pixel[0] = tuples[row][col][0];
    pixel[1] = tuples[row][col][0];
    pixel[2] = tuples[row][col][0];
}



static GetPixelFn get_rgbPixel;

static void
get_rgbPixel(tuple **     const tuples,
             unsigned int const col,
             unsigned int const row,
             sample *     const pixel) {
/*----------------------------------------------------------------------------
   Get a pixel from an RGB PAM
-----------------------------------------------------------------------------*/
    pixel [0] = tuples [row][col][0];
    pixel [1] = tuples [row][col][1];
    pixel [2] = tuples [row][col][2];
}


static bool
andMakesOpaque(const struct pam * const pamP,
               tuple **           const tuples,
               unsigned int       const row,
               unsigned int       const col,
               bool               const haveAlpha,
               unsigned int       const alphaPlane,
               bool               const haveAnd,
               unsigned int       const andPlane) {
/*----------------------------------------------------------------------------
   The AND mask makes a pixel opaque
-----------------------------------------------------------------------------*/
    if (haveAnd)
        return (pamP->maxval <= tuples[row][col][andPlane]);
    else if (haveAlpha)
        return (pamP->maxval <= tuples[row][col][alphaPlane]);
    else
        /* neither alpha channel nor AND mask: full opacity */
        return true;
}



static void
getPalette(struct pam *     const pamP,
           tuple **         const tuples,
           GetPixelFn *     const getPixel,
           struct Palette * const paletteP) {
/*----------------------------------------------------------------------------
  Create the palette for all the colors in 'tuples'.
-----------------------------------------------------------------------------*/
    unsigned int row;

    paletteP->colorCt = 0;  /* initial value */
    paletteP->tooManyColors = false;  /* initial value */

    for (row = 0; pamP->height > row && !paletteP->tooManyColors; ++row) {
        unsigned int col;
        for (col = 0; pamP->width > col && !paletteP->tooManyColors; ++col) {
            sample pixel[3];
            unsigned int i;

            getPixel(tuples, col, row, pixel);

            for (i = 0; i < paletteP->colorCt; ++i) {
                if ((paletteP->color[i][0] == pixel[0])
                    && (paletteP->color[i][1] == pixel[1])
                    && (paletteP->color[i][2] == pixel[2]))
                    break;
            }
            if (i == paletteP->colorCt) {
                /* We didn't find the color. */
                if (paletteP->colorCt >= 256) {
                    /* Image exceeds the palette capacity */
                    paletteP->tooManyColors = true;
                } else {
                    /* Add the color to the palette */
                    paletteP->color[paletteP->colorCt][0] = pixel[0];
                    paletteP->color[paletteP->colorCt][1] = pixel[1];
                    paletteP->color[paletteP->colorCt][2] = pixel[2];

                    ++paletteP->colorCt;
                }
            }
        }
    }
}



static bool
realAlphaNeeded(const struct pam * const pamP,
                tuple **           const tuples,
                unsigned int       const alphaPlane) {
/*----------------------------------------------------------------------------
  A real alpha channel (in contrast to an AND mask) is needed to represent the
  image in 'tuples', given that 'alphaPlane' is the alpha plane.

  A real alpha channel is needed if any pixel is translucent (neither opaque
  nor transparent).
-----------------------------------------------------------------------------*/
    unsigned int row;

    for (row = 0; row < pamP->height; ++row) {
        unsigned int col;
        for (col = 0; col < pamP->width; ++col) {
            sample const opacity = tuples[row][col][alphaPlane];

            if (opacity != 0 && opacity != pamP->maxval)
                return true;
        }
    }
    return false;
}



static void
writeBmpImageHeader(unsigned int const width,
                    unsigned int const height,
                    unsigned int const bpp,
                    unsigned int const rasterSize,
                    FILE *       const ofP) {
/*----------------------------------------------------------------------------

  Write BMP image header
    
  Note: bm_height is sum of rows in XOR mask and AND mask, while
  image_size is the size of the AND mask only.
    
  image_size does not include the sizes of the (optional) palette
  and the (mandatory) AND mask.
-----------------------------------------------------------------------------*/
    pm_writelittlelongu  (ofP, 40);              /* header_size          */
    pm_writelittlelongu  (ofP, width);           /* bm_width             */
    pm_writelittlelongu  (ofP, height *2);       /* bm_height            */
    pm_writelittleshortu (ofP, 1);               /* color_planes         */
    pm_writelittleshortu (ofP, bpp);             /* bits_per_pixel       */
    pm_writelittlelongu  (ofP, BI_RGB);          /* compression_method   */
    pm_writelittlelongu  (ofP, rasterSize);      /* image_size           */
    pm_writelittlelongu  (ofP, 0);               /* horizontal_resolution*/
    pm_writelittlelongu  (ofP, 0);               /* vertical_resolution  */
    pm_writelittlelongu  (ofP, 0);               /* colors_in_palette    */
    pm_writelittlelongu  (ofP, 0);               /* important_colors     */
}



static void
write32BitBmp(const struct pam *   const pamP,
              tuple     **         const tuples,
              GetPixelFn *         const getPixel,
              bool                 const haveAlpha,
              unsigned int         const alphaPlane,
              FILE *               const ofP,
              uint32_t *           const sizeP) {
/*----------------------------------------------------------------------------
  Write a 32-bit BMP encoded image to file *ofP.
-----------------------------------------------------------------------------*/
    int row;
    
    writeBmpImageHeader(pamP->width, pamP->height, 32, 
                        pamP->width * 4 * pamP->height, ofP);

    /*  write "XOR mask" */
    for (row = pamP->height - 1; row >= 0; --row) {
        unsigned int col;
        for (col = 0; col < pamP->width; ++col) {
            sample   pixel[3];
            uint32_t val;

            getPixel(tuples, col, row, pixel);

            val = ((uint32_t) pixel[PAM_RED_PLANE] << 16)
                + ((uint32_t) pixel[PAM_GRN_PLANE] <<  8)
                + ((uint32_t) pixel[PAM_BLU_PLANE] <<  0)
                ;
            
            if (haveAlpha)
                val += (uint32_t) tuples[row][col][alphaPlane] << 24;

            pm_writelittlelongu(ofP, val);
       }
    }
    *sizeP = 40 + pamP->height * pamP->width * 4;
}



static void
writeBmpPalette(const struct Palette * const paletteP,
                unsigned int           const maxColors,
                FILE *                 const ofP) {
/*----------------------------------------------------------------------------
   Write the palette of a BMP image.
-----------------------------------------------------------------------------*/
    unsigned int i;

    for (i = 0; i < paletteP->colorCt; ++i)
        pm_writelittlelongu(ofP, 0
                            +(paletteP->color[i][PAM_RED_PLANE] << 16)
                            +(paletteP->color[i][PAM_GRN_PLANE] <<  8)
                            +(paletteP->color[i][PAM_BLU_PLANE] <<  0));
    
    for (; i < maxColors; ++i)
        pm_writelittlelongu(ofP, 0);
}



static void
writeXorMask(const struct pam *     const pamP,
             tuple **               const tuples,
             GetPixelFn *           const getPixel,
             const struct Palette * const paletteP,
             unsigned int           const bpp,
             FILE *                 const ofP) {
/*----------------------------------------------------------------------------
   Write the "XOR mask" part of a BMP image.

   This is what one normally thinks of as the foreground image raster.
-----------------------------------------------------------------------------*/
    unsigned int const maxCol = ((pamP->width * bpp + 31) & ~31) / bpp;

    int row;
                 
    for (row = pamP->height - 1; row >= 0; --row) {
        uint8_t  val;
        uint16_t mask;
        unsigned int col;

        mask = 0x1;
        val  = 0x0;

        for (col = 0; col < pamP->width; ++col) {
            sample pixel[3];
            unsigned int i;

            mask <<= bpp;
            val  <<= bpp;

            getPixel(tuples, col, row, pixel);

            for (i = 0; i < paletteP->colorCt; ++i)
                if (true
                    && (pixel[0] == paletteP->color[i][0])
                    && (pixel[1] == paletteP->color[i][1])
                    && (pixel[2] == paletteP->color[i][2]))
                    break;

            assert(i < paletteP->colorCt);

            val |= i;

            if (mask > 0xFF) {
                pm_writecharu(ofP, val);
                mask = 0x1;
                val  = 0x0;
            }
        }
        for (; col < maxCol; ++col) {
            mask <<= bpp;
            val  <<= bpp;

            if (mask > 0xFF) {
                pm_writecharu(ofP, val);
                mask = 0x1;
            }
        }
    }
}



static void
writePaletteBmp(unsigned int           const bpp,
                const struct pam   *   const pamP,
                tuple **               const tuples,
                GetPixelFn *           const getPixel,
                const struct Palette * const paletteP,
                FILE *                 const ofP,
                uint32_t *             const sizeP) {
/*----------------------------------------------------------------------------
  Write a `BMP with palette' encoded image to file *ofP.

  Unless it would be smaller as a 32-bit direct image, in which case
  write that instead.
-----------------------------------------------------------------------------*/
    unsigned int const maxColors = 1 << bpp;

    unsigned int const rasterSize =
        pamP->height *((pamP->width * bpp + 31) & ~31) / 8;

    if (pamP->height * pamP->width * 4 <= maxColors * 4 + rasterSize)
        write32BitBmp(pamP, tuples, getPixel, false /*haveAlpha*/, 0,
                      ofP, sizeP);
    else {
        unsigned int const headerSize = 40;
        unsigned int const paletteSize = maxColors * 4;

        writeBmpImageHeader(pamP->width, pamP->height, bpp, rasterSize, ofP);

        writeBmpPalette(paletteP, maxColors, ofP);

        writeXorMask(pamP, tuples, getPixel, paletteP, bpp, ofP);

        *sizeP = headerSize + paletteSize + rasterSize;
    }
}



static void
writeAndMask(const struct pam * const pamP,
             tuple     **       const tuples,
             bool               const haveAlpha,
             unsigned int       const alphaPlane,
             bool               const haveAnd,
             unsigned int       const andPlane,
             FILE *             const ofP,
             uint32_t *         const sizeP) {
/*----------------------------------------------------------------------------
  Write the AND mask to file *ofP.
-----------------------------------------------------------------------------*/
    unsigned int const maxCol =((pamP->width * 1 + 31) & ~31) / 1;

    int row;
    unsigned int sizeSoFar;

    sizeSoFar = 0;

    for (row = pamP->height - 1; row >= 0; --row) {
        uint8_t  val;
        uint16_t mask;
        unsigned int col;

        mask = 0x1;
        val  = 0x0;

        for (col = 0; col < pamP->width; ++col) {
            mask <<= 1;
            val  <<= 1;

            if (!andMakesOpaque(pamP, tuples, row, col, 
                                haveAlpha, alphaPlane, haveAnd, andPlane))
                val |= 0x1;

            if (mask > 0xFF) {
                pm_writecharu(ofP, val);
                sizeSoFar += 1;
                mask = 0x1;
                val  = 0x0;
            }
        }
        for (; col < maxCol; ++col) {
            mask <<= 1;
            val  <<= 1;

            if (mask > 0xFF){
                pm_writecharu(ofP, val);
                sizeSoFar += 1;
                mask = 0x1;
            }
        }
    }
    *sizeP = sizeSoFar;
}



static void
makeAlphaFile(const struct pam * const imagePamP,
              tuple **           const imageTuples,
              unsigned int       const alphaPlane,
              const char **      const alphaFileNameP) {

    FILE * alphaFileP;
    struct pam alphaPam;
    tuple ** alphaTuples;
    unsigned int row;
    
    pm_make_tmpfile(&alphaFileP, alphaFileNameP);

    alphaPam.size   = sizeof(alphaPam);
    alphaPam.len    = PAM_STRUCT_SIZE(tuple_type);
    alphaPam.file   = alphaFileP;
    alphaPam.format = PAM_FORMAT;
    alphaPam.width  = imagePamP->width;
    alphaPam.height = imagePamP->height;
    alphaPam.depth  = 1;
    alphaPam.maxval = imagePamP->maxval;
    strcpy(alphaPam.tuple_type, PAM_PGM_TUPLETYPE);

    alphaTuples = pnm_allocpamarray(&alphaPam);

    assert(alphaPlane < imagePamP->depth);

    for (row = 0; row < alphaPam.height; ++row) {
        unsigned int col;
        for (col = 0; col < alphaPam.width; ++col)
            alphaTuples[row][col][0] = imageTuples[row][col][alphaPlane];
    }

    pnm_writepam(&alphaPam, alphaTuples);

    pnm_freepamarray(alphaTuples, &alphaPam);

    pm_close(alphaFileP);
}



struct AcceptToFileParm {
    FILE *   ofP;
    size_t * writeCtP;
};

static void
acceptToFile(int    const pipeToSuckFd,
             void * const accepterParm) {

    struct AcceptToFileParm * const parmP = accepterParm;

    FILE * const inFileP = fdopen(pipeToSuckFd, "r");

    bool eof;
    size_t copyCt;

    for (eof = false, copyCt = 0; !eof; ) {
        size_t readCt;
        unsigned char buffer[1024];

        readCt = fread(buffer, 1, sizeof(buffer), inFileP);

        if (readCt == 0)
            eof = true;
        else {
            size_t writeCt;

            writeCt = fwrite(buffer, 1, readCt, parmP->ofP);

            if (writeCt != readCt)
                pm_error("Write to images file failed.  errno=%d (%s)",
                         errno, strerror(errno));

            copyCt += writeCt;
        }
    }
    *parmP->writeCtP = copyCt;
}



static void
writePng(const struct pam * const pamP,
         tuple **           const tuples,
         bool               const haveAlpha,
         unsigned int       const alphaPlane,
         bool               const haveAnd,
         unsigned int       const andPlane,
         uint32_t *         const sizeP,
         FILE *             const ofP) {

    struct pamtuples pamTuples;
    size_t pngSize;
    struct AcceptToFileParm acceptParm;
    struct pam pam;

    pam = *pamP;
    pam.depth = pamP->depth - (haveAlpha ? 1 : 0) - (haveAnd ? 1 : 0);

    pamTuples.pamP    = &pam;
    pamTuples.tuplesP = (tuple ***)&tuples;

    /* We're going to fork a process to add stuff to *ofP, so we flush
       out this process' previous writes to that file first:
    */
    fflush(ofP);

    acceptParm.ofP = ofP;
    acceptParm.writeCtP = &pngSize;
    
    if (haveAlpha || haveAnd) {
        const char * alphaFileName;
        const char * command;

        if (haveAlpha)
            makeAlphaFile(pamP, tuples, alphaPlane, &alphaFileName);
        else
            makeAlphaFile(pamP, tuples, andPlane, &alphaFileName);

        strcpy (pam.tuple_type,
                pam.depth == 3 ? PAM_PPM_TUPLETYPE: PAM_PGM_TUPLETYPE);
        
        pm_asprintf(&command, "pnmtopng -alpha=\"%s\"", alphaFileName);

        pm_system(pm_feed_from_pamtuples, &pamTuples,
                  acceptToFile, &acceptParm,
                  command);
    
        pm_strfree(command);
    
        unlink(alphaFileName);
    } else {
        pm_system(pm_feed_from_pamtuples, &pamTuples,
                  acceptToFile, &acceptParm,
                  "pnmtopng");
    }

    *sizeP = pngSize;
}



static void
blackenXor(const struct pam * const pamP,
           tuple     **       const tuples,
           bool               const haveAlpha,
           unsigned int       const alphaPlane,
           bool               const haveAnd,
           unsigned int       const andPlane) {
/*----------------------------------------------------------------------------
  Set all pixels marked as transparent in AND mask to black.
-----------------------------------------------------------------------------*/
    unsigned int row;

    for (row = 0; row < pamP->height; ++row) {
        unsigned int col;
        for (col = 0; col < pamP->width; ++col) {
            if (!andMakesOpaque(pamP, tuples, row, col,
                                haveAlpha, alphaPlane, haveAnd, andPlane)) {
                tuples[row][col][0] = PAM_BLACK;

                if (pamP->depth >= 3) {
                    tuples[row][col][1] = PAM_BLACK;
                    tuples[row][col][2] = PAM_BLACK;
                }
            }
        }
    }
}




static void
readAndScalePam(struct pam * const pamP,
                bool         const doingPng,
                tuple **     const tuples) {

    if (doingPng) {
        /* Read the image with its native maxval */
        unsigned int row;
        for (row = 0; row < pamP->height; ++row)
            pnm_readpamrow(pamP, tuples[row]);
    } else {
        /* Read the image and scale to maxval 255 */
        tuple * tuplerow;
        unsigned int row;
        tuplerow = pnm_allocpamrow(pamP);

        for (row = 0; row < pamP->height; ++row) {
            pnm_readpamrow(pamP, tuplerow);
            pnm_scaletuplerow(pamP, tuples[row], tuplerow, 255);
        }
        pnm_freepamrow(tuplerow);
        pamP->maxval = 255;
    }
}



static void
determineImageType(const struct pam * const pamP,
                   tuple **           const tuples,
                   GetPixelFn **      const getPixelP,
                   bool *             const haveAlphaP,
                   unsigned int *     const alphaPlaneP,
                   bool *             const haveAndP,
                   unsigned int *     const andPlaneP) {

    /*  PAM input channels:
     *
     *  1-channel PAM: Grayscale
     *  2-channel PAM: Grayscale +Alpha
     *  3-channel PAM: RGB
     *  4-channel PAM: RGB +Alpha
     *  5-channel PAM: RGB +Alpha +AND mask
     */
    switch (pamP->depth) {
    case 1:
        *getPixelP  = get_grayscalePixel;
        *haveAlphaP = false;
        *haveAndP   = false;
        break;

    case 2:
        *getPixelP = get_grayscalePixel;
        if (realAlphaNeeded(pamP, tuples, 1)) {
            *haveAlphaP  = true;
            *alphaPlaneP = 1;
            *haveAndP    = false;
        } else {
            *haveAlphaP = false;
            *haveAndP   = true;
            *andPlaneP  = 1;
        }
        break;

    case 3:
        *getPixelP  = get_rgbPixel;
        *haveAlphaP = false;
        *haveAndP   = false;
        break;

    case 4:
        *getPixelP = get_rgbPixel;
        if (realAlphaNeeded(pamP, tuples, 3)) {
            *haveAlphaP  = true;
            *alphaPlaneP = 3;
            *haveAndP    = false;
        } else {
            *haveAlphaP = false;
            *haveAndP    = true;
            *andPlaneP  = 3;
        }
        break;

    case 5:
        *getPixelP   = get_rgbPixel;
        *haveAlphaP  = true;
        *alphaPlaneP = 3;
        *haveAndP    = true;
        *andPlaneP   = 4;
        break;

    default:
        pm_error("unexpected PAM depth %u.  "
                 "We understand depths 1-5", pamP->depth);
        break;
    }
}



static void
reportImageInfo(unsigned int           const imageNum,
                const struct pam *     const pamP,
                const struct Palette * const paletteP,
                bool                   const haveAlpha,
                bool                   const haveAnd) {

    const char * colorCt;

    if (paletteP->tooManyColors)
        pm_asprintf(&colorCt, "> 256");
    else
        pm_asprintf(&colorCt, "%u", paletteP->colorCt);

    pm_message("Image %2u:"
               " %3u x %3u x %u, %s colors%s%s",
               imageNum,
               pamP->width, pamP->height, pamP->depth,
               colorCt,
               haveAlpha ? ", alpha channel": "",
               haveAnd ? ", AND mask": "");

    pm_strfree(colorCt);
}



static void
writeIconAndCreateDirEntry(const struct pam *     const pamP,
                           tuple **               const tuples,
                           GetPixelFn *           const getPixel,
                           bool                   const doingPng,
                           bool                   const haveAlpha,
                           unsigned int           const alphaPlane,
                           bool                   const haveAnd,
                           unsigned int           const andPlane,
                           bool                   const mustBlackenXor,
                           const struct Palette * const paletteP,
                           FILE *                 const ofP,
                           struct IconDirEntry *  const dirEntryP) {
/*----------------------------------------------------------------------------
   Write to *ofP the icon image for the image represented by *pamP and
   'tuples'.

   Generate the information for an icon directory entry for this image
   and return it as *dirEntryP.  ==>BUT: the 'offset' member of this
   structure will not be meaningful. <==

   Make a PNG image if 'doingPng' is true; BMP otherwise.

   'haveAlpha' means that there is an alpha plane in 'tuples' and it is
   Plane 'alphaPlane'.

   'haveAnd' means that there is an AND plane in 'tuples' and it is Plane
   'andPlane'.

   *paletteP is the color palette for the icon; it contains an entry for each
   color in 'tuples'.  Except: it may simply indicate that there are too many
   colors in 'tuples' to have a palette.

   The 'bits_per_pixel' member of the directory entry is supposed to tell the
   color resolution of the image so the user can decide which of many versions
   of the icon in the file to use.  But we just call it 32 bits in every case
   except paletted BMP, where it actually relates to how many colors are in
   the image.
-----------------------------------------------------------------------------*/
    dirEntryP->width          = pamP->width;
    dirEntryP->height         = pamP->height;
    dirEntryP->color_planes   = 1;
    dirEntryP->zero           = 0;

    if (doingPng) {
        dirEntryP->color_count    = 0;
        dirEntryP->bits_per_pixel = 32;

        writePng(pamP, tuples, haveAlpha, alphaPlane, haveAnd, andPlane,
                 &dirEntryP->size, ofP);
    } else {
        uint32_t bmpSize;
        uint32_t andMaskSize;

        if (mustBlackenXor)
            blackenXor(pamP, tuples,
                       haveAlpha, alphaPlane, haveAnd, andPlane);

        if (haveAlpha) {
            dirEntryP->color_count    = 0;
            dirEntryP->bits_per_pixel = 32;

            write32BitBmp(pamP, tuples, getPixel, haveAlpha, alphaPlane,
                          ofP, &bmpSize);
        } else if (paletteP->tooManyColors) {
            /* Do a truecolor image */
            dirEntryP->color_count    = 0;
            dirEntryP->bits_per_pixel = 32;

            write32BitBmp(pamP, tuples, getPixel, false /*haveAlpha*/, 0,
                          ofP, &bmpSize);
        } else {
            /* Do a paletted image */

            if (paletteP->colorCt <= 2) {
                dirEntryP->color_count    = paletteP->colorCt;
                dirEntryP->bits_per_pixel = 1;
                    
                writePaletteBmp(1, pamP, tuples, getPixel, paletteP,
                                ofP, &bmpSize);
            } else if (paletteP->colorCt <= 16) {
                dirEntryP->color_count    = paletteP->colorCt;
                dirEntryP->bits_per_pixel = 4;
                    
                writePaletteBmp(4, pamP, tuples, getPixel,paletteP,
                                ofP, &bmpSize);
            } else {
                dirEntryP->color_count    = 0;
                dirEntryP->bits_per_pixel = 8;
                    
                writePaletteBmp(8, pamP, tuples, getPixel, paletteP,
                                ofP, &bmpSize);
            }
        }
        writeAndMask(pamP, tuples, haveAlpha, alphaPlane, haveAnd, andPlane,
                     ofP, &andMaskSize);

        dirEntryP->size = bmpSize + andMaskSize;
    }
}



static void
convertOneImage(unsigned int     const imageNum,
                FILE *           const ifP,
                unsigned int     const pngThreshold,
                bool             const mustBlackenXor,
                FILE *           const ofP,
                struct IconDir * const dirP) {

    struct IconDirEntry dirEntry;
    struct pam          pam;
    tuple **            tuples;
    bool                haveAlpha;
    unsigned int        alphaPlane;
    bool                haveAnd;
    unsigned int        andPlane;
    GetPixelFn *        getPixel;
    struct Palette      palette;
    bool                doingPng;
        
    /*  Output:
     *
     *  threshold^2 pixels or more:
     *      no alpha channel:        PNG (RGB)
     *      alpha channel:           PNG (RGBA)
     *      alpha channel +AND mask: PNG (RGBA), AND mask dropped
     *  alpha values other than 0 and maxval: 32bit +alpha BMP
     *  no more than   2 colors:  1bit or 32bit BMP
     *  no more than  16 colors:  4bit or 32bit BMP
     *  no more than 256 colors:  8bit or 32bit BMP
     *  more than    256 colors: 32bit BMP
     */
    pnm_readpaminit(ifP, &pam, PAM_STRUCT_SIZE(tuple_type));

    if (pam.width > 256 || pam.height > 256)
        pm_error("Image %u: too large as a windows icon (%u x %u).  "
                 "Maximum allowed dimension is 256",
                 imageNum, pam.width, pam.height);

    tuples = pnm_allocpamarray(&pam);

    doingPng = pam.width * pam.height >= pngThreshold;

    readAndScalePam(&pam, doingPng, tuples);

    determineImageType(&pam, tuples, &getPixel,
                       &haveAlpha, &alphaPlane, &haveAnd, &andPlane);

    getPalette(&pam, tuples, getPixel, &palette);

    if (verbose)
        reportImageInfo(imageNum, &pam, &palette, haveAlpha, haveAnd);

    writeIconAndCreateDirEntry(&pam, tuples, getPixel, doingPng,
                               haveAlpha, alphaPlane,
                               haveAnd, andPlane,
                               mustBlackenXor,
                               &palette,
                               ofP, &dirEntry);

    if (verbose)
        pm_message("Image %2u: %u bytes", imageNum, dirEntry.size);

    pnm_freepamarray(tuples, &pam);

    addToDirectory(&dirEntry, dirP);
}



static void
convert(FILE *           const ifP,
        unsigned int     const pngThreshold,
        bool             const mustBlackenXor,
        struct IconDir * const dirP,
        FILE *           const ofP) {
/*----------------------------------------------------------------------------
  Read a (multi-image) PAM file from *ifP and convert the individual images
  to the proper format for a Windows icon file and write those to *ofP.

  Where the number of pixels in an image is at least 'pngThreshold', use
  a PNG image.  Otherwise, use a BMP.
-----------------------------------------------------------------------------*/
    unsigned int imageNum;
    int eof;
    
    for (imageNum = 0, eof = false; !eof; ++imageNum) {
        convertOneImage(imageNum, ifP, pngThreshold, mustBlackenXor,
                        ofP, dirP);

        pnm_nextimage(ifP, &eof);
    }
}



static void
writeIconDirEntry(const struct IconDirEntry * const dirEntryP,
                  FILE *                      const ofP) {
        
    pm_writecharu        (ofP, dirEntryP->width);
    pm_writecharu        (ofP, dirEntryP->height);
    pm_writecharu        (ofP, dirEntryP->color_count);
    pm_writecharu        (ofP, dirEntryP->zero);
    pm_writelittleshortu (ofP, dirEntryP->color_planes);
    pm_writelittleshortu (ofP, dirEntryP->bits_per_pixel);
    pm_writelittlelongu  (ofP, dirEntryP->size); 
    pm_writelittlelongu  (ofP, dirEntryP->offset);
}



static void
writeIconDirectory(const struct IconDir * const dirP,
                   FILE *                 const ofP) {
/*----------------------------------------------------------------------------
  Write to file *ofP the icon directory described by *dirP.

  *dirP's image offset members are meaningless as input.  We fill them in.
-----------------------------------------------------------------------------*/
    uint32_t const hsize = 6 + dirP->count * 16;

    unsigned int imageNum;
    unsigned int imageOffset;

    pm_writelittleshortu(ofP, dirP->zero);
    pm_writelittleshortu(ofP, dirP->type);
    pm_writelittleshortu(ofP, dirP->count);

    for (imageNum = 0, imageOffset = hsize;
         imageNum < dirP->count;
         ++imageNum) {

        struct IconDirEntry * const dirEntryP = &dirP->entries[imageNum];
        
        pm_message("image %2u: %3u x %3u x %2u",
                   imageNum,
                   dirEntryP->width,
                   dirEntryP->height,
                   dirEntryP->bits_per_pixel);

        dirEntryP->offset = imageOffset;

        writeIconDirEntry(dirEntryP, ofP);

        imageOffset += dirEntryP->size;
    }
}



static void
copyFile(FILE * const ifP,
         FILE * const ofP) {

    bool eof;
    
    for (eof = false; !eof; ) {
        unsigned char buffer[1024];
        size_t bytesRead;

        bytesRead = fread(buffer, 1, sizeof(buffer), ifP);

        if (bytesRead == 0)
            eof = true;
        else {
            size_t bytesWritten;

            bytesWritten = fwrite(buffer, 1, bytesRead, ofP);

            if (bytesWritten < bytesRead)
                pm_error("Error writing to output file.");
        }
    }
}



static void
writeIconFile(const struct IconDir * const dirP,
              FILE *                 const imagesFileP,
              FILE *                 const ofP) {
/*----------------------------------------------------------------------------
  Write a windows icon file.

  *dirP is the icon directory to put in it.

  *imagesFileP contains all the text of the icon images.  The contents of
  this file go verbatim into the output.
-----------------------------------------------------------------------------*/
    writeIconDirectory(dirP, ofP);

    copyFile(imagesFileP, ofP);
}



int
main(int argc, const char *argv []) {

    struct CmdlineInfo cmdline;
    FILE * ifP;
    FILE * imagesFileP;
        /* This is the file in which we collect the individual icon
           images to be copied later to the output.
        */
    struct IconDir * dirP;

    pm_proginit(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    verbose = cmdline.verbose;

    /* The output icon file has directory information at the top that we
       can't know until we have looked at the input images.  So as we pass
       through the input, we collect the directory information and generate
       the individual icon images and store them in *imageFileP.  When we've
       been through all of the input, we write out the directory and then
       copy the images from *imageFileP to the output.
    */

    dirP = newIconDir();

    imagesFileP = pm_tmpfile();

    ifP = pm_openr(cmdline.inputFileName);

    convert(ifP, SQR(cmdline.pngthreshold), cmdline.truetransparent,
            dirP, imagesFileP);

    rewind(imagesFileP);

    writeIconFile(dirP, imagesFileP, stdout);

    freeIconDir(dirP);

    return 0;
}



