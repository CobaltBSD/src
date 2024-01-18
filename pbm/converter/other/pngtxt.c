#define HAVE_PNGLIB_WITH_ITXT 0

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <png.h>

#include "mallocvar.h"
#include "nstring.h"
#include "pngx.h"
#include "pngtxt.h"
#include "pm.h"



static void
readToken(char           const textline[],
          unsigned int   const lineLength,
          unsigned int * const cursorP,
          const char **  const tokenP) {
/*----------------------------------------------------------------------------
   Read a token from 'textline' (whose length is 'lineLength'), assuming the
   cursor is positioned to it now, leaving the cursor positioned after it.

   Tokens are delimited by white space.  We don't skip any white space before
   or after the token.  Ergo, if we are positioned to white space right now,
   the token we read is a null string.
-----------------------------------------------------------------------------*/
    char * tokenBuffer;
    char * cp;
    unsigned int cursor;

    cursor = *cursorP;
    
    MALLOCARRAY(tokenBuffer, lineLength + 1);
    /* leave room for terminating NUL */
    if (tokenBuffer == NULL) 
        pm_error("Unable to allocate memory for a %u-character "
                 "text string file line", lineLength);

    cp = &tokenBuffer[0];  /* initial value */
    
    if (textline[0] == '"') {
        ++cursor;  /* skip past opening quotation mark */
        while (textline[cursor] != '"') {
            if (cursor >= lineLength)
                pm_error("Invalid text string file format.  Line ends in "
                         "the middle of a quoted token.  Text at the end of "
                         "the line is '%s'", tokenBuffer);
            if (textline[cursor] == '\0')
                pm_error("Invalid text string file format:  Token contains "
                         "a NUL character.  Text leading up to the NUL "
                         "character is '%s'", tokenBuffer);
            *(cp++) = textline[cursor++];
        }
        ++cursor;  /* skip past closing quotation mark */
    } else {
        while ((cursor < lineLength) && 
               (textline[cursor] != ' ') && (textline[cursor] != '\t')) {
            
            if (textline[cursor] == '\0')
                pm_error("Invalid text string file format:  Token contains "
                         "a NUL character.  Text leading up to the NUL "
                         "character is '%s'", tokenBuffer);
            *(cp++) = textline[cursor++];
        }
    }
    *cp++ = '\0';

    *cursorP = cursor;

    *tokenP = tokenBuffer;
}




static void
skipWhiteSpace(char           const textline[],
               unsigned int   const lineLength,
               unsigned int * const cursorP) {
/*----------------------------------------------------------------------------
   Move *cursorP past white space (or, for some reason, NUL characters),
   in 'textline', which is 'lineLength' long.
-----------------------------------------------------------------------------*/
    unsigned int cursor;

    cursor = *cursorP;  /* initial value */

    while (cursor < lineLength && 
           (textline[cursor] == ' ' || textline[cursor] == '\t' ||
            textline[cursor] == '\0'))
        ++cursor;

    *cursorP = cursor;
}



static void
readTextString(char          const textline[],
               unsigned int  const lineLength,
               unsigned int  const startPos,
               png_charp *   const textStringP,
               png_size_t *  const textStringLengthP) {
/*----------------------------------------------------------------------------
  Extract the text string at 'startPos' in the buffer 'textline', whose
  length is 'lineLength'.  Return it in newly malloced storage with a
  pointer to that storage as 'textString' and the size of the text as
  *textStringLengthP.
-----------------------------------------------------------------------------*/
    char * cp;

    MALLOCARRAY(cp, lineLength + 1);  /* incl '\0' */
    if (!cp) 
        pm_error("Unable to allocate memory for text chunks");

    memcpy(cp, textline + startPos, lineLength - startPos);
    cp[lineLength - startPos] = '\0';  /* for safety - not part of text */
    *textStringP = cp;
    *textStringLengthP = lineLength - startPos;
}



static void
startTextChunkEngl(png_text *   const textChunkP, 
                   char         const textline[],
                   unsigned int const lineLength,
                   bool         const isCompressed,
                   bool         const verbose) {
/*----------------------------------------------------------------------------
   Assuming 'textline' is the first line of an entry in an English text
   string file, put the information from it in the comment record *textChunkP.
   Use the text on this line as the comment text, even though the true text
   string may include text from subsequent continuation lines as well.

   'textline' is not NUL-terminated.  Its length is 'lineLength', and it is at
   least one character long.  'textline' does not contain a newline character.

   'isCompressed' means it is a compressed text chunk.
-----------------------------------------------------------------------------*/
    unsigned int cursor;

    cursor = 0;

    {
        const char * key;

        readToken(textline, lineLength, &cursor, &key);

        pngx_setTextKey(textChunkP, key);

        pm_strfree(key);
    }

    skipWhiteSpace(textline, lineLength, &cursor);

    pngx_setTextLang(textChunkP, NULL);

    readTextString(textline, lineLength, cursor, &textChunkP->text,
                   &textChunkP->text_length);

    textChunkP->compression =
        isCompressed ? PNG_TEXT_COMPRESSION_zTXt : PNG_TEXT_COMPRESSION_NONE;
}



