 #ifndef PROCESS_H
 #define PROCESS_H

typedef struct {
    char *pid;
    int priority;
    int burst;
    int arrival;
}Process;

Process *p_new(char *pid, int priority, int burst, int arrival);
#endif
