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

uint8_t in_list(node *head, const mpz_t num) {
	for (node *n = head; n != NULL; n = n->next) {
		if (mpz_cmp(n->num, num) == 0)
			return 1;
	}
	return 0;
}

void create_add_node(node *head, const mpz_t num) {
	if (num == NULL)
		return;
	if (in_list(head, num))
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

size_t list_length(node *head) {
	size_t len = 0;
	for (node *n = head; n != NULL; n = n->next)
		len++;
	return len;
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

void head_set_num(node *head, mpz_t num) {
	mpz_init(head->num);
	mpz_set(head->num, num);
}

int main() {
	node *list = calloc(1, sizeof(node));
	mpz_t i;
	mpz_init_set_ui(i, 2*2); // a^b where a or b = 2
	head_set_num(list, i);

	for (int a=2; a <= 100; a++) {
		for (int b=2; b <= 100; b++) {
			mpz_ui_pow_ui(i, a, b);
			create_add_node(list, i);
		}
	}

	printf("list has %zu elements\n", list_length(list));

	free_list(list);

	return 0;
}
