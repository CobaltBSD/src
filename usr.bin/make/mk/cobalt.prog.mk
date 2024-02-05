INSTALL_COPY = -c
INSTALL_STRIP = -s

PREFIX ?= /usr

BINOWN ?= root
BINGRP ?= bin
BINMODE ?= 555
BINDIR ?= ${PREFIX}/bin

SBINDIR ?= ${PREFIX}/sbin
LIBEXECDIR ?= ${PREFIX}/libexec

MANOWN ?= root
MANGRP ?= bin
MANMODE?= 444
MANDIR ?= ${PREFIX}/share/man

DIRMODE?=	755

OBJS ?= ${PROG}.o

all: ${PROG}

${PROG}: ${OBJS}
	$(LD) ${OBJS} ${LDFLAGS} ${LIBS} -o ${PROG}

install: ${PROG} beforeinstall
	if [ x${PROG} != x ]; then \
		$(INSTALL) -D ${INSTALL_COPY} ${INSTALL_STRIP} \
			-o ${BINOWN} -g ${BINGRP} \
			-m ${BINMODE} ${PROG} ${DESTDIR}${BINDIR}/${PROG}; \
	fi
	if [ "x${MAN}" != x ]; then \
		for MANPAGE in ${MAN}; do \
			$(INSTALL) -D ${INSTALL_COPY} \
				-o ${MANOWN} -g ${MANGRP} \
				-m ${MANMODE} $$(basename $$MANPAGE) ${DESTDIR}${MANDIR}/man$${MANPAGE##*.}/$$MANPAGE; \
		done \
	fi
	for SLNK in ${SYMLINKS}; do \
		$(INSTALL) -d -m ${DIRMODE} $$(dirname ${DESTDIR}/$$SLNK); \
		ln -sf ${BINDIR}/${PROG} ${DESTDIR}/$$SLNK; \
	done
	for SCRPT in ${SCRIPT}; do \
		$(INSTALL) -D ${INSTALL_COPY} \
			-o ${BINOWN} -g ${BINGRP} \
			-m ${BINMODE} $$SCRPT ${DESTDIR}${BINDIR}/$${SCRPT%.*}; \
	done

clean:
	find . -name "*.o" -delete
	rm -fv ${PROG} ${CLEANFILES}

beforeinstall:
