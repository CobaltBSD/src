PROG=	dhcpleasectl
BINDIR=${SBINDIR}

MAN=	dhcpleasectl.8

CFLAGS+= -Wall
CFLAGS+= -Wstrict-prototypes -Wmissing-prototypes
CFLAGS+= -Wmissing-declarations
CFLAGS+= -Wshadow -Wpointer-arith -Wcast-qual
CFLAGS+= -Wsign-compare
#CFLAGS+= -I${.CURDIR} -I${.CURDIR}/../../usr.sbin/dhcpleased
CFLAGS+= -I../dhcpleased
LIBS=	-lutil

include cobalt.prog.mk
