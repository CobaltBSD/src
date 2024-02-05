OBJS=	apm.o apmsubr.o

BINDIR=${SBINDIR}
CFLAGS+=	-I${CURDIR}/../apmd
PROG=	apm
SYMLINKS=	${SBINDIR}/zzz
SYMLINKS+= ${SBINDIR}/ZZZ

MAN=	apm.8

include cobalt.prog.mk
