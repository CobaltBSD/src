#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>

int tflag = 0; // If not a range, if there should be a line break in between characters
int nflag = 0; // Convert characters to ASCII

void usage(void) {
	(void) fputs("unicode { [-t] hex hex ... | hexmin-hexmax ... | [-n] char ... }\n", stderr);
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
	setlocale(LC_CTYPE, "");
	int c;

	while ((c = getopt(argc, argv, "tn")) != -1) {
		switch (c) {
			case 't':
				tflag = 1;
				break;
			case 'n':
				nflag = 1;
				break;
			default:
				usage();
		}
	}
	argc -= optind;
	argv += optind;

	if (nflag) { // tflag is ignored if nflag is specified
		while (argc) {
			for (int i = 0; i < strlen(argv[0]); i++) {
				printf("%04x\n", argv[0][i]);
			}

			argc--;
			argv++;
		}
		exit(EXIT_SUCCESS);
	}

	int use_ranges = 0; // If any ranges are in use, display as a table instead
	while (argc) {
		if (use_ranges == 0) use_ranges = strchr(argv[0], '-') == NULL ? -1 : 1; // First value determines if it is a range or not
		char *tok = strtok(argv[0], "-");

		if (use_ranges == 1) {
			long c1 = strtol(tok, NULL, 16);
			tok = strtok(NULL, "-");

			long c2 = strtol(tok, NULL, 16);
			if (strtok(NULL, "-") != NULL) {
				(void) fputs("Invalid range\n", stderr);
				exit(EXIT_FAILURE);
			}

			for (; c1 < c2; c1++) {
				wprintf(L"%04lx %lc\n", c1, (wchar_t) c1);
			}
		} else {
			long c = strtol(argv[0], NULL, 16);
			printf("%lc%s", (wchar_t) c, tflag ? "" : "\n");
		}

		argc--;
		argv++;
	}

	return EXIT_SUCCESS;
}
