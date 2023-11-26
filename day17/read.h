#define RECIPIENTS 20

typedef struct recipient {
	int cap;
	int full;
} recipient;

extern recipient recipients[RECIPIENTS];

void read_input();
