#ifndef EXIF_H_INCLUDED
#define EXIF_H_INCLUDED

#include <stdio.h>
#include "netpbm/pm_c_util.h"

#define MAX_COMMENT 2000

#if MSVCRT
    #define PATH_MAX _MAX_PATH
#endif

typedef struct {
/*--------------------------------------------------------------------------
  A structure of this type contains the information from an EXIF header
  Image File Directory (IFD).

  It appears that some of these members are possible only for certain kinds of
  IFD (e.g. ThumbnailSize does not appear in a legal IFD for a main image),
  but we recognize all tags in all IFDs all the same.
--------------------------------------------------------------------------*/
    /* In all of the following members, a null pointer means "not present,"
       which normally means the tag from which the information comes was
       not present in the IFD.

       The EXIF format might require certain tags to be present, but we
       don't.
    */
    const char *   cameraMake;
    const char *   cameraModel;
    const char *   dateTime;
    float *        xResolutionP;
    float *        yResolutionP;
    int *          orientationP;
    int *          isColorP;
    int *          flashP;
    float *        focalLengthP;
    float *        exposureTimeP;
    unsigned int * shutterSpeedP;  /* e.g. 128 for 1/128 second */
    float *        apertureFNumberP;
    float *        distanceP;
    float *        exposureBiasP;
    int *          whiteBalanceP;
    int *          meteringModeP;
    int *          exposureProgramP;
    int *          isoEquivalentP;
    int *          compressionLevelP;
    const char *   comments;
    unsigned int * thumbnailOffsetP;
    unsigned int * thumbnailLengthP;
    unsigned int * exifImageLengthP;
    unsigned int * exifImageWidthP;
    double *       focalPlaneXResP;
    double *       focalPlaneUnitsP;

    const unsigned char * thumbnail;  /* Pointer at the thumbnail */
    unsigned thumbnailSize;     /* Size of thumbnail. */
} exif_ifd;


typedef struct {
/*--------------------------------------------------------------------------
  A structure of this type contains the information from an EXIF header.
--------------------------------------------------------------------------*/
    exif_ifd mainImage;       /* aka IFD0 */
    exif_ifd thumbnailImage;  /* aka IFD1 */
    float *  ccdWidthP;  /* NULL means none */
} exif_ImageInfo;


/* Prototypes for exif.c functions. */

void
exif_parse(const unsigned char * const exifSection,
           unsigned int          const length,
           exif_ImageInfo *      const imageInfoP,
           bool                  const wantTagTrace,
           const char **         const errorP);

void
exif_showImageInfo(const exif_ImageInfo * const imageInfoP);

void
exif_terminateImageInfo(exif_ImageInfo * const imageInfoP);

#endif
