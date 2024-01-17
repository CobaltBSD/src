#pragma once

ssize_t
writeall(int fd, const void *buf, size_t len);

int
concat(int f1, const char *s1, int f2, const char *s2);
