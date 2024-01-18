/* ppmtoarbtxt.c - convert PPM to a custom text-based format
**
** Renamed from ppmtotxt.c by Bryan Henderson in January 2003.
**
** Copyright (C) 1995 by Peter Kirchgessner
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
*/

#include <assert.h>
#include <string.h>
#ifdef __GLIBC__
  #include <printf.h>  /* Necessary for parse_printf_format() */
#endif

#include "pm_c_util.h"
#include "mallocvar.h"
#include "nstring.h"
#include "shhopt.h"
#include "ppm.h"

/* HAVE_PARSE_PRINTF_FORMAT means the system library has
   parse_printf_format(), declared in <printf.h>.  This essentially means
   systems with GNU libc.
*/

#ifndef HAVE_PARSE_PRINTF_FORMAT
  #ifdef PA_FLAG_MASK                   /* Defined in printf.h */
    #define HAVE_PARSE_PRINTF_FORMAT 1
  #else
    #define HAVE_PARSE_PRINTF_FORMAT 0
  #endif
#endif



struct CmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    const char * inputFileName;
    const char * bodySklFileName;
    const char * hd;
    const char * tl;
    unsigned int debug;
};



static void
parseCommandLine(int argc, const char ** argv,
                 struct CmdlineInfo * const cmdlineP) {
/*----------------------------------------------------------------------------
   Note that many of the strings that this function returns in the
   *cmdline_p structure are actually in the supplied argv array.  And
   sometimes, one of these strings is actually just a suffix of an entry
   in argv!
-----------------------------------------------------------------------------*/
    optEntry * option_def;
        /* Instructions to OptParseOptions3 on how to parse our options.
         */
    optStruct3 opt;

    unsigned int hdSpec, tlSpec;

    unsigned int option_def_index;
    
    MALLOCARRAY(option_def, 100);

    option_def_index = 0;   /* incremented by OPTENTRY */
    OPTENT3(0,   "hd",   OPT_STRING, &cmdlineP->hd, 
            &hdSpec,             0);
    OPTENT3(0,   "tl",   OPT_STRING, &cmdlineP->tl,
            &tlSpec,             0);
    OPTENT3(0,   "debug", OPT_FLAG, NULL,
            &cmdlineP->debug,      0);

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = FALSE;  /* We have no parms that are negative numbers */

    pm_optParseOptions3(&argc, (char **)argv, opt, sizeof(opt), 0);
    free(option_def);

    if (!hdSpec)
        cmdlineP->hd = NULL;

    if (!tlSpec)
        cmdlineP->tl = NULL;

    if (argc-1 < 1)
        pm_error("You must specify the body skeleton file name as an "
                 "argument");
    else {
        cmdlineP->bodySklFileName = strdup(argv[1]);

        if (argc-1 < 2)
            cmdlineP->inputFileName = strdup("-");  /* he wants stdin */
        else {
            cmdlineP->inputFileName = strdup(argv[2]);
            if (argc-1 > 2)
                pm_error("Too many arguments.  The only possible arguments "
                         "are the body skeleton file name and input image "
                         "file name");
        }
    }
}




typedef enum {
/* The types of object we handle */
    BDATA, IRED, IGREEN, IBLUE, ILUM, FRED, FGREEN, FBLUE, FLUM,
    WIDTH, HEIGHT, POSX, POSY
} SkeletonObjectType;

typedef enum {
    OBJTYP_ICOLOR, OBJTYP_FCOLOR, OBJTYP_INT, OBJTYP_BDATA
} SkeletonObjectClass;

/* Maximum size for a format string ("%d" etc.) */
/* Add one to this size for the terminating '\0'. */
#define MAXFORMAT 16

typedef union {
/* The data we keep for each object */
    struct Bndat {
        char * bdat;   /* Binary data (text with newlines etc.) */
        unsigned int ndat;
    } binData;
    
    struct Icdat {
        char icformat[MAXFORMAT+1];  /* Integer colors */
        unsigned int icolmin, icolmax;
    } icolData;

    struct Fcdat {
        char fcformat[MAXFORMAT+1];  /* Float colors */
        double fcolmin, fcolmax;
    } fcolData;
    
    struct Idat {
        char iformat[MAXFORMAT+1];   /* Integer data */
    } iData;
} SkeletonObjectData;


/* Each object has a type and some data */
typedef struct { 
    SkeletonObjectType objType;
    SkeletonObjectData odata;
} SkeletonObject;



