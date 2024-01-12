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
#line 63 "cfgparse.y"
#ifdef DEBUG
#define	YYDEBUG 1
#endif
#include "xkbevd.h"
#include <stdlib.h>
#line 75 "cfgparse.y"
#ifndef YYSTYPE_DEFINED
#define YYSTYPE_DEFINED
typedef union	{
	char *		str;
	int		ival;
	CfgEntryPtr	entry;
	ActDefPtr	act;
} YYSTYPE;
#endif /* YYSTYPE_DEFINED */
#line 29 "cfgparse.c"
#define END_OF_FILE 0
#define ERROR 255
#define BELL 1
#define ACCESSX 2
#define MESSAGE 3
#define NONE 20
#define IGNORE 21
#define ECHO 22
#define PRINT_EV 23
#define SHELL 24
#define SOUND 25
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
#define YYERRCODE 256
const short yylhs[] =
	{                                        -1,
    0,    9,    9,   10,   10,   12,   11,    7,    7,    7,
    8,    6,    6,    6,    6,    6,    6,    6,    5,    5,
    4,    4,    1,    3,    3,    2,
};
const short yylen[] =
	{                                         2,
    1,    2,    1,    2,    1,    3,    4,    1,    1,    1,
    2,    1,    1,    1,    1,    1,    1,    0,    1,    0,
    1,    1,    1,    1,    0,    1,
};
const short yydefred[] =
	{                                      0,
    8,    9,   10,   23,    0,    0,    0,    0,    3,    0,
    5,    0,    0,    2,   12,   13,   14,   15,   16,   17,
    0,    4,   26,   21,   22,    6,   19,    0,   24,   11,
    7,
};
const short yydgoto[] =
	{                                       5,
    6,   25,   30,   26,   28,   21,    7,   22,    8,    9,
   10,   11,
};
const short yysindex[] =
	{                                      8,
    0,    0,    0,    0,    0,  -40,  -25,    8,    0,   -8,
    0,  -42,  -42,    0,    0,    0,    0,    0,    0,    0,
  -37,    0,    0,    0,    0,    0,    0,  -24,    0,    0,
    0,};
const short yyrindex[] =
	{                                      0,
    0,    0,    0,    0,    0,    0,    0,   25,    0,    1,
    0,    0,  -22,    0,    0,    0,    0,    0,    0,    0,
    5,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,};
