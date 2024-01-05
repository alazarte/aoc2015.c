#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include"header.h"

void add_replace(Replaces *replaces, char *replace, char *with)
{
	strcpy(replaces->items[replaces->count].replace, replace);
	strcpy(replaces->items[replaces->count].with, with);
	replaces->count++;
}

void parse_input(Replaces *replaces, char input[500])
{
	char buffer[500] = { 0 };
	char *b = buffer;
	int line = 0;
	char next_line_input = 0;

	while (read(STDIN_FILENO, b, 1) > 0) {
		if (*b == '\n') {
			*b = '\0';
			if (strcmp(buffer, "") == 0) {
				next_line_input = 1;
			} else if (next_line_input == 1) {
				strcpy(input, buffer);
			} else {
				char *replace_str = strtok(buffer, " => ");
				char *replace_with = strtok(NULL, " => ");
				add_replace(replaces, replace_str, replace_with);
			}
			memset(buffer, '\0', 500);
			b = buffer;
			continue;
		}
		b++;
	}
}
