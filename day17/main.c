#include<stdio.h>
#include"read.h"

int min_containers = 9999;
int combinations_min_containers = 0;

int fill(int liters_left, recipient *recipients, int usable, int containers_used)
{
	if (liters_left == 0) {
		if (containers_used < min_containers) {
			min_containers = containers_used;
			combinations_min_containers = 0;
		}
		if (containers_used == min_containers) {
			combinations_min_containers++;
		}
		return 1;
	}
	if (liters_left < 0) {
		return 0;
	}

	int combinations = 0;
	for (int i = usable; i < RECIPIENTS; i++) {
		if (recipients[i].full)
			continue;
		liters_left -= recipients[i].cap;
		recipients[i].full = 1;
		containers_used++;
		combinations += fill(liters_left, recipients, i + 1, containers_used);
		containers_used--;
		liters_left += recipients[i].cap;
		recipients[i].full = 0;
	}
	return combinations;
}

int main()
{
	read_input();
	printf("Part 1: %d\n", fill(150, recipients, 0, 0));
	printf("Part 2: %d\n", combinations_min_containers);
}
