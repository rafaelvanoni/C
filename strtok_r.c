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
	char *delim = ", \t\r\n";
	char *endp = NULL;
	char *tok;

	tok = strtok_r(foo, delim, &endp);
	while (tok != NULL) {
		printf("%s %ld\n", tok, strlen(tok));
		tok = strtok_r(NULL, delim, &endp);
	}

	return (0);
}
