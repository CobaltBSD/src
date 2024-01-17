/*
MIT License

© 2011 Connor Lane Smith <cls@lubutu.com>
© 2011-2016 Dimitris Papastamos <sin@2f30.org>
© 2014-2016 Laslo Hunhold <dev@frign.de>

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/
// Originally part of suckless coreutils

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "arg.h"
#include "util.h"

static void
usage(void)
{
	fprintf(stderr, "usage: sponge file\n");
	exit(EXIT_FAILURE);
}

int
main(int argc, char *argv[])
{
	char tmp[] = "/tmp/sponge-XXXXXX";
	int fd, tmpfd;

	ARGBEGIN {
	default:
		usage();
	} ARGEND

	if (argc != 1)
		usage();

	if ((tmpfd = mkstemp(tmp)) < 0) {
		fprintf(stderr, "mkstemp:");
		exit(EXIT_FAILURE);
	}
	unlink(tmp);
	if (concat(0, "<stdin>", tmpfd, "<tmpfile>") < 0)
		return 1;
	if (lseek(tmpfd, 0, SEEK_SET) < 0) {
		fprintf(stderr, "lseek:");
		exit(EXIT_FAILURE);
	}

	if ((fd = creat(argv[0], 0666)) < 0) {
		fprintf(stderr, "creat %s:", argv[0]);
		exit(EXIT_FAILURE);
	}
	if (concat(tmpfd, "<tmpfile>", fd, argv[0]) < 0)
		return 1;

	return 0;
}
