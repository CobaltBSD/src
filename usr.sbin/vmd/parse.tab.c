/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 2
#define YYMINOR 0
#define YYPATCH 20230219

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#undef YYBTYACC
#define YYBTYACC 0
#define YYDEBUGSTR YYPREFIX "debug"
#define YYPREFIX "yy"

#define YYPURE 0

#line 26 "parse.y"
#include <sys/types.h>
#include <sys/queue.h>
#include <sys/socket.h>
#include <sys/uio.h>

#include <machine/vmmvar.h>

#include <arpa/inet.h>
#include <net/if.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <netdb.h>
#include <util.h>
#include <errno.h>
#include <err.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>

#include "vmd.h"

TAILQ_HEAD(files, file)		 files = TAILQ_HEAD_INITIALIZER(files);
static struct file {
	TAILQ_ENTRY(file)	 entry;
	FILE			*stream;
	char			*name;
	size_t			 ungetpos;
	size_t			 ungetsize;
	u_char			*ungetbuf;
	int			 eof_reached;
	int			 lineno;
	int			 errors;
} *file, *topfile;
struct file	*pushfile(const char *, int);
int		 popfile(void);
int		 yyparse(void);
int		 yylex(void);
int		 yyerror(const char *, ...)
    __attribute__((__format__ (printf, 1, 2)))
    __attribute__((__nonnull__ (1)));
int		 kw_cmp(const void *, const void *);
int		 lookup(char *);
int		 igetc(void);
int		 lgetc(int);
void		 lungetc(int);
int		 findeol(void);

TAILQ_HEAD(symhead, sym)	 symhead = TAILQ_HEAD_INITIALIZER(symhead);
struct sym {
	TAILQ_ENTRY(sym)	 entry;
	int			 used;
	int			 persist;
	char			*nam;
	char			*val;
};
int		 symset(const char *, const char *, int);
char		*symget(const char *);

ssize_t		 parse_size(char *, int64_t);
int		 parse_disk(char *, int);
unsigned int	 parse_format(const char *);

static struct vmop_create_params vmc;
static struct vm_create_params	*vcp;
static struct vmd_switch	*vsw;
static char			*kernel = NULL;
static char			 vsw_type[IF_NAMESIZE];
static int			 vmc_disable;
static size_t			 vmc_nnics;
static int			 errors;
extern struct vmd		*env;
extern const char		*vmd_descsw[];

typedef struct {
	union {
		uint8_t		 lladdr[ETHER_ADDR_LEN];
		int64_t		 number;
		char		*string;
		struct {
			uid_t	 uid;
			int64_t	 gid;
		}		 owner;
	} v;
	int lineno;
} YYSTYPE;

#line 119 "parse.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

