/*
 * https://github.com/rafaelvanoni/C.git
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define	MAX_LEN	(20)
#define	MAX_VAL	(99)

int
ibs(int *array, int len, int n)
{
	int l = 0, h = len - 1, m;

	while (l <= h) {
		m = l + (h-l)/2;

		if (array[m] == n) {
			return (m);
		}

		if (n > array[m]) {
			l = m + 1;
		} else {
			h = m - 1;
		}
	}

	return (-1);
}

int
cmp(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
}

int
main(int argc, char **argv)
{
	int *array, len, n;

	srand(time(NULL));

	do {
		len = rand() % MAX_LEN;
	} while (len == 0);

	array = calloc(len, sizeof (int));

	for (int i = 0; i < len; i++) {
		array[i] = rand() % MAX_VAL;
		if (rand() % 2 == 0) {
			n = array[i];
		}
	}

	qsort(array, len, sizeof(int), cmp);

	for (int i = 0; i < len; i++) {
		printf("%d ", array[i]);
	}

	printf("\nfound %d at %d\n", n, ibs(array, len, n));

	free(array);

	return (0);
}
