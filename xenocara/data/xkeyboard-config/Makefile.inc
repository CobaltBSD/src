XKC_TOP?=	../../..
XKB_DIR=	${CURDIR}/${XKC_TOP}/dist/xkeyboard-config
XKB_BASE=	${DESTDIR}${X11BASE}/share/X11/xkb

INSTALL_DIR=	${INSTALL} -d -o root -g wheel -m ${DIRMODE}

install:
	${INSTALL_DIR} ${XKB_BASE}/${XKB_SUBDIR}
	for f in ${DATA}; do \
		echo ${INSTALL_DATA} ${XKB_DIR}/${XKB_SUBDIR}/$$f ${XKB_BASE}/${XKB_SUBDIR}/$$f; \
		${INSTALL_DATA} ${XKB_DIR}/${XKB_SUBDIR}/$$f ${XKB_BASE}/${XKB_SUBDIR}/$$f; \
	done
