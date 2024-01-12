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
#line 92 "xkbparse.y"
#ifdef DEBUG
#define	YYDEBUG 1
#endif
#define	DEBUG_VAR parseDebug
#include "parseutils.h"
#include <X11/keysym.h>
#include <X11/extensions/XKBgeom.h>
#include <stdlib.h>

unsigned int parseDebug;

#line 110 "xkbparse.y"
#ifndef YYSTYPE_DEFINED
#define YYSTYPE_DEFINED
typedef union	{
	int		 ival;
	unsigned	 uval;
	char		*str;
	Atom	 	sval;
	ParseCommon	*any;
	ExprDef		*expr;
	VarDef		*var;
	VModDef		*vmod;
	InterpDef	*interp;
	KeyTypeDef	*keyType;
	SymbolsDef	*syms;
	ModMapDef	*modMask;
	GroupCompatDef	*groupCompat;
	IndicatorMapDef	*ledMap;
	IndicatorNameDef *ledName;
	KeycodeDef	*keyName;
	KeyAliasDef	*keyAlias;
	ShapeDef	*shape;
	SectionDef	*section;
	RowDef		*row;
	KeyDef		*key;
	OverlayDef	*overlay;
	OverlayKeyDef	*olKey;
	OutlineDef	*outline;
	DoodadDef	*doodad;
	XkbFile		*file;
} YYSTYPE;
#endif /* YYSTYPE_DEFINED */
#line 57 "xkbparse.c"
#define END_OF_FILE 0
#define ERROR_TOK 255
#define XKB_KEYMAP 1
#define XKB_KEYCODES 2
#define XKB_TYPES 3
#define XKB_SYMBOLS 4
#define XKB_COMPATMAP 5
#define XKB_GEOMETRY 6
#define XKB_SEMANTICS 7
#define XKB_LAYOUT 8
#define INCLUDE 10
#define OVERRIDE 11
#define AUGMENT 12
#define REPLACE 13
#define ALTERNATE 14
#define VIRTUAL_MODS 20
#define TYPE 21
#define INTERPRET 22
#define ACTION_TOK 23
#define KEY 24
#define ALIAS 25
#define GROUP 26
#define MODIFIER_MAP 27
#define INDICATOR 28
#define SHAPE 29
#define KEYS 30
#define ROW 31
#define SECTION 32
#define OVERLAY 33
#define TEXT 34
#define OUTLINE 35
#define SOLID 36
#define LOGO 37
#define VIRTUAL 38
#define EQUALS 40
#define PLUS 41
#define MINUS 42
#define DIVIDE 43
#define TIMES 44
#define OBRACE 45
#define CBRACE 46
#define OPAREN 47
#define CPAREN 48
#define OBRACKET 49
#define CBRACKET 50
#define DOT 51
#define COMMA 52
#define SEMI 53
#define EXCLAM 54
#define INVERT 55
#define STRING 60
#define INTEGER 61
#define FLOAT 62
#define IDENT 63
#define KEYNAME 64
#define PARTIAL 70
#define DEFAULT 71
#define HIDDEN 72
#define ALPHANUMERIC_KEYS 73
#define MODIFIER_KEYS 74
#define KEYPAD_KEYS 75
#define FUNCTION_KEYS 76
#define ALTERNATE_GROUP 77
#define YYERRCODE 256
const short yylhs[] =
	{                                        -1,
    0,    0,    0,   72,   72,   71,    5,    5,    5,   68,
   68,   69,   70,    6,    6,    6,    6,    6,   12,   12,
   11,   11,   10,   10,   10,   10,   10,   10,   10,   10,
   21,   21,   22,   22,   22,   22,   22,   22,   22,   22,
   22,   22,   22,   22,   22,   22,   22,   37,   37,   37,
   52,   53,   41,   42,   42,   43,   43,   44,   45,   45,
   38,   38,   46,   47,   39,   39,   39,   40,   40,   40,
   40,   40,   29,   29,   49,   48,   50,   51,   51,   54,
   54,   55,   56,   56,   57,   57,   57,   57,   57,   58,
   58,   59,   59,   60,   60,   61,   61,   62,   63,   63,
   64,   65,   65,   66,   66,   66,   36,   36,   35,   67,
    9,    9,    9,    9,   17,   17,   19,   19,   19,   19,
   19,   19,   19,   19,   19,   19,   19,    8,    8,    7,
    7,    7,    7,    7,   23,   23,   24,   24,   25,   25,
   25,   25,   25,   25,   26,   26,   26,   26,   26,   26,
   26,   26,   34,   34,   33,   27,   27,   27,   27,   28,
   28,   28,   28,   31,   31,   32,   32,   32,   32,   16,
   16,   16,   30,    4,    4,    1,    1,    3,    2,   13,
   18,   18,   20,   15,   15,   14,
};
const short yylen[] =
	{                                         2,
    1,    1,    1,    2,    1,    7,    1,    1,    1,    2,
    1,    7,    4,    1,    1,    1,    1,    1,    1,    0,
    2,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    2,    0,    2,    2,    2,    2,    2,    2,    2,    2,
    2,    2,    2,    2,    2,    2,    2,    4,    2,    3,
    4,    5,    3,    3,    1,    1,    3,    6,    3,    1,
    2,    1,    6,    6,    3,    1,    0,    3,    3,    1,
    2,    1,    3,    3,    5,    6,    6,    5,    6,    6,
    6,    6,    2,    1,    5,    1,    1,    1,    1,    2,
    1,    5,    1,    3,    1,    1,    3,    6,    3,    1,
    3,    3,    1,    3,    5,    3,    3,    1,    5,    6,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    0,    1,
    1,    1,    1,    1,    1,    0,    3,    1,    3,    3,
    3,    3,    3,    1,    2,    2,    2,    2,    1,    4,
    1,    3,    3,    1,    4,    1,    3,    4,    6,    1,
    1,    1,    1,    1,    0,    3,    3,    1,    1,    1,
    1,    1,    3,    2,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    0,    1,
};
const short yydefred[] =
	{                                      0,
   23,   24,   25,   26,   27,   28,   29,   30,    0,   22,
    0,    0,    0,   11,    3,    5,    0,   21,    7,   14,
   15,   17,   16,   18,    8,    9,    0,    0,    0,   10,
    0,    4,  186,  184,    0,    0,    0,    0,   32,    0,
    0,    0,    0,  130,  132,  131,  133,  134,    0,    0,
   31,    0,    0,   47,    0,    0,    0,  117,    0,    0,
    0,    0,    0,    0,  125,    0,    0,  112,  113,  114,
    0,    0,  181,  180,  182,    0,    0,    0,    0,  116,
    0,   33,   34,   35,   38,   39,   40,   41,   42,   43,
   36,   37,   44,   45,   46,    6,   12,    0,    0,   55,
  183,    0,  171,  179,  170,  172,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   49,    0,    0,    0,   53,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   50,
    0,  119,  118,  120,  121,  122,  123,  124,  126,  127,
    0,    0,    0,    0,    0,  178,  161,  162,  163,    0,
  115,  160,    0,  144,    0,  151,    0,    0,    0,    0,
   54,   62,    0,    0,    0,    0,    0,    0,    0,   72,
    0,   66,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  108,    0,    0,  103,    0,    0,    0,   86,   88,
    0,   84,   89,   87,    0,    0,  146,  149,  145,    0,
  147,  148,    0,    0,    0,    0,    0,   51,    0,  158,
    0,   48,    0,   61,    0,    0,    0,    0,  168,    0,
  169,    0,    0,  154,    0,   71,    0,    0,    0,   52,
   75,    0,    0,   78,    0,    0,    0,  177,  176,  175,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   83,
    0,    0,  152,    0,    0,    0,    0,  139,  142,    0,
    0,   63,   58,    0,    0,   73,    0,   74,    0,    0,
   69,   64,   65,   76,    0,   77,  104,  174,    0,    0,
    0,   81,  107,   80,  102,    0,   93,    0,   91,    0,
   82,   79,  110,  150,  159,  173,    0,  166,  167,  153,
    0,    0,    0,    0,   90,    0,    0,  100,  155,  109,
  105,    0,   96,    0,   95,   85,    0,    0,    0,    0,
    0,    0,  101,   98,   99,   97,   92,   94,
};
const short yydgoto[] =
	{                                       9,
  250,  157,  158,  251,   27,   28,   49,   50,   76,   10,
   11,   29,  159,   34,   35,  229,  160,  161,   80,  162,
   40,   51,  264,  265,  186,  164,  165,  166,  180,  231,
  232,  233,  234,  235,  192,  193,  172,  173,  181,  182,
   83,   99,  100,   84,  108,   85,   86,   87,   88,  200,
   90,   91,   92,   93,   94,  201,  202,  298,  299,  324,
  325,  203,  317,  318,  194,  195,  204,   13,   14,   15,
   16,   17,
};
const short yysindex[] =
	{                                    525,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  525,  778,  525,    0,    0,    0,  525,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  -46,  -46,  679,    0,
  241,    0,    0,    0,    3,   17,  -46,  525,    0,  703,
   17,  114,    8,    0,    0,    0,    0,    0,   36,  467,
    0,   86,   93,    0,   39,   97,   24,    0,  100,  100,
  132,   39,   40,   97,    0,   97,    0,    0,    0,    0,
  169,   39,    0,    0,    0,   97,  175,   -2,  174,    0,
  176,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  195,   79,    0,
    0,  186,    0,    0,    0,    0,  204,  207,  230,  244,
  247,  259,  272,  299,  301,  309,  132,  261,  310,  678,
  678,   44,    0,  678,  678,   39,    0,  951,  678,  951,
  742,  100,  678,  678,  678,  951,   43,  724,  277,    0,
  951,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  678,  678,  678,  678,  678,    0,    0,    0,    0,  583,
    0,    0,  158,    0,  329,    0,  287,  323,  213,  595,
    0,    0,  780,  595,  796,  834,   39,    0,  351,    0,
   81,    0,  343,  265,  101,  595,  292,  854,  362,  -11,
  372,    0,  129,  152,    0,   97,  368,   97,    0,    0,
    6,    0,    0,    0,  678,  892,    0,    0,    0,  581,
    0,    0,  678,  678,  678,  678,  678,    0,  678,    0,
  678,    0,  374,    0,  381,    0,   48,    0,    0,  389,
    0,  406,  402,    0,  210,    0,  586,  423,  742,    0,
    0,  444,  678,    0,  454,  201,   -3,    0,    0,    0,
  407,  632,  458,  362,  463,   41,  913,  419,  470,    0,
  356,  479,    0,  438,  497,  107,  107,    0,    0,  595,
  485,    0,    0,  215,  678,    0,   48,    0,   44,  595,
    0,    0,    0,    0,  595,    0,    0,    0,  -11,  362,
  595,    0,    0,    0,    0,  514,    0,  269,    0,  100,
    0,    0,    0,    0,    0,    0,  522,    0,    0,    0,
  529,  242,   80,  528,    0,  548,  349,    0,    0,    0,
    0,  678,    0,  433,    0,    0,  100,  552,  100,  460,
  553,   80,    0,    0,    0,    0,    0,    0,};
