/*
 * UDPSocket.h
 *
 *  Created on: 27.06.2019
 *      Author: koenigr
 */

#ifndef NETWORK_UDPSOCKET_H_
#define NETWORK_UDPSOCKET_H_

#include <arpa/inet.h>



class UDPSocket {
public:
	virtual ~UDPSocket();
	UDPSocket();

public:
	void init(int port);
	void sendMessage(char* c, sockaddr_in out_addr);
	sockaddr_in receiveMessage(char* c);


private:
	void print_address();
};

#endif /* NETWORK_UDPSOCKET_H_ */
