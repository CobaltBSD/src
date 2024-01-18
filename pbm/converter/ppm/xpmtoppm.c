/* xpmtoppm.c - convert XPM file (X11 pixmap) to PPM

   Copyright and history information is at end of file
*/

#define _BSD_SOURCE   /* Make sure strdup() is in string.h */
#define _XOPEN_SOURCE 500  /* Make sure strdup() is in string.h */

#include <assert.h>
#include <string.h>

#include "pm_c_util.h"
#include "mallocvar.h"
#include "shhopt.h"
#include "nstring.h"
#include "ppm.h"

#define MAX_LINE (8 * 1024)
  /* The maximum size XPM input line we can handle. */

/* number of xpmColorKeys */
#define NKEYS 5

const char *xpmColorKeys[] =
{
 "s",                   /* key #1: symbol */
 "m",                   /* key #2: mono visual */
 "g4",                  /* key #3: 4 grays visual */
 "g",                   /* key #4: gray visual */
 "c",                   /* key #5: color visual */
};

struct cmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    const char * input_filespec;  /* Filespecs of input files */
    const char * alpha_filename;
    int alpha_stdout;
    int verbose;
};


static bool verbose;



static void
parseCommandLine(int argc, char ** argv,
                 struct cmdlineInfo *cmdlineP) {
/*----------------------------------------------------------------------------
   Note that the file spec array we return is stored in the storage that
   was passed to us as the argv array.
-----------------------------------------------------------------------------*/
    optEntry * option_def;
        /* Instructions to OptParseOptions2 on how to parse our options.
         */
    optStruct3 opt;

    unsigned int option_def_index;

    MALLOCARRAY_NOFAIL(option_def, 100);

    option_def_index = 0;   /* incremented by OPTENT3 */
    OPTENT3(0,   "alphaout",   OPT_STRING, &cmdlineP->alpha_filename,
            NULL, 0);
    OPTENT3(0,   "verbose",    OPT_FLAG,   &cmdlineP->verbose,
            NULL, 0);

    cmdlineP->alpha_filename = NULL;
    cmdlineP->verbose = FALSE;

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = TRUE;  /* We may have parms that are negative numbers */

    pm_optParseOptions3(&argc, argv, opt, sizeof(opt), 0);
        /* Uses and sets argc, argv, and some of *cmdlineP and others. */

    if (argc - 1 == 0)
        cmdlineP->input_filespec = NULL;  /* he wants stdin */
    else if (argc - 1 == 1)
        cmdlineP->input_filespec = strdup(argv[1]);
    else 
        pm_error("Too many arguments.  The only argument accepted\n"
                 "is the input file specification");

    if (cmdlineP->alpha_filename && 
        streq(cmdlineP->alpha_filename, "-"))
        cmdlineP->alpha_stdout = TRUE;
    else 
        cmdlineP->alpha_stdout = FALSE;

}



struct ColorNameHashTableEntry {
/*----------------------------------------------------------------------------
   An entry in the color name hash table.  It maps a color name to a
   color, or is empty.
-----------------------------------------------------------------------------*/
    bool empty;
    char colorName[3];
        /* Actual length 0-3.  NOT NUL-terminated */
    pixel color;
};



typedef struct {
/*----------------------------------------------------------------------------
   This is a color map which is primarily a hash table that maps an XPM
   color name to a color.  An XPM color name is a 0-3 character name that
   appears in the raster of an XPM image to uniquely identify a color.
   The header of the XPM contains a listing of all the color names that
   appear in the raster, identifying a color for each.

   We represent a color as a 'pixel'.
-----------------------------------------------------------------------------*/
    unsigned int nameSize;
        /* Size of color names in this hash.  0-3 */
    struct ColorNameHashTableEntry * transparentP;
        /* The element of 'table' that is for the transparent color.
           NULL if there is none.
        */

    /* This is an internally chained hash table, i.e. there are no linked
       lists.  You use the hash function to get an index into the hash table.
       If the entry indexed by that is not for the color name you're looking
       for, you look at the next entry down, and keep going down until you
       either find the color name you're looking for or hit an empty entry.

       So that we never run out of space for new color names, we make the
       creator of the hash table tell us the maximum number of colors there
       will be.  We allocate twice that size in order to reduce average hash
       chain length.
    */
    unsigned int size;
    struct ColorNameHashTableEntry * table;
} ColorNameHash;



