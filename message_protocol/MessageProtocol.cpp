/*
 * MessageProtocol.cpp
 *
 *  Created on: 29.06.2019
 *      Author: koenigr
 */

#include "MessageProtocol.h"
#include "../states/StateManager.h"
#include "../Parameters.h"
#include "../gamestate/Ball.h"

#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <cstring>

#define MAIN_HEADER "PIPONG"
#define DELIMITER ":"
#define REQUEST_TYPE "REQ"
#define PLAYER_STATE_TYPE "PST"
#define REFLECT_TYPE "RFL"
#define COLLISION_TYPE "COL"
#define FINISH_TYPE "FIN"

#define INT " %d"
#define UINT " %u"
#define FLOAT " %f"
#define REMAIN "%[\001-\377]"
#define FRAME "FRAME "
#define PLAYERNO "PLAYERNO "
#define POSITION "POSITION "
#define POINTS "POINTS "
#define COUNTDOWN "COUNTDOWN "
#define ROUND "ROUND "
#define COLLFRAME "COLLFRAME "
#define BALLPOSX "BALLPOSX "
#define BALLPOSY "BALLPOSY "
#define BALLANG "BALLANG "

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

    return player_state;
}

std::string MessageProtocol::createReflect(GameState gs) {

    std::stringstream x;
    x   << MAIN_HEADER
        << DELIMITER << PLAYER_STATE_TYPE
        << DELIMITER << FRAME << gs.getBall().getBallFrame()
        << DELIMITER << PLAYERNO << gs.getPlayerNo()
        << DELIMITER << BALLPOSX << gs.getBall().getPosX()
        << DELIMITER << BALLPOSY << gs.getBall().getPosY()
        << DELIMITER << BALLANG <<  gs.getBall().getAngle();

    std::string reflect = x.str();

    return reflect;
}

std::string MessageProtocol::createCollision(GameState gs) {

    std::stringstream x;
    x   << MAIN_HEADER
        << DELIMITER  << COLLISION_TYPE
        << DELIMITER << FRAME << gs.getFrameNo()
        << DELIMITER << ROUND << gs.getRound()
        << DELIMITER << COLLFRAME << StateManager::last_collision_frame
        << DELIMITER << PLAYERNO << gs.getPlayerNo();

    std::string collision = x.str();

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
        else if (type == REFLECT_TYPE && actual_state == GAME_STATE) evalReflect(message, gs);
        else if (type == COLLISION_TYPE && actual_state == GAME_STATE) {
            evalCollision(remaining, gs);
        }

        else if (type == FINISH_TYPE && (actual_state == GAME_STATE || actual_state == COLLISION_STATE)) {
            evalFinish(remaining, gs);
            StateManager::setState(FINISH_STATE);
        }
        else {
            std::cout << "Wrong message type";
        }
    }
}

void MessageProtocol::evalRequest(std::string message, GameState& gs) {

    int player_no;
    unsigned int frame;
    unsigned int countdown;
    char rm[BUFSIZE];
    memset(rm, 0, BUFSIZE);

    int r = sscanf(message.c_str(), PLAYERNO INT DELIMITER FRAME UINT DELIMITER COUNTDOWN UINT REMAIN, &player_no, &frame, &countdown, rm);

    if (r >= 1) {
        if (!gs.getPlayer(player_no).isActive()) {
            AddressManager::addParticipant(player_no);
            gs.setPlayerActive(true, player_no);
        }

        if (frame >= gs.getPlayer(player_no).getFrame()) {

            gs.setFrame(player_no, frame);

            if (gs.getCountdown() < (countdown - 5) && countdown > 5) {
                gs.setCountdown(countdown);
            }
        }
    }
}


void MessageProtocol::evalPlayerState(std::string message, GameState &gs) {

    unsigned int frame;
    int player_no;
    int position;
    int points;
    char rm[BUFSIZE];
    memset(rm, 0, BUFSIZE);

    int r = sscanf(message.c_str(), FRAME UINT DELIMITER PLAYERNO INT DELIMITER POSITION INT DELIMITER POINTS INT REMAIN, &frame, &player_no, &position, &points, rm);

    if (r >= 3) {

        if (gs.getPlayer(player_no).getFrame() <= frame) {
            gs.setFrame(player_no, frame);
            gs.setPosition(player_no, position);
            gs.setPoints(player_no, points);
        }
    }

}

void MessageProtocol::evalReflect(std::string message, GameState &gs) {

    std::cout << "reflect message: " << message << std::endl;

    unsigned int ball_frame;
    int player_no;
    int posx;
    int posy;
    int ballang;
    char rm[BUFSIZE];
    memset(rm, 0, BUFSIZE);

    int r = sscanf(message.c_str(), FRAME UINT DELIMITER PLAYERNO INT DELIMITER BALLPOSX INT DELIMITER BALLPOSY INT DELIMITER BALLANG FLOAT REMAIN, &player_no, &ball_frame, &posx, &posy, &ballang, rm);

    if (r >= 6) {

        if (gs.getBall().getBallFrame() < ball_frame + 2) {
            gs.setBallPos(posx, posy, player_no);
            gs.setBallAngle(ballang, player_no);
        }
    }

}

void MessageProtocol::evalCollision(std::string message, GameState &gs) {
    // TODO round vergleichen, frame vergleichen

    unsigned int frame;
    int round;
    int collframe;
    int player_no;
    char rm[BUFSIZE];
    memset(rm, 0, BUFSIZE);

    int r = sscanf(message.c_str(), FRAME UINT DELIMITER ROUND INT DELIMITER COLLFRAME INT DELIMITER PLAYERNO INT REMAIN, &frame, &round, &collframe, &player_no, rm);

    if (r >= 3) {

        if (round == gs.getRound()) {
            StateManager::last_collision_frame = collframe;
            StateManager::setState(COLLISION_STATE);
        }
    }

}

void MessageProtocol::evalFinish(std::string message, GameState &gs) {

    unsigned int frame;
    int player_no;
    int points;
    char rm[BUFSIZE];
    memset(rm, 0, BUFSIZE);

    int r = sscanf(message.c_str(), FRAME UINT DELIMITER PLAYERNO INT DELIMITER POINTS INT REMAIN, &frame, &player_no, &points, rm);

    if (r >= 3) {

        gs.setPoints(player_no, points);
    }


}
