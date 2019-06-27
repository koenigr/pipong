/*
 * AddressManager.cpp
 *
 *  Created on: 27.06.2019
 *      Author: koenigr
 */

#include "AddressManager.h"

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>


AddressManager::AddressManager() {
	// TODO Auto-generated constructor stub

}

AddressManager::~AddressManager() {
	// TODO Auto-generated destructor stub
}

struct sockaddr_in broadcastAddr(int port) {

    struct sockaddr_in broadcast_addr;


    bzero((char *) &broadcast_addr, sizeof(broadcast_addr));
    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_addr.s_addr = INADDR_BROADCAST;
    broadcast_addr.sin_port = htons(port);

    print_address(broadcast_addr);

    return broadcast_addr;

}



void print_address(struct sockaddr_in addr) {
    char str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(addr.sin_addr), str, INET_ADDRSTRLEN);
    printf("Address: %s\n", str);
}