static ColorNameHash *
hash_create(unsigned int const nColors,
            unsigned int const nameSize) {

    ColorNameHash * hashP;

    MALLOCVAR_NOFAIL(hashP);

    hashP->nameSize = nameSize;

    hashP->size = nColors * 2;

    MALLOCARRAY(hashP->table, hashP->size);

    if (!hashP->table)
        pm_error("Failed to allocate memory for a %u-entry "
                 "color name hash table.", hashP->size);

    {
        unsigned int i;
        for (i = 0; i < hashP->size; ++i)
            hashP->table[i].empty = true;
    }

    hashP->transparentP = NULL;

    return hashP;
}



static void
hash_destroy(ColorNameHash * const hashP) {

    free(hashP->table);

    free(hashP);
}



static unsigned int
hashColorName(const char * const name,
              unsigned int const size,
              unsigned int const hashTableSize) {
/*----------------------------------------------------------------------------
   Return the hash value (initial index into the color name hash table)
   for the color name 'name', which is 'size' characters long.  The hash
   is to be in the range [0, hashTableSize).
-----------------------------------------------------------------------------*/
    /* I have no idea if this is an appropriate hash function.  I borrowed
       it from pnm_hashTuple()
    */

    unsigned int const hash_factor[] = {1, 33, 33*33};

    unsigned int i;
    unsigned int hash;

    hash = 0;  /* initial value */
    for (i = 0; i < size; ++i) {
        hash += name[i] * hash_factor[i];
    }
    hash %= hashTableSize;
    return hash;
}



static bool
entryMatch(struct ColorNameHashTableEntry const entry,
           const char *                   const name,
           unsigned int                   const size) {

    if (entry.empty)
        return true;

    assert(size <= ARRAY_SIZE(entry.colorName));

    {
        unsigned int i;
        
        for (i = 0; i < size; ++i) {
            if (name[i] != entry.colorName[i])
                return false;
        }
    }

    return true;
}



static void
bumpIndex(unsigned int * const indexP,
          unsigned int   const tableSize,
          unsigned int   const limit) {
/*----------------------------------------------------------------------------
   Bump *indexP to the next entry in a table of size 'tableSize', in a
   circular fashion.  But abort the program if this would take us to
   'limit'.
-----------------------------------------------------------------------------*/
    *indexP += 1;
    if (*indexP >= tableSize)
        *indexP = 0;

    if (*indexP == limit)
        pm_error("INTERNAL ERROR: color name hash table is full");
}



static void
hash_find(const ColorNameHash *             const hashP,
          const char *                      const name,
          struct ColorNameHashTableEntry ** const entryPP) {
/*----------------------------------------------------------------------------
   Find the entry in the color hash table *hashP for the color
   named 'name' in the lexicon of this XPM file.  If the color is in the
   table, this is where it is.  If it isn't, this is where it should go.
-----------------------------------------------------------------------------*/
    unsigned int const initialIndex  =
        hashColorName(name, hashP->nameSize, hashP->size);

    unsigned int i;

    for (i = initialIndex;
         !entryMatch(hashP->table[i], name, hashP->nameSize);
         bumpIndex(&i, hashP->size, initialIndex));
         
    *entryPP = &hashP->table[i];
}



static void
hash_add(ColorNameHash * const hashP,
         const char *    const name,
         pixel           const color,
         bool            const isTransparent) {

    struct ColorNameHashTableEntry * entryP;

    hash_find(hashP, name, &entryP);

    if (!entryP->empty)
        pm_error("Color name appears multiple times in color map");

    entryP->empty = false;
    {
        unsigned int i;
        for (i = 0; i < hashP->nameSize; ++i)
            entryP->colorName[i] = name[i];
    }
    entryP->color = color;

    if (isTransparent) {
        if (hashP->transparentP)
            pm_error("There are multiple NONE (transparent) entries in "
                     "the XPM color map");
        else
            hashP->transparentP = entryP;
    }
}



