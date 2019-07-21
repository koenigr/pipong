#ifndef STATE_H
#define STATE_H

#include "../network/AddressManager.h"
#include "../message_protocol/MessageProtocol.h"
#include "../network/UDPSocket.h"

class StateManager
{
public:
    void init(int player_self, GameState &gs, AddressManager &am, UDPSocket &pi_socket );
    void findPeers(AddressManager am, UDPSocket pi_socket, MessageProtocol mp, GameState gs);
    void mainLoop(int player_self, AddressManager am, MessageProtocol mp, UDPSocket pi_socket, GameState gs);
    void showPoints();

private:
    void receive_messages(UDPSocket &pi_socket, MessageProtocol mp);
    void process_input();
    void update_game_state();
    void deploy_game_state(AddressManager am, UDPSocket pi_socket);
    void display();

};

#endif // STATE_H
