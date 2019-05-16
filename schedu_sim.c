#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "lib/Queue.c"
#include "lib/Process.h"
/* #include "lib/CPU.c" */

int main(int argc, char* argv[]){
    char c;

    while ((c = getopt(argc,argv,"d")) != -1) {
        switch(c) {
        case 'd':
            d = atoi(optarg);
            break;
        default:
            usage(argv);
            exit(1);
        }
    }

    if (d == 1)
        char *test_filename = "data_1.txt"
    else if (d == 2)
        char *test_filename = "data_2.txt"
    else if (d == 3)
        char *test_filename = "data_3.txt"
    else
        exit(1)
    /* Process *p1 = p_new("p1", 1, 2, 3); */
    /* Queue *q = q_new(); */
    /* q_push(q, p1); */
    /* q_pop(q); */
}
