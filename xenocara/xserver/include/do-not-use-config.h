/* include/do-not-use-config.h.  Generated from do-not-use-config.h.in by configure.  */
/* include/do-not-use-config.h.in.  Generated from configure.ac by autoheader.  */

/* Define if building universal (internal helper macro) */
/* #undef AC_APPLE_UNIVERSAL_BUILD */

/* Default base font path */
#define BASE_FONT_PATH "/usr/X11R6/lib/X11/fonts"

/* Support BigRequests extension */
#define BIGREQS 1

/* Define to 1 if `struct sockaddr_in' has a `sin_len' member */
#define BSD44SOCKETS 1

/* Builder address */
#define BUILDERADDR "xorg@lists.freedesktop.org"

/* Builder string */
#define BUILDERSTRING ""

/* Prefix to use for bundle identifiers */
#define BUNDLE_ID_PREFIX ""

/* Include busfault OS API */
#define BUSFAULT 1

/* Support client ID tracking */
#define CLIENTIDS 1

/* Default font path */
#define COMPILEDDEFAULTFONTPATH "/usr/X11R6/lib/X11/fonts/misc/,/usr/X11R6/lib/X11/fonts/TTF/,/usr/X11R6/lib/X11/fonts/OTF/,/usr/X11R6/lib/X11/fonts/Type1/,/usr/X11R6/lib/X11/fonts/100dpi/,/usr/X11R6/lib/X11/fonts/75dpi/"

/* Support Composite Extension */
#define COMPOSITE 1

/* Use the HAL hotplug API */
/* #undef CONFIG_HAL */

/* Use kevent for kms enumeration */
#define CONFIG_KEVENT_KMS 1

/* Use libudev for input hotplug */
/* #undef CONFIG_UDEV */

/* Use libudev for kms enumeration */
/* #undef CONFIG_UDEV_KMS */

/* Use wscons for input auto configuration */
#define CONFIG_WSCONS 1

/* System is BSD-like */
#define CSRG_BASED 1

/* Simple debug messages */
/* #undef CYGDEBUG */

/* Debug window manager */
/* #undef CYGMULTIWINDOW_DEBUG */

/* Debug messages for window handling */
/* #undef CYGWINDOWING_DEBUG */

/* Support Damage extension */
#define DAMAGE 1

/* Support DBE extension */
#define DBE 1

/* Use ddxBeforeReset */
/* #undef DDXBEFORERESET */

/* Use OsVendorVErrorF */
/* #undef DDXOSVERRORF */

/* Enable debugging code */
/* #undef DEBUG */

/* Default library install path */
#define DEFAULT_LIBRARY_PATH "/usr/X11R6/lib"

/* Default log location */
#define DEFAULT_LOGDIR "/var/log"

/* Default logfile prefix */
#define DEFAULT_LOGPREFIX "Xorg."

/* Default module search path */
#define DEFAULT_MODULE_PATH "/usr/X11R6/lib/modules"

/* Default XDG_DATA dir under HOME */
#define DEFAULT_XDG_DATA_HOME ".local/share"

/* Default log dir under XDG_DATA_HOME */
#define DEFAULT_XDG_DATA_HOME_LOGDIR "xorg"

/* Support DGA extension */
#define DGA 1

/* Support DPMS extension */
#define DPMSExtension 1

/* Build DRI2 extension */
#define DRI2 1

/* Build DRI3 extension */
#define DRI3 1

/* Default DRI driver path */
#define DRI_DRIVER_PATH "/usr/X11R6/lib/modules/dri"

/* Fallback input driver */
#define FALLBACK_INPUT_DRIVER ""

/* Have gbm_bo_create_with_modifiers */
#define GBM_BO_WITH_MODIFIERS 1

/* Build glamor */
#define GLAMOR 1

/* Have GLAMOR_HAS_EGL_QUERY_DMABUF */
#define GLAMOR_HAS_EGL_QUERY_DMABUF 1

