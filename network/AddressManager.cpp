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
#include <vector>

#include "../tools/Tools.h"


int own_port;
struct sockaddr_in own_addr2; //TODO warum geht das nicht, wenn es own_addr heißt?
struct sockaddr_in broadcast_addr;
std::vector<sockaddr_in> participants;

AddressManager::AddressManager() {}

AddressManager::~AddressManager() {}

void AddressManager::print_infos() {
	printf("AddressManager lebe hoch\n");
}

void AddressManager::createOwnAddr(int port) {

	own_port = port;

    bzero((char *) &own_addr2, sizeof(own_addr2));
    own_addr2.sin_family = AF_INET;
    own_addr2.sin_addr.s_addr = INADDR_ANY;
    own_addr2.sin_port = htons(own_port);

    char m[] = "Own ";
    Tools::print_address(own_addr2, m);

    printf("Address set\n");
}

sockaddr_in AddressManager::getOwnAddr() {

    return own_addr2;
}

void AddressManager::createBroadcastAddr(int port) {

	printf("Create broadcast address\n");


    bzero((char *) &broadcast_addr, sizeof(broadcast_addr));
    broadcast_addr.sin_family = AF_INET;
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
    printf("Number of participants: %u", participants.size());
}

sockaddr_in AddressManager::getParticipant(int pos) {
	// TODO check that participant exists
	return participants[pos];
}

int AddressManager::getNumOfParticipants() {
	return participants.size();
}



