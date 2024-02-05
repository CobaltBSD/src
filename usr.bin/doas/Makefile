OBJS=	parse.tab.o doas.o env.o

PROG=	doas
MAN=	doas.1 doas.conf.5

BINOWN= root
BINMODE=4555

CFLAGS+= -I${CURDIR}
CFLAGS+=	-Wall

CLEANFILES += parse.tab.c parse.tab.h

include cobalt.prog.mk
