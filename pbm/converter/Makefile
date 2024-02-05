PROGS=bmptopnm giftopnm hdifftopam jpegtopnm pamtogif pamtohdiff pamtohtmltbl pamtopam pamtopnm pamtotga pamtotga pamtowinicon pbmtopgm pgmtopbm pgmtoppm pngtopam pnmtojpeg pnmtopng ppmtopgm winicontopam pgmtopgm pbmtoxbm xbmtopbm ppmtoascii ppmtobmp ppmtogif ppmtoppm ppmtorgb3 ppmtowinicon ppmtoxpm rgb3toppm tgatoppm winicontoppm xpmtoppm pamtopng
OBJS=exif.o jpegdatasource.o pngx.o pngtxt.o

# Including PROGS here may break parallel compilation
all: ${OBJS}
	for P in ${PROGS}; do \
		$(MAKE) $$P; \
	done

${OBJS}:
	$(CC) -c ${@:.o=.c}

.c:
	$(CC) ${OBJS} -lpbm -lm -ljpeg -lpng $< -o $@

clean:
	rm -fv ${PROGS} ${OBJS}

install: ${OBJS}
	for P in ${PROGS}; do \
		$(MAKE) $$P; \
		$(INSTALL) -D -c -s \
			-o root -g bin \
			-m 555 $$P ${DESTDIR}/usr/bin/$$P; \
	done
