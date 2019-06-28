
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

void init(int argc, char* argv[]) {

	printf("Initialize PiPong\n");

	am.print_infos();

    if (argc < 3) {
        fprintf(stderr,"usage %s hostname portown portout\n", argv[0]);
        exit(0);
    }

    int port_self = atoi(argv[1]);
    int port_out = atoi(argv[2]);

    am.createOwnAddr(port_self);
    am.createBroadcastAddr(port_out);
    pi_socket.init(am.getOwnAddr());

    printf("Initialization complete\n");
}

sockaddr_in receive_messages() {

	char buffer[BUFSIZE];
	struct sockaddr_in recv_addr = pi_socket.receiveMessage(buffer);

	return recv_addr;

}

void find_peers() {

    long int ms_start = Tools::getms();
    long int ms_then = Tools::getms();

	while(am.getNumOfParticipants() == 0) { // TODO loop until key press to proceed. Display all participants

		receive_messages();

		if ((ms_then - ms_start) > 1000) {

			char message[] = "I want to connect";
			pi_socket.sendMessage(message, am.getBroadcastAddr());

			ms_start = Tools::getms();

		}
		ms_then = Tools::getms();

	}




}



void process_input() {

}

void update_game_state() {

}

void deploy_game_state() {
	char message[] = "Hello you!";
	pi_socket.sendMessage(message, am.getBroadcastAddr());
}

void display() {

}


int main(int argc, char *argv[])
{

	init(argc, argv);

	find_peers();

    long int ms_start = Tools::getms();
    long int ms_then = Tools::getms();

    while(true) {

    	// receive_messages();

    	process_input();

    	update_game_state();

    	if ((ms_then - ms_start) > 1000) {

    		// deploy_game_state();
    		ms_start = Tools::getms();

    	}
    	ms_then = Tools::getms();

    	display();

    }

    return 0;
}

