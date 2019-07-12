#ifndef TEST_CODE_MESSAGE_PROTOCOL_GAMESTATEMSG_H_
#define TEST_CODE_MESSAGE_PROTOCOL_GAMESTATEMSG_H_

#include "../GameState/GameState.h"

class GamestateMsg {

public:

	GamestateMsg();

	GamestateMsg(char out_str[], GameState gamestate);
};

#endif /* TEST_CODE_MESSAGE_PROTOCOL_GAMESTATEMSG_H_ */


