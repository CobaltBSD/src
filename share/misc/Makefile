FILES=	\
	license.template mdoc.template \
	scsi_modes usb_hid_usages

all:
	$(MAKE) -C pcvtfonts

install:
	$(MAKE) -C pcvtfonts install
	for I in ${FILES}; do \
		$(INSTALL) -D -c $$I ${DESTDIR}/usr/share/misc/$$I; \
	done

clean:
	$(MAKE) -C pcvtfonts clean

#realinstall:
#	cd ${.CURDIR}; install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${FILES} \
#	    ${DESTDIR}${BINDIR}/misc
