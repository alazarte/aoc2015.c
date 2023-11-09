#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<limits.h>
#include<string.h>
#include"list.h"

node *root;

void cleanup(char *arr, char c, int n)
{
	for (int i = 0; i < n; i++) {
		arr[i] = c;
	}
}

void clean(char *buffer, int size)
{
	for (int i = 0; i < size; i++) {
		buffer[i] = '\0';
	}
}

char isnum(char c)
{
	return c >= '0' && c <= '9';
}

void compute(char *first_part, char *second_part, char *third_part,
	     char *fourth_part, char *fifth_part)
{
	unsigned short first = 0, second = 0, third = 0;

	// NOT a -> b
	if (strcmp(first_part, "NOT") == 0) {
		if (isnum(second_part[0])) {
			second = atoi(second_part);
		} else {
			second = get_value(root, second_part);
			if (found_value == 0) {
				return;
			}
		}

		malloc_node(root, fourth_part, ~second);
		return;
	}

	if (isnum(first_part[0])) {
		first = atoi(first_part);
	} else {
		first = get_value(root, first_part);
		if (found_value == 0) {
			return;
		}
	}

	// 5 -> b
	if (strcmp(second_part, "->") == 0) {
		malloc_node(root, third_part, first);
		return;
	}
	// a AND b -> c
	if (isnum(third_part[0])) {
		third = atoi(third_part);
	} else {
		third = get_value(root, third_part);
		if (found_value == 0) {
			return;
		}
	}

	if (strcmp(second_part, "AND") == 0) {
		malloc_node(root, fifth_part, first & third);
		return;
	}

	if (strcmp(second_part, "OR") == 0) {
		malloc_node(root, fifth_part, first | third);
		return;
	}

	if (strcmp(second_part, "RSHIFT") == 0) {
		malloc_node(root, fifth_part, first >> third);
		return;
	}

	if (strcmp(second_part, "LSHIFT") == 0) {
		malloc_node(root, fifth_part, first << third);
		return;
	}
}

void parse_line(char *line)
{
	char *l = line;
	char parts[5][100] = { '\0' };
	int part_n = 0, aux_s = 0;

	while (*l != '\0') {
		if (*l == ' ') {
			part_n++;
			aux_s = 0;
			l++;
			continue;
		}

		parts[part_n][aux_s++] = *l;
		l++;
	}

	compute(parts[0], parts[1], parts[2], parts[3], parts[4]);

	for (int i = 0; i < 5; i++) {
		clean(parts[i], 100);
	}
}

int main()
{
	root = malloc(sizeof(node));
	root->next = NULL;

	char buffer[500][100] = { '\0' };
	int buffer_i = 0;
	char *b = buffer[0];
	char ch;

	while (read(STDIN_FILENO, &ch, 1) > 0) {
		if (ch == '\n') {
			buffer_i++;
			b = buffer[buffer_i];
			continue;
		}
		*b++ = ch;
	}

	char found_a = 0;
	unsigned short initial_a = 0;
	while (found_a < 2) {
		for (int i = 0; i < 500; i++) {
			get_value(root, "a");
			if (found_value == 1) {
				printf("Part %d: ", found_a+1);
				printf("a=%hu ", get_value(root, "a"));
				printf("b=%hu\n", get_value(root, "b"));

				initial_a = get_value(root, "a");
				found_a++;

				free_nodes(root);
				root = malloc(sizeof(node));
				root->next = NULL;

				break;
			}

			if (buffer[i][0] == '\0') {
				i = 0;
				break;
			}

			print_list(root);
			parse_line(buffer[i]);
			if (initial_a != 0) {
				malloc_node(root, "b", initial_a);
			}
		}
	}

	free_nodes(root);
}
