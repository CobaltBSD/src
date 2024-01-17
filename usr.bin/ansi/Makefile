SCRIPT=	ansi.sh

realinstall:
	${INSTALL} -D ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${.CURDIR}/${SCRIPT} ${DESTDIR}${BINDIR}/ansi

.include <bsd.prog.mk>
