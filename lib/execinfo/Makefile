SHLIB_MAJOR=3
SHLIB_MINOR=0
LIB=	execinfo
LIBS=	-lm

CFLAGS+=	-fpic -DPIC -O2 -pipe -fno-strict-aliasing -std=gnu99 -fstack-protector

OBJS=	stacktraverse.o execinfo.o
HDRS=	execinfo.h

#includes:
#	@cd ${.CURDIR}; for i in ${HDRS}; do \
#		j="cmp -s $$i ${DESTDIR}/usr/include/$$i || \
#		    ${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} -m 444 \
#	            $$i ${DESTDIR}/usr/include"; \
#	        echo $$j; \
#	        eval "$$j"; \
#	done

include cobalt.lib.mk
