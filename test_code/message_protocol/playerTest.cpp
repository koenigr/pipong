#include "../../message_protocol/MessageProtocol.h"
#include "../../gamestate/GameState.h"

#include <iostream>
#include <cassert>

#define BUFSIZE 1024

int main() {

    MessageProtocol mp;
    GameState gs;
    int player_self = 2;

    gs.init(player_self);

    assert(gs.getFrameNo() == 0);

    // PLAYER TESTS

    std::string player_state = mp.createPlayerState(gs);
    std::cout << "created player_state: " << player_state << "\n";
    std::cout << "player_state length: " << player_state.length() << "\n";
    mp.evalMessage(1, player_state, gs);

    gs.incrFrameNo(1);



}
