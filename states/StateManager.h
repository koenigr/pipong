#ifndef STATE_H
#define STATE_H

#include "../network/AddressManager.h"
#include "../message_protocol/MessageProtocol.h"
#include "../network/UDPSocket.h"

class StateManager
{
private:

    static void receive_messages(const UDPSocket &pi_socket, GameState &gs);
    static void process_input(GameState &gs);
    static void update_game_state(GameState &gs);
    static void deploy_game_state(const GameState gs, const UDPSocket pi_socket);
    static void display(const GameState gs);

public:

    //enum States {FIND_PEERS, GAME, COLLISION, FINISH};
    static int actual_state;

    static void init(int player_self, GameState &gs, UDPSocket &pi_socket );
    static void waitForStartButtonPress();
    static void findPeers(UDPSocket &pi_socket, GameState &gs);
    static void gameLoop(UDPSocket &pi_socket, GameState &gs);
    static void showPoints(GameState &gs);

    static void setState(int new_state);
    static int getState();
};

#endif // STATE_H
