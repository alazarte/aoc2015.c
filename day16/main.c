#include<stdio.h>
#include<unistd.h>
#include"hash.c"

void print_sue(int index_numbers[4], int numbers[4], int original_stats[10])
{
	int checks = 0;
	int part_2_sue = 0;
	for (int i = 1; i < 4; i++) {
		if (index_numbers[i] == 1 || index_numbers[i] == 7) {
			if (original_stats[index_numbers[i]] < numbers[i])
				checks++;
		}
		if (index_numbers[i] == 3 || index_numbers[i] == 6) {
			if (original_stats[index_numbers[i]] > numbers[i]) {
				checks++;
				part_2_sue = 1;
			}
		}
		if (original_stats[index_numbers[i]] == numbers[i])
			checks++;
	}

	if (checks == 3) {
		if (part_2_sue == 1) {
			printf("Part 2: %d\n", numbers[0]);
		} else {
			printf("Part 1: %d\n", numbers[0]);
		}
	}
}

int main()
{
	int original_stats[10] = { 3, 7, 2, 3, 0, 0, 5, 3, 2, 1 };
	char ch;
	char buffer[100] = { 0 };
	char *b = buffer;
	int numbers[4] = { 0 };
	int index_numbers[4] = { 0 };
	char parsing_number = 0;
	int current_index = 0;

	while (read(STDIN_FILENO, &ch, 1) > 0) {
		if (ch == ' ' || ch == '\n') {
			*b = '\0';
			b = buffer;

			int index = hash(buffer);
			if (index != -1) {
				index_numbers[current_index] = index;
			}
			if (parsing_number) {
				current_index++;
				parsing_number = 0;
			}
			if (current_index == 4) {
				print_sue(index_numbers, numbers,
					  original_stats);
				for (int i = 0; i < 4; i++) {
					numbers[i] = 0;
					index_numbers[i] = 0;
				}
				current_index = 0;
			}
		}
		if ('a' <= ch && ch <= 'z') {
			*b++ = ch;
			continue;
		}
		if ('0' <= ch && ch <= '9') {
			parsing_number = 1;
			numbers[current_index] *= 10;
			numbers[current_index] += (ch - '0');
		}
	}
}
