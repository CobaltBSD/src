/*
 *
 * Copyright (C) 1997 Eric A. Howe
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *   Authors:  Eric A. Howe (mu@trends.net)
 *             Bryan Henderson, 2010
 */
#define _XOPEN_SOURCE 500  /* Make sure strdup() is in string.h */
#define _BSD_SOURCE   /* Ensure strdup() is in <string.h> */
#include <assert.h>
#include <time.h>
#include <string.h>

#include "mallocvar.h"
#include "nstring.h"
#include "ipdb.h"

typedef uint32_t pilot_time_t;




static unsigned int
imgPpb(IMAGE * const imgP) {
/*----------------------------------------------------------------------------
   Pixels per byte
-----------------------------------------------------------------------------*/
    return
        imgP->type == IMG_GRAY   ? 4 :
        imgP->type == IMG_GRAY16 ? 2 :
        8;
}



unsigned int
ipdb_img_ppb(IMAGE * const imgP) {
/*----------------------------------------------------------------------------
   Pixels per byte
-----------------------------------------------------------------------------*/
    return imgPpb(imgP);
}



size_t
ipdb_img_size(IMAGE * const imgP) {
/*----------------------------------------------------------------------------
  Size (in bytes) of an image's data.
-----------------------------------------------------------------------------*/
    return (size_t)(imgP->width / imgPpb(imgP) * imgP->height);
}



/*
 * Return the start of row `r'.
 */
 uint8_t *
 ipdb_img_row(IMAGE *      const imgP,
              unsigned int const row) {

     return &imgP->data[(row) * imgP->width / imgPpb(imgP)];
 }



 #define img_row(i, r)   

 static pilot_time_t const unixepoch = (66*365+17)*24*3600;
     /* The unix epoch in Mac time (the Mac epoch is 00:00 UTC 1904.01.01).
        The 17 is the number of leap years.
     */

 static const char * const errorDesc[] = {
     /* E_BADCOLORS      */
     "Invalid palette, only {0x00, 0x55, 0xAA, 0xFF} allowed.",

     /* E_NOTIMAGE       */
     "Not an image file.",

     /* E_IMAGETHERE     */
     "Image record already present, logic error.",

     /* E_IMAGENOTTHERE  */
     "Image record required before text record, logic error.",

     /* E_TEXTTHERE      */
     "Text record already present, logic error.",

     /* E_NOTRECHDR      */
     "Invalid record header encountered.",

     /* E_UNKNOWNRECHDR  */
     "Unknown record header.",

     /* E_TOOBIGG        */
     "Image too big, maximum size approx. 640*400 gray pixels.",

     /* E_TOOBIGM        */
     "Image too big, maximum size approx. 640*800 monochrome pixels.",
 };



 const char *
 ipdb_err(int const e) {

     if (e < 0)
         return e >= E_LAST ? errorDesc[-e - 1] : "unknown error";
     else
         return strerror(e);
 }



 static void
 rechdr_free(RECHDR * const recP) {

     if (recP) {
         free(recP->extra);
         free(recP);
     }
 }



 void
 ipdb_image_free(IMAGE * const imgP) {

     if (imgP) {
         rechdr_free(imgP->r);
         free(imgP->data);
         free(imgP);
     }
 }



 void
 ipdb_text_free(TEXT * const textP) {

     if (textP) {
         rechdr_free(textP->r);
         free(textP->data);
         free(textP);
     }
 }



 void
 ipdb_pdbhead_free(PDBHEAD * const headP) {

     free(headP);
 }



 void
 ipdb_clear(IPDB * const pdbP) {
     
     if (pdbP) {
         ipdb_image_free(pdbP->i);
         ipdb_text_free(pdbP->t);
         ipdb_pdbhead_free(pdbP->p);
    }
}



void
ipdb_free(IPDB * const pdbP) {

    ipdb_clear(pdbP);
    free(pdbP);
}