/* Have GLAMOR_HAS_EGL_QUERY_DRIVER */
#define GLAMOR_HAS_EGL_QUERY_DRIVER 1

/* Build glamor with GBM-based EGL support */
#define GLAMOR_HAS_GBM 1

/* Have GBM_BO_USE_LINEAR */
/* #undef GLAMOR_HAS_GBM_LINEAR */

/* Build GLX extension */
#define GLXEXT 1

/* Support XDM-AUTH*-1 */
/* #undef HASXDMAUTH */

/* System has /dev/xf86 aperture driver */
#define HAS_APERTURE_DRV 1

/* Cygwin has /dev/windows for signaling new win32 messages */
/* #undef HAS_DEVWINDOWS */

/* Support SHM */
#define HAS_SHM 1

/* Use Windows sockets */
/* #undef HAS_WINSOCK */

/* Define to 1 if you have the `arc4random_buf' function. */
#define HAVE_ARC4RANDOM_BUF 1

/* Define to 1 if you have the `authdes_create' function. */
/* #undef HAVE_AUTHDES_CREATE */

/* Define to 1 if you have the `authdes_seccreate' function. */
/* #undef HAVE_AUTHDES_SECCREATE */

/* Has backtrace support */
/* #undef HAVE_BACKTRACE */

/* Define to 1 if you have the `cbrt' function. */
#define HAVE_CBRT 1

/* Define to 1 if you have the `clock_gettime' function. */
#define HAVE_CLOCK_GETTIME 1

/* Have D-Bus support */
/* #undef HAVE_DBUS */

/* Define to 1 if you have the declaration of `program_invocation_short_name',
   and to 0 if you don't. */
#define HAVE_DECL_PROGRAM_INVOCATION_SHORT_NAME 0

/* Define to 1 if you have the <dirent.h> header file, and it defines `DIR'.
   */
#define HAVE_DIRENT_H 1

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 if you have the `epoll_create1' function. */
/* #undef HAVE_EPOLL_CREATE1 */

/* Have execinfo.h */
/* #undef HAVE_EXECINFO_H */

/* Define to 1 if you have the <fcntl.h> header file. */
#define HAVE_FCNTL_H 1

/* Define to 1 if you have the <fnmatch.h> header file. */
#define HAVE_FNMATCH_H 1

/* Define to 1 if you have the `getdtablesize' function. */
#define HAVE_GETDTABLESIZE 1

/* Define to 1 if you have the `geteuid' function. */
#define HAVE_GETEUID 1

/* Define to 1 if you have the `getifaddrs' function. */
#define HAVE_GETIFADDRS 1

/* Define to 1 if you have the `getpeereid' function. */
#define HAVE_GETPEEREID 1

/* Define to 1 if you have the `getpeerucred' function. */
/* #undef HAVE_GETPEERUCRED */

/* Define to 1 if you have the `getprogname' function. */
#define HAVE_GETPROGNAME 1

/* Define to 1 if you have the `getresuid' function. */
#define HAVE_GETRESUID 1

/* Define to 1 if you have the `getuid' function. */
#define HAVE_GETUID 1

/* Define to 1 if you have the `getzoneid' function. */
/* #undef HAVE_GETZONEID */

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the `isastream' function. */
/* #undef HAVE_ISASTREAM */

/* Define to 1 if you have the `issetugid' function. */
#define HAVE_ISSETUGID 1

/* Define to 1 if you have the `audit' library (-laudit). */
/* #undef HAVE_LIBAUDIT */

/* Define to 1 if you have the <libaudit.h> header file. */
/* #undef HAVE_LIBAUDIT_H */

/* Define to 1 if you have the `m' library (-lm). */
#define HAVE_LIBM 1

/* Have libunwind support */
/* #undef HAVE_LIBUNWIND */

/* Define to 1 if you have the `ws2_32' library (-lws2_32). */
/* #undef HAVE_LIBWS2_32 */

/* Define to 1 if you have the <linux/agpgart.h> header file. */
/* #undef HAVE_LINUX_AGPGART_H */

