#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#include "common.h"

static uint16_t values[256];

static inline void set_leaf(struct list_head *leaf)
{
    leaf->prev = NULL;
    leaf->next = NULL;
}

static inline void inorder_traversal(struct list_head *root, struct list_head *head)
{
    if (root != NULL) {
        inorder_traversal(root->prev, head);
		struct list_head *next = root->next;
        list_add_tail(root, head);
        inorder_traversal(next, head);
    }
}

static void list_tsort(struct list_head *head)
{	
    #define valueOf(node) list_entry(node, struct listitem, list)->i

    if (list_empty(head) || list_is_singular(head))
        return;
    
    struct list_head *root = head->next;
    list_del(root);
    set_leaf(root);
    while (!list_empty(head)) {
        struct list_head *target = head->next;
        list_del(target);
        set_leaf(target);
        struct list_head *position = root;
        while (1) {
            if (valueOf(target) <= valueOf(position)) {
                if (position->prev != NULL)
                    position = position->prev;
                else {
                    position->prev = target;
                    break;
                }
            } else {
                if (position->next != NULL)
                    position = position->next;
                else {
                    position->next = target;
                    break;
                }
            }
        }
    }

    inorder_traversal(root, head);
}

int main(void)
{
    struct list_head testlist;
    struct listitem *item, *is = NULL;
    size_t i;

    random_shuffle_array(values, (uint16_t) ARRAY_SIZE(values));

    INIT_LIST_HEAD(&testlist);

    assert(list_empty(&testlist));

    for (i = 0; i < ARRAY_SIZE(values); i++) {
        item = (struct listitem *) malloc(sizeof(*item));
        assert(item);
        item->i = values[i];
        list_add_tail(&item->list, &testlist);
    }

    assert(!list_empty(&testlist));

    qsort(values, ARRAY_SIZE(values), sizeof(values[0]), cmpint);
    list_tsort(&testlist);

    i = 0;
    list_for_each_entry_safe (item, is, &testlist, list) {
        assert(item->i == values[i]);
        list_del(&item->list);
        free(item);
        i++;
    }

    assert(i == ARRAY_SIZE(values));
    assert(list_empty(&testlist));

    return 0;
}
