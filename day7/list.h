#ifndef MAP_HEADER
#define MAP_HEADER

typedef struct Node {
	char key[3];
	unsigned short value;
	struct Node *next;
} node;

extern unsigned short found_value;

void add_node(node *root, node *new_node);
void print_list(node *root);
void malloc_node(node *root, char *key, unsigned short value);
void free_nodes(node *root);
unsigned short get_value(node *root, char *key);

#endif
