PROG=		crunchgen
MAN=		crunchgen.8
OBJS=		crunchgen.o crunched_skel.o crunchide.o elf_hide.o mangle.o
CFLAGS+=	-g -Wall
CLEANFILES+=	crunched_skel.c
BINDIR=${SBINDIR}

include cobalt.prog.mk

crunched_skel.c:
	sh ${CURDIR}/mkskel.sh ${CURDIR}/crunched_main.c > crunched_skel.c
