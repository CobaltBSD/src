SRCS=	fortunes startrek zippy recipes
BLDS=	fortunes.dat startrek.dat zippy.dat \
	recipes.dat

# THE THREE LINES
SRCS+=	fortunes-o limerick
BLDS+=	fortunes-o.dat limerick.dat

STRFILE=../strfile/strfile

all: ${BLDS}

${STRFILE}:
	$(MAKE) -C $(dir $@)

install: ${SRCS} ${BLDS}
	(cd ${CURDIR} && ${INSTALL} ${INSTALL_COPY} -d -o root -g bin -m 444 \
	    ${DESTDIR}/usr/share/games/fortune)
	${INSTALL} ${INSTALL_COPY} -o root -g bin -m 444 \
	    ${SRCS} ${DESTDIR}/usr/share/games/fortune
	${INSTALL} ${INSTALL_COPY} -o root -g bin -m 444 ${BLDS} \
	    ${DESTDIR}/usr/share/games/fortune

fortunes.dat limerick.dat startrek.dat zippy.dat recipes.dat:
	${STRFILE} -s ${CURDIR}/$(basename $@) $@

fortunes-o.dat: ${STRFILE}
	${STRFILE} -sx fortunes-o $@

clean:
	rm -fv *.dat
