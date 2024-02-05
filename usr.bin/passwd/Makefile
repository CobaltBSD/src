PROG=	passwd

OBJS=	local_passwd.o passwd.o getpwent.o \
	pwd_check.o
#.PATH:  ${.CURDIR}/../../pkg/dist/cblibc/libc/gen
LIBS+= -lutil
#CFLAGS+= -I${CURDIR}

#CFLAGS+=-I${.CURDIR}/../../pkg/dist/cblibc/libc/include

BINMODE=4555
BINOWN=root

MAN=passwd.1

include cobalt.prog.mk

getpwent.o:
	$(CC) -I${CURDIR}/../../lib/libc/include -c -UYP -D'DEF_WEAK(x)=asm("")' \
	    ${CURDIR}/../../lib/libc/gen/getpwent.c
