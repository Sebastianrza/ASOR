#include <stdlib.h> 
#include <stdio.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netdb.h> 
#include <errno.h> 
#include <time.h> 
#include <string.h>
#define BUFFSIZE 500
int main(int argc, char **argv) { 
    
    if(argc != 3) {
        fprintf(stderr, "Usage: %s ip port\n", argv[0]); 
        exit(EXIT_FAILURE);
    }


    int sd, s;
    struct sockaddr_storage peer_addr; socklen_t peer_addr_len;
    ssize_t nread;
    char buf[BUFFSIZE];

    // Time
    time_t tiempo = time(NULL); 
    struct tm *tm;
    size_t tam;

// Inicialización struct addr_info
    memset(&hints, 0, sizeof(struct addrinfo)); 
    hints.ai_family = AF_UNSPEC; /* Allow IPv4 or IPv6 */ 
    hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */ 
    hints.ai_ﬂags = AI_PASSIVE;	/* For wildcard IP address */ 
    hints.ai_protocol = 0;	/* Any protocol */ 
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL; 
    hints.ai_next = NULL;

    s = getaddrinfo(argv[1], argv[2], &hints, &result);

    if (s != 0) {
        fprintf(stderr, "error getaddrinfo: %s\n", gai_strerror(s)); 
        exit(EXIT_FAILURE);
    }

    
    sd = socket(result->ai_family, result->ai_socktype, 0);

    if(sd == -1) {
        perror("Socket error");
        exit(EXIT_FAILURE);
    }


    int bd = bind(sd, (struct sockaddr *) result->ai_addr, result->ai_addrlen);

    if(bd == -1) {
        perror("Bind error"); 
        exit(EXIT_FAILURE);
    }
    fd_set fd_set;
    while(1) {

        FD_ZERO(&fd_set);
        FD_SET(0, &fd_set);
        FD_SET(sd, &fd_set);

        if(select(sd + 1, &fd_set, NULL, NULL, NULL) == -1) { 
            perror("Select error");
            exit(EXIT_FAILURE);
        }

        if(FD_ISSET(sd, &fd_set)) {

            peer_addr_len = sizeof(struct sockaddr_storage);
            nread = recvfrom(sd, buf, 2, 0, (struct sockaddr *) &peer_addr, &peer_addr_len);

            if(nread == -1) {
                perror("Recvfrom error");
                exit(EXIT_FAILURE);
            }

            buf[1] = '\0';

            char host[NI_MAXHOST], service[NI_MAXSERV];
            s = getnameinfo((struct sockaddr *) &peer_addr, peer_addr_len, host, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICSERV);

            if (s == 0) {
                printf("Received %ld bytes from %s:%s\n", (long) nread, host, service); 
                if(buf[0] == 't') {
                    tm = localtime(&tiempo);
                    tam = strftime(buf, BUFFSIZE, "%I:%M:%S %p", tm); buf[tam] = '\0';
                    sendto(sd, buf, tam, 0, (struct sockaddr *) &peer_addr, peer_addr_len);
                } else if(buf[0] == 'd') {
                    tm = localtime(&tiempo);
                    tam = strftime(buf, BUFFSIZE, "%Y-%m-%d", tm); buf[tam] = '\0';
                    sendto(sd, buf, tam, 0, (struct sockaddr *) &peer_addr,peer_addr_len);
                    
                }else if(buf[0] == 'q') {
                    close(sd); 
                    exit(EXIT_SUCCESS);
                }else {
                    fprintf(stderr, "Comando %c no soportado\n", buf[0]);
                    exit(EXIT_FAILURE);
                }
            }else {
                fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));
                exit(EXIT_FAILURE);
            }

        }else {
            nread = read(0, &buf, 2); 
            if(nread == -1) {
                perror("Read error"); 
                exit(EXIT_FAILURE);
            }

            buf[1] = '\0';

            printf("Received %ld bytes from console.\n", (long) nread);

            if(buf[0] == 't') {
                tm = localtime(&tiempo);
                tam = strftime(buf, BUFFSIZE, "%I:%M:%S %p", tm); 
                buf[tam] = '\0';
                printf("%s\n", buf);
            }else if(buf[0] == 'd') {
                tm = localtime(&tiempo);
                tam = strftime(buf, BUFFSIZE, "%Y-%m-%d", tm); buf[tam] = '\0';
                printf("%s\n", buf);
            }else if(buf[0] == 'q') {
                exit(EXIT_SUCCESS);
            }else {
                fprintf(stderr, "Comando %c no soportado\n", buf[0]);
                exit(EXIT_FAILURE);
            }
        }
    }
    return 0;
}