/* Define to 1 if you have the <linux/apm_bios.h> header file. */
/* #undef HAVE_LINUX_APM_BIOS_H */

/* Define to 1 if you have the <linux/fb.h> header file. */
/* #undef HAVE_LINUX_FB_H */

/* Define to 1 if you have the `memfd_create' function. */
/* #undef HAVE_MEMFD_CREATE */

/* Define to 1 if you have the <minix/config.h> header file. */
/* #undef HAVE_MINIX_CONFIG_H */

/* Define to 1 if you have the `mkostemp' function. */
#define HAVE_MKOSTEMP 1

/* Define to 1 if you have the `mmap' function. */
#define HAVE_MMAP 1

/* Define to 1 if you have the <ndir.h> header file, and it defines `DIR'. */
/* #undef HAVE_NDIR_H */

/* Define to 1 if you have the `poll' function. */
#define HAVE_POLL 1

/* Define to 1 if you have the `posix_fallocate' function. */
/* #undef HAVE_POSIX_FALLOCATE */

/* Define if you have POSIX threads libraries and header files. */
#define HAVE_PTHREAD 1

/* Have PTHREAD_PRIO_INHERIT. */
#define HAVE_PTHREAD_PRIO_INHERIT 1

/* Have function pthread_setname_np(const char*) */
/* #undef HAVE_PTHREAD_SETNAME_NP_WITHOUT_TID */

/* Have function pthread_setname_np(pthread_t, const char*) */
/* #undef HAVE_PTHREAD_SETNAME_NP_WITH_TID */

/* Define to 1 if you have the `reallocarray' function. */
#define HAVE_REALLOCARRAY 1

/* Define to 1 if you have the `seteuid' function. */
#define HAVE_SETEUID 1

/* Define to 1 if you have the `setitimer' function. */
#define HAVE_SETITIMER 1

/* Use CommonCrypto SHA1 functions */
/* #undef HAVE_SHA1_IN_COMMONCRYPTO */

/* Use CryptoAPI SHA1 functions */
/* #undef HAVE_SHA1_IN_CRYPTOAPI */

/* Use libc SHA1 functions */
#define HAVE_SHA1_IN_LIBC 1

/* Use libgcrypt SHA1 functions */
/* #undef HAVE_SHA1_IN_LIBGCRYPT */

/* Use libmd SHA1 functions */
/* #undef HAVE_SHA1_IN_LIBMD */

/* Use libnettle SHA1 functions */
/* #undef HAVE_SHA1_IN_LIBNETTLE */

/* Use libsha1 for SHA1 */
/* #undef HAVE_SHA1_IN_LIBSHA1 */

/* Define to 1 if you have the `shmctl64' function. */
/* #undef HAVE_SHMCTL64 */

/* Have sigaction function */
#define HAVE_SIGACTION 1

/* Define to 1 if you have the `sigprocmask' function. */
#define HAVE_SIGPROCMASK 1

/* Define to 1 if the system has the type `socklen_t'. */
#define HAVE_SOCKLEN_T 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdio.h> header file. */
#define HAVE_STDIO_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the `strcasecmp' function. */
#define HAVE_STRCASECMP 1

/* Define to 1 if you have the `strcasestr' function. */
#define HAVE_STRCASESTR 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strlcat' function. */
#define HAVE_STRLCAT 1

/* Define to 1 if you have the `strlcpy' function. */
#define HAVE_STRLCPY 1

/* Define to 1 if you have the `strncasecmp' function. */
#define HAVE_STRNCASECMP 1

/* Define to 1 if you have the `strndup' function. */
#define HAVE_STRNDUP 1

/* Define to 1 if you have the <stropts.h> header file. */
/* #undef HAVE_STROPTS_H */

/* Define to 1 if libsystemd-daemon is available */
/* #undef HAVE_SYSTEMD_DAEMON */

/* Define to 1 if SYSV IPC is available */
#define HAVE_SYSV_IPC 1

