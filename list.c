#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "list.h"

void list_add_node_t(node_t **list, node_t *node_t) {
    node_t->next = *list;
    *list = node_t;
}

void list_concat(node_t **left, node_t *right) {
    while (*left)
        left = &((*left)->next);
    *left = right;
}

bool list_is_ordered(node_t *list) {
    bool first = true;
    int value;
    while (list) {
        if (first) {
            value = list->value;
            first = false;
        } else {
            if (list->value < value)
                return false;
            value = list->value;
        }
        list = list->next;
    }
    return true;
}

void list_display(node_t *list) {
    printf("%s IN ORDER : ", list_is_ordered(list) ? "   " : "NOT");
    while (list) {
        printf("%d ", list->value);
        list = list->next;
    }
    printf("\n");
}

node_t *list_make_node_t(node_t *list, int random) {
	node_t *node_t = malloc(sizeof(node_t));
	node_t->value = random;
	list_add_node_t(&list, node_t);
	return list;
}

void list_free(node_t **list) {
	while (*list) {
		node_t *n = (*list)->next;
		free(*list);
		list = &n;
	}
}

