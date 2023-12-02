#include<stdio.h>
#include<stdlib.h>

#define REPLACEMENTS 2
#define STRING_LEN 10000
#define ITEMS_CAP 1000

typedef struct {
	char replace[10];
	char with[10];
} Replace;

typedef struct {
	Replace *items;
	size_t count;
	size_t cap;
} Replaces;

typedef struct {
	char string[STRING_LEN];
} String;

typedef struct {
	String *items;
	size_t count;
	size_t cap;
} Strings;

size_t slen(char *str)
{
	char *s = str;
	while (*s != '\0')
		s++;
	return s - str;
}

char scmp(char *str1, char *str2)
{
	while (*str1 == *str2) {
		str1++;
		str2++;
		if (*str1 == '\0' || *str2 == '\0')
			break;
	}
	if (*str1 == *str2)
		return 1;

	return 0;
}

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

void scpy(char *to, char *from)
{
	while (*from != '\0') {
		*to++ = *from++;
	}
	*to = '\0';
}

void scpy_upto(char *to, char *from, size_t index)
{
	while ((*to++ = *from++) != '\0' && --index > 0) ;
}

void scpy_from(char *to, char *from, size_t index)
{
	while (index-- > 0)
		to++;
	scpy(to, from);
}

void add_replace(Replaces *replaces, char *replace, char *with)
{
	scpy(replaces->items[replaces->count].replace, replace);
	scpy(replaces->items[replaces->count].with, with);
	replaces->count++;
}

void add_string(Strings *strings, char *string)
{
	for (size_t i = 0; i < strings->count; i++) {
		if (scmp(string, strings->items[i].string))
			return;
	}
	scpy(strings->items[strings->count].string, string);
	strings->count++;
}

size_t replace_substr(char *final, char *input, char *replace, char *with,
		      size_t which)
{
	ssize_t index = find_substr_index(input, replace, which);
	if (index == -1)
		return 0;
	size_t replace_len = slen(replace);
	size_t with_len = slen(with);
	scpy_upto(final, input, index);
	scpy_from(final, with, index);
	scpy_from(final, (input + index + replace_len), index + with_len);

	return 1;
}

int main()
{
	char input[] = "CRnCaSiRnBSiRnFArTiBPTiTiBFArPBCaSiThSiRnTiBPBPMgArCaSiRnTiMgArCaSiThCaSiRnFArRnSiRnFArTiTiBFArCaCaSiRnSiThCaCaSiRnMgArFYSiRnFYCaFArSiThCaSiThPBPTiMgArCaPRnSiAlArPBCaCaSiRnFYSiThCaRnFArArCaCaSiRnPBSiRnFArMgYCaCaCaCaSiThCaCaSiAlArCaCaSiRnPBSiAlArBCaCaCaCaSiThCaPBSiThPBPBCaSiRnFYFArSiThCaSiRnFArBCaCaSiRnFYFArSiThCaPBSiThCaSiRnPMgArRnFArPTiBCaPRnFArCaCaCaCaSiRnCaCaSiRnFYFArFArBCaSiThFArThSiThSiRnTiRnPMgArFArCaSiThCaPBCaSiRnBFArCaCaPRnCaCaPMgArSiRnFYFArCaSiThRnPBPMgAr";

	char final[STRING_LEN] = { 0 };

	Replaces replaces;
	replaces.count = 0;
	replaces.cap = ITEMS_CAP;
	replaces.items = malloc(sizeof(Replace) * replaces.cap);

	Strings strings;
	strings.count = 0;
	strings.cap = ITEMS_CAP;
	strings.items = malloc(sizeof(String) * strings.cap);

	add_replace(&replaces, "Al", "ThF");
	add_replace(&replaces, "Al", "ThRnFAr");
	add_replace(&replaces, "B", "BCa");
	add_replace(&replaces, "B", "TiB");
	add_replace(&replaces, "B", "TiRnFAr");
	add_replace(&replaces, "Ca", "CaCa");
	add_replace(&replaces, "Ca", "PB");
	add_replace(&replaces, "Ca", "PRnFAr");
	add_replace(&replaces, "Ca", "SiRnFYFAr");
	add_replace(&replaces, "Ca", "SiRnMgAr");
	add_replace(&replaces, "Ca", "SiTh");
	add_replace(&replaces, "F", "CaF");
	add_replace(&replaces, "F", "PMg");
	add_replace(&replaces, "F", "SiAl");
	add_replace(&replaces, "H", "CRnAlAr");
	add_replace(&replaces, "H", "CRnFYFYFAr");
	add_replace(&replaces, "H", "CRnFYMgAr");
	add_replace(&replaces, "H", "CRnMgYFAr");
	add_replace(&replaces, "H", "HCa");
	add_replace(&replaces, "H", "NRnFYFAr");
	add_replace(&replaces, "H", "NRnMgAr");
	add_replace(&replaces, "H", "NTh");
	add_replace(&replaces, "H", "OB");
	add_replace(&replaces, "H", "ORnFAr");
	add_replace(&replaces, "Mg", "BF");
	add_replace(&replaces, "Mg", "TiMg");
	add_replace(&replaces, "N", "CRnFAr");
	add_replace(&replaces, "N", "HSi");
	add_replace(&replaces, "O", "CRnFYFAr");
	add_replace(&replaces, "O", "CRnMgAr");
	add_replace(&replaces, "O", "HP");
	add_replace(&replaces, "O", "NRnFAr");
	add_replace(&replaces, "O", "OTi");
	add_replace(&replaces, "P", "CaP");
	add_replace(&replaces, "P", "PTi");
	add_replace(&replaces, "P", "SiRnFAr");
	add_replace(&replaces, "Si", "CaSi");
	add_replace(&replaces, "Th", "ThCa");
	add_replace(&replaces, "Ti", "BP");
	add_replace(&replaces, "Ti", "TiTi");
	add_replace(&replaces, "e", "HF");
	add_replace(&replaces, "e", "NAl");
	add_replace(&replaces, "e", "OMg");

	for (size_t i = 0; i < replaces.count; i++) {
		Replace r = replaces.items[i];
		size_t which = 1;
		while (replace_substr(final, input, r.replace, r.with, which++)) {
			add_string(&strings, final);
		}
	}

	printf("Part 1: %ld\n", strings.count);

	free(replaces.items);
	free(strings.items);
}
