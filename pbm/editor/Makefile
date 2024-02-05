PROGS=pamaddnoise pambackground pamcomp pamcut pamdice pamditherbw pamedge pamenlarge pamfunc pammasksharpen pamperspective pamrecolor pamrubber pamscale pamstretch pamthreshold pamundice pamwipeout pbmclean pbmmask pbmpscale pbmreduce pgmdeshadow pgmenhance pgmmedian pnmalias pnmcat pnmconvol pnmcrop pnmgamma pnmhisteq pnminvert pnmmontage pnmnlfilt pnmnorm pnmpad pnmpaste pnmremap pnmrotate pnmscale pnmshear pnmsmooth pnmstitch pnmtile ppmbrighten ppmchange ppmcolormask ppmdim ppmdist ppmdither ppmdraw ppmflash ppmlabel ppmmix specialty/pamdeinterlace specialty/pammixinterlace specialty/pamoil specialty/pampaintspill specialty/pampop9 specialty/pbmlife specialty/pgmabel specialty/pgmbentley specialty/pgmmorphconv specialty/pnmindex specialty/pnmmercator specialty/ppm3d specialty/ppmglobe specialty/ppmrelief specialty/ppmshift specialty/ppmspread specialty/ppmtv
SCRIPTS=pnmmargin

all: ${PROGS}
	$(MAKE) -C pamflip

.c:
	$(CC) -lpbm -lm $< -o $@

clean:
	rm -fv ${PROGS}
	$(MAKE) -C pamflip clean

install: ${PROGS}
	for P in ${PROGS} ${SCRIPTS}; do \
		$(INSTALL) -D -c -s \
			-o root -g bin \
			-m 555 $$P ${DESTDIR}/usr/bin/$$(basename $$P); \
	done
	$(MAKE) -C pamflip install
