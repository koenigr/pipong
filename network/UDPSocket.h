/*
 * UDPSocket.h
 *
 *  Created on: 27.06.2019
 *      Author: koenigr
 */

#ifndef NETWORK_UDPSOCKET_H_
#define NETWORK_UDPSOCKET_H_

class UDPSocket {
public:
	virtual ~UDPSocket();
	UDPSocket(int port);

public:
	void sendMessage(char c[]);
	char* receiveMessage();


private:
	void print_address();
};

#endif /* NETWORK_UDPSOCKET_H_ */
