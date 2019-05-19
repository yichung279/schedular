#include <string.h>
#include <stdio.h>
#include <stdio.h>

#include "lib/Heap.c"
#include "lib/Process.c"

int compare_arrival(const void *a, const void *b){
	Process c = *(Process *)a;
	Process d = *(Process *)b;
	if(c.arrival < d.arrival)
		return -1;
	else if (c.arrival == d.arrival)
		return 0;
	return 1;
}

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
    Process process_list[10000];
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
                process_list[n_process].arrival = atoi(pch);
            pch = strtok (NULL, " ,.-");
        }

        n_process++;
    }

    /* qsort(process_list, n_process, sizeof(Process), compare_arrival); */
    /* for(int i = 0; i < n_process; i++) */
    /*     printf("%s %d %d %d\n", process_list[i].pid, process_list[i].priority, process_list[i].burst, process_list[i].arrival); */
    Heap *schedular;
    if (0 == strcmp("fcfs", argv[1]))
        schedular = h_new(is_smaller_arrival);
    else if (0 == strcmp("sjf", argv[1]))
        schedular = h_new(is_smaller_burst);
    else if (0 == strcmp("pri", argv[1]))
        schedular = h_new(is_smaller_priority);
    else
        exit(1);

    CPU *cpu = c_new();

    int time = 0;
    int n_completed_process = 0;
    int i_process = 0;
    while (n_completed_process != n_process) {
        if (process_list[i_process].arrival == time) {
            h_insert(schedular, &process_list[i_process]);
            i_process ++;
        }

        if (!cpu->p)  {
            cpu->p = h_extract(schedular);
            if(cpu->p)
                cpu->p->first_exe_time = time;
        }


        if(1 == cpu_run(cpu, time)) n_completed_process++;
        time++;
    }

    for(int i = 0; i < n_process; i++)
        printf("%s %d %d %d\n", process_list[i].pid, process_list[i].arrival, process_list[i].first_exe_time, process_list[i].completed_time);
    return 0;
}
