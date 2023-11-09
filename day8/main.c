#include<stdio.h>
#include<unistd.h>

typedef unsigned short usint;

int main()
{
	usint added_chars = 0;
	usint all_chars = 0;
	usint chars_in_memory = 0;
	usint skip_chars = 0;
	char escaped = 0;
	char ch;
	while (read(STDIN_FILENO, &ch, 1) > 0) {
		if (ch == '\n') {
			// remove surrounding double quotes
			chars_in_memory -= 2;
			added_chars += 2;
			continue;
		}

		all_chars++;

		if (skip_chars > 0) {
			skip_chars--;
			continue;
		}

		if (escaped && ch == 'x') {
			escaped = 0;
			skip_chars = 1;
			continue;
		}

		if (ch == '"') {
			added_chars += 1;
		}

		if (ch == '\\') {
			added_chars += 1;
			if (!escaped) {
				escaped = 1;
				continue;
			}
		}
		escaped = 0;

		chars_in_memory++;
	}
	printf("Part 1: %d\n", all_chars - chars_in_memory);
	printf("Part 2: %d\n", added_chars);
}