static pixel
hash_color(const ColorNameHash * const hashP,
           const char *          const name) {

    struct ColorNameHashTableEntry * entryP;

    hash_find(hashP, name, &entryP);

    if (entryP->empty)
        pm_error("Color name in raster is not in color map");

    return entryP->color;
}



static bool
hash_isTransparent(const ColorNameHash * const hashP,
                   const char *          const name) {

    struct ColorNameHashTableEntry * entryP;

    hash_find(hashP, name, &entryP);

    return (entryP == hashP->transparentP);
}



static char lastInputLine[MAX_LINE+1];
    /* contents of line most recently read from input */
static bool backup;
    /* TRUE means next read should be a reread of the most recently read
       line, i.e. lastInputLine, instead of a read from the input file.
    */



static void
getLine(char * const line,
        size_t const size,
        FILE * const stream) {
/*----------------------------------------------------------------------------
   Read the next line from the input file 'stream', through the one-line
   buffer lastInputLine[].

   If 'backup' is true, the "next line" is the previously read line, i.e.
   the one in that one-line buffer.  Otherwise, the "next line" is the next
   line from the real file.  After reading the backed up line, we reset 
   'backup' to false.

   Return the line as a null terminated string in *line, which is an
   array of 'size' bytes.

   Exit program if the line doesn't fit in the buffer.
-----------------------------------------------------------------------------*/
    if (size > sizeof(lastInputLine))
        pm_error("INTERNAL ERROR: getLine() received 'size' parameter "
                 "which is out of bounds");

    if (backup) {
        strncpy(line, lastInputLine, size); 
        backup = FALSE;
    } else {
        if (fgets(line, size, stream) == NULL)
            pm_error("EOF or read error on input file");
        if (strlen(line) == size - 1)
            pm_error("Input file has line that is too long (longer than "
                     "%u bytes).", (unsigned)size - 1);
        STRSCPY(lastInputLine, line);
    }
}



static void
getword(char * const output, char ** const cursorP) {

    char *t1;
    char *t2;

    for (t1=*cursorP; ISSPACE(*t1); t1++); /* skip white space */
    for (t2 = t1; !ISSPACE(*t2) && *t2 != '"' && *t2 != '\0'; t2++);
        /* Move to next white space, ", or eol */
    if (t2 > t1)
        strncpy(output, t1, t2 - t1);
    output[t2 - t1] = '\0';
    *cursorP = t2;
}    



static void
addToColorMap(ColorNameHash * const hashP,
              const char *    const colorName,
              char            const colorspec[],
              bool            const isTransparent) {
/*----------------------------------------------------------------------------
   Add the color named by colorspec[] to the colormap represented by *hashP,
   as the color associated with XPM color name 'colorNumber'.

   Note that *hashP determines how long 'colorName' is.
-----------------------------------------------------------------------------*/
    hash_add(hashP, colorName, ppm_parsecolor(colorspec, PPM_MAXMAXVAL),
             isTransparent);
}



static void
validateColorName(const char * const name,
                  unsigned int const charsPerPixel) {

    unsigned int i;

    for (i = 0; i < charsPerPixel; ++i) {
        if (name[i] == '"')
            pm_error("A color map entry ends in the middle of the colormap "
                     "index");
        else if (name[i] == '\0')
            pm_error("The XPM file ends in the middle of a color map entry");
    }
}



