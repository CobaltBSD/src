MAN=	ld.so.1

BINDIR=${LIBEXECDIR}

CC=clang
LD=ld

PROG=	ld.so
BINMODE=444

VERSION_SCRIPT=	${CURDIR}/Symbols.map
LDFLAGS+=--version-script=${VERSION_SCRIPT}

BOOT = boot.o

OBJS=	amd64/ldasm.o ${BOOT} loader.o resolve.o dlfcn.o dl_printf.o amd64/rtld_machine.o
OBJS+=	path.o util.o sod.o strsep.o strtol.o dir.o library_subr.o
OBJS+=	dl_uname.o dl_dirname.o strlcat.o strlen.o trace.o
OBJS+=	malloc.o reallocarray.o tib.o ffs.o

SYSCALL_OBJS=	dl_close.o \
		dl_exit.o \
		dl_fstat.o \
		dl_getdents.o \
		dl_getentropy.o \
		dl_getthrid.o \
		dl_issetugid.o \
		dl_kbind.o \
		dl_mimmutable.o \
		dl_mmap.o \
		dl_mprotect.o \
		dl_munmap.o \
		dl_msyscall.o \
		dl_open.o \
		dl_pledge.o \
		dl_pinsyscall.o \
		dl_read.o \
		dl___realpath.o \
		dl_sendsyslog.o \
		dl___set_tcb.o \
		dl_sysctl.o \
		dl_thrkill.o \
		dl_utrace.o \
		dl_write.o

OBJS+=	library.o ${SYSCALL_OBJS}

include cobalt.prog.mk

${SYSCALL_OBJS}: amd64/SYS.h
	printf '\t.file "$@.c"\n#include "amd64/SYS.h"\nDL_SYSCALL($(basename $(subst dl_,,$@)))\n' | \
		${CC} -c \
		-P -x assembler-with-cpp - \
		-o $@

CFLAGS += -fno-builtin
CFLAGS += -Wall -Werror
CFLAGS += -I${CURDIR} -I${CURDIR}/amd64 \
	-D'DEF_WEAK(x)=asm("")' -D'DEF_STRONG(x)=asm("")' \
	-Dstrsep=_dl_strsep -Dstrlcat=_dl_strlcat -Dstrlen=_dl_strlen
INSTALL_STRIP=

ELF_LDFLAGS+=--shared -Bsymbolic --no-undefined

test_prog=	test-$(PROG)
CLEANFILES+=	test-$(PROG)
candidate=	$(PROG).test
CLEANFILES+=	${candidate}

$(test_prog):
	printf '#include <stdio.h>\n#include <pthread.h>\nint main(int argc, char **argv){ pthread_attr_t attr; printf("%%s: ", argv[0]); pthread_attr_init(&attr); printf("%%s!\\n", argv[1] ? argv[1] : "foo"); }\n' | \
	$(CC) -P -x c - -Wl,-dynamic-linker,./$(candidate) -o $@ -lpthread

$(PROG): $(test_prog) ${VERSION_SCRIPT} $(OBJS)
	$(LD) -e _dl_start $(ELF_LDFLAGS) -o $(candidate) \
		`echo ${OBJS} | tr " " "\n" | sort -R`
	\
	! readelf -Wr ${candidate} |				\
	  egrep -qv '^($$|[ R])| (${RELATIVE_RELOC}) ';	\
	\
	ulimit -c 0; [ "`${CURDIR}/$(test_prog) ok`" = "${CURDIR}/$(test_prog): ok!" ]
	cp ${candidate} $@

boot.o:
	$(CC) ${CFLAGS} -fno-stack-protector -c $(basename $@).c

CLEANFILES+=	ld.so.a

ld.so.a: ${OBJS} ${CURDIR}/Symbols.map ${test_prog}
	ar cqD $@ $?

beforeinstall: ld.so.a
	install -d -o root -g wheel -m ${DIRMODE} \
	    ${DESTDIR}/usr/share/relink/usr/libexec
	install -o ${BINOWN} -g ${BINGRP} -m 444 \
	    ld.so.a ${DESTDIR}/usr/share/relink/usr/libexec/ld.so.a
