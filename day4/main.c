#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include"md5.h"

int begins_with_zeroes(char hash[32], int zeroes)
{
	int z = 0;
	for (unsigned int i = 0; i < 32; i++) {
		if (hash[i] != '0')
			break;
		z++;
		if (zeroes == z) {
			return 1;
		}
	}
	return 0;
}

void print_hash(uint8_t *p, char string[32])
{
	char buffer[3];
	string[0] = '\0';
	for (unsigned int i = 0; i < 16; i++) {
		sprintf(buffer, "%02x", p[i]);
		strcat(string, buffer);
	}
}

int main(int argn, char **argv)
{
	if (argn < 2) {
		printf("%s <input> <zeroes>\n", argv[0]);
		return 1;
	}

	char *key = argv[1];
	int zeroes = atoi(argv[2]);
	if (zeroes == 0) {
		printf("0 as amount of zeroes not allowed, or invalid input :shrug:\n");
	}

	int d = 0;
	char input_string[100];
	uint8_t hash[16];
	char hash_string[32];

	for (;;) {
		sprintf(input_string, "%s%d", key, d);
		md5String(input_string, hash);
		print_hash(hash, hash_string);
		if (begins_with_zeroes(hash_string, zeroes)) {
			break;
		}
		d++;
	}

	printf("Key: %d Final hash: %s\n", d, hash_string);
}
