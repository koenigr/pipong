/*
 * AddressManager.cpp
 *
 *  Created on: 27.06.2019
 *      Author: koenigr
 */

#include "AddressManager.h"

#include <arpa/inet.h>
#include <stdio.h>
#include <cstring>
#include <iostream>

#include "../tools/Tools.h"


AddressManager::~AddressManager() {
    std::cout << "Address manager destructor called\n";
}

void AddressManager::init() {

    std::cout << "\nAddressManager::init() start...\n";

    createOwnAddr();
    createBroadcastAddr();

    std::cout << "AddressManager::init() end\n\n";
}

void AddressManager::createOwnAddr() {

    memset((char *) &own_addr, 0, sizeof(own_addr));
    own_addr.sin_family = AF_INET;
    own_addr.sin_addr.s_addr = INADDR_ANY;
    own_addr.sin_port = htons(port);

    //char m[] = "Own ";
    //Tools::print_address(own_addr, m);
}

sockaddr_in AddressManager::getOwnAddr() {

    return own_addr;
}

void AddressManager::createBroadcastAddr() {

    //std::cout << "Create broadcast address\n";

    bzero((char *) &broadcast_addr, sizeof(broadcast_addr));
    broadcast_addr.sin_family = AF_INET;
    // broadcast_addr.sin_addr.s_addr = inet_addr("10.1.1.255");
    broadcast_addr.sin_addr.s_addr = INADDR_BROADCAST;
    broadcast_addr.sin_port = htons(port);

    //char m[] = "Broadcast ";
    //Tools::print_address(broadcast_addr, m);

    //std::cout << "broadcast address created\n";

}

sockaddr_in AddressManager::getBroadcastAddr() const {

    return broadcast_addr;
}

void AddressManager::addParticipant(sockaddr_in participant) {
	// TODO check if valid
	participants.push_back(participant);
    std::cout << "Number of participants: %u" << participants.size();
}

sockaddr_in AddressManager::getParticipant(int pos) {
	// TODO check that participant exists
	return participants[pos];
}

int AddressManager::getNumOfParticipants() {

    //std::cout << "Checking number of participants\n";

	return participants.size();
}



