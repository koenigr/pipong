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
    std::cout << "Address manager destructor calles\n";
}

void AddressManager::init() {

    std::cout << "\nInitializing AddressManager\n";

    createOwnAddr();
    createBroadcastAddr();

    std::cout << "AddressManager Initialization completed\n\n";
}

void AddressManager::createOwnAddr() {

    memset((char *) &own_addr, 0, sizeof(own_addr));
    own_addr.sin_family = AF_INET;
    own_addr.sin_addr.s_addr = INADDR_ANY;
    own_addr.sin_port = htons(port);

    char m[] = "Own ";
    Tools::print_address(own_addr, m);

    std::cout << "Address set\n";
}

sockaddr_in AddressManager::getOwnAddr() {

    return own_addr;
}

void AddressManager::createBroadcastAddr() {

	printf("Create broadcast address\n");

    bzero((char *) &broadcast_addr, sizeof(broadcast_addr));
    broadcast_addr.sin_family = AF_INET;
    // broadcast_addr.sin_addr.s_addr = inet_addr("10.1.1.255");
    broadcast_addr.sin_addr.s_addr = INADDR_BROADCAST;
    broadcast_addr.sin_port = htons(port);

    char m[] = "Broadcast ";
    Tools::print_address(broadcast_addr, m);

    printf("broadcast address created\n");

}

sockaddr_in AddressManager::getBroadcastAddr() {

    return broadcast_addr;
}

void AddressManager::addParticipant(sockaddr_in participant) {
	// TODO check if valid
	participants.push_back(participant);
    printf("Number of participants: %u", static_cast<int>(participants.size()));
}

sockaddr_in AddressManager::getParticipant(int pos) {
	// TODO check that participant exists
	return participants[pos];
}

int AddressManager::getNumOfParticipants() {

    //std::cout << "Checking number of participants\n";

	return participants.size();
}



