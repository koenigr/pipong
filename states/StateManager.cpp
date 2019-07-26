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

void StateManager::receive_messages(const UDPSocket &pi_socket, GameState &gs) {

    // std::cout << "\nReceive message\n";

    sockaddr_in recv;
    std::string message = pi_socket.receiveMessage();
    MessageProtocol::evalMessage(actual_state, message, gs);
    recv = pi_socket.getAddressOfReceivedMsg();
    char str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(recv.sin_addr), str, INET_ADDRSTRLEN);


    // std::cout << "Sender address: " << str << "\n";
    // std::cout << "Message received\n";
}

void StateManager::process_input() {

    //std::cout << "\nStart processing input...\n";

    //std::cout << "Input processing completed\n";
}

void StateManager::update_game_state(GameState &gs) {

    std::cout << "\nStart updating gamestate...\n";

    gs.incrFrameNo(actual_state);
    std::cout << gs.toString() << "\n";

    std::cout << "Gamestate updating completed\n";
}

void StateManager::deploy_game_state(const GameState gs, const AddressManager am, const UDPSocket pi_socket) {

    std::cout << "\nStart deploying gamestate..\n";

    std::string player_state_msg = MessageProtocol::createPlayerState(gs);
    std::cout << "Player state message: " << player_state_msg;
    pi_socket.sendMessage(player_state_msg, am.getBroadcastAddr());

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

    actual_state = 0;

    am.init();

    pi_socket.init(am.getOwnAddr());

    std::cout << "PiPong Initialization complete\n\n";
}

void StateManager::findPeers(AddressManager &am, UDPSocket &pi_socket, GameState &gs) {

    std::cout << "\nWaiting for peers...\n";

    long int ms_start = Tools::getms();
    long int ms_then = Tools::getms();

    while(gs.getCountdown() > 0) {

        receive_messages(pi_socket, gs);

        if ((ms_then - ms_start) > 1000/FRAMERATE) {

            std::string request = MessageProtocol::createRequest(gs);
            pi_socket.sendMessage((char *)request.c_str(), am.getBroadcastAddr());

            // TODO send response to all active peers

            std::cout << "Countdown: " << gs.getCountdown() << std::endl;

            gs.setCountdown(gs.getCountdown()-1);

            ms_start = Tools::getms();

        }
        ms_then = Tools::getms();

    }

//    std::cout << "Left for-loop\n";
//    char message[] = "New Participant ";
//    std::cout << "Char message created: " << message << "\n";
//    Tools::print_address(am.getParticipant(0), message);

    std::cout << "Peer connection completed\n";

}


void StateManager::mainLoop(AddressManager &am, UDPSocket &pi_socket, GameState &gs) {

    std::cout << "\nStarting game...\n";

    actual_state = 1;

    long int ms_start = Tools::getms();
    long int ms_then = Tools::getms();

    int i = 0;
    while(i < 10) {

    //receive_messages();



        if ((ms_then - ms_start) > 1000/FRAMERATE) {

            process_input(); // ??
            update_game_state(gs);
            deploy_game_state(gs, am, pi_socket);
            display(gs);
            ms_start = Tools::getms();
            i++;

        }
        ms_then = Tools::getms();

    }

    std::cout << "Game finished\n";
}

void StateManager::showPoints() {

    actual_state = 2;

    std::cout << "\nShow points\n";
    /*  send FSH
        display:    Player 1: ... Points
                    Player 2: ...

        perhaps sort...
    */

    std::cout << "The End\n";
}
