#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"header.h"

void add_string(Strings *strings, char *string)
{
	for (size_t i = 0; i < strings->count; i++) {
		if (strcmp(string, strings->items[i].string) == 0)
			return;
	}
	strcpy(strings->items[strings->count].string, string);
	strings->count++;
}

size_t replace_substr(char *final, char *input, char *replace, char *with,
		      size_t which)
{
	ssize_t index = find_substr_index(input, replace, which);
	if (index == -1)
		return 0;
	size_t replace_len = strlen(replace);
	size_t with_len = strlen(with);
	scpy_upto(final, input, index);
	scpy_from(final, with, index);
	scpy_from(final, (input + index + replace_len), index + with_len);

	return 1;
}

size_t count_elements(char *input, Compare compares[3])
{
	char *i = input;
	size_t elements = 0;

	while (*input != '\0') {
		// Rn Ar Y
		if (*input >= 'A' && *input <= 'Z')
			elements++;
		for (int j = 0; j < 3; j++) {
			char *c = compares[j].compare;
			while (*i != '\0' && *i == *c) {
				i++;
				c++;
			}
			if (*c == '\0') {
				compares[j].found++;
			}
			i = input;
		}
		input++;
	}

	return elements - compares[0].found - compares[1].found -
	    (2 * compares[2].found) - 1;
}

int main()
{
	char input[500] = { 0 };
	char final[STRING_LEN] = { 0 };

	Replaces replaces;
	replaces.count = 0;
	replaces.cap = ITEMS_CAP;
	replaces.items = malloc(sizeof(Replace) * replaces.cap);

	parse_input(&replaces, input);

	Compare compares[] = {
		{"Rn", 0},
		{"Ar", 0},
		{"Y", 0},
	};

	size_t elements = count_elements(input, compares);

	Strings strings;
	strings.count = 0;
	strings.cap = ITEMS_CAP;
	strings.items = malloc(sizeof(String) * strings.cap);

	for (size_t i = 0; i < replaces.count; i++) {
		Replace r = replaces.items[i];
		size_t which = 1;
		while (replace_substr(final, input, r.replace, r.with, which++)) {
			add_string(&strings, final);
		}
	}

	printf("Part 1: %ld\n", strings.count);
	printf("Part 2: %ld\n", elements);

	free(replaces.items);
	free(strings.items);
}
