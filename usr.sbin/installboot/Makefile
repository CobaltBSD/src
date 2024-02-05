PROG=		installboot
OBJS=		installboot.o util.o
MAN=		installboot.8

LIBS=		-lutil

LDFLAGS+=	-static

CFLAGS += -DSOFTRAID
OBJS += i386_installboot.o
OBJS += i386_nlist.o
OBJS += i386_softraid.o
OBJS += softraid.o

BINDIR=${SBINDIR}

include cobalt.prog.mk
