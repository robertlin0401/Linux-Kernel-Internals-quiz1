CC := gcc
exe := random_test
obj := list.o quicksort.o

all: $(exe)

$(exe): $(obj) $(exe).o
	$(CC) -o $@ $^

$(exe).o: $(exe).c
	$(CC) -c $<

%.o: %.c %.h
	$(CC) -c $<

.PHONY: clean
clean:
	rm -rf $(obj) $(exe).o $(exe)