const short yygindex[] =
	{                                      0,
    7,    6,    0,   15,    0,    0,    0,    0,    0,   21,
    0,    0,
};
#define YYTABLESIZE 71
const short yytable[] =
	{                                      12,
   18,   18,   18,   18,   25,   25,   25,   25,    1,    2,
    3,   15,   16,   17,   18,   19,   20,   23,   24,   24,
    4,   13,   23,   31,    1,   20,   29,   27,   14,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   18,    0,    0,   18,    0,    0,    0,   25,    0,    0,
    4,
};
const short yycheck[] =
	{                                      40,
    0,    1,    2,    3,    0,    1,    2,    3,    1,    2,
    3,   20,   21,   22,   23,   24,   25,   60,   12,   13,
   63,   47,   60,   48,    0,   48,   21,   13,    8,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   60,   -1,   -1,   63,   -1,   -1,   -1,   63,   -1,   -1,
   63,
};
#define YYFINAL 5
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 255
#if YYDEBUG
const char * const yyname[] =
	{
"end-of-file","BELL","ACCESSX","MESSAGE",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"NONE",
"IGNORE","ECHO","PRINT_EV","SHELL","SOUND",0,0,0,0,0,0,0,0,0,0,0,0,0,0,"EQUALS",
"PLUS","MINUS","DIVIDE","TIMES","OBRACE","CBRACE","OPAREN","CPAREN","OBRACKET",
"CBRACKET","DOT","COMMA","SEMI","EXCLAM","INVERT",0,0,0,0,"STRING","INTEGER",
"FLOAT","IDENT","KEYNAME",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,"ERROR",
};
const char * const yyrule[] =
	{"$accept : CfgFile",
"CfgFile : CfgEntryList",
"CfgEntryList : CfgEntryList CfgEntry",
"CfgEntryList : CfgEntry",
"CfgEntry : EventDef ActionDef",
"CfgEntry : VarDef",
"VarDef : Ident EQUALS NameSpec",
"EventDef : EventType OPAREN OptNameSpec CPAREN",
"EventType : BELL",
"EventType : ACCESSX",
"EventType : MESSAGE",
"ActionDef : ActionType OptString",
"ActionType : NONE",
"ActionType : IGNORE",
"ActionType : ECHO",
"ActionType : PRINT_EV",
"ActionType : SHELL",
"ActionType : SOUND",
"ActionType :",
"OptNameSpec : NameSpec",
"OptNameSpec :",
"NameSpec : Ident",
"NameSpec : String",
"Ident : IDENT",
"OptString : String",
"OptString :",
"String : STRING",
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
#line 194 "cfgparse.y"
int
yyerror(char *s)
{
    (void)fprintf(stderr,"%s: line %d of %s\n",s,lineNum,
					(scanFile?scanFile:"(unknown)"));
    if (scanStr)
	(void)fprintf(stderr,"last scanned symbol is: %s\n",scanStr);
    return 1;
}


int
yywrap(void)
{
   return 1;
}

int
CFGParseFile(FILE *file)
{
    if (file) {
	yyin= file;
	if (yyparse()==0) {
	    return 1;
	}
	return 0;
    }
    return 1;
}
#line 224 "cfgparse.c"
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
#line 87 "cfgparse.y"
{ InterpretConfigs(yyvsp[0].entry); }
break;
case 2:
#line 91 "cfgparse.y"
{
			    CfgEntryPtr tmp;
			    if (yyvsp[-1].entry!=NULL) {
				for (tmp=yyvsp[-1].entry;tmp->next!=NULL;tmp=tmp->next) {
				    /* conditional does the work */
				}
				tmp->next= yyvsp[0].entry;
				yyval.entry= yyvsp[-1].entry;
			    }
			    else yyval.entry= yyvsp[0].entry;
			}
break;
case 3:
#line 102 "cfgparse.y"
{ yyval.entry= yyvsp[0].entry; }
break;
case 4:
#line 106 "cfgparse.y"
{
			    if ((yyvsp[-1].entry)&&(yyvsp[0].act))
				yyvsp[-1].entry->action= *(yyvsp[0].act);
			    if (yyvsp[0].act)
				free(yyvsp[0].act);
			    yyval.entry= yyvsp[-1].entry;
			}
break;
case 5:
#line 113 "cfgparse.y"
{ yyval.entry= yyvsp[0].entry; }
break;
case 6:
#line 117 "cfgparse.y"
{
			    CfgEntryPtr cfg;
			    cfg= calloc(1,sizeof(CfgEntryRec));
			    if (cfg) {
				cfg->entry_type= VariableDef;
				cfg->event_type= 0;
				cfg->name.str= yyvsp[-2].str;
				cfg->action.type= UnknownAction;
				cfg->action.text= yyvsp[0].str;
				cfg->action.priv= 0;
				cfg->next= NULL;
			    }
			    yyval.entry= cfg;
			}
break;
case 7:
#line 134 "cfgparse.y"
{
			    CfgEntryPtr cfg;
			    cfg= calloc(1,sizeof(CfgEntryRec));
			    if (cfg) {
				cfg->entry_type= EventDef;
				cfg->event_type= yyvsp[-3].ival;
				cfg->name.str= yyvsp[-1].str;
				cfg->action.type= UnknownAction;
				cfg->action.text= NULL;
				cfg->action.priv= 0;
				cfg->next= NULL;
			    }
			    yyval.entry= cfg;
			}
break;
case 8:
#line 150 "cfgparse.y"
{ yyval.ival= XkbBellNotify; }
break;
case 9:
#line 151 "cfgparse.y"
{ yyval.ival= XkbAccessXNotify; }
break;
case 10:
#line 152 "cfgparse.y"
{ yyval.ival= XkbActionMessage; }
break;
case 11:
#line 156 "cfgparse.y"
{
			    ActDefPtr act;
			    act= calloc(1,sizeof(ActDefRec));
			    if (act) {
				act->type= yyvsp[-1].ival;
				act->text= yyvsp[0].str;
			    }
			    yyval.act= act;
			}
break;
case 12:
#line 167 "cfgparse.y"
{ yyval.ival = NoAction; }
break;
case 13:
#line 168 "cfgparse.y"
{ yyval.ival = NoAction; }
break;
case 14:
#line 169 "cfgparse.y"
{ yyval.ival = EchoAction; }
break;
case 15:
#line 170 "cfgparse.y"
{ yyval.ival = PrintEvAction; }
break;
case 16:
#line 171 "cfgparse.y"
{ yyval.ival = ShellAction; }
break;
case 17:
#line 172 "cfgparse.y"
{ yyval.ival = SoundAction; }
break;
case 18:
#line 173 "cfgparse.y"
{ yyval.ival = UnknownAction; }
break;
case 19:
#line 176 "cfgparse.y"
{ yyval.str= yyvsp[0].str; }
break;
case 20:
#line 177 "cfgparse.y"
{ yyval.str= NULL; }
break;
case 21:
#line 180 "cfgparse.y"
{ yyval.str= yyvsp[0].str; }
break;
case 22:
#line 181 "cfgparse.y"
{ yyval.str= yyvsp[0].str; }
break;
case 23:
#line 184 "cfgparse.y"
{ yyval.str= scanStr; scanStr= NULL; }
break;
case 24:
#line 187 "cfgparse.y"
{ yyval.str= yyvsp[0].str; }
break;
case 25:
#line 188 "cfgparse.y"
{ yyval.str= NULL; }
break;
case 26:
#line 191 "cfgparse.y"
{ yyval.str= scanStr; scanStr= NULL; }
break;
#line 570 "cfgparse.c"
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
