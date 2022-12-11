#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <sys/types.h>
#include <sys/socket.h> 
#include <netdb.h> 
#include <string.h>
#define BUFFSIZE 500

int main(int argc, char** argv) { 
    
    if (argc != 3) {
        fprintf(stderr, "Usage: %s ip port\n", argv[0]); 
        exit(EXIT_FAILURE);
    }

    struct addrinfo hints; struct addrinfo *result;

    memset(&hints, 0, sizeof(struct addrinfo)); 
    hints.ai_family = AF_UNSPEC; /* Allow IPv4 or IPv6 */ 
    hints.ai_socktype = SOCK_STREAM; /* Stream socket */
    hints.ai_ﬂags = AI_PASSIVE;	/* For wildcard IP address */

    int s = getaddrinfo(argv[1], argv[2], &hints, &result); if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s)); 
        exit(EXIT_FAILURE);
    }

    int sd = socket(result->ai_family, result->ai_socktype, 0); 
    if(sd == -1) {
        perror("Socket error"); exit(EXIT_FAILURE);
    }

    int bd = bind(sd, (struct sockaddr *) result->ai_addr, result->ai_addrlen);

    if(bd == -1) {
        perror("Bind error"); 
        exit(EXIT_FAILURE);
    }

    listen(sd, 5); 
    int clisd;
    struct sockaddr_storage addr; 
    socklen_t addrlen = sizeof(addr); 
    ssize_t nread;
    char buf[BUFFSIZE];
    char host[NI_MAXHOST], service[NI_MAXSERV]; 
    
    while(1) {
        clisd = accept(sd, (struct sockaddr *) &addr, &addrlen);

        pid_t pid;
        pid = fork(); 
        
        if (pid == 0) {
            s = getnameinfo((struct sockaddr *) &addr, addrlen, host, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);

            while(1) {

                if(s == 0) {
                    printf("Conexión desde Host: %s Puerto: %s\n", host, service);
                    do {
                        nread = recv(clisd, buf, 80, 0);
                        if(nread == 0){
                            printf("conexión terminada\n");
                        }else{
                            buf[nread] = '\0';
                            send(clisd, buf, nread,0);
                        }
                    }while(nread>0);
                }else{
                    fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));
                    exit(EXIT_FAILURE);
                }
            }
            close(clisd);
        }else{
            close(clisd);
        }
    }
    close(sd);

    return 0;
}