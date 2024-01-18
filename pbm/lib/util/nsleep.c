#include "pm_config.h"

#if MSVCRT
  #include <windows.h>
  #include <process.h>
#else
  #include <unistd.h>
#endif

#include "nsleep.h"



void
pm_sleep(unsigned int const milliseconds) {

#if MSVCRT
    SleepEx(milliseconds, TRUE);
#else

    /* We could use usleep() here if millisecond resolution is really
       important, but since Netpbm has no need for it today, we don't
       want to deal with the possibility that usleep() doesn't exist.
       08.08.01.
    */

    sleep((milliseconds + 999)/1000);
#endif
}
