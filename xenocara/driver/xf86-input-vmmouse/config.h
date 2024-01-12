/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

#include "xorg-server.h"

/* Define absolute valuator axes */
#define ABS_VALUATOR_AXES 1

/* Call conversion_proc from within the driver, as Xserver doesn't */
/* #undef CALL_CONVERSION_PROC */

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the `ioperm' function. */
/* #undef HAVE_IOPERM */

/* Define to 1 if you have the `iopl' function. */
/* #undef HAVE_IOPL */

/* Define to 1 if you have the `amd64' library (-lamd64). */
/* #undef HAVE_LIBAMD64 */

/* Define to 1 if you have the `i386' library (-li386). */
/* #undef HAVE_LIBI386 */

/* Has libudev installed */
/* #undef HAVE_LIBUDEV */

/* Define to 1 if you have the `x86_64' library (-lx86_64). */
/* #undef HAVE_LIBX86_64 */

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

/* Has version 1.1.0 or greater of the Xserver */
#define HAVE_XORG_SERVER_1_1_0 1

/* Has version 1.5.0 or greater of the Xserver */
#define HAVE_XORG_SERVER_1_5_0 1

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#define LT_OBJDIR ".libs/"

/* Do not include built-in mouse module fallback */
#define NO_MOUSE_MODULE 1

/* Name of package */
#define PACKAGE "xf86-input-vmmouse"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "https://gitlab.freedesktop.org/xorg/driver/xf86-input-vmmouse/issues"

/* Define to the full name of this package. */
#define PACKAGE_NAME "xf86-input-vmmouse"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "xf86-input-vmmouse 13.2.0"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "xf86-input-vmmouse"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "13.2.0"

/* Major version of this package */
#define PACKAGE_VERSION_MAJOR 13

/* Minor version of this package */
#define PACKAGE_VERSION_MINOR 2

/* Patch version of this package */
#define PACKAGE_VERSION_PATCHLEVEL 0

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* BSD /dev/io */
/* #undef USE_DEV_IO */

/* BSD i386 iopl */
/* #undef USE_I386_IOPL */

/* BSD X86_64 iopl */
/* #undef USE_X86_64_IOPL */

/* Version number of package */
#define VERSION "13.2.0"

/* Building for BSD flavour */
#define VMMOUSE_OS_BSD 1

/* Building for iopl / ioperm capable OS */
/* #undef VMMOUSE_OS_GENERIC */

/* Building for Solaris flavour */
/* #undef VMMOUSE_OS_SOLARIS */
