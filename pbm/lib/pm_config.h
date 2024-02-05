#pragma once

#include <sys/types.h>

#define BSD

/* Switch macros like _POSIX_SOURCE are supposed to add features from
   the indicated standard to the C library.  A source file defines one
   of these macros to declare that it uses features of that standard
   as opposed to conflicting features of other standards (e.g. the
   POSIX foo() subroutine might do something different from the X/Open
   foo() subroutine).  Plus, this forces the coder to understand upon
   what feature sets his program relies.

   But some C library developers have misunderstood this and think of these
   macros like the old __ansi__ macro, which tells the C library, "Don't 
   have any features that aren't in the ANSI standard."  I.e. it's just
   the opposite -- the macro subtracts features instead of adding them.

   This means that on some platforms, Netpbm programs must define
   _POSIX_SOURCE, and on others, it must not.  Netpbm's POSIX_IS_IMPLIED 
   macro indicates that we're on a platform where we need not define
   _POSIX_SOURCE (and probably must not).

   The problematic C libraries treat _XOPEN_SOURCE the same way.
*/
#if defined(__OpenBSD__) || defined (__NetBSD__) || defined(__bsdi__) || defined(__APPLE__)
#define POSIX_IS_IMPLIED
#endif

typedef off_t pm_filepos;
#define FTELLO ftello
#define FSEEKO fseeko

/* CONFIGURE: This is the name of an environment variable that tells
** where the color names database is.  If the environment variable isn't
** set, Netpbm tries the hardcoded defaults per macro 'RGB_DB_PATH'
** (see below).
*/
#define RGBENV "RGBDEF"    /* name of env-var */

#define RGB_DB_PATH "/usr/share/pbm/rgb.txt:/usr/lib/X11/rgb.txt:/usr/share/X11/rgb.txt:/usr/X11R6/lib/X11/rgb.txt:/usr/X11R6/share/X11/rgb.txt"

/* CONFIGURE: There should be an environment variable telling where the color
** names database (color dictionary) is for Netpbm to use, e.g. to determine
** what colord name "Salmon" is.  The name of that environment variable is
** above.  But as some people prefer hardcoded file paths to environment
** variables, if such environment variable is not set, Netpbm looks for the
** first existing file in the list which is the value of 'RGB_DB_PATH'.  And
** if none of those exist (including if the list is empty), Netpbm simply
** doesn't understand any color names.  Note that Netpbm comes with a color
** database (lib/rgb.txt in the source tree), but you might choose to have
** Netpbm use a different one.  See the documentation of ppm_parsecolor()
** for the format of the color database file.
*/

#define HAVE_VASPRINTF 1

#define LITERAL_FN_DEF_MATCH 0

#define pm_pipe pipe

/* UNALIGNED_OK means it's OK to do unaligned memory access, e.g.
   loading an 8-byte word from an address that is not a multiple of 8.
   On some systems, such an access causes a trap and a signal.

   This determination is conservative - There may be cases where unaligned
   access is OK and we say here it isn't.

   We know unaligned access is _not_ OK on at least SPARC and some ARM.
*/
#if defined(__x86_64__) | defined(__i486__) | defined(__vax__)
# define UNALIGNED_OK 1
#else
# define UNALIGNED_OK 0
#endif

#define TMPDIR P_tmpdir

/* only Pnmstitch uses UNREFERENCED_PARAMETER today (and I'm not sure why),
   but it might come in handy some day.
*/
#define UNREFERENCED_PARAMETER(x) (x)

#define pm_mkdir(dir, perm) mkdir(dir, perm) 

#define HAVE_MKSTEMP 1

/* CONFIGURE: On most BSD systems, malloc() gets declared in stdlib.h, on
** system V, it gets declared in malloc.h. On some systems, malloc.h
** doesn't declare these, so we have to do it here. On other systems,
** for example HP/UX, it declares them incompatibly.  And some systems,
** for example Dynix, don't have a malloc.h at all.  A sad situation.
** If you have compilation problems that point here, feel free to tweak
** or remove these declarations.
*/
#include <stdlib.h>

/* At least one compiler can't handle two declarations of the same function
   that aren't literally identical.  E.g. "static foo_fn_t foo1;" conflicts
   with "static void foo1(int);" even if type 'foo_fn_t' is defined as
   void(int).  (The compiler we saw do this is SGI IDO cc (for IRIX 4.3)).

   LITERAL_FN_DEF_MATCH says that the compiler might have this problem,
   so one must be conservative in redeclaring functions.
*/
#if defined(__GNUC__)
  #define LITERAL_FN_DEF_MATCH 0
#else
  #if (defined(__sgi))
    #define LITERAL_FN_DEF_MATCH 1
  #else   
    #define LITERAL_FN_DEF_MATCH 0
  #endif
#endif

/* CONFIGURE: GNU Compiler extensions are used in performance critical places
   when available.  Test whether they exist.

   Prevent the build from exploiting these extensions by defining
   NO_GCC_UNIQUE.

   Before Netpbm 10.65 (December 2013), Netpbm used GCC compiler extensions
   to generate SSE code in Pamflip.  Starting in 10.65, Netpbm instead uses
   the more standard operators defined in <emmtrins.h>.  To prevent Netpbm
   from explicitly using any SSE instructions, set WANT_SSE to N in
   config.mk.
*/

#if defined(__GNUC__) && !defined(NO_GCC_UNIQUE)
  #define GCCVERSION __GNUC__*100 + __GNUC_MINOR__
#else
  #define GCCVERSION 0
#endif

#ifndef HAVE_GCC_BITCOUNT
#if GCCVERSION >=304
  #define HAVE_GCC_BITCOUNT 1
  /* Use __builtin_clz(),  __builtin_ctz() (and variants for long)
     to count leading/trailing 0s in int (and long). */
#else
  #define HAVE_GCC_BITCOUNT 0
#endif
#endif

#ifndef HAVE_GCC_BSWAP
#if GCCVERSION >=403 || defined(__clang__)
  #define HAVE_GCC_BSWAP 1
  /* Use __builtin_bswap32(), __builtin_bswap64() for endian conversion.
     NOTE: On intel CPUs this may produce the bswap operand which is not
     available on 80386. */
#else
  #define HAVE_GCC_BSWAP 0
#endif
#endif

#ifndef HAVE_WORKING_SSE2
#if defined(__SSE2__) && ( GCCVERSION >=402 || defined(__clang__) )
  #define HAVE_WORKING_SSE2 1
  /* We can use SSE2 builtin functions to exploit SSE2 instructions.  GCC
     version 4.2 or newer is required; older GCC ostensibly has these SSE2
     builtins, but the compiler aborts with an error.  Note that __SSE2__
     means not only that the compiler has the capability, but that the user
     has not disabled it via compiler options.
  */
#else
  #define HAVE_WORKING_SSE2 0
#endif
#endif

typedef int qsort_comparison_fn(const void *, const void *);
    /* A compare function to pass to <stdlib.h>'s qsort() */
