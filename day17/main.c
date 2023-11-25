#include<stdio.h>

#define RECIPIENTS 20

int min_containers = 9999;
int part2 = 0;

typedef struct recipient {
	int cap;
	int full;
} recipient;

int fill(int liters_left, recipient *recipients, int usable, int containers_used)
{
	if (liters_left == 0) {
		if (containers_used == 4) {
			part2++;
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
	recipient recipients[RECIPIENTS] = {
		{50, 0},
		{48, 0},
		{45, 0},
		{44, 0},
		{42, 0},
		{41, 0},
		{35, 0},
		{35, 0},
		{33, 0},
		{30, 0},
		{24, 0},
		{20, 0},
		{18, 0},
		{18, 0},
		{16, 0},
		{14, 0},
		{13, 0},
		{13, 0},
		{6, 0},
		{1, 0},
	};
	printf("%d\n", fill(150, recipients, 0, 0));
	printf("%d\n", part2);
}
