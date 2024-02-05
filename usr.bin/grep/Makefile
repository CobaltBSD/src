PROG=	grep
OBJS=	binary.o file.o grep.o mmfile.o queue.o util.o
SYMLINKS=	${BINDIR}/egrep \
	${BINDIR}/fgrep \
	${BINDIR}/zgrep \
	${BINDIR}/zegrep \
	${BINDIR}/zfgrep

CFLAGS+= -Wall

LIBS=	-lz

include cobalt.prog.mk

#TODO: manpage symlinks
