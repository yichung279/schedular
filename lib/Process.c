#include <stdio.h>

#include "Process.h"

Process *p_new(char *pid, int priority, int burst, int arrival){
    Process *p = malloc(sizeof(Process));
    if (p == NULL)
        return NULL;

    strcpy(p->pid, pid);
    p->priority = priority;
    p->burst = burst;
    p->arrival = arrival;

    return p;
}

CPU *c_new() {
    CPU *c = malloc(sizeof(CPU));
    if (c == NULL)
        return NULL;

    c->p = NULL;

    return c;
}

bool cpu_run(CPU *c) {// return 1 when c->p complete
    if (!c->p) return 0;
    c->p->burst --;

    if (0 == c->p->burst) {
        c->p = NULL;
        return 1;
    }

    return 0;
}
