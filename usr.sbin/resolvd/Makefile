PROG=	resolvd

MAN=	resolvd.8

#DEBUG=	-g -DDEBUG=3 -O0

#CFLAGS+= -Wall -I${.CURDIR}
CFLAGS+= -Wstrict-prototypes -Wmissing-prototypes
CFLAGS+= -Wmissing-declarations
CFLAGS+= -Wshadow -Wpointer-arith -Wcast-qual
CFLAGS+= -Wsign-compare

LDFLAGS= -static

BINDIR=${SBINDIR}

include cobalt.prog.mk
