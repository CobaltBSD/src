/*
 * pbmtextps.c -  render text into a bitmap using a postscript interpreter
 *
 * Copyright (C) 2002 by James McCann.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted, provided
 * that the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation.  This software is provided "as is" without express or
 * implied warranty.
 *
 * PostScript is a registered trademark of Adobe Systems International.
 *
 * Additions by Bryan Henderson contributed to public domain by author.
 *
 */
#define _XOPEN_SOURCE   /* Make sure popen() is in stdio.h */
#define _BSD_SOURCE     /* Make sure stdrup() is in string.h */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "pm_c_util.h"
#include "mallocvar.h"
#include "nstring.h"
#include "shhopt.h"
#include "pbm.h"


#define BUFFER_SIZE 2048

struct cmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    unsigned int res;         /* resolution, DPI */
    unsigned int fontsize;    /* Size of font in points */
    const char * font;      /* Name of postscript font */
    float        stroke;
        /* Width of stroke in points (only for outline font) */
    unsigned int verbose;
    const char * text;
};



static void
writeFileToStdout(const char * const fileName){
    /* simple pbmtopbm */

    FILE * ifP;
    int format;
    int cols, rows, row ;
    unsigned char * bitrow; 
    
    ifP = pm_openr(fileName);
    pbm_readpbminit(ifP, &cols, &rows, &format);

    if (cols==0 || rows==0 || cols>INT_MAX-10 || rows>INT_MAX-10)
      pm_error("Abnormal output from gs program.  "
               "width x height = %u x %u", cols, rows);
               
    pbm_writepbminit(stdout, cols, rows, 0);           
               
    bitrow = pbm_allocrow_packed(cols);
    
    for (row = 0; row < rows; ++row) {
        pbm_readpbmrow_packed(ifP, bitrow, cols, format);
        pbm_writepbmrow_packed(stdout, bitrow, cols, 0);
    }
    pbm_freerow_packed(bitrow);
}



static void
validateFontName(const char * const name) {
/*-----------------------------------------------------------------------------
  Validate font name string.

  Abort with error message if it contains anything other than the printable
  characters in the ASCII 7-bit range, or any character with a special meaning
  in PostScript.
-----------------------------------------------------------------------------*/
    unsigned int idx;

    for (idx = 0; name[idx] != '\0'; ++idx) {
        char const c = name[idx]; 

        if (c < 32 || c > 125)
            pm_error("Invalid character in font name");
        else 
            switch (c) {
              case '[':   case ']':   case '(':   case ')':
              case '{':   case '}':   case '/':   case '\\':
              case '<':   case '>':   case '%':   case ' ':
              case '@':
                pm_error("Invalid character in font name");
            }
    }
}



static void
asciiHexEncode(char *          const inbuff,
               char *          const outbuff) {
/*-----------------------------------------------------------------------------
  Convert the input text string to ASCII-Hex encoding.

  Examples: "ABC abc 123" -> <4142432061626320313233>
            "FOO(BAR)FOO" -> <464f4f2842415229464f4f>
-----------------------------------------------------------------------------*/
    char const hexits[16] = "0123456789abcdef";

    unsigned int idx;

    for (idx = 0; inbuff[idx] != '\0'; ++idx) {
        unsigned int const item = (unsigned char) inbuff[idx]; 

        outbuff[idx*2]   = hexits[item >> 4];
        outbuff[idx*2+1] = hexits[item & 0xF];
    }

    outbuff[idx * 2] = '\0';
}



static void
buildTextFromArgs(int           const argc,
                  char **       const argv,
                  const char ** const asciiHexTextP) {
/*----------------------------------------------------------------------------
   Build the array of text to be included in the Postscript program to
   be rendered, from the arguments of this program.

   We encode it in ASCII-Hex notation as opposed to using the plain text from
   the command line because 1) the command line might have Postscript control
   characters in it; and 2) the command line might have text in 8-bit or
   multibyte code, but a Postscript program is supposed to be entirely
   printable ASCII characters.
-----------------------------------------------------------------------------*/
    char * text;
    unsigned int totalTextSize;
    unsigned int i;

    text = strdup("");
    totalTextSize = 1;

    if (argc-1 < 1)
        pm_error("No text");

    for (i = 1; i < argc; ++i) {
        if (i > 1) {
            totalTextSize += 1;
            text = realloc(text, totalTextSize);
            if (text == NULL)
                pm_error("out of memory");
            strcat(text, " ");
        } 
        totalTextSize += strlen(argv[i]);
        text = realloc(text, totalTextSize);
        if (text == NULL)
            pm_error("out of memory");
        strcat(text, argv[i]);
    }

    { 
        char * asciiHexText;

        MALLOCARRAY(asciiHexText, totalTextSize * 2);

        if (!asciiHexText)
            pm_error("Unable to allocate memory for hex encoding of %u "
                     "characters of text", totalTextSize);

        asciiHexEncode(text, asciiHexText);
        *asciiHexTextP = asciiHexText;
    }
    pm_strfree(text);
}



