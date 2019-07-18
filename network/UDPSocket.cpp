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
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "../tools/Tools.h"
#include "../Parameters.h"


int own_sockfd;
struct sockaddr_in own_addr;
sockaddr_in recv_addr;

UDPSocket::~UDPSocket() {

    close(own_sockfd);
}

void UDPSocket::init(sockaddr_in addr) {

	own_addr = addr;

	printf("Create socket\n");

    own_sockfd =  socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0);
    if (own_sockfd < 0)
    {
    	Tools::error("ERROR opening socket");
    }

	int broadcast=1;
 	setsockopt(own_sockfd, SOL_SOCKET, SO_BROADCAST,
      (void *) &broadcast, sizeof(broadcast));

    printf("Socket created.\n");


    // bind(int fd, struct sockaddr *local_addr, socklen_t addr_length)
    // bind() passes file descriptor, the address structure,
    // and the length of the address structure
    // This bind() call will bind  the socket to the current IP address on port, portno
    if (bind(own_sockfd, (struct sockaddr *) &own_addr,
             sizeof(own_addr)) < 0)
    	Tools::error("ERROR on binding");

    printf("Socket bound\n");
}


void UDPSocket::sendMessage(char* c, sockaddr_in out_addr) {

    printf("Send message to out_addr\n");

    char buffer[BUFSIZE];
    strncpy(buffer, c, BUFSIZE);
    buffer[BUFSIZE - 1] = '\0';

    int n = sendto(own_sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&out_addr, sizeof(out_addr));

    printf("Message sent from port %d to port %d with return code %d\n", ntohs(own_addr.sin_port), ntohs(out_addr.sin_port), n);

}

std::string UDPSocket::receiveMessage() {

    // std::cout << "\nUDPSocket starts receiving message...\n";

	socklen_t clilen;
    char buffer[BUFSIZE];

    int n = recvfrom(own_sockfd, buffer, 255, 0, (struct sockaddr *)&recv_addr, &clilen);
    if (n > 0) {

//        // TODO: was soll hier passieren?
//        printf("Here is the message: %s\n", buffer);
//        char m[] = "Receive address ";
//        Tools::print_address(recv_addr, m);
    }

    std::string out(buffer);

    // std::cout << "\nUDPSocket receiving complete\n";

    return out;
}

sockaddr_in UDPSocket::getAddressOfReceivedMsg() {

    // std::cout << "\nReturning address of received message...\n";

    return recv_addr;
}