#define MAX_SKL_HEAD_OBJ 64
#define MAX_SKL_BODY_OBJ 256
#define MAX_SKL_TAIL_OBJ 64
#define MAX_LINE_BUF 1024
#define MAX_OBJ_BUF 80



static void
dumpSkeleton(SkeletonObject ** const skeletonPList,
             unsigned int      const nSkeleton) {

    unsigned int i;

    pm_message("%u objects", nSkeleton);

    for (i = 0; i < nSkeleton; ++i) {
        SkeletonObject * const skeletonP = skeletonPList[i];

        pm_message("  Object: Type %u", skeletonP->objType);
    }
}



static void
dumpAllSkeleton(SkeletonObject ** const bodySkeletonPList,
                unsigned int      const bodyNskl,
                SkeletonObject ** const headSkeletonPList, 
                unsigned int      const headNskl,
                SkeletonObject ** const tailSkeletonPList,
                unsigned int      const tailNskl) {
    
    pm_message("Body skeleton:");
    dumpSkeleton(bodySkeletonPList, bodyNskl);

    pm_message("Head skeleton:");
    dumpSkeleton(headSkeletonPList, headNskl);

    pm_message("Tail skeleton:");
    dumpSkeleton(tailSkeletonPList, tailNskl);
}



static void
writeBndat(FILE *           const ofP,
           SkeletonObject * const objectP) {

    struct Bndat * const bdataP = &objectP->odata.binData;

    fwrite(bdataP->bdat, bdataP->ndat, 1, ofP);
}



static void
writeIcol(FILE *           const ofP,
          SkeletonObject * const objectP,
          double           const value) {

    /* Unlike Netpbm, the output format does not have an upper limit for
       maxval.  Here we allow all values representable by unsigned int.
    */

    struct Icdat * const icdataP = &objectP->odata.icolData;
    unsigned int const outValue =
        ROUNDU( icdataP->icolmin +
                ((double)icdataP->icolmax - icdataP->icolmin) * value);

    fprintf(ofP, icdataP->icformat, outValue);
}



static void
writeFcol(FILE *           const ofP,
          SkeletonObject * const objectP,
          double           const value) {

    struct Fcdat * const fcdataP = &objectP->odata.fcolData;
    
    fprintf(ofP, fcdataP->fcformat,
            (double)
            (fcdataP->fcolmin
             + (fcdataP->fcolmax - fcdataP->fcolmin) * value));
}



static void
writeIdat(FILE *           const ofP,
          SkeletonObject * const objectP,
          unsigned int     const value) {

    struct Idat * const idataP = &objectP->odata.iData;
    
    fprintf(ofP, idataP->iformat, value);
}



static void
writeText(FILE *            const ofP,
          unsigned int      const nObj,
          SkeletonObject ** const obj,
          unsigned int      const width,
          unsigned int      const height,
          unsigned int      const x,
          unsigned int      const y,
          double            const red,
          double            const green,
          double            const blue) {
    
    unsigned int i;

    for (i = 0; i < nObj; ++i) {
        switch (obj[i]->objType) {
        case BDATA:
            writeBndat(ofP, obj[i]);
            break;
        case IRED:
            writeIcol(ofP, obj[i], red);
            break;
        case IGREEN:
            writeIcol(ofP, obj[i], green);
            break;
        case IBLUE:
            writeIcol(ofP, obj[i], blue);
            break;
        case ILUM:
            writeIcol(ofP, obj[i],
                      PPM_LUMINR*red + PPM_LUMING*green + PPM_LUMINB*blue);
            break;
        case FRED:
            writeFcol(ofP, obj[i], red);
            break;
        case FGREEN:
            writeFcol(ofP, obj[i], green);
            break;
        case FBLUE:
            writeFcol(ofP, obj[i], blue);
            break;
        case FLUM:
            writeFcol(ofP, obj[i],
                      PPM_LUMINR*red + PPM_LUMING*green + PPM_LUMINB*blue);
            break;
        case WIDTH:
            writeIdat(ofP, obj[i], width);
            break;
        case HEIGHT:
            writeIdat(ofP, obj[i], height);
            break;
        case POSX:
            writeIdat(ofP, obj[i], x);
            break;
        case POSY:
            writeIdat(ofP, obj[i], y);
            break;
        }
    }
}



