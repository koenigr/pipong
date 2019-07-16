/*
 * MessageProtocol.cpp
 *
 *  Created on: 29.06.2019
 *      Author: koenigr
 */

#include "MessageProtocol.h"

#include "../Parameters.h"
#include "Request.h"
#include "Response.h"

Request req;
Response res;

void MessageProtocol::createRequest(char out_str[], int player_self) {
  req.createRequest(out_str, player_self);
}

void MessageProtocol::createResponse(char out_str[], int player_self) {
  res.createResponse(out_str, player_self);
}

void MessageProtocol::createGamestate() {

}

//TODO first check message type, then return fitting object


