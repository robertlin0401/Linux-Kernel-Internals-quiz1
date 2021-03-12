#include <stdlib.h>
#include <stddef.h>
#include "quicksort.h"

static int *list2arr(node_t **, int);

static inline void SWAP(int *a, int *b) {
	*a ^= *b; *b ^= *a; *a ^= *b;
}

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
	#define MAX_LEVELS 300

	int *arr = list2arr(list, elements);
	int pivot, begin[MAX_LEVELS], end[MAX_LEVELS], iter = 0, L, R;

	begin[0] = 0;
	end[0] = elements;
	while (iter >= 0) {
		L = begin[iter];
		R = end[iter] - 1;
		if (L < R) {
			pivot = arr[L];
			while (L < R) {
				while (arr[R] >= pivot && L < R) R--; if (L < R) arr[L++] = arr[R];
				while (arr[L] <= pivot && L < R) L++; if (L < R) arr[R--] = arr[L];
			}
			arr[L] = pivot;
			begin[iter+1] = L + 1;
			end[iter+1] = end[iter];
			end[iter++] = L;
			if (end[iter]-begin[iter] > end[iter-1]-begin[iter-1]) {
				SWAP(&begin[iter], &begin[iter-1]);
				SWAP(&end[iter], &end[iter-1]);
			}
		} else {
			iter--;
		}
	}

	for (iter = 0; iter < elements; ++iter) {
		(*list)->value = arr[iter];
		list = &((*list)->next);
	}
	free(arr);
}

static int *list2arr(node_t **list, int elements)
{
	int *arr = (int *)malloc(elements * sizeof(int));
	for (int iter = 0; iter < elements; ++iter) {
		arr[iter] = (*list)->value;
		list = &((*list)->next);
	}
	return arr;
}