static void
parseCommandLine(int argc, char ** argv,
                 struct cmdlineInfo *cmdlineP) {
/*---------------------------------------------------------------------------
  Note that the file spec array we return is stored in the storage that
  was passed to us as the argv array.
---------------------------------------------------------------------------*/
    optEntry * option_def;
    /* Instructions to OptParseOptions2 on how to parse our options.
   */
    optStruct3 opt;

    unsigned int option_def_index;

    MALLOCARRAY(option_def, 100);

    option_def_index = 0;   /* incremented by OPTENTRY */
    OPTENT3(0, "resolution", OPT_UINT,   &cmdlineP->res,            NULL,  0);
    OPTENT3(0, "font",       OPT_STRING, &cmdlineP->font,           NULL,  0);
    OPTENT3(0, "fontsize",   OPT_UINT,   &cmdlineP->fontsize,       NULL,  0);
    OPTENT3(0, "stroke",     OPT_FLOAT,  &cmdlineP->stroke,         NULL,  0);
    OPTENT3(0, "verbose",    OPT_FLAG,   NULL, &cmdlineP->verbose,         0);

    /* Set the defaults */
    cmdlineP->res = 150;
    cmdlineP->fontsize = 24;
    cmdlineP->font = "Times-Roman";
    cmdlineP->stroke = -1;

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = FALSE;

    pm_optParseOptions3(&argc, argv, opt, sizeof(opt), 0);

    validateFontName(cmdlineP->font);

    buildTextFromArgs(argc, argv, &cmdlineP->text);
}



static void
termCmdline(struct cmdlineInfo const cmdline) {

    pm_strfree(cmdline.text);
}



static const char *
construct_postscript(struct cmdlineInfo const cmdline) {

    const char * retval;
    const char * template;

    if (cmdline.stroke < 0) 
        template =
            "/%s findfont\n"
            "%d scalefont\n"
            "setfont\n"
            "12 36 moveto\n"
            "<%s> show\n"
            "showpage\n";
    else 
        template =
            "/%s findfont\n"
            "%d scalefont\n"
            "setfont\n"
            "12 36 moveto\n"
            "%f setlinewidth\n"
            "0 setgray\n"
            "<%s> true charpath\n"
            "stroke\n"
            "showpage\n";

    if (cmdline.stroke < 0)
        pm_asprintf(&retval, template, cmdline.font, cmdline.fontsize, 
                    cmdline.text);
    else
        pm_asprintf(&retval, template, cmdline.font, cmdline.fontsize, 
                    cmdline.stroke, cmdline.text);

    return retval;
}



static const char *
gsExecutableName() {

    const char * const which = "which gs";

    static char buffer[BUFFER_SIZE];

    FILE * f;

    memset(buffer, 0, BUFFER_SIZE);

    f = popen(which, "r");
    if (!f)
        pm_error("Can't find ghostscript");

    fread(buffer, 1, BUFFER_SIZE, f);
    if (buffer[strlen(buffer) - 1] == '\n')
        buffer[strlen(buffer) - 1] = '\0';
    pclose(f);
    
    if (buffer[0] != '/' && buffer[0] != '.')
        pm_error("Can't find ghostscript");

    return buffer;
}



static const char *
cropExecutableName(void) {

    const char * const which = "which pnmcrop";

    static char buffer[BUFFER_SIZE];
    const char * retval;

    FILE * f;

    memset(buffer, 0, BUFFER_SIZE);

    f = popen(which, "r");
    if (!f)
        retval = NULL;
    else {
        fread(buffer, 1, BUFFER_SIZE, f);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = 0;
        pclose(f);
            
        if (buffer[0] != '/' && buffer[0] != '.') {
            retval = NULL;
            pm_message("Can't find pnmcrop");
        } else
            retval = buffer;
    }
    return retval;
}



