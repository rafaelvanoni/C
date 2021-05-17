/*
 * https://github.com/rafaelvanoni/C.git
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>

#define	MIN_SZ		(10)
#define	MAX_SZ		(12)
#define	MAX_VAL		(99)

struct node {
	int		val;
	struct node	*next;
};

void
stack_push(struct node **s, struct node *n)
{
	assert(s != NULL);
	assert(n != NULL);

	n->next = *s;
	*s = n;
}

struct node *
stack_pop(struct node **s)
{
	struct node *n;

	assert(s != NULL);
	n = *s;
	if (*s != NULL) {
		*s = n->next;
	}

	return (n);
}

bool
stack_is_empty(struct node **s)
{
	struct node *n;

	if ((n = stack_pop(s)) == NULL) {
		return (true);
	}

	stack_push(s, n);
	return (false);
}

int
stack_count(struct node **s)
{
	struct node *t = NULL, *n;
	int c = 0;

	while ((n = stack_pop(s)) != NULL) {
		stack_push(&t, n);
		c++;
	}

	assert(stack_is_empty(s));

	while ((n = stack_pop(&t)) != NULL) {
		stack_push(s, n);
	}

	assert(stack_is_empty(&t));

	return (c);
}

struct node *
stack_reverse(struct node **s)
{
	struct node *r = NULL, *n;

	while ((n = stack_pop(s)) != NULL) {
		stack_push(&r, n);
	}

	assert(stack_is_empty(s));
	return (r);
}

int
stack_peek(struct node *s)
{
	if (s != NULL) {
		return (s->val);
	}

	return (-1);
}

void
stack_sort(struct node **s)
{
	struct node *t = NULL, *n;
	int peek;

	while (!stack_is_empty(s)) {
		n = stack_pop(s);

		while (!stack_is_empty(&t) && n->val < stack_peek(t)) {
			stack_push(s, stack_pop(&t));
		}
		stack_push(&t, n);
	}

	while ((n = stack_pop(&t)) != NULL) {
		stack_push(s, n);
	}
}

int
main(int argc, char **argv)
{
	struct node *s = NULL, *n, *rev = NULL;
	int i, n_nodes;

	srand(time(NULL));

	do {
		n_nodes = MIN_SZ + (rand() % MAX_SZ);
	} while (n_nodes < MIN_SZ || n_nodes > MAX_SZ);

	printf("creating a stack with %d nodes\n", n_nodes);
	for (i = 0; i < n_nodes; i++) {
		n = calloc(1, sizeof (struct node));
		n->val = rand() % MAX_VAL;
		printf("pushing %d\n", n->val);
		stack_push(&s, n);
	}

	printf("stack has %d items\n", stack_count(&s));
	while ((n = stack_pop(&s)) != NULL) {
		printf("popped %d\n", n->val);
		free(n);
	}

	printf("creating a stack with %d nodes\n", n_nodes);
	for (i = 0; i < n_nodes; i++) {
		n = calloc(1, sizeof (struct node));
		n->val = rand() % MAX_VAL;
		printf("pushing %d\n", n->val);
		stack_push(&s, n);
	}

	printf("reversing the stack..\n");
	rev = stack_reverse(&s);

	while ((n = stack_pop(&rev)) != NULL) {
		printf("popped %d\n", n->val);
		free(n);
	}

	printf("creating a stack with %d nodes\n", n_nodes);
	for (i = 0; i < n_nodes; i++) {
		n = calloc(1, sizeof (struct node));
		n->val = rand() % MAX_VAL;
		printf("pushing %d\n", n->val);
		stack_push(&s, n);
	}

	printf("sorting the stack..\n");
	stack_sort(&s);

	while ((n = stack_pop(&s)) != NULL) {
		printf("popped %d\n", n->val);
		free(n);
	}

	return (0);
}
