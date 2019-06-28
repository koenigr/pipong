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

#include "../tools/Tools.h"

AddressManager::AddressManager() {
	// TODO Auto-generated constructor stub

}

AddressManager::~AddressManager() {
	// TODO Auto-generated destructor stub
}


void AddressManager::print_infos() {
	printf("AddressManager lebe hoch\n");
}

sockaddr_in AddressManager::broadcastAddr(int port) {

	printf("Create broadcast address\n");

    struct sockaddr_in broadcast_addr;

    bzero((char *) &broadcast_addr, sizeof(broadcast_addr));
    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_addr.s_addr = INADDR_BROADCAST;
    broadcast_addr.sin_port = htons(port);

    Tools::print_address(broadcast_addr);

    printf("broadcast address created\n");

    return broadcast_addr;

}


