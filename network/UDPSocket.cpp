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

    std::cout << "\nInitializing UDPSocket\n";

	own_addr = addr;

    std::cout << "Create socket\n";

    own_sockfd =  socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0);
    std::cout << own_sockfd << "\n";
    if (own_sockfd < 0)
    {
    	Tools::error("ERROR opening socket");
    }

	int broadcast=1;
    int sockop = setsockopt(own_sockfd, SOL_SOCKET, SO_BROADCAST, (void *) &broadcast, sizeof(broadcast));

    std::cout << "Socket " << own_sockfd << " created.\n";
    std::cout << "Return of sockopt: " << sockop << "\n";

    // bind(int fd, struct sockaddr *local_addr, socklen_t addr_length)
    // bind() passes file descriptor, the address structure,
    // and the length of the address structure
    // This bind() call will bind  the socket to the current IP address on port, portno
    if (bind(own_sockfd, (struct sockaddr *) &own_addr,
             sizeof(own_addr)) < 0)
    	Tools::error("ERROR on binding");

    printf("Socket bound\n");

    std::cout << "UDPSocket Initialization completed\n\n";
}


void UDPSocket::sendMessage(char* c, const sockaddr_in &out_addr) const {

    std::cout << "\nUDPSocket::sendMessage start...\n";

    char buffer[BUFSIZE];
    strncpy(buffer, c, BUFSIZE);
    buffer[BUFSIZE - 1] = '\0';

    // std::cout << "Message: " << buffer << "\n";

    Tools::print_address(out_addr, "UPDSocket::sendMessage: ");
    int n = sendto(own_sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&out_addr, sizeof(out_addr));
    if (n < 1) {
        std::cout << "Problems with sending. Return value =" << n << "\n";
    }
    // std::cout << "Error no: " << errno << "\n";
    // std::cout << EBADF << "\n"; // An invalid descriptor was specified.
    std::cout << "Message sent from port " << std::to_string(ntohs(own_addr.sin_port)) << " to port " << std::to_string(ntohs(out_addr.sin_port)) << " with return code " << std::to_string(n) <<"\n";

    std::cout << "UDPSocket::sendMessage end\n";
}

std::string UDPSocket::receiveMessage() const {

    // std::cout << "\nUDPSocket starts receiving message...\n";

	socklen_t clilen;
    char buffer[BUFSIZE];

    int n = recvfrom(own_sockfd, buffer, 255, 0, (struct sockaddr *)&recv_addr, &clilen);
    if (n > 0) {

//        // TODO: was soll hier passieren?
        std::cout << "\nReceived a message\n";
        std::cout << "Here is the message: " << buffer << "\n";
        char m[] = "Receive address ";
        Tools::print_address(recv_addr, m);
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