static void
interpretXpm3ColorTableLine(char               const line[],
                            unsigned int       const seqNum, 
                            unsigned int       const charsPerPixel,
                            ColorNameHash *    const hashP) {
/*----------------------------------------------------------------------------
   Interpret one line of the color table in the XPM header.  'line' is the
   line from the XPM file.  It is the seqNum'th color table entry in the file.
   The raster in the file uses 'charsPerPixel' characters per pixel (i.e.
   a an XPM color name is 'charsPerPixel' characters).

   Add the information from this color table entry to the color name hash
   *hashP.

   The line may include values for multiple kinds of color (grayscale,
   color, etc.).  We take the highest of these (e.g. color over grayscale).

   If a color table entry indicates transparency, set *transparentP
   to indicate the XPM color name.
-----------------------------------------------------------------------------*/
    /* Note: this code seems to allow for multi-word color specifications,
       but I'm not aware that such are legal.  Ultimately, ppm_parsecolor()
       interprets the name, and I believe it takes only single word 
       color specifications.  -Bryan 2001.05.06.
    */
    char str2[MAX_LINE+1];    
    char * t1;
    char * t2;
    int endOfEntry;   /* boolean */
    
    unsigned int curkey, key, highkey;  /* current color key */
    bool lastwaskey;    
        /* The last token we processes was a key, and we have processed
           at least one token.
        */
    char curbuf[BUFSIZ];        /* current buffer */
    bool isTransparent;
    
    const char * colorName;
        /* The 0-3 character name this color map line gives the color
           (i.e. the name that the raster uses).  This is NOT NUL-terminated.
           It's length is bytesPerPixel.
        */

    /* read the chars */
    t1 = strchr(line, '"');
    if (t1 == NULL)
        pm_error("A line that is supposed to be an entry in the color "
                 "table does not start with a quote.  The line is '%s'.  "
                 "It is the %uth entry in the color table.", 
                 line, seqNum);
    else
        ++t1;  /* Points now to first color number character */
    
    validateColorName(t1, charsPerPixel);
    colorName = t1;

    t1 += charsPerPixel;

    /*
     * read color keys and values 
     */
    curkey = 0; 
    highkey = 1;
    lastwaskey = FALSE;
    t2 = t1;
    endOfEntry = FALSE;
    while ( !endOfEntry ) {
        int isKey;   /* boolean */
        getword(str2, &t2);
        if (strlen(str2) == 0)
            endOfEntry = TRUE;
        else {
            /* See if the word we got is a valid key (and get its key
               number if so)
            */
            for (key = 1; 
                 key <= NKEYS && !streq(xpmColorKeys[key - 1], str2); 
                 key++);
            isKey = (key <= NKEYS);

            if (lastwaskey || !isKey) {
                /* This word is a color specification (or "none" for
                   transparent).
                */
                if (!curkey) 
                    pm_error("Missing color key token in color table line "
                             "'%s' before '%s'.", line, str2);
                if (!lastwaskey) 
                    strcat(curbuf, " ");        /* append space */
                if ( (strneq(str2, "None", 4)) 
                     || (strneq(str2, "none", 4)) ) {
                    /* This entry identifies the transparent color number */
                    strcat(curbuf, "#000000");  /* Make it black */
                    isTransparent = TRUE;
                } else 
                    strcat(curbuf, str2);       /* append buf */
                lastwaskey = FALSE;
            } else { 
                /* This word is a key.  So we've seen the last of the 
                   info for the previous key, and we must either put it
                   in the color map or ignore it if we already have a higher
                   color form in the colormap for this colormap entry.
                */
                if (curkey > highkey) { /* flush string */
                    addToColorMap(hashP, colorName, curbuf, isTransparent);
                    highkey = curkey;
                }
                /* intialize state to process this new key */
                curkey = key;
                curbuf[0] = '\0';
                isTransparent = FALSE;
                lastwaskey = TRUE;
            }
            if (*t2 == '"') break;
        }
    }
    /* Put the info for the last key in the line into the colormap (or
       ignore it if there's already a higher color form for this colormap
       entry in it)
    */
    if (curkey > highkey) {
        addToColorMap(hashP, colorName, curbuf, isTransparent);
        highkey = curkey;
    }
    if (highkey == 1) 
        pm_error("C error scanning color table");
}



