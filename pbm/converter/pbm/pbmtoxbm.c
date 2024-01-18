/* pbmtoxbm.c - read a PBM image and produce an X11/X10 bitmap file
**
** Copyright (C) 1988 by Jef Poskanzer.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
*/

/* 2006.10 (afu)   
   Changed bitrow from plain to raw, read function from pbm_readpbmrow() to
   pbm_readpbmrow_packed().  Retired bitwise transformation functions.
 
   Output function putitem rewritten to handle both X10 and X11.

   Added -name option.  There is no check for the string thus given.

*/

#define _BSD_SOURCE 1      /* Make sure strdup() is in string.h */
#define _XOPEN_SOURCE 500  /* Make sure strdup() is in string.h */

#include <assert.h>
#include <string.h>

#include "pm_c_util.h"
#include "pbm.h"
#include "shhopt.h"
#include "mallocvar.h"
#include "bitreverse.h"
#include "nstring.h"


enum xbmVersion { X10, X11 };

struct CmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    const char *    inputFileName;
    const char *    name;
    enum xbmVersion xbmVersion;
};

static void
parseCommandLine(int                 argc, 
                 const char **       argv,
                 struct CmdlineInfo *cmdlineP ) {
/*----------------------------------------------------------------------------
   Parse program command line described in Unix standard form by argc
   and argv.  Return the information in the options as *cmdlineP.  

   If command line is internally inconsistent (invalid options, etc.),
   issue error message to stderr and abort program.

   Note that the strings we return are stored in the storage that
   was passed to us as the argv array.  We also trash *argv.
-----------------------------------------------------------------------------*/
    optEntry * option_def;
    /* Instructions to pm_optParseOptions3 on how to parse our options. */

    optStruct3 opt;
    unsigned int option_def_index;
    unsigned int x10, x11, nameSpec;
    MALLOCARRAY_NOFAIL(option_def, 100);

    option_def_index = 0;   /* incremented by OPTENT3 */

    OPTENT3(0, "name", OPT_STRING, &cmdlineP->name, &nameSpec, 0);
    OPTENT3(0, "x10" , OPT_FLAG,   NULL, &x10, 0);
    OPTENT3(0, "x11" , OPT_FLAG,   NULL, &x11, 0);

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = FALSE;  /* We have no parms that are negative numbers */

    pm_optParseOptions3(&argc, (char **)argv, opt, sizeof(opt), 0);
        /* Uses and sets argc, argv, and some of *cmdlineP and others. */

    if (!nameSpec)
        cmdlineP->name = NULL;
    else if (strlen(cmdlineP->name) > 56)
        pm_error("Image name too long: %d chars. (max 56)",
                 (unsigned)strlen(cmdlineP->name));
    else if (!ISALPHA(cmdlineP->name[0]) && cmdlineP->name[0] !='_')
        pm_error("Image name '%s' starts with non-alphabet character.",
                  cmdlineP->name);
    else {
        unsigned int i;
        for (i = 0 ; i < strlen(cmdlineP->name); ++i)
            if (!ISALNUM(cmdlineP->name[i]) && cmdlineP->name[i] != '_')
                pm_error("Image name '%s' contains invalid character (%c).",
                         cmdlineP->name, cmdlineP->name[i]);
    }
    
    if (x10 && x11)
        pm_error("You can't specify both -x10 and -x11");
    else if (x10)
        cmdlineP->xbmVersion = X10;
    else 
        cmdlineP->xbmVersion = X11;
        
    if (argc-1 < 1) 
        cmdlineP->inputFileName = "-";
    else {
        cmdlineP->inputFileName = argv[1];
        
        if (argc-1 > 1)
            pm_error("Program takes zero or one argument (filename).  You "
                     "specified %u", argc-1);
    }
    free(option_def);
}



