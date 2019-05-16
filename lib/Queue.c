#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Queue.h"

Queue *q_new(){
    Queue *q = malloc(sizeof(Queue));
    if (q == NULL)
        return NULL;

    q->head = NULL;
    q->tail = NULL;

    return q;
}

void q_free(Queue *q){
    if (!q) return;

    Node *current = q->head;
    Node *tmp;
    while(current){
        tmp = current;
        current = current->next;
        free(tmp);
    };
    free(q);
}

void q_push(Queue *q, Process *p){
    if (!q || !p) return;

    Node *node = malloc(sizeof(Node));
    if (!node) return;

    node->process = p;
    node->prev = q->tail;
    node->next = NULL;
    if (node->prev)
        node->prev->next = node;
    if (!q->head)
        q->head = node;
    q->tail = node;
}

Process *q_pop(Queue *q){
    if (!q) return NULL;
    if (!q->head) return NULL;

    Node *current = q->head;
    Process *p = current->process;
    q->head = current->next;
    if (current->next){
        current->next->prev = NULL;
    }else{
        q->tail = NULL;
    }
    free(current);
    return p;
}
