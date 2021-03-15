CC := gcc
exe := quick-sort tree-sort
lib := list.h common.h

all: $(exe)

quick-sort: quick-sort.c $(lib)
	$(CC) -o $@ $<

tree-sort: tree-sort.c $(lib)
	$(CC) -o $@ $<

.PHONY: clean
clean:
	rm -rf quick-sort.o
