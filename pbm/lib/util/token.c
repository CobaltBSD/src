#include <stdlib.h>
#include <assert.h>

#include "nstring.h"

#include "token.h"


void
pm_gettoken(const char *  const tokenStart,
            char          const delimiter,
            const char ** const tokenP,
            const char ** const nextP,
            const char ** const errorP) {
/*----------------------------------------------------------------------------
   Find the token starting at 'tokenStart' up to but not including
   the first 'delimiter' character or end of string.  Return it in newly
   malloced memory as *tokenP, NUL-terminated.

   Make *nextP point just past the token, i.e. to the delimiter or
   end of string NUL character.

   Note that if the string is empty, or starts with the delimiter,
   we return an empty string and *nextP == tokenStart, i.e. *nextP
   doesn't necessarily advance.
-----------------------------------------------------------------------------*/
    char * token;
    const char * cursor;
    unsigned int charCount;

    /* Run through the token, counting characters */

    charCount = 0;        /* initial value */
    cursor = tokenStart;  /* initial value */
    *errorP = NULL;       /* initial value */

    while (*cursor != delimiter && *cursor != '\0' && !*errorP) {
        if (*cursor == '\\') {
            ++cursor;
            if (*cursor == '\0')
                pm_asprintf(errorP,
                            "string ends with an escape character (\\)");
        } else {
            ++cursor;
            ++charCount;
        }
    }
    if (!*errorP) {
        token = malloc(charCount + 1);
        if (token == NULL)
            pm_asprintf(errorP, "Could not allocate %u bytes of memory "
                        "to parse a string",
                        charCount + 1);
        else {
            /* Go back and do it again, this time copying the characters */
            charCount = 0;
            cursor = tokenStart;

            while (*cursor != delimiter && *cursor != '\0') {
                if (*cursor == '\\')
                    ++cursor;

                assert(*cursor != '\0');

                token[charCount++] = *cursor++;
            }
            token[charCount] = '\0';
            
            *tokenP = token;
            *nextP = cursor;
        }
    }
}







