
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

#include "Parameters.h"

#include "network/UDPSocket.h"
#include "tools/Tools.h"
#include "network/AddressManager.h"

AddressManager am;
UDPSocket pi_socket;
struct sockaddr_in broadcast_addr;

void init(int argc, char* argv[]) {

	printf("Initialize PiPong\n");

	am.print_infos();

    if (argc < 3) {
        fprintf(stderr,"usage %s hostname portown portout\n", argv[0]);
        exit(0);
    }

    int port_self = atoi(argv[1]);
    int port_out = atoi(argv[2]);

    pi_socket.init(port_self);

    broadcast_addr = am.broadcastAddr(port_out);
    Tools::print_address(broadcast_addr);

    printf("Initialization complete\n");
}

void receive_messages() {

	char buffer[BUFSIZE];
	struct sockaddr_in recv_addr = pi_socket.receiveMessage(buffer);
	Tools::print_address(recv_addr);

}


int main(int argc, char *argv[])
{

	init(argc, argv);

    long int ms_start = Tools::getms();
    long int ms_then = Tools::getms();

    while(true) {


    	if ((ms_then - ms_start) > 1000) {

    		char message[] = "Hello you!";
    		pi_socket.sendMessage(message, broadcast_addr);

    		ms_start = Tools::getms();

    	}
    	ms_then = Tools::getms();
    }

    return 0;
}