/* Define to 1 if you have the <sys/agpgart.h> header file. */
/* #undef HAVE_SYS_AGPGART_H */

/* Define to 1 if you have the <sys/agpio.h> header file. */
/* #undef HAVE_SYS_AGPIO_H */

/* Define to 1 if you have the <sys/dir.h> header file, and it defines `DIR'.
   */
/* #undef HAVE_SYS_DIR_H */

/* Define to 1 if you have the <sys/kd.h> header file. */
/* #undef HAVE_SYS_KD_H */

/* Define to 1 if you have the <sys/linker.h> header file. */
/* #undef HAVE_SYS_LINKER_H */

/* Define to 1 if you have the <sys/mkdev.h> header file. */
/* #undef HAVE_SYS_MKDEV_H */

/* Define to 1 if you have the <sys/ndir.h> header file, and it defines `DIR'.
   */
/* #undef HAVE_SYS_NDIR_H */

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/sysmacros.h> header file. */
/* #undef HAVE_SYS_SYSMACROS_H */

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <sys/utsname.h> header file. */
#define HAVE_SYS_UTSNAME_H 1

/* Define to 1 if you have the <sys/vt.h> header file. */
/* #undef HAVE_SYS_VT_H */

/* Define to 1 if you have the `timingsafe_memcmp' function. */
#define HAVE_TIMINGSAFE_MEMCMP 1

/* Define to 1 if typeof works with your compiler. */
#define HAVE_TYPEOF 1

/* Define to 1 if you have the `udev_enumerate_add_match_tag' function. */
/* #undef HAVE_UDEV_ENUMERATE_ADD_MATCH_TAG */

/* Define to 1 if you have the `udev_monitor_filter_add_match_tag' function.
   */
/* #undef HAVE_UDEV_MONITOR_FILTER_ADD_MATCH_TAG */

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the `vasprintf' function. */
#define HAVE_VASPRINTF 1

/* Define to 1 if you have the `vsnprintf' function. */
#define HAVE_VSNPRINTF 1

/* Define to 1 if you have the `walkcontext' function. */
/* #undef HAVE_WALKCONTEXT */

/* Define to 1 if you have the <wchar.h> header file. */
#define HAVE_WCHAR_H 1

/* Have xshmfence support */
#define HAVE_XSHMFENCE 1

/* Use a separate input thread */
#define INPUTTHREAD 1

/* Support IPv6 for TCP connections */
#define IPv6 1

/* Listen on local socket */
#define LISTEN_LOCAL 1

/* Listen on TCP socket */
/* #undef LISTEN_TCP */

/* Listen on Unix socket */
#define LISTEN_UNIX 1

/* Support os-specific local connections */
/* #undef LOCALCONN */

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#define LT_OBJDIR ".libs/"

/* Support MIT-SHM extension */
#define MITSHM 1

/* Have monotonic clock from clock_gettime() */
#define MONOTONIC_CLOCK 1

/* Enable D-Bus core */
/* #undef NEED_DBUS */

/* Need XFree86 helper functions */
#define NEED_XF86_PROTOTYPES 1

/* Need XFree86 typedefs */
#define NEED_XF86_TYPES 1

/* Define to 1 if no local socket credentials interface exists */
/* #undef NO_LOCAL_CLIENT_CRED */

/* Name of package */
#define PACKAGE "xorg-server"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "https://gitlab.freedesktop.org/xorg/xserver/issues"

/* Define to the full name of this package. */
#define PACKAGE_NAME "xorg-server"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "xorg-server 21.1.9"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "xorg-server"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "21.1.9"

/* Major version of this package */
#define PACKAGE_VERSION_MAJOR 21

/* Minor version of this package */
#define PACKAGE_VERSION_MINOR 1

/* Patch version of this package */
#define PACKAGE_VERSION_PATCHLEVEL 9

/* Internal define for Xinerama */
#define PANORAMIX 1

