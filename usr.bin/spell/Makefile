SCRIPT=	spell.ksh
MAN=	spell.1

include cobalt.prog.mk

beforeinstall:
	${INSTALL} ${INSTALL_COPY} -d -o ${BINOWN} -g ${BINGRP} -m ${DIRMODE} \
		${DESTDIR}/usr/share/dict/special
	${INSTALL} ${INSTALL_COPY} -D -o ${BINOWN} -g ${BINGRP} -m ${DIRMODE} \
		${CURDIR}/stop ${DESTDIR}/usr/share/dict
	${INSTALL} ${INSTALL_COPY} -D -o ${BINOWN} -g ${BINGRP} -m ${DIRMODE} \
		${CURDIR}/american ${DESTDIR}/usr/share/dict
	${INSTALL} ${INSTALL_COPY} -D -o ${BINOWN} -g ${BINGRP} -m ${DIRMODE} \
		${CURDIR}/british ${DESTDIR}/usr/share/dict
	${INSTALL} ${INSTALL_COPY} -D -o ${BINOWN} -g ${BINGRP} -m ${DIRMODE} \
		${CURDIR}/special.4bsd  ${DESTDIR}/usr/share/dict/special/4bsd
	${INSTALL} ${INSTALL_COPY} -D -o ${BINOWN} -g ${BINGRP} -m ${DIRMODE} \
		${CURDIR}/special.math ${DESTDIR}/usr/share/dict/special/math
