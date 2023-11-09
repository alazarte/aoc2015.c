#include<stdio.h>
#include<unistd.h>

int main()
{
	char ch, last = '\0';
	int counter = 0;

	while (read(STDIN_FILENO, &ch, 1) > 0) {
		if (last == '\0') {
			last = ch;
		}

		if (ch < '0' || ch > '9') {
			break;
		}

		if (ch == last) {
			counter++;
		} else {
			printf("%d%c", counter, last);
			last = ch;
			counter = 1;
		}
	}
	printf("%d%c\n", counter, last);
}
