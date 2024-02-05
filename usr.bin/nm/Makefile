PROG=	nm
OBJS=	nm.o elf32.o elf64.o
CLEANFILES+=elf32.c elf64.c
CFLAGS+=-I${CURDIR}
SYMLINKS=	${BINDIR}/size
MAN=	nm.1 size.1

include cobalt.prog.mk

elf32.c: ${CURDIR}/elf.c
	echo '#define ELFSIZE 32' | cat - $< > $@

elf64.c: ${CURDIR}/elf.c
	echo '#define ELFSIZE 64' | cat - $< > $@