static const char *
gsCommand(const char *       const psFname,
          const char *       const outputFilename, 
          struct cmdlineInfo const cmdline) {

    const char * retval;
    double const x = (double) cmdline.res * 11;
    double const y = (double) cmdline.res * 
                     ((double) cmdline.fontsize * 2 + 72)  / 72;
    
    if (cmdline.res <= 0)
         pm_error("Resolution (dpi) must be positive.");
    
    if (cmdline.fontsize <= 0)
         pm_error("Font size must be positive.");
    
    /* The following checks are for guarding against overflows in this 
       function.  Huge x,y values that pass these checks may be
       rejected by the 'gs' program.
    */
    
    if (x > (double) INT_MAX-10)
         pm_error("Absurdly fine resolution: %u. Output width too large.",
                   cmdline.res );
    if (y > (double) INT_MAX-10)
         pm_error("Absurdly fine resolution (%u) and/or huge font size (%u). "
                  "Output height too large.", cmdline.res, cmdline.fontsize);
         
    pm_asprintf(&retval, "%s -g%dx%d -r%d -sDEVICE=pbm "
                "-sOutputFile=%s -q -dBATCH -dNOPAUSE %s "
                "</dev/null >/dev/null", 
                gsExecutableName(), (int) x, (int) y, cmdline.res, 
                outputFilename, psFname);

    return retval;
}



static const char *
cropCommand(const char * const inputFileName) {

    const char * retval;
    const char * plainOpt = pm_plain_output ? "-plain" : "" ;
    
    if (cropExecutableName()) {
        pm_asprintf(&retval, "%s -top -right %s %s", 
                    cropExecutableName(), plainOpt, inputFileName);
        if (retval == pm_strsol)
            pm_error("Unable to allocate memory");
    } else
        retval = NULL;

    return retval;
}



static void
writeProgram(const char *       const psFname,
             struct cmdlineInfo const cmdline) {

    const char * ps;
    FILE * psfile;

    psfile = fopen(psFname, "w");
    if (psfile == NULL)
        pm_error("Can't open temp file '%s'.  Errno=%d (%s)",
                 psFname, errno, strerror(errno));

    ps = construct_postscript(cmdline);

    if (cmdline.verbose)
        pm_message("Postscript program = '%s'", ps);
        
    if (fwrite(ps, 1, strlen(ps), psfile) != strlen(ps))
        pm_error("Can't write postscript to temp file");

    fclose(psfile);

    pm_strfree(ps);
}



static void
executeProgram(const char *       const psFname, 
               const char *       const outputFname,
               struct cmdlineInfo const cmdline) {

    const char * com;
    int rc;

    com = gsCommand(psFname, outputFname, cmdline);
    if (com == NULL)
        pm_error("Can't allocate memory for a 'ghostscript' command");
    
    if (cmdline.verbose)
        pm_message("Running Postscript interpreter '%s'", com);

    rc = system(com);
    if (rc != 0)
        pm_error("Failed to run Ghostscript process.  rc=%d", rc);

    pm_strfree(com);
}



static void
cropToStdout(const char * const inputFileName,
             bool         const verbose) {

    const char * com;

    com = cropCommand(inputFileName);

    if (com == NULL) {
        /* No pnmcrop.  So don't crop. */
        pm_message("Can't find pnmcrop command, image will be large");
        writeFileToStdout(inputFileName);
    } else {
        FILE * pnmcrop;

        if (verbose)
            pm_message("Running crop command '%s'", com);
        
        pnmcrop = popen(com, "r");
        if (pnmcrop == NULL)
            pm_error("Can't run pnmcrop process");
        else {
            char buf[2048];
            bool eof;

            eof = FALSE;
            
            while (!eof) {
                int bytesRead;

                bytesRead = fread(buf, 1, sizeof(buf), pnmcrop);
                if (bytesRead > 0) {
                    int rc;
                    rc = fwrite(buf, 1, bytesRead, stdout);
                    if (rc != bytesRead)
                        pm_error("Can't write to stdout");
                } else if (bytesRead == 0)
                    eof = TRUE;
                else
                    pm_error("Failed to read output of Pnmcrop process.  "
                             "Errno=%d (%s)", errno, strerror(errno));
            }
            fclose(pnmcrop);
        }
        pm_strfree(com);
    }
}



static void
createOutputFile(struct cmdlineInfo const cmdline) {

    const char * const template = "./pstextpbm.%d.tmp.%s";
    
    const char * psFname;
    const char * uncroppedPbmFname;

    pm_asprintf(&psFname, template, getpid(), "ps");
    if (psFname == NULL)
        pm_error("Unable to allocate memory");
 
    writeProgram(psFname, cmdline);

    pm_asprintf(&uncroppedPbmFname, template, getpid(), "pbm");
    if (uncroppedPbmFname == NULL)
        pm_error("Unable to allocate memory");
 
    executeProgram(psFname, uncroppedPbmFname, cmdline);

    unlink(psFname);
    pm_strfree(psFname);

    cropToStdout(uncroppedPbmFname, cmdline.verbose);

    unlink(uncroppedPbmFname);
    pm_strfree(uncroppedPbmFname);
}



int 
main(int argc, char *argv[]) {

    struct cmdlineInfo cmdline;

    pbm_init(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    createOutputFile(cmdline);

    termCmdline(cmdline);

    return 0;
}
