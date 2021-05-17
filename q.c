/*
 * https://github.com/rafaelvanoni/C.git
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>

#define	MIN_SZ		(10)
#define	MAX_SZ		(99)
#define	MAX_VAL		(99)

struct node {
	int		val;
	struct	node	*next;
};

struct queue {
	struct node	*head;
	struct node	*tail;
};

void
q_enq(struct queue *q, struct node *n)
{
	assert(q != NULL);
	assert(n != NULL);

	if (q->head == NULL) {
		assert(q->tail == NULL);
		q->head = n;
		q->tail = n;
		n->next = NULL;
	} else {
		assert(q->tail != NULL);
		q->tail->next = n;
		q->tail = n;
		n->next = NULL;
	}
}

struct node *
q_deq(struct queue *q)
{
	struct node *n;

	if (q->head == NULL) {
		assert(q->tail == NULL);
		return (NULL);
	}

	assert(q->tail != NULL);
	n = q->head;
	q->head = n->next;

	if (q->tail == n) {
		q->tail = q->head;
	}

	return (n);
}

bool
q_is_empty(struct queue *q)
{
	if (q->head == NULL) {
		assert(q->tail == NULL);
		return (true);
	}
	assert(q->tail != NULL);
	return (false);
}

int
main(int argc, char **argv)
{
	struct queue q = { 0 };
	struct node *n;
	int i, n_nodes;

	srand(time(NULL));

	do {
		n_nodes = MIN_SZ + (rand() % MAX_SZ);
	} while (n_nodes < MIN_SZ || n_nodes > MAX_SZ);

	printf("creating a queue with %d nodes\n", n_nodes);

	for (i = 0; i < n_nodes; i++) {
		n = calloc(1, sizeof (struct node));
		n->val = rand() % MAX_VAL;
		printf("enqueuing %d\n", n->val);
		q_enq(&q, n);
	}

	for (i = 0; i < n_nodes; i++) {
		n = q_deq(&q);
		printf("dequeued %d\n", n->val);
		free(n);
	}

	return (0);
}
