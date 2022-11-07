#include <sys/utsname.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>


int main(){

    long value = 1;

    value = sysconf(_SC_ARG_MAX);

    if(value == -1){
        printf("Error en ARG_MAX");
    }else{
        printf("Valor ARG_MAX: %lo \n", value);
    }

    value = sysconf(_SC_CHILD_MAX);
    if(value == -1){
        printf("Error en CHILD_MAX");
    }else{
        printf("Valor CHILD_MAX: %lo \n", value);
    }

    value = sysconf(_SC_OPEN_MAX);
    if(value == -1){
        printf("Error en OPEN_MAX");
    }else{
        printf("Valor OPEN_MAX: %lo \n", value);
    }

    return 0;
}