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
    std::string main_header = "PIPONG";
    std::string delimiter = ":";
    std::string request_type = "REQ";
    std::string response_type = "RSP";
    std::string player_state_type = "PST";
    std::string collision_type = "COL";
    std::string finish_type = "FIN";


public:

    std::string createRequest(GameState gs);

    std::string createResponse(GameState gs);

    std::string createPlayerState(GameState gs);

    std::string createCollision(GameState gs);

    std::string createFinish(GameState gs);

    void evalMessage(std::string message);

    void evalRequest(std::string message);

    void evalResponse(std::string message);

    void evalPlayerState(std::string message);

    void evalCollision(std::string message);

    void evalFinish(std::string message);

};

#endif /* TEST_CODE_MESSAGE_PROTOCOL_MESSAGEPROTOCOL_H_ */