#if !(defined(yylex) || defined(YYSTATE))
int YYLEX_DECL();
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define INCLUDE 257
#define ERROR 258
#define ADD 259
#define AGENTX 260
#define ALLOW 261
#define BOOT 262
#define CDROM 263
#define CONTEXT 264
#define DEVICE 265
#define DISABLE 266
#define DISK 267
#define DOWN 268
#define ENABLE 269
#define FORMAT 270
#define GROUP 271
#define INET6 272
#define INSTANCE 273
#define INTERFACE 274
#define LLADDR 275
#define LOCAL 276
#define LOCKED 277
#define MEMORY 278
#define NET 279
#define NIFS 280
#define OWNER 281
#define PATH 282
#define PREFIX 283
#define RDOMAIN 284
#define SIZE 285
#define SOCKET 286
#define SWITCH 287
#define UP 288
#define VM 289
#define VMID 290
#define STAGGERED 291
#define START 292
#define PARALLEL 293
#define DELAY 294
#define NUMBER 295
#define STRING 296
#define agentxopts 297
#define YYERRCODE 256
typedef int YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    0,    0,    0,    0,    0,    0,    0,   12,   13,
   14,   14,   14,   14,   17,   14,   14,   18,   15,   20,
   20,   21,   21,   21,   21,   21,   21,   23,   16,   11,
   11,   24,   24,   25,   25,   25,   25,   25,   25,   25,
   25,   25,   25,   25,   27,   27,   28,   28,   29,   29,
   29,   29,   29,   29,   29,    8,   31,    8,    8,    8,
    4,    4,   26,   26,   26,   32,   32,   33,   33,   34,
   34,   34,   34,   34,    9,    9,   10,   10,    1,    1,
    5,    5,    6,    6,    7,    7,    3,    3,    2,    2,
    2,   35,   35,   19,   19,   30,   30,   22,
};
static const YYINT yylen[] = {                            2,
    0,    3,    2,    3,    3,    3,    3,    3,    2,    3,
    2,    4,    3,    3,    0,    3,    6,    0,    7,    3,
    2,    1,    2,    2,    2,    2,    1,    0,    8,    0,
    2,    3,    2,    1,    3,    4,    2,    3,    2,    2,
    2,    2,    2,    1,    6,    3,    3,    2,    1,    1,
    1,    1,    1,    1,    2,    1,    0,    4,    2,    0,
    0,    2,    4,    1,    0,    3,    2,    3,    1,    2,
    2,    3,    2,    1,    1,    0,    2,    1,    1,    0,
    0,    1,    0,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    0,    2,    0,    2,    1,    2,
};
static const YYINT yydefred[] = {                         1,
    0,    0,    0,   15,    0,    0,    0,    0,    0,    0,
    3,    0,    0,    0,    0,    0,    8,    0,    9,    0,
    0,    0,    0,   18,    0,    0,    0,    2,    4,    5,
    6,    7,   77,   16,    0,   13,    0,   56,   57,   14,
    0,    0,   28,    0,   10,   12,   59,    0,    0,   31,
    0,    0,    0,    0,    0,    0,    0,   58,   94,   88,
   86,   87,    0,    0,    0,    0,   85,   22,   27,    0,
    0,    0,   17,   23,   24,   25,   26,   19,    0,   21,
    0,    0,    0,    0,   82,    0,    0,    0,   34,    0,
    0,    0,   44,    0,   20,    0,    0,   37,   39,    0,
   41,   42,   40,   43,    0,   29,    0,   33,   98,   49,
   53,   52,   54,   51,   50,    0,    0,   46,   89,   90,
   91,   38,    0,   35,   75,    0,   32,   55,    0,   62,
    0,   84,    0,    0,    0,    0,   74,   36,    0,   69,
    0,    0,   71,   73,   70,    0,    0,    0,   45,    0,
    0,   48,   97,    0,    0,    0,   79,   72,   92,   68,
    0,   96,   47,   63,    0,   67,   66,
};
#if defined(YYDESTRUCT_CALL) || defined(YYSTYPE_TOSTRING)
static const YYINT yystos[] = {                           0,
  299,  256,  257,  260,  276,  286,  287,  289,  291,  296,
   10,  311,  312,  313,  314,  315,   10,  296,  309,  316,
  272,  283,  281,  309,  309,  292,   61,   10,   10,   10,
   10,   10,  309,  297,  283,  296,  282,  295,  296,  307,
  317,  273,  310,  293,  296,  296,  296,  330,  123,  309,
  322,  295,  264,   10,  318,  123,  294,  296,  318,  266,
  268,  269,  271,  274,  277,  284,  288,  302,  306,  319,
  320,  318,  295,  309,  309,  275,  295,  125,  320,  318,
  261,  262,  263,  267,  276,  278,  280,  281,  302,  304,
  323,  324,  326,   10,  321,  273,  265,  309,  309,  309,
  295,  296,  295,  307,  274,  125,  324,  318,  318,  262,
  263,  267,  273,  274,  278,  281,  123,  328,  263,  267,
  279,  301,  270,  303,  296,  308,  321,  307,  318,  309,
  271,  277,  284,  287,  123,  305,  306,  325,  332,  333,
  327,  328,  309,  295,  309,  318,  275,  333,  125,   10,
   44,  318,  321,  329,  331,  333,  296,  300,   44,  334,
  318,  318,  327,  125,  333,  318,  318,
};
#endif /* YYDESTRUCT_CALL || YYSTYPE_TOSTRING */
static const YYINT yydgoto[] = {                          1,
  158,  122,   68,  124,   90,  136,  137,   40,  126,   19,
   43,   12,   13,   14,   15,   16,   20,   41,   55,   70,
   71,   95,   51,   91,   92,  138,   93,  141,  142,  154,
   48,  155,  139,  140,  160,
};
static const YYINT yysindex[] = {                         0,
  -10,   12, -271,    0, -216, -231, -271, -271, -266,   -6,
    0,   42,   48,   52,   53,   61,    0, -271,    0, -225,
 -209, -219, -253,    0, -197, -215, -213,    0,    0,    0,
    0,    0,    0,    0, -212,    0, -206,    0,    0,    0,
  -30, -271,    0, -196,    0,    0,    0, -166,   91,    0,
  -21, -189, -190,   91, -220,   91, -187,    0,    0,    0,
    0,    0, -271, -271, -165, -183,    0,    0,    0,  -29,
   91, -126,    0,    0,    0,    0,    0,    0,  103,    0,
 -159, -255, -271, -271,    0, -276, -178, -253,    0, -155,
  306,   91,    0,   91,    0,  264, -251,    0,    0, -148,
    0,    0,    0,    0, -173,    0,  103,    0,    0,    0,
    0,    0,    0,    0,    0, -253,   91,    0,    0,    0,
    0,    0, -271,    0,    0, -120,    0,    0,  359,    0,
 -271,    0, -171, -271,   91, -150,    0,    0, -202,    0,
    1,   -4,    0,    0,    0, -202, -169,   85,    0,   91,
   91,    0,    0,  359,  252,   91,    0,    0,    0,    0,
    0,    0,    0,    0,   91,    0,    0,
};
static const YYINT yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   21,    0,    0,
  120,    0,  122,    0,   10,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, -177,    0,
    0,    0,    0,  -81,    0,  349,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  222, -140,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  181,    0,    0,
 -140,  285,    0,  -52,    0,    0,    0,    0,    0,  203,
    0,    0,    0,    0,   49,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   -9,  372,    0,    0,    0,
    0,    0,    0,    0,    0,  137,    0,    0,    0,    0,
    0,    0,    0,    0, -254,    0,    0,    0,  160,    0,
    0,   13,    0,    0,    0, -136,   77,  105,    0,  326,
  372,    0,    0,    0, -136,  234,    0,    0,    0,    0,
  328,    0,    0,    0,  234,    0,    0,
};
#if YYBTYACC
static const YYINT yycindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,
};
#endif
static const YYINT yygindex[] = {                         0,
    0,    0,  -59,    0,    0,    0,  -17,  -80,    0,   -3,
    0,    0,    0,    0,    0,    0,    0,    0,  -47,    0,
   72, -105,    0,    0,   54,    0,    0,   -5,   57,    0,
    0,    0,    0, -128,    0,
};
#define YYTABLESIZE 653
static const YYINT yytable[] = {                         11,
   60,  127,  135,   24,   25,  150,   59,  104,   72,   97,
  148,  119,   89,   95,   33,  120,   95,  156,  101,  102,
   95,   17,   95,   80,   18,   26,  165,  121,   37,   95,
   78,   89,   95,   95,   60,  128,  153,   69,   50,  151,
   18,   38,   39,   95,  108,   60,  109,   61,   62,   23,
   63,   28,   69,   64,   27,   21,   65,   29,   76,   74,
   75,   30,   31,   66,   78,   61,   22,   67,  131,  129,
   32,   34,   95,   35,  132,   42,   36,   44,   98,   99,
  100,  133,   45,   46,  134,   67,   80,  146,   95,   47,
   95,   95,   49,   95,  152,   78,   95,   53,   52,   95,
   54,   56,  161,  162,   57,   58,   95,   73,  166,   76,
   95,   77,   94,   96,   93,   60,  103,  167,  105,  130,
   80,  123,  125,  144,  147,  149,  157,  143,  159,   11,
  145,   60,   30,   81,   81,   82,   83,   95,   83,   60,
   84,   79,   62,   78,  107,   78,   65,   61,  163,   85,
  131,   86,  118,   87,   88,    0,  132,    0,    0,    0,
    0,    0,    0,  133,    0,    0,  134,   67,    0,   64,
    0,   76,    0,   76,    0,    0,    0,    0,    0,   95,
   95,   95,    0,    0,   95,   95,   95,   95,    0,   95,
   60,   95,   95,   95,   95,   95,   95,    0,   95,   95,
    0,   80,   95,    0,    0,   95,   95,    0,   95,   95,
   95,    0,   61,   95,   95,   95,   95,    0,   95,    0,
    0,   95,    0,   95,   95,   95,    0,   95,   95,   93,
    0,   95,    0,    0,    0,   95,   60,    0,   61,   62,
    0,   63,    0,    0,   64,    2,    3,   65,    0,    4,
    0,   60,   60,   60,   66,    0,   60,   60,   67,   60,
    0,   65,    0,    0,   60,    5,   60,    0,   60,    0,
   60,   60,    0,    0,    0,    6,    7,    0,    8,    0,
    9,   78,   78,   78,   64,   10,   78,   78,   78,   78,
   78,   78,    0,   78,   78,   78,   78,   78,   78,    0,
   78,   78,    0,    0,   78,   60,    0,   78,   78,   76,
   76,   76,    0,    0,   76,   76,   76,   76,    0,   76,
    0,    0,   76,   76,   76,   76,   76,   61,   76,   76,
    0,    0,   76,    0,    0,   76,   76,   80,   80,   80,
    0,    0,   80,   80,   80,   80,   95,   80,    0,    0,
   80,   80,   80,   80,   80,    0,   80,   80,   95,    0,
   80,    0,    0,   80,   80,   93,   93,   93,    0,    0,
   93,   93,   93,   93,    0,   93,  164,    0,   93,   93,
   93,   93,   93,    0,   93,   93,  117,    0,   93,    0,
    0,   93,   93,    0,    0,    0,    0,   65,   65,   65,
    0,    0,   65,   65,    0,   65,    0,    0,    0,   95,
   65,   83,   65,    0,   65,    0,   65,   65,    0,    0,
   64,   64,   64,    0,    0,   64,   64,    0,   64,    0,
  106,    0,    0,   64,   83,   64,    0,   64,    0,   64,
   64,   60,   60,   60,    0,    0,   60,   60,    0,   60,
   95,    0,   94,    0,   60,    0,   60,    0,   60,    0,
   60,   60,    0,   61,   61,   61,    0,    0,   61,   61,
    0,   61,    0,    0,    0,    0,   61,    0,   61,    0,
   61,    0,   61,   61,    0,    0,    0,   95,    0,   95,
   95,    0,   95,    0,    0,   95,    0,    0,   95,    0,
    0,   95,    0,    0,   95,   95,    0,    0,   95,   95,
   95,    0,    0,    0,    0,    0,    0,   95,    0,   61,
   95,   95,  131,    0,    0,  110,  111,    0,  132,    0,
  112,    0,    0,    0,    0,  133,  113,  114,  134,   67,
    0,  115,    0,    0,  116,   95,   95,   95,    0,    0,
   95,   95,    0,   95,    0,    0,    0,    0,   95,    0,
   95,    0,   95,    0,   95,   95,   81,   82,   83,    0,
    0,   60,   84,    0,   62,    0,    0,    0,    0,    0,
    0,   85,    0,   86,    0,   87,   88,   95,   95,   98,
   98,    0,   95,    0,   98,    0,    0,    0,   95,   95,
   98,   98,    0,   95,    0,   98,   95,    0,   98,   95,
   95,   95,    0,    0,   95,   95,    0,   95,    0,    0,
  110,  111,   95,    0,   95,  112,   95,    0,   95,   95,
    0,  113,  114,   95,   95,    0,  115,    0,   95,  116,
    0,    0,    0,    0,   95,   95,    0,    0,    0,   95,
    0,    0,   95,
};
static const YYINT yycheck[] = {                         10,
   10,  107,  123,    7,    8,   10,   54,   88,   56,  265,
  139,  263,   72,  268,   18,  267,  271,  146,  295,  296,
  275,   10,  277,   71,  296,  292,  155,  279,  282,  284,
   10,   91,  287,  288,   44,  116,  142,   55,   42,   44,
  296,  295,  296,  125,   92,  266,   94,  268,  269,  281,
  271,   10,   70,  274,   61,  272,  277,   10,   10,   63,
   64,   10,   10,  284,   44,  268,  283,  288,  271,  117,
   10,  297,  125,  283,  277,  273,  296,  293,   82,   83,
   84,  284,  296,  296,  287,  288,   10,  135,  266,  296,
  268,  269,  123,  271,  142,  125,  274,  264,  295,  277,
   10,  123,  150,  151,  294,  296,  284,  295,  156,  275,
  288,  295,   10,  273,   10,  125,  295,  165,  274,  123,
   44,  270,  296,  295,  275,  125,  296,  131,   44,   10,
  134,   10,  123,  274,  261,  262,  263,  125,  275,  266,
  267,   70,  269,  123,   91,  125,   10,  268,  154,  276,
  271,  278,   96,  280,  281,   -1,  277,   -1,   -1,   -1,
   -1,   -1,   -1,  284,   -1,   -1,  287,  288,   -1,   10,
   -1,  123,   -1,  125,   -1,   -1,   -1,   -1,   -1,  261,
  262,  263,   -1,   -1,  266,  267,  268,  269,   -1,  271,
   10,  273,  274,  275,  276,  277,  278,   -1,  280,  281,
   -1,  125,  284,   -1,   -1,  287,  288,   -1,  261,  262,
  263,   -1,   10,  266,  267,  268,  269,   -1,  271,   -1,
   -1,  274,   -1,  276,  277,  278,   -1,  280,  281,  125,
   -1,  284,   -1,   -1,   -1,  288,  266,   -1,  268,  269,
   -1,  271,   -1,   -1,  274,  256,  257,  277,   -1,  260,
   -1,  261,  262,  263,  284,   -1,  266,  267,  288,  269,
   -1,  125,   -1,   -1,  274,  276,  276,   -1,  278,   -1,
  280,  281,   -1,   -1,   -1,  286,  287,   -1,  289,   -1,
  291,  261,  262,  263,  125,  296,  266,  267,  268,  269,
  270,  271,   -1,  273,  274,  275,  276,  277,  278,   -1,
  280,  281,   -1,   -1,  284,  125,   -1,  287,  288,  261,
  262,  263,   -1,   -1,  266,  267,  268,  269,   -1,  271,
   -1,   -1,  274,  275,  276,  277,  278,  125,  280,  281,
   -1,   -1,  284,   -1,   -1,  287,  288,  261,  262,  263,
   -1,   -1,  266,  267,  268,  269,  125,  271,   -1,   -1,
  274,  275,  276,  277,  278,   -1,  280,  281,  125,   -1,
  284,   -1,   -1,  287,  288,  261,  262,  263,   -1,   -1,
  266,  267,  268,  269,   -1,  271,  125,   -1,  274,  275,
  276,  277,  278,   -1,  280,  281,  123,   -1,  284,   -1,
   -1,  287,  288,   -1,   -1,   -1,   -1,  261,  262,  263,
   -1,   -1,  266,  267,   -1,  269,   -1,   -1,   -1,  125,
  274,  275,  276,   -1,  278,   -1,  280,  281,   -1,   -1,
  261,  262,  263,   -1,   -1,  266,  267,   -1,  269,   -1,
  125,   -1,   -1,  274,  275,  276,   -1,  278,   -1,  280,
  281,  261,  262,  263,   -1,   -1,  266,  267,   -1,  269,
  125,   -1,  125,   -1,  274,   -1,  276,   -1,  278,   -1,
  280,  281,   -1,  261,  262,  263,   -1,   -1,  266,  267,
   -1,  269,   -1,   -1,   -1,   -1,  274,   -1,  276,   -1,
  278,   -1,  280,  281,   -1,   -1,   -1,  266,   -1,  268,
  269,   -1,  271,   -1,   -1,  274,   -1,   -1,  277,   -1,
   -1,  268,   -1,   -1,  271,  284,   -1,   -1,  275,  288,
  277,   -1,   -1,   -1,   -1,   -1,   -1,  284,   -1,  268,
  287,  288,  271,   -1,   -1,  262,  263,   -1,  277,   -1,
  267,   -1,   -1,   -1,   -1,  284,  273,  274,  287,  288,
   -1,  278,   -1,   -1,  281,  261,  262,  263,   -1,   -1,
  266,  267,   -1,  269,   -1,   -1,   -1,   -1,  274,   -1,
  276,   -1,  278,   -1,  280,  281,  261,  262,  263,   -1,
   -1,  266,  267,   -1,  269,   -1,   -1,   -1,   -1,   -1,
   -1,  276,   -1,  278,   -1,  280,  281,  262,  263,  262,
  263,   -1,  267,   -1,  267,   -1,   -1,   -1,  273,  274,
  273,  274,   -1,  278,   -1,  278,  281,   -1,  281,  261,
  262,  263,   -1,   -1,  266,  267,   -1,  269,   -1,   -1,
  262,  263,  274,   -1,  276,  267,  278,   -1,  280,  281,
   -1,  273,  274,  262,  263,   -1,  278,   -1,  267,  281,
   -1,   -1,   -1,   -1,  273,  274,   -1,   -1,   -1,  278,
   -1,   -1,  281,
};
#if YYBTYACC
static const YYINT yyctable[] = {                        -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,
};
#endif
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 297
#define YYUNDFTOKEN 335
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"$end",0,0,0,0,0,0,0,0,0,"'\\n'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,"','",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'='",0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,"'{'",0,"'}'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"error","INCLUDE",
"ERROR","ADD","AGENTX","ALLOW","BOOT","CDROM","CONTEXT","DEVICE","DISABLE",
"DISK","DOWN","ENABLE","FORMAT","GROUP","INET6","INSTANCE","INTERFACE","LLADDR",
"LOCAL","LOCKED","MEMORY","NET","NIFS","OWNER","PATH","PREFIX","RDOMAIN","SIZE",
"SOCKET","SWITCH","UP","VM","VMID","STAGGERED","START","PARALLEL","DELAY",
"NUMBER","STRING","agentxopts","$accept","grammar","lladdr","bootdevice",
"disable","image_format","local","locked","updown","owner_id","optstring",
"string","vm_instance","include","varset","main","switch","vm","$$1","$$2",
"optnl","switch_opts_l","switch_opts","nl","$$3","vm_opts_l","vm_opts",
"iface_opts_o","instance","instance_l","instance_flags","optcommanl","$$4",
"iface_opts_l","iface_opts_c","iface_opts","optcomma","illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : grammar",
"grammar :",
"grammar : grammar include '\\n'",
"grammar : grammar '\\n'",
"grammar : grammar varset '\\n'",
"grammar : grammar main '\\n'",
"grammar : grammar switch '\\n'",
"grammar : grammar vm '\\n'",
"grammar : grammar error '\\n'",
"include : INCLUDE string",
"varset : STRING '=' STRING",
"main : LOCAL INET6",
"main : LOCAL INET6 PREFIX STRING",
"main : LOCAL PREFIX STRING",
"main : SOCKET OWNER owner_id",
"$$1 :",
"main : AGENTX $$1 agentxopts",
"main : STAGGERED START PARALLEL NUMBER DELAY NUMBER",
"$$2 :",
"switch : SWITCH string $$2 '{' optnl switch_opts_l '}'",
"switch_opts_l : switch_opts_l switch_opts nl",
"switch_opts_l : switch_opts optnl",
"switch_opts : disable",
"switch_opts : GROUP string",
"switch_opts : INTERFACE string",
"switch_opts : LOCKED LLADDR",
"switch_opts : RDOMAIN NUMBER",
"switch_opts : updown",
"$$3 :",
"vm : VM string vm_instance $$3 '{' optnl vm_opts_l '}'",
"vm_instance :",
"vm_instance : INSTANCE string",
"vm_opts_l : vm_opts_l vm_opts nl",
"vm_opts_l : vm_opts optnl",
"vm_opts : disable",
"vm_opts : DISK string image_format",
"vm_opts : local INTERFACE optstring iface_opts_o",
"vm_opts : BOOT string",
"vm_opts : BOOT DEVICE bootdevice",
"vm_opts : CDROM string",
"vm_opts : NIFS NUMBER",
"vm_opts : MEMORY NUMBER",
"vm_opts : MEMORY STRING",
"vm_opts : OWNER owner_id",
"vm_opts : instance",
"instance : ALLOW INSTANCE '{' optnl instance_l '}'",
"instance : ALLOW INSTANCE instance_flags",
"instance_l : instance_flags optcommanl instance_l",
"instance_l : instance_flags optnl",
"instance_flags : BOOT",
"instance_flags : MEMORY",
"instance_flags : INTERFACE",
"instance_flags : DISK",
"instance_flags : CDROM",
"instance_flags : INSTANCE",
"instance_flags : OWNER owner_id",
"owner_id : NUMBER",
"$$4 :",
"owner_id : STRING $$4 CONTEXT STRING",
"owner_id : PATH STRING",
"owner_id :",
"image_format :",
"image_format : FORMAT string",
"iface_opts_o : '{' optnl iface_opts_l '}'",
"iface_opts_o : iface_opts_c",
"iface_opts_o :",
"iface_opts_l : iface_opts_l iface_opts optnl",
"iface_opts_l : iface_opts optnl",
"iface_opts_c : iface_opts_c iface_opts optcomma",
"iface_opts_c : iface_opts",
"iface_opts : SWITCH string",
"iface_opts : GROUP string",
"iface_opts : locked LLADDR lladdr",
"iface_opts : RDOMAIN NUMBER",
"iface_opts : updown",
"optstring : STRING",
"optstring :",
"string : STRING string",
"string : STRING",
"lladdr : STRING",
"lladdr :",
"local :",
"local : LOCAL",
"locked :",
"locked : LOCKED",
"updown : UP",
"updown : DOWN",
"disable : ENABLE",
"disable : DISABLE",
"bootdevice : CDROM",
"bootdevice : DISK",
"bootdevice : NET",
"optcomma : ','",
"optcomma :",
"optnl : '\\n' optnl",
"optnl :",
"optcommanl : ',' optnl",
"optcommanl : nl",
"nl : '\\n' optnl",

};
#endif

