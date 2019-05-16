#include <stdio.h>

#include "Process.h"

Process *p_new(char *pid, int priority, int burst, int arrival){
    Process *p = malloc(sizeof(Process));
    if (p == NULL)
        return NULL;

    p->pid = pid;
    p->priority = priority;
    p->burst = burst;
    p->arrival = arrival;

    return p;
}

void cpu_run(CPU *c) {
    c->p->burst --;
}
