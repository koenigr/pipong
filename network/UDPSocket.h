/*
 * UDPSocket.h
 *
 *  Created on: 27.06.2019
 *      Author: koenigr
 */

#ifndef NETWORK_UDPSOCKET_H_
#define NETWORK_UDPSOCKET_H_

#include <arpa/inet.h>
#include <string>

class UDPSocket {
private:
    int own_sockfd;
    struct sockaddr_in own_addr;
    sockaddr_in recv_addr;

    void print_address();

public:
    virtual ~UDPSocket();
	void init(sockaddr_in own_addr);
	void sendMessage(char* c, sockaddr_in out_addr);
    std::string receiveMessage();
    sockaddr_in getAddressOfReceivedMsg();
    int getSockFD();

};

#endif /* NETWORK_UDPSOCKET_H_ */
