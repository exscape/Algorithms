#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <gmp.h>

/* Written: 2009-10-29, XXX */

typedef struct _node {
	struct _node *next;
	mpz_t num;
} node;

void add_node(node *head, node *new) {
	node *n;
	for (n = head; n->next != NULL; n = n->next)
		;
	n->next = new;
}

void create_add_node(node *head, const mpz_t num) {
	if (num == NULL)
		return;
	node *new = calloc(1, sizeof(node));
	mpz_init(new->num);
	mpz_set(new->num, num);
	new->next = NULL; /* not necessary with calloc, but it looks wrong to omit it. */
	add_node(head, new);
}

void print_list(node *head) {
	for (node *n = head; n != NULL; n = n->next) {
		gmp_printf("%Zd\n", n->num);
	}
}

void free_list(node *head) {
/*
	node *n = head;
	while ((n = n->next) != NULL) {
		mpz_clear(n->next->num);
		free(n->next);
	}
	mpz_clear(head->num);
	free(head);
*/
}

int main() {
	node *list = calloc(1, sizeof(node));
	mpz_t i;
	mpz_init_set_ui(i, 1000);
	mpz_set(list->num, i); // XXX: Wrapper function!

	mpz_mul_ui(i, i, 10);
	create_add_node(list, i);
	mpz_mul_ui(i, i, 10);
	create_add_node(list, i);
	mpz_mul_ui(i, i, 10);
	create_add_node(list, i);

	print_list(list);

	free_list(list);

	return 0;
}
