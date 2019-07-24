/*
 * MessageProtocol.cpp
 *
 *  Created on: 29.06.2019
 *      Author: koenigr
 */

#include "MessageProtocol.h"

#include <iostream>
#include <string>

// TODO test for corrupt messages


std::string MessageProtocol::createRequest(GameState gs) {

    std::cout << "\nMessageProtocol::createRequest start...\n";

    std::string request = main_header;
    request += delimiter + request_type;
    request += delimiter + "FRAME " + std::to_string(gs.getFrameNo()); // TODO: fixed size for number
    request += delimiter + "PLAYERNO " + std::to_string(gs.getPlayerNo());

    std::cout << "Request: " << request << "\n";
    std::cout << "MessageProtocol::createRequest end\n";

    return request;
}

std::string MessageProtocol::createResponse(GameState gs) {

    std::cout << "\nStarting to create response...\n";

    std::string response = main_header;
    response += delimiter + response_type;
    response += delimiter + "FRAME " + std::to_string(gs.getFrameNo());
    response += delimiter + "PLAYERNO " + std::to_string(gs.getPlayerNo());
    return response;

    std::cout << "Response creation completed\n";
}

std::string MessageProtocol::createPlayerState(GameState gs) {

    std::cout << "\nStarting to create playerState message...\n";

    std::string player_state = main_header;
    player_state += delimiter + player_state_type;
    player_state += delimiter + "FRAME " + std::to_string(gs.getFrameNo());
    player_state += delimiter + "PLAYERNO " + std::to_string(gs.getPlayerNo());
    player_state += delimiter + "POSITION: " + std::to_string(gs.getSelf().getPlayerPos());
    return player_state;

    std::cout << "Player_state creation completed\n";
}

std::string MessageProtocol::createCollision(GameState gs) {

    std::cout << "\nStarting to create collision message...\n";

    std::string collision = main_header;
    collision += delimiter + collision_type;
    collision += delimiter + "FRAME " + std::to_string(gs.getFrameNo());
    collision += delimiter + "PLAYERNO " + std::to_string(gs.getPlayerNo());
    // TODO random angle
    return collision;

    std::cout << "Collision creation completed\n";
}

std::string MessageProtocol::createFinish(GameState gs) {

    std::cout << "\nStarting to create finish message...\n";

    std::string finish = main_header;
    finish += delimiter + finish_type;
    finish += delimiter + "SEQNO " + std::to_string(gs.getFrameNo());
    finish += delimiter + "PLAYERNO " + std::to_string(gs.getPlayerNo());
    finish += delimiter + "POINTS " + std::to_string(gs.getSelf().getPlayerPoints());
    return finish;

    std::cout << "Finish creation completed\n";
}


void MessageProtocol::evalMessage(std::string message) {

    if (message.size() > 10 && message.substr(0, 6) == main_header) {

        std::cout << "Entered if statement" << "\n";

        std::string type = message.substr(7, 3);
        std::string msg = message.substr(11);

        if (type == request_type) evalRequest(msg);
        else if (type == response_type) evalResponse(msg);
        else if (type == player_state_type) evalPlayerState(msg);
        else if (type == collision_type) evalCollision(msg);
        else if (type == finish_type) evalFinish(msg);
        else {
            std::cout << "Wrong message type";
            exit(1);
        }
    }
}

void MessageProtocol::evalRequest(std::string message) {
    std::string submsg = message;

    if (submsg.size() < 6 || submsg.substr(0,6) != "FRAME ") {
        std::cout << "request message corrupted: " << submsg << "\n";
        exit(1);
    }
    submsg = submsg.substr(6);
    std::string frame = submsg.substr(0, submsg.find(delimiter));
    submsg = submsg.substr(submsg.find(delimiter) + 1);

    std::cout << submsg << " " << submsg.size() << "\n";

    if (submsg.size() < 10 || submsg.substr(0,9) != "PLAYERNO ") {
        std::cout << "request message corrupted: " << submsg.substr(0,9) << "\n";
        exit(1);
    }
    submsg = submsg.substr(9);
    std::string playerNo = submsg;

    std::cout << "Frame " << frame << "\n";
    std::cout << "PlayerNo " << playerNo;
}

void MessageProtocol::evalResponse(std::string message) {
    std::string submsg = message;
    submsg = submsg.substr(6);
    std::string frame = submsg.substr(0, submsg.find(delimiter));
    submsg = submsg.substr(11);
    std::string playerNo = submsg;

    std::cout << "Frame " << frame << "\n";
    std::cout << "PlayerNo " << playerNo;
}

void MessageProtocol::evalPlayerState(std::string message) {
    std::string submsg = message;
    submsg = submsg.substr(6);
    std::string frame = submsg.substr(0, submsg.find(delimiter));
    submsg = submsg.substr(11);
    std::string playerNo = submsg.substr(0, submsg.find(delimiter));
    submsg = submsg.substr(12);
    std::string position = submsg;

    std::cout << "Frame " << frame << "\n";
    std::cout << "PlayerNo " << playerNo << "\n";
    std::cout << "Position " << position << "\n";
}

void MessageProtocol::evalCollision(std::string message) {
    std::string submsg = message;
    submsg = submsg.substr(6);
    std::string frame = submsg.substr(0, submsg.find(delimiter));
    submsg = submsg.substr(11);
    std::string playerNo = submsg;

    std::cout << "Frame " << frame << "\n";
    std::cout << "PlayerNo " << playerNo << "\n";
}

void MessageProtocol::evalFinish(std::string message) {
    std::string submsg = message;
    submsg = submsg.substr(6);
    std::string frame = submsg.substr(0, submsg.find(delimiter));
    submsg = submsg.substr(11);
    std::string playerNo = submsg.substr(0, submsg.find(delimiter));
    submsg = submsg.substr(9);
    std::string points = submsg;

    std::cout << "Frame " << frame << "\n";
    std::cout << "PlayerNo " << playerNo << "\n";
    std::cout << "Points " << points << "\n";
}
