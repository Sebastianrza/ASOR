#include <sys/utsname.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>


int main(){

    long value = -1;


    value = pathconf(".", _PC_LINK_MAX);

    if(value == -1){
        printf("Error: %s",strerror(errno));
    }else{
        printf("Valor de LINK_MAX: %lo \n", value);
    }

    value = pathconf(".", _PC_PATH_MAX);

    if(value == -1){
        printf("Error: %s",strerror(errno));
    }else{
        printf("Valor de PATH_MAX: %lo \n", value);
    }


    value = pathconf(".", _PC_NAME_MAX);

    if(value == -1){
        printf("Error: %s",strerror(errno));
    }else{
        printf("Valor de NAME_MAX: %lo \n", value);
    }

    return 0;
    
}