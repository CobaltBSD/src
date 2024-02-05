PROG=	ksh
LIBS=	-lcurses

OBJS=	alloc.o c_ksh.o c_sh.o c_test.o c_ulimit.o edit.o emacs.o eval.o \
	exec.o expr.o history.o io.o jobs.o lex.o mail.o main.o \
	misc.o path.o shf.o syn.o table.o trap.o tree.o tty.o var.o \
	version.o vi.o

DEFS=	-DEMACS -DVI
CFLAGS+=${DEFS} -I. -I${CURDIR} -I${CURDIR}/../../lib/libc/gen
MAN=	ksh.1 sh.1

SYMLINKS=	${BINDIR}/rksh
SYMLINKS+=	${BINDIR}/sh

include cobalt.prog.mk
