PROGS=pamcrater pamgauss pamgradient pamseq pamshadedrelief pbmmake pbmpage pbmtext pgmkernel pgmmake pgmnoise pgmramp ppmcie ppmforge ppmmake ppmpat ppmrough ppmwheel

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
