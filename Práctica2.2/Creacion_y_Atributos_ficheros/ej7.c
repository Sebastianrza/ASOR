#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {

	mode_t prev = umask(027); // 027

	int file = open("ej7.txt", O_CREAT | O_RDONLY, 0777);

    if(file != -1){
        printf("Fichero creado. \n");
        close(file);
    }else{
        printf("Error al crear el fichero. \n");
    }
	return 0;
}