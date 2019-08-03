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
    static void displayResetBall(const bool draw_ball, const GameState gs);

public:

    //enum States {FIND_PEERS, GAME, COLLISION, FINISH};
    static int actual_state;

    static void init(UDPSocket &pi_socket );
    static void waitForStartButtonPress(UDPSocket &pi_socket, int player_self, GameState &gs);
    static void findPeers(UDPSocket &pi_socket, GameState &gs);
    static void gameLoop(UDPSocket &pi_socket, GameState &gs);
    static void showPoints(GameState &gs, bool &runGame);

    static void setState(int new_state);
    static int getState();
};

#endif // STATE_H