#if YYDEBUG
int      yydebug;
#endif

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;
int      yynerrs;

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
YYLTYPE  yyloc; /* position returned by actions */
YYLTYPE  yylloc; /* position from the lexer */
#endif

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
#ifndef YYLLOC_DEFAULT
#define YYLLOC_DEFAULT(loc, rhs, n) \
do \
{ \
    if (n == 0) \
    { \
        (loc).first_line   = YYRHSLOC(rhs, 0).last_line; \
        (loc).first_column = YYRHSLOC(rhs, 0).last_column; \
        (loc).last_line    = YYRHSLOC(rhs, 0).last_line; \
        (loc).last_column  = YYRHSLOC(rhs, 0).last_column; \
    } \
    else \
    { \
        (loc).first_line   = YYRHSLOC(rhs, 1).first_line; \
        (loc).first_column = YYRHSLOC(rhs, 1).first_column; \
        (loc).last_line    = YYRHSLOC(rhs, n).last_line; \
        (loc).last_column  = YYRHSLOC(rhs, n).last_column; \
    } \
} while (0)
#endif /* YYLLOC_DEFAULT */
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
#if YYBTYACC

#ifndef YYLVQUEUEGROWTH
#define YYLVQUEUEGROWTH 32
#endif
#endif /* YYBTYACC */

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#ifndef YYINITSTACKSIZE
#define YYINITSTACKSIZE 200
#endif

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    YYLTYPE  *p_base;
    YYLTYPE  *p_mark;
#endif
} YYSTACKDATA;
#if YYBTYACC

struct YYParseState_s
{
    struct YYParseState_s *save;    /* Previously saved parser state */
    YYSTACKDATA            yystack; /* saved parser stack */
    int                    state;   /* saved parser state */
    int                    errflag; /* saved error recovery status */
    int                    lexeme;  /* saved index of the conflict lexeme in the lexical queue */
    YYINT                  ctry;    /* saved index in yyctable[] for this conflict */
};
typedef struct YYParseState_s YYParseState;
#endif /* YYBTYACC */
/* variables for the parser stack */
static YYSTACKDATA yystack;
#if YYBTYACC

/* Current parser state */
static YYParseState *yyps = 0;

/* yypath != NULL: do the full parse, starting at *yypath parser state. */
static YYParseState *yypath = 0;

/* Base of the lexical value queue */
static YYSTYPE *yylvals = 0;

/* Current position at lexical value queue */
static YYSTYPE *yylvp = 0;

/* End position of lexical value queue */
static YYSTYPE *yylve = 0;

/* The last allocated position at the lexical value queue */
static YYSTYPE *yylvlim = 0;

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
/* Base of the lexical position queue */
static YYLTYPE *yylpsns = 0;

/* Current position at lexical position queue */
static YYLTYPE *yylpp = 0;

/* End position of lexical position queue */
static YYLTYPE *yylpe = 0;

/* The last allocated position at the lexical position queue */
static YYLTYPE *yylplim = 0;
#endif

/* Current position at lexical token queue */
static YYINT  *yylexp = 0;

static YYINT  *yylexemes = 0;
#endif /* YYBTYACC */
#line 780 "parse.y"

struct keywords {
	const char	*k_name;
	int		 k_val;
};

int
yyerror(const char *fmt, ...)
{
	va_list		 ap;
	char		*msg;

	file->errors++;
	va_start(ap, fmt);
	if (vasprintf(&msg, fmt, ap) == -1)
		fatal("yyerror vasprintf");
	va_end(ap);
	log_warnx("%s:%d: %s", file->name, yylval.lineno, msg);
	free(msg);
	return (0);
}

int
kw_cmp(const void *k, const void *e)
{
	return (strcmp(k, ((const struct keywords *)e)->k_name));
}

int
lookup(char *s)
{
	/* this has to be sorted always */
	static const struct keywords keywords[] = {
		{ "add",		ADD },
		{ "allow",		ALLOW },
		{ "boot",		BOOT },
		{ "cdrom",		CDROM },
		{ "context",		CONTEXT},
		{ "delay",		DELAY },
		{ "device",		DEVICE },
		{ "disable",		DISABLE },
		{ "disk",		DISK },
		{ "down",		DOWN },
		{ "enable",		ENABLE },
		{ "format",		FORMAT },
		{ "group",		GROUP },
		{ "id",			VMID },
		{ "include",		INCLUDE },
		{ "inet6",		INET6 },
		{ "instance",		INSTANCE },
		{ "interface",		INTERFACE },
		{ "interfaces",		NIFS },
		{ "lladdr",		LLADDR },
		{ "local",		LOCAL },
		{ "locked",		LOCKED },
		{ "memory",		MEMORY },
		{ "net",		NET },
		{ "owner",		OWNER },
		{ "parallel",		PARALLEL },
		{ "path",		PATH },
		{ "prefix",		PREFIX },
		{ "rdomain",		RDOMAIN },
		{ "size",		SIZE },
		{ "socket",		SOCKET },
		{ "staggered",		STAGGERED },
		{ "start",		START  },
		{ "switch",		SWITCH },
		{ "up",			UP },
		{ "vm",			VM }
	};
	const struct keywords	*p;

	p = bsearch(s, keywords, sizeof(keywords)/sizeof(keywords[0]),
	    sizeof(keywords[0]), kw_cmp);

	if (p)
		return (p->k_val);
	else
		return (STRING);
}

#define START_EXPAND	1
#define DONE_EXPAND	2

static int	expanding;

int
igetc(void)
{
	int	c;

	while (1) {
		if (file->ungetpos > 0)
			c = file->ungetbuf[--file->ungetpos];
		else
			c = getc(file->stream);

		if (c == START_EXPAND)
			expanding = 1;
		else if (c == DONE_EXPAND)
			expanding = 0;
		else
			break;
	}
	return (c);
}

int
lgetc(int quotec)
{
	int		c, next;

	if (quotec) {
		if ((c = igetc()) == EOF) {
			yyerror("reached end of file while parsing "
			    "quoted string");
			if (file == topfile || popfile() == EOF)
				return (EOF);
			return (quotec);
		}
		return (c);
	}

	while ((c = igetc()) == '\\') {
		next = igetc();
		if (next != '\n') {
			c = next;
			break;
		}
		yylval.lineno = file->lineno;
		file->lineno++;
	}
	if (c == '\t' || c == ' ') {
		/* Compress blanks to a single space. */
		do {
			c = getc(file->stream);
		} while (c == '\t' || c == ' ');
		ungetc(c, file->stream);
		c = ' ';
	}

	if (c == EOF) {
		/*
		 * Fake EOL when hit EOF for the first time. This gets line
		 * count right if last line in included file is syntactically
		 * invalid and has no newline.
		 */
		if (file->eof_reached == 0) {
			file->eof_reached = 1;
			return ('\n');
		}
		while (c == EOF) {
			if (file == topfile || popfile() == EOF)
				return (EOF);
			c = igetc();
		}
	}
	return (c);
}

void
lungetc(int c)
{
	if (c == EOF)
		return;

	if (file->ungetpos >= file->ungetsize) {
		void *p = reallocarray(file->ungetbuf, file->ungetsize, 2);
		if (p == NULL)
			err(1, "%s", __func__);
		file->ungetbuf = p;
		file->ungetsize *= 2;
	}
	file->ungetbuf[file->ungetpos++] = c;
}

int
findeol(void)
{
	int	c;

	/* skip to either EOF or the first real EOL */
	while (1) {
		c = lgetc(0);
		if (c == '\n') {
			file->lineno++;
			break;
		}
		if (c == EOF)
			break;
	}
	return (ERROR);
}

int
yylex(void)
{
	char	 buf[8096];
	char	*p, *val;
	int	 quotec, next, c;
	int	 token;

top:
	p = buf;
	while ((c = lgetc(0)) == ' ' || c == '\t')
		; /* nothing */

	yylval.lineno = file->lineno;
	if (c == '#')
		while ((c = lgetc(0)) != '\n' && c != EOF)
			; /* nothing */
	if (c == '$' && !expanding) {
		while (1) {
			if ((c = lgetc(0)) == EOF)
				return (0);

			if (p + 1 >= buf + sizeof(buf) - 1) {
				yyerror("string too long");
				return (findeol());
			}
			if (isalnum(c) || c == '_') {
				*p++ = c;
				continue;
			}
			*p = '\0';
			lungetc(c);
			break;
		}
		val = symget(buf);
		if (val == NULL) {
			yyerror("macro '%s' not defined", buf);
			return (findeol());
		}
		p = val + strlen(val) - 1;
		lungetc(DONE_EXPAND);
		while (p >= val) {
			lungetc((unsigned char)*p);
			p--;
		}
		lungetc(START_EXPAND);
		goto top;
	}

	switch (c) {
	case '\'':
	case '"':
		quotec = c;
		while (1) {
			if ((c = lgetc(quotec)) == EOF)
				return (0);
			if (c == '\n') {
				file->lineno++;
				continue;
			} else if (c == '\\') {
				if ((next = lgetc(quotec)) == EOF)
					return (0);
				if (next == quotec || next == ' ' ||
				    next == '\t')
					c = next;
				else if (next == '\n') {
					file->lineno++;
					continue;
				} else
					lungetc(next);
			} else if (c == quotec) {
				*p = '\0';
				break;
			} else if (c == '\0') {
				yyerror("syntax error");
				return (findeol());
			}
			if (p + 1 >= buf + sizeof(buf) - 1) {
				yyerror("string too long");
				return (findeol());
			}
			*p++ = c;
		}
		yylval.v.string = strdup(buf);
		if (yylval.v.string == NULL)
			fatal("yylex: strdup");
		return (STRING);
	}

#define allowed_to_end_number(x) \
	(isspace(x) || x == ')' || x ==',' || x == '/' || x == '}' || x == '=')

	if (c == '-' || isdigit(c)) {
		do {
			*p++ = c;
			if ((size_t)(p-buf) >= sizeof(buf)) {
				yyerror("string too long");
				return (findeol());
			}
		} while ((c = lgetc(0)) != EOF && isdigit(c));
		lungetc(c);
		if (p == buf + 1 && buf[0] == '-')
			goto nodigits;
		if (c == EOF || allowed_to_end_number(c)) {
			const char *errstr = NULL;

			*p = '\0';
			yylval.v.number = strtonum(buf, LLONG_MIN,
			    LLONG_MAX, &errstr);
			if (errstr) {
				yyerror("\"%s\" invalid number: %s",
				    buf, errstr);
				return (findeol());
			}
			return (NUMBER);
		} else {
nodigits:
			while (p > buf + 1)
				lungetc((unsigned char)*--p);
			c = (unsigned char)*--p;
			if (c == '-')
				return (c);
		}
	}

#define allowed_in_string(x) \
	(isalnum(x) || (ispunct(x) && x != '(' && x != ')' && \
	x != '{' && x != '}' && \
	x != '!' && x != '=' && x != '#' && \
	x != ','))

	if (isalnum(c) || c == ':' || c == '_' || c == '/') {
		do {
			*p++ = c;
			if ((size_t)(p-buf) >= sizeof(buf)) {
				yyerror("string too long");
				return (findeol());
			}
		} while ((c = lgetc(0)) != EOF && (allowed_in_string(c)));
		lungetc(c);
		*p = '\0';
		if ((token = lookup(buf)) == STRING)
			if ((yylval.v.string = strdup(buf)) == NULL)
				fatal("yylex: strdup");
		return (token);
	}
	if (c == '\n') {
		yylval.lineno = file->lineno;
		file->lineno++;
	}
	if (c == EOF)
		return (0);
	return (c);
}

