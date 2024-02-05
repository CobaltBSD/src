INSTALL_COPY = -c
SHAREMODE=444

X11BASE ?=		/usr/X11R6

DIRMODE=755

LIBDIR?= /usr/lib

BINOWN ?= root
BINGRP ?= bin

XSRCDIR = /usr/src/xenocara
CONFIG_SITE=	${XSRCDIR}/etc/config.site

INSTALL_DATA = \
	${INSTALL} ${INSTALL_COPY} -D -o ${BINOWN} -g ${BINGRP} -m ${SHAREMODE}

PKG_CONFIG_LIBDIR=	/usr/lib/pkgconfig:${X11BASE}/lib/pkgconfig

XENOCARA_PATH?=	/bin:/sbin:/usr/bin:/usr/sbin:/usr/X11R6/bin

CONFIGURE_ARGS+=

CLEANFILES+=config.status

CONFIGURE_ENV=	PKG_CONFIG_LIBDIR="$(PKG_CONFIG_LIBDIR)" \
		CONFIG_SITE=$(CONFIG_SITE) \
		CC="$(CC)" \
		CFLAGS="$(CFLAGS:C/ *$//)" \
		CXX="$(CXX)" \
		CXXFLAGS="$(CXXFLAGS:C/ *$//)" \
		AR_FLAGS="cruD" \
		MAKE="${MAKE}"

all: config.status
	$(MAKE)

clean:
	$(MAKE) distclean
	rm -fv ${CLEANFILES}

install:
	$(MAKE) DESTDIR=${DESTDIR} install

config.status:
	${CONFIGURE_ENV} PATH=$(XENOCARA_PATH) \
		exec sh ${CURDIR}/configure --prefix=${X11BASE} \
		--sysconfdir=/etc \
		--mandir=${X11BASE}/man \
		${CONFIGURE_ARGS}