/* System has PC console */
/* #undef PCCONS_SUPPORT */

/* Default PCI text file ID path */
#define PCI_TXT_IDS_PATH ""

/* System has PCVT console */
/* #undef PCVT_SUPPORT */

/* Support Present extension */
#define PRESENT 1

/* Overall prefix */
#define PROJECTROOT "/usr/X11R6"

/* Define to necessary symbol if this constant uses a non-standard name on
   your system. */
/* #undef PTHREAD_CREATE_JOINABLE */

/* Support RANDR extension */
#define RANDR 1

/* Make PROJECT_ROOT relative to the xserver location */
/* #undef RELOCATE_PROJECTROOT */

/* Support RENDER extension */
#define RENDER 1

/* Support X resource extension */
#define RES 1

/* Build Rootless code */
/* #undef ROOTLESS */

/* Support MIT-SCREEN-SAVER extension */
#define SCREENSAVER 1

/* Support Secure RPC ("SUN-DES-1") authentication for X11 clients */
/* #undef SECURE_RPC */

/* Server miscellaneous config path */
#define SERVER_MISC_CONFIG_PATH "/usr/X11R6/lib/xorg"

/* Support SHAPE extension */
#define SHAPE 1

/* The size of `unsigned long', as computed by sizeof. */
#define SIZEOF_UNSIGNED_LONG 8

/* Build a standalone xpbproxy */
/* #undef STANDALONE_XPBPROXY */

/* Define to 1 if all of the C90 standard headers exist (not just the ones
   required in a freestanding environment). This macro is provided for
   backward compatibility; new code need not use it. */
#define STDC_HEADERS 1

/* Where to install the Xorg binary and Xorg.wrap */
/* #undef SUID_WRAPPER_DIR */

/* Define to 1 on systems derived from System V Release 4 */
/* #undef SVR4 */

/* sysconfdir */
#define SYSCONFDIR "/etc/X11"

/* System has syscons console */
/* #undef SYSCONS_SUPPORT */

/* Enable systemd-logind integration */
/* #undef SYSTEMD_LOGIND */

/* Support TCP socket connections */
#define TCPCONN 1

/* Support UNIX socket connections */
#define UNIXCONN 1

/* NetBSD PIO alpha IO */
/* #undef USE_ALPHA_PIO */

/* BSD AMD64 iopl */
#define USE_AMD64_IOPL 1

/* BSD /dev/io */
/* #undef USE_DEV_IO */

/* BSD i386 iopl */
/* #undef USE_I386_IOPL */

/* Enable extensions on AIX 3, Interix.  */
#ifndef _ALL_SOURCE
# define _ALL_SOURCE 1
#endif
/* Enable general extensions on macOS.  */
#ifndef _DARWIN_C_SOURCE
# define _DARWIN_C_SOURCE 1
#endif
/* Enable general extensions on Solaris.  */
#ifndef __EXTENSIONS__
# define __EXTENSIONS__ 1
#endif
/* Enable GNU extensions on systems that have them.  */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif
/* Enable X/Open compliant socket functions that do not require linking
   with -lxnet on HP-UX 11.11.  */
#ifndef _HPUX_ALT_XOPEN_SOCKET_API
# define _HPUX_ALT_XOPEN_SOCKET_API 1
#endif
/* Identify the host operating system as Minix.
   This macro does not affect the system headers' behavior.
   A future release of Autoconf may stop defining this macro.  */
#ifndef _MINIX
/* # undef _MINIX */
#endif
/* Enable general extensions on NetBSD.
   Enable NetBSD compatibility extensions on Minix.  */
#ifndef _NETBSD_SOURCE
# define _NETBSD_SOURCE 1
#endif
/* Enable OpenBSD compatibility extensions on NetBSD.
   Oddly enough, this does nothing on OpenBSD.  */
