#include<stdio.h>

#define INGREDIENTS 4
#define STATS 5

int final_score(int ingredients[INGREDIENTS][STATS],
		int spoons_per_ingredient[INGREDIENTS])
{
	int ingredients_score[STATS] = { 0 };
	for (int i = 0; i < INGREDIENTS; i++) {
		for (int j = 0; j < 4; j++) {
			ingredients_score[j] +=
			    ingredients[i][j] * spoons_per_ingredient[i];
		}
	}

	int final_score = 1;
	for (int i = 0; i < 4; i++) {
		final_score *= ingredients_score[i];
	}

	return final_score;
}

int main()
{
	int spoons = 100;
	int ingredients[INGREDIENTS][STATS] = { {2, 0, -2, 0, 3},
	{0, 5, -3, 0, 3},
	{0, 0, 5, -1, 8},
	{0, -1, 0, 5, 8}
	};

	int spoons_per_ingredient[INGREDIENTS] = { 0, 0, 0, 0 };

	for (int i = 0; i < INGREDIENTS; i++) {
		spoons_per_ingredient[i] = spoons / INGREDIENTS;
	}

	int score = 0;
	int max_score = final_score(ingredients, spoons_per_ingredient);
	int index_best_spoon = -1;

	for (int m = 0; m < 5000; m++) {
		for (int i = 0; i < INGREDIENTS; i++) {
			spoons_per_ingredient[i]--;
			for (int j = 0; j < INGREDIENTS; j++) {
				if (j == i)
					continue;
				spoons_per_ingredient[j]++;
				score =
				    final_score(ingredients,
						spoons_per_ingredient);
				if (max_score < score) {
					max_score = score;
					index_best_spoon = j;
				}
				spoons_per_ingredient[j]--;
			}
			if (index_best_spoon != -1) {
				spoons_per_ingredient[index_best_spoon]++;
				index_best_spoon = -1;
			} else {
				spoons_per_ingredient[i]++;
			}
		}
	}

	printf("final_score=%d\n", final_score(ingredients, spoons_per_ingredient));

	//ingredients[0] =;
	//ingredients[1] = ;
}
