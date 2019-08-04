/*
 * MessageProtocol.cpp
 *
 *  Created on: 29.06.2019
 *      Author: koenigr
 */

#include "MessageProtocol.h"
#include "../states/StateManager.h"
#include "../Parameters.h"

#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <cstring>

#define MAIN_HEADER "PIPONG"
#define DELIMITER ":"
#define REQUEST_TYPE "REQ"
#define PLAYER_STATE_TYPE "PST"
#define COLLISION_TYPE "COL"
#define FINISH_TYPE "FIN"

#define INT " %d"
#define UINT " %u"
#define REMAIN "%[\001-\377]"
#define FRAME "FRAME "
#define PLAYERNO "PLAYERNO "
#define POSITION "POSITION "
#define POINTS "POINTS "
#define COUNTDOWN "COUNTDOWN "

std::string MessageProtocol::createRequest(GameState gs) {

    //std::cout << "\nMessageProtocol::createRequest() start...\n";

    std::stringstream x;
    x   << MAIN_HEADER
        << DELIMITER << REQUEST_TYPE
        << DELIMITER << PLAYERNO << gs.getPlayerNo()
        << DELIMITER << FRAME << gs.getFrameNo()
        << DELIMITER << COUNTDOWN << gs.getCountdown();

    std::string request = x.str();

    std::cout << "\nMessageProtocol::createRequest: " << request << std::endl;
    //std::cout << "MessageProtocol::createRequest() end\n";

    return request;
}

std::string MessageProtocol::createPlayerState(GameState gs) {

    //std::cout << "\nStarting to create playerState message...\n";

    std::stringstream x;
    x   << MAIN_HEADER
        << DELIMITER << PLAYER_STATE_TYPE
        << DELIMITER << FRAME << gs.getFrameNo()
        << DELIMITER << PLAYERNO << gs.getPlayerNo()
        << DELIMITER << POSITION << gs.getSelf().getPosition()
        << DELIMITER << POINTS << gs.getSelf().getPoints();

    std::string player_state = x.str();

    // std::cout << "\nMessageProtocol::createPlayerState(): " << player_state << std::endl;
    //std::cout << "Player_state creation completed\n";

    return player_state;
}

std::string MessageProtocol::createCollision(GameState gs) {

    //std::cout << "\nStarting to create collision message...\n";

    std::stringstream x;
    x   << MAIN_HEADER
        << DELIMITER  << COLLISION_TYPE
        << DELIMITER << FRAME << gs.getFrameNo()
        << DELIMITER << PLAYERNO << gs.getPlayerNo();
    // TODO random angle

    std::string collision = x.str();

    std::cout << "\nMessageProtocol::createCollision(): " << collision << std::endl;
    //std::cout << "Collision creation completed\n";

    return collision;
}

std::string MessageProtocol::createFinish(GameState gs) {

    //std::cout << "\nStarting to create finish message...\n";

    std::stringstream x;
    x   << MAIN_HEADER
        << DELIMITER << FINISH_TYPE
        << DELIMITER << FRAME << gs.getFrameNo()
        << DELIMITER << PLAYERNO << gs.getPlayerNo()
        << DELIMITER << POINTS << gs.getSelf().getPoints();

    std::string finish = x.str();

    std::cout << "\nMessageProtocol::createFinish(): " << finish << std::endl;
    //std::cout << "Finish creation completed\n";

    return finish;
}


void MessageProtocol::evalMessage(std::string message, GameState& gs) {

    char tp[4];
    char rm[BUFSIZE];
    int r = sscanf(message.c_str(), MAIN_HEADER DELIMITER "%3s" DELIMITER REMAIN, tp, rm);

    if (r == 2) {

        std::string type(tp);
        std::string remaining(rm);
        int actual_state = StateManager::getState();

        if (type == REQUEST_TYPE && ( actual_state == FINDPEERS_STATE || actual_state == WAIT_STATE)) {
            evalRequest(remaining, gs);
            StateManager::setState(FINDPEERS_STATE);
        }
        else if (type == PLAYER_STATE_TYPE && actual_state == GAME_STATE) evalPlayerState(remaining, gs);
        else if (type == COLLISION_TYPE && actual_state == GAME_STATE) {
            evalCollision(remaining, gs);
            StateManager::setState(COLLISION_STATE);
        }

        else if (type == FINISH_TYPE && (actual_state == GAME_STATE || actual_state == COLLISION_STATE)) {
            evalFinish(remaining, gs);
            StateManager::setState(FINISH_STATE);
        }
        else {
            std::cout << "Wrong message type";
            //exit(1);
        }
    }
}

