#include<stdio.h>
#include<unistd.h>
#include"read.h"

recipient recipients[RECIPIENTS] = { 0 };

void sort(int numbers[RECIPIENTS])
{
	char swapped = 1;
	while (swapped) {
		swapped = 0;
		for (int i = 0; i < RECIPIENTS - 1; i++) {
			if (numbers[i] < numbers[i + 1]) {
				int aux = numbers[i];
				numbers[i] = numbers[i + 1];
				numbers[i + 1] = aux;
				swapped = 1;
			}
		}
		for (int i = RECIPIENTS - 1; i > 0; i--) {
			if (numbers[i] > numbers[i - 1]) {
				int aux = numbers[i];
				numbers[i] = numbers[i - 1];
				numbers[i - 1] = aux;
				swapped = 1;
			}
		}
	}
}

void read_input()
{
	char ch;
	int index_number = 0;
	int current_number = 0;
	int numbers[RECIPIENTS] = { 0 };

	while (read(STDIN_FILENO, &ch, 1) > 0) {
		if (ch == '\n') {
			numbers[index_number++] = current_number;
			current_number = 0;
		}
		if ('0' <= ch && ch <= '9') {
			current_number = (current_number * 10) + (ch - '0');
		}
	}

	sort(numbers);
	for (int i = 0; i < RECIPIENTS; i++) {
		recipients[i].cap = numbers[i];
		recipients[i].full = 0;
	}
}
