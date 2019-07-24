#ifndef STATE_H
#define STATE_H

#include "../network/AddressManager.h"
#include "../message_protocol/MessageProtocol.h"
#include "../network/UDPSocket.h"

class StateManager
{
public:
    void init(int player_self, GameState &gs, AddressManager &am, UDPSocket &pi_socket );
    void findPeers(AddressManager &am, UDPSocket &pi_socket, MessageProtocol &mp, GameState &gs);
    void mainLoop(AddressManager &am, MessageProtocol &mp, UDPSocket &pi_socket, GameState &gs);
    void showPoints();

private:
    void receive_messages(const UDPSocket &pi_socket, const MessageProtocol mp);
    void process_input();
    void update_game_state(GameState &gs);
    void deploy_game_state(const MessageProtocol mp, const GameState gs, const AddressManager am, const UDPSocket pi_socket);
    void display(const GameState gs);

};

#endif // STATE_H