static void
generateName(char          const filenameArg[],
             const char ** const nameP) {
/*----------------------------------------------------------------------------
   Generate a name for the image to put in the bitmap file.  Derive it from
   the filename argument filenameArg[] and return it as a null-terminated
   string in newly malloc'ed space at *nameP.

   We take the part of the name after the rightmost slash
   (i.e. filename without the directory path part), stopping before
   any period.  We convert any punctuation to underscores.

   If the argument is "-", meaning standard input, we return the name
   "noname".  Also, if the argument is null or ends in a slash, we
   return "noname".
-----------------------------------------------------------------------------*/
    if (streq(filenameArg, "-"))
        *nameP = strdup("noname");
    else {
        int nameIndex, argIndex;
        /* indices into the input and output buffers */

        /* Start just after the rightmost slash, or at beginning if no slash */
        if (strrchr(filenameArg, '/') == 0) 
            argIndex = 0;
        else argIndex = strrchr(filenameArg, '/') - filenameArg + 1;

        if (filenameArg[argIndex] == '\0') 
            *nameP = strdup("noname");
        else {
            char * name;
            nameIndex = 0;  /* Start at beginning of name buffer */

            name = malloc(strlen(filenameArg));
    
            while (filenameArg[argIndex] != '\0' 
                   && filenameArg[argIndex] != '.') {
                const char filenameChar = filenameArg[argIndex++];
                name[nameIndex++] = 
                    ISALNUM(filenameChar) ? filenameChar : '_';
            }
            name[nameIndex] = '\0';
            *nameP = name;
        }
    }
}



static unsigned short int itemBuff[22];
static int itemCnt;    /* takes values 0 to 15 (x11) or 21 (x10) */
static enum xbmVersion itemVersion;



static void
putitemX10(unsigned char const item) {

    if (itemCnt == 22) {
        /* Buffer is full.  Write out one line. */
        int rc;
        rc = printf(" 0x%02x%02x,0x%02x%02x,0x%02x%02x,0x%02x%02x,"
                    "0x%02x%02x,0x%02x%02x,0x%02x%02x,0x%02x%02x,"
                    "0x%02x%02x,0x%02x%02x,0x%02x%02x,\n",
                    itemBuff[ 1], itemBuff[ 0], itemBuff[ 3], itemBuff[ 2],
                    itemBuff[ 5], itemBuff[ 4], itemBuff[ 7], itemBuff[ 6],
                    itemBuff[ 9], itemBuff[ 8], itemBuff[11], itemBuff[10],
                    itemBuff[13], itemBuff[12], itemBuff[15], itemBuff[14],
                    itemBuff[17], itemBuff[16], itemBuff[19], itemBuff[18],
                    itemBuff[21], itemBuff[20]
            );

        if (rc < 0)        
            pm_error("Error writing X10 bitmap raster item.  "
                     "printf() failed with errno %d (%s)",
                     errno, strerror(errno));
        
        itemCnt = 0;
    }
    itemBuff[itemCnt++] = bitreverse[item];
}



static void
putitemX11(unsigned char const item) {

    if (itemCnt == 15 ) {
        /* Buffer is full.  Write out one line. */
        int rc;
        rc = printf(" 0x%02x,0x%02x,0x%02x,0x%02x,"
                    "0x%02x,0x%02x,0x%02x,0x%02x,"
                    "0x%02x,0x%02x,0x%02x,0x%02x,"
                    "0x%02x,0x%02x,0x%02x,\n",
                    itemBuff[0], itemBuff[1], itemBuff[2], itemBuff[3],
                    itemBuff[4], itemBuff[5], itemBuff[6], itemBuff[7],
                    itemBuff[8], itemBuff[9], itemBuff[10],itemBuff[11],
                    itemBuff[12],itemBuff[13],itemBuff[14]
            );
        if (rc < 0)        
            pm_error("Error writing X11 bitmap raster item.  "
                     "printf() failed with errno %d (%s)",
                     errno, strerror(errno));
        
        itemCnt = 0;
    }
    itemBuff[itemCnt++] = bitreverse[item];
}



static void
putitem(unsigned char const item) {

    switch (itemVersion) {
    case X10: putitemX10(item); break;
    case X11: putitemX11(item); break;
    }
}



