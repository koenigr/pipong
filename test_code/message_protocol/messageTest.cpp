#include "../../message_protocol/MessageProtocol.h"
#include "../../gamestate/GameState.h"

#include <iostream>
#include <cassert>

#define BUFSIZE 1024

int main() {

    GameState gs;
    int player_self = 2;

    gs.init(player_self);

	// REQUEST TESTS

    assert(gs.getSelf().isActive());

    std::string request = MessageProtocol::createRequest(gs);
    std::cout << "created request: " << request << "\n";
    std::cout << "request length: " << request.length() << "\n";
    MessageProtocol::evalMessage(0, request, gs);

    // PLAYER TESTS

    std::string player_state = MessageProtocol::createPlayerState(gs);
    std::cout << "created player_state: " << player_state << "\n";
    std::cout << "player_state length: " << player_state.length() << "\n";
    MessageProtocol::evalMessage(1, player_state, gs);

    gs.incrFrameNo();

    // COLLISION TESTS

    std::string collision = MessageProtocol::createCollision(gs);
    std::cout << "created collision: " << collision << "\n";
    std::cout << "collision length: " << collision.length() << "\n";
    MessageProtocol::evalMessage(1, collision, gs);

    gs.incrFrameNo();

    // FINISH TESTS

    std::string finish = MessageProtocol::createFinish(gs);
    std::cout << "created finish: " << finish << "\n";
    std::cout << "finish length: " << finish.length() << "\n";
    MessageProtocol::evalMessage(2, finish, gs);

}
