#include cobalt.xconf.mk

#LOCALAPPD=/usr/local/lib/X11/app-defaults
#LOCALAPPX=/usr/local/lib/X11
#REALAPPD=/etc/X11/app-defaults

#SUBDIR= proto font/util data/bitmaps lib app data \
#	xserver driver util doc
SUBDIR=	proto \
	xserver util

#beforeinstall beforebuild:
#	cd util/macros && exec ${MAKE} -f Makefile.bsd-wrapper install

#afterinstall afterbuild:
#	exec ${MAKE} fix-appd
#	/usr/sbin/makewhatis -Qv ${DESTDIR}/usr/X11R6/man
#	chown root:wheel ${DESTDIR}/usr/X11R6/man/mandoc.db
#	chmod 644 ${DESTDIR}/usr/X11R6/man/mandoc.db
#	touch ${DESTDIR}/var/sysmerge/xetcsum
#	cd ${DESTDIR}/ && \
#		sort ${.CURDIR}/distrib/sets/lists/xetc/{mi,md.${MACHINE}} | \
#		xargs sha256 -h ${DESTDIR}/var/sysmerge/xetcsum || true
#	chown root:wheel ${DESTDIR}/var/sysmerge/xetcsum
#	chmod 644 ${DESTDIR}/var/sysmerge/xetcsum
#	cd distrib/sets && exec ${MAKE}

#fix-appd:
	# Make sure /usr/local/lib/X11/app-defaults is a link
#	if [ ! -L $(DESTDIR)${LOCALAPPD} ]; then \
#	    if [ -d $(DESTDIR)${LOCALAPPD} ]; then \
#		mv $(DESTDIR)${LOCALAPPD}/* $(DESTDIR)${REALAPPD} || true; \
#		rmdir $(DESTDIR)${LOCALAPPD}; \
#	    fi; \
#	    mkdir -p ${DESTDIR}${LOCALAPPX}; \
#	    ln -s ${REALAPPD} ${DESTDIR}${LOCALAPPD}; \
#	    chown -h root:wheel ${DESTDIR}${LOCALAPPD}; \
#	fi

#font-cache:
#	cd font/alias && exec ${MAKE} -f Makefile.bsd-wrapper afterinstall

include cobalt.xorg.subdir.mk