static SkeletonObjectClass
objClass(SkeletonObjectType const objType) {

    switch (objType) {
    case IRED:
    case IGREEN:
    case IBLUE:
    case ILUM:
        return OBJTYP_ICOLOR;

    case FRED:
    case FGREEN:
    case FBLUE:
    case FLUM:
        return OBJTYP_FCOLOR;

    case WIDTH:
    case HEIGHT:
    case POSX:
    case POSY:
        return OBJTYP_INT;
    case BDATA:
        return OBJTYP_BDATA;
    }
    return 999; /* quiet compiler warning */
}


/*----------------------------------------------------------------------------
  Format string validation

  We validate format strings (such as "%f" "%03d") found in the skeleton files
  for convenience, even though behavior is documented as undefined when the
  user supplies a bogus format string.  Certain strings, most notably those
  with "%n", are especially risky; they pose a security threat.

  On systems with Glibc, we check with parse_printf_format().  On other
  systems we conduct a cursory scan of the characters in the format string,
  looking for characters that trigger non-numeric conversions, etc.

  Documentation for parse_printf_format() is usually available in texinfo
  format on GNU/Linux systems.  As of Dec. 2014 there is no official man page.
  
  Online documentation is available from:
  https://
  www.gnu.org/software/libc/manual/html_node/Parsing-a-Template-String.html
-----------------------------------------------------------------------------*/

#if HAVE_PARSE_PRINTF_FORMAT
static void
validateParsePrintfFlag(int                const printfConversion,
                        SkeletonObjectType const ctyp,
                        const char **      const errorP) {
/*----------------------------------------------------------------------------
  Assuming 'printfConversion' is the value reported by parse_printf_format()
  as the type of argument a format string requires, 
  return an explanation of how it is incompatible with 'ctyp' as
  *errorP -- return null string if it is compatible.
-----------------------------------------------------------------------------*/
    /* We first check for "%n", then the type modifiers, and finally the
       actual conversion type (char, int, float, double, string or pointer.)
    */
    switch (printfConversion & PA_FLAG_MASK) {
    case PA_FLAG_PTR:  /* This means %n */
        pm_asprintf(errorP, "Contains a %%n conversion specifier");
        break;

    case PA_FLAG_SHORT:
    case PA_FLAG_LONG:
    case PA_FLAG_LONG_LONG:
        /* We omit PA_FLAG_LONG_DOUBLE because it is a synonym for
           PA_FLAG_LONG_LONG: listing both causes compilation errors.
        */
        pm_asprintf(errorP, "Invalid type modifier");
        break;

    default:
        switch (printfConversion & ~PA_FLAG_MASK) {
        case PA_CHAR:
            pm_message("Warning: char type conversion."); 
        case PA_INT:
            if(objClass(ctyp) == OBJTYP_ICOLOR ||
               objClass(ctyp) == OBJTYP_INT )
                *errorP = NULL;
            else
                pm_asprintf(errorP, "Conversion specifier requires a "
                            "character or integer argument, but it is in "
                            "a replacement sequence for a different type");
            break;
        case PA_DOUBLE:
            if(objClass(ctyp) == OBJTYP_FCOLOR)
                *errorP = NULL;
            else
                pm_asprintf(errorP, "Conversion specifier requires a "
                            "double precision floating point argument, "
                            "but it is in "
                            "a replacement sequence for a different type");
            break;
        case PA_FLOAT:
        case PA_STRING:    /* %s */
        case PA_POINTER:   /* %p */
        default:
            pm_asprintf(errorP, "Conversion specifier requires an argument of "
                        "a type that this program never provides for "
                        "any replacement sequence");
        }
    }
}
#endif



#if HAVE_PARSE_PRINTF_FORMAT
static void
validateFormatWithPpf(const char *       const format,
                      SkeletonObjectType const ctyp,
                      const char **      const errorP) {
/*----------------------------------------------------------------------------
  Validate format string 'format' for use with a skeleton of type 'ctyp',
  using the system parse_printf_format() function.

  Return as *errorP an explanation of how it is invalid, or a null string
  if it is valid.
-----------------------------------------------------------------------------*/
    /* We request parse_printf_format() to report the details of the first
       8 conversions.  8 because the maximum length of format is 16 means it
       can have up to 8 conversions: "%d%d%d%d%d%d%d%d".

       Actually this is more than necessary: we are concerned with only the
       first conversion and whether there it is the only one.
    */

    int printfConversion[MAXFORMAT/2] = {0, 0, 0, 0, 0, 0, 0, 0};

    size_t const n =
        parse_printf_format(format, MAXFORMAT/2, printfConversion);

    switch (n) {
    case 0:
        pm_asprintf(errorP, "No transformation found");
        break;

    case 1:
        validateParsePrintfFlag(printfConversion[0], ctyp, errorP);
        break;

    default:
        pm_asprintf(errorP, "Has %lu extra transformation%s ",
                    (unsigned long)n-1, n-1 > 1 ? "s" : "");
        break;
    }
}
#endif



