 #ifndef CPU_H
 #define CPU_H

typedef struct {
    char *pid;
    int priority;
    int burst;
    int arrival;
}Process;

typedef struct {
  Process *p;
}CPU;

Process *p_new(char *pid, int priority, int burst, int arrival);

void cpu_run(CPU *p);
#endif
