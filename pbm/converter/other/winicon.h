#include "pm_c_util.h"

#define ICONDIR_TYPE_ICO (1)

/*  windows icon structures  */
struct IconDirEntry {
    uint16_t width;               /* image width in pixels 0 == 256 */
    uint16_t height;              /* image height in pixels 0 == 256 */
    uint8_t  color_count;         /* 0 if bits_per_pixel >= 8 */
    uint8_t  zero;                /* 0 */
    uint16_t color_planes;        /* 1 */
    uint16_t bits_per_pixel;      /* allowed values: 1, 4, 8, 16 or 32 (1) */
    uint32_t size;                /* size of image */
    uint32_t offset;              /* file offset of image */

    uint16_t index;               /* extra field (not in file) */
};

/*  (1) This is from
 *  http://blogs.msdn.com/b/oldnewthing/archive/2010/10/19/10077610.aspx.
 *
 *  However, the bpp value in the icon directory is used as a hint for
 *  image selection only.  It seems to be legal to set this value to
 *  zero, and e.g. in SHELL32.DLL of Win98SE, there are many 8bpp
 *  images described as 24 bit images in the icon directory.
 *
 *  The bpp value of image 1 in icon 150 in SHELL32.DLL of WinXP is 24
 *  (in header and BMP).  This may be a bug, as the 32 x 32 x 8 image
 *  is missing, but it shows the Windows icon rendering engine is able
 *  to cope with 24 bit images).
 *
 *  16bpp icons are at least rare in the wild.
 */
struct IconDir {
    uint16_t zero;                /* 0 */
    uint16_t type;                /* 1 */
    uint16_t count;               /* number of images in icon */

    unsigned int entriesAllocCt;     /* # of allocated slots in 'entries'*/
    struct IconDirEntry * entries;   /* one entry for each image */
};

/*  BMP image structures  */

struct BitmapInfoHeader {
    uint32_t header_size;         /* >= 40 */
    int32_t  bm_width;
    int32_t  bm_height;
    uint16_t color_planes;
    uint16_t bits_per_pixel;
    uint32_t compression_method;
    uint32_t image_size;
    int32_t  horizontal_resolution; /* pixels per meter (!) */
    int32_t  vertical_resolution;   /* pixels per meter (!) */
    uint32_t colors_in_palette;
    uint32_t important_colors;

    bool top_down;                /* extra field (not in file) */

};

typedef enum {
    BI_RGB       = 0,
    BI_BITFIELDS = 3

} BiCompression;

/*  PNG image structures  */
#define PNG_HEADER { 0x89, 'P', 'N', 'G', '\r', '\n', 0x1A /* ^Z */, '\n' }

struct PngIhdr {
    uint32_t length;              /* 13 */
    uint32_t signature;           /* "IHDR" */
    uint32_t width;               /* image width in pixels */
    uint32_t height;              /* image height in pixels */
    uint8_t  bit_depth;           /* depth per channel */
    uint8_t  color_type;          /* recognized values: 0, 2, 3, 4 and 6 */
    uint8_t  compression;
    uint8_t  filter;
    uint8_t  interlace;
    uint32_t crc;
};
