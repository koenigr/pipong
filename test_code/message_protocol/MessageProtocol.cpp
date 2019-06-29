/*
 * MessageProtocol.cpp
 *
 *  Created on: 29.06.2019
 *      Author: koenigr
 */

#include "MessageProtocol.h"
#include "Parameters.h"

enum Type {REQUEST, RESPONSE, GAMESTATE};

struct connect_request {
	Type message_type = Type::REQUEST;
};

struct connect_response {
	Type message_type = Type::RESPONSE;

};

struct gamestate {
	Type message_type = Type::GAMESTATE;

};

void getConnectRequestJSON() {

}

void getConnectResponseJSON() {

}

void getGamestateJSON() {

}

