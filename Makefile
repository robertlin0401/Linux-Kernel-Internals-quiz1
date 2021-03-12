CC := gcc
exe := random_test optimized_random_test non_recursive_test
obj := list.o quicksort.o

all: $(exe)

random_test: $(obj) random_test.o
	$(CC) -o $@ $^

random_test.o: random_test.c
	$(CC) -c $<

optimized_random_test: $(obj) optimized_random_test.o
	$(CC) -o $@ $^

optimized_random_test.o: optimized_random_test.c
	$(CC) -c $<

non_recursive_test: $(obj) non_recursive_test.o
	$(CC) -o $@ $^

non_recursive_test.o: non_recursive_test.c
	$(CC) -c $<

%.o: %.c %.h
	$(CC) -c $<

.PHONY: clean
clean:
	rm -rf $(obj) random_test.o optimized_random_test.o

