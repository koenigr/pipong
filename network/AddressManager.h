/*
 * AddressManager.h
 *
 *  Created on: 27.06.2019
 *      Author: koenigr
 */

#ifndef NETWORK_ADDRESSMANAGER_H_
#define NETWORK_ADDRESSMANAGER_H_

#include <arpa/inet.h>


class AddressManager {
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
