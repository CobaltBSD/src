#define _XOPEN_SOURCE 500
#define _BSD_SOURCE

#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wchar.h>
#include <fts.h>

#include "ls.h"
#include "extern.h"

int
colorprint(FTSENT *p)
{
	// Wrap the name in appropriate color bytes
	// TODO: make this customizable

	char *colorbytes = "\033[0;37;49m"; // Default is white w/ black background

	int fullpath_sz = snprintf(NULL, 0, "%s/%s", p->fts_path, p->fts_accpath);
	char *fullpath = malloc(fullpath_sz + 1);
	(void) sprintf(fullpath, "%s/%s", p->fts_path, p->fts_accpath);

	struct stat path_stat;
	(void) lstat(fullpath, &path_stat);

	// Check file types
	if(S_ISBLK(path_stat.st_mode)) {
		colorbytes = "\033[1;33;49m";
	} else if(S_ISCHR(path_stat.st_mode)) {
		colorbytes = "\033[0;33;49m";
	} else if(S_ISLNK(path_stat.st_mode)) {
		colorbytes = "\033[1;35;49m";
	} else if(S_ISFIFO(path_stat.st_mode)) {
		colorbytes = "\033[3;33;49m";
	} else if(S_ISSOCK(path_stat.st_mode)) {
		colorbytes = "\033[3;35;49m";
	} else if(S_ISDIR(path_stat.st_mode)) {
		colorbytes = "\033[1;36;49m";
	} else if(S_IXUSR & path_stat.st_mode) {
		colorbytes = "\033[1;31;49m";
	}

	// Check file permissions
	if((path_stat.st_mode & 04000) == 04000) { // Check setuid
		colorbytes = "\033[1;37;41m";
	} else if((path_stat.st_mode & 03000) == 03000) { // Fourth digit is set to 3
		colorbytes = "\033[1;30;43m";
	} else if((path_stat.st_mode & 02000) == 02000) { // Check setgid
		colorbytes = "\033[0;30;43m";
	} else if((path_stat.st_mode & 01000) == 01000) { // Check sticky bit
		colorbytes = "\033[1;30;42m";
	}

	// Check broken symlink TODO
	// Check file extension TODO media (bold magenta?), archives (bold red?), audio (dark cyan/blue), old (dark gray)

	int newname_sz = snprintf(NULL, 0, "%s%s\033[0m", colorbytes, p->fts_name);
	char *newname = malloc(newname_sz + 1);
	(void) sprintf(newname, "%s%s\033[0m", colorbytes, p->fts_name);

	wchar_t	  wc;
	int	  len;  /* length in bytes of UTF-8 encoded string */
	int	  width;  /* display width of a single Unicode char */
	int	  total_width;  /* display width of the whole string */

	for (total_width = 0; *newname != '\0'; newname += len) {
		if ((len = mbtowc(&wc, newname, MB_CUR_MAX)) == -1) {
			(void) mbtowc(NULL, NULL, MB_CUR_MAX);
			putchar(*newname);
			total_width++;
			len = 1;
		} else if ((width = wcwidth(wc)) == -1) {
			fwrite(newname, 1, len, stdout);
			total_width++;
		} else {
			fwrite(newname, 1, len, stdout);
			total_width += width;
		}
	}
	return total_width - 14; // The -14 is necessary to adjust for the color bytes
}
