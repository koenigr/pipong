/*
 * MessageProtocol.cpp
 *
 *  Created on: 29.06.2019
 *      Author: koenigr
 */

#include "MessageProtocol.h"

#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <cstring>

#define MAIN_HEADER "PIPONG"
#define DELIMITER ":"
#define REQUEST_TYPE "REQ"
#define RESPONSE_TYPE "RSP"
#define PLAYER_STATE_TYPE "PST"
#define COLLISION_TYPE "COL"
#define FINISH_TYPE "FIN"

#define INT " %d"
#define REMAIN "%[\001-\377]"
#define FRAME "FRAME "
#define PLAYERNO "PLAYERNO "
#define POSITION "POSITION "
#define POINTS "POINTS "
#define SEQNO "SEQNO "
#define COUNTDOWN_IDENT "COUNTDOWN "


std::string MessageProtocol::createRequest(GameState gs) {

    //std::cout << "\nMessageProtocol::createRequest() start...\n";

    std::stringstream x;
    x   << MAIN_HEADER
        << DELIMITER << REQUEST_TYPE
        << DELIMITER << FRAME << gs.getFrameNo()
        << DELIMITER << PLAYERNO << gs.getPlayerNo();

    std::string request = x.str();

    std::cout << "MessageProtocol::createRequest() Request: " << request << std::endl;
    //std::cout << "MessageProtocol::createRequest() end\n";

    return request;
}

std::string MessageProtocol::createResponse(GameState gs) {

    //std::cout << "\nStarting to create response...\n";

    std::stringstream x;
    x   << MAIN_HEADER
        << DELIMITER << FRAME << gs.getFrameNo()
        << DELIMITER << PLAYERNO << gs.getPlayerNo()
        << DELIMITER << COUNTDOWN_IDENT  << gs.getCountdown();

    std::string response = x.str();

    //std::cout << "Response creation completed\n";

    return response;
}

std::string MessageProtocol::createPlayerState(GameState gs) {

    //std::cout << "\nStarting to create playerState message...\n";

    std::stringstream x;
    x   << MAIN_HEADER
        << DELIMITER << PLAYER_STATE_TYPE
        << DELIMITER << FRAME << gs.getFrameNo()
        << DELIMITER << PLAYERNO << gs.getPlayerNo()
        << DELIMITER << POSITION << gs.getSelf().getPlayerPos()
        << DELIMITER << POINTS << gs.getSelf().getPlayerPoints();

    std::string player_state = x.str();

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

    //std::cout << "Collision creation completed\n";

    return collision;
}

std::string MessageProtocol::createFinish(GameState gs) {

    //std::cout << "\nStarting to create finish message...\n";

    std::stringstream x;
    x   << MAIN_HEADER
        << DELIMITER << FINISH_TYPE
        << DELIMITER << SEQNO << gs.getFrameNo()
        << DELIMITER << PLAYERNO << gs.getPlayerNo()
        << DELIMITER << POINTS << gs.getSelf().getPlayerPoints();

    std::string finish = x.str();

    //std::cout << "Finish creation completed\n";

    return finish;
}


void MessageProtocol::evalMessage(int actual_state, std::string message) {

    char tp[4];
    char rm[BUFSIZE];
    int r = sscanf(message.c_str(), MAIN_HEADER DELIMITER "%3s" DELIMITER REMAIN, tp, rm);

    if (r == 2) {

        std::string type(tp);
        std::string remaining(rm);

        if (type == REQUEST_TYPE && actual_state == 0) evalRequest(remaining);
        else if (type == RESPONSE_TYPE && actual_state == 0) evalResponse(remaining);
        else if (type == PLAYER_STATE_TYPE && actual_state == 1) evalPlayerState(remaining);
        else if (type == COLLISION_TYPE && actual_state == 1) evalCollision(remaining);
        else if (type == FINISH_TYPE && (actual_state == 1 || actual_state == 2)) evalFinish(remaining);
        else {
            std::cout << "Wrong message type";
            exit(1);
        }
    }
}

void MessageProtocol::evalRequest(std::string message) {

    std::cout << "MessageProtocol::evalRequest()\n";
    std::cout << message << std::endl;

    int frame;
    int player_no;
    char rm[BUFSIZE];
    memset(rm, 0, BUFSIZE);

    int r = sscanf(message.c_str(), FRAME INT DELIMITER PLAYERNO INT REMAIN, &frame, &player_no, rm);

    if (r >= 2) {
        std::cout << "r " << r << std::endl;
        std::cout << "fr " << frame << std::endl;
        std::cout << "pn " << player_no << std::endl;
        std::cout << "rm " << rm << std::endl;
        // TODO evaluate information
    }

}

void MessageProtocol::evalResponse(std::string message) {

    std::cout << "MessageProtocol::evalResponse()\n";
    std::cout << message << std::endl;

    int frame;
    int player_no;
    unsigned int countdown;
    char rm[BUFSIZE];
    memset(rm, 0, BUFSIZE);

    int r = sscanf(message.c_str(), FRAME INT DELIMITER PLAYERNO INT DELIMITER COUNTDOWN_IDENT "%u" REMAIN, &frame, &player_no, &countdown, rm);

    if (r >= 3) {
        std::cout << "r " << r << std::endl;
        std::cout << "fr " << frame << std::endl;
        std::cout << "pn " << player_no << std::endl;
        std::cout << "cd " << countdown << std::endl;
        std::cout << "rm " << rm << std::endl;
        // TODO evaluate information
    }

}

void MessageProtocol::evalPlayerState(std::string message) {

    std::cout << "MessageProtocol::evalPlayerState()\n";

    int frame;
    int player_no;
    int position;
    char rm[BUFSIZE];
    memset(rm, 0, BUFSIZE);

    int r = sscanf(message.c_str(), FRAME INT DELIMITER PLAYERNO INT DELIMITER POSITION INT REMAIN, &frame, &player_no, &position, rm);

    if (r >= 3) {
        std::cout << "r " << r << std::endl;
        std::cout << "fr " << frame << std::endl;
        std::cout << "pn " << player_no << std::endl;
        std::cout << "rm " << rm << std::endl;
    }

}

void MessageProtocol::evalCollision(std::string message) {
    std::string submsg = message;
    submsg = submsg.substr(6);
    std::string frame = submsg.substr(0, submsg.find(DELIMITER));
    submsg = submsg.substr(11);
    std::string playerNo = submsg;

    std::cout << "Frame " << frame << "\n";
    std::cout << "PlayerNo " << playerNo << "\n";
}

void MessageProtocol::evalFinish(std::string message) {
    std::string submsg = message;
    submsg = submsg.substr(6);
    std::string frame = submsg.substr(0, submsg.find(DELIMITER));
    submsg = submsg.substr(11);
    std::string playerNo = submsg.substr(0, submsg.find(DELIMITER));
    submsg = submsg.substr(9);
    std::string points = submsg;

    std::cout << "Frame " << frame << "\n";
    std::cout << "PlayerNo " << playerNo << "\n";
    std::cout << "Points " << points << "\n";
}