static void
startTextChunkIntl(png_text *   const textChunkP, 
                   char         const textline[],
                   unsigned int const lineLength,
                   bool         const isCompressed,
                   bool         const verbose) {
/*----------------------------------------------------------------------------
  Assuming 'textline' is the first line of an entry in an international (not
  English) text string file, put the information from it in the text chunk
  *textChunkP.  Use the text on this line as the text string, even though the
  true text string may include text from subsequent continuation lines as
  well.

  'textline' is not NUL-terminated.  Its length is 'lineLength', and it is at
  least one character long.  'textline' does not contain a newline character.

  'isInternational' means it is an international (i.e. non-English) text
  chunk.

  Leave the language attribute (textChunkP->lang) unset.
-----------------------------------------------------------------------------*/
    unsigned int cursor;

    cursor = 0;  /* Initial value */

    {
        const char * key;

        readToken(textline, lineLength, &cursor, &key);

        pngx_setTextKey(textChunkP, key);

        pm_strfree(key);
    }

    skipWhiteSpace(textline, lineLength, &cursor);

    {
        const char * isoLang;

        readToken(textline, lineLength, &cursor, &isoLang);

        pngx_setTextLang(textChunkP, isoLang);

        pm_strfree(isoLang);
    }

    skipWhiteSpace(textline, lineLength, &cursor);

    {
        const char * langKey;
    
        readToken(textline, lineLength, &cursor, &langKey);

        pngx_setTextLangKey(textChunkP, langKey);

        pm_strfree(langKey);
    }

    skipWhiteSpace(textline, lineLength, &cursor);

    /* Beginning of text string (continuation lines may follow) */
    readTextString(textline, lineLength, cursor, &textChunkP->text,
                   &textChunkP->text_length);

    textChunkP->compression = 
        isCompressed ? PNG_ITXT_COMPRESSION_zTXt :PNG_ITXT_COMPRESSION_NONE;
}



static void
continueTextString(png_text *   const textChunkP, 
                   char         const textline[],
                   unsigned int const lineLength) {
/*----------------------------------------------------------------------------
   Update the text chunk *textChunkP by adding to it the text from
   textline[], which is a continuation line from a text string file.

   'textline' is not NUL-terminated.  Its length is 'lineLength', and
   it is at least one character long.  'textline' does not contain a
   newline character.
-----------------------------------------------------------------------------*/
    unsigned int cursor;  /* cursor into textline[] */

    unsigned int const newTextLength =
        textChunkP->text_length + lineLength + 1 + 1;

    REALLOCARRAY(textChunkP->text, newTextLength);

    if (textChunkP->text == NULL)
        pm_error("Unable to allocate %u bytes of memory for text string",
                 newTextLength);

    textChunkP->text[textChunkP->text_length++] = '\n';

    cursor = 0; 

    skipWhiteSpace(textline, lineLength, &cursor);

    memcpy(textChunkP->text + textChunkP->text_length,
           textline + cursor,
           lineLength - cursor);

    textChunkP->text_length += lineLength - cursor;

    textChunkP->text[textChunkP->text_length] = '\0';  /* for safety */
}



static void
getFileLine(FILE *         const fileP, 
            const char **  const textP, 
            unsigned int * const lengthP) {
/*----------------------------------------------------------------------------
   Read the next line (characters from current position through the first
   newline character) and return it.  Put the text in newly malloc'ed 
   storage.

   Do not include the newline.

   Add a terminating NUL for safety, but note that you can't rely on this
   as the end of line marker because the line may contain a NUL.  *lengthP
   does not include the NUL that we add.

   If there are no more characters in the file, return NULL.
-----------------------------------------------------------------------------*/
    char * textline;  /* malloc'ed */
    unsigned int cursor;  /* cursor into textline[] */
    unsigned int allocatedSz;
        /* The number of characters of space that are allocated for
           'textline' 
        */
    bool eol;
    bool gotSomething;

    allocatedSz = 128;  /* initial value */

    MALLOCARRAY(textline, allocatedSz);
    if (textline == NULL)
        pm_error("Unable to allocate buffer to read a line of a file.");
    
    cursor = 0;
    eol = FALSE;
    gotSomething = FALSE;

    while (!eol) {
        int const c = getc(fileP);
        
        if (c != EOF)
            gotSomething = TRUE;

        if (c == '\n' || c == EOF)
            eol = TRUE;
        else {
            /* leave space for safety NUL */
            if (cursor > allocatedSz - 1 - 1) {
                allocatedSz *= 2;
                REALLOCARRAY(textline, allocatedSz);
                if (textline == NULL)
                    pm_error("Unable to allocate buffer to read a line of "
                             "a file.");
            }
            textline[cursor++] = c;
        }
    }
    textline[cursor] = '\0';  /* For safety; not part of line */

    if (gotSomething) {
        *textP = textline;
        *lengthP = cursor;
    } else {
        free(textline);
        *textP = NULL;
    }
}



