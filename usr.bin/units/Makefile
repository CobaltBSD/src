PROG=	units
MAN=	units.1

beforeinstall:
	${INSTALL} ${INSTALL_COPY} -D -o ${BINOWN} -g ${BINGRP} -m 444 \
	    ${CURDIR}/units.lib ${DESTDIR}/usr/share/misc/units.lib

include cobalt.prog.mk
