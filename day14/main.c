#include<stdio.h>
#include<unistd.h>

typedef struct TravelInfo {
	int total_seconds;
	int moving_seconds;
	int rest_seconds;
	int kmps;
} speed_info;

int kms_travel(speed_info deer, int total_seconds)
{
	int current_seconds = 0;
	int km_done = 0;
	while (current_seconds < total_seconds) {
		current_seconds += deer.moving_seconds;
		km_done += deer.kmps * deer.moving_seconds;
		current_seconds += deer.rest_seconds;
	}
	return km_done;
}

int main()
{
	int numbers[3];
	int numbers_index = 0;
	int current_number = 0;
	int deer_index = 0;
	char ch;
	speed_info deers[10];

	while (read(STDIN_FILENO, &ch, 1) > 0) {
		if ('0' <= ch && ch <= '9') {
			current_number = (current_number * 10) + (ch - '0');
		} else if (ch == '\n') {
			deers[deer_index].kmps = numbers[0];
			deers[deer_index].moving_seconds = numbers[1];
			deers[deer_index].rest_seconds = numbers[2];
			deer_index++;
			numbers_index = 0;
		} else if (current_number != 0) {
			numbers[numbers_index++] = current_number;
			current_number = 0;
		}
	}

	int max_kms = 0;
	for (int i=0; i<10; i++) {
		int current_kms = kms_travel(deers[i], 2503);
		if (current_kms > max_kms) {
			max_kms = current_kms;
		}
	}
	printf("Part 1: %d\n", max_kms);
}