struct file *
pushfile(const char *name, int secret)
{
	struct file	*nfile;

	if ((nfile = calloc(1, sizeof(struct file))) == NULL) {
		log_warn("%s", __func__);
		return (NULL);
	}
	if ((nfile->name = strdup(name)) == NULL) {
		log_warn("%s", __func__);
		free(nfile);
		return (NULL);
	}
	if ((nfile->stream = fopen(nfile->name, "r")) == NULL) {
		free(nfile->name);
		free(nfile);
		return (NULL);
	}
	nfile->lineno = TAILQ_EMPTY(&files) ? 1 : 0;
	nfile->ungetsize = 16;
	nfile->ungetbuf = malloc(nfile->ungetsize);
	if (nfile->ungetbuf == NULL) {
		log_warn("%s", __func__);
		fclose(nfile->stream);
		free(nfile->name);
		free(nfile);
		return (NULL);
	}
	TAILQ_INSERT_TAIL(&files, nfile, entry);
	return (nfile);
}

int
popfile(void)
{
	struct file	*prev;

	if ((prev = TAILQ_PREV(file, files, entry)) != NULL)
		prev->errors += file->errors;

	TAILQ_REMOVE(&files, file, entry);
	fclose(file->stream);
	free(file->name);
	free(file->ungetbuf);
	free(file);
	file = prev;
	return (file ? 0 : EOF);
}

int
parse_config(const char *filename)
{
	extern const char	 default_conffile[];
	struct sym		*sym, *next;

	if ((file = pushfile(filename, 0)) == NULL) {
		/* no default config file is fine */
		if (errno == ENOENT && filename == default_conffile) {
			log_debug("%s: missing", filename);
			return (0);
		}
		log_warn("failed to open %s", filename);
		if (errno == ENOENT)
			return (0);
		return (-1);
	}
	topfile = file;
	setservent(1);

	/* Set the default switch type */
	(void)strlcpy(vsw_type, VMD_SWITCH_TYPE, sizeof(vsw_type));

	yyparse();
	errors = file->errors;
	popfile();

	endservent();

	/* Free macros and check which have not been used. */
	TAILQ_FOREACH_SAFE(sym, &symhead, entry, next) {
		if (!sym->used)
			fprintf(stderr, "warning: macro '%s' not "
			    "used\n", sym->nam);
		if (!sym->persist) {
			free(sym->nam);
			free(sym->val);
			TAILQ_REMOVE(&symhead, sym, entry);
			free(sym);
		}
	}

	if (errors)
		return (-1);

	return (0);
}

int
symset(const char *nam, const char *val, int persist)
{
	struct sym	*sym;

	TAILQ_FOREACH(sym, &symhead, entry) {
		if (strcmp(nam, sym->nam) == 0)
			break;
	}

	if (sym != NULL) {
		if (sym->persist == 1)
			return (0);
		else {
			free(sym->nam);
			free(sym->val);
			TAILQ_REMOVE(&symhead, sym, entry);
			free(sym);
		}
	}
	if ((sym = calloc(1, sizeof(*sym))) == NULL)
		return (-1);

	sym->nam = strdup(nam);
	if (sym->nam == NULL) {
		free(sym);
		return (-1);
	}
	sym->val = strdup(val);
	if (sym->val == NULL) {
		free(sym->nam);
		free(sym);
		return (-1);
	}
	sym->used = 0;
	sym->persist = persist;
	TAILQ_INSERT_TAIL(&symhead, sym, entry);
	return (0);
}

int
cmdline_symset(char *s)
{
	char	*sym, *val;
	int	ret;

	if ((val = strrchr(s, '=')) == NULL)
		return (-1);
	sym = strndup(s, val - s);
	if (sym == NULL)
		fatal("%s: strndup", __func__);
	ret = symset(sym, val + 1, 1);
	free(sym);

	return (ret);
}

char *
symget(const char *nam)
{
	struct sym	*sym;

	TAILQ_FOREACH(sym, &symhead, entry) {
		if (strcmp(nam, sym->nam) == 0) {
			sym->used = 1;
			return (sym->val);
		}
	}
	return (NULL);
}

ssize_t
parse_size(char *word, int64_t val)
{
	char		 result[FMT_SCALED_STRSIZE];
	ssize_t		 size;
	long long	 res;

	if (word != NULL) {
		if (scan_scaled(word, &res) != 0) {
			log_warn("invalid memory size: %s", word);
			return (-1);
		}
		val = (int64_t)res;
	}

	if (val < (1024 * 1024)) {
		log_warnx("memory size must be at least 1MB");
		return (-1);
	}

	if (val > VMM_MAX_VM_MEM_SIZE) {
		if (fmt_scaled(VMM_MAX_VM_MEM_SIZE, result) == 0)
			log_warnx("memory size too large (limit is %s)",
			    result);
		else
			log_warnx("memory size too large");
		return (-1);
	}

	/* Round down to the megabyte. */
	size = (val / (1024 * 1024)) * (1024 * 1024);

	if (size != val) {
		if (fmt_scaled(size, result) == 0)
			log_debug("memory size rounded to %s", result);
		else
			log_debug("memory size rounded to %zd bytes", size);
	}

	return ((ssize_t)size);
}

int
parse_disk(char *word, int type)
{
	char	 buf[BUFSIZ], path[PATH_MAX];
	int	 fd;
	ssize_t	 len;

	if (vmc.vmc_ndisks >= VM_MAX_DISKS_PER_VM) {
		log_warnx("too many disks");
		return (-1);
	}

	if (realpath(word, path) == NULL) {
		log_warn("disk %s", word);
		return (-1);
	}

	if (!type) {
		/* Use raw as the default format */
		type = VMDF_RAW;

		/* Try to derive the format from the file signature */
		if ((fd = open(path, O_RDONLY)) != -1) {
			len = read(fd, buf, sizeof(buf));
			close(fd);
			if (len >= (ssize_t)strlen(VM_MAGIC_QCOW) &&
			    strncmp(buf, VM_MAGIC_QCOW,
			    strlen(VM_MAGIC_QCOW)) == 0) {
				/* The qcow version will be checked later */
				type = VMDF_QCOW2;
			}
		}
	}

	if (strlcpy(vmc.vmc_disks[vmc.vmc_ndisks], path,
	    sizeof(vmc.vmc_disks[vmc.vmc_ndisks])) >=
	    sizeof(vmc.vmc_disks[vmc.vmc_ndisks])) {
		log_warnx("disk path too long");
		return (-1);
	}
	vmc.vmc_disktypes[vmc.vmc_ndisks] = type;

	vmc.vmc_ndisks++;

	return (0);
}

unsigned int
parse_format(const char *word)
{
	if (strcasecmp(word, "raw") == 0)
		return (VMDF_RAW);
	else if (strcasecmp(word, "qcow2") == 0)
		return (VMDF_QCOW2);
	return (0);
}

/*
 * Parse an ipv4 address and prefix for local interfaces and validate
 * constraints for vmd networking.
 */
int
parse_prefix4(const char *str, struct local_prefix *out, const char **errstr)
{
	struct addrinfo		 hints, *res = NULL;
	struct sockaddr_storage	 ss;
	struct in_addr		 addr;
	int			 mask = 16;
	char			*p, *ps;

	if ((ps = strdup(str)) == NULL)
		fatal("%s: strdup", __func__);

	if ((p = strrchr(ps, '/')) != NULL) {
		mask = strtonum(p + 1, 1, 16, errstr);
		if (errstr != NULL && *errstr) {
			free(ps);
			return (1);
		}
		p[0] = '\0';
	}

	/* Attempt to construct an address from the user input. */
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_NUMERICHOST;

	if (getaddrinfo(ps, NULL, &hints, &res) == 0) {
		memset(&ss, 0, sizeof(ss));
		memcpy(&ss, res->ai_addr, res->ai_addrlen);
		addr.s_addr = ss2sin(&ss)->sin_addr.s_addr;
		freeaddrinfo(res);
	} else { /* try 10/8 parsing */
		memset(&addr, 0, sizeof(addr));
		if (inet_net_pton(AF_INET, ps, &addr, sizeof(addr)) == -1) {
			if (errstr)
				*errstr = "invalid format";
			free(ps);
			return (1);
		}
	}
	free(ps);

	/*
	 * Validate the prefix by comparing it with the mask. Since we
	 * constrain the mask length to 16 above, this also validates
	 * we reserve the last 16 bits for use by vmd to assign vm id
	 * and interface id.
	 */
	if ((addr.s_addr & prefixlen2mask(mask)) != addr.s_addr) {
		if (errstr)
			*errstr = "bad mask";
		return (1);
	}

	/* Copy out the local prefix. */
	out->lp_in.s_addr = addr.s_addr;
	out->lp_mask.s_addr = prefixlen2mask(mask);
	return (0);
}

/*
 * Parse an ipv6 address and prefix for local interfaces and validate
 * constraints for vmd networking.
 */
int
parse_prefix6(const char *str, struct local_prefix *out, const char **errstr)
{
	struct addrinfo		 hints, *res = NULL;
	struct sockaddr_storage	 ss;
	struct in6_addr		 addr6, mask6;
	size_t			 i;
	int			 mask = 64, err;
	char			*p, *ps;

	if ((ps = strdup(str)) == NULL)
		fatal("%s: strdup", __func__);

	if ((p = strrchr(ps, '/')) != NULL) {
		mask = strtonum(p + 1, 0, 64, errstr);
		if (errstr != NULL && *errstr) {
			free(ps);
			return (1);
		}
		p[0] = '\0';
	}

	/* Attempt to construct an address from the user input. */
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET6;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_NUMERICHOST;

	if ((err = getaddrinfo(ps, NULL, &hints, &res)) != 0) {
		if (errstr)
			*errstr = gai_strerror(err);
		free(ps);
		return (1);
	}
	free(ps);

	memset(&ss, 0, sizeof(ss));
	memcpy(&ss, res->ai_addr, res->ai_addrlen);
	freeaddrinfo(res);

	memcpy(&addr6, (void*)&ss2sin6(&ss)->sin6_addr, sizeof(addr6));
	prefixlen2mask6(mask, &mask6);

	/*
	 * Validate the prefix by comparing it with the mask. Since we
	 * constrain the mask length to 64 above, this also validates
	 * that we're reserving bits for the encoding of the ipv4
	 * address, the vm id, and interface id. */
	for (i = 0; i < 16; i++) {
		if ((addr6.s6_addr[i] & mask6.s6_addr[i]) != addr6.s6_addr[i]) {
			if (errstr)
				*errstr = "bad mask";
			return (1);
		}
	}

	/* Copy out the local prefix. */
	memcpy(&out->lp_in6, &addr6, sizeof(out->lp_in6));
	memcpy(&out->lp_mask6, &mask6, sizeof(out->lp_mask6));
	return (0);
}
#line 1548 "parse.tab.c"

/* For use in generated program */
#define yydepth (int)(yystack.s_mark - yystack.s_base)
#if YYBTYACC
#define yytrial (yyps->save)
#endif /* YYBTYACC */

#if YYDEBUG
#include <stdio.h>	/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    YYLTYPE *newps;
#endif

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    newps = (YYLTYPE *)realloc(data->p_base, newsize * sizeof(*newps));
    if (newps == 0)
        return YYENOMEM;

    data->p_base = newps;
    data->p_mark = newps + i;
#endif

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;

#if YYDEBUG
    if (yydebug)
        fprintf(stderr, "%sdebug: stack size increased to %d\n", YYPREFIX, newsize);
#endif
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    free(data->p_base);
#endif
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif /* YYPURE || defined(YY_NO_LEAKS) */
#if YYBTYACC

