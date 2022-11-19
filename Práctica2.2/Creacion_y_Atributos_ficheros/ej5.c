#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){


    const char path[] = "/home/cursoredes/ej5.txt";

    int d = open(path, O_CREAT, 0645);

    if(d != -1){
        printf("fichero creado. \n");
        printf("Descriptor = %i \n", d);
    }else{
        printf("error al crear el fichero.\n");
    }

    return 0;
}