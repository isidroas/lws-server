#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

struct sockaddr_in addr;
int socketfd, connfd;

void led_tcp_initialize(){
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd==-1){
        printf("Error in socket creation\n");
        exit(1);
    }

    printf("Socket created\n");

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = inet_addr("10.42.0.157"); 

    connfd = connect(socketfd,(struct sockaddr *) &addr, sizeof(addr));
    if (connfd!=0){
        printf("Fail to connect to server\n");
        exit(1);
    }
    printf("Connected to server\n");
}


void led_tcp_send(int len, char *buf){
    send(socketfd, buf, len, 0);
}

void led_tcp_close(){
    close(socketfd);
}
