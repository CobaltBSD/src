DB = /usr/lib/locate/src.db

OSrev=1.0

BINOWN=root
BINGRP=bin

all:

install: makedb

makedb:
	install -d -m 755 /${DESTDIR}$(dir ${DB})
	/bin/sh ${CURDIR}/makelocatedb ${OSrev} >${DESTDIR}${DB}
	chown ${BINOWN}:${BINGRP} ${DESTDIR}${DB}
	chmod 644 ${DESTDIR}${DB}
