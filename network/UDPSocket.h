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
    void init(const sockaddr_in &own_addr);
    void sendMessage(const std::string c, const sockaddr_in &out_addr) const;
    std::string receiveMessage() const;
    sockaddr_in getAddressOfReceivedMsg() const;
    int getSockFD();

};

#endif /* NETWORK_UDPSOCKET_H_ */
