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

void set_node_data(node **node, const char *str) {
	if (str == NULL) 
		return;
	if (strlen(str) >= DATASIZE) {
		fprintf(stderr, "Warning: string %s truncated to %d characters\n", str, DATASIZE-1);
	}
	memset((*node)->data, 0, DATASIZE);
	strncpy((*node)->data, str, DATASIZE-1);
}

void create_add_node(node **head, const char *str, int where) {
	if (str == NULL) 
		return;
	if (strlen(str) >= DATASIZE) {
		fprintf(stderr, "Warning: string %s truncated to %d characters\n", str, DATASIZE-1);
	}

	node *new = malloc(sizeof(node));
	set_node_data(&new, str);
	new->next = NULL;

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

/* LinkedListProblems.pdf problem #1 */
int Count(node **head, const char *needle) {
	int count = 0;
	for (node *n = *head; n != NULL; n = n->next) {
		if (!strcmp(n->data, needle))
			count++;
	}

	return count;
}

size_t Length(node **head) {
	size_t len = 0;
	for (node *n = *head; n != NULL; n = n->next)
		len++;

	return len;
}

/* LinkedListProblems.pdf problem #2 */
char *GetNth(node **head, int index) {
	int i=0;
	for (node *n = *head; n != NULL; n = n->next, i++) {
		if (index == i)
			return strdup(n->data);
	}
	return NULL;
}

/* LinkedListProblem.pdf problem #3, although I started writing this before finding that file */
void free_list(node **head) {
	node *cur = *head;
	node *next;
	while (cur != NULL) {
		printf("About to free node \"%s\", next = %p\n", cur->data, cur->next);
		next = cur->next;
		free(cur);
		cur = next;
	}

	*head = NULL;
}

/* LinkedListProblems.pdf problem #4 */
char *Pop(node **head) {
	if (Length(head) == 0)
		return NULL;
	
	node *new_head = (*head)->next;
	char *data = strdup((*head)->data);
	free(*head);
	*head = new_head; /* No special case needed for NULL */

	return data;
}

int main() {
	node *list = calloc(1, sizeof(node));
	printf("Length after allocating: %zu\n", Length(&list));
	set_node_data(&list, "Alpha");
	printf("Length after adding 1 element: %zu\n", Length(&list));

	create_add_node(&list, "Beta", START);
	create_add_node(&list, "Gamma", END);
	create_add_node(&list, "Omega", START);
	create_add_node(&list, "Alpha", END);

	printf("Length with 5 elements: %zu\n", Length(&list));

	print_list(&list);

	printf("Count(Alpha): %d\n", Count(&list, "Alpha"));
	printf("Count(Omega): %d\n", Count(&list, "Omega"));
	printf("Count(Delta): %d\n", Count(&list, "Delta"));

	/* Note: These leak, as the caller is responsible for freeing the memory. */
//	printf("GetNth(0): %s\n", GetNth(&list, 0));
//	printf("GetNth(2): %s\n", GetNth(&list, 2));
//	printf("GetNth(20): %s\n", GetNth(&list, 20));
//

	for (int i=0; i<3; i++) {
		char *s = Pop(&list);
		printf("Pop: %s\n", s);
		printf("New length: %zu\n", Length(&list));
		free(s);
	}

	free_list(&list);
	printf("Length after freeing: %zu\n", Length(&list));
	return 0;
}
