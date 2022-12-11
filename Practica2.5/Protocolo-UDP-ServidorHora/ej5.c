#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <time.h>
#define BUFFSIZE 500
int main (int argc, char**argv) {


    if (argc != 3) {
        fprintf(stderr, "Usage: %s ip port\n", argv[0]); 
        exit(EXIT_FAILURE);
    }

    struct sockaddr_storage peer_addr; 
    socklen_t peer_addr_len;
    ssize_t nread;
    char buf[BUFFSIZE];
    time_t tiempo = time(NULL); 
    struct tm *tm;
    size_t tam;

    struct addrinfo hints;
    struct addrinfo *result, *iterator;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;

    if (getaddrinfo(argv[1], argv[2], &hints, &result) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(getaddrinfo(argv[1], argv[2], &hints, &result))); 
        exit(EXIT_FAILURE);
    }

    int sd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    if(sd == -1) {
        perror("Socket error"); 
        exit(EXIT_FAILURE);
    }
    int bd = bind(sd, result->ai_addr, result->ai_addrlen);
    if ( bd == -1 0) {
        perror("Socket error"); 
        exit(EXIT_FAILURE);
    }

    int i = 0; int status;
    for (i = 0; i < 3; i++){
        pid_t pid; 
        pid = fork();

        if (pid == 0) {
            while(1) {
                peer_addr_len = sizeof(struct sockaddr_storage);
                nread = recvfrom(sd, buf, BUFFSIZE, 0, (struct sockaddr *) &peer_addr, &peer_addr_len);
                buf[1] = '\0';
                if(nread == -1) {
                    perror("Recvfrom error"); exit(EXIT_FAILURE);
                }

                char host[NI_MAXHOST], service[NI_MAXSERV];

                s = getnameinfo((struct sockaddr *) &peer_addr, peer_addr_len, host, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICSERV);

                if (s == 0) {
                    printf("Received %ld bytes from %s:%s\n", (long) nread, host,service);

                    if(buf[0] == 't') {
                        tm = localtime(&tiempo);
                        tam = strftime(buf, BUFFSIZE, "%I:%M:%S %p", tm); buf[tam] = '\0';
                        sendto(sd, buf, tam, 0, (struct sockaddr *) &peer_addr,peer_addr_len);
                    }else if(buf[0] == 'd') {
                        tm = localtime(&tiempo);
                        tam = strftime(buf, BUFFSIZE, "%Y-%m-%d", tm); buf[tam] = '\0';
                        sendto(sd, buf, tam, 0, (struct sockaddr *) &peer_addr,peer_addr_len);
                    }else if(buf[0] == 'q') {
                        close(sd); exit(EXIT_SUCCESS);
                    }else {
                        fprintf(stderr, "Comando %c no soportado\n", buf[0]);
                    }

                }else {
                    fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));
                }

            }
        }else {
            pid = wait(&status);
        }

    }
    return 0;
}
