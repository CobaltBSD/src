SCRIPT=		ctfstrip.sh
PROG=		ctfconv
OBJS=		ctfconv.o parse.o elf.o dw.o generate.o hash.o xmalloc.o \
		pool.o

CFLAGS+=	-W -Wall -Wstrict-prototypes -Wno-unused -Wunused-variable \
		-Wno-unused-parameter

CFLAGS+=	-DZLIB
LIBS=-lz

MAN=		ctfconv.1 ctfstrip.1

include cobalt.prog.mk
