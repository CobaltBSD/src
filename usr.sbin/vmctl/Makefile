PROG=	vmctl
OBJS=	vmctl.o main.o atomicio.o
OBJS+=	vioqcow2.o vioraw.o log.o
CFLAGS+= -Wall
CFLAGS+= -Wstrict-prototypes -Wmissing-prototypes
CFLAGS+= -Wmissing-declarations
CFLAGS+= -Wshadow -Wpointer-arith -Wcast-qual
CFLAGS+= -Wsign-compare
CFLAGS+= -I${CURDIR}/../vmd
LIBS=	-lutil -lpthread

MAN= vmctl.8

BINDIR=${SBINDIR}

include cobalt.prog.mk
