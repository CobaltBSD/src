#ifndef PNGX_H_INCLUDED
#define PNGX_H_INCLUDED

#include <png.h>
#include "pm_c_util.h"

/* pngx is designed to be an extension of the PNG library to make using
   the PNG library easier and cleaner.
*/

struct pngx_chroma {
    float wx;
    float wy;
    float rx;
    float ry;
    float gx;
    float gy;
    float bx;
    float by;
};

struct pngx_phys {
    int x;
    int y;
    int unit;
};

struct pngx_text {
    png_text *   line;
    unsigned int size;
};

struct pngx_plte {
    png_color *  palette;
    unsigned int size;
};

struct pngx_trns {
    png_byte *    trans;
    unsigned int  numTrans;
    png_color_16  transColor;
};

typedef enum {PNGX_READ, PNGX_WRITE} pngx_rw;

struct pngx {
    png_structp  png_ptr;
    png_infop    info_ptr;
    pngx_rw      rw;
    png_uint_16  maxval;
    unsigned int numPassesRequired;
        /* The number of times we have write the complete image to the
           compressor.  This is more than one when the compressor is set
           up to do an interlaced format.
        */
};

void
pngx_create(struct pngx ** const pngxPP,
            pngx_rw        const rw,
            jmp_buf *      const jmpbufP);

void
pngx_destroy(struct pngx * const pngxP);

bool
pngx_chunkIsPresent(struct pngx * const pngxP,
                    uint32_t      const chunkType);

unsigned int
pngx_bitDepth(struct pngx * const pngxP);

png_color_16
pngx_bkgd(struct pngx *  const pngxP);

png_byte
pngx_colorType(struct pngx * const pngxP);

png_byte
pngx_filterType(struct pngx * const pngxP);

double
pngx_gama(struct pngx * const pngxP);

uint32_t
pngx_imageHeight(struct pngx * const pngxP);

uint32_t
pngx_imageWidth(struct pngx * const pngxP);

png_byte
pngx_interlaceType(struct pngx * const pngxP);

struct pngx_plte
pngx_plte(struct pngx * const pngxP);

png_color_8
pngx_sbit(struct pngx * const pngxP);

struct pngx_text
pngx_text(struct pngx * const pngxP);

png_time
pngx_time(struct pngx * const pngxP);

struct pngx_trns
pngx_trns(struct pngx * const pngxP);

uint32_t
pngx_xPixelsPerMeter(struct pngx * const pngxP);

uint32_t
pngx_yPixelsPerMeter(struct pngx * const pngxP);

float
pngx_pixelAspectRatio(struct pngx * const pngxP);

bool
pngx_pixelAspectRatioIsKnown(struct pngx * const pngxP);

void
pngx_removeChunk(struct pngx * const pngxP,
                 uint32_t      const chunkType);

void
pngx_setBkgdPalette(struct pngx * const pngxP,
                    unsigned int  const backgroundIndex);

void
pngx_setBkgdRgb(struct pngx * const pngxP,
                png_color_16  const backgroundArg);

void
pngx_setChrm(struct pngx *      const pngxP,
             struct pngx_chroma const chroma);

typedef enum {
    PNGX_PERCEPTUAL,
    PNGX_RELATIVE_COLORIMETRIC,
    PNGX_SATURATION,
    PNGX_ABSOLUTE_COLORIMETRIC
} pngx_srgbIntent;

const char *
pngx_srgbIntentDesc(pngx_srgbIntent const srgbIntent);

void
pngx_setSrgb(struct pngx *   const pngxP,
             pngx_srgbIntent const srgbIntent);

void
pngx_setCompressionSize(struct pngx * const pngxP,
                        unsigned int  const bufferSize);

void
pngx_setFilter(struct pngx * const pngxP,
               int           const filterSet);

void
pngx_setGama(struct pngx * const pngxP,
             float         const fileGamma);

void
pngx_setGamma(struct pngx * const pngxP,
              float         const displayGamma,
              float         const imageGamma);

void
pngx_setHist(struct pngx * const pngxP,
             png_uint_16 * const histogram);

void
pngx_setIhdr(struct pngx * const pngxP,
             unsigned int  const width,
             unsigned int  const height,
             unsigned int  const bitDepth,
             int           const colorType,
             int           const interlaceMethod,
             int           const compressionMethod,
             int           const filterMethod);

void
pngx_setInterlaceHandling(struct pngx * const pngxP);

void
pngx_setInvalid(struct pngx * const pngxP);

void
pngx_setPacking(struct pngx * const pngxP);

void
pngx_setPhys(struct pngx *    const pngxP,
             struct pngx_phys const phys);

void
pngx_setPlte(struct pngx * const pngxP,
             png_color *   const palette,
             unsigned int  const paletteSize);

void
pngx_setSbit(struct pngx * const pngxP,
             png_color_8   const sbit);

void
pngx_setShift(struct pngx * const pngxP,
              png_color_8   const sigBitArg);

void
pngx_setSigBytes(struct pngx * const pngxP,
                 unsigned int  const sigByteCt);

void
pngx_setTextKey(png_text *   const textP,
                const char * const key);

void
pngx_setTextLang(png_text *   const textP,
                 const char * const language);

void
pngx_setTextLangKey(png_text *   const textP,
                    const char * const key);

void
pngx_termText(png_text * const textP);

void
pngx_setText(struct pngx * const pngxP,
             png_textp     const textP,
             unsigned int  const count);

void
pngx_setTime(struct pngx * const pngxP,
             time_t        const timeArg);

void
pngx_setTrnsPalette(struct pngx *    const pngxP,
                    const png_byte * const transPalette,
                    unsigned int     const paletteSize);

void
pngx_setTrnsValue(struct pngx * const pngxP,
                  png_color_16  const transColorArg);

void
pngx_readInfo(struct pngx * const pngxP);

void
pngx_writeInfo(struct pngx * const pngxP);

void
pngx_readStart(struct pngx * const pngxP,
               FILE *        const ifP);

void
pngx_readRow(struct pngx * const pngxP,
             png_byte *    const rowBuf,
             png_byte *    const displayRow);

void
pngx_readImage(struct pngx * const pngxP,
               png_byte **   const image);

void
pngx_writeRow(struct pngx *    const pngxP,
              const png_byte * const line);

void
pngx_readEnd(struct pngx * const pngxP);

void
pngx_writeEnd(struct pngx * const pngxP);

#endif
