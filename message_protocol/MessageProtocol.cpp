/*
 * MessageProtocol.cpp
 *
 *  Created on: 29.06.2019
 *      Author: koenigr
 */

#include "MessageProtocol.h"

#include <iostream>
#include <string>

std::string header = "PIPONG";
std::string delimiter = ":";
std::string request_type = "REQ";
std::string response_type = "RSP";
std::string player_state_type = "PST";
std::string collision_type = "COL";
std::string finish_type = "FIN";

std::string MessageProtocol::createRequest(GameState gs) {
    std::string request = header;
    request += delimiter + request_type;
    request += delimiter + "SEQNO " + std::to_string(gs.getSequenceNo());
    request += delimiter + "PLAYERNO " + std::to_string(gs.getPlayerNo());
    return request;
}

std::string MessageProtocol::createResponse(GameState gs) {
    std::string response = header;
    response += delimiter + response_type;
    response += delimiter + "SEQNO " + std::to_string(gs.getSequenceNo());
    response += delimiter + "PLAYERNO " + std::to_string(gs.getPlayerNo());
    return response;
}

std::string MessageProtocol::createPlayerState(GameState gs) {
    std::string player_state = header;
    player_state += delimiter + player_state_type;
    player_state += delimiter + "SEQNO " + std::to_string(gs.getSequenceNo());
    player_state += delimiter + "PLAYERNO " + std::to_string(gs.getPlayerNo());
    player_state += delimiter + "POSITION: " + std::to_string(gs.getSelf().getPlayerPos());
    return player_state;
}

std::string MessageProtocol::createCollision(GameState gs) {
    std::string collision = header;
    collision += delimiter + collision_type;
    collision += delimiter + "SEQNO " + std::to_string(gs.getSequenceNo());
    collision += delimiter + "PLAYERNO " + std::to_string(gs.getPlayerNo());
    // TODO random angle
    return collision;
}

std::string MessageProtocol::createFinish(GameState gs) {
    std::string finish = header;
    finish += delimiter + finish_type;
    finish += delimiter + "SEQNO " + std::to_string(gs.getSequenceNo());
    finish += delimiter + "PLAYERNO " + std::to_string(gs.getPlayerNo());
    finish += delimiter + "POINTS " + std::to_string(gs.getSelf().getPlayerPoints());
    return finish;
}


void MessageProtocol::evalMessage(std::string message) {
    std::string type = message.substr(0, 3);
    std::string msg = message.substr(4);
    std::cout << "MessageType: " << message.substr(0, 3) << "\n";
    if (type == request_type) evalRequest(msg);
    else if (type == response_type) evalResponse(msg);
    else if (type == player_state_type) evalPlayerState(msg);
    else if (type == collision_type) evalCollision(msg);
    else if (type == finish_type) evalFinish(msg);
    else {
        std::cout << "Wrong message type";
        exit(1);
    }

    std::cout << "\n\n";
}

void MessageProtocol::evalRequest(std::string message) {
    std::string submsg = message;
    submsg = submsg.substr(6);
    std::string sequence = submsg.substr(0, submsg.find(delimiter));
    submsg = submsg.substr(11);
    std::string playerNo = submsg;

    std::cout << "Sequence " << sequence << "\n";
    std::cout << "PlayerNo " << playerNo;
}

void MessageProtocol::evalResponse(std::string message) {
    std::string submsg = message;
    submsg = submsg.substr(6);
    std::string sequence = submsg.substr(0, submsg.find(delimiter));
    submsg = submsg.substr(11);
    std::string playerNo = submsg;

    std::cout << "Sequence " << sequence << "\n";
    std::cout << "PlayerNo " << playerNo;
}

void MessageProtocol::evalPlayerState(std::string message) {
    std::string submsg = message;
    submsg = submsg.substr(6);
    std::string sequence = submsg.substr(0, submsg.find(delimiter));
    submsg = submsg.substr(11);
    std::string playerNo = submsg.substr(0, submsg.find(delimiter));
    submsg = submsg.substr(12);
    std::string position = submsg;

    std::cout << "Sequence " << sequence << "\n";
    std::cout << "PlayerNo " << playerNo << "\n";
    std::cout << "Position " << position << "\n";
}

void MessageProtocol::evalCollision(std::string message) {
    std::string submsg = message;
    submsg = submsg.substr(6);
    std::string sequence = submsg.substr(0, submsg.find(delimiter));
    submsg = submsg.substr(11);
    std::string playerNo = submsg;

    std::cout << "Sequence " << sequence << "\n";
    std::cout << "PlayerNo " << playerNo << "\n";
}

void MessageProtocol::evalFinish(std::string message) {
    std::string submsg = message;
    submsg = submsg.substr(6);
    std::string sequence = submsg.substr(0, submsg.find(delimiter));
    submsg = submsg.substr(11);
    std::string playerNo = submsg.substr(0, submsg.find(delimiter));
    submsg = submsg.substr(9);
    std::string points = submsg;

    std::cout << "Sequence " << sequence << "\n";
    std::cout << "PlayerNo " << playerNo << "\n";
    std::cout << "Points " << points << "\n";
}
