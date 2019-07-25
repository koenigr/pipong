// test sending and receiving gamestates

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>

#include "../../gamestate/GameState.h"

#define BUFSIZE 1024

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

long int getms(timeval tp) {  
     gettimeofday(&tp, NULL);
     return tp.tv_sec * 1000 + tp.tv_usec / 1000;
}

void print_addr(sockaddr_in addr, int port) {
    char str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(addr.sin_addr), str, INET_ADDRSTRLEN);
    printf("Address: %s\n", str);
    printf("Read portno %d\n", port);
}

void create_addr(sockaddr_in &addr, int port) {
    bzero((char *) &addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
}

void create_broadcast(sockaddr_in &addr, int port) {
    bzero((char *) &addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_BROADCAST;
    addr.sin_port = htons(port);
}

void send_message(sockaddr_in out_addr, int sockfd, char message[]) {
	char buffer[BUFSIZE];
    memset(buffer, 0, BUFSIZE);
    socklen_t clilen = sizeof(out_addr);
    strcpy(buffer, message);
    printf("Send message: %s\n", buffer);
    sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&out_addr, clilen);
}

int main(int argc, char *argv[])
{
     int sockfd;
     int port;
     int clientlen;
     socklen_t clilen;
     char buffer[BUFSIZE];
     struct sockaddr_in own_addr;
     struct sockaddr_in out_addr;
     struct sockaddr_in recv_addr;
     struct timeval tp;
     GameState gs;

     gs.init(0);

     printf("Create socket\n");

     port = 2222;

     sockfd =  socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");

 	 int broadcast=1;
  	 setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST,
        (void *) &broadcast, sizeof(broadcast));

     printf("Socket created.\n");

     create_addr(own_addr, port);

     print_addr(own_addr, port);

     create_broadcast(out_addr, port);

     print_addr(out_addr, port);

     if (bind(sockfd, (struct sockaddr *) &own_addr,
              sizeof(own_addr)) < 0)
              error("ERROR on binding");

     // RECEIVE
     long int ms_start = getms(tp);
     long int ms_then = getms(tp);

     printf("Read socket\n");
     while(true) {

        if (recvfrom(sockfd,buffer, 255, 0, (struct sockaddr *)&recv_addr, &clilen) > 0) {
            printf("Receive message: %s\n",buffer);
        }
        memset(buffer, 0, BUFSIZE);

       if ((ms_then - ms_start) > 1000) {

    	   // SEND
    	   char m[BUFSIZE];
           sprintf(m, "Hi! says port %d", port);
    	   send_message(out_addr, sockfd, m);

           ms_start = getms(tp);
       }

       ms_then = getms(tp);;
     }

     close(sockfd);
     return 0; 
}
