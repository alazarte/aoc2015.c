#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<unistd.h>
#define HOUSES 1000
typedef unsigned short suint;

void move_coor(char mov, suint *x, suint *y)
{
	switch (mov) {
	case '>':
		*x += 1;
		break;
	case 'v':
		*y += 1;
		break;
	case '<':
		*x -= 1;
		break;
	case '^':
		*y -= 1;
		break;
	}
}

int main()
{
	char ch;

	suint houses_part1[HOUSES][HOUSES];
	suint houses_part2[HOUSES][HOUSES];
	// coordinates for part 1
	suint a_x = HOUSES / 2, a_y = HOUSES / 2;

	// coordinates for santa and robot
	suint s_x = HOUSES / 2, s_y = HOUSES / 2;
	suint r_x = HOUSES / 2, r_y = HOUSES / 2;

	suint *x = &s_x, *y = &s_y;
	char santa_turn = 1;

	int unique_houses_part1 = 1;
	int unique_houses_part2 = 1;

	// first house is visited
	houses_part1[a_x][a_y] = 1;
	houses_part2[a_x][a_y] = 1;

	// could avoid having two different maps by reading the whole input 
	// into a buffer and then working on the same map, first for part1 and 
	// then for part2 after resetting visited houses
	while (read(STDIN_FILENO, &ch, 1) > 0) {
		move_coor(ch, &a_x, &a_y);
		if (houses_part1[a_x][a_y] == 0)
			unique_houses_part1 += 1;
		houses_part1[a_x][a_y] += 1;

		move_coor(ch, x, y);
		if (houses_part2[*x][*y] == 0)
			unique_houses_part2 += 1;
		houses_part2[*x][*y] += 1;

		santa_turn = !santa_turn;
		if (santa_turn) {
			x = &s_x;
			y = &s_y;
		} else {
			x = &r_x;
			y = &r_y;
		}
	}

	printf("Part 1: %d\n", unique_houses_part1);
	printf("Part 2: %d\n", unique_houses_part2);
}
