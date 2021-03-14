#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

#include "common.h"

static uint16_t values[256];

static bool isValid(struct list_head *head, struct list_head *L, struct list_head *R)
{
    while (1) {
        if (L == R) return true;
        if (L == head) return false;
        L = L->next;
    }
}

static int list_offset(struct list_head *head, struct list_head *begin, struct list_head *end)
{
    int count = 0;
    while (begin != end) {
        if (begin == head) return -1;
        count++;
        begin = begin->next;
    }
    return count;
}

static void SWAP(struct list_head **a, struct list_head **b)
{
    struct list_head *temp = *a;
    *a = *b;
    *b = temp;
}

static void list_qsort(struct list_head *head)
{
    #define MAX_LEVELS 300
    #define isValid() isValid(head, L, R)
    #define valueOf(node) list_entry(node, struct listitem, list)->i

    struct list_head *pivot, *begin[MAX_LEVELS], *end[MAX_LEVELS], *L, *R;
    int iter = 0;

    if (list_empty(head) || list_is_singular(head))
        return;

    begin[0] = head->next;
    end[0] = head;
    while (iter >= 0) {
        L = begin[iter];
        R = end[iter]->prev;
        if (isValid()) {
            pivot = L;
            while (isValid()) {
                while (valueOf(R) >= valueOf(pivot) && isValid()) R = R->prev;
                if (isValid()) {
                    struct list_head *target = R;
                    R = R->next;
                    list_move(target, L);
                    L = L->next;
                }
                while (valueOf(L) <= valueOf(pivot) && isValid()) L = L->next;
                if (isValid()) {
                    struct list_head *target = L;
                    L = L->prev;
                    list_move_tail(target, R);
                    R = R->prev;
                }
            }
            end[iter+1] = end[iter];
            end[iter++] = L;
            L = L->next;
            list_move_tail(pivot, L);
            begin[iter+1] = L;
            if (list_offset(head, begin[iter], end[iter]) > list_offset(head, begin[iter-1], end[iter-1])) {
                SWAP(&begin[iter], &begin[iter-1]);
                SWAP(&end[iter], &end[iter-1]);
            }
        } else {
            iter--;
        }
    }
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
    list_qsort(&testlist);

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
