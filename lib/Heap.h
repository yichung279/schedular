#ifndef HEAP_H
#define HEAP_H
#include <stdbool.h>

#include "Process.h"

typedef struct{
    Process **arr;
    int size;
    int i_last_ele;
    int (*is_smaller)(const void *, const void*);
}Heap;

Heap *h_new(int (*compr)(const void *, const void*));

void h_free(Heap *h);

void h_swap(Heap *h, int i1, int i2);

void heapify(Heap *h, int i);

void h_insert(Heap *h, Process *p);

Process *h_extract(Heap *h);// get + delete
#endif
