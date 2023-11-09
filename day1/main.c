#include<stdio.h>
#include<unistd.h>

int main()
{
	int pos = 0, enter_pos = -1;
	short floor = 0;

	char ch;
	while (read(STDIN_FILENO, &ch, 1) > 0) {
		switch (ch) {
		case '(':
			floor++;
			break;
		case ')':
			floor--;
			break;
		}
		pos++;
		if (enter_pos == -1 && floor == -1) {
			enter_pos = pos;
		}
	}

	printf("Part 1: %d\n", floor);
	printf("Part 2: %d\n", enter_pos);
}
