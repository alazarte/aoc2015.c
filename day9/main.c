#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOCATIONS 100
#define STRING_SIZE 100

typedef struct Destination {
	char to[STRING_SIZE];
	unsigned int distance;
} destination;

typedef struct Location {
	unsigned int id;
	char from[STRING_SIZE];
	destination destinations[STRING_SIZE];
	unsigned short index_dest;
	struct Location *next;
} location;

// TODO no need to be global
int last_location = 1;
unsigned int visited[LOCATIONS];
int index_visited = 0;

void split(char **parts, char *buffer)
{
	char *b = buffer;
	int part_index = 0;
	char *to = parts[part_index];

	while (*b != '\0') {
		if (*b == ' ') {
			*to = '\0';
			to = parts[++part_index];
			b++;
			continue;
		}
		*to++ = *b++;
	}
}

void replace(char *buffer, char what, char with)
{
	while (*buffer != '\0') {
		if (*buffer == what) {
			*buffer = with;
			return;
		}
		buffer++;
	}
}

void parse_line(char **parts, char *buffer)
{
	for (int i = 0; i < 5; i++) {
		parts[i] = malloc(10);
	}

	split(parts, buffer);
}

void parts_into_location(char *from, char *to, char *distance, location *l)
{
	strcpy(l->from, from);
	destination d = {
		.distance = atoi(distance),
	};
	strcpy(d.to, to);
	l->destinations[l->index_dest++] = d;
}

void cleanup(char **parts)
{
	for (int i = 0; i < 5; i++) {
		free(parts[i]);
	}
}

location *find_location(location *locations, char *from)
{
	for (int i = 0; i < last_location; i++) {
		if (strcmp(locations[i].from, from) == 0) {
			return &locations[i];
		}
	}
	// TODO where to increment size, which is last_location
	location *l = &locations[last_location];
	l->id = last_location;
	last_location += 1;
	return l;
}

void travel(char *from, location *locations, int *min_distance,
	    int *max_distance, int distance)
{
	location *l = find_location(locations, from);
	visited[index_visited++] = l->id;
	char none_found = 1;

	for (int i = 0; i < l->index_dest; i++) {
		destination d = l->destinations[i];

		location *to_visit = find_location(locations, d.to);
		char found = 0;
		for (int j = 0; j < index_visited; j++) {
			if (to_visit->id == visited[j]) {
				found = 1;
			}
		}

		if (found) {
			continue;
		}

		none_found = 0;

		travel(d.to, locations, min_distance, max_distance, distance + d.distance);
	}

	if (none_found == 1) {
		if (*min_distance == 0 || *min_distance > distance) {
			*min_distance = distance;
		}
		if (*max_distance == 0 || *max_distance < distance) {
			*max_distance = distance;
		}
	}

	index_visited--;
}

int main()
{
	char *parts[5];
	char buffer[50] = { '\0' };
	location locations[LOCATIONS];

	while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
		replace(buffer, '\n', '\0');
		parse_line(parts, buffer);

		location *l = find_location(locations, parts[0]);

		parts_into_location(parts[0], parts[2], parts[4], l);

		l = find_location(locations, parts[2]);
		parts_into_location(parts[2], parts[0], parts[4], l);
	}

	int min = 0, max = 0;
	int min_distance = 0;
	int max_distance = 0;
	for (int i = 1; i < last_location; i++) {
		travel(locations[i].from, locations, &min, &max, 0);
		if (min_distance == 0 || min_distance > min) {
			min_distance = min;
		}
		if (max_distance == 0 || max_distance > max) {
			max_distance = max;
		}
	}
	printf("Part 1: %d\n", min_distance);
	printf("Part 2: %d\n", max_distance);

	cleanup(parts);
}
