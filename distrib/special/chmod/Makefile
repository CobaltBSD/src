#	$OpenBSD: Makefile,v 1.2 2023/08/14 08:56:20 kn Exp $

PROG=	chmod
CFLAGS+=-DSUPPORT_DOT
LINKS=	${BINDIR}/chmod ${BINDIR}/chgrp \
	${BINDIR}/chmod /usr/sbin/chown

# XXX compatibility
afterinstall:
	(cd ${DESTDIR}/usr/sbin; \
	    ln -sf ../../sbin/chown .; \
	    ln -sf ../../bin/chgrp .)
	(cd ${DESTDIR}/usr/bin; \
	    ln -sf ../../bin/chmod chflags)


.PATH:  ${.CURDIR}/../../../usr.bin/chmod
.include <bsd.prog.mk>
