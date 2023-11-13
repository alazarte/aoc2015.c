#include<stdio.h>
#include<unistd.h>
#include<string.h>

char search_substring(char *in, char *sub, int to_compare)
{
	char *s = sub;
	int n = to_compare;

	while (*in != '\0' && *in != *s)
		in++;

	if (*in == '\0') {
		return -1;
	}

	while (*in++ == *s++ && --n > 0) ;

	if (n == 0)
		return 1;

	return search_substring(in, sub, to_compare);
}

void parse_seat_info(size_t size, int seat_info[100][size])
{
	char buffer[100];
	char *b = buffer;
	char ch;
	int n = 0;

	size_t current_person = 0;
	size_t other_person = 0;

	while (read(STDIN_FILENO, &ch, 1) > 0) {
		if (ch == '\n') {
			if (other_person == size) {
				current_person++;
				other_person = 0;
			}

			if (current_person == other_person) {
				seat_info[current_person][other_person] = 0;
				other_person++;
			}

			char gain = search_substring(buffer, "gain", 4);
			seat_info[current_person][other_person] = n * gain;
			other_person++;

			*b = '\0';
			b = buffer;
			n = 0;
			continue;
		}

		*b++ = ch;
		if (ch >= '0' && ch <= '9') {
			n = (n * 10) + (ch - '0');
		}
	}
}

int happiness(size_t size, int seat_info[100][size], int pos[size])
{
	int happ = 0;
	int left = 0, right = 0;

	for (size_t i = 0; i < size; i++) {
		if (i == 0) {
			left = pos[size - 1];
		} else {
			left = pos[i - 1];
		}

		if (i == (size - 1)) {
			right = pos[0];
		} else {
			right = pos[i + 1];
		}

		happ += seat_info[pos[i]][left];
		happ += seat_info[pos[i]][right];
	}
	return happ;
}

char is_sitting(size_t size, int value, int position[size], int sitting)
{
	for (int i = 0; i < sitting; i++) {
		if (position[i] == value)
			return 1;
	}
	return 0;
}

int sit(size_t size, int seat_info[100][size], int values[size],
	int position[size], size_t sitting)
{
	int max_happ = 0;
	if (sitting == size) {
		int happ = happiness(size, seat_info, position);
		if (max_happ < happ) {
			max_happ = happ;
		}
		return max_happ;
	}
	for (size_t i = 0; i < size; i++) {
		if (is_sitting(size, values[i], position, sitting))
			continue;
		position[sitting] = values[i];
		int happ = sit(size, seat_info, values, position, sitting + 1);
		if (max_happ < happ) {
			max_happ = happ;
		}
	}
	return max_happ;
}

size_t parse_n(char *s)
{
	size_t n = 0;
	while (*s != '\0') {
		n = (n * 10) + (*s - '0');
		s++;
	}
	return n;
}

int main(int argc, char **argv)
{
	size_t size = 0;
	if (argc < 2) {
		printf("How many people?\n");
		return 1;
	}

	size = parse_n(argv[1]);

	int pos[size];
	for(size_t i; i<size; i++) {
		pos[i] = 0;
	}

	int seat_info[100][size];
	for(size_t i; i<100; i++) {
		for(size_t j; j<size; j++) {
			seat_info[i][j] = 0;
		}
	}
	parse_seat_info(size, seat_info);

	int initial_pos[size];
	for (size_t i = 0; i < size; i++) {
		initial_pos[i] = i;
	}

	int max_happ = sit(size, seat_info, initial_pos, pos, 0);
	printf("%d\n", max_happ);
}
