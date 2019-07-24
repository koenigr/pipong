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

    std::string createRequest(GameState gs) const;

    std::string createResponse(GameState gs) const;

    std::string createPlayerState(GameState gs) const;

    std::string createCollision(GameState gs) const;

    std::string createFinish(GameState gs) const;

    void evalMessage(std::string message) const;

    void evalRequest(std::string message) const;

    void evalResponse(std::string message) const;

    void evalPlayerState(std::string message) const;

    void evalCollision(std::string message) const;

    void evalFinish(std::string message) const;

};

#endif /* TEST_CODE_MESSAGE_PROTOCOL_MESSAGEPROTOCOL_H_ */
