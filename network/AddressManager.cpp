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

std::string AddressManager::addr_arr[4] = {"10.1.1.10", "10.1.1.20", "10.1.1.16", "10.1.1.17"};
int AddressManager::port = 2222;

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
    broadcast_addr.sin_addr.s_addr = inet_addr("10.1.1.255");
    //broadcast_addr.sin_addr.s_addr = INADDR_BROADCAST;
    broadcast_addr.sin_port = htons(port);

    //char m[] = "Broadcast ";
    //Tools::print_address(broadcast_addr, m);

    //std::cout << "broadcast address created\n";

}

sockaddr_in AddressManager::getBroadcastAddr() {

    return broadcast_addr;
}


// TODO do not add oneself
void AddressManager::addParticipant(const int player_no) {

    if (player_no > 3) {
        Tools::error("AddressManager::addParticipant(): Trying to access non-existing participant\n");
    }

    struct sockaddr_in participant;
    inet_pton(AF_INET, addr_arr[player_no].c_str(), &(participant.sin_addr));
    // TODO: port?
	participants.push_back(participant);

}

void AddressManager::getParticipant(int pos, sockaddr_in &participant) {
    if (pos >= (int) participants.size()) {
        Tools::error("AddressManager::getParticipant(): Trying to get non-existing participant\n");
    }
    participant = participants[pos];
}

int AddressManager::getNumOfParticipants() {

	return participants.size();
}