static void
handleArrayAllocation(png_text **    const arrayP,
                      unsigned int * const allocatedChunkCtP,
                      unsigned int   const chunkIdx) {

    if (chunkIdx >= *allocatedChunkCtP) {
        *allocatedChunkCtP *= 2;
        REALLOCARRAY(*arrayP, *allocatedChunkCtP);
        if (*arrayP == NULL) 
            pm_error("unable to allocate memory for %u text chunks",
                *allocatedChunkCtP);
    }
}



static bool
isContinuationLine(const char * const line) {
/*----------------------------------------------------------------------------
   Text line 'line', if it is from a text string file, is a continuation of a
   text string started in an earlier line.

   What identifies a line as a continuation line is that it starts with
   a space or tab.
-----------------------------------------------------------------------------*/
    return line[0] == ' ' || line[0] == '\t';
}



static void
reportChunkCt(bool         const ztxt,
              bool         const itxt,
              unsigned int const chunkCt) {

    const char * chunkType;

    if (itxt)
        chunkType = "iTXt";
    else {
        if (ztxt)
            chunkType = "zTXt";
        else
            chunkType = "tEXt";
    }

    pm_message("Writing %u %s chunks", chunkCt, chunkType);
}



/******************************************************************************
                            EXTERNAL SUBROUTINES
******************************************************************************/


void 
pngtxt_addChunk(struct pngx * const pngxP,
                FILE *        const tfP, 
                bool          const ztxt,
                bool          const itxt,
                bool          const verbose) {
/*----------------------------------------------------------------------------
   Add text chunks (tEXt, zTXt, or iTXt) to the PNG image represented by
   *pngxP as directed by file *tfP.

   'itxt' means to make them international language (iTXt) chunks.  Otherwise
   they are either tEXt or zTXt chunks, depending upon 'ztxt'.

   'ztxt' means to make the text compressed.  If the chunks are not
   international (i.e. 'itxt' is false), this means the chunks are zTXt chunks
   instead of 'tEXt' chunks.
-----------------------------------------------------------------------------*/
    bool noChunksYet;
    bool eof;
    png_textp text;  /* An array; one chunk per element */
    unsigned int chunkCt;
        /* Number of chunks we have completed in the 'text' array */
    unsigned int allocatedChunkCt;
        /* Number of entries currently allocated for the PNG text array */

    /* In an international text string file, the first entry tells the
       language of all of the chunks, by having key 'Language'.
    */

    allocatedChunkCt = 256;  /* initial value */

    MALLOCARRAY(text, allocatedChunkCt);
    if (text == NULL) 
        pm_error("unable to allocate memory for text chunk array");

    for (chunkCt = 0, noChunksYet = true, eof = false; !eof; ) {
        const char * textline;
        unsigned int lineLength;

        getFileLine(tfP, &textline, &lineLength);
        if (textline == NULL)
            eof = true;
        else {
            if (lineLength == 0) {
                /* skip this empty line */
            } else {
                handleArrayAllocation(&text, &allocatedChunkCt, chunkCt);

                if (!isContinuationLine(textline)) {
                    png_text * textChunkP;

                    if (noChunksYet) {
                        /* No previous chunk to move past */
                    } else
                        ++chunkCt;
                    noChunksYet = false;
                    
                    textChunkP = &text[chunkCt];
                
                    if (itxt)
                        startTextChunkIntl(textChunkP, 
                                           textline, lineLength, ztxt,
                                           verbose);
                    else
                        startTextChunkEngl(textChunkP, 
                                           textline, lineLength, ztxt,
                                           verbose);
                } else {
                    png_text * const textChunkP = &text[chunkCt];

                    /* Line starts with whitespace, which means it is
                       a continuation of the current text string.
                    */
                    if (noChunksYet)
                        pm_error("Invalid text string file format: "
                                 "first line is a continuation line! "
                                 "(It starts with whitespace)");
                    continueTextString(textChunkP, textline, lineLength);
                }
            }
            pm_strfree(textline);
        }
    }
    if (!noChunksYet)
        ++chunkCt;

    if (verbose)
        reportChunkCt(ztxt, itxt, chunkCt);

    if (chunkCt > 0)
        pngx_setText(pngxP, text, chunkCt);

    free(text);
}



