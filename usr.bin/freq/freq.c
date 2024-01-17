#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(void) {
	int c;

	size_t sz = 0;
	unsigned char *str = NULL;

	while (1) {
		sz++;
		str = realloc(str, sz * sizeof(int));
		(void) fread(str + sz - 1, sizeof(char), 1, stdin);
		if (feof(stdin)) break;
	}

	unsigned char hist[UCHAR_MAX] = {0};

	for (int i = 0; i < sz && str[i] != 0; i++) {
		hist[str[i]] += 1;
	}

	for (int i = 0; i < UCHAR_MAX; i++) {
		if (hist[i] != 0) {
			printf("%03d %03o %02x %lc\t%d\n", i, i, i, i == '\n' || i > 0x7f ? '-' : i, hist[i]);
		}
	}
	
	return 0;
}
