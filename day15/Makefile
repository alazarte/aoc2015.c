out=a.out
cflags=-Wall -Wextra

all: run

cc:
	$(CC) $(cflags) -o $(out) $(files) main.c

run: cc
	cat input.txt | ./$(out)
