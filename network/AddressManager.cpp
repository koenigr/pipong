/*
 * AddressManager.cpp
 *
 *  Created on: 27.06.2019
 *      Author: koenigr
 */

#include "AddressManager.h"


AddressManager::AddressManager() {
	// TODO Auto-generated constructor stub

}

AddressManager::~AddressManager() {
	// TODO Auto-generated destructor stub
}

struct sockaddr_in broadcastAddr(int port) {

    struct sockaddr_in broadcast_addr;


    bzero((char *) &out_addr, sizeof(out_addr)); // clear address structure
    out_addr.sin_family = AF_INET; /* setup the host_addr structure for use in bind call */    // server byte order
    //out_addr.sin_addr.s_addr = inet_addr("255.255.255.255"); // automatically be filled with current host's IP address
	 out_addr.sin_addr.s_addr = INADDR_BROADCAST;
    out_addr.sin_port = htons(port); // convert short integer value for port must be converted into network byte order

    {
        // now get it back and print it
        char str[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(out_addr.sin_addr), str, INET_ADDRSTRLEN);
        printf("Address: %s\n", str);
        printf("Read portno %d\n", portout);

    }

    return broadcast_addr;

}
