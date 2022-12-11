#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char**argv) {


    if (argc != 2) {
        fprintf(stderr, "Usage: %s ip\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    struct addrinfo hints;
    struct addrinfo *result, *iterator;

    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = 0; /* Datagram socket */
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
    hints.ai_protocol = 0;          /* Any protocol */
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;

    if (getaddrinfo(argv[1], NULL, &hints, &result) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(getaddrinfo(argv[1], NULL, &hints, &result)));
        exit(EXIT_FAILURE);
    }


    for (iterator = result; iterator != NULL; iterator = iterator->ai_next) {
        char host[NI_MAXHOST], serv[NI_MAXSERV] ;

        getnameinfo(iterator->ai_addr, iterator->ai_addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST);

        printf("%s\t%i\t%i\n", host, iterator->ai_family, iterator->ai_socktype);
        
    }
    return 0;
}