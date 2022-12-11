#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <sys/types.h>
#include <sys/socket.h> 
#include <netdb.h> 
#include <unistd.h> 
#include <string.h>
#define BUFFSIZE 500

int main(int argc, char** argv) { 
    
    if (argc != 3) {
        fprintf(stderr, "Usage: %s ip port\n", argv[0]); 
        exit(EXIT_FAILURE);
    }

    struct addrinfo hints; struct addrinfo *result;
    hints.ai_family = AF_UNSPEC; /* Allow IPv4 or IPv6 */ 
    hints.ai_socktype = SOCK_STREAM; /* Stream socket */ 
    hints.ai_ﬂags = AI_PASSIVE;

    int s = getaddrinfo(argv[1], argv[2], &hints, &result); 
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s)); 
        exit(EXIT_FAILURE);
    }

    int sd = socket(result->ai_family, result->ai_socktype, result->ai_protocol); 
    connect(sd, (struct sockaddr *) result->ai_addr, result->ai_addrlen);

    if(sd == -1) {
        perror("Socket error"); 
        exit(EXIT_FAILURE);
    }

    ssize_t nread;
    char buf[BUFFSIZE];
    char host[NI_MAXHOST], serv[NI_MAXSERV];

    while(1) {
        nread = read(0, buf, BUFFSIZE); 
        buf[nread] = '\0';

        if(nread == 2 && buf[0] == 'q'){ 
            break;
        }

        send(sd, buf, nread, 0);

        nread = recv(sd, buf, BUFFSIZE, 0); 
        buf[nread] = '\0';
        printf("%s", buf);
    }
    close(sd); 
    
    return 0;
}

