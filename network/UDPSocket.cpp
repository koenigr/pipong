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



UDPSocket::~UDPSocket() {
    std::cout << "CLOSING SOCKETFD!!!!\n";
}

void UDPSocket::init(const sockaddr_in& addr) {

    std::cout << "\nUDPSocket::init() start...\n";

	own_addr = addr;
    own_sockfd =  socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0);

    if (own_sockfd < 0)
    {
    	Tools::error("ERROR opening socket");
    }

	int broadcast=1;
    int sockop = setsockopt(own_sockfd, SOL_SOCKET, SO_BROADCAST, (void *) &broadcast, sizeof(broadcast));
    if (sockop != 0) {
        std::cout << "Errno: " << errno << std::endl;
        Tools::error("ERROR on setsockopt");
    }

    if (bind(own_sockfd, (struct sockaddr *) &own_addr, sizeof(own_addr)) < 0) {
        Tools::error("ERROR on binding");
    }

    std::cout << "UDPSocket ::init() end\n\n";
}


void UDPSocket::sendMessage(const std::string c, const sockaddr_in &out_addr) const {

    std::cout << "\nUDPSocket::sendMessage start...\n";

    char buffer[BUFSIZE];
    strncpy(buffer, c.c_str(), BUFSIZE);
    buffer[BUFSIZE - 1] = '\0';

    int n = sendto(own_sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&out_addr, sizeof(out_addr));
    if (n < 1) {
        std::cout << "Problems with sending. Return value =" << n << "\n";
    }
}

std::string UDPSocket::receiveMessage() const {

    // std::cout << "\nUDPSocket starts receiving message...\n";

	socklen_t clilen;
    char buffer[BUFSIZE];
    memset(buffer, 0, sizeof(buffer));

    int n = recvfrom(own_sockfd, buffer, 255, 0, (struct sockaddr *)&recv_addr, &clilen);
    if (n > 0) {

//        // TODO: was soll hier passieren?
        //std::cout << "\nReceived a message\n";
        //std::cout << "Here is the message: " << buffer << "\n";
        //char m[] = "Receive address ";
        //Tools::print_address(recv_addr, m);
    }

    std::string out_str(buffer);

    // std::cout << "\nUDPSocket receiving complete\n";

    return out_str;
}

sockaddr_in UDPSocket::getAddressOfReceivedMsg() const {

    // std::cout << "\nReturning address of received message...\n";

    return recv_addr;
}

int UDPSocket::getSockFD() {
    return own_sockfd;
}


