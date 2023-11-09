out=a.out
cflags=-Wall -Wextra -lm
files=json.c part1.c part2.c

all: run

cc:
	$(CC) $(cflags) -o $(out) $(files) main.c

run: cc
	cat input.txt | ./$(out)
