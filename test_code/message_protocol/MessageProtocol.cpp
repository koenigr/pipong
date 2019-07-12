/*
 * MessageProtocol.cpp
 *
 *  Created on: 29.06.2019
 *      Author: koenigr
 */

#include "MessageProtocol.h"
#include "Parameters.h"
#include "Request.h"
#include "Response.h"
#include "Gamestate.h"

enum Type {REQUEST, RESPONSE, GAMESTATE};

Request rqst;
Response rsp;
Gamestate gmst;


void MessageProtocol::createRequest(char out_str[], char ip_addr[], int port) {
  Request(out_str, ip_addr, port);
}

void MessageProtocol::createResponse() {

}

void MessageProtocol::createGamestate() {

}

//TODO first check message type, then return fitting object


