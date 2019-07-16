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

    void createRequest(char out_str[], int player_self);

    void createResponse(char out_str[], int player_self);

    void createPlayerState(GameState gs, char out_str[], int player_self);

    void createCollision(char out_str[], int player_state);

    void createFinish(GameState gs, char out_str[], int player_state);

    void evalMessage(char in_str[]);

    void evalRequest(char in_str[]);

    void evalResponse(char in_str[]);

    void evalPlayerState(char in_str[]);

    void evalCollision(char in_str[]);

    void evalFinish(char in_str[]);

};

#endif /* TEST_CODE_MESSAGE_PROTOCOL_MESSAGEPROTOCOL_H_ */
