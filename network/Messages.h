/*
 * Messages.h
 *
 *  Created on: 28.06.2019
 *      Author: koenigr
 */

#ifndef NETWORK_MESSAGES_H_
#define NETWORK_MESSAGES_H_

class Messages {

public:
	Messages();
	struct game_message;
	game_message getMessages();
};

#endif /* NETWORK_MESSAGES_H_ */
