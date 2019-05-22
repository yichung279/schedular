#include <string.h>
#include <stdio.h>
#include <stdio.h>

#include "lib/Heap.c"
#include "lib/Process.c"

#define QUANTUM 5

// Passing these functions through function pointers, we compare different parts of process with same schedualr. 
int is_smaller_arrival(const void *a, const void *b){
	Process c = *(Process *)a;
	Process d = *(Process *)b;
    if (c.arrival < d.arrival)
        return 1;
    return 0;
}

int is_smaller_priority(const void *a, const void *b){
	Process c = *(Process *)a;
	Process d = *(Process *)b;
    if (c.priority < d.priority)
        return 1;
    return 0;
}

int is_smaller_burst(const void *a, const void *b){
	Process c = *(Process *)a;
	Process d = *(Process *)b;
    if (c.burst < d.burst)
        return 1;
    return 0;
}

int main(int argc, char* argv[]){

    char test_filename[128];
    strcpy(test_filename, argv[2]);
    printf("%s\n", test_filename);

    FILE *trace_file = fopen(test_filename, "rb");
    char buf[512];

    int n_process = 0;
    Process process_list[100000];
    // structure of Process 
    // {
    //      char pid[8];
    //      int priority;
    //      int burst;
    //      // the time when process put in to ready queue  	
    //      int arrival;
    //      // the time when process FIRST put in to ready queue  
    //      int first_arrival;
    //	    int first_exe_time;
    //	    int completed_time;
    // }
    // read file and save processes in process_list
    while(fgets(buf, 1000, trace_file) != NULL) {
        char *pch;
		pch = strtok (buf," ,.-");
		for(int i = 0; i < 4;i++){
            if (0 == i) {
                strcpy(process_list[n_process].pid, pch);
            }
            else if (1 ==i)
                process_list[n_process].priority = atoi(pch);
            else if (2 == i)
                process_list[n_process].burst = atoi(pch);
            else if (3 == i)
                process_list[n_process].first_arrival = atoi(pch);
            pch = strtok (NULL, " ,.-");
        }

        n_process++;
    }

    // Use heap to implement a schedular.
    Heap *schedular;
    // structure of Heap	
    // {
    //     // an array of Processes
    //     Process **arr;
    //     int size;      
    //     int i_last_ele;
    //     // function pointer comparing arrival, burst, or priority 
    //     int (*is_smaller)(const void *, const void*);
    // }
    // new a schedular with different algorithm
    if (0 == strcmp("fcfs", argv[1]) || 0 == strcmp("rr", argv[1]))
        schedular = h_new(is_smaller_arrival);
    else if (0 == strcmp("sjf", argv[1]) || 0 == strcmp("srtf", argv[1]))
        schedular = h_new(is_smaller_burst);
    else if (0 == strcmp("pri", argv[1]))
        schedular = h_new(is_smaller_priority);
    else
        exit(1);

    CPU *cpu = c_new();
    // structure of Heap	
    // {
    //     Process *p;
    // }

    int time = 0;
    int n_completed_process = 0;
    int i_process = 0;
    int process_run_time = 0;
    while (n_completed_process != n_process) {
        // Add all process that arrive at time.
	while (process_list[i_process].first_arrival == time) {
            process_list[i_process].arrival = time;
            h_insert(schedular, &process_list[i_process]);
            i_process ++;
        }

	// If cpu idle dispatch new process in to cpu 
        if (!cpu->p)  {
            cpu->p = h_extract(schedular);
            process_run_time = 0;
            if(cpu->p) {
                cpu->p->first_exe_time = cpu->p->first_exe_time
                    ? cpu->p->first_exe_time
                    : time;
            }
	// preemptive
        }else if (0 == strcmp("srtf", argv[1])) {
            if (schedular->arr[1]) {
                if (schedular->arr[1]->burst < cpu->p->burst) {
                    h_insert(schedular, cpu->p);
                    cpu->p = h_extract(schedular);
                    cpu->p->first_exe_time = cpu->p->first_exe_time
                        ? cpu->p->first_exe_time
                        : time;
                }
            }
	// rr
        }else if (0 == strcmp("rr", argv[1]) && QUANTUM == process_run_time) {
            cpu->p->arrival = time;
            h_insert(schedular, cpu->p);
            cpu->p = h_extract(schedular);
            process_run_time = 0;
            cpu->p->first_exe_time = cpu->p->first_exe_time
                ? cpu->p->first_exe_time
                : time;
        }

        if(1 == cpu_run(cpu, time)) n_completed_process++;
        process_run_time ++;
        time++;
    }

    for(int i = 0; i < n_process; i++)
        printf("%s %d %d %d\n", process_list[i].pid, process_list[i].first_arrival, process_list[i].first_exe_time, process_list[i].completed_time);
    return 0;
}
