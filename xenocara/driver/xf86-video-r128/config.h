/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

#include "xorg-server.h"

/* Define to 1 if you have the <byteswap.h> header file. */
/* #undef HAVE_BYTESWAP_H */

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdio.h> header file. */
#define HAVE_STDIO_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the <xaa.h> header file. */
/* #undef HAVE_XAA_H */

/* xextproto 7.1 available */
#define HAVE_XEXTPROTO_71 1

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#define LT_OBJDIR ".libs/"

/* Name of package */
#define PACKAGE "xf86-video-r128"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "https://gitlab.freedesktop.org/xorg/driver/xf86-video-r128/-/issues"

/* Define to the full name of this package. */
#define PACKAGE_NAME "xf86-video-r128"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "xf86-video-r128 6.12.1"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "xf86-video-r128"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "6.12.1"

/* Major version of this package */
#define PACKAGE_VERSION_MAJOR 6

/* Minor version of this package */
#define PACKAGE_VERSION_MINOR 12

/* Patch version of this package */
#define PACKAGE_VERSION_PATCHLEVEL 1

/* Enable DRI driver support */
#define R128DRI 1

/* Enable developmental DRI driver support */
#define R128DRI_DEVEL 1

/* Define to 1 if all of the C90 standard headers exist (not just the ones
   required in a freestanding environment). This macro is provided for
   backward compatibility; new code need not use it. */
#define STDC_HEADERS 1

/* Build support for Exa */
#define USE_EXA 1

/* Define to use byteswap macros from <sys/endian.h> */
#define USE_SYS_ENDIAN_H 1

/* Version number of package */
#define VERSION "6.12.1"

/* Define to 16-bit byteswap macro */
#define bswap_16 __swap16

/* Define to 32-bit byteswap macro */
#define bswap_32 __swap32

/* Define to 64-bit byteswap macro */
#define bswap_64 __swap64
