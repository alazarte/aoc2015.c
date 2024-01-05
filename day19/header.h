#define REPLACEMENTS 2
#define STRING_LEN 10000
#define ITEMS_CAP 1000

typedef struct {
	char compare[10];
	size_t found;
} Compare;

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

void parse_input(Replaces *replaces, char input[500]);
void add_replace(Replaces *replaces, char *replace, char *with);
ssize_t find_substr_index(char *input, char *replace, size_t which);
void scpy_upto(char *to, char *from, size_t index);
void scpy_from(char *to, char *from, size_t index);
