PROG=	xinstall
MAN=	install.1

include cobalt.prog.mk

install:
	${INSTALL} ${INSTALL_COPY} -D ${INSTALL_STRIP} \
	    -o ${BINOWN} -g ${BINGRP} \
	    -m ${BINMODE} ${PROG} ${DESTDIR}${BINDIR}/install
	${INSTALL} ${INSTALL_COPY} -D \
	    -o ${BINOWN} -g ${BINGRP} \
	    -m 444 ${MAN} ${DESTDIR}/usr/share/man/man1/${MAN}
