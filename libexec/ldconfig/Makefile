MAN=	ldconfig.8

PROG=	ldconfig
OBJS=	ldconfig.o shlib.o etc.o sod.o ldconfig_path.o
CFLAGS+=-Wall
CFLAGS+=-I${CURDIR}/../ld.so
LDFLAGS+=-static
BINDIR=	/usr/sbin

include cobalt.prog.mk
