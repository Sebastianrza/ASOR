#include <sched.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>



void escribe(char* proceso){

    int pid = getpid();
    int ppid = getppid();
    int pgid = getpgid(0);

     if(pgid == -1){
      perror("Error getpgid");
      exit(EXIT_FAILURE);
    }
 
    int sid = getsid(0);
    if(sid == -1){
      perror("Error getsid");
      exit(EXIT_FAILURE);
    }


    printf("PID: %s%i\n", proceso,pid);
    printf("PPID: %s%i\n", proceso,ppid);
    printf("PGID: %s%i\n",proceso, pgid);
    printf("SID: %s%i\n", proceso,sid);

    struct rlimit rlimit;

    int limit = getrlimit(RLIMIT_NOFILE, &rlimit);
 
    if(limit == -1){
      perror("Error getrlimit");
      exit(EXIT_FAILURE);
    }
    printf("Numero máximo de ficheros: %i\n", rlimit.rlim_max);
    char dir[512];
    getcwd(dir, 512);

    if(dir == NULL){
      perror("Error getcwd");
      exit(EXIT_FAILURE);
    }

    printf("Directorio: %s\n", dir);
}
int main() {
  
   pid_t pid = fork();

   if(pid == -1) {
    perror("error fork");
    exit(EXIT_FAILURE);
   }else if(pid == 0)//proceso hijo
   {
        setsid();
        chdir("/tmp");
        escribe("hijo");
   }else{
        escribe("padre");
   }

   return 0;
}
