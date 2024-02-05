# -DEXTENDED 
# 	if you want the paste & spaste macros.

PROG=	m4
CFLAGS+=-DEXTENDED -I.
CFLAGS+=-W -Wall -Wstrict-prototypes -pedantic \
	-Wno-unused -Wno-char-subscripts -Wno-sign-compare

LIBS= -lm -lutil

CLEANFILES+=parser.tab.c parser.tab.h tokenizer.yy.c

OBJS=	eval.o expr.o look.o main.o misc.o gnum4.o trace.o parser.tab.o tokenizer.o
MAN=	m4.1

include cobalt.prog.mk
