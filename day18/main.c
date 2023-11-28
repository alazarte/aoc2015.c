#include<stdio.h>
#include<unistd.h>

#define SIZE 100
#define STEPS 100

int on_neighbors(char table[SIZE][SIZE], int x, int y)
{
	int are_on = 0;
	for (int i = y - 1; i <= y + 1; i++) {
		if (i < 0 || i >= SIZE)
			continue;
		for (int j = x - 1; j <= x + 1; j++) {
			if (i == y && j == x)
				continue;
			if (j < 0 || j >= SIZE)
				continue;
			if (table[i][j] == '#')
				are_on++;
		}
	}
	return are_on;
}

void step(char table[SIZE][SIZE], char new_table[SIZE][SIZE],
	  char stuck_on_corners)
{
	for (int i = 0; i < SIZE; i++) {
		int j_from = 0;
		int j_to = SIZE;
		if (stuck_on_corners) {
			if (i == 0 || i == (SIZE - 1)) {
				j_from = 1;
				j_to = SIZE - 1;
			}
		}

		for (int j = j_from; j < j_to; j++) {
			int on = on_neighbors(table, j, i);
			if (table[i][j] == '#') {
				if (on < 2 || on > 3)
					new_table[i][j] = '.';
			} else {
				// TODO other condition
				if (on == 3)
					new_table[i][j] = '#';
			}
		}
	}
}

int count_lights(char table[SIZE][SIZE])
{
	int lights = 0;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (table[i][j] == '#')
				lights++;
		}
	}
	return lights;
}

void copy(char table[SIZE][SIZE], char new_table[SIZE][SIZE])
{
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			table[i][j] = new_table[i][j];
		}
	}
}

void print_table(char table[SIZE][SIZE])
{
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			printf("%c ", table[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int main()
{
	int row = 0;
	int col = 0;
	char ch;
	char table[SIZE][SIZE] = { 0 };
	char original_table[SIZE][SIZE] = { 0 };
	char new_table[SIZE][SIZE] = { 0 };
	while (read(STDIN_FILENO, &ch, 1) > 0) {
		if (ch == '\n') {
			row++;
			col = 0;
		}
		if (ch == '.' || ch == '#') {
			table[row][col] = ch;
			col++;
		}
	}

	copy(new_table, table);
	copy(original_table, table);

	for (int j = 0; j < STEPS; j++) {
		step(table, new_table, 0);
		copy(table, new_table);
	}

	printf("Part 1: %d\n", count_lights(table));

	copy(table, original_table);
	copy(new_table, original_table);

	for (int j = 0; j < STEPS; j++) {
		step(table, new_table, 1);
		copy(table, new_table);
	}

	printf("Part 2: %d\n", count_lights(table));
}
