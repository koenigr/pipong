/*
 * MessageProtocol.cpp
 *
 *  Created on: 29.06.2019
 *      Author: koenigr
 */

#include "MessageProtocol.h"

#include "GamestateMsg.h"
#include "../Parameters.h"
#include "Request.h"
#include "Response.h"

enum Type {REQUEST, RESPONSE, GAMESTATE}; //TODO ??

Request rqst;
Response rsp;
GamestateMsg gmst;


void MessageProtocol::createRequest(char out_str[], char ip_addr[]) {
  Request(out_str, ip_addr);
}

void MessageProtocol::createResponse(char out_str[], char ip_addr[]) {
  Response(out_str, ip_addr);
}

void MessageProtocol::createGamestate() {

}

//TODO first check message type, then return fitting object