static YYParseState *
yyNewState(unsigned size)
{
    YYParseState *p = (YYParseState *) malloc(sizeof(YYParseState));
    if (p == NULL) return NULL;

    p->yystack.stacksize = size;
    if (size == 0)
    {
        p->yystack.s_base = NULL;
        p->yystack.l_base = NULL;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        p->yystack.p_base = NULL;
#endif
        return p;
    }
    p->yystack.s_base    = (YYINT *) malloc(size * sizeof(YYINT));
    if (p->yystack.s_base == NULL) return NULL;
    p->yystack.l_base    = (YYSTYPE *) malloc(size * sizeof(YYSTYPE));
    if (p->yystack.l_base == NULL) return NULL;
    memset(p->yystack.l_base, 0, size * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    p->yystack.p_base    = (YYLTYPE *) malloc(size * sizeof(YYLTYPE));
    if (p->yystack.p_base == NULL) return NULL;
    memset(p->yystack.p_base, 0, size * sizeof(YYLTYPE));
#endif

    return p;
}

static void
yyFreeState(YYParseState *p)
{
    yyfreestack(&p->yystack);
    free(p);
}
#endif /* YYBTYACC */

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab
#if YYBTYACC
#define YYVALID        do { if (yyps->save)            goto yyvalid; } while(0)
#define YYVALID_NESTED do { if (yyps->save && \
                                yyps->save->save == 0) goto yyvalid; } while(0)
#endif /* YYBTYACC */

int
YYPARSE_DECL()
{
    int yym, yyn, yystate, yyresult;
#if YYBTYACC
    int yynewerrflag;
    YYParseState *yyerrctx = NULL;
#endif /* YYBTYACC */
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    YYLTYPE  yyerror_loc_range[3]; /* position of error start/end (0 unused) */
#endif
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
    if (yydebug)
        fprintf(stderr, "%sdebug[<# of symbols on state stack>]\n", YYPREFIX);
#endif
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    memset(yyerror_loc_range, 0, sizeof(yyerror_loc_range));
#endif

#if YYBTYACC
    yyps = yyNewState(0); if (yyps == 0) goto yyenomem;
    yyps->save = 0;
#endif /* YYBTYACC */
    yym = 0;
    /* yyn is set below */
    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark = yystack.p_base;
#endif
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
#if YYBTYACC
        do {
        if (yylvp < yylve)
        {
            /* we're currently re-reading tokens */
            yylval = *yylvp++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yylloc = *yylpp++;
#endif
            yychar = *yylexp++;
            break;
        }
        if (yyps->save)
        {
            /* in trial mode; save scanner results for future parse attempts */
            if (yylvp == yylvlim)
            {   /* Enlarge lexical value queue */
                size_t p = (size_t) (yylvp - yylvals);
                size_t s = (size_t) (yylvlim - yylvals);

                s += YYLVQUEUEGROWTH;
                if ((yylexemes = (YYINT *)realloc(yylexemes, s * sizeof(YYINT))) == NULL) goto yyenomem;
                if ((yylvals   = (YYSTYPE *)realloc(yylvals, s * sizeof(YYSTYPE))) == NULL) goto yyenomem;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                if ((yylpsns   = (YYLTYPE *)realloc(yylpsns, s * sizeof(YYLTYPE))) == NULL) goto yyenomem;
#endif
                yylvp   = yylve = yylvals + p;
                yylvlim = yylvals + s;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylpp   = yylpe = yylpsns + p;
                yylplim = yylpsns + s;
#endif
                yylexp  = yylexemes + p;
            }
            *yylexp = (YYINT) YYLEX;
            *yylvp++ = yylval;
            yylve++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            *yylpp++ = yylloc;
            yylpe++;
#endif
            yychar = *yylexp++;
            break;
        }
        /* normal operation, no conflict encountered */
#endif /* YYBTYACC */
        yychar = YYLEX;
#if YYBTYACC
        } while (0);
#endif /* YYBTYACC */
        if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            fprintf(stderr, "%s[%d]: state %d, reading token %d (%s)",
                            YYDEBUGSTR, yydepth, yystate, yychar, yys);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
            if (!yytrial)
#endif /* YYBTYACC */
                fprintf(stderr, " <%s>", YYSTYPE_TOSTRING(yychar, yylval));
#endif
            fputc('\n', stderr);
        }
#endif
    }
