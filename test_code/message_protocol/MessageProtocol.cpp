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
	enum Type message_type;

};

struct gamestate {
	enum Type message_type;

};