static void
validateFormatOne(char               const typeSpecifier,
                  bool               const isLastInString,
                  SkeletonObjectType const ctyp,
                  bool *             const validatedP,
                  const char **      const errorP) {

    switch (typeSpecifier) {
        /* Valid character encountered.  Skip. */
        /* ' ' (space) is listed here, but should never occur for
           we use sscanf() to parse the fields.
        */
    case ' ': case '-': case '+': case '\'': case '#': case '.':
    case '0': case '1': case '2': case '3': case '4': case '5':
    case '6': case '7': case '8': case '9':
        break;
        
    case 'c': case 'C':
        pm_message("Warning: char type conversion: %%%c.", typeSpecifier);
    case 'i': case 'd': case 'u': case 'o': case 'x': case 'X':
        if (!isLastInString)
            pm_asprintf(errorP, "Extra characters at end");
        else if(objClass(ctyp) != OBJTYP_ICOLOR &&
                objClass(ctyp) != OBJTYP_INT )
            pm_asprintf(errorP, "Conversion type mismatch");
        else
            *validatedP = true;
        break;

    case 'f': case 'F': case 'g': case 'G': case 'a': case 'A':
        if (!isLastInString)
            pm_asprintf(errorP, "Extra characters at end");
        else if(objClass(ctyp) != OBJTYP_FCOLOR)
            pm_asprintf(errorP, "Conversion type mismatch");
        else
            *validatedP = true;
        break;

    case '\0':
        pm_asprintf(errorP, "No conversion specified");
        break;
    case '%':
        pm_asprintf(errorP, "No more than one %% is allowed");
        break;
    case '$':
    case '*':
        pm_asprintf(errorP, "%c is not allowed", typeSpecifier);
        break;
    case 'h': case 'l': case 'L': case 'q': case 'j': case 'Z': case 't':
        pm_asprintf(errorP, "Modifier %c is not allowed in format",
                    typeSpecifier);
        break;
    case 's': case 'S': case 'm': case 'p': case 'n':
        pm_asprintf(errorP, "Invalid conversion type");
        break;
    default:
        pm_asprintf(errorP, "Abnormal character");
        break;
    }
}



static void
validateFormatGen(const char *       const format,
                  SkeletonObjectType const ctyp,
                  const char **      const errorP)  {
/*----------------------------------------------------------------------------
  Validate format string 'format' for use with a skeleton of type 'ctyp',
  without using the system parse_printf_format() function.

  The string must begin with "%" and end with the translation type character
  ("%d", "%x", "%f", etc.)

  We check only for invalid characters.  Invalid constructs, such as
  "%00.00.00d" will pass this test.

  Return as *errorP an explanation of how it is invalid, or a null string
  if it is valid.
-----------------------------------------------------------------------------*/
    if (format[0] != '%')
        pm_asprintf(errorP, "Does not start with %%");
    else {
        unsigned int i;
        bool validated;

        for (i = 1, validated = false, *errorP = NULL;
             !validated && !*errorP;
             ++i) {

            validateFormatOne(format[i], format[i+1] == '\0', ctyp,
                              &validated, errorP);
        }
    }
}



static void
validateFormat(const char *       const format,
               SkeletonObjectType const ctyp) {

    const char * error;

    if (strlen(format) > MAXFORMAT)
        pm_asprintf(&error, "Too long");
    else {
#if HAVE_PARSE_PRINTF_FORMAT
        if (true)
            validateFormatWithPpf(format, ctyp, &error);
        else  /* Silence compiler warning about unused function */
            validateFormatGen(format, ctyp, &error);
#else
        validateFormatGen(format, ctyp, &error);
#endif
    }

    if (error)
        pm_error("Invalid format string '%s'.  %s", format, error);
}              
               


