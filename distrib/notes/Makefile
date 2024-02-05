M=amd64

OSrev=1.0
OSREV=${OSrev}

TARG=	INSTALL.${M}
SRC=	$(CURDIR)/INSTALL
DEP=	$(SRC) $(CURDIR)/mirrors $(CURDIR)/${M}/whatis $(CURDIR)/${M}/contents \
	$(CURDIR)/${M}/hardware $(CURDIR)/${M}/xfer $(CURDIR)/${M}/prep \
	$(CURDIR)/${M}/install $(CURDIR)/${M}/upgrade ${CURDIR}/${M}/features \
	$(CURDIR)/packages $(CURDIR)/m4.common

all:	$(TARG)

$(TARG): $(DEP)
	m4 -DOSREV=$(OSREV) -DOSrev=$(OSrev) -DINCLUDE=$(CURDIR)/${M} \
	-DMACHINE=${M} -Uunix $(SRC) > $@

install: ${TARG}
	install -d -m 755 /${DESTDIR}
	cp -v ${TARG} /${DESTDIR}

clean:
	rm -fv INSTALL.${M}
