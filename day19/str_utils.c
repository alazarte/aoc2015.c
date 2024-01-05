#include<sys/types.h>
#include<string.h>

ssize_t find_substr_index(char *input, char *replace, size_t which)
{
	char *r = replace;
	char *i = input;
	char *m = input;

	while (*i != '\0') {
		// keep input pointer in place and check if next chars match
		while (*m != '\0' && *m == *r) {
			m++;
			r++;
		}

		// in case it did, then replace pointer should be empty
		if (*r == '\0') {
			if (which != 1)
				which--;
			else
				return i - input;
		}

		r = replace;
		i++;
		m = i;
	}
	return -1;
}

void scpy_upto(char *to, char *from, size_t index)
{
	while ((*to++ = *from++) != '\0' && --index > 0) ;
}

void scpy_from(char *to, char *from, size_t index)
{
	while (index-- > 0)
		to++;
	strcpy(to, from);
}

