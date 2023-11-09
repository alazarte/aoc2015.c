out=a.out
cflags=-Wall -Wextra

all: cc run

cc:
	$(CC) $(cflags) -o $(out) list.c main.c

run: cc
	cat input.txt | ./$(out)
