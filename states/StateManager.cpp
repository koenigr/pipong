#include "StateManager.h"
#include "../tools/Tools.h"
#include "../network/AddressManager.h"
#include "../network/UDPSocket.h"
#include "../message_protocol/MessageProtocol.h"
#include "../gamestate/GameState.h"
#include "../Parameters.h"
#include "../display/Display.h"

#include <iostream>

// PRIVATE

void StateManager::receive_messages(const UDPSocket pi_socket, const MessageProtocol mp) {

    // std::cout << "\nReceive message\n";

    sockaddr_in recv;
    std::string message = pi_socket.receiveMessage();
    mp.evalMessage(message);
    recv = pi_socket.getAddressOfReceivedMsg();
    char str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(recv.sin_addr), str, INET_ADDRSTRLEN);


    // std::cout << "Sender address: " << str << "\n";
    // std::cout << "Message received\n";
}

void StateManager::process_input() {

    std::cout << "\nStart processing input...\n";

    std::cout << "Input processing completed\n";
}

void StateManager::update_game_state() {

    std::cout << "\nStart updating gamestate...\n";

    std::cout << "Gamestate updatint completed\n";
}

void StateManager::deploy_game_state(const AddressManager am, const UDPSocket pi_socket) {

    std::cout << "\nStart deploying gamestate..\n";

    char message[] = "Gamestate changed";
    pi_socket.sendMessage(message, am.getBroadcastAddr());

    std::cout << "Deploying gamestate completed\n";
}

void StateManager::display(const GameState gs) {

    std::cout << "\nStart display...\n";

    Display::drawGameState(gs);

    std::cout << "Display completed\n";
}

// PUBLIC

void StateManager::init(int player_self, GameState &gs, AddressManager &am, UDPSocket &pi_socket ) {

    std::cout << "\nInitializing PiPong\n";

    gs.init(player_self);

    am.init();

    pi_socket.init(am.getOwnAddr());

    std::cout << "PiPong Initialization complete\n\n";
}

void StateManager::findPeers(AddressManager &am, UDPSocket &pi_socket, MessageProtocol &mp, GameState &gs) {

    std::cout << "\nWaiting for peers...\n";

    long int ms_start = Tools::getms();
    long int ms_then = Tools::getms();

   for (int i = 0; i < 50; i++) {

        // std::cout << "Entered while-loop\n";

        StateManager::receive_messages(pi_socket, mp);

        // std::cout << "Again in while loop\n";

        if ((ms_then - ms_start) > 1000) {

            std::string request = mp.createRequest(gs);
            std::cout << "find peers request: " << request << "\n";
            Tools::print_address(am.getBroadcastAddr(), "findPeers broadcast addr: ");
            pi_socket.sendMessage((char *)request.c_str(), am.getBroadcastAddr());

            ms_start = Tools::getms();

        }
        ms_then = Tools::getms();

    }

    char message[] = "New Participant ";
    Tools::print_address(am.getParticipant(0), message);

    std::cout << "Peer connection completed\n";

}


void StateManager::mainLoop(AddressManager &am, MessageProtocol &mp, UDPSocket &pi_socket, GameState &gs) {

    std::cout << "\nStarting game...\n";

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

//    bool LOOP = true;

//    while (LOOP) {

//        if ( gs.getPlayer(player_self).getPlayerPoints() == 0) {
//            LOOP = false;
//        }
//    }

    std::cout << "Game finished\n";
}

void StateManager::showPoints() {

    std::cout << "\nShow points\n";
    /*  send FSH
        display:    Player 1: ... Points
                    Player 2: ...

        perhaps sort...
    */

    std::cout << "The End\n";
}
