SCRIPT=	winhostname.sh

realinstall:
	${INSTALL} -D ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${.CURDIR}/${SCRIPT} ${DESTDIR}${BINDIR}/winhostname

.include <bsd.prog.mk>