static void
readV3ColorTable(FILE *             const ifP,
                 ColorNameHash **   const colorNameHashPP,
                 unsigned int       const nColors,
                 unsigned int       const charsPerPixel) {
/*----------------------------------------------------------------------------
   Read the color table from the XPM Version 3 header.

   Assume *ifP is positioned to the color table; leave it positioned after.
-----------------------------------------------------------------------------*/
    ColorNameHash * const colorNameHashP = hash_create(nColors, charsPerPixel);

    unsigned int seqNum;
        /* Sequence number of entry within color table in XPM header */

    for (seqNum = 0; seqNum < nColors; ++seqNum) {
        char line[MAX_LINE+1];
        getLine(line, sizeof(line), ifP);
        /* skip the comment line if any */
        if (strneq(line, "/*", 2))
            getLine(line, sizeof(line), ifP);
            
        interpretXpm3ColorTableLine(line, seqNum, charsPerPixel,
                                    colorNameHashP);
                                    
    }
    *colorNameHashPP = colorNameHashP;
}



static void
readXpm3Header(FILE *             const ifP,
               unsigned int *     const widthP,
               unsigned int *     const heightP, 
               unsigned int *     const charsPerPixelP,
               ColorNameHash **   const colorNameHashPP) {
/*----------------------------------------------------------------------------
  Read the header of the XPM file on stream *ifP.  Assume the
  getLine() stream is presently positioned to the beginning of the
  file and it is a Version 3 XPM file.  Leave the stream positioned
  after the header.

  Return as *widthP and *heightP the dimensions of the image indicated
  by the header.

  Return as *charsPerPixelP the number of characters the header says the
  raster uses for each pixel, i.e. the XPM color name length.

  Return the color map as *colorNameHashPP.
-----------------------------------------------------------------------------*/
    char line[MAX_LINE+1];
    const char * xpm3_signature = "/* XPM */";
    
    unsigned int width, height;
    unsigned int nColors;
    unsigned int charsPerPixel;

    /* Read the XPM signature comment */
    getLine(line, sizeof(line), ifP);
    if (!strneq(line, xpm3_signature, strlen(xpm3_signature))) 
        pm_error("Apparent XPM 3 file does not start with '/* XPM */'.  "
                 "First line is '%s'", xpm3_signature);

    /* Read the assignment line */
    getLine(line, sizeof(line), ifP);
    if (!strneq(line, "static char", 11))
        pm_error("Cannot find data structure declaration.  Expected a "
                 "line starting with 'static char', but found the line "
                 "'%s'.", line);

    getLine(line, sizeof(line), ifP);

    /* Skip the comment block, if one starts here */
    if (strneq(line, "/*", 2)) {
        while (!strstr(line, "*/"))
            getLine(line, sizeof(line), ifP);
        getLine(line, sizeof(line), ifP);
    }

    /* Parse the hints line */
    if (sscanf(line, "\"%u %u %u %u\",", &width, &height,
               &nColors, &charsPerPixel) != 4)
        pm_error("error scanning hints line");

    if (verbose) {
        pm_message("Width x Height:  %u x %u", width, height);
        pm_message("no. of colors:  %u", nColors);
        pm_message("chars per pixel:  %u", charsPerPixel);
    }

    readV3ColorTable(ifP, colorNameHashPP, nColors, charsPerPixel);

    *widthP         = width;
    *heightP        = height;
    *charsPerPixelP = charsPerPixel;
}



