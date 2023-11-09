out=a.out
cflags=-Wall -Wextra

all: run

cc:
	$(CC) $(cflags) -o $(out) main.c

run: cc
	cat input.txt | ./$(out)
