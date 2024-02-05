INSTALL_COPY = -c
INSTALL_STRIP = -s

PREFIX ?= /usr

BINOWN ?= root
BINGRP ?= bin
BINMODE ?= 555

LIBOWN ?=	root
LIBGRP ?=	bin
LIBMODE ?=	444
LIBDIR ?=	${PREFIX}/lib

MANOWN ?= root
MANGRP ?= bin
MANMODE?= 444
MANDIR ?= ${PREFIX}/share/man

DIRMODE?=	755

OBJS ?= ${LIB}.o

FULLSHLIBNAME = lib${LIB}.so.${SHLIB_MAJOR}.${SHLIB_MINOR}

all: ${LIB}

${LIB}: ${OBJS}
	$(CC) -shared ${OBJS} ${LDFLAGS} ${LIBS} -Wl,-soname=${FULLSHLIBNAME} -o ${FULLSHLIBNAME}

install: ${LIB}
	if [ x${LIB} != x ]; then \
		$(INSTALL) -D ${INSTALL_COPY} ${INSTALL_STRIP} \
			-o ${BINOWN} -g ${BINGRP} \
			-m ${BINMODE} ${FULLSHLIBNAME} ${DESTDIR}${LIBDIR}/${FULLSHLIBNAME}; \
	fi
	if [ "x${MAN}" != x ]; then \
		for MANPAGE in ${MAN}; do \
			$(INSTALL) -D ${INSTALL_COPY} \
				-o ${MANOWN} -g ${MANGRP} \
				-m ${MANMODE} $$MANPAGE ${DESTDIR}${MANDIR}/man$${MANPAGE##*.}/$$MANPAGE; \
		done \
	fi
	for SLNK in ${SYMLINKS}; do \
		$(INSTALL) -d -m ${DIRMODE} $$(dirname ${DESTDIR}/$$SLNK); \
		ln -sf ${LIBDIR}/${LIB} ${DESTDIR}/$$SLNK; \
	done
	for HDR in ${HDRS}; do \
		$(INSTALL) -D ${INSTALL_COPY} \
			-o ${BINOWN} -g ${BINGRP} \
			-m 444 $$HDR ${DESTDIR}/usr/include/${HDRPREFIX}/$$HDR; \
	done

clean:
	rm -fv ${FULLSHLIBNAME} *.o
