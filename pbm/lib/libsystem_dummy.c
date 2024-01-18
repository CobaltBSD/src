/*=============================================================================
                             libsystem_dummy.c
===============================================================================
  This is a dummy version of libsystem.c, for use on systems that don't
  have the kind of process control that libsystem.c needs.

  With this module, programs will build cleanly, but if a program actually
  calls pm_system(), it will die with an error message saying that
  the facility is not available.
=============================================================================*/

#include <assert.h>

#include "pm.h"
#include "pm_system.h"

void
pm_system_vp(const char *    const progName,
             const char **   const argArray,
             void stdinFeeder(int, void *),
             void *          const feederParm,
             void stdoutAccepter(int, void *),
             void *          const accepterParm) {

    pm_error("This program wants to run another program using pm_system_vp() "
             "in the libnetpbm library, but libnetpbm was built without "
             "the pm_system_vp() facility -- probably because this system "
             "doesn't have the process management facilities pm_system() "
             "requires.");
}

void
pm_system_lp(const char *    const progName,
             void stdinFeeder(int, void *),
             void *          const feederParm,
             void stdoutAccepter(int, void *),
             void *          const accepterParm,
             ...) {

    pm_error("This program wants to run another program using pm_system_lp() "
             "in the libnetpbm library, but libnetpbm was built without "
             "the pm_system_lp() facility -- probably because this system "
             "doesn't have the process management facilities pm_system() "
             "requires.");
}

void
pm_system(void                  stdinFeeder(int, void *),
          void *          const feederParm,
          void                  stdoutAccepter(int, void *),
          void *          const accepterParm,
          const char *    const shellCommand) {

    pm_error("This program wants to run another program using pm_system() "
             "in the libnetpbm library, but libnetpbm was built without "
             "the pm_system() facility -- probably because this system "
             "doesn't have the process management facilities pm_system() "
             "requires.");
}


void
pm_feed_from_memory(int    const pipeToFeedFd,
                    void * const feederParm) {

    assert(FALSE);  /* Can't ever run, since pm_system() is a dummy */
}



void
pm_accept_to_memory(int    const pipetosuckFd,
                    void * const accepterParm) {

    assert(FALSE);  /* Can't ever run, since pm_system() is a dummy */
}

