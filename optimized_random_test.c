#include <stdio.h>
#include <stdlib.h>
#include <sys/random.h>
#include "list.h"
#include "quicksort.h"

void (*quicksort)(node_t **) = recursive_quicksort;

int main(int argc, char **argv) {
    size_t count = 20;
	int *seed = (int *)malloc(sizeof(int));
	int result = getrandom(seed, sizeof(int), GRND_RANDOM | GRND_NONBLOCK);
	if (result == -1) *seed = result;
	srandom(*seed);
	free(seed);

    node_t *list = NULL;
    while (count--)
        list = list_make_node_t(list, random() % 1024);

    list_display(list);
    (*quicksort)(&list);
    list_display(list);

    if (!list_is_ordered(list))
        return EXIT_FAILURE;

    list_free(&list);
    return EXIT_SUCCESS;
}

