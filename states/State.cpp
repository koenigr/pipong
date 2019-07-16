#include "State.h"
#include "../network/AddressManager.h"
#include "../network/UDPSocket.h"
#include "../message_protocol/MessageProtocol.h"
#include "../gamestate/GameState.h"

State::State() {}

void State::findPeers() {

}

void State::mainLoop(int player_self, AddressManager* am, MessageProtocol* mp, UDPSocket* pi_socket, GameState* gs) {

    bool LOOP = true;

    while (LOOP) {

        if ( gs->getPlayer(player_self).getPlayerPoints() == 0) {
            LOOP = false;
        }
    }
}

void State::showPoints() {
    /*  send FSH
        display:    Player 1: ... Points
                    Player 2: ...

        perhaps sort...
    */
}
