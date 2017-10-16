#include <stdio.h>
#include <stdlib.h>

#define BUFSZ (128)

int main(int argc, char *argv[])
{
	FILE *F;
	char *buf;
	int c, line=1, i=0, size=BUFSZ;

	if (argc != 2) exit(1);
	F=fopen(argv[1], "r");
	buf = malloc(BUFSZ);
	if (!buf) {
		fprintf(stderr, "Out of memory\n");
		abort();
	}

	while ((c=fgetc(F)) != EOF) {
		if (i == size-1) {
			size *= 2;
			buf = realloc(buf, size);
		}
		if (c == '\r') continue;
		else if (c != '\n') buf[i++] = c;
		else {
			buf[i] = '\0';
			printf("%d.%d: %s\n", line++, i, buf); fflush(stdout);
			i = 0;
		}
	}
	return 0;
}

