/* pbmmake.c - create a blank bitmap of a specified size
 *
 * Akira Urushibata ("Douso") wrote some of the core code that went
 * into the Netpbm 10.23 (July 2004) version of this program and licenses
 * that code to the public under GPL.
 *
 * Bryan Henderson wrote the rest of that version and contributed his
 * work to the public domain.
 *
 * See doc/HISTORY for a full history of this program.
**
*/

#include "pm_c_util.h"
#include "shhopt.h"
#include "mallocvar.h"
#include "pbm.h"

enum color {COLOR_BLACK, COLOR_WHITE, COLOR_GRAY};

struct cmdlineInfo {
    /* All the information the user supplied in the command line,
       in a form easy for the program to use.
    */
    unsigned int width;
    unsigned int height;
    enum color color;
};



static void
parseCommandLine(int argc, char ** argv,
                 struct cmdlineInfo *cmdlineP) {
/*----------------------------------------------------------------------------
   Note that the file spec array we return is stored in the storage that
   was passed to us as the argv array.
-----------------------------------------------------------------------------*/
    optEntry *option_def;
        /* Instructions to pm_optParseOptions3 on how to parse our options.
         */
    optStruct3 opt;

    unsigned int option_def_index;
    unsigned int blackOpt, whiteOpt, grayOpt;

    MALLOCARRAY_NOFAIL(option_def, 100);

    option_def_index = 0;   /* incremented by OPTENTRY */
    OPTENT3(0, "black",     OPT_FLAG, NULL, &blackOpt, 0);
    OPTENT3(0, "white",     OPT_FLAG, NULL, &whiteOpt, 0);
    OPTENT3(0, "gray",      OPT_FLAG, NULL, &grayOpt,  0);
    OPTENT3(0, "grey",      OPT_FLAG, NULL, &grayOpt,  0);

    opt.opt_table = option_def;
    opt.short_allowed = FALSE;  /* We have no short (old-fashioned) options */
    opt.allowNegNum = FALSE;  /* We may have parms that are negative numbers */

    pm_optParseOptions3(&argc, argv, opt, sizeof(opt), 0);
        /* Uses and sets argc, argv, and some of *cmdlineP and others. */

    if (blackOpt + whiteOpt + grayOpt > 1)
        pm_error("You can specify only one of -black, -white, and -gray");
    
    if (blackOpt)
        cmdlineP->color = COLOR_BLACK;
    else if (whiteOpt)
        cmdlineP->color = COLOR_WHITE;
    else if (grayOpt)
        cmdlineP->color = COLOR_GRAY;
    else
        cmdlineP->color = COLOR_WHITE;

    if (argc-1 != 2)
        pm_error("Wrong number of arguments (%d).  There are two "
                 "non-option arguments: width and height in pixels",
                 argc-1);
    else {
        cmdlineP->width  = pm_parse_width(argv[1]);
        cmdlineP->height = pm_parse_height(argv[2]);
    }
}



static void 
writeGrayRaster(unsigned int const cols, 
                unsigned int const rows,
                FILE *       const ofP) {

    unsigned int const lastCol = (cols-1)/8;

    unsigned char * bitrow0, * bitrow1;
    unsigned int i;

    bitrow0 = pbm_allocrow_packed(cols);
    bitrow1 = pbm_allocrow_packed(cols);

    for (i=0; i <= lastCol; ++i) { 
        bitrow0[i] = (PBM_WHITE*0xaa) | (PBM_BLACK*0x55);
        bitrow1[i] = (PBM_WHITE*0x55) | (PBM_BLACK*0xaa);
        /* 0xaa = 10101010 ; 0x55 = 01010101 */
    }

    pbm_cleanrowend_packed(bitrow0, cols);
    pbm_cleanrowend_packed(bitrow1, cols);

  if (rows > 1) {
        unsigned int row;
        for (row = 1; row < rows; row += 2) {
            pbm_writepbmrow_packed(ofP, bitrow0, cols, 0);
            pbm_writepbmrow_packed(ofP, bitrow1, cols, 0);
        }
    }
    if (rows % 2 == 1)
        pbm_writepbmrow_packed(ofP, bitrow0, cols, 0);

    pbm_freerow(bitrow0);
    pbm_freerow(bitrow1);
}

    

static void
writeSingleColorRaster(unsigned int const cols,
                       unsigned int const rows,
                       bit          const color,
                       FILE *       const ofP) {

    unsigned int const lastCol = (cols-1)/8;

    unsigned char * bitrow0;
    unsigned int i;

    bitrow0 = pbm_allocrow_packed(cols);

    for (i = 0; i <= lastCol; ++i) 
        bitrow0[i] = color*0xff;

    if (color != 0)
        pbm_cleanrowend_packed(bitrow0, cols);
    /* row end trimming, not necessary with white */

    {
        unsigned int row;
        for (row = 0; row < rows; ++row)
            pbm_writepbmrow_packed(ofP, bitrow0, cols, 0);
    }
    pbm_freerow(bitrow0);
}



int
main(int argc, char * argv[]) {

    struct cmdlineInfo cmdline;

    pbm_init(&argc, argv);

    parseCommandLine(argc, argv, &cmdline);

    pbm_writepbminit(stdout, cmdline.width, cmdline.height, 0);
    
    if (cmdline.color == COLOR_GRAY)
        writeGrayRaster(cmdline.width, cmdline.height, stdout);
    else {
        bit const color = cmdline.color == COLOR_WHITE ? PBM_WHITE : PBM_BLACK;
        writeSingleColorRaster(cmdline.width, cmdline.height, color, stdout);
    }
    pm_close(stdout);
    
    return 0;
}
