#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <iostream>

#include "network/UDPSocket.h"
#include "network/AddressManager.h"
#include "message_protocol/MessageProtocol.h"
#include "gamestate/GameState.h"
#include "states/StateManager.h"

UDPSocket pi_socket;
GameState gs;

int main(int argc, char* argv[]) {

    if(argc < 2) {
        std::cout << "Usage: ./PiPong <player_no>\n";
        exit(1);
    }

    int player_self = atoi(argv[1]);

    StateManager::init(player_self, gs, pi_socket);

	while(true) { // TODO finish button pressed

        // StateManager::waitForStartButtonPress();

        // StateManager::findPeers(pi_socket, gs);

        StateManager::gameLoop(pi_socket, gs);

        StateManager::showPoints(gs);

   }

    return 0;
}

