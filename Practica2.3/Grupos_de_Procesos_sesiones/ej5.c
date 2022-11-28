#include <sched.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
int main() {
  
    int pid = getpid();
    int ppid = getppid();
    int pgid = getpgid(0);
    struct rlimit rlimit;

    int limit = getrlimit(RLIMIT_NOFILE, &rlimit);
    
    if(pgid == -1){
      perror("Error getpgid");
      exit(EXIT_FAILURE);
    }
    if(limit == -1){
      perror("Error getrlimit");
      exit(EXIT_FAILURE);
    }
    int sid = getsid(0);
    if(sid == -1){
      perror("Error getsid");
      exit(EXIT_FAILURE);
    }
    
    printf("PID: %i\n", pid);
    printf("PPID: %i\n", ppid);
    printf("PGID: %i\n", pgid);
    printf("SID: %i\n", sid);
    

    printf("Numero máximo de ficheros: %i\n", rlimit.rlim_max);

    char dir[512];
    getcwd(dir, 512);

    if(dir == NULL){
      perror("Error getcwd");
      exit(EXIT_FAILURE);
    }

    printf("Directorio: %s\n", dir);
    return 0;
}
