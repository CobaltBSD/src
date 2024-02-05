PROG=		mklocale
OBJS=		yacc.tab.o lex.o
CFLAGS+=	-I. -I${CURDIR} -I${CURDIR}/../libc -I${CURDIR}/../libc/include
CLEANFILES += yacc.tab.c yacc.tab.h lex.yy.c
MAN=mklocale.1

include cobalt.prog.mk