#ifndef _OPENBSD_SOURCE
# define _OPENBSD_SOURCE 1
#endif
/* Define to 1 if needed for POSIX-compatible behavior.  */
#ifndef _POSIX_SOURCE
/* # undef _POSIX_SOURCE */
#endif
/* Define to 2 if needed for POSIX-compatible behavior.  */
#ifndef _POSIX_1_SOURCE
/* # undef _POSIX_1_SOURCE */
#endif
/* Enable POSIX-compatible threading on Solaris.  */
#ifndef _POSIX_PTHREAD_SEMANTICS
# define _POSIX_PTHREAD_SEMANTICS 1
#endif
/* Enable extensions specified by ISO/IEC TS 18661-5:2014.  */
#ifndef __STDC_WANT_IEC_60559_ATTRIBS_EXT__
# define __STDC_WANT_IEC_60559_ATTRIBS_EXT__ 1
#endif
/* Enable extensions specified by ISO/IEC TS 18661-1:2014.  */
#ifndef __STDC_WANT_IEC_60559_BFP_EXT__
# define __STDC_WANT_IEC_60559_BFP_EXT__ 1
#endif
/* Enable extensions specified by ISO/IEC TS 18661-2:2015.  */
#ifndef __STDC_WANT_IEC_60559_DFP_EXT__
# define __STDC_WANT_IEC_60559_DFP_EXT__ 1
#endif
/* Enable extensions specified by ISO/IEC TS 18661-4:2015.  */
#ifndef __STDC_WANT_IEC_60559_FUNCS_EXT__
# define __STDC_WANT_IEC_60559_FUNCS_EXT__ 1
#endif
/* Enable extensions specified by ISO/IEC TS 18661-3:2015.  */
#ifndef __STDC_WANT_IEC_60559_TYPES_EXT__
# define __STDC_WANT_IEC_60559_TYPES_EXT__ 1
#endif
/* Enable extensions specified by ISO/IEC TR 24731-2:2010.  */
#ifndef __STDC_WANT_LIB_EXT2__
# define __STDC_WANT_LIB_EXT2__ 1
#endif
/* Enable extensions specified by ISO/IEC 24747:2009.  */
#ifndef __STDC_WANT_MATH_SPEC_FUNCS__
# define __STDC_WANT_MATH_SPEC_FUNCS__ 1
#endif
/* Enable extensions on HP NonStop.  */
#ifndef _TANDEM_SOURCE
# define _TANDEM_SOURCE 1
#endif
/* Enable X/Open extensions.  Define to 500 only if necessary
   to make mbstate_t available.  */
#ifndef _XOPEN_SOURCE
/* # undef _XOPEN_SOURCE */
#endif


/* Vendor man version */
#define VENDOR_MAN_VERSION "Version 21.1.9"

/* Vendor name */
#define VENDOR_NAME "The X.Org Foundation"

/* Vendor name */
#define VENDOR_NAME_SHORT "X.Org"

/* Vendor release */
#define VENDOR_RELEASE ((10000000) + ((21) * 100000) + ((1) * 1000) + 9)

/* Version number of package */
#define VERSION "21.1.9"

/* Building with libdrm support */
#define WITH_LIBDRM 1

/* Building vgahw module */
#define WITH_VGAHW 1

/* Define WORDS_BIGENDIAN to 1 if your processor stores words with the most
   significant byte first (like Motorola and SPARC, unlike Intel). */
#if defined AC_APPLE_UNIVERSAL_BUILD
# if defined __BIG_ENDIAN__
#  define WORDS_BIGENDIAN 1
# endif
#else
# ifndef WORDS_BIGENDIAN
/* #  undef WORDS_BIGENDIAN */
# endif
#endif

/* System has wscons console */
#define WSCONS_SUPPORT 1

/* Build X-ACE extension */
#define XACE 1

/* Support XCMisc extension */
#define XCMISC 1

/* Name of configuration directory */
#define XCONFIGDIR "xorg.conf.d"

/* Name of configuration file */
#define XCONFIGFILE "xorg.conf"

/* Build Security extension */
#define XCSECURITY 1

