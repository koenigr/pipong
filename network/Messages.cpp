/*
 * Messages.cpp
 *
 *  Created on: 28.06.2019
 *      Author: koenigr
 */

#include "Messages.h"


struct game_message {
	char * CONN_REQ[];
};

game_message gm;

Messages::Messages() {
  gm.CONN_REQ = "Hi, I want to connect";
}

game_message Messages::getMessages() {
	return gm;
}

