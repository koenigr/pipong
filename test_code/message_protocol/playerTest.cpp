#include "../../message_protocol/MessageProtocol.h"
#include "../../gamestate/GameState.h"
#include "../../Parameters.h"

#include <iostream>
#include <cassert>

#define BUFSIZE 1024

int main() {

    std::cout << "Running PlayerTest\n";

    GameState gs0;
    gs0.init(0);

    GameState gs1;
    gs1.init(1);

    assert(gs0.getFrameNo() == 0);

    // PLAYER TESTS

    std::string player_state = MessageProtocol::createPlayerState(gs0);
    std::cout << "created player_state: " << player_state << "\n";
    std::cout << "player_state length: " << player_state.length() << "\n";
    MessageProtocol::evalMessage(1, player_state, gs0);

    // Moving player 1

    gs1.incrFrameNo(1);
    gs1.decrPoints();
    gs1.setPosition(1, 5);

    assert(gs1.getSelf().getPoints() == INIT_PLAYER_POINTS - 1);
    assert(gs1.getSelf().getPosition() == 5);
    assert(gs0.getPlayer(1).getPoints() == INIT_PLAYER_POINTS);
    assert(gs0.getPlayer(1).getPosition() == 0);

    std::string player_state1 = MessageProtocol::createPlayerState(gs1);
    MessageProtocol::evalMessage(1, player_state1, gs0);

    assert(gs0.getPlayer(1).getPoints() == INIT_PLAYER_POINTS - 1);
    assert(gs0.getPlayer(1).getPosition() == 5);




}
