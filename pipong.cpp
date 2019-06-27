
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "network/UDPSocket.h"
#include "tools/Tools.h"
#include "network/AddressManager.h"

AddressManager am;

int main(int argc, char *argv[])
{
	am = new AddressManager;

    if (argc < 3) {
        fprintf(stderr,"usage %s hostname portown portout\n", argv[0]);
        exit(0);
    }

    int port_self = atoi(argv[1]);
    int port_out = atoi(argv[2]);


    UDPSocket pi_socket(port_self);
    struct sockaddr_in recv_addr = am.broadcastAddr(port_out);

    long int ms_start = Tools::getms();
    long int ms_then = Tools::getms();

    while(true) {
    	char * buffer = pi_socket.receiveMessage();

    	if ((ms_then - ms_start) > 1000) {
    		pi_socket.sendMessage("hjkhk");
    		ms_start = Tools::getms();
    	}
    	ms_then = Tools::getms();
    }

    return 0;
}
