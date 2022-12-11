#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> ,
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <time.h>
#define SIZEBUFF 500

int main(int argc, char **argv){

    if(argc != 3){
        fprintf(stderr, "Usage: %s ip, port \n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int s;
    struct addrinfo hints; struct addrinfo *result;
    struct sockaddr_storage peer_addr; socklen_t peer_addr_len;
    ssize_t nread;
    char buf[SIZEBUFF];

    // TIME
    time_t tiempo; struct tm *tm; size_t tam;
    memset(&hints, 0, sizeof(struct addrinfo)); 
    hints.ai_family = AF_UNSPEC; /* Allow IPv4 or IPv6 */ 
    hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */ 
    hints.ai_ﬂags = AI_PASSIVE;	/* For wildcard IP address */ 
    hints.ai_protocol = 0;	/* Any protocol */ 
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL; hints.ai_next = NULL;

    if (getaddrinfo(argv[1], argv[2], &hints, &result) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(getaddrinfo(argv[1], argv[2], &hints, &result))); 
        exit(EXIT_FAILURE);
    }
    int sd = socket(result->ai_family, result->ai_socktype, 0);

    if( sd == -1) {
        perror("Socket error"); 
        exit(EXIT_FAILURE);
    }

    int bd = bind(sd, (struct sockaddr *) result->ai_addr, result->ai_addrlen); 

    while(1) {
        peer_addr_len = sizeof(struct sockaddr_storage);
        nread = recvfrom(sd, buf, BUFFSIZE, 0, (struct sockaddr *) &peer_addr, &peer_addr_len); 
        
        buf[1] = '\0';

        if(nread == -1) {
            perror("Recvfrom error"); 
            exit(EXIT_FAILURE);
        }

        char host[NI_MAXHOST], service[NI_MAXSERV];

        s = getnameinfo((struct sockaddr *) &peer_addr, peer_addr_len, host, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICSERV);

        if (s == 0) {
        printf("Received %ld bytes from %s:%s\n", (long) nread, host, service); 
            if(buf[0] == 't') {
                tiempo = time(NULL);
                tm = localtime(&tiempo);
                tam = strftime(buf, BUFFSIZE, "%I:%M:%S %p", tm); buf[tam] = '\0';
                sendto(sd, buf, tam, 0, (struct sockaddr *) &peer_addr, peer_addr_len);
            }else if(buf[0] == 'd') {
                tam = strftime(buf, BUFFSIZE, "%Y-%m-%d", tm); buf[tam] = '\0';
                sendto(sd, buf, tam, 0, (struct sockaddr *) &peer_addr, peer_addr_len);
            }else if(buf[0] == 'q') {
                close(sd); 
                exit(EXIT_SUCCESS);
            }else {
                fprintf(stderr, "Comando %c no soportado\n", buf[0]);
            }

        }else {
            fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));
        }

    }
    
    return 0;

}