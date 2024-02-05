PROGS=pamarith pambayer pamchannel pamdepth pamendian pamexec pamfix pampick pamsplit pamstack pamvalidate pnmcolormap ppmdcfont ppmddumpfont

all: ${PROGS}
	$(MAKE) -C pamx

.c:
	$(CC) -lpbm -lm $< -o $@

clean:
	rm -fv ${PROGS}
	$(MAKE) -C pamx clean

install: ${PROGS}
	for P in ${PROGS}; do \
		$(INSTALL) -D -c -s \
			-o root -g bin \
			-m 555 $$P ${DESTDIR}/usr/bin/$$P; \
	done
	$(MAKE) -C pamx install
