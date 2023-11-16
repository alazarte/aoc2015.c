#include<stdio.h>
#include<unistd.h>

typedef struct SpeedInfo {
	int total_moving_seconds;
	int total_rest_seconds;
	int kmps;

	int remaining_moving_seconds;
	int remaining_rest_seconds;
	char rested;
	int points;
	int distance_covered;
} speed_info;


int main()
{
	int numbers[3];
	int numbers_index = 0;
	int current_number = 0;
	int deer_index = 0;
	char ch;
	int total_seconds = 2503;
	speed_info deers[9];

	while (read(STDIN_FILENO, &ch, 1) > 0) {
		if ('0' <= ch && ch <= '9') {
			current_number = (current_number * 10) + (ch - '0');
		} else if (ch == '\n') {
			deers[deer_index].kmps = numbers[0];
			deers[deer_index].total_moving_seconds = numbers[1];
			deers[deer_index].total_rest_seconds = numbers[2];
			deers[deer_index].remaining_moving_seconds = numbers[1];
			deers[deer_index].remaining_rest_seconds = 0;
			deers[deer_index].rested = 0;
			deers[deer_index].points = 0;
			deers[deer_index].distance_covered = 0;
			deer_index++;
			numbers_index = 0;
		} else if (current_number != 0) {
			numbers[numbers_index++] = current_number;
			current_number = 0;
		}
	}

	int winning_index = -1;
	int largest_distance = 0;
	for(int second=0; second<=total_seconds; second++) {
		for(int deer_index=0; deer_index<9; deer_index++) {
			if (largest_distance <= deers[deer_index].distance_covered) {
				winning_index = deer_index;
				largest_distance = deers[deer_index].distance_covered;
			}
		}

		deers[winning_index].points++;

		for(int deer_index=0; deer_index<9; deer_index++) {
			if (deers[deer_index].remaining_rest_seconds > 0) {
				deers[deer_index].remaining_rest_seconds--;
			} else if (deers[deer_index].remaining_moving_seconds > 0) {
				deers[deer_index].remaining_moving_seconds--;
				deers[deer_index].distance_covered += deers[deer_index].kmps;
			} else if (deers[deer_index].rested) {
				deers[deer_index].remaining_moving_seconds = deers[deer_index].total_moving_seconds;
				deers[deer_index].rested = 0;
				// process the deer again
				deer_index--;
			} else {
				deers[deer_index].remaining_rest_seconds = deers[deer_index].total_rest_seconds;
				deers[deer_index].rested = 1;
				// process the deer again
				deer_index--;
			}
		}
	}

	int max_distance = 0;
	int max_points = 0;
	for (int i=0; i<9; i++) {
		if (max_distance < deers[i].distance_covered) {
			max_distance = deers[i].distance_covered;
		}
		if (max_points < deers[i].points) {
			max_points = deers[i].points;
		}
	}

	printf("Part 1: %d\n", max_distance);
	printf("Part 2: %d\n", max_points);
}
