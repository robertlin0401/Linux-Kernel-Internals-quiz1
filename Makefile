CC := gcc
exe := test
obj := list.o quicksort.o

all: $(obj) $(exe).o
	$(CC) -o $(exe) $^

$(exe).o: $(exe).c
	$(CC) -c $<

%.o: %.c %.h
	$(CC) -c $<

.PHONY: clean
clean:
	rm -rf $(obj) $(exe).o $(exe)

