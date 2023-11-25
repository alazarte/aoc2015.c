#include<string.h>

char hash(char *s)
{
	if (strcmp(s, "children") == 0) {
		return 0;
	} else if (strcmp(s, "cats") == 0) {
		return 1;
	} else if (strcmp(s, "samoyeds") == 0) {
		return 2;
	} else if (strcmp(s, "pomeranians") == 0) {
		return 3;
	} else if (strcmp(s, "akitas") == 0) {
		return 4;
	} else if (strcmp(s, "vizslas") == 0) {
		return 5;
	} else if (strcmp(s, "goldfish") == 0) {
		return 6;
	} else if (strcmp(s, "trees") == 0) {
		return 7;
	} else if (strcmp(s, "cars") == 0) {
		return 8;
	} else if (strcmp(s, "perfumes") == 0) {
		return 9;
	} else {
		return -1;
	}
}

