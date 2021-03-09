#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

typedef struct __node {                   
    int value;
    struct __node *next;
} node_t;

void list_add_node_t(node_t **, node_t *);

void list_concat(node_t **, node_t *);

bool list_is_ordered(node_t *);

void list_display(node_t *);

node_t *list_make_node_t(node_t *, int);


#endif
