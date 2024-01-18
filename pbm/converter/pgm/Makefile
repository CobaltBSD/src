ifeq ($(SRCDIR)x,x)
  SRCDIR = $(CURDIR)/../..
  BUILDDIR = $(SRCDIR)
endif
SUBDIR = converter/pgm
VPATH=.:$(SRCDIR)/$(SUBDIR)

include $(BUILDDIR)/config.mk

PORTBINARIES =	asciitopgm bioradtopgm fstopgm hipstopgm \
		lispmtopgm pgmtofs pgmtolispm pgmtopgm pgmtosbig pgmtost4 \
	        psidtopgm spottopgm sbigtopgm st4topgm
MATHBINARIES =	rawtopgm
BINARIES =	$(PORTBINARIES) $(MATHBINARIES)

OBJECTS = $(BINARIES:%=%.o)
MERGEBINARIES = $(BINARIES)
MERGE_OBJECTS = $(MERGEBINARIES:%=%.o2)

.PHONY: all
all: $(BINARIES)

include $(SRCDIR)/common.mk
