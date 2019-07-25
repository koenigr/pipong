/*
 * MessageProtocol.h
 *
 *  Created on: 29.06.2019
 *      Author: koenigr
 */

#ifndef TEST_CODE_MESSAGE_PROTOCOL_MESSAGEPROTOCOL_H_
#define TEST_CODE_MESSAGE_PROTOCOL_MESSAGEPROTOCOL_H_

#include "../gamestate/GameState.h"

class MessageProtocol {

public:

    static std::string createRequest(GameState gs);

    static std::string createResponse(GameState gs);

    static std::string createPlayerState(GameState gs);

    static std::string createCollision(GameState gs);

    static std::string createFinish(GameState gs);

    static void evalMessage(int actual_state, std::string message);

    static void evalRequest(std::string message);

    static void evalResponse(std::string message);

    static void evalPlayerState(std::string message);

    static void evalCollision(std::string message);

    static void evalFinish(std::string message);

};

#endif /* TEST_CODE_MESSAGE_PROTOCOL_MESSAGEPROTOCOL_H_ */
