/*
 * https://github.com/rafaelvanoni/C.git
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>

#define	MIN_NODES	(3)
#define	MAX_NODES	(8)
#define	MAX_VAL		(10)

struct node {
	int		val;
	struct node	*l;
	struct node	*r;
};

void
bt_pretty_print(struct node *t, int pad)
{
	if (t == NULL) {
		return;
	}

	bt_pretty_print(t->r, pad + 5);
	printf("%*d\n", pad, t->val);
	bt_pretty_print(t->l, pad + 5);
}

void
bt_print_df_inorder(struct node *t)
{
	if (t == NULL) {
		return;
	}

	bt_print_df_inorder(t->r);
	printf("%d ", t->val);
	bt_print_df_inorder(t->l);
}

void
bt_print_df_postorder(struct node *t)
{
	if (t == NULL) {
		return;
	}

	bt_print_df_postorder(t->r);
	bt_print_df_postorder(t->l);
	printf("%d ", t->val);
}

void
bt_print_df_preorder(struct node *t)
{
	if (t == NULL) {
		return;
	}

	printf("%d ", t->val);
	bt_print_df_preorder(t->r);
	bt_print_df_preorder(t->l);
}

void
bt_add(struct node **t, struct node *x)
{
	if (*t == NULL) {
		*t = x;
	} else {
		struct node *n = *t;

		if (n->val > x->val) {
			bt_add(&n->l, x);
		} else {
			bt_add(&n->r, x);
		}
	}
}

void
bt_delete(struct node **t)
{
	struct node *n;

	if (*t == NULL) {
		return;
	}

	n = *t;
	bt_delete(&n->l);
	n->l = NULL;
	bt_delete(&n->r);
	n->r = NULL;
	free(n);
	*t = NULL;
}

int
bt_count(struct node *t)
{
	if (t == NULL) {
		return (0);
	}

	return (bt_count(t->l) + bt_count(t->r) + 1);
}

int
bt_height(struct node *t)
{
	int l, r;

	if (t == NULL) {
		return (0);
	}

	l = bt_height(t->l) + 1;
	r = bt_height(t->r) + 1;

	return (l > r ? l : r);
}

bool
bt_find_val(struct node *t, int val)
{
	if (t == NULL) {
		return (false);
	}

	if (t->val == val) {
		return (true);
	}

	bt_find_val(t->l, val);
	bt_find_val(t->r, val);

	return (false);
}

int
main(int argc, char **argv)
{
	struct node *t = NULL, *n;
	int i, n_nodes;

	srand(time(NULL));

	do {
		n_nodes = (rand() + MIN_NODES) % MAX_NODES;;
	} while (n_nodes <= MIN_NODES || n_nodes >= MAX_NODES);

	printf("creating a binary tree with %d nodes..\n", n_nodes);

	for (i = 0; i < n_nodes; i++) {
		n = calloc(1, sizeof (struct node));
		n->val = rand() % MAX_VAL;
		bt_add(&t, n);
	}

	printf("pretty printing in depth first in order..\n");
	bt_pretty_print(t, 0);

	printf("printing depth first in order..\n");
	bt_print_df_inorder(t);
	printf("\n");

	printf("printing depth first post order..\n");
	bt_print_df_postorder(t);
	printf("\n");

	printf("printing depth first pre order..\n");
	bt_print_df_preorder(t);
	printf("\n");

	printf("counting nodes..found %d\n", bt_count(t));
	printf("checking height..found %d\n", bt_height(t));

	printf("deleting the tree..\n");
	bt_delete(&t);

	printf("pretty printing in depth first in order..\n");
	bt_pretty_print(t, 0);

	return (0);
}
