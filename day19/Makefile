out=a.out
cflags=-Wall -Wextra

all: cc run

run: cc
	cat input.txt | ./$(out)

cc:
	$(CC) $(cflags) -o $(out) main.c

clean:
	rm a.out read.o
