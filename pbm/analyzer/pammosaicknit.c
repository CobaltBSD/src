/* ----------------------------------------------------------------------
 *
 * Validate a mosaic knitting pattern
 *
 * By Scott Pakin <scott+pbm@pakin.org>
 *
 * ----------------------------------------------------------------------
 *
 * Copyright (C) 2010 Scott Pakin <scott+pbm@pakin.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses/.
 *
 * ----------------------------------------------------------------------
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mallocvar.h"
#include "pam.h"

int const max_skips = 3;      /* Maximum number of consecutive skips */

/* Each pixel can be either black or white and can be valid or invalid. */
typedef enum {
    MK_VALID_BLACK,
    MK_VALID_WHITE,
    MK_INVALID_BLACK,
    MK_INVALID_WHITE
} mkPixelType;


static void
initializeInvalidColors(struct pam * const pamP,
                        tuple *      const blackColorP,
                        tuple *      const whiteColorP) {
    tuple invalidBlack;
    tuple invalidWhite;

    invalidBlack = pnm_allocpamtuple(pamP);
    invalidBlack[PAM_RED_PLANE] = pamP->maxval/3;
    invalidBlack[PAM_GRN_PLANE] = 0;
    invalidBlack[PAM_BLU_PLANE] = 0;
    *blackColorP = invalidBlack;

    invalidWhite = pnm_allocpamtuple(pamP);
    invalidWhite[PAM_RED_PLANE] = pamP->maxval;
    invalidWhite[PAM_GRN_PLANE] = pamP->maxval*3/4;
    invalidWhite[PAM_BLU_PLANE] = pamP->maxval*3/4;
    *whiteColorP = invalidWhite;
}



static void
pamRowToKnitRow(struct pam *  const pamP,
                const tuple * const pamRow,
                mkPixelType * const knitRow) {

    if (pamP->depth == 3) {
        /* Convert from RGB. */
        unsigned int col;

        for (col = 0; col < pamP->width; ++col) {
            double luminosity;

            luminosity =
                pamRow[col][0]*pnm_lumin_factor[0] +
                pamRow[col][1]*pnm_lumin_factor[1] +
                pamRow[col][2]*pnm_lumin_factor[2];
            if (luminosity < pamP->maxval/2.0)
                knitRow[col] = MK_VALID_BLACK;
            else
                knitRow[col] = MK_VALID_WHITE;
        }
    }
    else {
        /* Convert from either grayscale or black and white. */
        unsigned int col;

        for (col = 0; col < pamP->width; ++col) {
            if (pamRow[col][0]*2 < pamP->maxval)
                knitRow[col] = MK_VALID_BLACK;
            else
                knitRow[col] = MK_VALID_WHITE;
        }
    }
}



static void
knitRowToPamRow(struct pam *        const pamP,
                const mkPixelType * const knitRow,
                tuple *             const pamRow,
                tuple               const invalidBlack,
                tuple               const invalidWhite) {

    tuple        validBlack;
    tuple        validWhite;
    unsigned int col;

    validBlack = pnm_allocpamtuple(pamP);
    pnm_createBlackTuple(pamP, &validBlack);
    validWhite = pnm_allocpamtuple(pamP);
    validWhite[PAM_RED_PLANE] = pamP->maxval;
    validWhite[PAM_GRN_PLANE] = pamP->maxval;
    validWhite[PAM_BLU_PLANE] = pamP->maxval;

    for (col = 0; col < pamP->width; ++col) {
        switch (knitRow[col]) {
          case MK_VALID_BLACK:
              pnm_assigntuple(pamP, pamRow[col], validBlack);
              break;

          case MK_VALID_WHITE:
              pnm_assigntuple(pamP, pamRow[col], validWhite);
              break;

          case MK_INVALID_BLACK:
              pnm_assigntuple(pamP, pamRow[col], invalidBlack);
              break;

          case MK_INVALID_WHITE:
              pnm_assigntuple(pamP, pamRow[col], invalidWhite);
              break;

          default:
            abort();
            break;
        }
    }

    pnm_freepamtuple(validBlack);
    pnm_freepamtuple(validWhite);
}



