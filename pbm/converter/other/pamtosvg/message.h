/* message.h: extend the standard programming environment a little. */

#ifndef MESSAGE_H
#define MESSAGE_H

#include <stdio.h>
#include <stdlib.h>

#include "logreport.h"

/* Define common sorts of messages.  */

#define START_FATAL() do { fputs ("fatal: ", stderr); LOG("fatal: ")
#define END_FATAL() fputs (".\n", stderr); exit (1); } while (0)

#define FATAL(s)							\
  START_FATAL (); fprintf (stderr, "%s", s); LOG (s); END_FATAL ()
#define FATAL1(s, e1)							\
  START_FATAL (); fprintf (stderr, s, e1); LOG1 (s, e1); END_FATAL ()


#define START_WARNING() do { fputs ("warning: ", stderr); LOG ("warning: ")
#define END_WARNING() fputs (".\n", stderr); } while (0)

#define WARNING(s)							\
  START_WARNING (); fprintf (stderr, "%s", s); LOG (s); END_WARNING ()
#define WARNING1(s, e1)							\
  START_WARNING (); fprintf (stderr, s, e1); LOG1 (s, e1); END_WARNING ()

#endif /* not MESSAGE_H */

