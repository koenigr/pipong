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
private:

    static void evalRequest(std::string message, GameState &gs);

    static void evalPlayerState(std::string message, GameState &gs);

    static void evalCollision(std::string message, GameState &gs);

    static void evalFinish(std::string message, GameState &gs);


public:

    static std::string createRequest(GameState gs);

    static std::string createPlayerState(GameState gs);

    static std::string createCollision(GameState gs);

    static std::string createFinish(GameState gs);

    static void evalMessage(InputManager::States &actual_state, std::string message, GameState &gs);

};

#endif /* TEST_CODE_MESSAGE_PROTOCOL_MESSAGEPROTOCOL_H_ */
