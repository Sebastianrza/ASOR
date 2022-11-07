#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>

int main(){

    printf("Usuario Real: %d \n", getuid());
    printf("Usuario Efectivo: %d \n", geteuid());
    
    printf("Grupo Real: %d \n", getgid());
    printf("Grupo efectivo: %d \n", getegid());

    /*
    Aseguramos que tiene activado el bit setuid cuando euid o egid se cambie
    al usuario o grupo del fichero.
    */
    return 0;
}