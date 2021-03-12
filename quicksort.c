#include <stddef.h>
#include "quicksort.h"

void recursive_quicksort(node_t **list, int elements)
{
    if (!*list)
        return;

    node_t *pivot = *list;
    int value = pivot->value;
    node_t *p = pivot->next;
    pivot->next = NULL;

    node_t *left = NULL, *right = NULL;
    while (p) {
        node_t *n = p;
        p = p->next;
        list_add_node_t(n->value > value ? &right : &left, n);
    }

    recursive_quicksort(&left, 0);
    recursive_quicksort(&right, 0);

    node_t *result = NULL;
    list_concat(&result, left);
    list_concat(&result, pivot);
	list_concat(&result, right);
    *list = result;
}

void non_recursive_quicksort(node_t **list, int elements)
{
	
}
