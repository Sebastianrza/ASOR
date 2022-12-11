#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netdb.h>
#include <unistd.h> 
#include <string.h>
#define SIZEBUFF 500

int main(int argc, char** argv) { 
    
    struct addrinfo hints;
    struct addrinfo *result; 
    int j, sf;
    size_t len; ssize_t nread;
    char buf[BUFFSIZE];
    struct sockaddr_storage peer_addr; socklen_t peer_addr_len;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s ip,port,command\n", argv[0]); 
        exit(EXIT_FAILURE);
    }

    memset(&hints, 0, sizeof(struct addrinfo)); 
    hints.ai_family = AF_UNSPEC; /* Allow IPv4 or IPv6 */ 
    hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */ 
    hints.ai_ﬂags = 0;
    hints.ai_protocol = 0;	/* Any protocol */

    
    if (getaddrinfo(argv[1], argv[2], &hints, &result) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerrorgetaddrinfo(argv[1], argv[2], &hints, &result))); exit(EXIT_FAILURE);
    }

    sf = socket(result->ai_family, result->ai_socktype, result->ai_protocol); 
    if(sf == -1) {
        perror("Socket error"); 
        exit(EXIT_FAILURE);
    }

    char host[NI_MAXHOST], serv[NI_MAXSERV];
    sendto(sf, argv[3], 2, 0, result->ai_addr, result->ai_addrlen); 
    
    if (*argv[3] == 'd' || *argv[3] == 't'){
        ssize_t tam = recvfrom(sfd, buf, BUFFSIZE, 0, (struct sockaddr *) &peer_addr, &peer_addr_len);
        buf[tam] = '\0';
        printf("%s\n", buf);
    }
    return 0;
}

