#	$OpenBSD: Makefile,v 1.41 2015/11/26 19:01:47 deraadt Exp $

.include <bsd.own.mk>

PROG=	passwd
#SRCS=	local_passwd.c passwd.c getpwent.c \

SRCS=	local_passwd.c passwd.c \
	pwd_check.c
#.PATH:  ${.CURDIR}/../../pkg/dist/cblibc/libc/gen
#DPADD+= ${LIBRPCSVC} ${LIBUTIL}
#LDADD+= -lrpcsvc -lutil
DPADD+= ${LIBUTIL}
LDADD+= -lutil
CFLAGS+= -I${.CURDIR}

#CFLAGS+=-I${.CURDIR}/../../pkg/dist/cblibc/libc/include

BINMODE=4555
BINOWN=root

#getpwent.o: getpwent.c
#	${COMPILE.c} -UYP -D'DEF_WEAK(x)=asm("")' \
#	    ${.CURDIR}/../../pkg/dist/cblibc/libc/gen/getpwent.c

.include <bsd.prog.mk>
