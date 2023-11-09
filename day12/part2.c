#include "json.h"
#include "parts.h"

#include <stdio.h>
#include <string.h>

static int process_value(json_value * value, int depth, char *found_red);

static int process_object(json_value *value, int depth)
{
	char found_red = 0;
	int length, x, acc = 0;
	if (value == NULL) {
		return 0;
	}
	length = value->u.object.length;
	for (x = 0; x < length; x++) {
		acc +=
		    process_value(value->u.object.values[x].value, depth + 1,
				  &found_red);
		if (found_red) {
			found_red = 0;
			return 0;
		}
	}
	return acc;
}

static int process_array(json_value *value, int depth)
{
	int length, x, acc = 0;
	if (value == NULL) {
		return 0;
	}
	length = value->u.array.length;
	for (x = 0; x < length; x++) {
		acc += process_value(value->u.array.values[x], depth, NULL);
	}
	return acc;
}

static int process_value(json_value *value, int depth, char *found_red)
{
	if (value == NULL) {
		return 0;
	}
	switch (value->type) {
	case json_object:
		return process_object(value, depth + 1);
	case json_array:
		return process_array(value, depth + 1);
	case json_integer:
		return value->u.integer;
	case json_string:
		if (found_red != NULL
		    && strcmp(value->u.string.ptr, "red") == 0) {
			*found_red = 1;
			break;
		}
		break;
	default:
		return 0;
	}

	return 0;
}

int part2(char *buffer)
{
	json_char *json;
	json_value *value;

	int acc;

	json = (json_char *) buffer;

	value = json_parse(json, SIZE);

	if (value == NULL) {
		fprintf(stderr, "Unable to parse data\n");
		return -1;
	}

	acc = process_value(value, 0, NULL);

	json_value_free(value);
	return acc;
}