const short yyrindex[] =
	{                                    985,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  993,    0,  665,    0,    0,    0,  116,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  571,  339,    0,    0,
    0,    0,    0,    0,    0,  394,  571,  725,    0,  446,
    0,  725,  519,    0,    0,    0,    0,    0,  540,    0,
    0,    0,    0,    0,    0,  112,  156,    0,  163,    0,
  262,  276,  307,  384,    0,  404,    4,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  579,  411,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  126,    0,    0,
    0,    0,    0,    0,    0,    0,  576,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  462,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  228,
    0,    0,    0,    0,  337,    0,    0,  397,    0,  167,
    0,    0,    0,  597,    0,  543,    0,  473,    0,    0,
    0,    0,    0,    0,    0,  237,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  307,  412,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  578,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  291,    0,  468,    0,    0,
    0,    0,  593,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  596,  124,  191,    0,    0,  539,
    0,    0,    0,    0,  578,    0,    0,    0,    0,  506,
    0,    0,    0,    0,  340,    0,    0,    0,    0,    0,
  534,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,};
const short yygindex[] =
	{                                      0,
  398,  -56,    0,  342,    0,  622,    0,    0,    0,  641,
    0,   46,  -50,    0,  -24,  -55,    7,  -47,    0,  -40,
  623,    0,  400, -128,  105,  382,  -33,    0,  435,  399,
    0,  451,  401,    0,  434, -177,  -39,   87,    0,  450,
    0,    0,  564,    0,    0,    0,    0,    0,    0,  647,
    0,    0,    0,    0,    0,    0,  490,    0,  410,    0,
  366,    0,    0,  392,    0,  455,  668,  684,   32,    0,
  706,    0,
};
#define YYTABLESIZE 1022
const short yytable[] =
	{                                      77,
  106,  107,   79,   36,  111,  185,  113,   98,  109,  110,
   82,  246,   41,   33,  112,  102,   81,   44,   45,   46,
   47,   48,  114,  115,  118,  116,  142,  143,   58,  144,
  247,  145,  146,  196,  148,  119,  197,  149,  198,   67,
   68,   69,   70,  127,   30,   12,  121,   38,  122,  248,
  249,  259,  127,   53,  127,  103,   78,  248,  249,   72,
  139,   39,   31,  111,  142,  143,   58,  144,   73,  145,
  146,  147,  148,   30,   65,  149,   75,  150,   98,  103,
   79,  183,   79,  178,  104,  189,  105,  189,   79,  191,
   79,  190,  227,   79,   81,   54,   81,  179,  199,  101,
  104,   73,   81,   73,   81,   73,   73,   81,  104,   75,
  105,   75,  312,   75,   75,    1,   20,  208,  208,  106,
  208,  208,   20,   20,  322,   79,  238,   79,  168,  236,
  126,  127,  239,  224,   78,  224,   78,   78,   96,   81,
   79,   81,   78,   74,   78,   97,  242,   78,  224,  216,
  217,  119,  243,   79,   81,  114,  101,  258,   79,   52,
  119,  199,  119,   74,  140,  140,  224,   81,  140,  140,
  106,  140,   81,  140,  253,  140,  140,   56,   56,   78,
  254,   78,  230,    1,    2,    3,    4,    5,    6,    7,
    8,  178,  104,  330,   78,  118,  117,  255,  214,  215,
  216,  217,  120,  256,  118,  179,  118,   78,  191,   79,
  218,  120,   78,  120,  120,  124,  175,  297,   57,   57,
  106,  308,  188,   81,  163,  167,  123,  206,  169,  170,
  128,  141,  141,  174,  125,  141,  141,  184,  141,  187,
  141,   19,  141,  141,  129,   78,  287,   25,   26,  316,
   79,  130,  254,  214,  215,  216,  217,  210,  297,  278,
  306,  279,  323,   78,   81,  222,  277,  156,  156,  156,
  156,  156,  156,  156,  131,  156,  333,  156,  316,  156,
  156,  323,  138,  132,  138,  230,  133,  321,  138,  142,
  143,   58,  144,  254,  145,  146,  147,  148,  296,   65,
  149,  121,  150,  134,   78,  214,  215,  216,  217,  261,
  121,  135,  121,  140,  314,  122,  205,  241,  266,  267,
  268,  269,   72,  270,  122,  271,  122,  214,  215,  216,
  217,   73,  214,  215,  216,  217,  220,  126,  185,   75,
  171,  280,  171,  136,  244,  137,  123,  285,  185,  185,
  185,  185,  185,  138,  141,  123,  291,  123,  185,  185,
  185,  185,  185,  185,  185,  185,  185,  185,  219,  185,
  185,  221,  185,  185,  185,  185,  185,  149,  149,  149,
  149,  149,  149,  185,  149,  137,  149,  137,  149,  149,
  237,  137,  185,   32,  328,  240,  214,  215,  216,  217,
  329,  185,  185,   32,   32,   32,   32,   32,  302,  185,
  190,  252,  257,   32,   32,   32,   32,   32,   32,   32,
   32,   32,   32,  124,   32,   32,  272,   32,   32,   32,
   32,   32,  124,  273,  124,  275,  157,  157,  157,  157,
  157,  157,  157,  126,  157,   13,  157,   32,  157,  157,
  115,  125,  126,  277,  126,  276,   32,   32,  289,  115,
  125,  115,  125,  300,   32,  129,  129,  129,  129,  129,
  129,  129,  129,  129,  129,  282,  129,  129,  331,  129,
  129,  129,  129,  129,  332,  304,   55,   56,   57,   58,
   59,   60,   61,   62,   63,   64,  284,   65,   66,  129,
   67,   68,   69,   70,   71,  336,  286,   67,  129,  129,
  292,  243,  115,   67,  181,  294,  129,  170,   70,  170,
   72,  115,  301,  115,   70,  214,  215,  216,  217,   73,
   74,  303,  207,  209,  305,  211,  212,   75,  129,  129,
  129,  129,  129,  129,  129,  129,  129,  129,  243,  129,
  129,   68,  129,  129,  129,  129,  129,   68,  313,  128,
  128,  128,  128,  128,  128,  128,  128,  128,  128,  319,
  128,  128,  129,  128,  128,  128,  128,  128,  320,  106,
  326,  129,  129,  143,  143,  106,  143,  327,  143,  129,
  143,  143,  165,  128,    1,    2,    3,    4,    5,    6,
    7,    8,  128,  128,  334,  337,  142,  143,   58,  144,
  128,  145,  146,  147,  148,  185,   65,  149,  156,  150,
   60,  214,  215,  216,  217,  136,  151,  152,  263,  213,
  311,  121,  153,  122,  176,  214,  215,  216,  217,  154,
  155,   59,  164,  135,  288,  101,  104,  156,   73,   74,
   37,   18,  142,  143,   58,  144,   75,  145,  146,  147,
  148,   43,   65,  149,    2,  150,   20,   20,   20,   20,
   20,  281,  151,  152,  307,  309,  290,  274,  153,  310,
   20,   21,   22,   23,   24,  154,  155,  293,  283,  171,
  260,  101,  104,  156,   73,   74,   89,  338,  142,  143,
   58,  144,   75,  145,  146,  147,  148,  315,   65,  149,
  295,  150,   44,   45,   46,   47,   48,   95,  151,  152,
  335,   42,   32,    0,  153,    0,   20,   20,   20,   20,
   20,  154,  155,    0,    0,    0,    0,  101,  104,  156,
   73,   74,    0,    0,  142,  143,   58,  144,   75,  145,
  146,  196,  148,    0,  197,  149,  198,   67,   68,   69,
   70,    0,  142,  143,   58,  144,    0,  145,  146,  147,
  148,    0,   65,  149,    0,  150,    0,   72,   19,   20,
   21,   22,   23,   24,   25,   26,   73,    0,    0,    0,
  176,    0,    0,    0,   75,  177,    0,    0,    0,    0,
  142,  143,   58,  144,   73,  145,  146,  147,  148,    0,
   65,  149,   75,  150,    0,    0,  142,  143,   58,  144,
    0,  145,  146,  147,  148,  223,   65,  149,    0,  150,
    0,    0,    0,   72,    0,    0,    0,    0,    0,    0,
    0,  225,   73,    0,    0,    0,    0,    0,    0,   72,
   75,    0,    0,    0,  142,  143,   58,  144,   73,  145,
  146,  147,  148,    0,   65,  226,   75,  150,    0,    0,
    0,    0,    0,    0,  142,  143,   58,  144,  227,  145,
  146,  147,  148,    0,   65,  149,    0,  150,    0,    0,
    0,    0,    0,    0,  104,    0,  228,    0,    0,  245,
    0,    0,    0,    0,   75,    0,    0,   72,    0,    0,
    0,    0,  142,  143,   58,  144,   73,  145,  146,  147,
  148,    0,   65,  149,   75,  150,    0,    0,    0,    0,
    0,    0,    0,  142,  143,   58,  144,  262,  145,  146,
  147,  148,  296,   65,  149,   72,  150,    0,    0,    0,
    0,    0,    0,    0,   73,    0,    0,    0,    0,    0,
    0,    0,   75,    0,    0,    0,   72,    0,    0,    0,
    0,  142,  143,   58,  144,   73,  145,  146,  147,  148,
    0,   65,  149,   75,  150,   20,   20,   20,   20,   20,
   20,   20,   20,   19,   19,   19,   19,   19,   19,   19,
   19,    0,    0,    0,   72,    0,    0,    0,    0,    0,
    0,    0,    0,   73,    0,    0,    0,    0,    0,    0,
    0,   75,
};
const short yycheck[] =
	{                                      50,
   57,   57,   50,   28,   61,  134,   63,   55,   59,   60,
   50,  189,   37,   60,   62,   56,   50,   10,   11,   12,
   13,   14,   63,   64,   72,   66,   21,   22,   23,   24,
   42,   26,   27,   28,   29,   76,   31,   32,   33,   34,
   35,   36,   37,   40,   13,    0,   49,   45,   51,   61,
   62,   46,   49,   46,   51,   32,   50,   61,   62,   54,
  117,   45,   17,   60,   21,   22,   23,   24,   63,   26,
   27,   28,   29,   42,   31,   32,   71,   34,  126,   32,
  128,  132,  130,  131,   61,   45,   63,   45,  136,  137,
  138,   49,   45,  141,  128,   60,  130,  131,  138,   60,
   61,   63,  136,   63,  138,   63,   63,  141,   61,   71,
   63,   71,  290,   71,   71,    0,    1,  151,  152,  176,
  154,  155,    7,    8,   45,  173,   46,  175,  122,  177,
   52,   53,   52,  173,  128,  175,  130,  131,   53,  173,
  188,  175,  136,   64,  138,   53,   46,  141,  188,   43,
   44,   40,   52,  201,  188,  196,   60,  198,  206,   46,
   49,  201,   51,   64,   41,   42,  206,  201,   45,   46,
  227,   48,  206,   50,   46,   52,   53,   52,   53,  173,
   52,  175,  176,   70,   71,   72,   73,   74,   75,   76,
   77,  239,   61,  322,  188,   40,   28,   46,   41,   42,
   43,   44,   40,   52,   49,  239,   51,  201,  256,  257,
   53,   49,  206,   51,   40,   40,  130,  257,   52,   53,
  277,  277,  136,  257,  120,  121,   53,  141,  124,  125,
   45,   41,   42,  129,   40,   45,   46,  133,   48,  135,
   50,    1,   52,   53,   41,  239,   46,    7,    8,  300,
  298,   45,   52,   41,   42,   43,   44,  153,  298,   50,
   46,   52,  313,  257,  298,   53,   52,   40,   41,   42,
   43,   44,   45,   46,   45,   48,  327,   50,  329,   52,
   53,  332,   46,   40,   48,  279,   40,   46,   52,   21,
   22,   23,   24,   52,   26,   27,   28,   29,   30,   31,
   32,   40,   34,   45,  298,   41,   42,   43,   44,  205,
   49,   40,   51,   53,   46,   40,   40,   53,  214,  215,
  216,  217,   54,  219,   49,  221,   51,   41,   42,   43,
   44,   63,   41,   42,   43,   44,   50,   47,    0,   71,
   50,  237,   52,   45,   53,   45,   40,  243,   10,   11,
   12,   13,   14,   45,   45,   49,  252,   51,   20,   21,
   22,   23,   24,   25,   26,   27,   28,   29,   40,   31,
   32,   49,   34,   35,   36,   37,   38,   41,   42,   43,
   44,   45,   46,   45,   48,   46,   50,   48,   52,   53,
   40,   52,   54,    0,   46,   53,   41,   42,   43,   44,
   52,   63,   64,   10,   11,   12,   13,   14,   53,   71,
   49,   40,   45,   20,   21,   22,   23,   24,   25,   26,
   27,   28,   29,   40,   31,   32,   53,   34,   35,   36,
   37,   38,   49,   53,   51,   47,   40,   41,   42,   43,
   44,   45,   46,   40,   48,    0,   50,   54,   52,   53,
   40,   40,   49,   52,   51,   50,   63,   64,   52,   49,
   49,   51,   51,   45,   71,   20,   21,   22,   23,   24,
   25,   26,   27,   28,   29,   53,   31,   32,   46,   34,
   35,   36,   37,   38,   52,   48,   20,   21,   22,   23,
   24,   25,   26,   27,   28,   29,   53,   31,   32,   54,
   34,   35,   36,   37,   38,   46,   53,   46,   63,   64,
   53,   52,   40,   52,   47,   53,   71,   50,   46,   52,
   54,   49,   53,   51,   52,   41,   42,   43,   44,   63,
   64,   53,  151,  152,   50,  154,  155,   71,   20,   21,
   22,   23,   24,   25,   26,   27,   28,   29,   52,   31,
   32,   46,   34,   35,   36,   37,   38,   52,   45,   20,
   21,   22,   23,   24,   25,   26,   27,   28,   29,   48,
   31,   32,   54,   34,   35,   36,   37,   38,   50,   46,
   53,   63,   64,   45,   46,   52,   48,   40,   50,   71,
   52,   53,   50,   54,   70,   71,   72,   73,   74,   75,
   76,   77,   63,   64,   53,   53,   21,   22,   23,   24,
   71,   26,   27,   28,   29,   45,   31,   32,   40,   34,
   45,   41,   42,   43,   44,   48,   41,   42,   48,   47,
  289,   49,   47,   51,   49,   41,   42,   43,   44,   54,
   55,   45,   50,   48,  247,   60,   61,   62,   63,   64,
   29,   11,   21,   22,   23,   24,   71,   26,   27,   28,
   29,   39,   31,   32,    0,   34,    2,    3,    4,    5,
    6,  237,   41,   42,  275,  277,   45,  227,   47,  279,
    2,    3,    4,    5,    6,   54,   55,  254,  239,  126,
  201,   60,   61,   62,   63,   64,   50,  332,   21,   22,
   23,   24,   71,   26,   27,   28,   29,  298,   31,   32,
  256,   34,   10,   11,   12,   13,   14,   50,   41,   42,
  329,   38,   17,   -1,   47,   -1,    2,    3,    4,    5,
    6,   54,   55,   -1,   -1,   -1,   -1,   60,   61,   62,
   63,   64,   -1,   -1,   21,   22,   23,   24,   71,   26,
   27,   28,   29,   -1,   31,   32,   33,   34,   35,   36,
   37,   -1,   21,   22,   23,   24,   -1,   26,   27,   28,
   29,   -1,   31,   32,   -1,   34,   -1,   54,    1,    2,
    3,    4,    5,    6,    7,    8,   63,   -1,   -1,   -1,
   49,   -1,   -1,   -1,   71,   54,   -1,   -1,   -1,   -1,
   21,   22,   23,   24,   63,   26,   27,   28,   29,   -1,
   31,   32,   71,   34,   -1,   -1,   21,   22,   23,   24,
   -1,   26,   27,   28,   29,   46,   31,   32,   -1,   34,
   -1,   -1,   -1,   54,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   46,   63,   -1,   -1,   -1,   -1,   -1,   -1,   54,
   71,   -1,   -1,   -1,   21,   22,   23,   24,   63,   26,
   27,   28,   29,   -1,   31,   32,   71,   34,   -1,   -1,
   -1,   -1,   -1,   -1,   21,   22,   23,   24,   45,   26,
   27,   28,   29,   -1,   31,   32,   -1,   34,   -1,   -1,
   -1,   -1,   -1,   -1,   61,   -1,   63,   -1,   -1,   46,
   -1,   -1,   -1,   -1,   71,   -1,   -1,   54,   -1,   -1,
   -1,   -1,   21,   22,   23,   24,   63,   26,   27,   28,
   29,   -1,   31,   32,   71,   34,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   21,   22,   23,   24,   46,   26,   27,
   28,   29,   30,   31,   32,   54,   34,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   63,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   71,   -1,   -1,   -1,   54,   -1,   -1,   -1,
   -1,   21,   22,   23,   24,   63,   26,   27,   28,   29,
   -1,   31,   32,   71,   34,    1,    2,    3,    4,    5,
    6,    7,    8,    1,    2,    3,    4,    5,    6,    7,
    8,   -1,   -1,   -1,   54,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   63,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   71,
};
#define YYFINAL 9
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 255
#if YYDEBUG
const char * const yyname[] =
	{
"end-of-file","XKB_KEYMAP","XKB_KEYCODES","XKB_TYPES","XKB_SYMBOLS",
"XKB_COMPATMAP","XKB_GEOMETRY","XKB_SEMANTICS","XKB_LAYOUT",0,"INCLUDE",
"OVERRIDE","AUGMENT","REPLACE","ALTERNATE",0,0,0,0,0,"VIRTUAL_MODS","TYPE",
"INTERPRET","ACTION_TOK","KEY","ALIAS","GROUP","MODIFIER_MAP","INDICATOR",
"SHAPE","KEYS","ROW","SECTION","OVERLAY","TEXT","OUTLINE","SOLID","LOGO",
"VIRTUAL",0,"EQUALS","PLUS","MINUS","DIVIDE","TIMES","OBRACE","CBRACE","OPAREN",
"CPAREN","OBRACKET","CBRACKET","DOT","COMMA","SEMI","EXCLAM","INVERT",0,0,0,0,
"STRING","INTEGER","FLOAT","IDENT","KEYNAME",0,0,0,0,0,"PARTIAL","DEFAULT",
"HIDDEN","ALPHANUMERIC_KEYS","MODIFIER_KEYS","KEYPAD_KEYS","FUNCTION_KEYS",
"ALTERNATE_GROUP",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"ERROR_TOK",
};
const char * const yyrule[] =
	{"$accept : XkbFile",
"XkbFile : XkbCompMapList",
"XkbFile : XkbMapConfigList",
"XkbFile : XkbConfig",
"XkbCompMapList : XkbCompMapList XkbCompositeMap",
"XkbCompMapList : XkbCompositeMap",
"XkbCompositeMap : OptFlags XkbCompositeType OptMapName OBRACE XkbMapConfigList CBRACE SEMI",
"XkbCompositeType : XKB_KEYMAP",
"XkbCompositeType : XKB_SEMANTICS",
"XkbCompositeType : XKB_LAYOUT",
"XkbMapConfigList : XkbMapConfigList XkbMapConfig",
"XkbMapConfigList : XkbMapConfig",
"XkbMapConfig : OptFlags FileType OptMapName OBRACE DeclList CBRACE SEMI",
"XkbConfig : OptFlags FileType OptMapName DeclList",
"FileType : XKB_KEYCODES",
"FileType : XKB_TYPES",
"FileType : XKB_COMPATMAP",
"FileType : XKB_SYMBOLS",
"FileType : XKB_GEOMETRY",
"OptFlags : Flags",
"OptFlags :",
"Flags : Flags Flag",
"Flags : Flag",
"Flag : PARTIAL",
"Flag : DEFAULT",
"Flag : HIDDEN",
"Flag : ALPHANUMERIC_KEYS",
"Flag : MODIFIER_KEYS",
"Flag : KEYPAD_KEYS",
"Flag : FUNCTION_KEYS",
"Flag : ALTERNATE_GROUP",
"DeclList : DeclList Decl",
"DeclList :",
"Decl : OptMergeMode VarDecl",
"Decl : OptMergeMode VModDecl",
"Decl : OptMergeMode InterpretDecl",
"Decl : OptMergeMode KeyNameDecl",
"Decl : OptMergeMode KeyAliasDecl",
"Decl : OptMergeMode KeyTypeDecl",
"Decl : OptMergeMode SymbolsDecl",
"Decl : OptMergeMode ModMapDecl",
"Decl : OptMergeMode GroupCompatDecl",
"Decl : OptMergeMode IndicatorMapDecl",
"Decl : OptMergeMode IndicatorNameDecl",
"Decl : OptMergeMode ShapeDecl",
"Decl : OptMergeMode SectionDecl",
"Decl : OptMergeMode DoodadDecl",
"Decl : MergeMode STRING",
"VarDecl : Lhs EQUALS Expr SEMI",
"VarDecl : Ident SEMI",
"VarDecl : EXCLAM Ident SEMI",
"KeyNameDecl : KeyName EQUALS Expr SEMI",
"KeyAliasDecl : ALIAS KeyName EQUALS KeyName SEMI",
"VModDecl : VIRTUAL_MODS VModDefList SEMI",
"VModDefList : VModDefList COMMA VModDef",
"VModDefList : VModDef",
"VModDef : Ident",
"VModDef : Ident EQUALS Expr",
"InterpretDecl : INTERPRET InterpretMatch OBRACE VarDeclList CBRACE SEMI",
"InterpretMatch : KeySym PLUS Expr",
"InterpretMatch : KeySym",
"VarDeclList : VarDeclList VarDecl",
"VarDeclList : VarDecl",
"KeyTypeDecl : TYPE String OBRACE VarDeclList CBRACE SEMI",
"SymbolsDecl : KEY KeyName OBRACE SymbolsBody CBRACE SEMI",
"SymbolsBody : SymbolsBody COMMA SymbolsVarDecl",
"SymbolsBody : SymbolsVarDecl",
"SymbolsBody :",
"SymbolsVarDecl : Lhs EQUALS Expr",
"SymbolsVarDecl : Lhs EQUALS ArrayInit",
"SymbolsVarDecl : Ident",
"SymbolsVarDecl : EXCLAM Ident",
"SymbolsVarDecl : ArrayInit",
"ArrayInit : OBRACKET OptKeySymList CBRACKET",
"ArrayInit : OBRACKET ActionList CBRACKET",
"GroupCompatDecl : GROUP Integer EQUALS Expr SEMI",
"ModMapDecl : MODIFIER_MAP Ident OBRACE ExprList CBRACE SEMI",
"IndicatorMapDecl : INDICATOR String OBRACE VarDeclList CBRACE SEMI",
"IndicatorNameDecl : INDICATOR Integer EQUALS Expr SEMI",
"IndicatorNameDecl : VIRTUAL INDICATOR Integer EQUALS Expr SEMI",
"ShapeDecl : SHAPE String OBRACE OutlineList CBRACE SEMI",
"ShapeDecl : SHAPE String OBRACE CoordList CBRACE SEMI",
"SectionDecl : SECTION String OBRACE SectionBody CBRACE SEMI",
"SectionBody : SectionBody SectionBodyItem",
"SectionBody : SectionBodyItem",
"SectionBodyItem : ROW OBRACE RowBody CBRACE SEMI",
"SectionBodyItem : VarDecl",
"SectionBodyItem : DoodadDecl",
"SectionBodyItem : IndicatorMapDecl",
"SectionBodyItem : OverlayDecl",
"RowBody : RowBody RowBodyItem",
"RowBody : RowBodyItem",
"RowBodyItem : KEYS OBRACE Keys CBRACE SEMI",
"RowBodyItem : VarDecl",
"Keys : Keys COMMA Key",
"Keys : Key",
"Key : KeyName",
"Key : OBRACE ExprList CBRACE",
"OverlayDecl : OVERLAY String OBRACE OverlayKeyList CBRACE SEMI",
"OverlayKeyList : OverlayKeyList COMMA OverlayKey",
"OverlayKeyList : OverlayKey",
"OverlayKey : KeyName EQUALS KeyName",
"OutlineList : OutlineList COMMA OutlineInList",
"OutlineList : OutlineInList",
"OutlineInList : OBRACE CoordList CBRACE",
"OutlineInList : Ident EQUALS OBRACE CoordList CBRACE",
"OutlineInList : Ident EQUALS Expr",
"CoordList : CoordList COMMA Coord",
"CoordList : Coord",
"Coord : OBRACKET SignedNumber COMMA SignedNumber CBRACKET",
"DoodadDecl : DoodadType String OBRACE VarDeclList CBRACE SEMI",
"DoodadType : TEXT",
"DoodadType : OUTLINE",
"DoodadType : SOLID",
"DoodadType : LOGO",
"FieldSpec : Ident",
"FieldSpec : Element",
"Element : ACTION_TOK",
"Element : INTERPRET",
"Element : TYPE",
"Element : KEY",
"Element : GROUP",
"Element : MODIFIER_MAP",
"Element : INDICATOR",
"Element : SHAPE",
"Element : ROW",
"Element : SECTION",
"Element : TEXT",
"OptMergeMode : MergeMode",
"OptMergeMode :",
"MergeMode : INCLUDE",
"MergeMode : AUGMENT",
"MergeMode : OVERRIDE",
"MergeMode : REPLACE",
"MergeMode : ALTERNATE",
"OptExprList : ExprList",
"OptExprList :",
"ExprList : ExprList COMMA Expr",
"ExprList : Expr",
"Expr : Expr DIVIDE Expr",
"Expr : Expr PLUS Expr",
"Expr : Expr MINUS Expr",
"Expr : Expr TIMES Expr",
"Expr : Lhs EQUALS Expr",
"Expr : Term",
"Term : MINUS Term",
"Term : PLUS Term",
"Term : EXCLAM Term",
"Term : INVERT Term",
"Term : Lhs",
"Term : FieldSpec OPAREN OptExprList CPAREN",
"Term : Terminal",
"Term : OPAREN Expr CPAREN",
"ActionList : ActionList COMMA Action",
"ActionList : Action",
"Action : FieldSpec OPAREN OptExprList CPAREN",
"Lhs : FieldSpec",
"Lhs : FieldSpec DOT FieldSpec",
"Lhs : FieldSpec OBRACKET Expr CBRACKET",
"Lhs : FieldSpec DOT FieldSpec OBRACKET Expr CBRACKET",
"Terminal : String",
"Terminal : Integer",
"Terminal : Float",
"Terminal : KeyName",
"OptKeySymList : KeySymList",
"OptKeySymList :",
"KeySymList : KeySymList COMMA KeySym",
"KeySymList : KeySymList COMMA KeySyms",
"KeySymList : KeySym",
"KeySymList : KeySyms",
"KeySym : IDENT",
"KeySym : SECTION",
"KeySym : Integer",
"KeySyms : OBRACE KeySymList CBRACE",
"SignedNumber : MINUS Number",
"SignedNumber : Number",
"Number : FLOAT",
"Number : INTEGER",
"Float : FLOAT",
"Integer : INTEGER",
"KeyName : KEYNAME",
"Ident : IDENT",
"Ident : DEFAULT",
"String : STRING",
"OptMapName : MapName",
"OptMapName :",
"MapName : STRING",
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
#line 772 "xkbparse.y"
void
yyerror(const char *s)
{
    if (warningLevel>0) {
	(void)fprintf(stderr,"%s: line %d of %s\n",s,lineNum,
					(scanFile?scanFile:"(unknown)"));
	if ((warningLevel>3))
	    (void)fprintf(stderr,"last scanned symbol is: %s\n",scanBuf);
    }
    return;
}


int
yywrap(void)
{
   return 1;
}

#line 761 "xkbparse.c"
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
case 1:
#line 169 "xkbparse.y"
{ yyval.file= rtrnValue= yyvsp[0].file; }
break;
case 2:
#line 171 "xkbparse.y"
{ yyval.file= rtrnValue= yyvsp[0].file;  }
break;
case 3:
#line 173 "xkbparse.y"
{ yyval.file= rtrnValue= yyvsp[0].file; }
break;
case 4:
#line 177 "xkbparse.y"
{ yyval.file= (XkbFile *)AppendStmt(&yyvsp[-1].file->common,&yyvsp[0].file->common); }
break;
case 5:
#line 179 "xkbparse.y"
{ yyval.file= yyvsp[0].file; }
break;
case 6:
#line 185 "xkbparse.y"
{ yyval.file= CreateXKBFile(yyvsp[-5].uval,yyvsp[-4].str,&yyvsp[-2].file->common,yyvsp[-6].uval); }
break;
case 7:
#line 188 "xkbparse.y"
{ yyval.uval= XkmKeymapFile; }
break;
case 8:
#line 189 "xkbparse.y"
{ yyval.uval= XkmSemanticsFile; }
break;
case 9:
#line 190 "xkbparse.y"
{ yyval.uval= XkmLayoutFile; }
break;
case 10:
#line 194 "xkbparse.y"
{ yyval.file= (XkbFile *)AppendStmt(&yyvsp[-1].file->common,&yyvsp[0].file->common); }
break;
case 11:
#line 196 "xkbparse.y"
{ yyval.file= yyvsp[0].file; }
break;
case 12:
#line 202 "xkbparse.y"
{ yyval.file= CreateXKBFile(yyvsp[-5].uval,yyvsp[-4].str,yyvsp[-2].any,yyvsp[-6].uval); }
break;
case 13:
#line 206 "xkbparse.y"
{ yyval.file= CreateXKBFile(yyvsp[-2].uval,yyvsp[-1].str,yyvsp[0].any,yyvsp[-3].uval); }
break;
case 14:
#line 210 "xkbparse.y"
{ yyval.uval= XkmKeyNamesIndex; }
break;
case 15:
#line 211 "xkbparse.y"
{ yyval.uval= XkmTypesIndex; }
break;
case 16:
#line 212 "xkbparse.y"
{ yyval.uval= XkmCompatMapIndex; }
break;
case 17:
#line 213 "xkbparse.y"
{ yyval.uval= XkmSymbolsIndex; }
break;
case 18:
#line 214 "xkbparse.y"
{ yyval.uval= XkmGeometryIndex; }
break;
case 19:
#line 217 "xkbparse.y"
{ yyval.uval= yyvsp[0].uval; }
break;
case 20:
#line 218 "xkbparse.y"
{ yyval.uval= 0; }
break;
case 21:
#line 221 "xkbparse.y"
{ yyval.uval= ((yyvsp[-1].uval)|(yyvsp[0].uval)); }
break;
case 22:
#line 222 "xkbparse.y"
{ yyval.uval= yyvsp[0].uval; }
break;
case 23:
#line 225 "xkbparse.y"
{ yyval.uval= XkbLC_Partial; }
break;
case 24:
#line 226 "xkbparse.y"
{ yyval.uval= XkbLC_Default; }
break;
case 25:
#line 227 "xkbparse.y"
{ yyval.uval= XkbLC_Hidden; }
break;
case 26:
#line 228 "xkbparse.y"
{ yyval.uval= XkbLC_AlphanumericKeys; }
break;
case 27:
#line 229 "xkbparse.y"
{ yyval.uval= XkbLC_ModifierKeys; }
break;
case 28:
#line 230 "xkbparse.y"
{ yyval.uval= XkbLC_KeypadKeys; }
break;
case 29:
#line 231 "xkbparse.y"
{ yyval.uval= XkbLC_FunctionKeys; }
break;
case 30:
#line 232 "xkbparse.y"
{ yyval.uval= XkbLC_AlternateGroup; }
break;
case 31:
#line 236 "xkbparse.y"
{ yyval.any= AppendStmt(yyvsp[-1].any,yyvsp[0].any); }
break;
case 32:
#line 237 "xkbparse.y"
{ yyval.any= NULL; }
break;
case 33:
#line 241 "xkbparse.y"
{
			    yyvsp[0].var->merge= StmtSetMerge(&yyvsp[0].var->common,yyvsp[-1].uval);
			    yyval.any= &yyvsp[0].var->common;
			}
break;
case 34:
#line 246 "xkbparse.y"
{
			    yyvsp[0].vmod->merge= StmtSetMerge(&yyvsp[0].vmod->common,yyvsp[-1].uval);
			    yyval.any= &yyvsp[0].vmod->common;
			}
break;
case 35:
#line 251 "xkbparse.y"
{
			    yyvsp[0].interp->merge= StmtSetMerge(&yyvsp[0].interp->common,yyvsp[-1].uval);
			    yyval.any= &yyvsp[0].interp->common;
			}
break;
case 36:
#line 256 "xkbparse.y"
{
			    yyvsp[0].keyName->merge= StmtSetMerge(&yyvsp[0].keyName->common,yyvsp[-1].uval);
			    yyval.any= &yyvsp[0].keyName->common;
			}
break;
case 37:
#line 261 "xkbparse.y"
{
			    yyvsp[0].keyAlias->merge= StmtSetMerge(&yyvsp[0].keyAlias->common,yyvsp[-1].uval);
			    yyval.any= &yyvsp[0].keyAlias->common;
			}
break;
case 38:
#line 266 "xkbparse.y"
{
			    yyvsp[0].keyType->merge= StmtSetMerge(&yyvsp[0].keyType->common,yyvsp[-1].uval);
			    yyval.any= &yyvsp[0].keyType->common;
			}
break;
case 39:
#line 271 "xkbparse.y"
{
			    yyvsp[0].syms->merge= StmtSetMerge(&yyvsp[0].syms->common,yyvsp[-1].uval);
			    yyval.any= &yyvsp[0].syms->common;
			}
break;
case 40:
#line 276 "xkbparse.y"
{
			    yyvsp[0].modMask->merge= StmtSetMerge(&yyvsp[0].modMask->common,yyvsp[-1].uval);
			    yyval.any= &yyvsp[0].modMask->common;
			}
break;
case 41:
#line 281 "xkbparse.y"
{
			    yyvsp[0].groupCompat->merge= StmtSetMerge(&yyvsp[0].groupCompat->common,yyvsp[-1].uval);
			    yyval.any= &yyvsp[0].groupCompat->common;
			}
break;
case 42:
#line 286 "xkbparse.y"
{
			    yyvsp[0].ledMap->merge= StmtSetMerge(&yyvsp[0].ledMap->common,yyvsp[-1].uval);
			    yyval.any= &yyvsp[0].ledMap->common;
			}
break;
case 43:
#line 291 "xkbparse.y"
{
			    yyvsp[0].ledName->merge= StmtSetMerge(&yyvsp[0].ledName->common,yyvsp[-1].uval);
			    yyval.any= &yyvsp[0].ledName->common;
			}
break;
case 44:
#line 296 "xkbparse.y"
{
			    yyvsp[0].shape->merge= StmtSetMerge(&yyvsp[0].shape->common,yyvsp[-1].uval);
			    yyval.any= &yyvsp[0].shape->common;
			}
break;
case 45:
#line 301 "xkbparse.y"
{
			    yyvsp[0].section->merge= StmtSetMerge(&yyvsp[0].section->common,yyvsp[-1].uval);
			    yyval.any= &yyvsp[0].section->common;
			}
break;
case 46:
#line 306 "xkbparse.y"
{
			    yyvsp[0].doodad->merge= StmtSetMerge(&yyvsp[0].doodad->common,yyvsp[-1].uval);
			    yyval.any= &yyvsp[0].doodad->common;
			}
break;
case 47:
#line 311 "xkbparse.y"
{
			    if (yyvsp[-1].uval==MergeAltForm) {
				yyerror("cannot use 'alternate' to include other maps");
				yyval.any= &IncludeCreate(scanBuf,MergeDefault)->common;
			    }
			    else {
				yyval.any= &IncludeCreate(scanBuf,yyvsp[-1].uval)->common;
			    }
                        }
break;
case 48:
#line 323 "xkbparse.y"
{ yyval.var= VarCreate(yyvsp[-3].expr,yyvsp[-1].expr); }
break;
case 49:
#line 325 "xkbparse.y"
{ yyval.var= BoolVarCreate(yyvsp[-1].sval,1); }
break;
case 50:
#line 327 "xkbparse.y"
{ yyval.var= BoolVarCreate(yyvsp[-1].sval,0); }
break;
case 51:
#line 331 "xkbparse.y"
{
			    KeycodeDef *def;

			    def= KeycodeCreate(yyvsp[-3].str,yyvsp[-1].expr);
			    if (yyvsp[-3].str)
				free(yyvsp[-3].str);
			    yyval.keyName= def;
			}
break;
case 52:
#line 342 "xkbparse.y"
{
			    KeyAliasDef	*def;
			    def= KeyAliasCreate(yyvsp[-3].str,yyvsp[-1].str);
			    if (yyvsp[-3].str)	free(yyvsp[-3].str);	
			    if (yyvsp[-1].str)	free(yyvsp[-1].str);	
			    yyval.keyAlias= def;
			}
break;
case 53:
#line 352 "xkbparse.y"
{ yyval.vmod= yyvsp[-1].vmod; }
break;
case 54:
#line 356 "xkbparse.y"
{ yyval.vmod= (VModDef *)AppendStmt(&yyvsp[-2].vmod->common,&yyvsp[0].vmod->common); }
break;
case 55:
#line 358 "xkbparse.y"
{ yyval.vmod= yyvsp[0].vmod; }
break;
case 56:
#line 362 "xkbparse.y"
{ yyval.vmod= VModCreate(yyvsp[0].sval,NULL); }
break;
case 57:
#line 364 "xkbparse.y"
{ yyval.vmod= VModCreate(yyvsp[-2].sval,yyvsp[0].expr); }
break;
case 58:
#line 370 "xkbparse.y"
{
			    yyvsp[-4].interp->def= yyvsp[-2].var;
			    yyval.interp= yyvsp[-4].interp;
			}
break;
case 59:
#line 377 "xkbparse.y"
{ yyval.interp= InterpCreate(yyvsp[-2].str, yyvsp[0].expr); }
break;
case 60:
#line 379 "xkbparse.y"
{ yyval.interp= InterpCreate(yyvsp[0].str, NULL); }
break;
case 61:
#line 383 "xkbparse.y"
{ yyval.var= (VarDef *)AppendStmt(&yyvsp[-1].var->common,&yyvsp[0].var->common); }
break;
case 62:
#line 385 "xkbparse.y"
{ yyval.var= yyvsp[0].var; }
break;
case 63:
#line 391 "xkbparse.y"
{ yyval.keyType= KeyTypeCreate(yyvsp[-4].sval,yyvsp[-2].var); }
break;
case 64:
#line 397 "xkbparse.y"
{ yyval.syms= SymbolsCreate(yyvsp[-4].str,(ExprDef *)yyvsp[-2].var); }
break;
case 65:
#line 401 "xkbparse.y"
{ yyval.var= (VarDef *)AppendStmt(&yyvsp[-2].var->common,&yyvsp[0].var->common); }
break;
case 66:
#line 403 "xkbparse.y"
{ yyval.var= yyvsp[0].var; }
break;
case 67:
#line 404 "xkbparse.y"
{ yyval.var= NULL; }
break;
case 68:
#line 408 "xkbparse.y"
{ yyval.var= VarCreate(yyvsp[-2].expr,yyvsp[0].expr); }
break;
case 69:
#line 410 "xkbparse.y"
{ yyval.var= VarCreate(yyvsp[-2].expr,yyvsp[0].expr); }
break;
case 70:
#line 412 "xkbparse.y"
{ yyval.var= BoolVarCreate(yyvsp[0].sval,1); }
break;
case 71:
#line 414 "xkbparse.y"
{ yyval.var= BoolVarCreate(yyvsp[0].sval,0); }
break;
case 72:
#line 416 "xkbparse.y"
{ yyval.var= VarCreate(NULL,yyvsp[0].expr); }
break;
case 73:
#line 420 "xkbparse.y"
{ yyval.expr= yyvsp[-1].expr; }
break;
case 74:
#line 422 "xkbparse.y"
{ yyval.expr= ExprCreateUnary(ExprActionList,TypeAction,yyvsp[-1].expr); }
break;
case 75:
#line 426 "xkbparse.y"
{ yyval.groupCompat= GroupCompatCreate(yyvsp[-3].ival,yyvsp[-1].expr); }
break;
case 76:
#line 430 "xkbparse.y"
{ yyval.modMask= ModMapCreate(yyvsp[-4].sval,yyvsp[-2].expr); }
break;
case 77:
#line 434 "xkbparse.y"
{ yyval.ledMap= IndicatorMapCreate(yyvsp[-4].sval,yyvsp[-2].var); }
break;
case 78:
#line 438 "xkbparse.y"
{ yyval.ledName= IndicatorNameCreate(yyvsp[-3].ival,yyvsp[-1].expr,False); }
break;
case 79:
#line 440 "xkbparse.y"
{ yyval.ledName= IndicatorNameCreate(yyvsp[-3].ival,yyvsp[-1].expr,True); }
break;
case 80:
#line 444 "xkbparse.y"
{ yyval.shape= ShapeDeclCreate(yyvsp[-4].sval,(OutlineDef *)&yyvsp[-2].outline->common); }
break;
case 81:
#line 446 "xkbparse.y"
{
			    OutlineDef *outlines;
			    outlines= OutlineCreate(None,yyvsp[-2].expr);
			    yyval.shape= ShapeDeclCreate(yyvsp[-4].sval,outlines);
			}
break;
case 82:
#line 454 "xkbparse.y"
{ yyval.section= SectionDeclCreate(yyvsp[-4].sval,yyvsp[-2].row); }
break;
case 83:
#line 458 "xkbparse.y"
{ yyval.row=(RowDef *)AppendStmt(&yyvsp[-1].row->common,&yyvsp[0].row->common);}
break;
case 84:
#line 460 "xkbparse.y"
{ yyval.row= yyvsp[0].row; }
break;
case 85:
#line 464 "xkbparse.y"
{ yyval.row= RowDeclCreate(yyvsp[-2].key); }
break;
case 86:
#line 466 "xkbparse.y"
{ yyval.row= (RowDef *)yyvsp[0].var; }
break;
case 87:
#line 468 "xkbparse.y"
{ yyval.row= (RowDef *)yyvsp[0].doodad; }
break;
case 88:
#line 470 "xkbparse.y"
{ yyval.row= (RowDef *)yyvsp[0].ledMap; }
break;
case 89:
#line 472 "xkbparse.y"
{ yyval.row= (RowDef *)yyvsp[0].overlay; }
break;
case 90:
#line 476 "xkbparse.y"
{ yyval.key=(KeyDef *)AppendStmt(&yyvsp[-1].key->common,&yyvsp[0].key->common);}
break;
case 91:
#line 478 "xkbparse.y"
{ yyval.key= yyvsp[0].key; }
break;
case 92:
#line 482 "xkbparse.y"
{ yyval.key= yyvsp[-2].key; }
break;
case 93:
#line 484 "xkbparse.y"
{ yyval.key= (KeyDef *)yyvsp[0].var; }
break;
case 94:
#line 488 "xkbparse.y"
{ yyval.key=(KeyDef *)AppendStmt(&yyvsp[-2].key->common,&yyvsp[0].key->common);}
break;
case 95:
#line 490 "xkbparse.y"
{ yyval.key= yyvsp[0].key; }
break;
case 96:
#line 494 "xkbparse.y"
{ yyval.key= KeyDeclCreate(yyvsp[0].str,NULL); }
break;
case 97:
#line 496 "xkbparse.y"
{ yyval.key= KeyDeclCreate(NULL,yyvsp[-1].expr); }
break;
case 98:
#line 500 "xkbparse.y"
{ yyval.overlay= OverlayDeclCreate(yyvsp[-4].sval,yyvsp[-2].olKey); }
break;
case 99:
#line 504 "xkbparse.y"
{
			    yyval.olKey= (OverlayKeyDef *)
				AppendStmt(&yyvsp[-2].olKey->common,&yyvsp[0].olKey->common);
			}
break;
case 100:
#line 509 "xkbparse.y"
{ yyval.olKey= yyvsp[0].olKey; }
break;
case 101:
#line 513 "xkbparse.y"
{ yyval.olKey= OverlayKeyCreate(yyvsp[-2].str,yyvsp[0].str); }
break;
case 102:
#line 517 "xkbparse.y"
{ yyval.outline=(OutlineDef *)AppendStmt(&yyvsp[-2].outline->common,&yyvsp[0].outline->common);}
break;
case 103:
#line 519 "xkbparse.y"
{ yyval.outline= yyvsp[0].outline; }
break;
case 104:
#line 523 "xkbparse.y"
{ yyval.outline= OutlineCreate(None,yyvsp[-1].expr); }
break;
case 105:
#line 525 "xkbparse.y"
{ yyval.outline= OutlineCreate(yyvsp[-4].sval,yyvsp[-1].expr); }
break;
case 106:
#line 527 "xkbparse.y"
{ yyval.outline= OutlineCreate(yyvsp[-2].sval,yyvsp[0].expr); }
break;
case 107:
#line 531 "xkbparse.y"
{ yyval.expr= (ExprDef *)AppendStmt(&yyvsp[-2].expr->common,&yyvsp[0].expr->common); }
break;
case 108:
#line 533 "xkbparse.y"
{ yyval.expr= yyvsp[0].expr; }
break;
case 109:
#line 537 "xkbparse.y"
{
			    ExprDef *expr;
			    expr= ExprCreate(ExprCoord,TypeUnknown);
			    expr->value.coord.x= yyvsp[-3].ival;
			    expr->value.coord.y= yyvsp[-1].ival;
			    yyval.expr= expr;
			}
break;
case 110:
#line 547 "xkbparse.y"
{ yyval.doodad= DoodadCreate(yyvsp[-5].uval,yyvsp[-4].sval,yyvsp[-2].var); }
break;
case 111:
#line 550 "xkbparse.y"
{ yyval.uval= XkbTextDoodad; }
break;
case 112:
#line 551 "xkbparse.y"
{ yyval.uval= XkbOutlineDoodad; }
break;
case 113:
#line 552 "xkbparse.y"
{ yyval.uval= XkbSolidDoodad; }
break;
case 114:
#line 553 "xkbparse.y"
{ yyval.uval= XkbLogoDoodad; }
break;
case 115:
#line 556 "xkbparse.y"
{ yyval.sval= yyvsp[0].sval; }
break;
case 116:
#line 557 "xkbparse.y"
{ yyval.sval= yyvsp[0].sval; }
break;
case 117:
#line 561 "xkbparse.y"
{ yyval.sval= XkbInternAtom(NULL,"action",False); }
break;
case 118:
#line 563 "xkbparse.y"
{ yyval.sval= XkbInternAtom(NULL,"interpret",False); }
break;
case 119:
#line 565 "xkbparse.y"
{ yyval.sval= XkbInternAtom(NULL,"type",False); }
break;
case 120:
#line 567 "xkbparse.y"
{ yyval.sval= XkbInternAtom(NULL,"key",False); }
break;
case 121:
#line 569 "xkbparse.y"
{ yyval.sval= XkbInternAtom(NULL,"group",False); }
break;
case 122:
#line 571 "xkbparse.y"
{yyval.sval=XkbInternAtom(NULL,"modifier_map",False);}
break;
case 123:
#line 573 "xkbparse.y"
{ yyval.sval= XkbInternAtom(NULL,"indicator",False); }
break;
case 124:
#line 575 "xkbparse.y"
{ yyval.sval= XkbInternAtom(NULL,"shape",False); }
break;
case 125:
#line 577 "xkbparse.y"
{ yyval.sval= XkbInternAtom(NULL,"row",False); }
break;
case 126:
#line 579 "xkbparse.y"
{ yyval.sval= XkbInternAtom(NULL,"section",False); }
break;
case 127:
#line 581 "xkbparse.y"
{ yyval.sval= XkbInternAtom(NULL,"text",False); }
break;
case 128:
#line 584 "xkbparse.y"
{ yyval.uval= yyvsp[0].uval; }
break;
case 129:
#line 585 "xkbparse.y"
{ yyval.uval= MergeDefault; }
break;
case 130:
#line 588 "xkbparse.y"
{ yyval.uval= MergeDefault; }
break;
case 131:
#line 589 "xkbparse.y"
{ yyval.uval= MergeAugment; }
break;
case 132:
#line 590 "xkbparse.y"
{ yyval.uval= MergeOverride; }
break;
case 133:
#line 591 "xkbparse.y"
{ yyval.uval= MergeReplace; }
break;
case 134:
#line 592 "xkbparse.y"
{ yyval.uval= MergeAltForm; }
break;
case 135:
#line 595 "xkbparse.y"
{ yyval.expr= yyvsp[0].expr; }
break;
case 136:
#line 596 "xkbparse.y"
{ yyval.expr= NULL; }
break;
case 137:
#line 600 "xkbparse.y"
{ yyval.expr= (ExprDef *)AppendStmt(&yyvsp[-2].expr->common,&yyvsp[0].expr->common); }
break;
case 138:
#line 602 "xkbparse.y"
{ yyval.expr= yyvsp[0].expr; }
break;
case 139:
#line 606 "xkbparse.y"
{ yyval.expr= ExprCreateBinary(OpDivide,yyvsp[-2].expr,yyvsp[0].expr); }
break;
case 140:
#line 608 "xkbparse.y"
{ yyval.expr= ExprCreateBinary(OpAdd,yyvsp[-2].expr,yyvsp[0].expr); }
break;
case 141:
#line 610 "xkbparse.y"
{ yyval.expr= ExprCreateBinary(OpSubtract,yyvsp[-2].expr,yyvsp[0].expr); }
break;
case 142:
#line 612 "xkbparse.y"
{ yyval.expr= ExprCreateBinary(OpMultiply,yyvsp[-2].expr,yyvsp[0].expr); }
break;
case 143:
#line 614 "xkbparse.y"
{ yyval.expr= ExprCreateBinary(OpAssign,yyvsp[-2].expr,yyvsp[0].expr); }
break;
case 144:
#line 616 "xkbparse.y"
{ yyval.expr= yyvsp[0].expr; }
break;
case 145:
#line 620 "xkbparse.y"
{ yyval.expr= ExprCreateUnary(OpNegate,yyvsp[0].expr->type,yyvsp[0].expr); }
break;
case 146:
#line 622 "xkbparse.y"
{ yyval.expr= ExprCreateUnary(OpUnaryPlus,yyvsp[0].expr->type,yyvsp[0].expr); }
break;
case 147:
#line 624 "xkbparse.y"
{ yyval.expr= ExprCreateUnary(OpNot,TypeBoolean,yyvsp[0].expr); }
break;
case 148:
#line 626 "xkbparse.y"
{ yyval.expr= ExprCreateUnary(OpInvert,yyvsp[0].expr->type,yyvsp[0].expr); }
break;
case 149:
#line 628 "xkbparse.y"
{ yyval.expr= yyvsp[0].expr;  }
break;
case 150:
#line 630 "xkbparse.y"
{ yyval.expr= ActionCreate(yyvsp[-3].sval,yyvsp[-1].expr); }
break;
case 151:
#line 632 "xkbparse.y"
{ yyval.expr= yyvsp[0].expr;  }
break;
case 152:
#line 634 "xkbparse.y"
{ yyval.expr= yyvsp[-1].expr;  }
break;
case 153:
#line 638 "xkbparse.y"
{ yyval.expr= (ExprDef *)AppendStmt(&yyvsp[-2].expr->common,&yyvsp[0].expr->common); }
break;
case 154:
#line 640 "xkbparse.y"
{ yyval.expr= yyvsp[0].expr; }
break;
case 155:
#line 644 "xkbparse.y"
{ yyval.expr= ActionCreate(yyvsp[-3].sval,yyvsp[-1].expr); }
break;
case 156:
#line 648 "xkbparse.y"
{
			    ExprDef *expr;
                            expr= ExprCreate(ExprIdent,TypeUnknown);
                            expr->value.str= yyvsp[0].sval;
                            yyval.expr= expr;
			}
break;
case 157:
#line 655 "xkbparse.y"
{
                            ExprDef *expr;
                            expr= ExprCreate(ExprFieldRef,TypeUnknown);
                            expr->value.field.element= yyvsp[-2].sval;
                            expr->value.field.field= yyvsp[0].sval;
                            yyval.expr= expr;
			}
break;
case 158:
#line 663 "xkbparse.y"
{
			    ExprDef *expr;
			    expr= ExprCreate(ExprArrayRef,TypeUnknown);
			    expr->value.array.element= None;
			    expr->value.array.field= yyvsp[-3].sval;
			    expr->value.array.entry= yyvsp[-1].expr;
			    yyval.expr= expr;
			}
break;
case 159:
#line 672 "xkbparse.y"
{
			    ExprDef *expr;
			    expr= ExprCreate(ExprArrayRef,TypeUnknown);
			    expr->value.array.element= yyvsp[-5].sval;
			    expr->value.array.field= yyvsp[-3].sval;
			    expr->value.array.entry= yyvsp[-1].expr;
			    yyval.expr= expr;
			}
break;
case 160:
#line 683 "xkbparse.y"
{
			    ExprDef *expr;
                            expr= ExprCreate(ExprValue,TypeString);
                            expr->value.str= yyvsp[0].sval;
                            yyval.expr= expr;
			}
break;
case 161:
#line 690 "xkbparse.y"
{
			    ExprDef *expr;
                            expr= ExprCreate(ExprValue,TypeInt);
                            expr->value.ival= yyvsp[0].ival;
                            yyval.expr= expr;
			}
break;
case 162:
#line 697 "xkbparse.y"
{
			    ExprDef *expr;
			    expr= ExprCreate(ExprValue,TypeFloat);
			    expr->value.ival= yyvsp[0].ival;
			    yyval.expr= expr;
			}
break;
case 163:
#line 704 "xkbparse.y"
{
			    ExprDef *expr;
			    expr= ExprCreate(ExprValue,TypeKeyName);
			    memset(expr->value.keyName,0,5);
			    strncpy(expr->value.keyName,yyvsp[0].str,4);
			    free(yyvsp[0].str);
			    yyval.expr= expr;
			}
break;
case 164:
#line 714 "xkbparse.y"
{ yyval.expr= yyvsp[0].expr; }
break;
case 165:
#line 715 "xkbparse.y"
{ yyval.expr= NULL; }
break;
case 166:
#line 719 "xkbparse.y"
{ yyval.expr= AppendKeysymList(yyvsp[-2].expr,yyvsp[0].str); }
break;
case 167:
#line 721 "xkbparse.y"
{ yyval.expr= AppendKeysymList(yyvsp[-2].expr,strdup("NoSymbol")); }
break;
case 168:
#line 723 "xkbparse.y"
{ yyval.expr= CreateKeysymList(yyvsp[0].str); }
break;
case 169:
#line 725 "xkbparse.y"
{ yyval.expr= CreateKeysymList(strdup("NoSymbol")); }
break;
case 170:
#line 728 "xkbparse.y"
{ yyval.str= strdup(scanBuf); }
break;
case 171:
#line 729 "xkbparse.y"
{ yyval.str= strdup("section"); }
break;
case 172:
#line 731 "xkbparse.y"
{
			    if (yyvsp[0].ival<10)	{ yyval.str= malloc(2); yyval.str[0]= '0' + yyvsp[0].ival; yyval.str[1]= '\0'; }
			    else	{ yyval.str= malloc(19); snprintf(yyval.str, 19, "0x%x", yyvsp[0].ival); }
			}
break;
case 173:
#line 738 "xkbparse.y"
{ yyval.expr= yyvsp[-1].expr; }
break;
case 174:
#line 741 "xkbparse.y"
{ yyval.ival= -yyvsp[0].ival; }
break;
case 175:
#line 742 "xkbparse.y"
{ yyval.ival= yyvsp[0].ival; }
break;
case 176:
#line 745 "xkbparse.y"
{ yyval.ival= scanInt; }
break;
case 177:
#line 746 "xkbparse.y"
{ yyval.ival= scanInt*XkbGeomPtsPerMM; }
break;
case 178:
#line 749 "xkbparse.y"
{ yyval.ival= scanInt; }
break;
case 179:
#line 752 "xkbparse.y"
{ yyval.ival= scanInt; }
break;
case 180:
#line 755 "xkbparse.y"
{ yyval.str= strdup(scanBuf); }
break;
case 181:
#line 758 "xkbparse.y"
{ yyval.sval= XkbInternAtom(NULL,scanBuf,False); }
break;
case 182:
#line 759 "xkbparse.y"
{ yyval.sval= XkbInternAtom(NULL,"default",False); }
break;
case 183:
#line 762 "xkbparse.y"
{ yyval.sval= XkbInternAtom(NULL,scanBuf,False); }
break;
case 184:
#line 765 "xkbparse.y"
{ yyval.str= yyvsp[0].str; }
break;
case 185:
#line 766 "xkbparse.y"
{ yyval.str= NULL; }
break;
case 186:
#line 769 "xkbparse.y"
{ yyval.str= strdup(scanBuf); }
break;
#line 1826 "xkbparse.c"
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
