#ifndef STATE_H
#define STATE_H

#include "../network/AddressManager.h"
#include "../message_protocol/MessageProtocol.h"
#include "../network/UDPSocket.h"

class StateManager
{
private:
    void receive_messages(const UDPSocket &pi_socket, GameState &gs);
    void process_input();
    void update_game_state(GameState &gs);
    void deploy_game_state(const GameState gs, const UDPSocket pi_socket);
    void display(const GameState gs);

public:
    int actual_state;
    void init(int player_self, GameState &gs, UDPSocket &pi_socket );
    void waitForStartButtonPress();
    void findPeers(UDPSocket &pi_socket, GameState &gs);
    void gameLoop(UDPSocket &pi_socket, GameState &gs);
    void showPoints(GameState &gs);

};

#endif // STATE_H