static void
readV1ColorTable(FILE *           const ifP,
                 ColorNameHash ** const colorNameHashPP,
                 unsigned int     const nColors,
                 unsigned int     const charsPerPixel) {
/*----------------------------------------------------------------------------
   Read the color table from the XPM Version 1 header.

   Assume *ifP is positioned to the color table; leave it positioned after.
-----------------------------------------------------------------------------*/
    ColorNameHash * const colorNameHashP = hash_create(nColors, charsPerPixel);

    unsigned int i;

    for (i = 0; i < nColors; ++i) {
        char line[MAX_LINE+1];
        char str1[MAX_LINE+1];
        char str2[MAX_LINE+1];
        char * t1;
        char * t2;

        getLine(line, sizeof(line), ifP);

        if ((t1 = strchr(line, '"')) == NULL)
            pm_error("D error scanning color table");
        if ((t2 = strchr(t1 + 1, '"')) == NULL)
            pm_error("E error scanning color table");
        if (t2 - t1 - 1 != charsPerPixel)
            pm_error("wrong number of chars per pixel in color table");
        strncpy(str1, t1 + 1, t2 - t1 - 1);
        str1[t2 - t1 - 1] = '\0';

        if ((t1 = strchr(t2 + 1, '"')) == NULL)
            pm_error("F error scanning color table");
        if ((t2 = strchr(t1 + 1, '"')) == NULL)
            pm_error("G error scanning color table");
        strncpy(str2, t1 + 1, t2 - t1 - 1);
        str2[t2 - t1 - 1] = '\0';

        addToColorMap(colorNameHashP, str1, str2, false);
    }
    *colorNameHashPP = colorNameHashP;
}



static void
readXpm1Header(FILE *           const ifP,
               unsigned int *   const widthP,
               unsigned int *   const heightP, 
               unsigned int *   const charsPerPixelP,
               ColorNameHash ** const colorNameHashPP) {
/*----------------------------------------------------------------------------
  Read the header of the XPM file on stream *ifP.  Assume the
  getLine() stream is presently positioned to the beginning of the
  file and it is a Version 1 XPM file.  Leave the stream positioned
  after the header.
  
  Return the information from the header the same as for readXpm3Header.
-----------------------------------------------------------------------------*/
    int format, v;
    bool processedStaticChar;  
        /* We have read up to and interpreted the "static char..." line */
    char * t1;
    unsigned int nColors;
    bool gotPixel, gotNColors, gotWidth, gotHeight, gotFormat;

    gotNColors = false;
    gotWidth   = false;
    gotHeight  = false;
    gotFormat  = false;
    gotPixel   = false;

    /* Read the initial defines. */
    processedStaticChar = FALSE;
    while (!processedStaticChar) {
        char line[MAX_LINE+1];
        char str1[MAX_LINE+1];

        getLine(line, sizeof(line), ifP);

        if (sscanf(line, "#define %s %d", str1, &v) == 2) {
            if ((t1 = strrchr(str1, '_')) == NULL)
                t1 = str1;
            else
                ++t1;
            if (streq(t1, "format")) {
                gotFormat = true;
                format = v;
            } else if (streq(t1, "width")) {
                gotWidth = true;
                *widthP = v;
            } else if (streq(t1, "height")) {
                gotHeight = true;
                *heightP = v;
            } else if (streq(t1, "nColors")) {
                gotNColors = true;
                nColors = v;
            } else if (streq(t1, "pixel")) {
                gotPixel = TRUE;
                *charsPerPixelP = v;
            }
        } else if (strneq(line, "static char", 11)) {
            if ((t1 = strrchr(line, '_')) == NULL)
                t1 = line;
            else
                ++t1;
            processedStaticChar = TRUE;
        }
    }
    /* File is positioned to "static char" line, which is in line[] and
       t1 points to position of last "_" in the line, or the beginning of
       the line if there is no "_"
    */
    if (!gotPixel)
        pm_error("No 'pixel' value (characters per pixel)");
    if (!gotFormat)
        pm_error("missing or invalid format");
    if (format != 1)
        pm_error("can't handle XPM version %d", format);
    if (!gotWidth)
        pm_error("missing or invalid width");
    if (!gotHeight)
        pm_error("missing or invalid height");
    if (!gotNColors)
        pm_error("missing or invalid nColors");

    if (*charsPerPixelP > 2)
        pm_message("WARNING: > 2 characters per pixel uses a lot of memory");

    /* If there's a monochrome color table, skip it. */
    if (strneq(t1, "mono", 4)) {
        for (;;) {
            char line[MAX_LINE+1];
            getLine(line, sizeof(line), ifP);
            if (strneq(line, "static char", 11))
                break;
        }
    }
    readV1ColorTable(ifP, colorNameHashPP, nColors, *charsPerPixelP);

    /* Position to first line of raster (which is the line after
       "static char ...").
    */
    for (;;) {
        char line[MAX_LINE+1];
        getLine(line, sizeof(line), ifP);
        if (strneq(line, "static char", 11))
            break;
    }
}



