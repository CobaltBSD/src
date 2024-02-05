PROGS=pamfile pammosaicknit pamsharpmap pamsharpness pamslice pamsumm pamtilt pbmminkowski pgmhist pgmminkowski pgmtexture pnmhistmap pnmpsnr ppmhist

all: ${PROGS}

.c:
	$(CC) -lpbm -lm $< -o $@

clean:
	rm -fv ${PROGS}

install: ${PROGS}
	for P in ${PROGS}; do \
		$(INSTALL) -D -c -s \
			-o root -g bin \
			-m 555 $$P ${DESTDIR}/usr/bin/$$P; \
	done
