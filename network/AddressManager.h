/*
 * AddressManager.h
 *
 *  Created on: 27.06.2019
 *      Author: koenigr
 */

#ifndef NETWORK_ADDRESSMANAGER_H_
#define NETWORK_ADDRESSMANAGER_H_

class AddressManager {
public:
	AddressManager();
	virtual ~AddressManager();
	struct sockaddr_in broadcastAddr(int port);
	void print_address(struct sockaddr_in addr);
};

#endif /* NETWORK_ADDRESSMANAGER_H_ */
