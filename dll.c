/*
 * https://github.com/rafaelvanoni/C.git
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>

#define	MIN_SZ		(5)
#define	MAX_SZ		(10)
#define	MAX_VAL		(99)

struct node {
	int		val;
	struct node	*prev;
	struct node	*next;
};

struct dll {
	struct node	*head;
	struct node	*tail;
};

typedef enum {
	FWD = 1,
	BKW = 2,
} direction;

void
dll_print(struct dll *l, direction d)
{
	struct node *n;
	int i = 0;

	n = (d == FWD) ? l->head : l->tail;

	while (n != NULL) {
		printf("[%d] %d\n", i++, n->val);
		n = (d == FWD) ? n->next : n->prev;
	}
}

void
dll_prepend(struct dll *l, struct node *n)
{
	assert(l != NULL);
	assert(n != NULL);

	if (l->head == NULL) {
		assert(l->tail == NULL);
		l->head = n;
		l->tail = n;
		n->next = NULL;
		n->prev = NULL;
	} else {
		assert(l->tail != NULL);
		l->head->prev = n;
		n->next = l->head;
		l->head = n;
	}
}

void
dll_append(struct dll *l, struct node *n)
{
	assert(l != NULL);
	assert(n != NULL);

	if (l->head == NULL) {
		assert(l->tail == NULL);
		l->head = n;
		l->tail = n;
		n->prev = NULL;
		n->next = NULL;
	} else {
		assert(l->tail != NULL);
		l->tail->next = n;
		n->prev = l->tail;
		l->tail = n;
	}
}

void
dll_delete(struct dll *l)
{
	struct node *n = l->head, *m;

	assert(l != NULL);

	while (n != NULL) {
		m = n->next;
		free(n);
		n = m;
	}

	l->head = NULL;
	l->tail = NULL;
}

int
dll_count(struct dll *l)
{
	struct node *n = l->tail;
	int c = 0;

	assert(l != NULL);

	while (n != NULL) {
		c++;
		n = n->prev;
	}

	return (c);
}

int
dll_behead(struct dll *l)
{
	struct node *n;
	int val;

	assert(l != NULL);

	if (l->head == NULL) {
		assert(l->tail != NULL);
		return (-1);
	}

	assert(l->tail != NULL);

	n = l->head;
	val = n->val;

	if (n->next != NULL) {
		n->next->prev = NULL;
		l->head = n->next;
	} else {
		l->head = NULL;
	}

	if (l->tail == n) {
		l->tail = NULL;
	}

	free(n);
	return (val);
}

int
dll_chop(struct dll *l)
{
	struct node *n;
	int val;

	assert(l != NULL);

	if (l->tail == NULL) {
		assert(l->head == NULL);
		return (-1);
	}

	assert(l->head != NULL);

	n = l->tail;
	val = n->val;

	if (n->prev != NULL) {
		n->prev->next = NULL;
		l->tail = n->prev;
	} else {
		l->tail = NULL;
	}

	if (l->head == n) {
		l->head = NULL;
	}

	free(n);
	return (val);
}

int
main(int argc, char **argv)
{
	struct dll l = { 0 };
	struct node *n;
	int i, n_nodes;

	srand(time(NULL));

	do {
		n_nodes = MIN_SZ + (rand() % MAX_SZ);
	} while (n_nodes < MIN_SZ || n_nodes > MAX_SZ);

	printf("prepending %d nodes to a doubly linked list\n", n_nodes);

	for (i = 0; i < n_nodes; i++) {
		n = calloc(1, sizeof (struct node));
		n->val = rand() % MAX_VAL;
		dll_prepend(&l, n);
	}

	dll_print(&l, FWD);
	printf("\n");
	dll_print(&l, BKW);
	printf("\n");

	printf("appending %d nodes to a doubly linked list\n", n_nodes/2);

	for (i = 0; i < n_nodes/2; i++) {
		n = calloc(1, sizeof (struct node));
		n->val = rand() % MAX_VAL;
		dll_append(&l, n);
	}

	dll_print(&l, FWD);
	printf("\n");
	dll_print(&l, BKW);
	printf("\n");

	printf("dll has %d nodes\n", dll_count(&l));

	printf("beheading the dll.. got %d\n", dll_behead(&l));
	printf("beheading the dll.. got %d\n", dll_behead(&l));
	printf("beheading the dll.. got %d\n", dll_behead(&l));
	dll_print(&l, FWD);
	printf("\n");
	dll_print(&l, BKW);
	printf("\n");

	printf("chopping the dll.. got %d\n", dll_chop(&l));
	printf("chopping the dll.. got %d\n", dll_chop(&l));
	printf("chopping the dll.. got %d\n", dll_chop(&l));
	dll_print(&l, FWD);
	printf("\n");
	dll_print(&l, BKW);
	printf("\n");

	printf("deleting the dll..\n");
	dll_delete(&l);
	dll_print(&l, FWD);

	return (0);
}
