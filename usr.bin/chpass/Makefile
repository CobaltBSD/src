PROG=	chpass
OBJS=	chpass.o edit.o field.o table.o util.o getpwent.o
BINOWN=	root
BINMODE=4555
SYMLINKS=	${BINDIR}/chfn ${BINDIR}/chpass ${BINDIR}/chsh
LIBS= -lutil

include cobalt.prog.mk

getpwent.o:
	$(CC) -I${CURDIR}/../../lib/libc/include -c -UYP -D'DEF_WEAK(x)=asm("")' \
	    ${CURDIR}/../../lib/libc/gen/getpwent.c

