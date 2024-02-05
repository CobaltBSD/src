PROG=	iostat
MAN=	iostat.8

#.PATH:	${.CURDIR}/../../usr.bin/vmstat

#CFLAGS+=-I${.CURDIR}/../../usr.bin/vmstat

# dkstats.c pulled in from ../../usr.bin/vmstat
OBJS=	dkstats.o iostat.o

LIBS=	-lkvm

BINDIR=${SBINDIR}

include cobalt.prog.mk
