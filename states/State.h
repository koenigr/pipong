#ifndef STATE_H
#define STATE_H

#include "../network/AddressManager.h"
#include "../message_protocol/MessageProtocol.h"
#include "../network/UDPSocket.h"

class State
{
public:
    State();
    void findPeers();
    void mainLoop(int player_self, AddressManager* am, MessageProtocol* mp, UDPSocket* pi_socket, GameState* gs);
    void showPoints();
};

#endif // STATE_H