static SkeletonObject *
newBinDataObj(unsigned int const nDat, 
              const char * const bdat) {
/*----------------------------------------------------------------------------
  Create a binary data object.
-----------------------------------------------------------------------------*/
    SkeletonObject * objectP;

    objectP = malloc(sizeof(*objectP) + nDat);

    if (!objectP)
        pm_error("Failed to allocate memory for binary data object "
                 "with %u bytes", nDat);

    objectP->objType = BDATA;
    objectP->odata.binData.ndat = nDat;
    objectP->odata.binData.bdat = ((char *)objectP) + sizeof(SkeletonObject);
    memcpy(objectP->odata.binData.bdat, bdat, nDat);

    return objectP;
}



static SkeletonObject *
newIcolDataObj(SkeletonObjectType const ctyp,
               const char *       const format,
               unsigned int       const icolmin,
               unsigned int       const icolmax) {
/*----------------------------------------------------------------------------
  Create integer color data object.
-----------------------------------------------------------------------------*/
    SkeletonObject * objectP;

    MALLOCVAR(objectP);

    if (!objectP)
        pm_error("Failed to allocate memory for an integer color data "
                 "object");

    objectP->objType = ctyp;
    validateFormat(format, ctyp);
    strcpy(objectP->odata.icolData.icformat, format);
    objectP->odata.icolData.icolmin = icolmin;
    objectP->odata.icolData.icolmax = icolmax;

    return objectP;
}



static SkeletonObject *
newFcolDataObj(SkeletonObjectType  const ctyp,
               const char *        const format,
               double              const fcolmin,
               double              const fcolmax) {
/*----------------------------------------------------------------------------
  Create float color data object.
-----------------------------------------------------------------------------*/
    SkeletonObject * objectP;

    MALLOCVAR(objectP);

    if (!objectP)
        pm_error("Failed to allocate memory for a float color data object");

    objectP->objType = ctyp;
    validateFormat(format, ctyp);
    strcpy(objectP->odata.fcolData.fcformat, format);
    objectP->odata.fcolData.fcolmin = fcolmin;
    objectP->odata.fcolData.fcolmax = fcolmax;

    return objectP;
}



static SkeletonObject *
newIdataObj(SkeletonObjectType const ctyp,
            const char *       const format) {
/*----------------------------------------------------------------------------
  Create universal data object.
-----------------------------------------------------------------------------*/
    SkeletonObject * objectP;

    MALLOCVAR(objectP);

    if (!objectP)
        pm_error("Failed to allocate memory for a universal data object");

    objectP->objType = ctyp;
    validateFormat(format, ctyp);
    strcpy(objectP->odata.iData.iformat, format);

    return objectP;
}



static char const escape = '#';



static SkeletonObjectType
interpretObjType(const char * const typstr) {

    SkeletonObjectType objType;

    /* handle integer colors */
    if      (streq(typstr, "ired")  ) objType = IRED;
    else if (streq(typstr, "igreen")) objType = IGREEN;
    else if (streq(typstr, "iblue") ) objType = IBLUE;
    else if (streq(typstr, "ilum")  ) objType = ILUM;
    /* handle real colors */
    else if (streq(typstr, "fred")  ) objType = FRED;
    else if (streq(typstr, "fgreen")) objType = FGREEN;
    else if (streq(typstr, "fblue") ) objType = FBLUE;
    else if (streq(typstr, "flum")  ) objType = FLUM;
    /* handle integer data */
    else if (streq(typstr, "width") ) objType = WIDTH;
    else if (streq(typstr, "height")) objType = HEIGHT;
    else if (streq(typstr, "posx")  ) objType = POSX;
    else if (streq(typstr, "posy")  ) objType = POSY;
    else                              objType = BDATA;

    return objType;
}



static SkeletonObject *
newIcSkelFromReplString(const char *       const objstr,
                        SkeletonObjectType const objType) {

    SkeletonObject * retval;
    unsigned int icolmin, icolmax;
    char formstr[MAX_OBJ_BUF];
    unsigned int nOdata;

    nOdata = sscanf(objstr, "%*s%s%u%u", formstr, &icolmin, &icolmax);

    if (nOdata == 3)
        retval = newIcolDataObj(objType, formstr, icolmin, icolmax);
    else if (nOdata == EOF) {
        /* No arguments specified.  Use defaults */
        retval = newIcolDataObj(objType, "%u", 0, 255);
    } else
        retval = NULL;

    return retval;
}



