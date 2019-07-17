#include "../../message_protocol/MessageProtocol.h"
#include "../../gamestate/GameState.h"

#include <iostream>

#define BUFSIZE 1024

int main() {

	MessageProtocol mp;
    GameState gs;
    int player_self = 2;

    gs.init(player_self);

	// REQUEST TESTS

    std::string request = mp.createRequest(gs);
    std::cout << "created request: " << request << "\n";
    std::cout << "request length: " << request.length() << "\n";
    mp.evalMessage(request.substr(7));

    gs.incrFrameNo();

	// RESPONSE TESTS

    std::string response = mp.createResponse(gs);
    std::cout << "created response: " << response << "\n";
    std::cout << "response length: " << response.length() << "\n";
    mp.evalMessage(response.substr(7));

    gs.incrFrameNo();

    // PLAYER TESTS

    std::string player_state = mp.createPlayerState(gs);
    std::cout << "created player_state: " << player_state << "\n";
    std::cout << "player_state length: " << player_state.length() << "\n";
    mp.evalMessage(player_state.substr(7));

    gs.incrFrameNo();

    // COLLISION TESTS

    std::string collision = mp.createCollision(gs);
    std::cout << "created collision: " << collision << "\n";
    std::cout << "collision length: " << collision.length() << "\n";
    mp.evalMessage(collision.substr(7));

    gs.incrFrameNo();

    // FINISH TESTS

    std::string finish = mp.createFinish(gs);
    std::cout << "created finish: " << finish << "\n";
    std::cout << "finish length: " << finish.length() << "\n";
    mp.evalMessage(finish.substr(7));

}
