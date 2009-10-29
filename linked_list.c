#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/* Written: 2009-10-29, XXX */

#define DATASIZE 16

typedef struct _node {
	struct _node *next;
	char data[DATASIZE];
} node;

void add_node(node *head, node *new) {
	node *n;
	for (n = head; n->next != NULL; n = n->next)
		;
	n->next = new;
}

void create_add_node(node *head, const char *str) {
	if (str == NULL) 
		return;
	if (strlen(str) >= DATASIZE) {
		fprintf(stderr, "Warning: string %s truncated to %d characters\n", str, DATASIZE-1);
	}
	node *new = malloc(sizeof(node));
	memset(new->data, 0, DATASIZE);
	strncpy(new->data, str, DATASIZE-1);
	new->next = NULL;
	add_node(head, new);
}

void print_list(node *head) {
	for (node *n = head; n != NULL; n = n->next) {
		printf("%s\n", n->data);
	}
}

int main() {
	node *head = malloc(sizeof(node));
	strcpy(head->data, "Alpha");

	node *node2 = malloc(sizeof(node));
	strcpy(node2->data, "Beta");
	add_node(head, node2);

	create_add_node(head, "Gamma");
	create_add_node(head, "Omega");

	print_list(head);

	return 0;
}
