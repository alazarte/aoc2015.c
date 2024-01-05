out=a.out
cflags=-Wall -Wextra
objs=parse_input str_utils

all: clean cc run

run: cc
	cat input.txt | ./$(out)

cc: $(addsuffix .o,$(objs))
	$(CC) $(cflags) -o $(out) $^ main.c

$(objs):
	$(CC) -c $@.c

clean:
	rm -f *.o $(out)
