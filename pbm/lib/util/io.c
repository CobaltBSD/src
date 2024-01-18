#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "mallocvar.h"
#include "nstring.h"

#include "io.h"


void
pm_freadline(FILE *        const fileP,
             const char ** const lineP,
             const char ** const errorP) {
/*----------------------------------------------------------------------------
   Read a line (assuming the file is text with lines delimited by newlines)
   from file *fileP.  Return that line in newly malloced storage as *lineP.

   The newline delimiter is not part of the line.

   As a special case, if the file doesn't end in a newline, the characters
   after the last newline are a line.

   If there are no more lines in the file, return *lineP == NULL.
-----------------------------------------------------------------------------*/
    char * buffer;
    size_t bufferSize;
    size_t cursor;
    bool gotLine;
    bool eof;

    bufferSize = 1024;  /* initial value */
    *errorP = NULL; /* initial value */
    
    MALLOCARRAY(buffer, bufferSize);

    for (cursor = 0, gotLine = false, eof = false;
         !gotLine && !eof && !*errorP; ) {
        if (cursor + 1 >= bufferSize) {
            if (bufferSize > INT_MAX/2) {
                free(buffer);
                buffer = NULL;
            } else {
                bufferSize *= 2;
                REALLOCARRAY(buffer, bufferSize);
            }
        }

        if (!buffer)
            pm_asprintf(errorP,
                        "Couldn't get memory for a %u-byte file read buffer.",
                        (unsigned int)bufferSize);
        else {
            int const rc = getc(fileP);
        
            if (rc < 0) {
                if (feof(fileP))
                    eof = true;
                else
                    pm_asprintf(errorP,
                                "Failed to read a character from file.  "
                                "Errno = %d (%s)",
                                errno, strerror(errno));
            } else {
                char const c = (char)rc;

                if (c == '\n')
                    gotLine = true;
                else {
                    buffer[cursor++] = c;
                }
            }
        }
    }
    if (*errorP) {
        if (buffer)
            free(buffer);
    } else {
        if (eof && cursor == 0) {
            *lineP = NULL;
            free(buffer);
        } else {
            assert(cursor < bufferSize);
            buffer[cursor++] = '\0';

            *lineP = buffer;
        }
    }
}


