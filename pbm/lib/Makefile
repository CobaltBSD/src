LIB = pbm
HDRS=util/pm_c_util.h util/mallocvar.h pm_config.h util/shhopt.h pam.h pm.h pnm.h ppm.h pgm.h pbm.h ppmcmap.h util/nstring.h pm_system.h pammap.h colorname.h ppmdfont.h util/bitreverse.h pm_gamma.h dithers.h pamdraw.h util/bitarith.h util/token.h util/io.h util/matrix.h ppmdraw.h lum.h pbmfont.h util/bitio.h version.h util/filename.h
HDRPREFIX=pbm

SHLIB_MAJOR = 0
SHLIB_MINOR = 0

CFLAGS += -Iutil
LIBS = -lm

CLEANFILES+=standardppmdfont.c

OBJS = \
      colorname.o \
      fileio.o \
      libpam.o \
      libpamcolor.o \
      libpamd.o \
      libpammap.o \
      libpamn.o \
      libpamread.o \
      libpamwrite.o \
      libpbm1.o \
      libpbm2.o \
      libpbm3.o \
      libpbmfont.o \
      libpgm1.o \
      libpgm2.o \
      libpm.o \
      libpnm1.o \
      libpnm2.o \
      libpnm3.o \
      libppm1.o \
      libppm2.o \
      libppmcmap.o \
      libppmcolor.o \
      libppmd.o \
      libppmfloyd.o \
      libppmfuzzy.o \
      libsystem.o \
      path.o \
      pmfileio.o \
      ppmdfont.o \
      standardppmdfont.o \
      util/shhopt.o \
      util/nstring.o \
      util/vasprintf.o \
      util/mallocvar.o \
      util/token.o \
      util/filename.o \
      util/io.o \
      util/matrix.o \
      util/bitio.o

include cobalt.lib.mk

# standardppmdfont.c has a circular dependency on pbm
standardppmdfont.c:
	ppmdcfont <standard.ppmdfont >$@
