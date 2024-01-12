#include <stdlib.h>
#include <string.h>
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYLEX yylex()
#define YYEMPTY -1
#define yyclearin (yychar=(YYEMPTY))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING() (yyerrflag!=0)
#define YYPREFIX "yy"
#line 68 "gram.y"

#include <stdio.h>
#include <ctype.h>
#include "twm.h"
#include "menus.h"
#include "list.h"
#include "util.h"
#include "screen.h"
#include "parse.h"
#include "add_window.h"
#include "icons.h"
#include <X11/Xos.h>
#include <X11/Xmu/CharSet.h>

static char empty[1];
static char *Action = empty;
static char *Name = empty;
static MenuRoot *root, *pull = NULL;

static MenuRoot *GetRoot(const char *name, const char *fore, const char *back);
static void GotButton(int butt, int func);
static void GotKey(char *key, int func);
static void GotTitleButton(char *bitmapname, int func, Bool rightside);
static Bool CheckWarpScreenArg(char *s);
static Bool CheckWarpRingArg(char *s);
static Bool CheckColormapArg(char *s);
static void RemoveDQuote(char *str);

static char *ptr;
static name_list **list;
static int cont = 0;
static int color;
int mods = 0;
unsigned int mods_used = (ShiftMask | ControlMask | Mod1Mask);

extern int yylineno;
static void yyerror(const char *s);

#line 108 "gram.y"
#ifndef YYSTYPE_DEFINED
#define YYSTYPE_DEFINED
typedef union
{
    int num;
    char *ptr;
} YYSTYPE;
#endif /* YYSTYPE_DEFINED */
#line 61 "gram.c"
#define LB 257
#define RB 258
#define LP 259
#define RP 260
#define MENUS 261
#define MENU 262
#define BUTTON 263
#define DEFAULT_FUNCTION 264
#define PLUS 265
#define MINUS 266
#define ALL 267
#define OR 268
#define CURSORS 269
#define PIXMAPS 270
#define ICONS 271
#define COLOR 272
#define SAVECOLOR 273
#define MONOCHROME 274
#define FUNCTION 275
#define ICONMGR_SHOW 276
#define ICONMGR 277
#define WINDOW_FUNCTION 278
#define ZOOM 279
#define ICONMGRS 280
#define ICONMGR_GEOMETRY 281
#define ICONMGR_NOSHOW 282
#define MAKE_TITLE 283
#define GRAYSCALE 284
#define ICONIFY_BY_UNMAPPING 285
#define DONT_ICONIFY_BY_UNMAPPING 286
#define NO_TITLE 287
#define AUTO_RAISE 288
#define NO_HILITE 289
#define ICON_REGION 290
#define META 291
#define SHIFT 292
#define LOCK 293
#define CONTROL 294
#define WINDOW 295
#define TITLE 296
#define ICON 297
#define ROOT 298
#define FRAME 299
#define COLON 300
#define EQUALS 301
#define SQUEEZE_TITLE 302
#define DONT_SQUEEZE_TITLE 303
#define START_ICONIFIED 304
#define NO_TITLE_HILITE 305
#define TITLE_HILITE 306
#define MOVE 307
#define RESIZE 308
#define WAIT 309
#define SELECT 310
#define KILL 311
#define LEFT_TITLEBUTTON 312
#define RIGHT_TITLEBUTTON 313
#define NUMBER 314
#define KEYWORD 315
#define NKEYWORD 316
#define CKEYWORD 317
#define CLKEYWORD 318
#define FKEYWORD 319
#define FSKEYWORD 320
#define SKEYWORD 321
#define DKEYWORD 322
#define JKEYWORD 323
#define WINDOW_RING 324
#define WARP_CURSOR 325
#define ERRORTOKEN 326
#define NO_STACKMODE 327
#define STRING 328
#define YYERRCODE 256
const short yylhs[] =
	{                                        -1,
    0,   24,   24,    6,    6,    6,    6,    6,    6,    6,
    6,    6,    6,    6,    6,   25,    6,    6,    6,    6,
    6,    6,    6,    6,   26,    6,   27,    6,    6,   28,
    6,   29,    6,   30,    6,    6,   31,    6,    6,   32,
    6,    6,   33,    6,    6,   34,    6,   35,    6,   36,
    6,   37,    6,   38,    6,   39,    6,   40,    6,   41,
    6,   42,    6,    6,   43,    6,    6,    6,   44,    6,
    6,   45,    6,   13,   14,   15,   22,   23,   46,   46,
   49,   49,   49,   49,   49,   49,   47,   47,   50,   50,
   50,   50,   50,   50,   50,   50,   50,   48,   48,   51,
   51,   51,   51,   51,   51,   51,   51,   51,   51,    2,
   52,   52,   53,    3,   54,   54,   55,   55,   55,   55,
   55,   55,   55,   55,   55,   55,   55,   55,   55,   55,
   55,   55,   55,   55,   55,   55,   55,   55,    4,   56,
   56,   17,   57,   17,   17,    5,   58,   58,   59,   59,
    7,   60,   60,   61,   16,   62,   16,   16,   64,   16,
   63,   63,    8,   65,   65,   66,   66,    9,   67,   67,
   68,   10,   69,   69,   70,   11,   71,   71,   72,   12,
   73,   73,   74,   74,   18,   18,   21,   21,   21,   19,
    1,   20,
};
const short yylen[] =
	{                                         2,
    1,    0,    2,    1,    1,    1,    1,    1,    6,    3,
    2,    2,    1,    2,    2,    0,    3,    1,    4,    4,
    2,    2,    2,    2,    0,    3,    0,    3,    1,    0,
    3,    0,    3,    0,    3,    1,    0,    3,    1,    0,
    3,    1,    0,    3,    1,    0,    3,    0,    3,    0,
    3,    0,    9,    0,    4,    0,    4,    0,    3,    0,
    3,    0,    3,    2,    0,    3,    2,    2,    0,    3,
    1,    0,    3,    1,    2,    2,    6,    6,    0,    2,
    1,    1,    1,    1,    2,    1,    0,    2,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    0,    2,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    3,
    0,    2,    2,    3,    0,    2,    3,    2,    3,    2,
    3,    2,    3,    2,    3,    2,    3,    2,    3,    2,
    3,    2,    3,    2,    3,    2,    3,    2,    3,    0,
    2,    2,    0,    4,    2,    3,    0,    2,    1,    1,
    3,    0,    2,    2,    1,    0,    5,    1,    0,    3,
    0,    5,    3,    0,    2,    3,    4,    3,    0,    2,
    1,    3,    0,    2,    2,    3,    0,    2,    1,    3,
    0,    2,    2,    7,    1,    2,    1,    2,    2,    2,
    1,    1,
};
const short yydefred[] =
	{                                      2,
    0,    0,    4,    0,    0,    0,    0,    0,   58,   60,
    0,   65,    0,   32,    0,    0,   30,    0,    0,   46,
   62,    0,   25,    0,   50,    0,    0,    0,    0,   48,
    0,    0,    0,   74,    0,    0,   72,    0,    0,  191,
    0,    3,    5,    6,    7,    8,    0,    0,  192,  190,
  185,    0,   67,  115,   15,  111,   14,    0,    0,  147,
   64,    0,   56,    0,   68,   12,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   76,   75,    0,    0,    0,   79,   23,
   79,   21,   22,   24,    0,    0,  186,    0,    0,  173,
   59,  140,   61,    0,   66,    0,  169,   33,  164,   31,
   10,   28,   47,   63,   17,   26,   44,   51,   38,    0,
  161,  160,   49,   35,    0,    0,   73,   70,   41,    0,
    0,    0,  181,   55,  114,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  116,  110,    0,  112,
    0,    0,  146,  150,  149,  148,  177,   57,    0,    0,
    0,    0,   19,   20,   86,    0,   82,   83,   84,   98,
   80,   87,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  113,  172,    0,  174,  139,
    0,    0,  141,    0,  168,  171,  170,  163,    0,  165,
    0,  157,    0,   85,    0,    0,    0,  180,    0,  182,
  133,  125,  123,  119,  121,  117,  127,  129,  131,  135,
  137,  175,  145,    0,  176,  179,  178,    0,    9,    0,
  107,  108,  105,  106,  100,  101,  102,  103,  104,    0,
  109,   99,   96,   97,   94,   95,   89,   90,   91,   92,
   93,    0,   88,   52,    0,  183,    0,    0,  166,    0,
    0,  187,    0,   78,   77,    0,    0,  152,  144,  167,
  188,  189,  162,   53,    0,    0,    0,  151,    0,  153,
    0,  154,  184,
};
const short yydgoto[] =
	{                                       1,
   41,   57,   55,  103,   61,   42,  269,  110,  108,  101,
  158,  134,   43,   44,   45,   46,  193,   53,   47,   50,
  263,   94,   90,    2,   72,   73,   69,   67,   64,   81,
   76,   88,   74,   70,   80,   75,  266,   96,  106,   58,
   59,   71,   62,   87,   86,  130,  206,  205,  171,  253,
  242,   99,  150,   98,  147,  152,  257,  104,  156,  276,
  280,   78,  162,   79,  160,  200,  159,  197,  151,  189,
  194,  227,  174,  210,
};
const short yysindex[] =
	{                                      0,
    0, -183,    0, -312, -294, -291, -231, -227,    0,    0,
 -224,    0, -312,    0, -291, -294,    0, -312,    0,    0,
    0,    0,    0,    0,    0,    0, -312,    0,    0,    0,
    0, -312, -312,    0, -294, -312,    0,    0,    0,    0,
 -267,    0,    0,    0,    0,    0, -297, -222,    0,    0,
    0, -312,    0,    0,    0,    0,    0, -219, -218,    0,
    0, -218,    0, -217,    0,    0, -215, -294, -217, -217,
 -218, -217, -217, -217, -217, -217, -287, -214, -217, -217,
 -217, -241, -240,    0,    0, -217, -217, -217,    0,    0,
    0,    0,    0,    0, -312, -206,    0,  787, -243,    0,
    0,    0,    0, -256,    0, -203,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, -264,
    0,    0,    0,    0, -291, -291,    0,    0,    0, -247,
 -116, -233,    0,    0,    0, -312, -312, -312, -312, -312,
 -312, -312, -312, -312, -312, -312,    0,    0, -312,    0,
 -252, -249,    0,    0,    0,    0,    0,    0, -251, -250,
 -294, -246,    0,    0,    0, -294,    0,    0,    0,    0,
    0,    0, -312, -245, -312, -312, -312, -312, -312, -312,
 -312, -312, -312, -312, -312,    0,    0, -312,    0,    0,
 -312, -312,    0, -255,    0,    0,    0,    0, -312,    0,
 -294,    0, -238,    0,  771, 1035, -189,    0, -207,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, -303,    0, -248,
    0,    0,    0,    0,    0,    0,    0,    0,    0, -291,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -291,    0,    0, -312,    0, -163, -294,    0, -294,
 -294,    0, -294,    0,    0, -206, -186,    0,    0,    0,
    0,    0,    0,    0, -312, -244, -145,    0, -312,    0,
 -291,    0,    0,};