static void
validateRasterPixel(const char * const pixelChars,
                    unsigned int const charsPerPixel) {

    unsigned int i;

    for (i = 0; i < charsPerPixel; ++i) {
        if (pixelChars[i] == '\0')
            pm_error("XPM input file ends in the middle of a string "
                     "that represents a raster line");
        else if (pixelChars[i] == '"')
            pm_error("A string that represents a raster line in the "
                     "XPM input file is too short to contain all the "
                     "pixels (%u characters each)",
                     charsPerPixel);
    }
}



static void
convertRow(char                  const line[],
           unsigned int          const width,
           unsigned int          const charsPerPixel,
           const ColorNameHash * const colorNameHashP,
           pixel *               const pixrow,
           bit *                 const alpharow) {
/*----------------------------------------------------------------------------
   Convert one row from XPM input, which describes one raster line of the
   image, to PPM.  The XPM line is in 'line', and its format is 'width' pixel,
   'charsPerPixel' characters per pixel.  *colorNameHashP is the color table
   that applies to the line.

   Put the PPM pixels in 'pixrow'.

   Also produce PBM row 'alpharow' with the transparency information from the
   row.

   If the line doesn't start with a quote (e.g. it is empty), we issue
   a warning and just treat the line as one that describes no pixels.

   Abort program if there aren't exactly 'width' pixels in the line.
-----------------------------------------------------------------------------*/
    const char * lineCursor;

    lineCursor = strchr(line, '"');  /* position to 1st quote in line */
    if (lineCursor == NULL) {
        /* We've seen a purported XPM that had a blank line in it.  Just
           ignoring it was the right thing to do.  05.05.27.
        */
        pm_message("WARNING:  No opening quotation mark in XPM input "
                   "line which is supposed to be a line of raster data: "
                   "'%s'.  Ignoring this line.", line);
    } else {
        unsigned int col;
    
        ++lineCursor; /* Skip to first character after quote */

        /* Handle pixels until a close quote, eol, or we've returned all
           the pixels Caller wants.
        */
        for (col = 0; col < width; ++col) {

            validateRasterPixel(lineCursor, charsPerPixel);

            pixrow[col] = hash_color(colorNameHashP, lineCursor);

            alpharow[col] = hash_isTransparent(colorNameHashP, lineCursor) ?
                PBM_BLACK : PBM_WHITE;
            
            lineCursor += charsPerPixel;
        }
        if (*lineCursor != '"')
            pm_error("A raster line continues past width of image");
    }
}



static void
convertRaster(FILE *                const ifP,
              unsigned int          const cols,
              unsigned int          const rows, 
              unsigned int          const charsPerPixel,
              const ColorNameHash * const colorNameHashP,
              FILE *                const imageOutFileP,
              FILE *                const alphaOutFileP) {
/*----------------------------------------------------------------------------
  Read the XPM raster from *ifP and write the PPM raster to *imageOutFileP
  and the alpha channel to *alphaOutFileP (where those are, respectively,
  non-null).

  The dimensions are 'cols' by 'rows' and the color map for the XPM
  raster is *colorNameHashP.
-----------------------------------------------------------------------------*/
    char line[MAX_LINE+1];
    pixel * pixrow;
    bit * alpharow;
    unsigned int row;

    pixrow   = ppm_allocrow(cols);
    alpharow = pbm_allocrow(cols);

    for (row = 0; row < rows; ++row) {
        bool haveLine;

        for (haveLine = false; !haveLine; ) {
            getLine(line, sizeof(line), ifP); 

            if (strneq(line, "/*", 2)) {
                /* It's a comment.  Ignore it. */
            } else
                haveLine = true;
        }
        convertRow(line, cols, charsPerPixel, colorNameHashP,
                   pixrow, alpharow);

        if (imageOutFileP)
            ppm_writeppmrow(imageOutFileP, 
                            pixrow, cols, PPM_MAXMAXVAL, 0);
            if (alphaOutFileP)
                pbm_writepbmrow(alphaOutFileP, alpharow, cols, 0);
    }

    pbm_freerow(alpharow);
    ppm_freerow(pixrow);
}
 


