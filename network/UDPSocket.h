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

public:
    virtual ~UDPSocket();
	void init(sockaddr_in own_addr);
	void sendMessage(char* c, sockaddr_in out_addr);
    std::string receiveMessage();
    sockaddr_in getAddressOfReceivedMsg();

private:
	void print_address();
};

#endif /* NETWORK_UDPSOCKET_H_ */
