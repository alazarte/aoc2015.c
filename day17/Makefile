out=a.out
cflags=-Wall -Wextra

all: run

run: cc
	cat input.txt | ./$(out)

cc: read.o
	$(CC) $(cflags) -o $(out) read.o main.c

read.o:
	cc -c read.c

clean:
	rm a.out read.o
