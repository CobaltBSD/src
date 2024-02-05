PROG=	chmod
MAN=	chmod.1 chgrp.1 chown.8 chflags.1
SYMLINKS=	${BINDIR}/chgrp \
		${SBINDIR}/chown

# XXX compatibility
#afterinstall:
#	(cd ${DESTDIR}/usr/sbin && \
#	    ln -sf chown . && \
#	    ln -sf ../bin/chgrp . && \
#	    chown -h ${BINOWN}:${BINGRP} chown chgrp)
#	(cd ${DESTDIR}/usr/bin && \
#	    ln -sf bin/chmod chflags && \
#	    chown -h ${BINOWN}:${BINGRP} chflags)

include cobalt.prog.mk