static void
validateMosaicPattern(struct pam * const inPamP,
                      struct pam * const outPamP) {
/* --------------------------------------------------------------------------
   Validate a mosaic knitting pattern.  A valid pattern starts with a
   "black" row on the bottom and alternates "white" and "black" rows.
   A "black" row can contain any arrangement of black pixels but no
   more than max_skips consecutive white pixels.  A "white" row can
   contain any arrangement of white pixels but no more than max_skips
   consecutive black pixels.  Columns wrap horizontally, so that
   characteristic is taken into consideration when tallying
   consecutive pixels.  Invalid pixels are flagged with a red hue.  It
   is assumed that the input image is fairly small (on the order of a
   few tens of pixels in each dimension), so red pixels should stand
   out fairly well when the image is zoomed in.
--------------------------------------------------------------------------*/

    tuple *       inPamRow;      /* One row of data read from the input file */
    mkPixelType * knitRow;     /* Same as inPamRow but expressed as stitches */
    tuple *       outPamRow;  /* One row of data to write to the output file */
    tuple         invalidBlack; /* Color representing an invalid black input */
    tuple         invalidWhite; /* Color representing an invalid white input */
    mkPixelType   rowColor;     /* Base color of the current row */
    unsigned int  row;

    inPamRow = pnm_allocpamrow(inPamP);
    outPamRow = pnm_allocpamrow(outPamP);
    MALLOCARRAY(knitRow, inPamP->width);
    initializeInvalidColors(outPamP, &invalidBlack, &invalidWhite);

    rowColor = inPamP->height % 2 == 0 ? MK_VALID_WHITE : MK_VALID_BLACK;
    for (row = 0; row < inPamP->height; ++row) {
        unsigned int col;

        pnm_readpamrow(inPamP, inPamRow);
        pamRowToKnitRow(inPamP, inPamRow, knitRow);
        for (col = 0; col < inPamP->width; ++col) {
            if (knitRow[col] != rowColor) {
                unsigned int runLength = 0;  /* Number of consecutive skips */

                for (runLength = 0;
                     runLength < inPamP->width &&
                         knitRow[(col+runLength)%inPamP->width] != rowColor;
                     ++runLength)
                    ;
                if (runLength > max_skips) {
                    /* We have too many skips in a row -- mark them
                       with the "invalid" color. */
                    unsigned int badOffset;
                    mkPixelType  badColor;

                    badColor = rowColor == MK_VALID_WHITE ?
                        MK_INVALID_BLACK : MK_INVALID_WHITE;
                    for (badOffset = 0; badOffset < runLength; ++badOffset) {
                        knitRow[(col+badOffset)%inPamP->width] = badColor;
                    }
                }
                col += runLength - 1;
            }
        }
        knitRowToPamRow(outPamP, knitRow, outPamRow,
                        invalidBlack, invalidWhite);
        pnm_writepamrow(outPamP, outPamRow);
        rowColor = rowColor == MK_VALID_BLACK ?
            MK_VALID_WHITE : MK_VALID_BLACK;
    }

    free(knitRow);
    pnm_freepamrow(outPamRow);
    pnm_freepamrow(inPamRow);
}



int
main(int argc, const char *argv[]) {
    struct pam   inPam;
    struct pam   outPam;
    const char * inputFilename;
    FILE       * inFileP;

    pm_proginit(&argc, argv);

    inputFilename = (argc > 1) ? argv[1] : "-";
    inFileP = pm_openr(inputFilename);

    pnm_readpaminit(inFileP, &inPam, PAM_STRUCT_SIZE(tuple_type));

    outPam = inPam;
    outPam.file = stdout;
    outPam.format = PAM_FORMAT;
    outPam.depth = 3;
    outPam.maxval = 255;
    outPam.bytes_per_sample = 1;
    strcpy(outPam.tuple_type, PAM_PPM_TUPLETYPE);
    pnm_writepaminit(&outPam);

    validateMosaicPattern(&inPam, &outPam);

    pm_closer(inFileP);
    return 0;
}

