#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"list.h"

unsigned short found_value = 0;

void add_node(node *root, node *new_node)
{
	if (root == NULL) {
		return;
	}
	while (root->next != NULL) {
		if (strcmp(root->key, new_node->key) == 0) {
			root->value = new_node->value;
			return;
		}
		root = root->next;
	}
	if (strcmp(root->key, new_node->key) == 0) {
		root->value = new_node->value;
		return;
	}
	root->next = new_node;
}

void print_list(node *root)
{
	while (root != NULL) {
		root = root->next;
	}
}

void malloc_node(node *root, char *key, unsigned short value)
{
	node *n = malloc(sizeof(node));
	strcpy(n->key, key);
	n->value = value;
	add_node(root, n);
}

void free_nodes(node *root)
{
	node *next;
	while (root->next != NULL) {
		next = root->next;
		// printf("freeing node: %s\n", root->key);
		free(root);
		root = next;
	}
	// printf("freeing node: %s\n", root->key);
	free(root);
}

unsigned short get_value(node *root, char *key)
{
	while (root != NULL) {
		if (strcmp(root->key, key) == 0) {
			found_value = 1;
			return root->value;
		}
		root = root->next;
	}
	found_value = 0;
	return 0;
}

// int main() {
//      node *root = malloc(sizeof(node));
//      strcpy(root->key, "ab");
//      root->value = 12;
//
//      node *n = malloc_node("ca", 9);
//      add_node(root, n);
//
//      printf("%hu\n", get_value(root, "ca"));
//      if (found_value) {
//              printf("Value was found\n");
//      } else {
//              printf("Value was NOT found\n");
//      }
//
//      print_list(root);
//      free_nodes(root);
// }
