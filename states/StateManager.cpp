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

// PRIVATE

int StateManager::actual_state;

void StateManager::receive_messages(const UDPSocket &pi_socket, GameState &gs) {

    std::string message = pi_socket.receiveMessage();
    MessageProtocol::evalMessage(message, gs);
}

void StateManager::process_input(GameState &gs) {

    //std::cout << "\nStart processing input...\n";
    int player_pos = InputManager::getPlayerPosition();
    gs.setPosition(gs.getPlayerNo(), player_pos);
    //std::cout << ">>>>>>>>>> new player pos: " << gs.getPosition(gs.getPlayerNo()) << std::endl;

    //std::cout << "Input processing completed\n";
}

void StateManager::update_game_state(GameState &gs) {

    //std::cout << "\nStateManager::update_game_state() start...\n";

    gs.incrFrameNo();
    // std::cout << gs.toString() << "\n";
    gs.updateBall();

    //std::cout << "StateManager::update_game_state() end\n";
}

void StateManager::deploy_game_state(const GameState gs, const UDPSocket pi_socket) {

    //std::cout << "\nStart deploying gamestate..\n";

    std::string player_state_msg = MessageProtocol::createPlayerState(gs);
    // std::cout << "Player state message: " << player_state_msg;

    for (int i = 0; i < AddressManager::getNumOfParticipants(); i++ ) {
        sockaddr_in participant;
        Tools::print_address(participant, "StateManager::deploy_game_state: ");
        AddressManager::getParticipant(i, participant);
        pi_socket.sendMessage(player_state_msg, participant);
    }
    //pi_socket.sendMessage(player_state_msg, am.getBroadcastAddr());

    //std::cout << "Deploying gamestate completed\n";
}

void StateManager::display(const GameState gs) {

    //std::cout << "\nStateManager::display() start...\n";

    Display::drawGameState(gs);

    //std::cout << "StateManager::display() end\n";
}

void StateManager::displayResetBall(const bool draw_ball, const GameState gs) {

    std::cout << "StateManager::displayResetBall() start ..\n";

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

    std::cout << "\nStateManager::waitForStartButtonPress()...\n";

    while (actual_state == WAIT_STATE) {
        Display::drawHello();
        bool pressed = InputManager::startButtonPressed();
        StateManager::receive_messages(pi_socket, gs);
        if (pressed) {
           std::cout << "Pressed\n";
           setState(FINDPEERS_STATE);
        }
        usleep(1000 / FRAMERATE);
    }

    std::cout << "Start Button pressed\n";
}

void StateManager::findPeers(UDPSocket &pi_socket, GameState &gs) {

    std::cout << "\nWaiting for peers...\n";

    long int ms_start = Tools::getms();
    long int ms_then = Tools::getms();

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

    gs.resetAllFrames();
    gs.setCountdown(COUNTDOWN_START_VAL);

    long int ms_start = Tools::getms();
    long int ms_then = Tools::getms();

    int i = 0;
    while(gs.getSelf().getPoints() > 0) {

        receive_messages(pi_socket, gs);

        switch(actual_state) {
        case GAME_STATE:
            if ((ms_then - ms_start) > 1000/FRAMERATE) {
                process_input(gs);
                update_game_state(gs);
                deploy_game_state(gs, pi_socket);
                display(gs);
                ms_start = Tools::getms();
                std::cout << "StateManager::gameLoop() loop no: " << i << std::endl;
                i++;

            }
            break;
        case COLLISION_STATE:
            std::cout << "collision state\n";
            int seed = 0; // TODO number of last collision frame
            gs.newRound(0); //
            bool resetLoop = true;
            bool draw_ball = true;

	int i = 0;
	int j = 0;

            while (resetLoop) {

                if ((ms_then - ms_start) > 1000/FRAMERATE) {

			std::cout << " reset loop " << resetLoop << std::endl;
			std::cout << " draw ball " << draw_ball << std::endl;
			std::cout << " i " << i << std::endl;
			std::cout << " j " << j << std::endl;

                    displayResetBall(draw_ball, gs);
                    i = (i+1) % (FRAMERATE / 4);
                    if (i == 0) {
                        draw_ball = !draw_ball;
                        j++;
                    }


                if (j >= 8) {
                    StateManager::setState(GAME_STATE);
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

void StateManager::showPoints(GameState &gs, bool &runGame) {

    std::cout << "StateManager::showPoints() " << gs.toString() << std::endl;
    bool end = false;
    while (!end) {
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
