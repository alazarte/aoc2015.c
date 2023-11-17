#include<stdio.h>
#include<unistd.h>

#define DEERS 9

typedef struct DeerInfo {
	int total_moving_seconds;
	int total_rest_seconds;
	int kmps;

	int remaining_moving_seconds;
	int remaining_rest_seconds;
	char rested;
	int points;
	int distance_covered;
} deer_info;

deer_info make_deer(int kmps, int total_moving_seconds, int total_rest_seconds)
{
	deer_info d = {
		.kmps = kmps,
		.total_moving_seconds = total_moving_seconds,
		.total_rest_seconds = total_rest_seconds,
		.remaining_moving_seconds = total_moving_seconds,
		.remaining_rest_seconds = 0,
		.rested = 0,
		.points = 0,
		.distance_covered = 0,
	};
	return d;
}

void one_second_step_deers(deer_info deers[DEERS])
{
	for (int deer_index = 0; deer_index < 9; deer_index++) {
		if (deers[deer_index].remaining_rest_seconds > 0) {
			deers[deer_index].remaining_rest_seconds--;
		} else if (deers[deer_index].remaining_moving_seconds > 0) {
			deers[deer_index].remaining_moving_seconds--;
			deers[deer_index].distance_covered +=
			    deers[deer_index].kmps;
		} else if (deers[deer_index].rested) {
			deers[deer_index].remaining_moving_seconds =
			    deers[deer_index].total_moving_seconds;
			deers[deer_index].rested = 0;
			// process the deer again
			deer_index--;
		} else {
			deers[deer_index].remaining_rest_seconds =
			    deers[deer_index].total_rest_seconds;
			deers[deer_index].rested = 1;
			// process the deer again
			deer_index--;
		}
	}
}

int farthest_deer_index(deer_info deers[DEERS])
{
	int winning_index = -1;
	int largest_distance = -1;
	for (int deer_index = 0; deer_index < 9; deer_index++) {
		if (largest_distance <= deers[deer_index].distance_covered) {
			winning_index = deer_index;
			largest_distance = deers[deer_index].distance_covered;
		}
	}
	return winning_index;
}

int main()
{
	int numbers[3];
	int numbers_index = 0;
	int current_number = 0;
	int deer_index = 0;
	char ch;
	int total_seconds = 2503;
	deer_info deers[9];

	while (read(STDIN_FILENO, &ch, 1) > 0) {
		if ('0' <= ch && ch <= '9') {
			current_number = (current_number * 10) + (ch - '0');
		} else if (ch == '\n') {
			deers[deer_index++] =
			    make_deer(numbers[0], numbers[1], numbers[2]);
			numbers_index = 0;
		} else if (current_number != 0) {
			numbers[numbers_index++] = current_number;
			current_number = 0;
		}
	}

	int deer = -1;
	for (int second = 0; second <= total_seconds; second++) {
		one_second_step_deers(deers);
		deer = farthest_deer_index(deers);
		deers[deer].points++;

	}

	int max_distance = 0;
	int max_points = 0;
	for (int i = 0; i < 9; i++) {
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