static void
puttermX10(void) {

    unsigned int i;

    assert(itemCnt % 2 == 0);

    for (i = 0; i < itemCnt; i += 2) {
        int rc;

        assert(i + 1 < itemCnt);

        rc = printf("%s0x%02x%02x%s",
                    (i == 0) ? " " : "",
                    itemBuff[i+1],
                    itemBuff[i], 
                    (i + 2 >= itemCnt) ? "" : ",");
        if (rc < 0)        
            pm_error("Error writing Item %u at end of X10 bitmap raster.  "
                     "printf() failed with errno %d (%s)",
                     i, errno, strerror(errno));
    }
}



static void
puttermX11(void) {

    unsigned int i;

    for (i = 0; i < itemCnt; ++i) {
        int rc;

        rc = printf("%s0x%02x%s",
                    (i == 0)  ? " " : "",
                    itemBuff[i],
                    (i + 1 >= itemCnt) ? "" : ",");

        if (rc < 0)        
            pm_error("Error writing Item %u at end of X11 bitmap raster.  "
                     "printf() failed with errno %d (%s)",
                     i, errno, strerror(errno));
    }
}



static void
putinit(enum xbmVersion const xbmVersion) {

    itemCnt = 0;
    itemVersion = xbmVersion;
}



static void
putterm(void) {

    switch (itemVersion) {
    case X10: puttermX10(); break;
    case X11: puttermX11(); break;
    }

    {
        int rc;

        rc = printf("};\n");

        if (rc < 0)        
            pm_error("Error writing end of X11 bitmap raster.  "
                     "printf() failed with errno %d (%s)",
                     errno, strerror(errno));
    }
}



static void
writeXbmHeader(enum xbmVersion const xbmVersion,
               const char *    const name,
               unsigned int    const width,
               unsigned int    const height,
               FILE *          const ofP) {

    printf("#define %s_width %u\n", name, width);
    printf("#define %s_height %u\n", name, height);
    printf("static %s %s_bits[] = {\n",
           xbmVersion == X10 ? "short" : "char",
           name);
}



static void
convertRaster(FILE *          const ifP,
              unsigned int    const cols,
              unsigned int    const rows,
              int             const format,
              FILE *          const ofP,
              enum xbmVersion const xbmVersion) {
              
    unsigned int const bitsPerUnit = xbmVersion == X10 ? 16 : 8;   
    unsigned int const padright = ROUNDUP(cols, bitsPerUnit) - cols;
        /* Amount of padding to round cols up to the nearest multiple of 
           8 (if x11) or 16 (if x10).
        */
    unsigned int const bitrowBytes = (cols + padright) / 8;

    unsigned char * bitrow;
    unsigned int row;

    putinit(xbmVersion);

    bitrow = pbm_allocrow_packed(cols + padright);
    
    for (row = 0; row < rows; ++row) {
        unsigned int i;

        pbm_readpbmrow_packed(ifP, bitrow, cols, format);
        pbm_cleanrowend_packed(bitrow, cols);

        if (padright >= 8) {
            assert(bitrowBytes > 0);
            bitrow[bitrowBytes-1] = 0x00;
        }
        for (i = 0; i < bitrowBytes; ++i)
            putitem(bitrow[i]);
    }

    putterm();

    pbm_freerow(bitrow);
}



int
main(int           argc,
     const char ** argv) {

    struct CmdlineInfo cmdline; 
    FILE * ifP;
    int rows, cols, format;
    const char * name;

    pm_proginit(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);
    if (cmdline.name == NULL) 
        generateName(cmdline.inputFileName, &name);
    else
        name = strdup(cmdline.name);

    ifP = pm_openr(cmdline.inputFileName);
    
    pbm_readpbminit(ifP, &cols, &rows, &format);
    
    writeXbmHeader(cmdline.xbmVersion, name, cols, rows, stdout);

    convertRaster(ifP, cols, rows, format, stdout, cmdline.xbmVersion);

    pm_strfree(name);
    pm_close(ifP);

    return 0;
}



