#include<stdio.h>
#include<unistd.h>
#include<string.h>

// TODO maybe join the two together as both have a loop through the string
char contains_distinct(char *line, char *any, int amount)
{
	char *l = line;

	char any_str[strlen(any) + 1];
	strcpy(any_str, any);
	char *ap = any_str;
	char pair_found = 0;
	char last = '\0';
	char valid_line = 1;

	int found = 0;

	while (*l != '\0') {
		if (!pair_found && last != '\0' && last == *l)
			pair_found = 1;

		if ((last == 'a' && *l == 'b') ||
		    (last == 'c' && *l == 'd') ||
		    (last == 'p' && *l == 'q') || (last == 'x' && *l == 'y'))
			valid_line = 0;

		while ((found != amount) && *ap != '\0') {
			if (*l == *ap) {
				found++;
				if (found == amount)
					break;
			}
			ap++;
		}

		last = *l;
		l++;
		ap = any_str;
	}

	return (found == amount) && pair_found && valid_line;
}

char search_pairs_and_between(char *string)
{
	char *p = string;
	char *s = (p + 2);
	char pair_found = 0;
	char between = 0;

	while (*(p + 1) != '\0') {
		while (*(s + 1) != '\0') {
			if (*p == *s && *(p + 1) == *(s + 1)) {
				pair_found = 1;
			}
			s++;
		}
		if (*p == *(p + 2)) {
			between = 1;
		}
		if (pair_found && between)
			return 1;
		p++;
		s = (p + 2);
	}

	return pair_found && between;
}

int main()
{
	char line[1000];
	char *l = line;
	char ch;
	int part1 = 0, part2 = 0;

	while (read(STDIN_FILENO, &ch, 1) > 0) {
		if (ch == '\n') {
			*l = '\0';

			if (search_pairs_and_between(line)) {
				part2++;
			}

			if (contains_distinct(line, "aeiou", 3)) {
				part1++;
			}

			l = line;
		}
		if (ch >= 'a' && ch <= 'z')
			*l++ = ch;
	}

	printf("Part 1: %d\nPart 2: %d\n", part1, part2);
}
