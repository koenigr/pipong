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

    static std::string addr_arr[4];
    static int port;
    static struct sockaddr_in own_addr;
    static struct sockaddr_in broadcast_addr;
    static std::vector<sockaddr_in> participants;

    static void createBroadcastAddr();
    static void createOwnAddr();


public:
    static void init();
    static sockaddr_in getBroadcastAddr();
    static sockaddr_in getOwnAddr();
    static void print_infos();
    static void addParticipant(int const player_no);
    static void getParticipant(int pos, sockaddr_in& participant);
    static int getNumOfParticipants();

private:
};

#endif /* NETWORK_ADDRESSMANAGER_H_ */
