#ifndef TOKEN_H_INCLUDE
#define TOKEN_H_INCLUDE

void
pm_gettoken(const char *  const tokenStart,
            char          const delimiter,
            const char ** const tokenP,
            const char ** const nextP,
            const char ** const errorP);

#endif
