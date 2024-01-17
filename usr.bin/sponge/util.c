#include <unistd.h>
#include <stdio.h>

ssize_t
writeall(int fd, const void *buf, size_t len)
{
	const char *p = buf;
	ssize_t n;

	while (len) {
		n = write(fd, p, len);
		if (n <= 0)
			return n;
		p += n;
		len -= n;
	}

	return p - (const char *)buf;
}
	
int
concat(int f1, const char *s1, int f2, const char *s2)
{
	char buf[8192];
	ssize_t n;

	while ((n = read(f1, buf, sizeof(buf))) > 0) {
		if (writeall(f2, buf, n) < 0) {
			fprintf(stderr, "write %s:", s2);
			return -2;
		}
	}
	if (n < 0) {
		fprintf(stderr, "read %s:", s1);
		return -1;
	}
	return 0;
}
