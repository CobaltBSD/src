#pragma once

#include <sys/types.h>

typedef off_t pm_filepos;
#define FTELLO ftello
#define FSEEKO fseeko

#define RGBENV "RGBDEF"    /* name of env-var */

#define RGB_DB_PATH "/usr/share/netpbm/rgb.txt:/usr/lib/X11/rgb.txt:/usr/share/X11/rgb.txt:/usr/X11R6/lib/X11/rgb.txt"

#define LITERAL_FN_DEF_MATCH 0

#define pm_pipe pipe

#define TMPDIR P_tmpdir

#define UNREFERENCED_PARAMETER(x) (x)

#define pm_mkdir(dir, perm) mkdir(dir, perm) 
