#include <sched.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
int main() {
	


    pid_t pid = getpid();
    int scheduler = sched_getscheduler(pid);

    
    if(scheduler == -1 ){
        perror("error");
        exit(EXIT_FAILURE);
    }
  //Planificación
    switch (scheduler) {
        case SCHED_OTHER:
        printf("SCHEDULER: OTHER\n");
        break;
        case SCHED_FIFO:
        printf("SCHEDULER: FIFO\n");
        break;
        case SCHED_RR:
        printf("SCHEDULER: RR\n");
        break;
    }

  //Prioridad
    int prio = getpriority(PRIO_PROCESS, 0);

    printf("PRIORIDAD: %i\n", prio);

    //Max y min
    int max = sched_get_priority_max(scheduler);
    int min = sched_get_priority_min(scheduler);

    if(min == -1 || max == -1){
        perror("error");
        exit(EXIT_FAILURE);
    }
    printf("MAX: %i \n", max);
    printf("MIN: %i\n", min);
    return 0;
}