PDBHEAD *
ipdb_pdbhead_alloc(const char * const name) {

    PDBHEAD * pdbHeadP;

    MALLOCVAR(pdbHeadP);

    if (pdbHeadP) {
        MEMSZERO(pdbHeadP);

        STRSCPY(pdbHeadP->name, name == NULL ? "unnamed" : name);

        /*
         * All of the Image Viewer pdb files that I've come across have
         * 3510939142U (1997.08.16 14:38:22 UTC) here.  I don't know where
         * this bizarre date comes from but the real date works fine so
         * I'm using it.
         */
        pdbHeadP->ctime =
            pdbHeadP->mtime = (pilot_time_t)time(NULL) + unixepoch;
        
        MEMSCPY(&pdbHeadP->type, IPDB_vIMG);
        MEMSCPY(&pdbHeadP->id,   IPDB_View);
    }
    return pdbHeadP;
}



static RECHDR *
rechdr_alloc(int      const type,
             uint32_t const offset) {

    /*
     * We never produce the `extra' bytes (we only read them from a file)
     * so there is no point allocating them here.
     */

    RECHDR  * recHdrP;

    MALLOCVAR(recHdrP);
    
    if (recHdrP) {
        MEMSSET(recHdrP, 0);

        recHdrP->offset   = offset;
        recHdrP->rec_type = (uint8_t)(0xff & type);
        MEMSCPY(&recHdrP->unknown, IPDB_MYST);
    }
    return recHdrP;
}



/*
 * The offset will be patched up as needed elsewhere.
 */
#define IMGOFFSET   (PDBHEAD_SIZE + 8)



IMAGE *
ipdb_image_alloc(const char * const name,
            int          const type,
            int          const w,
            int          const h) {

    bool failed;
    IMAGE * imgP;

    failed = false;

    MALLOCVAR(imgP);

    if (imgP) {
        MEMSZERO(imgP);

        STRSCPY(imgP->name, name == NULL ? "unnamed" : name);
        imgP->type     = type;
        imgP->x_anchor = 0xffff;
        imgP->y_anchor = 0xffff;
        imgP->width    = w;
        imgP->height   = h;

        imgP->r = rechdr_alloc(IMG_REC, IMGOFFSET);

        if (imgP->r) {
            if (w != 0 && h != 0) {
                MALLOCARRAY(imgP->data, w * h);

                if (imgP->data) {
                    memset(imgP->data, 0, sizeof(*(imgP->data)) * w * h);
                } else
                    failed = true;
            }
            if (failed)
                rechdr_free(imgP->r);
        } else
            failed = true;
        
        if (failed)
            ipdb_image_free(imgP);
    } else 
        failed = true;

    return failed ? NULL : imgP;
}



TEXT *
ipdb_text_alloc(const char * const content) {

    TEXT * textP;
    bool failed;

    failed = false;
    /*
     * The offset will be patched up later on when we know what it
     * should be.
     */

    MALLOCVAR(textP);

    if (textP) {
        MEMSZERO(textP);

        textP->r = rechdr_alloc(TEXT_REC, 0);

        if (textP->r) {
            if (content) {
                textP->data = strdup(content);

                if (!textP->data)
                    failed = true;
            }
            if (failed)
                rechdr_free(textP->r);
        } else
            failed = true;

        if (failed)
            ipdb_text_free(textP);
    } else
        failed = true;

    return failed ? NULL : textP;
}



IPDB *
ipdb_alloc(const char * const name) {

    IPDB * pdbP;
    bool failed;

    failed = false;

    MALLOCVAR(pdbP);

    if (pdbP) {
        MEMSZERO(pdbP);

        if (name) {
            pdbP->p = ipdb_pdbhead_alloc(name);

            if (!pdbP->p)
                failed = true;
        }
        if (failed)
            ipdb_free(pdbP);
    } else
        failed = true;

    return failed ? NULL : pdbP;
}



const char *
ipdb_typeName(uint8_t const type) {

    switch (type) {
    case IMG_GRAY16: return "16 Bit Grayscale"; break;
    case IMG_GRAY: return "Grayscale"; break;
    case IMG_MONO: return "Monochrome"; break;
    default: return "???";
    }
}
