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
#ifndef YYSTYPE_DEFINED
#define YYSTYPE_DEFINED
typedef union
{
    int num;
    char *ptr;
} YYSTYPE;
#endif /* YYSTYPE_DEFINED */
extern YYSTYPE yylval;
