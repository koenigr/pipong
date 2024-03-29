#include "StateManager.h"
#include "../tools/Tools.h"
#include "../network/AddressManager.h"
#include "../network/UDPSocket.h"
#include "../message_protocol/MessageProtocol.h"
#include "../gamestate/GameState.h"
#include "../Parameters.h"
#include "../display/Display.h"
#include "../input/InputManager.h"

#include <iostream>
#include <cstring>

// PRIVATE

int StateManager::actual_state;
int StateManager::last_collision_frame;

void StateManager::receive_messages(const UDPSocket &pi_socket, GameState &gs) {

    std::string message = pi_socket.receiveMessage();
    MessageProtocol::evalMessage(message, gs);
}

void StateManager::process_input(GameState &gs) {

    int player_pos = InputManager::getPlayerPosition();
    gs.setPosition(gs.getPlayerNo(), player_pos);
}

void StateManager::update_game_state(UDPSocket &pi_socket, GameState &gs) {

    gs.incrFrameNo();
    gs.updateBall(pi_socket);

}

void StateManager::deploy_game_state(const GameState gs, const UDPSocket pi_socket) {

    std::string player_state_msg = MessageProtocol::createPlayerState(gs);

    for (int i = 0; i < AddressManager::getNumOfParticipants(); i++ ) {
        sockaddr_in participant;
        memset((char *) &participant, 0, sizeof(participant));
        AddressManager::getParticipant(i, participant);
        pi_socket.sendMessage(player_state_msg, participant);
    }
}

void StateManager::deploy_collision_state(std::string collision_state_msg, const GameState gs, const UDPSocket pi_socket) {

    for (int i = 0; i < AddressManager::getNumOfParticipants(); i++ ) {
        sockaddr_in participant;
        memset((char *) &participant, 0, sizeof(participant));
        AddressManager::getParticipant(i, participant);
        pi_socket.sendMessage(collision_state_msg, participant);
    }
}

void StateManager::display(const GameState gs) {

    Display::drawGameState(gs);
}

void StateManager::displayResetBall(const bool draw_ball, const GameState gs) {

    Display::drawGameState(draw_ball, gs);

}

// PUBLIC

void StateManager::init(UDPSocket &pi_socket ) {

    std::cout << "\nInitializing PiPong\n";

    Display::init();

    InputManager::init();

    AddressManager::init();

    pi_socket.init(AddressManager::getOwnAddr());

    std::cout << "PiPong Initialization complete\n\n";
}

void StateManager::waitForStartButtonPress(UDPSocket &pi_socket, int player_self, GameState &gs) {

    setState(WAIT_STATE);

    gs.init(player_self);
    gs.resetAllFrames();
    gs.setCountdown(COUNTDOWN_START_VAL);

    std::cout << "\nStateManager::waitForStartButtonPress()...\n";

    while (actual_state == WAIT_STATE) {
        Display::drawHello();
        bool pressed = InputManager::startButtonPressed();
        StateManager::receive_messages(pi_socket, gs);
        if (pressed) {
           setState(FINDPEERS_STATE);
        }
        usleep(1000 / FRAMERATE);
    }

    std::cout << "Start Button pressed or request message received\n";
}

void StateManager::findPeers(UDPSocket &pi_socket, GameState &gs) {

    std::cout << "\nWaiting for peers...\n";

    long int ms_start = Tools::getms();
    long int ms_then = Tools::getms();

    std::cout << "Countdown " << gs.getCountdown() << std::endl;

    while(gs.getCountdown() > 0) {

        receive_messages(pi_socket, gs);

        if ((ms_then - ms_start) > 1000/FRAMERATE) {

            std::string request = MessageProtocol::createRequest(gs);
            pi_socket.sendMessage((char *)request.c_str(), AddressManager::getBroadcastAddr()); // TODO send always to fixed IP addresses.

            std::cout << "Countdown: " << gs.getCountdown() << std::endl;

            gs.decrCountdown();
            gs.incrFrameNo();
            std::cout << gs.getFrameNo() << std::endl;
            Display::drawWaitForPeers(gs);
            ms_start = Tools::getms();

        }
        ms_then = Tools::getms();

    }

    std::cout << "Peer connection completed\n";

}


void StateManager::gameLoop(UDPSocket &pi_socket, GameState &gs) {

    std::cout << "\nStateManager::gameLoop() start...\n";

    setState(GAME_STATE);

    long int ms_start = Tools::getms();
    long int ms_then = Tools::getms();

    last_collision_frame = 0;

    int i = 0;

    while(gs.getSelf().getPoints() > 0 && !(StateManager::getState() == FINISH_STATE)) {
        receive_messages(pi_socket, gs);

        switch(actual_state) {
        case GAME_STATE:
            if ((ms_then - ms_start) > 1000/FRAMERATE) {
                process_input(gs);
                update_game_state(pi_socket, gs);
                deploy_game_state(gs, pi_socket);
                display(gs);
                ms_start = Tools::getms();
                i++;

            }
            break;
        case COLLISION_STATE:
            std::string collision_state_msg = MessageProtocol::createCollision(gs);
            int seed = last_collision_frame;
            bool resetLoop = true;
            bool draw_ball = true;

            gs.newRound(seed);
            int i = 0;
            int j = 0;

            while (resetLoop) {

                if ((ms_then - ms_start) > 1000/FRAMERATE) {

                    deploy_collision_state(collision_state_msg, gs, pi_socket);

                    displayResetBall(draw_ball, gs);

                    i = (i+1) % (FRAMERATE / 4);

                    if (i == 0) {
                        draw_ball = !draw_ball;
                        j++;
                    }


                    if (j >= 8) {
                        setState(GAME_STATE);
                        resetLoop = false;
                    }

                    ms_start = Tools::getms();
                }

                ms_then = Tools::getms();
            }

            break;

    }

    ms_then = Tools::getms();

    }

    std::cout << "StateManager::gameLoop() end\n";
}

void StateManager::showPoints(UDPSocket &pi_socket, GameState &gs, bool &runGame) {

    setState(FINISH_STATE);

    std::cout << "StateManager::showPoints() " << gs.toString() << std::endl;
    bool end = false;
    std::string finish_msg = MessageProtocol::createFinish(gs);
    while (!end) {
        for (int i = 0; i < AddressManager::getNumOfParticipants(); i++ ) {
            sockaddr_in participant;
            memset((char *) &participant, 0, sizeof(participant));
            AddressManager::getParticipant(i, participant);
            pi_socket.sendMessage(finish_msg, participant);
        }
        receive_messages(pi_socket, gs);
        Display::drawPoints(gs);
        bool restartPressed = InputManager::restartButtonPressed();
        if (restartPressed) {
           std::cout << "restart pressed\n";
           end = true;
        }

        bool exitPressed = InputManager::exitButtonPressed();
        if (exitPressed) {
           end = true;
           runGame = false;
           StateManager::setState(WAIT_STATE);
           std::cout << "exit pressed\n";
        }
        usleep(1000 / FRAMERATE);
    }
}

void StateManager::setState(int new_state) {
    actual_state = new_state;
}

int StateManager::getState() {
    return actual_state;
}
