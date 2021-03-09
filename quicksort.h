#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "list.h"

void (*)quicksort(node_t **);

void recursive_quicksort(node_t **list)
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

    recursive_quicksort(&left);
    recursivequicksort(&right);

    node_t *result = NULL;
    list_concat(&result, left);
    list_concat(&result, pivot);
	list_concat(&result, right);
    *list = result;
}

#endif

