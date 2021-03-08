#ifndef LIST.H
#define LIST.H
#include <stdbool.h>

typedef struct __node {                   
    int value;
    struct __node *next;
} node_t;

static inline void list_add_node_t(node_t **, node_t *);

static inline void list_concat(node_t **, node_t *);

static bool list_is_order(node_t *);

static void list_display(node_t *);

#endif
