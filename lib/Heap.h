#ifndef HEAP_H
#define HEAP_H
#include <stdbool.h>

#include "Process.h"

typedef struct{
    Process **arr;
    int size;
    int i_last_ele;
}Heap;

Heap *h_new();

void h_free(Heap *h);

void h_swap(Heap *h, int i1, int i2);

void h_insert(Heap *h, Process *p);

Process *h_pop(Heap *h);// get + delete
#endif
