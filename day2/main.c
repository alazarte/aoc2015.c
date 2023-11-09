#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int max(int a, int b)
{
	if (a < b) {
		return b;
	}
	return a;
}

int min(int a, int b)
{
	if (a < b) {
		return a;
	}
	return b;
}

int main()
{
	char ch;
	char number[5];
	char *n = number;

	int box_i = 0;
	int l, w, h;
	int *box[3] = { &l, &w, &h };
	int total = 0;
	int ribbon = 0;

	while (read(STDIN_FILENO, &ch, 1) > 0) {
		if (ch >= '0' && ch <= '9') {
			*n++ = ch;
			continue;
		}
		*n = '\0';
		*box[box_i++] = atoi(number);

		n = number;
		if (box_i < 3) {
			continue;
		}

		int min1 = min(l, w);
		int min2 = min(max(l, w), h);

		int slack = min1 * min2;
		ribbon += 2 * min1 + 2 * min2 + (l * w * h);

		int a = (2 * l * w) + (2 * w * h) + (2 * h * l);
		total += (a + slack);
		box_i = 0;
		continue;
	}

	printf("Part 1: %d\nPart 2: %d\n", total, ribbon);

	return 0;
}