static void
readXpmHeader(FILE *           const ifP,
              unsigned int *   const widthP,
              unsigned int *   const heightP, 
              unsigned int *   const charsPerPixelP,
              ColorNameHash ** const colorNameHashPP) {
/*----------------------------------------------------------------------------
  Read the XPM header, including color map.

  In the colormap, put black for the transparent color, if the XPM image
  contains one.
-----------------------------------------------------------------------------*/
    char line[MAX_LINE+1];
    char str1[MAX_LINE+1];
    int rc;
    unsigned int charsPerPixel;
    unsigned int width, height;

    backup = FALSE;

    /* Read the header line */
    getLine(line, sizeof(line), ifP);
    backup = TRUE;  /* back up so next read reads this line again */
    
    rc = sscanf(line, "/* %s */", str1);
    if (rc == 1 && strneq(str1, "XPM", 3)) {
        /* It's an XPM version 3 file */
        readXpm3Header(ifP, &width, &height, &charsPerPixel, colorNameHashPP);
    } else {
        /* Assume it's an XPM version 1 file */
        readXpm1Header(ifP, &width, &height, &charsPerPixel, colorNameHashPP);
    }
    *widthP         = width;
    *heightP        = height;
    *charsPerPixelP = charsPerPixel;
}
 


int
main(int argc, char *argv[]) {

    FILE * ifP;
    FILE * alphaOutFileP;
    FILE * imageOutFileP;
    unsigned int cols, rows;
    unsigned int charsPerPixel;
    ColorNameHash * colorNameHashP;

    struct cmdlineInfo cmdline;

    ppm_init(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    verbose = cmdline.verbose;

    if ( cmdline.input_filespec != NULL ) 
        ifP = pm_openr( cmdline.input_filespec);
    else
        ifP = stdin;

    if (cmdline.alpha_stdout)
        alphaOutFileP = stdout;
    else if (cmdline.alpha_filename == NULL) 
        alphaOutFileP = NULL;
    else {
        alphaOutFileP = pm_openw(cmdline.alpha_filename);
    }

    if (cmdline.alpha_stdout) 
        imageOutFileP = NULL;
    else
        imageOutFileP = stdout;

    readXpmHeader(ifP, &cols, &rows, &charsPerPixel, &colorNameHashP);

    if (imageOutFileP)
        ppm_writeppminit(imageOutFileP, cols, rows, PPM_MAXMAXVAL, 0);
    if (alphaOutFileP)
        pbm_writepbminit(alphaOutFileP, cols, rows, 0);


    convertRaster(ifP, cols, rows, charsPerPixel, colorNameHashP,
                  imageOutFileP, alphaOutFileP);
    
    pm_close(ifP);
    if (imageOutFileP)
        pm_close(imageOutFileP);
    if (alphaOutFileP)
        pm_close(alphaOutFileP);

    hash_destroy(colorNameHashP);
    
    return 0;
}



/*
**
** Copyright (C) 1991 by Jef Poskanzer.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
**
** Upgraded to handle XPM version 3 by
**   Arnaud Le Hors (lehors@mirsa.inria.fr)
**   Tue Apr 9 1991
**
** Rainer Sinkwitz sinkwitz@ifi.unizh.ch - 21 Nov 91:
**  - Bug fix, no advance of read ptr, would not read 
**    colors like "ac c black" because it would find 
**    the "c" of "ac" and then had problems with "c"
**    as color.
**    
**  - Now understands multiword X11 color names
**  
**  - Now reads multiple color keys. Takes the color
**    of the hightest available key. Lines no longer need
**    to begin with key 'c'.
**    
**  - expanded line buffer to from 500 to 2048 for bigger files
*/

