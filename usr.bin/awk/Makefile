PROG=	awk
OBJS=	awkgram.tab.o lex.o b.o main.o parse.o proctab.o tran.o lib.o run.o
LIBS=	-lm
MAN=	awk.1
CLEANFILES+=proctab.c maketab ${YACCFILES}
CFLAGS+=-DHAS_ISBLANK -DNDEBUG

include cobalt.prog.mk

proctab.c: maketab
	./maketab awkgram.tab.h >proctab.c

maketab: awkgram.tab.o maketab.c
	$(CC) ${CFLAGS} ${CURDIR}/maketab.c -o $@
