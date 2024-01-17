SCRIPT=	pkg.sh

realinstall:
	${INSTALL} -D ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${.CURDIR}/${SCRIPT} ${DESTDIR}${BINDIR}/pkg

.include <bsd.prog.mk>
