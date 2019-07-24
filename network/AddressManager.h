/*
 * AddressManager.h
 *
 *  Created on: 27.06.2019
 *      Author: koenigr
 */

#ifndef NETWORK_ADDRESSMANAGER_H_
#define NETWORK_ADDRESSMANAGER_H_

#include <arpa/inet.h>
#include <string>
#include <vector>

class AddressManager {
private:
    std::string addr_arr[4] = {"10.1.1.10", "10.1.1.20", "10.1.1.16", "10.1.1.17"};

    int port = 2222;
    struct sockaddr_in own_addr2; //TODO warum geht das nicht, wenn es own_addr heißt?
    struct sockaddr_in broadcast_addr;
    std::vector<sockaddr_in> participants;


public:
    ~AddressManager();
	void createBroadcastAddr();
	void createOwnAddr();
	sockaddr_in getBroadcastAddr();
	sockaddr_in getOwnAddr();
	void print_infos();
	void addParticipant(sockaddr_in participant);
	sockaddr_in getParticipant(int pos);
	int getNumOfParticipants();

private:
};

#endif /* NETWORK_ADDRESSMANAGER_H_ */
