#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/sysmacros.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {


	if (argc != 2) {
		 fprintf(stderr,"Usage: %s <pathname>\n", argv[0]);
		 exit(EXIT_FAILURE);
	}

	struct stat buff;

	int statint = stat(argv[1], &buff);

	if (statint == -1) {
		perror("stat");
        exit(EXIT_FAILURE);
	}

	char* hard = malloc(sizeof(char)*(5 + strlen(argv[1])));
	char* sym = malloc(sizeof(char)*(5 + strlen(argv[1])));
	strcpy(hard, argv[1]);
	strcpy(sym, argv[1]);

	hard = strcat(hard, ".hard");
	sym = strcat(sym, ".sym");

	printf("HARD: %s\n", hard);
	printf("SYM: %s\n", sym);

	mode_t mode = buff.st_mode;

	if (S_ISREG(mode)) {
		printf("%s es un archivo ordinario.\n", argv[1]);

		if (link(argv[1],hard) == -1) {
			perror("Enlace rigido");
            exit(EXIT_FAILURE);
		} else printf("Se ha creado enlace regido.\n");

		if (symlink(argv[1],sym) == -1) {
			perror("Enlace rigido");
            exit(EXIT_FAILURE);
		} else printf("Se ha creado enlace simbólico.\n");

	} else  {
		printf("La ruta %s no es un fichero regular.\n", argv[1]);
	}

	return 0;
}