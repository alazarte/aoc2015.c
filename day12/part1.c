int part1(char *buffer)
{
	int current_number = 0;
	char is_negative = 1;
	int sum = 0;
	char *b = buffer;

	while (*b != '\0') {
		if (*b >= '0' && *b <= '9') {
			current_number = (current_number * 10) + (*b - '0');
		} else if (*b == '-') {
			is_negative = -1;
		} else {
			current_number *= is_negative;
			is_negative = 1;
			sum += current_number;
			current_number = 0;
		}
		b++;
	}

	return sum;
}
