#include <sys/utsname.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

int main(){

    struct utsname buf;

    if(uname(&buf) == -1){
        perror("Error");
        return -1;
    }else{
        printf("Sysname: %s \n", buf.sysname);
        printf("Nodename: %s \n", buf.nodename);
        printf("Release: %s \n", buf.release);
        printf("Version: %s \n", buf.version);
        printf("Machine: %s \n", buf.machine);
    }

    return 0;
    

}