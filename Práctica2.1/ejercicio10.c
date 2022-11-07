#include <string.h>
#include <stdio.h>
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
int main(){

    uid_t uid = getuid();

    printf("Usuario Real: %d \n", getuid());
    printf("Usuario Efectivo: %d \n", geteuid());
    
    printf("Grupo Real: %d \n", getgid());
    printf("Grupo efectivo: %d \n", getegid());

    struct passwd *buf;

    buf = getpwuid(uid);

    printf("Nombre usuario: %s \n", buf->pw_name);
    printf("Directorio home: %s \n", buf->pw_dir);
    printf("Descripcion Usuario: %s \n", buf->pw_gecos);

    return 0;
}