void MessageProtocol::evalRequest(std::string message, GameState& gs) {

    std::cout << "MessageProtocol::evalRequest()\n";
    std::cout << message << std::endl;

    int player_no;
    unsigned int frame;
    unsigned int countdown;
    char rm[BUFSIZE];
    memset(rm, 0, BUFSIZE);

    int r = sscanf(message.c_str(), PLAYERNO INT DELIMITER FRAME UINT DELIMITER COUNTDOWN UINT REMAIN, &player_no, &frame, &countdown, rm);

    if (r >= 1) {
//        std::cout << "r " << r << std::endl;
//        std::cout << "pn " << player_no << std::endl;
//        std::cout << "fr " << frame << std::endl;
//        std::cout << "cd " << countdown << std::endl;
//        std::cout << "rm " << rm << std::endl;

        gs.setPlayerActive(true, player_no);
        AddressManager::addParticipant(player_no);
        std::cout << "MessageProtocol::evalRequest() numOfParticipants: " << AddressManager::getNumOfParticipants() << std::endl;

        if (frame >= gs.getPlayer(player_no).getFrame()) {

            gs.setFrame(player_no, frame);

            if (gs.getCountdown() < (countdown - 5) && countdown > 5) {
                std::cout << gs.getCountdown() << " < " << countdown << " - 5\n";
                gs.setCountdown(countdown);
            }
        }
    }

}


void MessageProtocol::evalPlayerState(std::string message, GameState &gs) {

    std::cout << "MessageProtocol::evalPlayerState()\n";
    std::cout << message << std::endl;

    unsigned int frame;
    int player_no;
    int position;
    int points;
    char rm[BUFSIZE];
    memset(rm, 0, BUFSIZE);

    int r = sscanf(message.c_str(), FRAME UINT DELIMITER PLAYERNO INT DELIMITER POSITION INT DELIMITER POINTS INT REMAIN, &frame, &player_no, &position, &points, rm);

    if (r >= 3) {
        std::cout << "r " << r << std::endl;
        std::cout << "fr " << frame << std::endl;
        std::cout << "pn " << player_no << std::endl;
        std::cout << "po " << position << std::endl;
        std::cout << "po " << points << std::endl;
        std::cout << "rm " << rm << std::endl;

        if (gs.getPlayer(player_no).getFrame() <= frame) {
            gs.setFrame(player_no, frame);
            gs.setPosition(player_no, position);
            gs.setPoints(player_no, points);
        }
    }

}

void MessageProtocol::evalCollision(std::string message, GameState &gs) {
    // TODO round vergleichen, frame vergleichen

    std::cout << "MessageProtocol::evalCollision()\n";
    std::cout << message << std::endl;

    unsigned int frame;
    int player_no;
    char rm[BUFSIZE];
    memset(rm, 0, BUFSIZE);

    int r = sscanf(message.c_str(), FRAME UINT DELIMITER PLAYERNO INT REMAIN, &frame, &player_no, rm);

    if (r >= 2) {
        std::cout << "r " << r << std::endl;
        std::cout << "fr " << frame << std::endl;
        std::cout << "pn " << player_no << std::endl;
        std::cout << "rm " << rm << std::endl;
    }

}

void MessageProtocol::evalFinish(std::string message, GameState &gs) {

    std::cout << "MessageProtocol::evalFinish()\n";
    std::cout << message << std::endl;

    unsigned int frame;
    int player_no;
    int points;
    char rm[BUFSIZE];
    memset(rm, 0, BUFSIZE);

    int r = sscanf(message.c_str(), FRAME UINT DELIMITER PLAYERNO INT DELIMITER POINTS INT REMAIN, &frame, &player_no, &points, rm);

    if (r >= 3) {
        std::cout << "r " << r << std::endl;
        std::cout << "fr " << frame << std::endl;
        std::cout << "pn " << player_no << std::endl;
        std::cout << "po " << points << std::endl;
        std::cout << "rm " << rm << std::endl;
    }


}
