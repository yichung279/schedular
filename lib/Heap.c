#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Heap.h"

#define HEAP_SIZE 1000

Heap *h_new() {
    Heap *h = malloc(sizeof(Heap));
    h->arr = malloc(HEAP_SIZE * sizeof(Process *));
    h->size = HEAP_SIZE;
    h->i_last_ele = 0;
    return h;
}


void h_free(Heap *h) {
    for (int i = 0; i < h->size; i++) free(h->arr[i]);
    free(h);
}

void h_swap(Heap *h, int i1, int i2) {
    Process *tmp = h->arr[i1];
    h->arr[i1] = h->arr[i2];
    h->arr[i2] = tmp;
}

void h_insert(Heap *h, Process *p) {
    h->i_last_ele++;
    h->arr[h->i_last_ele] = p;

    int idx = h->i_last_ele;
    int new_idx;
    while (h->arr[idx]) {
        new_idx = (int)floor(idx/2);
        if (0 == new_idx) break;
        if (h->arr[new_idx]->burst < h->arr[idx]->burst ) break;
        h_swap(h, idx, new_idx);

        idx = new_idx;
    }
}
