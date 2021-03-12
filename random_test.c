#include <stdlib.h>
#include "list.h"
#include "quicksort.h"

void (*quicksort)(node_t **, int) = recursive_quicksort;

int main(int argc, char **argv) {
    size_t count = 20;
	const size_t elements = count;

    node_t *list = NULL;
    while (count--)
        list = list_make_node_t(list, random() % 1024);

    list_display(list);
    (*quicksort)(&list, elements);
    list_display(list);

    if (!list_is_ordered(list))
        return EXIT_FAILURE;

    list_free(&list);
    return EXIT_SUCCESS;
}

