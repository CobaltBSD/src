/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

#include "xorg-server.h"

/* Avoid PIO and use MMIO for atimisc. */
/* #undef AVOID_CPIO */

/* Do not build DGA support. */
/* #undef AVOID_DGA */

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

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
#define PACKAGE "xf86-video-mach64"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "https://gitlab.freedesktop.org/xorg/driver/xf86-video-mach64/issues"

/* Define to the full name of this package. */
#define PACKAGE_NAME "xf86-video-mach64"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "xf86-video-mach64 6.9.7"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "xf86-video-mach64"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "6.9.7"

/* Major version of this package */
#define PACKAGE_VERSION_MAJOR 6

/* Minor version of this package */
#define PACKAGE_VERSION_MINOR 9

/* Patch version of this package */
#define PACKAGE_VERSION_PATCHLEVEL 7

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Build TV-Out support for atimisc. */
/* #undef TV_OUT */

/* Build support for Exa */
#define USE_EXA 1

/* Build support for XAA */
/* #undef USE_XAA */

/* Version number of package */
#define VERSION "6.9.7"

/* Enable DRI driver support */
#define XF86DRI 1

/* Enable developmental DRI driver support */
#define XF86DRI_DEVEL 1
