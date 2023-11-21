#include<stdio.h>
#include<unistd.h>

#define TOTAL 4
#define STATS 5

int ingredients[TOTAL][STATS] = { 0 };

void read_input()
{
	char ch, parsing_number = 0, negative_modifier = 1;
	int current_number = 0, index_ing = 0, index_stat = 0;

	while (read(STDIN_FILENO, &ch, 1) > 0) {
		if ('0' <= ch && ch <= '9') {
			current_number = (current_number * 10) + (ch - '0');
			parsing_number = 1;
		}
		// considering there's no dash in any other part of the input
		if (ch == '-') {
			negative_modifier = -1;
		}

		if (parsing_number && (ch == ' ' || ch == '\n')) {
			ingredients[index_ing][index_stat++] =
			    current_number * negative_modifier;
			current_number = 0;
			parsing_number = 0;
			negative_modifier = 1;
		}

		if (ch == '\n') {
			index_stat = 0;
			index_ing++;
		}
	}
}
