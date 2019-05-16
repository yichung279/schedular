#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *pid;
    int priority;
    int burst;
    int arrival;
}Process;

typedef struct node{
    Process *process;
    struct node *next;
    struct node *prev;
}Node;

typedef struct {
  Node *head;
  Node *tail;
}Queue;

Process *p_new(char *pid, int priority, int burst, int arrival);

Queue *q_new();

void q_free(Queue *q);

void q_push(Queue *q, Process *p);

Process *q_pop(Queue *q);
