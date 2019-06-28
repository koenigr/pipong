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
	AddressManager();
	virtual ~AddressManager();
	sockaddr_in broadcastAddr(int port);
	void print_infos();

private:
};

#endif /* NETWORK_ADDRESSMANAGER_H_ */
