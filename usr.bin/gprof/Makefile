TARGET_MACHINE_CPU=	amd64

PROG=	gprof
MAN=	gprof.1
OBJS=	gprof.o arcs.o dfn.o elf.o lookup.o ${TARGET_MACHINE_CPU}.o \
	hertz.o printgprof.o printlist.o
CFLAGS+= -I. -DMD_INCLUDE=\"${TARGET_MACHINE_CPU}.h\"

include cobalt.prog.mk

beforeinstall:
	$(INSTALL) ${INSTALL_COPY} -d -o ${BINOWN} -g ${BINGRP} -m ${DIRMODE} \
	    ${DESTDIR}${PREFIX}/share/misc
	$(INSTALL) ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} -m 444 \
	    ${CURDIR}/gprof.flat ${CURDIR}/gprof.callg \
	    ${DESTDIR}${PREFIX}/share/misc