#if YYBTYACC

    /* Do we have a conflict? */
    if (((yyn = yycindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
        yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
        YYINT ctry;

        if (yypath)
        {
            YYParseState *save;
#if YYDEBUG
            if (yydebug)
                fprintf(stderr, "%s[%d]: CONFLICT in state %d: following successful trial parse\n",
                                YYDEBUGSTR, yydepth, yystate);
#endif
            /* Switch to the next conflict context */
            save = yypath;
            yypath = save->save;
            save->save = NULL;
            ctry = save->ctry;
            if (save->state != yystate) YYABORT;
            yyFreeState(save);

        }
        else
        {

            /* Unresolved conflict - start/continue trial parse */
            YYParseState *save;
#if YYDEBUG
            if (yydebug)
            {
                fprintf(stderr, "%s[%d]: CONFLICT in state %d. ", YYDEBUGSTR, yydepth, yystate);
                if (yyps->save)
                    fputs("ALREADY in conflict, continuing trial parse.\n", stderr);
                else
                    fputs("Starting trial parse.\n", stderr);
            }
#endif
            save                  = yyNewState((unsigned)(yystack.s_mark - yystack.s_base + 1));
            if (save == NULL) goto yyenomem;
            save->save            = yyps->save;
            save->state           = yystate;
            save->errflag         = yyerrflag;
            save->yystack.s_mark  = save->yystack.s_base + (yystack.s_mark - yystack.s_base);
            memcpy (save->yystack.s_base, yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
            save->yystack.l_mark  = save->yystack.l_base + (yystack.l_mark - yystack.l_base);
            memcpy (save->yystack.l_base, yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            save->yystack.p_mark  = save->yystack.p_base + (yystack.p_mark - yystack.p_base);
            memcpy (save->yystack.p_base, yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
            ctry                  = yytable[yyn];
            if (yyctable[ctry] == -1)
            {
#if YYDEBUG
                if (yydebug && yychar >= YYEOF)
                    fprintf(stderr, "%s[%d]: backtracking 1 token\n", YYDEBUGSTR, yydepth);
#endif
                ctry++;
            }
            save->ctry = ctry;
            if (yyps->save == NULL)
            {
                /* If this is a first conflict in the stack, start saving lexemes */
                if (!yylexemes)
                {
                    yylexemes = (YYINT *) malloc((YYLVQUEUEGROWTH) * sizeof(YYINT));
                    if (yylexemes == NULL) goto yyenomem;
                    yylvals   = (YYSTYPE *) malloc((YYLVQUEUEGROWTH) * sizeof(YYSTYPE));
                    if (yylvals == NULL) goto yyenomem;
                    yylvlim   = yylvals + YYLVQUEUEGROWTH;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    yylpsns   = (YYLTYPE *) malloc((YYLVQUEUEGROWTH) * sizeof(YYLTYPE));
                    if (yylpsns == NULL) goto yyenomem;
                    yylplim   = yylpsns + YYLVQUEUEGROWTH;
#endif
                }
                if (yylvp == yylve)
                {
                    yylvp  = yylve = yylvals;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    yylpp  = yylpe = yylpsns;
#endif
                    yylexp = yylexemes;
                    if (yychar >= YYEOF)
                    {
                        *yylve++ = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                        *yylpe++ = yylloc;
#endif
                        *yylexp  = (YYINT) yychar;
                        yychar   = YYEMPTY;
                    }
                }
            }
            if (yychar >= YYEOF)
            {
                yylvp--;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylpp--;
#endif
                yylexp--;
                yychar = YYEMPTY;
            }
            save->lexeme = (int) (yylvp - yylvals);
            yyps->save   = save;
        }
        if (yytable[yyn] == ctry)
        {
#if YYDEBUG
            if (yydebug)
                fprintf(stderr, "%s[%d]: state %d, shifting to state %d\n",
                                YYDEBUGSTR, yydepth, yystate, yyctable[ctry]);
#endif
            if (yychar < 0)
            {
                yylvp++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylpp++;
#endif
                yylexp++;
            }
            if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                goto yyoverflow;
            yystate = yyctable[ctry];
            *++yystack.s_mark = (YYINT) yystate;
            *++yystack.l_mark = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            *++yystack.p_mark = yylloc;
#endif
            yychar  = YYEMPTY;
            if (yyerrflag > 0) --yyerrflag;
            goto yyloop;
        }
        else
        {
            yyn = yyctable[ctry];
            goto yyreduce;
        }
    } /* End of code dealing with conflicts */
#endif /* YYBTYACC */
    if (((yyn = yysindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
#if YYDEBUG
        if (yydebug)
            fprintf(stderr, "%s[%d]: state %d, shifting to state %d\n",
                            YYDEBUGSTR, yydepth, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        *++yystack.p_mark = yylloc;
#endif
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if (((yyn = yyrindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag != 0) goto yyinrecovery;
#if YYBTYACC

    yynewerrflag = 1;
    goto yyerrhandler;
    goto yyerrlab; /* redundant goto avoids 'unused label' warning */

yyerrlab:
    /* explicit YYERROR from an action -- pop the rhs of the rule reduced
     * before looking for error recovery */
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark -= yym;
#endif

    yynewerrflag = 0;
yyerrhandler:
    while (yyps->save)
    {
        int ctry;
        YYParseState *save = yyps->save;
#if YYDEBUG
        if (yydebug)
            fprintf(stderr, "%s[%d]: ERROR in state %d, CONFLICT BACKTRACKING to state %d, %d tokens\n",
                            YYDEBUGSTR, yydepth, yystate, yyps->save->state,
                    (int)(yylvp - yylvals - yyps->save->lexeme));
#endif
        /* Memorize most forward-looking error state in case it's really an error. */
        if (yyerrctx == NULL || yyerrctx->lexeme < yylvp - yylvals)
        {
            /* Free old saved error context state */
            if (yyerrctx) yyFreeState(yyerrctx);
            /* Create and fill out new saved error context state */
            yyerrctx                 = yyNewState((unsigned)(yystack.s_mark - yystack.s_base + 1));
            if (yyerrctx == NULL) goto yyenomem;
            yyerrctx->save           = yyps->save;
            yyerrctx->state          = yystate;
            yyerrctx->errflag        = yyerrflag;
            yyerrctx->yystack.s_mark = yyerrctx->yystack.s_base + (yystack.s_mark - yystack.s_base);
            memcpy (yyerrctx->yystack.s_base, yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
            yyerrctx->yystack.l_mark = yyerrctx->yystack.l_base + (yystack.l_mark - yystack.l_base);
            memcpy (yyerrctx->yystack.l_base, yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yyerrctx->yystack.p_mark = yyerrctx->yystack.p_base + (yystack.p_mark - yystack.p_base);
            memcpy (yyerrctx->yystack.p_base, yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
            yyerrctx->lexeme         = (int) (yylvp - yylvals);
        }
        yylvp          = yylvals   + save->lexeme;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        yylpp          = yylpsns   + save->lexeme;
#endif
        yylexp         = yylexemes + save->lexeme;
        yychar         = YYEMPTY;
        yystack.s_mark = yystack.s_base + (save->yystack.s_mark - save->yystack.s_base);
        memcpy (yystack.s_base, save->yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
        yystack.l_mark = yystack.l_base + (save->yystack.l_mark - save->yystack.l_base);
        memcpy (yystack.l_base, save->yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        yystack.p_mark = yystack.p_base + (save->yystack.p_mark - save->yystack.p_base);
        memcpy (yystack.p_base, save->yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
        ctry           = ++save->ctry;
        yystate        = save->state;
        /* We tried shift, try reduce now */
        if ((yyn = yyctable[ctry]) >= 0) goto yyreduce;
        yyps->save     = save->save;
        save->save     = NULL;
        yyFreeState(save);

        /* Nothing left on the stack -- error */
        if (!yyps->save)
        {
#if YYDEBUG
            if (yydebug)
                fprintf(stderr, "%sdebug[%d,trial]: trial parse FAILED, entering ERROR mode\n",
                                YYPREFIX, yydepth);
#endif
            /* Restore state as it was in the most forward-advanced error */
            yylvp          = yylvals   + yyerrctx->lexeme;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yylpp          = yylpsns   + yyerrctx->lexeme;
#endif
            yylexp         = yylexemes + yyerrctx->lexeme;
            yychar         = yylexp[-1];
            yylval         = yylvp[-1];
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yylloc         = yylpp[-1];
#endif
            yystack.s_mark = yystack.s_base + (yyerrctx->yystack.s_mark - yyerrctx->yystack.s_base);
            memcpy (yystack.s_base, yyerrctx->yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
            yystack.l_mark = yystack.l_base + (yyerrctx->yystack.l_mark - yyerrctx->yystack.l_base);
            memcpy (yystack.l_base, yyerrctx->yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yystack.p_mark = yystack.p_base + (yyerrctx->yystack.p_mark - yyerrctx->yystack.p_base);
            memcpy (yystack.p_base, yyerrctx->yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
            yystate        = yyerrctx->state;
            yyFreeState(yyerrctx);
            yyerrctx       = NULL;
        }
        yynewerrflag = 1;
    }
    if (yynewerrflag == 0) goto yyinrecovery;
#endif /* YYBTYACC */

    YYERROR_CALL("syntax error");
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yyerror_loc_range[1] = yylloc; /* lookahead position is error start position */
#endif

#if !YYBTYACC
    goto yyerrlab; /* redundant goto avoids 'unused label' warning */
yyerrlab:
#endif
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if (((yyn = yysindex[*yystack.s_mark]) != 0) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    fprintf(stderr, "%s[%d]: state %d, error recovery shifting to state %d\n",
                                    YYDEBUGSTR, yydepth, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                /* lookahead position is error end position */
                yyerror_loc_range[2] = yylloc;
                YYLLOC_DEFAULT(yyloc, yyerror_loc_range, 2); /* position of error span */
                *++yystack.p_mark = yyloc;
#endif
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    fprintf(stderr, "%s[%d]: error recovery discarding state %d\n",
                                    YYDEBUGSTR, yydepth, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                /* the current TOS position is the error start position */
                yyerror_loc_range[1] = *yystack.p_mark;
#endif
#if defined(YYDESTRUCT_CALL)
#if YYBTYACC
                if (!yytrial)
#endif /* YYBTYACC */
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    YYDESTRUCT_CALL("error: discarding state",
                                    yystos[*yystack.s_mark], yystack.l_mark, yystack.p_mark);
#else
                    YYDESTRUCT_CALL("error: discarding state",
                                    yystos[*yystack.s_mark], yystack.l_mark);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
#endif /* defined(YYDESTRUCT_CALL) */
                --yystack.s_mark;
                --yystack.l_mark;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                --yystack.p_mark;
#endif
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            fprintf(stderr, "%s[%d]: state %d, error recovery discarding token %d (%s)\n",
                            YYDEBUGSTR, yydepth, yystate, yychar, yys);
        }
#endif
#if defined(YYDESTRUCT_CALL)
#if YYBTYACC
        if (!yytrial)
#endif /* YYBTYACC */
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            YYDESTRUCT_CALL("error: discarding token", yychar, &yylval, &yylloc);
#else
            YYDESTRUCT_CALL("error: discarding token", yychar, &yylval);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
#endif /* defined(YYDESTRUCT_CALL) */
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
    yym = yylen[yyn];
#if YYDEBUG
    if (yydebug)
    {
        fprintf(stderr, "%s[%d]: state %d, reducing by rule %d (%s)",
                        YYDEBUGSTR, yydepth, yystate, yyn, yyrule[yyn]);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
        if (!yytrial)
#endif /* YYBTYACC */
            if (yym > 0)
            {
                int i;
                fputc('<', stderr);
                for (i = yym; i > 0; i--)
                {
                    if (i != yym) fputs(", ", stderr);
                    fputs(YYSTYPE_TOSTRING(yystos[yystack.s_mark[1-i]],
                                           yystack.l_mark[1-i]), stderr);
                }
                fputc('>', stderr);
            }
#endif
        fputc('\n', stderr);
    }
#endif
    if (yym > 0)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)

    /* Perform position reduction */
    memset(&yyloc, 0, sizeof(yyloc));
#if YYBTYACC
    if (!yytrial)
#endif /* YYBTYACC */
    {
        YYLLOC_DEFAULT(yyloc, &yystack.p_mark[-yym], yym);
        /* just in case YYERROR is invoked within the action, save
           the start of the rhs as the error start position */
        yyerror_loc_range[1] = yystack.p_mark[1-yym];
    }
#endif

    switch (yyn)
    {
case 8:
#line 152 "parse.y"
	{ file->errors++; }
#line 2221 "parse.tab.c"
break;
case 9:
#line 155 "parse.y"
	{
			struct file	*nfile;

			if ((nfile = pushfile(yystack.l_mark[0].v.string, 0)) == NULL) {
				yyerror("failed to include file %s", yystack.l_mark[0].v.string);
				free(yystack.l_mark[0].v.string);
				YYERROR;
			}
			free(yystack.l_mark[0].v.string);

			file = nfile;
			lungetc('\n');
		}
#line 2238 "parse.tab.c"
break;
case 10:
#line 170 "parse.y"
	{
			char *s = yystack.l_mark[-2].v.string;
			while (*s++) {
				if (isspace((unsigned char)*s)) {
					yyerror("macro name cannot contain "
					    "whitespace");
					free(yystack.l_mark[-2].v.string);
					free(yystack.l_mark[0].v.string);
					YYERROR;
				}
			}
			if (symset(yystack.l_mark[-2].v.string, yystack.l_mark[0].v.string, 0) == -1)
				fatalx("cannot store variable");
			free(yystack.l_mark[-2].v.string);
			free(yystack.l_mark[0].v.string);
		}
#line 2258 "parse.tab.c"
break;
case 11:
#line 188 "parse.y"
	{
			env->vmd_cfg.cfg_flags |= VMD_CFG_INET6;
		}
#line 2265 "parse.tab.c"
break;
case 12:
#line 191 "parse.y"
	{
			const char	*err;

			if (parse_prefix6(yystack.l_mark[0].v.string, &env->vmd_cfg.cfg_localprefix,
			    &err)) {
				yyerror("invalid local inet6 prefix: %s", err);
				YYERROR;
			} else {
				env->vmd_cfg.cfg_flags |= VMD_CFG_INET6;
				env->vmd_cfg.cfg_flags &= ~VMD_CFG_AUTOINET6;
			}
			free(yystack.l_mark[0].v.string);
		}
#line 2282 "parse.tab.c"
break;
case 13:
#line 204 "parse.y"
	{
			const char	*err;

			if (parse_prefix4(yystack.l_mark[0].v.string, &env->vmd_cfg.cfg_localprefix,
			    &err)) {
				yyerror("invalid local prefix: %s", err);
				YYERROR;
			}
			free(yystack.l_mark[0].v.string);
		}
#line 2296 "parse.tab.c"
break;
case 14:
#line 214 "parse.y"
	{
			env->vmd_ps.ps_csock.cs_uid = yystack.l_mark[0].v.owner.uid;
			env->vmd_ps.ps_csock.cs_gid = yystack.l_mark[0].v.owner.gid == -1 ? 0 : yystack.l_mark[0].v.owner.gid;
		}
#line 2304 "parse.tab.c"
break;
case 15:
#line 218 "parse.y"
	{
			/*env->vmd_cfg.cfg_agentx.ax_enabled = 1;*/
		}
#line 2311 "parse.tab.c"
break;
case 16:
#line 220 "parse.y"
	{
			/*if (env->vmd_cfg.cfg_agentx.ax_path[0] == '\0')
				if (strlcpy(env->vmd_cfg.cfg_agentx.ax_path,
				    AGENTX_MASTER_PATH,
				    sizeof(env->vmd_cfg.cfg_agentx.ax_path)) >=
				    sizeof(env->vmd_cfg.cfg_agentx.ax_path)) {
					yyerror("invalid agentx path");
					YYERROR;
				}*/
		}
#line 2325 "parse.tab.c"
break;
case 17:
#line 230 "parse.y"
	{
			env->vmd_cfg.cfg_flags |= VMD_CFG_STAGGERED_START;
			env->vmd_cfg.delay.tv_sec = yystack.l_mark[0].v.number;
			env->vmd_cfg.parallelism = yystack.l_mark[-2].v.number;
		}
#line 2334 "parse.tab.c"
break;
case 18:
#line 237 "parse.y"
	{
			if ((vsw = calloc(1, sizeof(*vsw))) == NULL)
				fatal("could not allocate switch");

			vsw->sw_id = env->vmd_nswitches + 1;
			vsw->sw_name = yystack.l_mark[0].v.string;
			vsw->sw_flags = VMIFF_UP;

			vmc_disable = 0;
		}
#line 2348 "parse.tab.c"
break;
case 19:
#line 246 "parse.y"
	{
			if (strnlen(vsw->sw_ifname,
			    sizeof(vsw->sw_ifname)) == 0) {
				yyerror("switch \"%s\" "
				    "is missing interface name",
				    vsw->sw_name);
				YYERROR;
			}

			if (vmc_disable) {
				log_debug("%s:%d: switch \"%s\""
				    " skipped (disabled)",
				    file->name, yylval.lineno, vsw->sw_name);
			} else if (!env->vmd_noaction) {
				TAILQ_INSERT_TAIL(env->vmd_switches,
				    vsw, sw_entry);
				env->vmd_nswitches++;
				log_debug("%s:%d: switch \"%s\" registered",
				    file->name, yylval.lineno, vsw->sw_name);
			}
		}
#line 2373 "parse.tab.c"
break;
case 22:
#line 273 "parse.y"
	{
			vmc_disable = yystack.l_mark[0].v.number;
		}
#line 2380 "parse.tab.c"
break;
case 23:
#line 276 "parse.y"
	{
			if (priv_validgroup(yystack.l_mark[0].v.string) == -1) {
				yyerror("invalid group name: %s", yystack.l_mark[0].v.string);
				free(yystack.l_mark[0].v.string);
				YYERROR;
			}
			vsw->sw_group = yystack.l_mark[0].v.string;
		}
#line 2392 "parse.tab.c"
break;
case 24:
#line 284 "parse.y"
	{
			if (priv_getiftype(yystack.l_mark[0].v.string, vsw_type, NULL) == -1 ||
			    priv_findname(vsw_type, vmd_descsw) == -1) {
				yyerror("invalid switch interface: %s", yystack.l_mark[0].v.string);
				free(yystack.l_mark[0].v.string);
				YYERROR;
			}

			if (strlcpy(vsw->sw_ifname, yystack.l_mark[0].v.string,
			    sizeof(vsw->sw_ifname)) >= sizeof(vsw->sw_ifname)) {
				yyerror("switch interface too long: %s", yystack.l_mark[0].v.string);
				free(yystack.l_mark[0].v.string);
				YYERROR;
			}
			free(yystack.l_mark[0].v.string);
		}
#line 2412 "parse.tab.c"
break;
case 25:
#line 300 "parse.y"
	{
			vsw->sw_flags |= VMIFF_LOCKED;
		}
#line 2419 "parse.tab.c"
break;
case 26:
#line 303 "parse.y"
	{
			if (yystack.l_mark[0].v.number < 0 || yystack.l_mark[0].v.number > RT_TABLEID_MAX) {
				yyerror("invalid rdomain: %lld", yystack.l_mark[0].v.number);
				YYERROR;
			}
			vsw->sw_flags |= VMIFF_RDOMAIN;
			vsw->sw_rdomain = yystack.l_mark[0].v.number;
		}
#line 2431 "parse.tab.c"
break;
case 27:
#line 311 "parse.y"
	{
			if (yystack.l_mark[0].v.number)
				vsw->sw_flags |= VMIFF_UP;
			else
				vsw->sw_flags &= ~VMIFF_UP;
		}
#line 2441 "parse.tab.c"
break;
case 28:
#line 319 "parse.y"
	{
			unsigned int	 i;
			char		*name;

			memset(&vmc, 0, sizeof(vmc));
			vmc.vmc_kernel = -1;

			vcp = &vmc.vmc_params;
			vmc_disable = 0;
			vmc_nnics = 0;

			if (yystack.l_mark[0].v.string != NULL) {
				/* This is an instance of a pre-configured VM */
				if (strlcpy(vmc.vmc_instance, yystack.l_mark[-1].v.string,
				    sizeof(vmc.vmc_instance)) >=
				    sizeof(vmc.vmc_instance)) {
					yyerror("vm %s name too long", yystack.l_mark[-1].v.string);
					free(yystack.l_mark[-1].v.string);
					free(yystack.l_mark[0].v.string);
					YYERROR;
				}

				free(yystack.l_mark[-1].v.string);
				name = yystack.l_mark[0].v.string;
				vmc.vmc_flags |= VMOP_CREATE_INSTANCE;
			} else
				name = yystack.l_mark[-1].v.string;

			for (i = 0; i < VM_MAX_NICS_PER_VM; i++) {
				/* Set the interface to UP by default */
				vmc.vmc_ifflags[i] |= IFF_UP;
			}

			if (strlcpy(vcp->vcp_name, name,
			    sizeof(vcp->vcp_name)) >= sizeof(vcp->vcp_name)) {
				yyerror("vm name too long");
				free(yystack.l_mark[-1].v.string);
				free(yystack.l_mark[0].v.string);
				YYERROR;
			}

			/* set default user/group permissions */
			vmc.vmc_owner.uid = 0;
			vmc.vmc_owner.gid = -1;
		}
#line 2490 "parse.tab.c"
break;
case 29:
#line 363 "parse.y"
	{
			struct vmd_vm	*vm;
			int		 ret;

			/* configured interfaces vs. number of interfaces */
			if (vmc_nnics > vmc.vmc_nnics)
				vmc.vmc_nnics = vmc_nnics;

			if (!env->vmd_noaction) {
				ret = vm_register(&env->vmd_ps, &vmc,
				    &vm, 0, 0);
				if (ret == -1 && errno == EALREADY) {
					log_debug("%s:%d: vm \"%s\""
					    " skipped (%s)",
					    file->name, yylval.lineno,
					    vcp->vcp_name,
					    (vm->vm_state & VM_STATE_RUNNING) ?
					    "running" : "already exists");
				} else if (ret == -1) {
					yyerror("vm \"%s\" failed: %s",
					    vcp->vcp_name, strerror(errno));
					YYERROR;
				} else {
					if (vmc_disable)
						vm->vm_state |= VM_STATE_DISABLED;
					else
						vm->vm_state |= VM_STATE_WAITING;
					log_debug("%s:%d: vm \"%s\" "
					    "registered (%s)",
					    file->name, yylval.lineno,
					    vcp->vcp_name,
					    vmc_disable ?
					    "disabled" : "enabled");
				}
				vm->vm_kernel_path = kernel;
				vm->vm_kernel = -1;
				vm->vm_from_config = 1;
			}
			kernel = NULL;
		}
#line 2534 "parse.tab.c"
break;
case 30:
#line 405 "parse.y"
	{ yyval.v.string = NULL; }
#line 2539 "parse.tab.c"
break;
case 31:
#line 406 "parse.y"
	{ yyval.v.string = yystack.l_mark[0].v.string; }
#line 2544 "parse.tab.c"
break;
case 34:
#line 413 "parse.y"
	{
			vmc_disable = yystack.l_mark[0].v.number;
		}
#line 2551 "parse.tab.c"
break;
case 35:
#line 416 "parse.y"
	{
			if (parse_disk(yystack.l_mark[-1].v.string, yystack.l_mark[0].v.number) != 0) {
				yyerror("failed to parse disks: %s", yystack.l_mark[-1].v.string);
				free(yystack.l_mark[-1].v.string);
				YYERROR;
			}
			free(yystack.l_mark[-1].v.string);
			vmc.vmc_flags |= VMOP_CREATE_DISK;
		}
#line 2564 "parse.tab.c"
break;
case 36:
#line 425 "parse.y"
	{
			unsigned int	i;
			char		type[IF_NAMESIZE];

			i = vmc_nnics;
			if (++vmc_nnics > VM_MAX_NICS_PER_VM) {
				yyerror("too many interfaces: %zu", vmc_nnics);
				free(yystack.l_mark[-1].v.string);
				YYERROR;
			}

			if (yystack.l_mark[-3].v.number)
				vmc.vmc_ifflags[i] |= VMIFF_LOCAL;
			if (yystack.l_mark[-1].v.string != NULL) {
				if (strcmp(yystack.l_mark[-1].v.string, "tap") != 0 &&
				    (priv_getiftype(yystack.l_mark[-1].v.string, type, NULL) == -1 ||
				    strcmp(type, "tap") != 0)) {
					yyerror("invalid interface: %s", yystack.l_mark[-1].v.string);
					free(yystack.l_mark[-1].v.string);
					YYERROR;
				}

				if (strlcpy(vmc.vmc_ifnames[i], yystack.l_mark[-1].v.string,
				    sizeof(vmc.vmc_ifnames[i])) >=
				    sizeof(vmc.vmc_ifnames[i])) {
					yyerror("interface name too long: %s",
					    yystack.l_mark[-1].v.string);
					free(yystack.l_mark[-1].v.string);
					YYERROR;
				}
			}
			free(yystack.l_mark[-1].v.string);
			vmc.vmc_flags |= VMOP_CREATE_NETWORK;
		}
#line 2602 "parse.tab.c"
break;
case 37:
#line 459 "parse.y"
	{
			char	 path[PATH_MAX];

			if (kernel != NULL) {
				yyerror("kernel specified more than once");
				free(yystack.l_mark[0].v.string);
				YYERROR;

			}
			if (realpath(yystack.l_mark[0].v.string, path) == NULL) {
				yyerror("kernel path not found: %s",
				    strerror(errno));
				free(yystack.l_mark[0].v.string);
				YYERROR;
			}
			free(yystack.l_mark[0].v.string);
			kernel = malloc(sizeof(path));
			if (kernel == NULL)
				yyerror("malloc");
			memcpy(kernel, &path, sizeof(path));
			vmc.vmc_flags |= VMOP_CREATE_KERNEL;
		}
#line 2628 "parse.tab.c"
break;
case 38:
#line 481 "parse.y"
	{
			vmc.vmc_bootdevice = yystack.l_mark[0].v.number;
		}
#line 2635 "parse.tab.c"
break;
case 39:
#line 484 "parse.y"
	{
			if (vmc.vmc_cdrom[0] != '\0') {
				yyerror("cdrom specified more than once");
				free(yystack.l_mark[0].v.string);
				YYERROR;

			}
			if (strlcpy(vmc.vmc_cdrom, yystack.l_mark[0].v.string,
			    sizeof(vmc.vmc_cdrom)) >=
			    sizeof(vmc.vmc_cdrom)) {
				yyerror("cdrom name too long");
				free(yystack.l_mark[0].v.string);
				YYERROR;
			}
			free(yystack.l_mark[0].v.string);
			vmc.vmc_flags |= VMOP_CREATE_CDROM;
		}
#line 2656 "parse.tab.c"
break;
case 40:
#line 501 "parse.y"
	{
			if (vmc.vmc_nnics != 0) {
				yyerror("interfaces specified more than once");
				YYERROR;
			}
			if (yystack.l_mark[0].v.number < 0 || yystack.l_mark[0].v.number > VM_MAX_NICS_PER_VM) {
				yyerror("too many interfaces: %lld", yystack.l_mark[0].v.number);
				YYERROR;
			}
			vmc.vmc_nnics = (size_t)yystack.l_mark[0].v.number;
			vmc.vmc_flags |= VMOP_CREATE_NETWORK;
		}
#line 2672 "parse.tab.c"
break;
case 41:
#line 513 "parse.y"
	{
			ssize_t	 res;
			if (vcp->vcp_memranges[0].vmr_size != 0) {
				yyerror("memory specified more than once");
				YYERROR;
			}
			if ((res = parse_size(NULL, yystack.l_mark[0].v.number)) == -1) {
				yyerror("failed to parse size: %lld", yystack.l_mark[0].v.number);
				YYERROR;
			}
			vcp->vcp_memranges[0].vmr_size = (size_t)res;
			vmc.vmc_flags |= VMOP_CREATE_MEMORY;
		}
#line 2689 "parse.tab.c"
break;
case 42:
#line 526 "parse.y"
	{
			ssize_t	 res;
			if (vcp->vcp_memranges[0].vmr_size != 0) {
				yyerror("argument specified more than once");
				free(yystack.l_mark[0].v.string);
				YYERROR;
			}
			if ((res = parse_size(yystack.l_mark[0].v.string, 0)) == -1) {
				yyerror("failed to parse size: %s", yystack.l_mark[0].v.string);
				free(yystack.l_mark[0].v.string);
				YYERROR;
			}
			vcp->vcp_memranges[0].vmr_size = (size_t)res;
			vmc.vmc_flags |= VMOP_CREATE_MEMORY;
		}
#line 2708 "parse.tab.c"
break;
case 43:
#line 541 "parse.y"
	{
			vmc.vmc_owner.uid = yystack.l_mark[0].v.owner.uid;
			vmc.vmc_owner.gid = yystack.l_mark[0].v.owner.gid;
		}
#line 2716 "parse.tab.c"
break;
case 49:
#line 556 "parse.y"
	{ vmc.vmc_insflags |= VMOP_CREATE_KERNEL; }
#line 2721 "parse.tab.c"
break;
case 50:
#line 557 "parse.y"
	{ vmc.vmc_insflags |= VMOP_CREATE_MEMORY; }
#line 2726 "parse.tab.c"
break;
case 51:
#line 558 "parse.y"
	{ vmc.vmc_insflags |= VMOP_CREATE_NETWORK; }
#line 2731 "parse.tab.c"
break;
case 52:
#line 559 "parse.y"
	{ vmc.vmc_insflags |= VMOP_CREATE_DISK; }
#line 2736 "parse.tab.c"
break;
case 53:
#line 560 "parse.y"
	{ vmc.vmc_insflags |= VMOP_CREATE_CDROM; }
#line 2741 "parse.tab.c"
break;
case 54:
#line 561 "parse.y"
	{ vmc.vmc_insflags |= VMOP_CREATE_INSTANCE; }
#line 2746 "parse.tab.c"
break;
case 55:
#line 562 "parse.y"
	{
			vmc.vmc_insowner.uid = yystack.l_mark[0].v.owner.uid;
			vmc.vmc_insowner.gid = yystack.l_mark[0].v.owner.gid;
		}
#line 2754 "parse.tab.c"
break;
case 56:
#line 568 "parse.y"
	{
			yyval.v.owner.uid = yystack.l_mark[0].v.number;
			yyval.v.owner.gid = -1;
		}
#line 2762 "parse.tab.c"
break;
case 57:
#line 572 "parse.y"
	{
			char		*user, *group;
			struct passwd	*pw;
			struct group	*gr;

			yyval.v.owner.uid = 0;
			yyval.v.owner.gid = -1;

			user = yystack.l_mark[0].v.string;
			if ((group = strchr(user, ':')) != NULL) {
				if (group == user)
					user = NULL;
				*group++ = '\0';
			}

			if (user != NULL && *user) {
				if ((pw = getpwnam(user)) == NULL) {
					yyerror("failed to get user: %s",
					    user);
					free(yystack.l_mark[0].v.string);
					YYERROR;
				}
				yyval.v.owner.uid = pw->pw_uid;
			}

			if (group != NULL && *group) {
				if ((gr = getgrnam(group)) == NULL) {
					yyerror("failed to get group: %s",
					    group);
					free(yystack.l_mark[0].v.string);
					YYERROR;
				}
				yyval.v.owner.gid = gr->gr_gid;
			}

			free(yystack.l_mark[0].v.string);
		}
#line 2803 "parse.tab.c"
break;
case 58:
#line 611 "parse.y"
	{
			/*if (strlcpy(env->vmd_cfg.cfg_agentx.ax_context, $2,
			    sizeof(env->vmd_cfg.cfg_agentx.ax_context)) >=
			    sizeof(env->vmd_cfg.cfg_agentx.ax_context)) {
				yyerror("agentx context too large");
				free($2);
				YYERROR;
			}
			free($2);*/
		}
#line 2817 "parse.tab.c"
break;
case 59:
#line 621 "parse.y"
	{
			/*if (strlcpy(env->vmd_cfg.cfg_agentx.ax_path, $2,
			    sizeof(env->vmd_cfg.cfg_agentx.ax_path)) >=
			    sizeof(env->vmd_cfg.cfg_agentx.ax_path)) {
				yyerror("agentx path too large");
				free($2);
				YYERROR;
			}
			free($2);
			if (env->vmd_cfg.cfg_agentx.ax_path[0] != '/') {
				yyerror("agentx path is not absolute");
				YYERROR;
			}*/
		}
#line 2835 "parse.tab.c"
break;
case 61:
#line 640 "parse.y"
	{
			yyval.v.number = 0;
		}
#line 2842 "parse.tab.c"
break;
case 62:
#line 643 "parse.y"
	{
			if ((yyval.v.number = parse_format(yystack.l_mark[0].v.string)) == 0) {
				yyerror("unrecognized disk format %s", yystack.l_mark[0].v.string);
				free(yystack.l_mark[0].v.string);
				YYERROR;
			}
		}
#line 2853 "parse.tab.c"
break;
case 70:
#line 665 "parse.y"
	{
			unsigned int	i = vmc_nnics;

			/* No need to check if the switch exists */
			if (strlcpy(vmc.vmc_ifswitch[i], yystack.l_mark[0].v.string,
			    sizeof(vmc.vmc_ifswitch[i])) >=
			    sizeof(vmc.vmc_ifswitch[i])) {
				yyerror("switch name too long: %s", yystack.l_mark[0].v.string);
				free(yystack.l_mark[0].v.string);
				YYERROR;
			}
			free(yystack.l_mark[0].v.string);
		}
#line 2870 "parse.tab.c"
break;
case 71:
#line 678 "parse.y"
	{
			unsigned int	i = vmc_nnics;

			if (priv_validgroup(yystack.l_mark[0].v.string) == -1) {
				yyerror("invalid group name: %s", yystack.l_mark[0].v.string);
				free(yystack.l_mark[0].v.string);
				YYERROR;
			}

			/* No need to check if the group exists */
			(void)strlcpy(vmc.vmc_ifgroup[i], yystack.l_mark[0].v.string,
			    sizeof(vmc.vmc_ifgroup[i]));
			free(yystack.l_mark[0].v.string);
		}
#line 2888 "parse.tab.c"
break;
case 72:
#line 692 "parse.y"
	{
			if (yystack.l_mark[-2].v.number)
				vmc.vmc_ifflags[vmc_nnics] |= VMIFF_LOCKED;
			memcpy(vmc.vmc_macs[vmc_nnics], yystack.l_mark[0].v.lladdr, ETHER_ADDR_LEN);
		}
#line 2897 "parse.tab.c"
break;
case 73:
#line 697 "parse.y"
	{
			if (yystack.l_mark[0].v.number < 0 || yystack.l_mark[0].v.number > RT_TABLEID_MAX) {
				yyerror("invalid rdomain: %lld", yystack.l_mark[0].v.number);
				YYERROR;
			}
			vmc.vmc_ifflags[vmc_nnics] |= VMIFF_RDOMAIN;
			vmc.vmc_ifrdomain[vmc_nnics] = yystack.l_mark[0].v.number;
		}
#line 2909 "parse.tab.c"
break;
case 74:
#line 705 "parse.y"
	{
			if (yystack.l_mark[0].v.number)
				vmc.vmc_ifflags[vmc_nnics] |= VMIFF_UP;
			else
				vmc.vmc_ifflags[vmc_nnics] &= ~VMIFF_UP;
		}
#line 2919 "parse.tab.c"
break;
case 75:
#line 713 "parse.y"
	{ yyval.v.string = yystack.l_mark[0].v.string; }
#line 2924 "parse.tab.c"
break;
case 76:
#line 714 "parse.y"
	{ yyval.v.string = NULL; }
#line 2929 "parse.tab.c"
break;
case 77:
#line 717 "parse.y"
	{
			if (asprintf(&yyval.v.string, "%s%s", yystack.l_mark[-1].v.string, yystack.l_mark[0].v.string) == -1)
				fatal("asprintf string");
			free(yystack.l_mark[-1].v.string);
			free(yystack.l_mark[0].v.string);
		}
#line 2939 "parse.tab.c"
break;
case 79:
#line 726 "parse.y"
	{
			struct ether_addr *ea;

			if ((ea = ether_aton(yystack.l_mark[0].v.string)) == NULL) {
				yyerror("invalid address: %s\n", yystack.l_mark[0].v.string);
				free(yystack.l_mark[0].v.string);
				YYERROR;
			}
			free(yystack.l_mark[0].v.string);

			memcpy(yyval.v.lladdr, ea, ETHER_ADDR_LEN);
		}
#line 2955 "parse.tab.c"
break;
case 80:
#line 738 "parse.y"
	{
			memset(yyval.v.lladdr, 0, ETHER_ADDR_LEN);
		}
#line 2962 "parse.tab.c"
break;
case 81:
#line 743 "parse.y"
	{ yyval.v.number = 0; }
#line 2967 "parse.tab.c"
break;
case 82:
#line 744 "parse.y"
	{ yyval.v.number = 1; }
#line 2972 "parse.tab.c"
break;
case 83:
#line 747 "parse.y"
	{ yyval.v.number = 0; }
#line 2977 "parse.tab.c"
break;
case 84:
#line 748 "parse.y"
	{ yyval.v.number = 1; }
#line 2982 "parse.tab.c"
break;
case 85:
#line 751 "parse.y"
	{ yyval.v.number = 1; }
#line 2987 "parse.tab.c"
break;
case 86:
#line 752 "parse.y"
	{ yyval.v.number = 0; }
#line 2992 "parse.tab.c"
break;
case 87:
#line 755 "parse.y"
	{ yyval.v.number = 0; }
#line 2997 "parse.tab.c"
break;
case 88:
#line 756 "parse.y"
	{ yyval.v.number = 1; }
#line 3002 "parse.tab.c"
break;
case 89:
#line 759 "parse.y"
	{ yyval.v.number = VMBOOTDEV_CDROM; }
#line 3007 "parse.tab.c"
break;
case 90:
#line 760 "parse.y"
	{ yyval.v.number = VMBOOTDEV_DISK; }
#line 3012 "parse.tab.c"
break;
case 91:
#line 761 "parse.y"
	{ yyval.v.number = VMBOOTDEV_NET; }
#line 3017 "parse.tab.c"
break;
#line 3019 "parse.tab.c"
    default:
        break;
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark -= yym;
#endif
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
        {
            fprintf(stderr, "%s[%d]: after reduction, ", YYDEBUGSTR, yydepth);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
            if (!yytrial)
#endif /* YYBTYACC */
                fprintf(stderr, "result is <%s>, ", YYSTYPE_TOSTRING(yystos[YYFINAL], yyval));
#endif
            fprintf(stderr, "shifting from state 0 to final state %d\n", YYFINAL);
        }
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        *++yystack.p_mark = yyloc;
#endif
        if (yychar < 0)
        {
#if YYBTYACC
            do {
            if (yylvp < yylve)
            {
                /* we're currently re-reading tokens */
                yylval = *yylvp++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylloc = *yylpp++;
#endif
                yychar = *yylexp++;
                break;
            }
            if (yyps->save)
            {
                /* in trial mode; save scanner results for future parse attempts */
                if (yylvp == yylvlim)
                {   /* Enlarge lexical value queue */
                    size_t p = (size_t) (yylvp - yylvals);
                    size_t s = (size_t) (yylvlim - yylvals);

                    s += YYLVQUEUEGROWTH;
                    if ((yylexemes = (YYINT *)realloc(yylexemes, s * sizeof(YYINT))) == NULL)
                        goto yyenomem;
                    if ((yylvals   = (YYSTYPE *)realloc(yylvals, s * sizeof(YYSTYPE))) == NULL)
                        goto yyenomem;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    if ((yylpsns   = (YYLTYPE *)realloc(yylpsns, s * sizeof(YYLTYPE))) == NULL)
                        goto yyenomem;
#endif
                    yylvp   = yylve = yylvals + p;
                    yylvlim = yylvals + s;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    yylpp   = yylpe = yylpsns + p;
                    yylplim = yylpsns + s;
#endif
                    yylexp  = yylexemes + p;
                }
                *yylexp = (YYINT) YYLEX;
                *yylvp++ = yylval;
                yylve++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                *yylpp++ = yylloc;
                yylpe++;
#endif
                yychar = *yylexp++;
                break;
            }
            /* normal operation, no conflict encountered */
#endif /* YYBTYACC */
            yychar = YYLEX;
#if YYBTYACC
            } while (0);
#endif /* YYBTYACC */
            if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
                fprintf(stderr, "%s[%d]: state %d, reading token %d (%s)\n",
                                YYDEBUGSTR, yydepth, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if (((yyn = yygindex[yym]) != 0) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
    {
        fprintf(stderr, "%s[%d]: after reduction, ", YYDEBUGSTR, yydepth);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
        if (!yytrial)
#endif /* YYBTYACC */
            fprintf(stderr, "result is <%s>, ", YYSTYPE_TOSTRING(yystos[yystate], yyval));
#endif
        fprintf(stderr, "shifting from state %d to state %d\n", *yystack.s_mark, yystate);
    }
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    *++yystack.p_mark = yyloc;
#endif
    goto yyloop;
#if YYBTYACC

    /* Reduction declares that this path is valid. Set yypath and do a full parse */
yyvalid:
    if (yypath) YYABORT;
    while (yyps->save)
    {
        YYParseState *save = yyps->save;
        yyps->save = save->save;
        save->save = yypath;
        yypath = save;
    }
#if YYDEBUG
    if (yydebug)
        fprintf(stderr, "%s[%d]: state %d, CONFLICT trial successful, backtracking to state %d, %d tokens\n",
                        YYDEBUGSTR, yydepth, yystate, yypath->state, (int)(yylvp - yylvals - yypath->lexeme));
#endif
    if (yyerrctx)
    {
        yyFreeState(yyerrctx);
        yyerrctx = NULL;
    }
    yylvp          = yylvals + yypath->lexeme;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yylpp          = yylpsns + yypath->lexeme;
#endif
    yylexp         = yylexemes + yypath->lexeme;
    yychar         = YYEMPTY;
    yystack.s_mark = yystack.s_base + (yypath->yystack.s_mark - yypath->yystack.s_base);
    memcpy (yystack.s_base, yypath->yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
    yystack.l_mark = yystack.l_base + (yypath->yystack.l_mark - yypath->yystack.l_base);
    memcpy (yystack.l_base, yypath->yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark = yystack.p_base + (yypath->yystack.p_mark - yypath->yystack.p_base);
    memcpy (yystack.p_base, yypath->yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
    yystate        = yypath->state;
    goto yyloop;
#endif /* YYBTYACC */

yyoverflow:
    YYERROR_CALL("yacc stack overflow");
#if YYBTYACC
    goto yyabort_nomem;
yyenomem:
    YYERROR_CALL("memory exhausted");
yyabort_nomem:
#endif /* YYBTYACC */
    yyresult = 2;
    goto yyreturn;

yyabort:
    yyresult = 1;
    goto yyreturn;

yyaccept:
#if YYBTYACC
    if (yyps->save) goto yyvalid;
#endif /* YYBTYACC */
    yyresult = 0;

yyreturn:
#if defined(YYDESTRUCT_CALL)
    if (yychar != YYEOF && yychar != YYEMPTY)
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        YYDESTRUCT_CALL("cleanup: discarding token", yychar, &yylval, &yylloc);
#else
        YYDESTRUCT_CALL("cleanup: discarding token", yychar, &yylval);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */

    {
        YYSTYPE *pv;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        YYLTYPE *pp;

        for (pv = yystack.l_base, pp = yystack.p_base; pv <= yystack.l_mark; ++pv, ++pp)
             YYDESTRUCT_CALL("cleanup: discarding state",
                             yystos[*(yystack.s_base + (pv - yystack.l_base))], pv, pp);
#else
        for (pv = yystack.l_base; pv <= yystack.l_mark; ++pv)
             YYDESTRUCT_CALL("cleanup: discarding state",
                             yystos[*(yystack.s_base + (pv - yystack.l_base))], pv);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
    }
#endif /* defined(YYDESTRUCT_CALL) */

#if YYBTYACC
    if (yyerrctx)
    {
        yyFreeState(yyerrctx);
        yyerrctx = NULL;
    }
    while (yyps)
    {
        YYParseState *save = yyps;
        yyps = save->save;
        save->save = NULL;
        yyFreeState(save);
    }
    while (yypath)
    {
        YYParseState *save = yypath;
        yypath = save->save;
        save->save = NULL;
        yyFreeState(save);
    }
#endif /* YYBTYACC */
    yyfreestack(&yystack);
    return (yyresult);
}
