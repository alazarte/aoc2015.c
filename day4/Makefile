out=a.out
cflags=-Wall -Wextra
input=iwrupvqb
zeroes=5

all: cc run

cc:
	$(CC) $(cflags) -o $(out) md5.c main.c

run: cc
	printf "Part1: "; ./$(out) $(input) 5
	printf "Part2: "; ./$(out) $(input) 6
