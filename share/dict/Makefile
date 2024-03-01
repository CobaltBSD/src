# Missing: connectives, words

FILES=	README propernames web2 web2a
#LINKS=	${BINDIR}/dict/web2 ${BINDIR}/dict/words

all clean cleandir tags:

install:
	for I in ${FILES}; do \
		$(INSTALL) -D -c -o root -g bin -m 444 $$I ${DESTDIR}/usr/share/dict/$$I; \
	done
