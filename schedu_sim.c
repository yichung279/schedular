#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "lib/Queue.c"
#include "lib/Process.h"

int compare_arrival(const void *a, const void *b){
	Process c = *(Process *)a;
	Process d = *(Process *)b;
	if(c.arrival < d.arrival)
		return -1;
	else if (c.arrival == d.arrival)
		return 0;
	return 1;           //傳回  1 代表 a>b
}

int main(int argc, char* argv[]){

    char test_filename[128];
    strcpy(test_filename, argv[1]);
    printf("%s\n", test_filename);

    FILE *trace_file = fopen(test_filename, "r");
    char buf[512];

    int n_process = 0;
    Process process_list[10000];
    while(fgets(buf, 1000, trace_file) != NULL) {
        char *pch;
		pch = strtok (buf," ,.-");
		for(int i = 0; i < 4;i++){
            if (0 == i)
                process_list[n_process].pid = pch;
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

    qsort(process_list, n_process, sizeof(Process), compare_arrival);
    for(int i = 0; i <10; i++)
        printf("%s %d %d %d\n", process_list[i].pid, process_list[i].priority, process_list[i].burst, process_list[i].arrival);

    /* while (fgets(buf, 1000, trace_file) != NULL) { */
    /*  */
    /* } */
    /* Process *p1 = p_new("p1", 1, 2, 3); */
    /* Queue *q = q_new(); */
    /* q_push(q, p1); */
    /* q_pop(q); */
}
