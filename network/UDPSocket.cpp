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

#include "tools/Tools.h"

#define BUFSIZE 1024
#define ADDRESS = INADDR_ANY;

int sockfd;
int port;
struct sockaddr_in own_addr;


UDPSocket::UDPSocket(int port) {

	printf("Create socket\n");

    sockfd =  socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0);
    if (sockfd < 0)
       Tools::error("ERROR opening socket");

	int broadcast=1;
 	setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST,
      (void *) &broadcast, sizeof(broadcast));

    printf("Socket created.\n");

    bzero((char *) &own_addr, sizeof(own_addr));
    own_addr.sin_family = AF_INET;
    own_addr.sin_addr.s_addr = INADDR_ANY;
    own_addr.sin_port = htons(port);



    printf("Address set\n");

    // bind(int fd, struct sockaddr *local_addr, socklen_t addr_length)
    // bind() passes file descriptor, the address structure,
    // and the length of the address structure
    // This bind() call will bind  the socket to the current IP address on port, portno
    if (bind(sockfd, (struct sockaddr *) &own_addr,
             sizeof(own_addr)) < 0)
             Tools::error("ERROR on binding");

    printf("Socket bound\n");
}

UDPSocket::~UDPSocket() {

    close(sockfd);
}


void sendMessage(char c[]) {


    int clientlen;
    socklen_t clilen;

    char buffer[BUFSIZE] = c;
    // This send() function sends the 13 bytes of the string to the new socket
    printf("send hello world to sockfd\n");
    printf("sockfd: %d\n", sockfd);
    clilen = sizeof(out_addr);
	   bzero(buffer,256);
    sprintf(buffer, "hi! says port %d", portown);
	   //strcpy(buffer, "Sending a message from goddamn port but do not have fucking int");
    n = sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&out_addr, clilen);
    bzero(buffer,256);



}
char* receiveMessage() {

	char buffer[BUFSIZE];
    int n = recvfrom(sockfd,buffer, 255, 0, (struct sockaddr *)&recv_addr, &clilen);
    if (n > 0) {
        printf("Here is the message: %s\n",buffer);
    }
    memset(buffer, BUFSIZE, sizeof(buffer)); // TODO?? BUFSIZE, sizeofbuffer?

}


void print_address() {
	// now get it back and print it
    char str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(own_addr.sin_addr), str, INET_ADDRSTRLEN);
    printf("Address: %s\n", str);
    printf("Read portno %d\n", port);

}