static SkeletonObject *
newFcSkelFromReplString(const char *       const objstr,
                        SkeletonObjectType const objType) {

    SkeletonObject * retval;
    double fcolmin, fcolmax;
    char formstr[MAX_OBJ_BUF];
    unsigned int nOdata;

    nOdata = sscanf(objstr, "%*s%s%lf%lf", formstr,
                    &fcolmin, &fcolmax);

    if (nOdata == 3)
        retval = newFcolDataObj(objType, formstr, fcolmin, fcolmax);
    else if (nOdata == EOF) {
        /* No arguments specified.  Use defaults */
        retval = newFcolDataObj(objType, "%f", 0.0, 1.0);
    } else
        retval = NULL;

    return retval;
} 



static SkeletonObject *
newISkelFromReplString(const char *       const objstr,
                       SkeletonObjectType const objType) {

    SkeletonObject * retval;
    char formstr[MAX_OBJ_BUF];
    unsigned int const nOdata = sscanf(objstr, "%*s%s", formstr);
    
    if (nOdata == 1)
        retval = newIdataObj(objType, formstr);
    else if (nOdata == EOF) {
        /* No arguments specified.  Use defaults */
        retval = newIdataObj(objType, "%u");
    } else
        retval = NULL;

    return retval;
} 



static SkeletonObject *
newSkeletonFromReplString(const char * const objstr) {
/*----------------------------------------------------------------------------
  Create a skeleton from the replacement string 'objstr' (the stuff
  between the parentheses in #(...) ).

  Return NULL if it isn't a valid replacement string.
-----------------------------------------------------------------------------*/
    /* We use sscanf() to parse the contents of objstr, giving it a format
       template with the largest number of fields possible plus one extra to
       pick up and check for the existence of invalid trailing characters.  We
       read and discard fields beyond the first, if any.  The appropriate
       new**SkelFromReplString() function determines their contents with a
       separate call to sscanf().
    */

    SkeletonObject * retval;
    char typstr[MAX_OBJ_BUF];
    SkeletonObjectType objType;
    int conversionCt;
    char s1[MAX_OBJ_BUF];    /* Dry read. */
    char s2[MAX_OBJ_BUF];    /* Extra tailing characters. */
    float f1, f2;            /* Dry read. */ 

    typstr[0] = '\0';  /* initial value */

    conversionCt = sscanf(objstr, "%s%s%f%f%s", typstr, s1, &f1, &f2, s2);
    switch (conversionCt) {
    case 1: case 2: case 4:
        objType = interpretObjType(typstr);
      break;
    default:
        objType = BDATA;
    }

    switch (objClass(objType)) {
    case OBJTYP_ICOLOR:
        retval = newIcSkelFromReplString(objstr, objType);
        break;
    case OBJTYP_FCOLOR:
        retval = newFcSkelFromReplString(objstr, objType);
        break;
    case OBJTYP_INT:
        retval = newISkelFromReplString(objstr, objType);
        break;
    case OBJTYP_BDATA:
        retval = NULL;
    }
    return retval;
}



static void
readThroughCloseParen(FILE * const ifP,
                      char * const objstr,
                      size_t const objstrSize,
                      bool * const unclosedP) {
/*----------------------------------------------------------------------------
   Read *ifP up through close parenthesis ( ')' ) into 'objstr', which
   is of size 'objstrSize'.  Make it a NUL-terminated string.

   Return *unclosedP true iff we run out of file or run out of objstr
   before we see a close parenthesis.  In this case, return the rest of
   the file, or as much as fits, in 'objstr', not NUL-terminated.
-----------------------------------------------------------------------------*/
    unsigned int i;
    bool eof;
    bool gotEscSeq;

    for (i= 0, eof = false, gotEscSeq = false;
         i < objstrSize - 1 && !gotEscSeq && !eof;
         ++i) {

        int rc;

        rc = getc(ifP);
        if (rc == EOF)
            eof = true;
        else {
            char const chr = rc;
            if (chr == ')') {
                gotEscSeq = true;
                objstr[i] = '\0';
	        } else
                objstr[i] = chr;
        }
    }
    *unclosedP = !gotEscSeq;
}



typedef struct {
    unsigned int      capacity;
    SkeletonObject ** skeletonPList;
    unsigned int      nSkeleton;
} SkeletonBuffer;



static void
SkeletonBuffer_init(SkeletonBuffer *  const bufferP,
                    unsigned int      const capacity,
                    SkeletonObject ** const skeletonPList) {

    bufferP->capacity      = capacity;
    bufferP->skeletonPList = skeletonPList;
    bufferP->nSkeleton     = 0;
}



