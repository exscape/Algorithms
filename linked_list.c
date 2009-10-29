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

enum _where {
	START = 0,
	END = 1
};

void create_add_node(node **head, const char *str, int where) {
	if (str == NULL) 
		return;
	if (strlen(str) >= DATASIZE) {
		fprintf(stderr, "Warning: string %s truncated to %d characters\n", str, DATASIZE-1);
	}

	node *new = calloc(1, sizeof(node));
	strncpy(new->data, str, DATASIZE-1);

	if (where == START) {
		new->next = *head;
		*head = new;
	}
	else if (where == END) {
		node *n;
		for (n = *head; n->next != NULL; n = n->next)
			;
		n->next = new;
	}
	else {
		fprintf(stderr, "Error: invalid \"where\" value specificed for create_add_node\n");
		exit(1);
	}
}

void print_list(node **head) {
	for (node *n = *head; n != NULL; n = n->next) {
		printf("%s\n", n->data);
	}
}

void free_list(node **head) {
	// XXX: FIXME!
	node *n = *head;
	while ((n = n->next) != NULL) {
		free(n->next);
	}
	free(*head); *head = NULL;
}

void set_node_data(node **node, const char *str) {
	// XXX: DRY?
	if (str == NULL) 
		return;
	if (strlen(str) >= DATASIZE) {
		fprintf(stderr, "Warning: string %s truncated to %d characters\n", str, DATASIZE-1);
	}
	memset((*node)->data, 0, DATASIZE);
	strncpy((*node)->data, str, DATASIZE-1);
}

int main() {
	node *list = calloc(1, sizeof(node));
	set_node_data(&list, "Alpha (start)");

	create_add_node(&list, "Beta (start)", START);
	create_add_node(&list, "Gamma (end)", END);
	create_add_node(&list, "Omega (start)", START);

	print_list(&list);

	free_list(&list);
	return 0;
}