/* Support XDM Control Protocol */
#define XDMCP 1

/* Support XF86 Big font extension */
/* #undef XF86BIGFONT */

/* Name of configuration file */
#define XF86CONFIGFILE "xorg.conf"

/* Build DRI extension */
#define XF86DRI 1

/* Support XFree86 Video Mode extension */
#define XF86VIDMODE 1

/* Support XFixes extension */
#define XFIXES 1

/* Building XFree86 server */
#define XFree86Server 1

/* Build XDGA support */
#define XFreeXDGA 1

/* Support Xinerama extension */
#define XINERAMA 1

/* Support X Input extension */
#define XINPUT 1

/* Path to XKB data */
#define XKB_BASE_DIRECTORY "/usr/X11R6/share/X11/xkb"

/* Path to XKB bin dir */
#define XKB_BIN_DIRECTORY "/usr/X11R6/bin"

/* Default XKB layout */
#define XKB_DFLT_LAYOUT "us"

/* Default XKB model */
#define XKB_DFLT_MODEL "pc105"

/* Default XKB options */
#define XKB_DFLT_OPTIONS ""

/* Default XKB ruleset */
#define XKB_DFLT_RULES "base"

/* Default XKB variant */
#define XKB_DFLT_VARIANT ""

/* Path to XKB output dir */
#define XKM_OUTPUT_DIR "/var/db/xkb/"

/* Building Xorg server */
#define XORGSERVER 1

/* Vendor man version */
#define XORG_MAN_VERSION "Version 21.1.9"

/* Building Xorg server */
#define XORG_SERVER 1

/* Current Xorg version */
#define XORG_VERSION_CURRENT ((10000000) + ((21) * 100000) + ((1) * 1000) + 9)

/* Have Quartz */
/* #undef XQUARTZ */

/* Support application updating through sparkle. */
/* #undef XQUARTZ_SPARKLE */

/* Support Record extension */
#define XRECORD 1

/* Build SELinux extension */
/* #undef XSELINUX */

/* Define to 1 if the DTrace Xserver provider probes should be built in. */
/* #undef XSERVER_DTRACE */

/* Use libpciaccess for all pci manipulation */
#define XSERVER_LIBPCIACCESS 1

/* X server supports platform device enumeration */
/* #undef XSERVER_PLATFORM_BUS */

/* Support XSync extension */
#define XSYNC 1

/* Support XTest extension */
#define XTEST 1

/* Enable xtrans fd passing support */
#define XTRANS_SEND_FDS 1

/* Support Xv extension */
#define XV 1

/* Vendor name */
#define XVENDORNAME "The X.Org Foundation"

/* Short vendor name */
#define XVENDORNAMESHORT "X.Org"

/* byte order */
#define X_BYTE_ORDER X_LITTLE_ENDIAN

/* Use X server privilege separation */
#define X_PRIVSEP 1

/* Build Xv extension */
#define XvExtension 1

/* Build XvMC extension */
#define XvMCExtension 1

/* Define to 1 if `lex' declares `yytext' as a `char *' by default, not a
   `char[]'. */
#define YYTEXT_POINTER 1

/* Number of bits in a file offset, on hosts where this is settable. */
/* #undef _FILE_OFFSET_BITS */

/* Enable GNU and other extensions to the C environment for glibc */
#define _GNU_SOURCE 1

/* Define for large files, on AIX-style hosts. */
/* #undef _LARGE_FILES */

/* Defined if needed to expose struct msghdr.msg_control */
/* #undef _XOPEN_SOURCE */

/* Define to 1 if unsigned long is 64 bits. */
#define _XSERVER64 1

/* Vendor web address for support */
#define __VENDORDWEBSUPPORT__ "http://wiki.x.org"

/* Name of X server */
#define __XSERVERNAME__ "Xorg"

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define as a signed integer type capable of holding a process identifier. */
/* #undef pid_t */

/* Define to __typeof__ if your compiler spells it that way. */
/* #undef typeof */
