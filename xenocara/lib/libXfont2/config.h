/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Define to 1 if `struct sockaddr_in' has a `sin_len' member */
#define BSD44SOCKETS 1

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 if you have the <endian.h> header file. */
#define HAVE_ENDIAN_H 1

/* Define to 1 if you have the <err.h> header file. */
#define HAVE_ERR_H 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Has libbsd */
/* #undef HAVE_LIBBSD */

/* Define to 1 if you have the `ws2_32' library (-lws2_32). */
/* #undef HAVE_LIBWS2_32 */

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `poll' function. */
#define HAVE_POLL 1

/* Define to 1 if you have the <poll.h> header file. */
#define HAVE_POLL_H 1

/* Define to 1 if you have the `readlink' function. */
#define HAVE_READLINK 1

/* Define to 1 if you have the `reallocarray' function. */
#define HAVE_REALLOCARRAY 1

/* Define to 1 if you have the `realpath' function. */
#define HAVE_REALPATH 1

/* Define to 1 if the system has the type `socklen_t'. */
#define HAVE_SOCKLEN_T 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the `strcasecmp' function. */
#define HAVE_STRCASECMP 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strlcat' function. */
#define HAVE_STRLCAT 1

/* Define to 1 if you have the `strlcpy' function. */
#define HAVE_STRLCPY 1

/* Define to 1 if you have the <sys/poll.h> header file. */
#define HAVE_SYS_POLL_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Support IPv6 for TCP connections */
#define IPv6 1

/* Support os-specific local connections */
/* #undef LOCALCONN */

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#define LT_OBJDIR ".libs/"

/* Name of package */
#define PACKAGE "libXfont2"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "https://gitlab.freedesktop.org/xorg/lib/libxfont/-/issues"

/* Define to the full name of this package. */
#define PACKAGE_NAME "libXfont2"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "libXfont2 2.0.6"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "libXfont2"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "2.0.6"

/* Major version of this package */
#define PACKAGE_VERSION_MAJOR 2

/* Minor version of this package */
#define PACKAGE_VERSION_MINOR 0

/* Patch version of this package */
#define PACKAGE_VERSION_PATCHLEVEL 6

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Support TCP socket connections */
#define TCPCONN 1

/* Support UNIX socket connections */
#define UNIXCONN 1

/* Enable extensions on AIX 3, Interix.  */
#ifndef _ALL_SOURCE
# define _ALL_SOURCE 1
#endif
/* Enable GNU extensions on systems that have them.  */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif
/* Enable threading extensions on Solaris.  */
#ifndef _POSIX_PTHREAD_SEMANTICS
# define _POSIX_PTHREAD_SEMANTICS 1
#endif
/* Enable extensions on HP NonStop.  */
#ifndef _TANDEM_SOURCE
# define _TANDEM_SOURCE 1
#endif
/* Enable general extensions on Solaris.  */
#ifndef __EXTENSIONS__
# define __EXTENSIONS__ 1
#endif


/* Version number of package */
#define VERSION "2.0.6"

/* Support bdf format bitmap font files */
#define XFONT_BDFFORMAT 1

/* Support bitmap font files */
#define XFONT_BITMAP 1

/* Support built-in fonts */
#define XFONT_BUILTINS 1

/* Support the X Font Services Protocol */
/* #undef XFONT_FC */

/* Support fonts in files */
#define XFONT_FONTFILE 1

/* Support FreeType rasterizer for nearly all font file formats */
#define XFONT_FREETYPE 1

/* Support pcf format bitmap font files */
#define XFONT_PCFFORMAT 1

/* Support snf format bitmap font files */
/* #undef XFONT_SNFFORMAT */

/* Support bzip2 for bitmap fonts */
/* #undef X_BZIP2_FONT_COMPRESSION */

/* Support gzip for bitmap fonts */
#define X_GZIP_FONT_COMPRESSION 1

/* Define to 1 if on MINIX. */
/* #undef _MINIX */

/* Define to 2 if the system does not provide POSIX.1 features except with
   this defined. */
/* #undef _POSIX_1_SOURCE */

/* Define to 1 if you need to in order for `stat' and other things to work. */
/* #undef _POSIX_SOURCE */

/* Defined if needed to expose struct msghdr.msg_control */
/* #undef _XOPEN_SOURCE */
