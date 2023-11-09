#include"parts.h"

#include<stdio.h>
#include<unistd.h>

#define SCOPES 1000

char is_in(char ch, char *chars)
{
	char *c = chars;
	while (*c != '\0') {
		if (*c == ch) {
			return 1;
		}
		c++;
	}
	return 0;
}

int main()
{
	char buffer[SIZE] = { 0 };
	char *b = buffer;
	char ch;

	while (read(STDIN_FILENO, &ch, 1) > 0) {
		*b++ = ch;
	}

	printf("Part 1: %d\n", part1(buffer));
	printf("Part 2: %d\n", part2(buffer));
}
