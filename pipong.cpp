
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

AddressManager am;
UDPSocket pi_socket;
GameState gs;
StateManager state_manager;

int main(int argc, char* argv[]) {

    if(argc < 2) {
        std::cout << "Usage: ./PiPong <player_no>\n";
        exit(1);
    }

    int player_self = atoi(argv[1]);

    state_manager.init(player_self, gs, am, pi_socket);

    state_manager.waitForStartButtonPress();

    // state_manager.findPeers(am, pi_socket, gs);

    // state_manager.gameLoop(am, pi_socket, gs);

    state_manager.showPoints(gs);

    return 0;
}

