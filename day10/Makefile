SHELL=/bin/bash
CFLAGS=-Wall -Wextra
OUT=./a.out
CFILE=day10.c

build:
	$(CC) $(CFLAGS) -o $(OUT) $(CFILE)

run:
	[[ -f run.sh ]]
	chmod +x run.sh
	echo "Part 1"
	time ./run.sh 40
	echo "Part 2"
	time ./run.sh 50