static void
SkeletonBuffer_add(SkeletonBuffer * const bufferP,
                   SkeletonObject * const skeletonP) {

    if (bufferP->nSkeleton >= bufferP->capacity)
        pm_error("Too many skeletons.  Max = %u", bufferP->capacity);

    bufferP->skeletonPList[bufferP->nSkeleton++] = skeletonP;
}                   



typedef struct {

    char data[MAX_LINE_BUF + MAX_OBJ_BUF + 16];

    unsigned int length;

    SkeletonBuffer * skeletonBufferP;
        /* The buffer to which we flush.  Flushing means turning all the
           characters currently in our buffer into a binary skeleton object
           here.
        */

} Buffer;



static void
Buffer_init(Buffer *         const bufferP,
            SkeletonBuffer * const skeletonBufferP) {

    bufferP->skeletonBufferP = skeletonBufferP;
    bufferP->length = 0;
}



static void
Buffer_flush(Buffer * const bufferP) {
/*----------------------------------------------------------------------------
   Flush the buffer out to a binary skeleton object.
-----------------------------------------------------------------------------*/
    SkeletonBuffer_add(bufferP->skeletonBufferP,
                       newBinDataObj(bufferP->length, bufferP->data));

    bufferP->length = 0;
}



static void
Buffer_add(Buffer * const bufferP,
           char     const newChar) {

    if (bufferP->length >= MAX_LINE_BUF)
        Buffer_flush(bufferP);

    assert(bufferP->length < MAX_LINE_BUF);

    bufferP->data[bufferP->length++] = newChar;
}



static void
Buffer_dropFinalNewline(Buffer * const bufferP) {
/*----------------------------------------------------------------------------
   If the last thing in the buffer is a newline, remove it.
-----------------------------------------------------------------------------*/
    if (bufferP->length >= 1 && bufferP->data[bufferP->length-1] == '\n') {
            /* Drop finishing newline character */
            --bufferP->length;
    }
}



static void
addImpostorReplacementSeq(Buffer *     const bufferP,
                          const char * const seqContents) {
/*----------------------------------------------------------------------------
  Add to buffer *bufferP something that looks like a replacement sequence but
  doesn't have the proper contents (the stuff between the parentheses) to be
  one.  For example,

  "#(fread x)"

  seqContents[] is the contents, NUL-terminated.
-----------------------------------------------------------------------------*/
    const char * p;

    Buffer_add(bufferP, escape);
    Buffer_add(bufferP, '(');

    for (p = &seqContents[0]; *p; ++p)
        Buffer_add(bufferP, *p);

    Buffer_add(bufferP, ')');
}



static void
readSkeletonFile(const char *      const filename,
                 unsigned int      const maxskl,
                 const char **     const errorP,
                 unsigned int *    const nSkeletonP,
                 SkeletonObject ** const skeletonPList) {
/*----------------------------------------------------------------------------
-----------------------------------------------------------------------------*/
    FILE * sklfileP;
    SkeletonBuffer skeletonBuffer;
        /* A buffer for accumulating skeleton objects */
    Buffer buffer;
        /* A buffer for accumulating binary (literal; unsubstituted) data, on
           its way to becoming a binary skeleton object. 
        */
    bool eof;
    const char * error;

    SkeletonBuffer_init(&skeletonBuffer, maxskl, skeletonPList);

    Buffer_init(&buffer, &skeletonBuffer);

    sklfileP = pm_openr(filename);

    for (eof = false, error = NULL; !eof && !error; ) {

        int rc;

        rc = getc(sklfileP);

        if (rc == EOF)
            eof = true;
        else {
            char const chr = rc;

            if (chr != escape) {
                /* Not a replacement sequence; just a literal character */
                Buffer_add(&buffer, chr);
            } else {
                int rc;
                rc = getc(sklfileP);
                if (rc == EOF) {
                    /* Not a replacement sequence, just an escape caharacter
                       at the end of the file.
                    */
                    Buffer_add(&buffer, escape);
                    eof = true;
                } else {
                    char const chr = rc;

                    if (chr != '(') {
                        /* Not a replacement sequence, just a lone escape
                           character
                        */
                        Buffer_add(&buffer, escape);
                        Buffer_add(&buffer, chr);
                    } else {
                        char objstr[MAX_OBJ_BUF];
                        bool unclosed;
                        readThroughCloseParen(sklfileP,
                                              objstr, sizeof(objstr),
                                              &unclosed);
                        if (unclosed)
                            pm_asprintf(&error, "Unclosed parentheses "
                                        "in #() escape sequence");
                        else {
                            SkeletonObject * const skeletonP =
                                newSkeletonFromReplString(objstr);

                            if (skeletonP) {
                                Buffer_flush(&buffer);
                                SkeletonBuffer_add(&skeletonBuffer, skeletonP);
                            } else
                                addImpostorReplacementSeq(&buffer, objstr);
                        }
                    }
                }
            }
        }
    }

    if (!error) {
        Buffer_dropFinalNewline(&buffer);
        Buffer_flush(&buffer);
    }
    *errorP = error;
    *nSkeletonP = skeletonBuffer.nSkeleton;

    fclose(sklfileP);
}



