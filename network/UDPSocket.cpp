/*
 * UDPSocket.cpp
 *
 *  Created on: 27.06.2019
 *      Author: koenigr
 */

#include "UDPSocket.h"

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "../tools/Tools.h"

#define BUFSIZE 1024
#define ADDRESS = INADDR_ANY;

int own_sockfd;
int own_port;
struct sockaddr_in own_addr;


UDPSocket::UDPSocket(int own_port) {

	printf("Create socket\n");

    own_sockfd =  socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0);
    if (own_sockfd < 0)
       Tools::error("ERROR opening socket");

	int broadcast=1;
 	setsockopt(own_sockfd, SOL_SOCKET, SO_BROADCAST,
      (void *) &broadcast, sizeof(broadcast));

    printf("Socket created.\n");

    bzero((char *) &own_addr, sizeof(own_addr));
    own_addr.sin_family = AF_INET;
    own_addr.sin_addr.s_addr = INADDR_ANY;
    own_addr.sin_port = htons(own_port);



    printf("Address set\n");

    // bind(int fd, struct sockaddr *local_addr, socklen_t addr_length)
    // bind() passes file descriptor, the address structure,
    // and the length of the address structure
    // This bind() call will bind  the socket to the current IP address on port, portno
    if (bind(own_sockfd, (struct sockaddr *) &own_addr,
             sizeof(own_addr)) < 0)
             Tools::error("ERROR on binding");

    printf("Socket bound\n");
}

UDPSocket::~UDPSocket() {

    close(own_sockfd);
}


void sendMessage(char c[], struct sockaddr_in out_addr) {


    printf("send hello world to sockfd\n");

    int clientlen;
    socklen_t clilen;

    char buffer[BUFSIZE] = c[];
    clilen = sizeof(out_addr);
	bzero(buffer,256);
    sprintf(buffer, "hi! says port %d", own_port); // TODO: send c
    int n = sendto(own_sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&out_addr, clilen);
    bzero(buffer,256);



}
char* receiveMessage() {

	sockaddr_in recv_addr;

	socklen_t clilen;
	char buffer[BUFSIZE];
    int n = recvfrom(own_sockfd,buffer, 255, 0, (struct sockaddr *)&recv_addr, &clilen);
    if (n > 0) {
        printf("Here is the message: %s\n",buffer);
    }
    memset(buffer, BUFSIZE, sizeof(buffer)); // TODO?? BUFSIZE, sizeofbuffer?

    return &buffer;

}



