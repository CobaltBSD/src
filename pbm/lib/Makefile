LIB = pbm

SHLIB_MAJOR = 0
SHLIB_MINOR = 0

CFLAGS += -Iutil
LDADD = -lm

SRCS = \
      colorname.c \
      fileio.c \
      libpam.c \
      libpamcolor.c \
      libpamd.c \
      libpammap.c \
      libpamn.c \
      libpamread.c \
      libpamwrite.c \
      libpbm1.c \
      libpbm2.c \
      libpbm3.c \
      libpbmfont.c \
      libpgm1.c \
      libpgm2.c \
      libpm.c \
      libpnm1.c \
      libpnm2.c \
      libpnm3.c \
      libppm1.c \
      libppm2.c \
      libppmcmap.c \
      libppmcolor.c \
      libppmd.c \
      libppmfloyd.c \
      libppmfuzzy.c \
      libsystem.c \
      path.c \
      pmfileio.c \
      ppmdfont.c \
      standardppmdfont.c \
      util/shhopt.c \
      util/nstring.c \
      util/vasprintf.c \
      util/mallocvar.c \
      util/token.c \
      util/filename.c \
      util/io.c \
      util/matrix.c

#all:
#	cc -shared -Iutil libpam.c libpamcolor.c libpamd.c libpammap.c libpamn.c libpamread.c libpamwrite.c libpbm1.c libpbm2.c libpbm3.c libpbmfont.c libpgm1.c libpgm2.c libpm.c libpnm1.c libpnm2.c libpnm3.c libppm1.c libppm2.c libppmcmap.c libppmcolor.c libppmd.c libppmfloyd.c libppmfuzzy.c libsystem.c path.c pmfileio.c ppmdfont.c standardppmdfont.c util/shhopt.c util/nstring.c util/vasprintf.c util/mallocvar.c util/token.c util/filename.c -lm -o libnetpbm.so -Wl,-soname,libpbm.so.0.0
#	ln -sf libpbm.so libpbm.so.0.0

#standardppmdfont.c:
#	ppmdcfont <standard.ppmdfont >$@

.include <bsd.lib.mk>
