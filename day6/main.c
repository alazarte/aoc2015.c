#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#define LIGHTS_ROW 1000

int main()
{
	char grid_1[LIGHTS_ROW][LIGHTS_ROW] = { 0 };
	char grid_2[LIGHTS_ROW][LIGHTS_ROW] = { 0 };
	int sum_1 = 0, sum_2 = 0;

	char line[50];
	char *l = line;
	char ch;
	int y1, y2, x1, x2;
	char command[10];

	while (read(STDIN_FILENO, &ch, 1) > 0) {
		if (ch != '\n') {
			*l++ = ch;
			continue;
		}
		*l = '\0';
		l = line;

		sscanf(line, "%10[a-z ] %d,%d through %d, %d\n", command,
		       &x1, &y1, &x2, &y2);

		for (int x = x1; x <= x2; x++) {
			for (int y = y1; y <= y2; y++) {
				if (strcmp(command, "turn on ") == 0) {
					grid_1[x][y] = 1;
					grid_2[x][y] += 1;
				} else if (strcmp(command, "turn off ") == 0) {
					if (grid_2[x][y] == 0) {
						continue;
					}
					grid_1[x][y] = 0;
					grid_2[x][y] -= 1;
				} else {
					grid_1[x][y] = !grid_1[x][y];
					grid_2[x][y] += 2;
				}
			}
		}

	}

	for (int i = 0; i < LIGHTS_ROW; i++) {
		for (int j = 0; j < LIGHTS_ROW; j++) {
			if (grid_2[i][j]) {
				sum_2 += grid_2[i][j];
			}
			if (grid_1[i][j]) {
				sum_1++;
			}
		}
	}

	printf("Part1: %d\nPart2: %d\n", sum_1, sum_2);
}
