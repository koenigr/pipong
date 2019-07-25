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

#define MAIN_HEADER "PIPONG"
#define DELIMITER ":"
#define REQUEST_TYPE "REQ"
#define RESPONSE_TYPE "RSP"
#define PLAYER_STATE_TYPE "PST"
#define COLLISION_TYPE "COL"
#define FINISH_TYPE "FIN"


std::string MessageProtocol::createRequest(GameState gs) {

    //std::cout << "\nMessageProtocol::createRequest() start...\n";

    std::stringstream x;
    x   << MAIN_HEADER
        << DELIMITER << REQUEST_TYPE
        << DELIMITER << "FRAME " << gs.getFrameNo()
        << DELIMITER << "PLAYERNO " << gs.getPlayerNo();

    std::string request = x.str();

    std::cout << "MessageProtocol::createRequest() Request: " << request << std::endl;
    //std::cout << "MessageProtocol::createRequest() end\n";

    return request;
}

std::string MessageProtocol::createResponse(GameState gs) {

    //std::cout << "\nStarting to create response...\n";

    std::stringstream x;
    x   << MAIN_HEADER
        << DELIMITER << RESPONSE_TYPE
        << DELIMITER << "FRAME " << gs.getFrameNo()
        << DELIMITER << "PLAYERNO " << gs.getPlayerNo();

    std::string response = x.str();

    //std::cout << "Response creation completed\n";

    return response;
}

std::string MessageProtocol::createPlayerState(GameState gs) {

    //std::cout << "\nStarting to create playerState message...\n";

    std::stringstream x;
    x   << MAIN_HEADER
        << DELIMITER << PLAYER_STATE_TYPE
        << DELIMITER << "FRAME " << gs.getFrameNo()
        << DELIMITER << "PLAYERNO " << gs.getPlayerNo()
        << DELIMITER << "POSITION " << gs.getSelf().getPlayerPos()
        << DELIMITER << "POINTS " << gs.getSelf().getPlayerPoints();

    std::string player_state = x.str();

    //std::cout << "Player_state creation completed\n";

    return player_state;
}

std::string MessageProtocol::createCollision(GameState gs) {

    //std::cout << "\nStarting to create collision message...\n";

    std::stringstream x;
    x   << MAIN_HEADER
        << DELIMITER  << COLLISION_TYPE
        << DELIMITER << "FRAME " << gs.getFrameNo()
        << DELIMITER << "PLAYERNO " << gs.getPlayerNo();
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
        << DELIMITER << "SEQNO " << gs.getFrameNo()
        << DELIMITER << "PLAYERNO " << gs.getPlayerNo()
        << DELIMITER << "POINTS " << gs.getSelf().getPlayerPoints();

    std::string finish = x.str();

    //std::cout << "Finish creation completed\n";

    return finish;
}


void MessageProtocol::evalMessage(int actual_state, std::string message) {

    char tp[4];
    char rm[BUFSIZE];
    int r = sscanf(message.c_str(), MAIN_HEADER DELIMITER "%3s" DELIMITER "%[\001-\377]", tp, rm);

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

    std::cout << "evalReq\n";
    std::string submsg = message;

    if (submsg.size() < 6 || submsg.substr(0,6) != "FRAME ") {
        std::cout << "request message corrupted: " << submsg << "\n";
        exit(1);
    }
    submsg = submsg.substr(6);
    std::string frame = submsg.substr(0, submsg.find(DELIMITER));
    submsg = submsg.substr(submsg.find(DELIMITER) + 1);

    std::cout << submsg << " " << submsg.size() << "\n";

    if (submsg.size() < 10 || submsg.substr(0,9) != "PLAYERNO ") {
        std::cout << "request message corrupted: " << submsg.substr(0,9) << "\n";
        exit(1);
    }
    submsg = submsg.substr(9);
    std::string playerNo = submsg;

    //std::cout << "Frame " << frame << "\n";
    //std::cout << "PlayerNo " << playerNo;
}

void MessageProtocol::evalResponse(std::string message) {
    std::string submsg = message;
    submsg = submsg.substr(6);
    std::string frame = submsg.substr(0, submsg.find(DELIMITER));
    submsg = submsg.substr(11);
    std::string playerNo = submsg;

    std::cout << "Frame " << frame << "\n";
    std::cout << "PlayerNo " << playerNo;
}

void MessageProtocol::evalPlayerState(std::string message) {
    std::string submsg = message;
    submsg = submsg.substr(6);
    std::string frame = submsg.substr(0, submsg.find(DELIMITER));
    submsg = submsg.substr(11);
    std::string playerNo = submsg.substr(0, submsg.find(DELIMITER));
    submsg = submsg.substr(12);
    std::string position = submsg;

    std::cout << "Frame " << frame << "\n";
    std::cout << "PlayerNo " << playerNo << "\n";
    std::cout << "Position " << position << "\n";
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