static void
convertIt(FILE *            const ifP,
          FILE *            const ofP,
          SkeletonObject ** const bodySkeletonPList,
          unsigned int      const bodyNskl,
          SkeletonObject ** const headSkeletonPList, 
          unsigned int      const headNskl,
          SkeletonObject ** const tailSkeletonPList,
          unsigned int      const tailNskl) {

    pixel * pixelrow;
    pixval maxval;
    double dmaxval;
    int rows, cols;
    int format;
    unsigned int row;

    ppm_readppminit(ifP, &cols, &rows, &maxval, &format);

    pixelrow = ppm_allocrow(cols);

    dmaxval = (double)maxval;

    /* Write header */
    writeText(ofP, headNskl, headSkeletonPList, 
              cols, rows , 0, 0, 0.0, 0.0, 0.0);

    /* Write raster */
    for (row = 0; row < rows; ++row) {
        unsigned int col;

        ppm_readppmrow(ifP, pixelrow, cols, maxval, format);

        for (col = 0; col < cols; ++col) {
            pixel const thisPixel = pixelrow[col];

            writeText(ofP, bodyNskl, bodySkeletonPList,
                      cols, rows, col, row,
                      PPM_GETR(thisPixel)/dmaxval,
                      PPM_GETG(thisPixel)/dmaxval,
                      PPM_GETB(thisPixel)/dmaxval);
        }
    }

    /* Write trailer */
    writeText(ofP, tailNskl, tailSkeletonPList, 
              cols, rows, 0, 0, 0.0, 0.0, 0.0);
}



int
main(int           argc,
     const char ** argv) {
    
    struct CmdlineInfo cmdline;

    unsigned int headNskl, bodyNskl, tailNskl;
    SkeletonObject * headSkeletonPList[MAX_SKL_HEAD_OBJ];
    SkeletonObject * bodySkeletonPList[MAX_SKL_BODY_OBJ];
    SkeletonObject * tailSkeletonPList[MAX_SKL_TAIL_OBJ];
    FILE * ifP;
    const char * error;

    pm_proginit(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    ifP = pm_openr(cmdline.inputFileName);

    readSkeletonFile(cmdline.bodySklFileName, ARRAY_SIZE(bodySkeletonPList),
                     &error, &bodyNskl, bodySkeletonPList);
    if (error)
        pm_error("Invalid body skeleton file '%s'.  %s",
                 cmdline.bodySklFileName, error);

    if (cmdline.hd) {
        readSkeletonFile(cmdline.hd, ARRAY_SIZE(headSkeletonPList),
                         &error, &headNskl, headSkeletonPList);
        if (error)
            pm_error("Invalid head skeleton file '%s'.  %s",
                     cmdline.hd, error);
    } else
        headNskl = 0;

    if (cmdline.tl) {
        readSkeletonFile(cmdline.tl, ARRAY_SIZE(tailSkeletonPList),
                         &error, &tailNskl, tailSkeletonPList);
        if (error)
            pm_error("Invalid tail skeleton file '%s'.  %s",
                     cmdline.tl, error);
    } else
        tailNskl = 0;

    if (cmdline.debug)
        dumpAllSkeleton(bodySkeletonPList, bodyNskl,
                        headSkeletonPList, headNskl,
                        tailSkeletonPList, tailNskl);

    convertIt(ifP, stdout,
              bodySkeletonPList, bodyNskl,
              headSkeletonPList, headNskl,
              tailSkeletonPList, tailNskl);

    pm_close(ifP);

    return 0;
}


