#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>

#define	LIST_LEN	(10)
#define	MAX_VAL		(99)

struct node {
	int		val;
	struct node	*next;
};

void
sll_print(struct node *l)
{
	struct node *n = l;
	int i = 0;

	while (n != NULL) {
		printf("[%d] %d\n", i++, n->val);
		n = n->next;
	}
}

void
sll_delete(struct node **l)
{
	struct node *n;

	assert(*l != NULL);
	n = *l;

	while (n != NULL) {
		*l = n->next;
		free(n);
		n = *l;
	}

	assert(*l == NULL);
}

void
sll_prepend(struct node **l, struct node *n)
{
	assert(l != NULL);
	assert(n != NULL);

	if (*l == NULL) {
		*l = n;
		n->next = NULL;
	} else {
		n->next = *l;
		*l = n;
	}
}

void
sll_append(struct node **l, struct node *n)
{
	if (*l == NULL) {
		*l = n;
		n->next = NULL;
	} else {
		struct node *i = *l;

		do {
			if (i->next == NULL) {
				i->next = n;
				n->next = NULL;
			}
			i = i->next;
		} while (i != NULL);
	}
}

void
sll_delete_val(struct node **l, int v)
{
	struct node *n = *l, *prev = NULL;

	while (n != NULL) {
		if (n->val == v) {
			if (prev == NULL) {
				assert(n == *l);
				*l = n->next;
				free(n);
				n = *l;
			} else {
				prev->next = n->next;
				free(n);
				n = prev->next;
				if (n == NULL) {
					break;
				}
			}
		}

		prev = n;
		n = n->next;
	}
}

void
sll_reverse(struct node **l)
{
	struct node *r = NULL;

	while (*l != NULL) {
		struct node *n;
		/* pop the top of 'l' */
		n = *l;
		*l = n->next;

		/* prepend it to 'r' */
		n->next = r;
		r = n;
	}

	assert(*l == NULL);
	*l = r;
}

int
sll_print_middle(struct node *l)
{
	struct node *n, *m;
	int i;

	n = l;
	m = l;
	i = 0;

	while (n != NULL) {
		if (++i % 2 == 0) {
			m = m->next;
		}

		n = n->next;
	}

	assert(m != NULL);
	return (m->val);
}

int
main(int argc, char **argv)
{
	struct node *l = NULL, *n;
	int i;

	srand(time(NULL));

	printf("prepending a new list..\n");
	for (i = 0; i < LIST_LEN; i++) {
		n = calloc(1, sizeof (struct node));
		n->val = rand() % MAX_VAL;
		sll_prepend(&l, n);
	}

	sll_print(l);
	printf("deleting the list..\n");
	sll_delete(&l);
	sll_print(l);

	printf("appending a new list..\n");
	for (i = 0; i < LIST_LEN; i++) {
		n = calloc(1, sizeof (struct node));
		n->val = rand() % MAX_VAL;
		sll_append(&l, n);
	}

	sll_print(l);
	printf("element at the middle is %d\n", sll_print_middle(l));
	printf("deleting all instances of '0'..\n");
	sll_delete_val(&l, 0);
	sll_print(l);

	printf("reversing..\n");
	sll_reverse(&l);
	sll_print(l);

	printf("deleting the list..\n");
	sll_delete(&l);
	printf("printing the list..\n");
	sll_print(l);

	return (0);
}
