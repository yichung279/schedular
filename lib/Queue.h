#ifndef QUEUE_H
#define QUEUE_H
#include <stdbool.h>

#include "Process.c"

typedef struct node{
    Process *process;
    struct node *next;
    struct node *prev;
}Node;

typedef struct {
  Node *head;
  Node *tail;
}Queue;

Queue *q_new();

void q_free(Queue *q);

void q_push(Queue *q, Process *p);

Process *q_pop(Queue *q);
#endif
