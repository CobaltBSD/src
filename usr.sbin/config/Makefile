PROG=	config
OBJS=	files.o gram.tab.o hash.o main.o mkheaders.o mkioconf.o mkmakefile.o \
	mkswap.o pack.o scan.o sem.o util.o \
	ukc.o misc.o ukcutil.o cmd.o
OBJS+=  exec_elf.o

#CFLAGS+=-I${.CURDIR} -I.

LIBS=	-lkvm

MAN=	config.8

BINDIR=${SBINDIR}

CLEANFILES+=gram.tab.c gram.tab.h scan.yy.c

include cobalt.prog.mk
