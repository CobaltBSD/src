/* include/xwin-config.h.  Generated from xwin-config.h.in by configure.  */
/*
 * xwin-config.h.in
 *
 * This file has all defines used in the xwin ddx
 *
 */
#include <dix-config.h>

/* Winsock networking */
/* #undef HAS_WINSOCK */

/* Cygwin has /dev/windows for signaling new win32 messages */
/* #undef HAS_DEVWINDOWS */

/* Switch on debug messages */
/* #undef CYGDEBUG */
/* #undef CYGWINDOWING_DEBUG */
/* #undef CYGMULTIWINDOW_DEBUG */

/* Define to 1 if unsigned long is 64 bits. */
#define _XSERVER64 1

/* Short vendor name */
#define XVENDORNAMESHORT "X.Org"

/* Vendor web address for support */
#define __VENDORDWEBSUPPORT__ "http://wiki.x.org"

/* Default log location */
#define DEFAULT_LOGDIR "/var/log"

/* Whether we should re-locate the root to where the executable lives */
/* #undef RELOCATE_PROJECTROOT */
