 #ifndef CPU_H
 #define CPU_H

typedef struct {
    char pid[8];
    int priority;
    int burst;
    int arrival;
    int first_arrival;
    int first_exe_time;
    int completed_time;
}Process;

typedef struct {
  Process *p;
}CPU;

Process *p_new(char *pid, int priority, int burst, int arrival);

CPU *c_new();

bool cpu_run(CPU *c, int time);
#endif
