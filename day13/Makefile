out=a.out
cflags=-Wall -Wextra

all: cc

cc:
	$(CC) $(cflags) -o $(out) $(files) main.c

run: cc
	cat part1.txt | ./$(out) 8
	cat part2.txt | ./$(out) 9
