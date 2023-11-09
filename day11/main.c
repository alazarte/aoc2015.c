#include<stdio.h>
#include<unistd.h>
#include<string.h>

char charin(char *in, char c)
{
	while (*in != '\0') {
		if (c == *in) {
			return 1;
		}
		in++;
	}
	return 0;
}

void increase(char *s)
{
	char ch;
	while (*s != '\0')
		s++;
	s--;
	while (*s == 'z') {
		*s = 'a';
		s--;
	}
	if (*s == '\0') {
		return;
	}
	ch = *s;
	*s = (ch + 1);
}

int main(int argn, char **argv)
{
	if (argn < 2) {
		printf("Provide password to rotate\n");
		return 1;
	}

	char *input = argv[1];
	char *i = input;
	char last = *input;
	char three_increasing = 1;
	char pairs = -1;
	char valid_letters = 1;
	char skip_over = 0;

	increase(input);
	for (;;) {
		i = input;
		last = '\0';
		three_increasing = 1;
		pairs = 0;
		valid_letters = 1;

		while (*i != '\0') {
			if (three_increasing != 3) {
				if (*i == (last + 1)) {
					three_increasing++;
				} else {
					three_increasing = 1;
				}
			}

			if (!skip_over && *i == last) {
				// printf("%c == %c\n", *i, last);
				pairs++;
				skip_over = 1;
			} else {
				skip_over = 0;
			}

			if (charin("iol", *i)) {
				valid_letters = 0;
			}

			last = *i;
			i++;
		}
		if (three_increasing == 3 && pairs == 2 && valid_letters == 1) {
			break;
		}
		increase(input);
	}
	printf("%s\n", input);

	return 0;
}
