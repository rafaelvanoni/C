/*
 * https://github.com/rafaelvanoni/C.git
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int
main(int argc, char **argv)
{
	char foo[] = "one,two,three";
	char bar[] = "fourfive";
	char *ptr = foo;

	/* count the number of commas in 'foo' and 'bar' */
	while ((ptr = strchr(ptr, ',')) != NULL) {
		printf("found a comma in 'foo' at %p\n", ptr);
		ptr++;
	}

	ptr = bar;

	while ((ptr = strchr(ptr, ',')) != NULL) {
		printf("found a comma in 'bar' at %p\n", ptr);
		ptr++;
	}

	return (0);
}
