
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

#include "Parameters.h"

#include "network/UDPSocket.h"
#include "tools/Tools.h"
#include "network/AddressManager.h"
#include "message_protocol/MessageProtocol.h"

AddressManager am;
MessageProtocol mp;
UDPSocket pi_socket;

void init() {

    printf("Initialize PiPong\n");

    am.print_infos();
    am.createOwnAddr();
    am.createBroadcastAddr();
    pi_socket.init(am.getOwnAddr());

    printf("Initialization complete\n");
}

void receive_messages(sockaddr_in* recv) {

	char buffer[BUFSIZE];

    *recv = pi_socket.receiveMessage(buffer);

}

void find_peers() {

    long int ms_start = Tools::getms();
    long int ms_then = Tools::getms();

    while(am.getNumOfParticipants() == 0) { // TODO loop until key press to proceed. Display all participants

        // TODO: Wie erkennen, dass Versuch Verbindung und NUR dann hinzufügen?
        sockaddr_in * recv;
        receive_messages(recv);
        char str[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(recv.sin_addr), str, INET_ADDRSTRLEN);

        //if (strcmp(str, "255.127.0.0") != 0 && strcmp(str, "0.0.0.0") != 0 ) {
            //am.addParticipant(recv);
        //}

        if ((ms_then - ms_start) > 1000) {

            char request[BUFSIZE];
            mp.createRequest(request, inet_ntoa(am.getOwnAddr().sin_addr));
            pi_socket.sendMessage(request, am.getBroadcastAddr());

            ms_start = Tools::getms();

        }
        ms_then = Tools::getms();

    }

    char message[] = "New Participant ";
    Tools::print_address(am.getParticipant(0), message);


}

void process_input() {

}

void update_game_state() {

}

void deploy_game_state() {
	char message[] = "Gamestate changed";
	pi_socket.sendMessage(message, am.getBroadcastAddr());
}

void display() {

}


int main()
{

	init();

	find_peers();

//    long int ms_start = Tools::getms();
//    long int ms_then = Tools::getms();

//    while(true) {

//    	//receive_messages();

//    	process_input();

//    	update_game_state();

//    	if ((ms_then - ms_start) > 1000) {

//    		//deploy_game_state();
//    		ms_start = Tools::getms();

//    	}
//    	ms_then = Tools::getms();

//    	display();

//    }

    return 0;
}

