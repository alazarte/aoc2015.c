#include<stdio.h>
#include"read.c"

int final_score(int spoons[TOTAL], char is_500)
{
	if (is_500) {
		int cals = 0;
		for (int i = 0; i < TOTAL; i++) {
			cals += ingredients[i][STATS - 1] * spoons[i];
		}
		if (cals != 500) {
			return 0;
		}
	}

	int score_per_ingredient[STATS] = { 0 };
	for (int i = 0; i < STATS - 1; i++) {	// stats
		for (int j = 0; j < TOTAL; j++) {	// ingredients
			score_per_ingredient[i] +=
			    ingredients[j][i] * spoons[j];
		}
	}

	int total_score = 1;
	for (int i = 0; i < STATS - 1; i++) {
		if (score_per_ingredient[i] <= 0)
			return 0;
		total_score *= score_per_ingredient[i];
	}

	return total_score;
}

int main()
{
	read_input();

	int max_part_one_score = 0, max_part_two_score;
	for (int a = 1; a < 97; a++) {
		for (int b = 1; b < 97 - a; b++) {
			for (int c = 1; c < 97 - a - b; c++) {
				int d = 100 - a - b - c;
				if ((a + b + c + d) != 100) {
					return 1;
				}
				int spoons[TOTAL] = { a, b, c, d };

				int part_one_score =
				    final_score(spoons, 0);
				if (part_one_score > max_part_one_score)
					max_part_one_score = part_one_score;

				int part_two_score =
				    final_score(spoons, 1);
				if (part_two_score > max_part_two_score)
					max_part_two_score = part_two_score;
			}
		}
	}

	printf("Part 1=%d\n", max_part_one_score);
	printf("Part 2=%d\n", max_part_two_score);

	return 0;
}
