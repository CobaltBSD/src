PROG=	traceroute

OBJS=	traceroute.o worker.o

#CFLAGS+= -Wall -I${.CURDIR}
CFLAGS+= -Wstrict-prototypes -Wmissing-prototypes
CFLAGS+= -Wmissing-declarations
CFLAGS+= -Wshadow -Wpointer-arith -Wcast-qual
LIBS=	-levent

MAN=	traceroute.8

BINDIR=${SBINDIR}
SYMLINKS=${BINDIR}/traceroute6
BINOWN=	root
BINMODE=4555

include cobalt.prog.mk