const short yyrindex[] =
	{                                      0,
    0,  116,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  658,    0,    0,    1,    0,
    0,   74,    0,  147,    0,  220,    0,  293,  366,    0,
  439,    0,    0,    0,    0,    0,    0,  512,  585,    0,
    0,    0,    0,    0,    0,    0,    0, -231,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  731,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  -59,    0,    0,    0,    0,
    0,    0,    0,    0,  814,  830,  854,  870,  894,  910,
  934,  950,  974,  990, 1014,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, -209,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,};
const short yygindex[] =
	{                                      0,
   23,    0,    0,  -52,    0,    0,    0,    0, 1267,    0,
    0, -149,    0,    0,    0,    0,    0,  -15,    0,  -11,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   32,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,
};
#define YYTABLESIZE 1355
const short yytable[] =
	{                                      65,
   29,  153,  225,   91,   66,  187,  195,  198,  190,  105,
   49,  202,  208,  278,  148,   40,  260,  261,  114,   49,
  165,   51,   52,   84,   40,   54,   48,   51,   52,   56,
   40,   93,   60,   89,  120,   63,   95,  100,  102,  107,
   68,  109,  121,  166,  167,  168,  169,  143,  142,   77,
  133,  255,  170,  157,   82,   83,  111,  161,   85,  125,
  126,  154,  149,   51,   52,   49,  173,  191,  192,   92,
  254,   40,    3,   18,   97,   40,   40,   40,    4,    5,
    6,   40,   40,   40,  230,    7,    8,    9,   10,   11,
   12,   13,   14,  268,   15,   16,   17,   18,   19,   20,
   21,   22,   23,   24,   25,   26,   27,  142,  142,  163,
  164,   51,   52,  275,  281,    1,  274,  132,   28,   29,
   30,   31,  131,    0,    0,    0,  155,    0,   32,   33,
    0,   34,   35,    0,    0,    0,    0,   36,    0,    0,
   37,   38,    0,   39,   40,    0,   45,    0,    0,  201,
    0,  165,    0,    0,  204,    0,    0,    0,  175,  176,
  177,  178,  179,  180,  181,  182,  183,  184,  185,    0,
    0,  186,    0,  188,  166,  167,  168,  169,  226,    0,
    0,  196,  199,  172,  203,    0,    0,    0,    0,  229,
    0,    0,    0,  256,    0,  207,  209,  211,  212,  213,
  214,  215,  216,  217,  218,  219,  220,  221,   81,    0,
  222,    0,    0,  223,  224,    0,  259,    0,  262,   39,
    0,  228,    0,    0,  264,    0,    0,  241,    0,    0,
    0,   81,   81,   81,   81,    0,  265,    0,    0,    0,
   81,    0,    0,    0,    0,    0,  270,    0,  271,  272,
  258,  273,    0,    0,    0,    0,   29,   27,    0,    0,
    0,    0,   29,   29,   29,  283,    0,    0,    0,   29,
   29,   29,   29,   29,   29,   29,   29,  267,   29,   29,
   29,   29,   29,   29,   29,   29,   29,   29,   29,   29,
   29,    0,  155,    0,    0,    0,    0,  277,  279,    0,
    0,  282,   29,   29,   29,   29,    0,    0,    0,    0,
    0,    0,   29,   29,    0,   29,   29,    0,    0,    0,
    0,   29,    0,    0,   29,   29,    0,   29,   29,   18,
   16,    0,    0,    0,    0,   18,   18,   18,    0,    0,
    0,    0,   18,   18,   18,   18,   18,   18,   18,   18,
    0,   18,   18,   18,   18,   18,   18,   18,   18,   18,
   18,   18,   18,   18,    0,  158,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   18,   18,   18,   18,    0,
    0,    0,    0,    0,    0,   18,   18,    0,   18,   18,
    0,    0,    0,    0,   18,    0,    0,   18,   18,    0,
   18,   18,   45,   43,    0,    0,    0,    0,   45,   45,
   45,    0,    0,    0,    0,   45,   45,   45,   45,   45,
   45,   45,   45,    0,   45,   45,   45,   45,   45,   45,
   45,   45,   45,   45,   45,   45,   45,    0,   36,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   45,   45,
   45,   45,    0,    0,    0,    0,    0,    0,   45,   45,
    0,   45,   45,    0,    0,    0,    0,   45,    0,    0,
   45,   45,    0,   45,   45,   39,   37,    0,    0,    0,
    0,   39,   39,   39,    0,    0,    0,    0,   39,   39,
   39,   39,   39,   39,   39,   39,    0,   39,   39,   39,
   39,   39,   39,   39,   39,   39,   39,   39,   39,   39,
    0,   71,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   39,   39,   39,   39,    0,    0,    0,    0,    0,
    0,   39,   39,    0,   39,   39,    0,    0,    0,    0,
   39,    0,    0,   39,   39,    0,   39,   39,  155,  156,
    0,    0,    0,    0,  155,  155,  155,    0,    0,    0,
    0,  155,  155,  155,  155,  155,  155,  155,  155,    0,
  155,  155,  155,  155,  155,  155,  155,  155,  155,  155,
  155,  155,  155,    0,   42,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  155,  155,  155,  155,    0,    0,
    0,    0,    0,    0,  155,  155,    0,  155,  155,    0,
    0,    0,    0,  155,    0,    0,  155,  155,    0,  155,
  155,  158,  159,    0,    0,    0,    0,  158,  158,  158,
    0,    0,    0,    0,  158,  158,  158,  158,  158,  158,
  158,  158,    0,  158,  158,  158,  158,  158,  158,  158,
  158,  158,  158,  158,  158,  158,    0,   13,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  158,  158,  158,
  158,    0,    0,    0,    0,    0,    0,  158,  158,    0,
  158,  158,    0,    0,    0,    0,  158,    0,    0,  158,
  158,    0,  158,  158,   36,   34,    0,    0,    0,    0,
   36,   36,   36,    0,    0,    0,    0,   36,   36,   36,
   36,   36,   36,   36,   36,    0,   36,   36,   36,   36,
   36,   36,   36,   36,   36,   36,   36,   36,   36,    0,
   11,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   36,   36,   36,   36,    0,    0,    0,    0,    0,    0,
   36,   36,    0,   36,   36,    0,    0,    0,    0,   36,
    0,    0,   36,   36,    0,   36,   36,   71,   69,    0,
    0,    0,    0,   71,   71,   71,    0,    0,    0,    0,
   71,   71,   71,   71,   71,   71,   71,   71,    0,   71,
   71,   71,   71,   71,   71,   71,   71,   71,   71,   71,
   71,   71,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   71,   71,   71,   71,    0,    0,    0,
    0,    0,    0,   71,   71,    0,   71,   71,    0,    0,
    0,    0,   71,    0,    0,   71,   71,    0,   71,   71,
   42,   40,    0,    0,    0,    0,   42,   42,   42,    0,
    0,    0,    0,   42,   42,   42,   42,   42,   42,   42,
   42,    0,   42,   42,   42,   42,   42,   42,   42,   42,
   42,   42,   42,   42,   42,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   42,   42,   42,   42,
    0,    0,    0,    0,    0,    0,   42,   42,    0,   42,
   42,    0,    0,    0,    0,   42,    0,    0,   42,   42,
    0,   42,   42,   13,    0,    0,    0,    0,    0,   13,
   13,   13,    0,    0,    0,    0,   13,   13,   13,   13,
   13,   13,   13,   13,    0,   13,   13,   13,   13,   13,
   13,   13,   13,   13,   13,   13,   13,   13,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   13,
   13,   13,   13,    0,    0,    0,    0,    0,    0,   13,
   13,    0,   13,   13,    0,    0,    0,    0,   13,    0,
    0,   13,   13,    0,   13,   13,   11,    0,    0,    0,
    0,    0,   11,   11,   11,    0,    0,    0,    0,   11,
   11,   11,   11,   11,   11,   11,   11,    0,   11,   11,
   11,   11,   11,   11,   11,   11,   11,   11,   11,   11,
   11,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   11,   11,   11,   11,    0,  231,  232,    0,
    0,    0,   11,   11,  135,   11,   11,  233,  136,  137,
    0,   11,    0,    0,   11,   11,    0,   11,   11,    0,
    0,  234,    0,  138,    0,  235,  236,  237,  238,  239,
  240,  134,    0,    0,    0,  134,  134,    0,    0,    0,
    0,    0,  139,  140,    0,  141,    0,  126,    0,    0,
  134,  126,  126,  142,  143,  144,  145,  146,   40,    0,
    0,    0,    0,    0,    0,    0,  126,    0,    0,  134,
  134,  124,  134,    0,    0,  124,  124,    0,    0,    0,
  134,  134,  134,  134,  134,  126,  126,  120,  126,    0,
  124,  120,  120,    0,    0,    0,  126,  126,  126,  126,
  126,    0,    0,    0,    0,    0,  120,    0,    0,  124,
  124,  122,  124,    0,    0,  122,  122,    0,    0,    0,
  124,  124,  124,  124,  124,  120,  120,  118,  120,    0,
  122,  118,  118,    0,    0,    0,  120,  120,  120,  120,
  120,    0,    0,    0,    0,    0,  118,    0,    0,  122,
  122,  128,  122,    0,    0,  128,  128,    0,    0,    0,
  122,  122,  122,  122,  122,  118,  118,  130,  118,    0,
  128,  130,  130,    0,    0,    0,  118,  118,  118,  118,
  118,    0,    0,    0,    0,    0,  130,    0,    0,  128,
  128,  132,  128,    0,    0,  132,  132,    0,    0,    0,
  128,  128,  128,  128,  128,  130,  130,  136,  130,    0,
  132,  136,  136,    0,    0,    0,  130,  130,  130,  130,
  130,    0,    0,    0,    0,    0,  136,    0,    0,  132,
  132,  138,  132,    0,    0,  138,  138,    0,    0,    0,
  132,  132,  132,  132,  132,  136,  136,    0,  136,    0,
  138,    0,    0,    0,    0,    0,  136,  136,  136,  136,
  136,  243,  244,    0,    0,    0,    0,    0,    0,  138,
  138,  245,  138,    0,    0,    0,    0,    0,    0,    0,
  138,  138,  138,  138,  138,  246,    0,    0,    0,  247,
  248,  249,  250,  251,  252,  112,  113,    0,  115,  116,
  117,  118,  119,    0,    0,  122,  123,  124,    0,    0,
    0,    0,  127,  128,  129,
};
const short yycheck[] =
	{                                      15,
    0,  258,  258,  301,   16,  258,  258,  258,  258,   62,
  314,  258,  258,  258,  258,  328,  265,  266,   71,  314,
  268,  319,  320,   35,  328,  257,    4,  319,  320,  257,
  328,   47,  257,  301,  322,   13,  259,  257,  257,  257,
   18,  257,  257,  291,  292,  293,  294,  257,  258,   27,
  257,  259,  300,  257,   32,   33,   68,  322,   36,  301,
  301,  318,  306,  319,  320,  314,  300,  317,  318,   47,
  260,  328,  256,    0,   52,  328,  328,  328,  262,  263,
  264,  328,  328,  328,  323,  269,  270,  271,  272,  273,
  274,  275,  276,  257,  278,  279,  280,  281,  282,  283,
  284,  285,  286,  287,  288,  289,  290,  317,  318,  125,
  126,  319,  320,  300,  260,    0,  266,   95,  302,  303,
  304,  305,   91,   -1,   -1,   -1,  104,   -1,  312,  313,
   -1,  315,  316,   -1,   -1,   -1,   -1,  321,   -1,   -1,
  324,  325,   -1,  327,  328,   -1,    0,   -1,   -1,  161,
   -1,  268,   -1,   -1,  166,   -1,   -1,   -1,  136,  137,
  138,  139,  140,  141,  142,  143,  144,  145,  146,   -1,
   -1,  149,   -1,  151,  291,  292,  293,  294,  194,   -1,
   -1,  159,  160,  300,  162,   -1,   -1,   -1,   -1,  201,
   -1,   -1,   -1,  209,   -1,  173,  174,  175,  176,  177,
  178,  179,  180,  181,  182,  183,  184,  185,  268,   -1,
  188,   -1,   -1,  191,  192,   -1,  228,   -1,  230,    0,
   -1,  199,   -1,   -1,  240,   -1,   -1,  205,   -1,   -1,
   -1,  291,  292,  293,  294,   -1,  252,   -1,   -1,   -1,
  300,   -1,   -1,   -1,   -1,   -1,  258,   -1,  260,  261,
  228,  263,   -1,   -1,   -1,   -1,  256,  257,   -1,   -1,
   -1,   -1,  262,  263,  264,  281,   -1,   -1,   -1,  269,
  270,  271,  272,  273,  274,  275,  276,  255,  278,  279,
  280,  281,  282,  283,  284,  285,  286,  287,  288,  289,
  290,   -1,    0,   -1,   -1,   -1,   -1,  275,  276,   -1,
   -1,  279,  302,  303,  304,  305,   -1,   -1,   -1,   -1,
   -1,   -1,  312,  313,   -1,  315,  316,   -1,   -1,   -1,
   -1,  321,   -1,   -1,  324,  325,   -1,  327,  328,  256,
  257,   -1,   -1,   -1,   -1,  262,  263,  264,   -1,   -1,
   -1,   -1,  269,  270,  271,  272,  273,  274,  275,  276,
   -1,  278,  279,  280,  281,  282,  283,  284,  285,  286,
  287,  288,  289,  290,   -1,    0,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  302,  303,  304,  305,   -1,
   -1,   -1,   -1,   -1,   -1,  312,  313,   -1,  315,  316,
   -1,   -1,   -1,   -1,  321,   -1,   -1,  324,  325,   -1,
  327,  328,  256,  257,   -1,   -1,   -1,   -1,  262,  263,
  264,   -1,   -1,   -1,   -1,  269,  270,  271,  272,  273,
  274,  275,  276,   -1,  278,  279,  280,  281,  282,  283,
  284,  285,  286,  287,  288,  289,  290,   -1,    0,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  302,  303,
  304,  305,   -1,   -1,   -1,   -1,   -1,   -1,  312,  313,
   -1,  315,  316,   -1,   -1,   -1,   -1,  321,   -1,   -1,
  324,  325,   -1,  327,  328,  256,  257,   -1,   -1,   -1,
   -1,  262,  263,  264,   -1,   -1,   -1,   -1,  269,  270,
  271,  272,  273,  274,  275,  276,   -1,  278,  279,  280,
  281,  282,  283,  284,  285,  286,  287,  288,  289,  290,
   -1,    0,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  302,  303,  304,  305,   -1,   -1,   -1,   -1,   -1,
   -1,  312,  313,   -1,  315,  316,   -1,   -1,   -1,   -1,
  321,   -1,   -1,  324,  325,   -1,  327,  328,  256,  257,
   -1,   -1,   -1,   -1,  262,  263,  264,   -1,   -1,   -1,
   -1,  269,  270,  271,  272,  273,  274,  275,  276,   -1,
  278,  279,  280,  281,  282,  283,  284,  285,  286,  287,
  288,  289,  290,   -1,    0,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  302,  303,  304,  305,   -1,   -1,
   -1,   -1,   -1,   -1,  312,  313,   -1,  315,  316,   -1,
   -1,   -1,   -1,  321,   -1,   -1,  324,  325,   -1,  327,
  328,  256,  257,   -1,   -1,   -1,   -1,  262,  263,  264,
   -1,   -1,   -1,   -1,  269,  270,  271,  272,  273,  274,
  275,  276,   -1,  278,  279,  280,  281,  282,  283,  284,
  285,  286,  287,  288,  289,  290,   -1,    0,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  302,  303,  304,
  305,   -1,   -1,   -1,   -1,   -1,   -1,  312,  313,   -1,
  315,  316,   -1,   -1,   -1,   -1,  321,   -1,   -1,  324,
  325,   -1,  327,  328,  256,  257,   -1,   -1,   -1,   -1,
  262,  263,  264,   -1,   -1,   -1,   -1,  269,  270,  271,
  272,  273,  274,  275,  276,   -1,  278,  279,  280,  281,
  282,  283,  284,  285,  286,  287,  288,  289,  290,   -1,
    0,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  302,  303,  304,  305,   -1,   -1,   -1,   -1,   -1,   -1,
  312,  313,   -1,  315,  316,   -1,   -1,   -1,   -1,  321,
   -1,   -1,  324,  325,   -1,  327,  328,  256,  257,   -1,
   -1,   -1,   -1,  262,  263,  264,   -1,   -1,   -1,   -1,
  269,  270,  271,  272,  273,  274,  275,  276,   -1,  278,
  279,  280,  281,  282,  283,  284,  285,  286,  287,  288,
  289,  290,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  302,  303,  304,  305,   -1,   -1,   -1,
   -1,   -1,   -1,  312,  313,   -1,  315,  316,   -1,   -1,
   -1,   -1,  321,   -1,   -1,  324,  325,   -1,  327,  328,
  256,  257,   -1,   -1,   -1,   -1,  262,  263,  264,   -1,
   -1,   -1,   -1,  269,  270,  271,  272,  273,  274,  275,
  276,   -1,  278,  279,  280,  281,  282,  283,  284,  285,
  286,  287,  288,  289,  290,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  302,  303,  304,  305,
   -1,   -1,   -1,   -1,   -1,   -1,  312,  313,   -1,  315,
  316,   -1,   -1,   -1,   -1,  321,   -1,   -1,  324,  325,
   -1,  327,  328,  256,   -1,   -1,   -1,   -1,   -1,  262,
  263,  264,   -1,   -1,   -1,   -1,  269,  270,  271,  272,
  273,  274,  275,  276,   -1,  278,  279,  280,  281,  282,
  283,  284,  285,  286,  287,  288,  289,  290,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  302,
  303,  304,  305,   -1,   -1,   -1,   -1,   -1,   -1,  312,
  313,   -1,  315,  316,   -1,   -1,   -1,   -1,  321,   -1,
   -1,  324,  325,   -1,  327,  328,  256,   -1,   -1,   -1,
   -1,   -1,  262,  263,  264,   -1,   -1,   -1,   -1,  269,
  270,  271,  272,  273,  274,  275,  276,   -1,  278,  279,
  280,  281,  282,  283,  284,  285,  286,  287,  288,  289,
  290,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  302,  303,  304,  305,   -1,  267,  268,   -1,
   -1,   -1,  312,  313,  258,  315,  316,  277,  262,  263,
   -1,  321,   -1,   -1,  324,  325,   -1,  327,  328,   -1,
   -1,  291,   -1,  277,   -1,  295,  296,  297,  298,  299,
  300,  258,   -1,   -1,   -1,  262,  263,   -1,   -1,   -1,
   -1,   -1,  296,  297,   -1,  299,   -1,  258,   -1,   -1,
  277,  262,  263,  307,  308,  309,  310,  311,  328,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  277,   -1,   -1,  296,
  297,  258,  299,   -1,   -1,  262,  263,   -1,   -1,   -1,
  307,  308,  309,  310,  311,  296,  297,  258,  299,   -1,
  277,  262,  263,   -1,   -1,   -1,  307,  308,  309,  310,
  311,   -1,   -1,   -1,   -1,   -1,  277,   -1,   -1,  296,
  297,  258,  299,   -1,   -1,  262,  263,   -1,   -1,   -1,
  307,  308,  309,  310,  311,  296,  297,  258,  299,   -1,
  277,  262,  263,   -1,   -1,   -1,  307,  308,  309,  310,
  311,   -1,   -1,   -1,   -1,   -1,  277,   -1,   -1,  296,
  297,  258,  299,   -1,   -1,  262,  263,   -1,   -1,   -1,
  307,  308,  309,  310,  311,  296,  297,  258,  299,   -1,
  277,  262,  263,   -1,   -1,   -1,  307,  308,  309,  310,
  311,   -1,   -1,   -1,   -1,   -1,  277,   -1,   -1,  296,
  297,  258,  299,   -1,   -1,  262,  263,   -1,   -1,   -1,
  307,  308,  309,  310,  311,  296,  297,  258,  299,   -1,
  277,  262,  263,   -1,   -1,   -1,  307,  308,  309,  310,
  311,   -1,   -1,   -1,   -1,   -1,  277,   -1,   -1,  296,
  297,  258,  299,   -1,   -1,  262,  263,   -1,   -1,   -1,
  307,  308,  309,  310,  311,  296,  297,   -1,  299,   -1,
  277,   -1,   -1,   -1,   -1,   -1,  307,  308,  309,  310,
  311,  267,  268,   -1,   -1,   -1,   -1,   -1,   -1,  296,
  297,  277,  299,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  307,  308,  309,  310,  311,  291,   -1,   -1,   -1,  295,
  296,  297,  298,  299,  300,   69,   70,   -1,   72,   73,
   74,   75,   76,   -1,   -1,   79,   80,   81,   -1,   -1,
   -1,   -1,   86,   87,   88,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 328
#if YYDEBUG
const char * const yyname[] =
	{
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"LB","RB","LP","RP","MENUS",
"MENU","BUTTON","DEFAULT_FUNCTION","PLUS","MINUS","ALL","OR","CURSORS",
"PIXMAPS","ICONS","COLOR","SAVECOLOR","MONOCHROME","FUNCTION","ICONMGR_SHOW",
"ICONMGR","WINDOW_FUNCTION","ZOOM","ICONMGRS","ICONMGR_GEOMETRY",
"ICONMGR_NOSHOW","MAKE_TITLE","GRAYSCALE","ICONIFY_BY_UNMAPPING",
"DONT_ICONIFY_BY_UNMAPPING","NO_TITLE","AUTO_RAISE","NO_HILITE","ICON_REGION",
"META","SHIFT","LOCK","CONTROL","WINDOW","TITLE","ICON","ROOT","FRAME","COLON",
"EQUALS","SQUEEZE_TITLE","DONT_SQUEEZE_TITLE","START_ICONIFIED",
"NO_TITLE_HILITE","TITLE_HILITE","MOVE","RESIZE","WAIT","SELECT","KILL",
"LEFT_TITLEBUTTON","RIGHT_TITLEBUTTON","NUMBER","KEYWORD","NKEYWORD","CKEYWORD",
"CLKEYWORD","FKEYWORD","FSKEYWORD","SKEYWORD","DKEYWORD","JKEYWORD",
"WINDOW_RING","WARP_CURSOR","ERRORTOKEN","NO_STACKMODE","STRING",
};
const char * const yyrule[] =
	{"$accept : twmrc",
"twmrc : stmts",
"stmts :",
"stmts : stmts stmt",
"stmt : error",
"stmt : noarg",
"stmt : sarg",
"stmt : narg",
"stmt : squeeze",
"stmt : ICON_REGION string DKEYWORD DKEYWORD number number",
"stmt : ICONMGR_GEOMETRY string number",
"stmt : ICONMGR_GEOMETRY string",
"stmt : ZOOM number",
"stmt : ZOOM",
"stmt : PIXMAPS pixmap_list",
"stmt : CURSORS cursor_list",
"$$1 :",
"stmt : ICONIFY_BY_UNMAPPING $$1 win_list",
"stmt : ICONIFY_BY_UNMAPPING",
"stmt : LEFT_TITLEBUTTON string EQUALS action",
"stmt : RIGHT_TITLEBUTTON string EQUALS action",
"stmt : button string",
"stmt : button action",
"stmt : string fullkey",
"stmt : button full",
"$$2 :",
"stmt : DONT_ICONIFY_BY_UNMAPPING $$2 win_list",
"$$3 :",
"stmt : ICONMGR_NOSHOW $$3 win_list",
"stmt : ICONMGR_NOSHOW",
"$$4 :",
"stmt : ICONMGRS $$4 iconm_list",
"$$5 :",
"stmt : ICONMGR_SHOW $$5 win_list",
"$$6 :",
"stmt : NO_TITLE_HILITE $$6 win_list",
"stmt : NO_TITLE_HILITE",
"$$7 :",
"stmt : NO_HILITE $$7 win_list",
"stmt : NO_HILITE",
"$$8 :",
"stmt : NO_STACKMODE $$8 win_list",
"stmt : NO_STACKMODE",
"$$9 :",
"stmt : NO_TITLE $$9 win_list",
"stmt : NO_TITLE",
"$$10 :",
"stmt : MAKE_TITLE $$10 win_list",
"$$11 :",
"stmt : START_ICONIFIED $$11 win_list",
"$$12 :",
"stmt : AUTO_RAISE $$12 win_list",
"$$13 :",
"stmt : MENU string LP string COLON string RP $$13 menu",
"$$14 :",
"stmt : MENU string $$14 menu",
"$$15 :",
"stmt : FUNCTION string $$15 function",
"$$16 :",
"stmt : ICONS $$16 icon_list",
"$$17 :",
"stmt : COLOR $$17 color_list",
"$$18 :",
"stmt : GRAYSCALE $$18 color_list",
"stmt : SAVECOLOR save_color_list",
"$$19 :",
"stmt : MONOCHROME $$19 color_list",
"stmt : DEFAULT_FUNCTION action",
"stmt : WINDOW_FUNCTION action",
"$$20 :",
"stmt : WARP_CURSOR $$20 win_list",
"stmt : WARP_CURSOR",
"$$21 :",
"stmt : WINDOW_RING $$21 win_list",
"noarg : KEYWORD",
"sarg : SKEYWORD string",
"narg : NKEYWORD number",
"full : EQUALS keys COLON contexts COLON action",
"fullkey : EQUALS keys COLON contextkeys COLON action",
"keys :",
"keys : keys key",
"key : META",
"key : SHIFT",
"key : LOCK",
"key : CONTROL",
"key : META number",
"key : OR",
"contexts :",
"contexts : contexts context",
"context : WINDOW",
"context : TITLE",
"context : ICON",
"context : ROOT",
"context : FRAME",
"context : ICONMGR",
"context : META",
"context : ALL",
"context : OR",
"contextkeys :",
"contextkeys : contextkeys contextkey",
"contextkey : WINDOW",
"contextkey : TITLE",
"contextkey : ICON",
"contextkey : ROOT",
"contextkey : FRAME",
"contextkey : ICONMGR",
"contextkey : META",
"contextkey : ALL",
"contextkey : OR",
"contextkey : string",
"pixmap_list : LB pixmap_entries RB",
"pixmap_entries :",
"pixmap_entries : pixmap_entries pixmap_entry",
"pixmap_entry : TITLE_HILITE string",
"cursor_list : LB cursor_entries RB",
"cursor_entries :",
"cursor_entries : cursor_entries cursor_entry",
"cursor_entry : FRAME string string",
"cursor_entry : FRAME string",
"cursor_entry : TITLE string string",
"cursor_entry : TITLE string",
"cursor_entry : ICON string string",
"cursor_entry : ICON string",
"cursor_entry : ICONMGR string string",
"cursor_entry : ICONMGR string",
"cursor_entry : BUTTON string string",
"cursor_entry : BUTTON string",
"cursor_entry : MOVE string string",
"cursor_entry : MOVE string",
"cursor_entry : RESIZE string string",
"cursor_entry : RESIZE string",
"cursor_entry : WAIT string string",
"cursor_entry : WAIT string",
"cursor_entry : MENU string string",
"cursor_entry : MENU string",
"cursor_entry : SELECT string string",
"cursor_entry : SELECT string",
"cursor_entry : KILL string string",
"cursor_entry : KILL string",
"color_list : LB color_entries RB",
"color_entries :",
"color_entries : color_entries color_entry",
"color_entry : CLKEYWORD string",
"$$22 :",
"color_entry : CLKEYWORD string $$22 win_color_list",
"color_entry : CKEYWORD string",
"save_color_list : LB s_color_entries RB",
"s_color_entries :",
"s_color_entries : s_color_entries s_color_entry",
"s_color_entry : string",
"s_color_entry : CLKEYWORD",
"win_color_list : LB win_color_entries RB",
"win_color_entries :",
"win_color_entries : win_color_entries win_color_entry",
"win_color_entry : string string",
"squeeze : SQUEEZE_TITLE",
"$$23 :",
"squeeze : SQUEEZE_TITLE $$23 LB win_sqz_entries RB",
"squeeze : DONT_SQUEEZE_TITLE",
"$$24 :",
"squeeze : DONT_SQUEEZE_TITLE $$24 win_list",
"win_sqz_entries :",
"win_sqz_entries : win_sqz_entries string JKEYWORD signed_number number",
"iconm_list : LB iconm_entries RB",
"iconm_entries :",
"iconm_entries : iconm_entries iconm_entry",
"iconm_entry : string string number",
"iconm_entry : string string string number",
"win_list : LB win_entries RB",
"win_entries :",
"win_entries : win_entries win_entry",
"win_entry : string",
"icon_list : LB icon_entries RB",
"icon_entries :",
"icon_entries : icon_entries icon_entry",
"icon_entry : string string",
"function : LB function_entries RB",
"function_entries :",
"function_entries : function_entries function_entry",
"function_entry : action",
"menu : LB menu_entries RB",
"menu_entries :",
"menu_entries : menu_entries menu_entry",
"menu_entry : string action",
"menu_entry : string LP string COLON string RP action",
"action : FKEYWORD",
"action : FSKEYWORD string",
"signed_number : number",
"signed_number : PLUS number",
"signed_number : MINUS number",
"button : BUTTON number",
"string : STRING",
"number : NUMBER",
};
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH 10000
#endif
#endif
#define YYINITSTACKSIZE 200
/* LINTUSED */
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short *yyss;
short *yysslim;
YYSTYPE *yyvs;
unsigned int yystacksize;
int yyparse(void);
#line 658 "gram.y"

static void
yyerror(const char *s)
{
    parseWarning("error in input file:  %s", s ? s : "");
    ParseError = 1;
}

static void
RemoveDQuote(char *str)
{
    register char *i, *o;
    register int n;
    register int count;

    for (i = str + 1, o = str; *i && *i != '\"'; o++) {
        if (*i == '\\') {
            switch (*++i) {
            case 'n':
                *o = '\n';
                i++;
                break;
            case 'b':
                *o = '\b';
                i++;
                break;
            case 'r':
                *o = '\r';
                i++;
                break;
            case 't':
                *o = '\t';
                i++;
                break;
            case 'f':
                *o = '\f';
                i++;
                break;
            case '0':
                if (*++i == 'x')
                    goto hex;
                else
                    --i;
                /* FALLTHRU */
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
                n = 0;
                count = 0;
                while (*i >= '0' && *i <= '7' && count < 3) {
                    n = (n << 3) + (*i++ - '0');
                    count++;
                }
                *o = (char) n;
                break;
              hex:
            case 'x':
                n = 0;
                count = 0;
                while (i++, count++ < 2) {
                    if (*i >= '0' && *i <= '9')
                        n = (n << 4) + (*i - '0');
                    else if (*i >= 'a' && *i <= 'f')
                        n = (n << 4) + (*i - 'a') + 10;
                    else if (*i >= 'A' && *i <= 'F')
                        n = (n << 4) + (*i - 'A') + 10;
                    else
                        break;
                }
                *o = (char) n;
                break;
            case '\n':
                i++;            /* punt */
                o--;            /* to account for o++ at end of loop */
                break;
            case '\"':
            case '\'':
            case '\\':
            default:
                *o = *i++;
                break;
            }
        }
        else
            *o = *i++;
    }
    *o = '\0';
}

static MenuRoot *
GetRoot(const char *name, const char *fore, const char *back)
{
    MenuRoot *tmp;

    tmp = FindMenuRoot(name);
    if (tmp == NULL)
        tmp = NewMenuRoot(name);

    if (fore) {
        int save;

        save = Scr->FirstTime;
        Scr->FirstTime = TRUE;
        GetColor(COLOR, &tmp->hi_fore, fore);
        GetColor(COLOR, &tmp->hi_back, back);
        Scr->FirstTime = (short) save;
    }

    return tmp;
}

static void
GotButton(int butt, int func)
{
    int i;

    for (i = 0; i < NUM_CONTEXTS; i++) {
        if ((cont & (1 << i)) == 0)
            continue;

        Scr->Mouse[butt][i][mods].func = func;
        if (func == F_MENU) {
            pull->prev = NULL;
            Scr->Mouse[butt][i][mods].menu = pull;
        }
        else {
            root = GetRoot(TWM_ROOT, NULLSTR, NULLSTR);
            Scr->Mouse[butt][i][mods].item = AddToMenu(root, "x", Action,
                                                       NULL, func, NULLSTR, NULLSTR);
        }
    }
    Action = empty;
    pull = NULL;
    cont = 0;
    mods_used |= (unsigned) mods;
    mods = 0;
}

static void
GotKey(char *key, int func)
{
    int i;

    for (i = 0; i < NUM_CONTEXTS; i++) {
        if ((cont & (1 << i)) == 0)
            continue;
        if (!AddFuncKey(key, i, mods, func, Name, Action))
            break;
    }

    Action = empty;
    pull = NULL;
    cont = 0;
    mods_used |= (unsigned) mods;
    mods = 0;
}

static void
GotTitleButton(char *bitmapname, int func, Bool rightside)
{
    if (!CreateTitleButton(bitmapname, func, Action, pull, rightside, True)) {
        parseWarning("unable to create %s titlebutton \"%s\"",
                     rightside ? "right" : "left", bitmapname);
    }
    Action = empty;
    pull = NULL;
}

static Bool
CheckWarpScreenArg(char *s)
{
    XmuCopyISOLatin1Lowered(s, s);

    if (strcmp(s, WARPSCREEN_NEXT) == 0 ||
        strcmp(s, WARPSCREEN_PREV) == 0 ||
        strcmp(s, WARPSCREEN_BACK) == 0)
        return True;

    for (; *s && isascii(*s) && isdigit(*s); s++);      /* SUPPRESS 530 */
    return (*s ? False : True);
}

static Bool
CheckWarpRingArg(char *s)
{
    XmuCopyISOLatin1Lowered(s, s);

    if (strcmp(s, WARPSCREEN_NEXT) == 0 ||
        strcmp(s, WARPSCREEN_PREV) == 0)
        return True;

    return False;
}

static Bool
CheckColormapArg(char *s)
{
    XmuCopyISOLatin1Lowered(s, s);

    if (strcmp(s, COLORMAP_NEXT) == 0 ||
        strcmp(s, COLORMAP_PREV) == 0 ||
        strcmp(s, COLORMAP_DEFAULT) == 0)
        return True;

    return False;
}
#line 1028 "gram.c"
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(void)
{
    unsigned int newsize;
    long sslen;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = yystacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;
    sslen = yyssp - yyss;
#ifdef SIZE_MAX
#define YY_SIZE_MAX SIZE_MAX
#else
#define YY_SIZE_MAX 0xffffffffU
#endif
    if (newsize && YY_SIZE_MAX / newsize < sizeof *newss)
        goto bail;
    newss = (short *)realloc(yyss, newsize * sizeof *newss);
    if (newss == NULL)
        goto bail;
    yyss = newss;
    yyssp = newss + sslen;
    if (newsize && YY_SIZE_MAX / newsize < sizeof *newvs)
        goto bail;
    newvs = (YYSTYPE *)realloc(yyvs, newsize * sizeof *newvs);
    if (newvs == NULL)
        goto bail;
    yyvs = newvs;
    yyvsp = newvs + sslen;
    yystacksize = newsize;
    yysslim = yyss + newsize - 1;
    return 0;
bail:
    if (yyss)
            free(yyss);
    if (yyvs)
            free(yyvs);
    yyss = yyssp = NULL;
    yyvs = yyvsp = NULL;
    yystacksize = 0;
    return -1;
}

#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse(void)
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif /* YYDEBUG */

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    if (yyss == NULL && yygrowstack()) goto yyoverflow;
    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yysslim && yygrowstack())
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#if defined(__GNUC__)
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#if defined(__GNUC__)
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yysslim && yygrowstack())
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yyvsp[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 9:
#line 152 "gram.y"
{ AddIconRegion(yyvsp[-4].ptr, yyvsp[-3].num, yyvsp[-2].num, yyvsp[-1].num, yyvsp[0].num); }
break;
case 10:
#line 153 "gram.y"
{ if (Scr->FirstTime)
                                                  {
                                                    Scr->iconmgr.geometry=yyvsp[-1].ptr;
                                                    Scr->iconmgr.columns=yyvsp[0].num;
                                                  }
                                                }
break;
case 11:
#line 159 "gram.y"
{ if (Scr->FirstTime)
                                                    Scr->iconmgr.geometry = yyvsp[0].ptr;
                                                }
break;
case 12:
#line 162 "gram.y"
{ if (Scr->FirstTime)
                                          {
                                                Scr->DoZoom = TRUE;
                                                Scr->ZoomCount = (short)yyvsp[0].num;
                                          }
                                        }
break;
case 13:
#line 168 "gram.y"
{ if (Scr->FirstTime)
                                                Scr->DoZoom = TRUE; }
break;
case 14:
#line 170 "gram.y"
{}
break;
case 15:
#line 171 "gram.y"
{}
break;
case 16:
#line 172 "gram.y"
{ list = &Scr->IconifyByUn; }
break;
case 18:
#line 174 "gram.y"
{ if (Scr->FirstTime)
                    Scr->IconifyByUnmapping = TRUE; }
break;
case 19:
#line 176 "gram.y"
{
                                          GotTitleButton (yyvsp[-2].ptr, yyvsp[0].num, False);
                                        }
break;
case 20:
#line 179 "gram.y"
{
                                          GotTitleButton (yyvsp[-2].ptr, yyvsp[0].num, True);
                                        }
break;
case 21:
#line 182 "gram.y"
{ root = GetRoot(yyvsp[0].ptr, NULLSTR, NULLSTR);
                                          Scr->Mouse[yyvsp[-1].num][C_ROOT][0].func = F_MENU;
                                          Scr->Mouse[yyvsp[-1].num][C_ROOT][0].menu = root;
                                        }
break;
case 22:
#line 186 "gram.y"
{ Scr->Mouse[yyvsp[-1].num][C_ROOT][0].func = yyvsp[0].num;
                                          if (yyvsp[0].num == F_MENU)
                                          {
                                            pull->prev = NULL;
                                            Scr->Mouse[yyvsp[-1].num][C_ROOT][0].menu = pull;
                                          }
                                          else
                                          {
                                            root = GetRoot(TWM_ROOT,NULLSTR,NULLSTR);
                                            Scr->Mouse[yyvsp[-1].num][C_ROOT][0].item =
                                                AddToMenu(root,"x",Action,
                                                          NULL,yyvsp[0].num,NULLSTR,NULLSTR);
                                          }
                                          Action = empty;
                                          pull = NULL;
                                        }
break;
case 23:
#line 202 "gram.y"
{ GotKey(yyvsp[-1].ptr, yyvsp[0].num); }
break;
case 24:
#line 203 "gram.y"
{ GotButton(yyvsp[-1].num, yyvsp[0].num); }
break;
case 25:
#line 204 "gram.y"
{ list = &Scr->DontIconify; }
break;
case 27:
#line 206 "gram.y"
{ list = &Scr->IconMgrNoShow; }
break;
case 29:
#line 208 "gram.y"
{ Scr->IconManagerDontShow = TRUE; }
break;
case 30:
#line 209 "gram.y"
{ list = &Scr->IconMgrs; }
break;
case 32:
#line 211 "gram.y"
{ list = &Scr->IconMgrShow; }
break;
case 34:
#line 213 "gram.y"
{ list = &Scr->NoTitleHighlight; }
break;
case 36:
#line 215 "gram.y"
{ if (Scr->FirstTime)
                                                Scr->TitleHighlight = FALSE; }
break;
case 37:
#line 217 "gram.y"
{ list = &Scr->NoHighlight; }
break;
case 39:
#line 219 "gram.y"
{ if (Scr->FirstTime)
                                                Scr->Highlight = FALSE; }
break;
case 40:
#line 221 "gram.y"
{ list = &Scr->NoStackModeL; }
break;
case 42:
#line 223 "gram.y"
{ if (Scr->FirstTime)
                                                Scr->StackMode = FALSE; }
break;
case 43:
#line 225 "gram.y"
{ list = &Scr->NoTitle; }
break;
case 45:
#line 227 "gram.y"
{ if (Scr->FirstTime)
                                                Scr->NoTitlebar = TRUE; }
break;
case 46:
#line 229 "gram.y"
{ list = &Scr->MakeTitle; }
break;
case 48:
#line 231 "gram.y"
{ list = &Scr->StartIconified; }
break;
case 50:
#line 233 "gram.y"
{ list = &Scr->AutoRaise; }
break;
case 52:
#line 235 "gram.y"
{
                                        root = GetRoot(yyvsp[-5].ptr, yyvsp[-3].ptr, yyvsp[-1].ptr); }
break;
case 53:
#line 237 "gram.y"
{ root->real_menu = TRUE;}
break;
case 54:
#line 238 "gram.y"
{ root = GetRoot(yyvsp[0].ptr, NULLSTR, NULLSTR); }
break;
case 55:
#line 239 "gram.y"
{ root->real_menu = TRUE; }
break;
case 56:
#line 240 "gram.y"
{ root = GetRoot(yyvsp[0].ptr, NULLSTR, NULLSTR); }
break;
case 58:
#line 242 "gram.y"
{ list = &Scr->IconNames; }
break;
case 60:
#line 244 "gram.y"
{ color = COLOR; }
break;
case 62:
#line 246 "gram.y"
{ color = GRAYSCALE; }
break;
case 65:
#line 250 "gram.y"
{ color = MONOCHROME; }
break;
case 67:
#line 252 "gram.y"
{ Scr->DefaultFunction.func = yyvsp[0].num;
                                          if (yyvsp[0].num == F_MENU)
                                          {
                                            pull->prev = NULL;
                                            Scr->DefaultFunction.menu = pull;
                                          }
                                          else
                                          {
                                            root = GetRoot(TWM_ROOT,NULLSTR,NULLSTR);
                                            Scr->DefaultFunction.item =
                                                AddToMenu(root,"x",Action,
                                                          NULL,yyvsp[0].num, NULLSTR, NULLSTR);
                                          }
                                          Action = empty;
                                          pull = NULL;
                                        }
break;
case 68:
#line 268 "gram.y"
{ Scr->WindowFunction.func = yyvsp[0].num;
                                           root = GetRoot(TWM_ROOT,NULLSTR,NULLSTR);
                                           Scr->WindowFunction.item =
                                                AddToMenu(root,"x",Action,
                                                          NULL,yyvsp[0].num, NULLSTR, NULLSTR);
                                           Action = empty;
                                           pull = NULL;
                                        }
break;
case 69:
#line 276 "gram.y"
{ list = &Scr->WarpCursorL; }
break;
case 71:
#line 278 "gram.y"
{ if (Scr->FirstTime)
                                            Scr->WarpCursor = TRUE; }
break;
case 72:
#line 280 "gram.y"
{ list = &Scr->WindowRingL; }
break;
case 74:
#line 285 "gram.y"
{ if (!do_single_keyword (yyvsp[0].num)) {
                                            parseWarning (
                                                 "unknown singleton keyword %d",
                                                 yyvsp[0].num);
                                            ParseError = 1;
                                          }
                                        }
break;
case 75:
#line 294 "gram.y"
{ if (!do_string_keyword (yyvsp[-1].num, yyvsp[0].ptr)) {
                                            parseWarning (
                                                 "unknown string keyword %d (value \"%s\")",
                                                 yyvsp[-1].num, yyvsp[0].ptr);
                                            ParseError = 1;
                                          }
                                        }
break;
case 76:
#line 303 "gram.y"
{ if (!do_number_keyword (yyvsp[-1].num, yyvsp[0].num)) {
                                            parseWarning (
                                                 "unknown numeric keyword %d (value %d)",
                                                 yyvsp[-1].num, yyvsp[0].num);
                                            ParseError = 1;
                                          }
                                        }
break;
case 77:
#line 314 "gram.y"
{ yyval.num = yyvsp[0].num; }
break;
case 78:
#line 317 "gram.y"
{ yyval.num = yyvsp[0].num; }
break;
case 81:
#line 324 "gram.y"
{ mods |= Mod1Mask; }
break;
case 82:
#line 325 "gram.y"
{ mods |= ShiftMask; }
break;
case 83:
#line 326 "gram.y"
{ mods |= LockMask; }
break;
case 84:
#line 327 "gram.y"
{ mods |= ControlMask; }
break;
case 85:
#line 328 "gram.y"
{ if (yyvsp[0].num < 1 || yyvsp[0].num > 5) {
                                             parseWarning (
                                                  "bad modifier number (%d), must be 1-5",
                                                  yyvsp[0].num);
                                             ParseError = 1;
                                          } else {
                                             mods |= (Mod1Mask << (yyvsp[0].num - 1));
                                          }
                                        }
break;
case 86:
#line 337 "gram.y"
{ }
break;
case 89:
#line 344 "gram.y"
{ cont |= C_WINDOW_BIT; }
break;
case 90:
#line 345 "gram.y"
{ cont |= C_TITLE_BIT; }
break;
case 91:
#line 346 "gram.y"
{ cont |= C_ICON_BIT; }
break;
case 92:
#line 347 "gram.y"
{ cont |= C_ROOT_BIT; }
break;
case 93:
#line 348 "gram.y"
{ cont |= C_FRAME_BIT; }
break;
case 94:
#line 349 "gram.y"
{ cont |= C_ICONMGR_BIT; }
break;
case 95:
#line 350 "gram.y"
{ cont |= C_ICONMGR_BIT; }
break;
case 96:
#line 351 "gram.y"
{ cont |= C_ALL_BITS; }
break;
case 97:
#line 352 "gram.y"
{  }
break;
case 100:
#line 359 "gram.y"
{ cont |= C_WINDOW_BIT; }
break;
case 101:
#line 360 "gram.y"
{ cont |= C_TITLE_BIT; }
break;
case 102:
#line 361 "gram.y"
{ cont |= C_ICON_BIT; }
break;
case 103:
#line 362 "gram.y"
{ cont |= C_ROOT_BIT; }
break;
case 104:
#line 363 "gram.y"
{ cont |= C_FRAME_BIT; }
break;
case 105:
#line 364 "gram.y"
{ cont |= C_ICONMGR_BIT; }
break;
case 106:
#line 365 "gram.y"
{ cont |= C_ICONMGR_BIT; }
break;
case 107:
#line 366 "gram.y"
{ cont |= C_ALL_BITS; }
break;
case 108:
#line 367 "gram.y"
{ }
break;
case 109:
#line 368 "gram.y"
{ Name = yyvsp[0].ptr; cont |= C_NAME_BIT; }
break;
case 113:
#line 379 "gram.y"
{ SetHighlightPixmap (yyvsp[0].ptr); }
break;
case 117:
#line 390 "gram.y"
{
                        NewBitmapCursor(&Scr->FrameCursor, yyvsp[-1].ptr, yyvsp[0].ptr); }
break;
case 118:
#line 392 "gram.y"
{
                        NewFontCursor(&Scr->FrameCursor, yyvsp[0].ptr); }
break;
case 119:
#line 394 "gram.y"
{
                        NewBitmapCursor(&Scr->TitleCursor, yyvsp[-1].ptr, yyvsp[0].ptr); }
break;
case 120:
#line 396 "gram.y"
{
                        NewFontCursor(&Scr->TitleCursor, yyvsp[0].ptr); }
break;
case 121:
#line 398 "gram.y"
{
                        NewBitmapCursor(&Scr->IconCursor, yyvsp[-1].ptr, yyvsp[0].ptr); }
break;
case 122:
#line 400 "gram.y"
{
                        NewFontCursor(&Scr->IconCursor, yyvsp[0].ptr); }
break;
case 123:
#line 402 "gram.y"
{
                        NewBitmapCursor(&Scr->IconMgrCursor, yyvsp[-1].ptr, yyvsp[0].ptr); }
break;
case 124:
#line 404 "gram.y"
{
                        NewFontCursor(&Scr->IconMgrCursor, yyvsp[0].ptr); }
break;
case 125:
#line 406 "gram.y"
{
                        NewBitmapCursor(&Scr->ButtonCursor, yyvsp[-1].ptr, yyvsp[0].ptr); }
break;
case 126:
#line 408 "gram.y"
{
                        NewFontCursor(&Scr->ButtonCursor, yyvsp[0].ptr); }
break;
case 127:
#line 410 "gram.y"
{
                        NewBitmapCursor(&Scr->MoveCursor, yyvsp[-1].ptr, yyvsp[0].ptr); }
break;
case 128:
#line 412 "gram.y"
{
                        NewFontCursor(&Scr->MoveCursor, yyvsp[0].ptr); }
break;
case 129:
#line 414 "gram.y"
{
                        NewBitmapCursor(&Scr->ResizeCursor, yyvsp[-1].ptr, yyvsp[0].ptr); }
break;
case 130:
#line 416 "gram.y"
{
                        NewFontCursor(&Scr->ResizeCursor, yyvsp[0].ptr); }
break;
case 131:
#line 418 "gram.y"
{
                        NewBitmapCursor(&Scr->WaitCursor, yyvsp[-1].ptr, yyvsp[0].ptr); }
break;
case 132:
#line 420 "gram.y"
{
                        NewFontCursor(&Scr->WaitCursor, yyvsp[0].ptr); }
break;
case 133:
#line 422 "gram.y"
{
                        NewBitmapCursor(&Scr->MenuCursor, yyvsp[-1].ptr, yyvsp[0].ptr); }
break;
case 134:
#line 424 "gram.y"
{
                        NewFontCursor(&Scr->MenuCursor, yyvsp[0].ptr); }
break;
case 135:
#line 426 "gram.y"
{
                        NewBitmapCursor(&Scr->SelectCursor, yyvsp[-1].ptr, yyvsp[0].ptr); }
break;
case 136:
#line 428 "gram.y"
{
                        NewFontCursor(&Scr->SelectCursor, yyvsp[0].ptr); }
break;
case 137:
#line 430 "gram.y"
{
                        NewBitmapCursor(&Scr->DestroyCursor, yyvsp[-1].ptr, yyvsp[0].ptr); }
break;
case 138:
#line 432 "gram.y"
{
                        NewFontCursor(&Scr->DestroyCursor, yyvsp[0].ptr); }
break;
case 142:
#line 444 "gram.y"
{ if (!do_colorlist_keyword (yyvsp[-1].num, color,
                                                                     yyvsp[0].ptr)) {
                                            parseWarning (
                                                 "unhandled list color keyword %d (string \"%s\")",
                                                 yyvsp[-1].num, yyvsp[0].ptr);
                                            ParseError = 1;
                                          }
                                        }
break;
case 143:
#line 452 "gram.y"
{ list = do_colorlist_keyword(yyvsp[-1].num,color,
                                                                      yyvsp[0].ptr);
                                          if (!list) {
                                            parseWarning (
                                                 "unhandled color list keyword %d (string \"%s\")",
                                                 yyvsp[-1].num, yyvsp[0].ptr);
                                            ParseError = 1;
                                          }
                                        }
break;
case 144:
#line 461 "gram.y"
{ /* No action */; }
break;
case 145:
#line 462 "gram.y"
{ if (!do_color_keyword (yyvsp[-1].num, color,
                                                                 yyvsp[0].ptr)) {
                                            parseWarning (
                                                 "unhandled color keyword %d (string \"%s\")",
                                                 yyvsp[-1].num, yyvsp[0].ptr);
                                            ParseError = 1;
                                          }
                                        }
break;
case 149:
#line 479 "gram.y"
{ do_string_savecolor(color, yyvsp[0].ptr); }
break;
case 150:
#line 480 "gram.y"
{ do_var_savecolor(yyvsp[0].num); }
break;
case 154:
#line 490 "gram.y"
{ if (Scr->FirstTime &&
                                              color == Scr->Monochrome)
                                            AddToList(list, yyvsp[-1].ptr, yyvsp[0].ptr); }
break;
case 155:
#line 495 "gram.y"
{
                                    if (HasShape) Scr->SqueezeTitle = TRUE;
                                }
break;
case 156:
#line 498 "gram.y"
{ list = &Scr->SqueezeTitleL;
                                  if (HasShape && Scr->SqueezeTitle == -1)
                                    Scr->SqueezeTitle = TRUE;
                                }
break;
case 158:
#line 503 "gram.y"
{ Scr->SqueezeTitle = FALSE; }
break;
case 159:
#line 504 "gram.y"
{ list = &Scr->DontSqueezeTitleL; }
break;
case 162:
#line 509 "gram.y"
{
                                if (Scr->FirstTime) {
                                   do_squeeze_entry (list, yyvsp[-3].ptr, yyvsp[-2].num, yyvsp[-1].num, yyvsp[0].num);
                                }
                        }
break;
case 166:
#line 524 "gram.y"
{ if (Scr->FirstTime)
                                            AddToList(list, yyvsp[-2].ptr, (char *)
                                                AllocateIconManager(yyvsp[-2].ptr, NULLSTR,
                                                        yyvsp[-1].ptr,yyvsp[0].num));
                                        }
break;
case 167:
#line 530 "gram.y"
{ if (Scr->FirstTime)
                                            AddToList(list, yyvsp[-3].ptr, (char *)
                                                AllocateIconManager(yyvsp[-3].ptr,yyvsp[-2].ptr,
                                                yyvsp[-1].ptr, yyvsp[0].num));
                                        }
break;
case 171:
#line 544 "gram.y"
{ if (Scr->FirstTime)
                                            AddToList(list, yyvsp[0].ptr, 0);
                                        }
break;
case 175:
#line 556 "gram.y"
{ if (Scr->FirstTime) AddToList(list, yyvsp[-1].ptr, yyvsp[0].ptr); }
break;
case 179:
#line 566 "gram.y"
{ AddToMenu(root, empty, Action, NULL, yyvsp[0].num,
                                                NULLSTR, NULLSTR);
                                          Action = empty;
                                        }
break;
case 183:
#line 579 "gram.y"
{ AddToMenu(root, yyvsp[-1].ptr, Action, pull, yyvsp[0].num,
                                                NULLSTR, NULLSTR);
                                          Action = empty;
                                          pull = NULL;
                                        }
break;
case 184:
#line 584 "gram.y"
{
                                          AddToMenu(root, yyvsp[-6].ptr, Action, pull, yyvsp[0].num,
                                                yyvsp[-4].ptr, yyvsp[-2].ptr);
                                          Action = empty;
                                          pull = NULL;
                                        }
break;
case 185:
#line 592 "gram.y"
{ yyval.num = yyvsp[0].num; }
break;
case 186:
#line 593 "gram.y"
{
                                yyval.num = yyvsp[-1].num;
                                Action = yyvsp[0].ptr;
                                switch (yyvsp[-1].num) {
                                  case F_MENU:
                                    pull = GetRoot (yyvsp[0].ptr, NULLSTR,NULLSTR);
                                    pull->prev = root;
                                    break;
                                  case F_WARPRING:
                                    if (!CheckWarpRingArg (Action)) {
                                        parseWarning (
                                             "ignoring invalid f.warptoring argument \"%s\"",
                                             Action);
                                        yyval.num = F_NOP;
                                    }
                                    break;
                                  case F_WARPTOSCREEN:
                                    if (!CheckWarpScreenArg (Action)) {
                                        parseWarning (
                                             "ignoring invalid f.warptoscreen argument \"%s\"",
                                             Action);
                                        yyval.num = F_NOP;
                                    }
                                    break;
                                  case F_COLORMAP:
                                    if (CheckColormapArg (Action)) {
                                        yyval.num = F_COLORMAP;
                                    } else {
                                        parseWarning (
                                             "ignoring invalid f.colormap argument \"%s\"",
                                             Action);
                                        yyval.num = F_NOP;
                                    }
                                    break;
                                } /* end switch */
                                   }
break;
case 187:
#line 632 "gram.y"
{ yyval.num = yyvsp[0].num; }
break;
case 188:
#line 633 "gram.y"
{ yyval.num = yyvsp[0].num; }
break;
case 189:
#line 634 "gram.y"
{ yyval.num = -(yyvsp[0].num); }
break;
case 190:
#line 637 "gram.y"
{ yyval.num = yyvsp[0].num;
                                          if (yyvsp[0].num == 0)
                                                yyerror("bad button 0");

                                          if (yyvsp[0].num > MAX_BUTTONS)
                                          {
                                                yyval.num = 0;
                                                yyerror("button number too large");
                                          }
                                        }
break;
case 191:
#line 649 "gram.y"
{ ptr = strdup(yyvsp[0].ptr);
                                          RemoveDQuote(ptr);
                                          yyval.ptr = ptr;
                                        }
break;
case 192:
#line 654 "gram.y"
{ yyval.num = yyvsp[0].num; }
break;
#line 1934 "gram.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yysslim && yygrowstack())
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    if (yyss)
            free(yyss);
    if (yyvs)
            free(yyvs);
    yyss = yyssp = NULL;
    yyvs = yyvsp = NULL;
    yystacksize = 0;
    return (1);
yyaccept:
    if (yyss)
            free(yyss);
    if (yyvs)
            free(yyvs);
    yyss = yyssp = NULL;
    yyvs = yyvsp = NULL;
    yystacksize = 0;
    return (0);
}
