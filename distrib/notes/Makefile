M=amd64

OSrev=1.0
OSREV=${OSrev}

TARG=	INSTALL.${M}
SRC=	$(CURDIR)/INSTALL
DEP=	$(SRC) $(CURDIR)/whatis $(CURDIR)/contents \
	$(CURDIR)/hardware $(CURDIR)/xfer $(CURDIR)/prep \
	$(CURDIR)/install $(CURDIR)/upgrade ${CURDIR}/features \
	$(CURDIR)/packages $(CURDIR)/m4.common

all:	$(TARG)

$(TARG): $(DEP)
	m4 -DOSREV=$(OSREV) -DOSrev=$(OSrev) -DINCLUDE=$(CURDIR) \
	-DMACHINE=${M} -Uunix $(SRC) > $@

install: ${TARG}
	install -d -m 755 /${DESTDIR}
	cp -v ${TARG} /${DESTDIR}

clean:
	rm -fv INSTALL.${M}
