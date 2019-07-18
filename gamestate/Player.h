/*
 * Player.h
 *
 *  Created on: 29.06.2019
 *      Author: koenigr
 */

#ifndef TEST_CODE_GAMESTATE_PLAYER_H_
#define TEST_CODE_GAMESTATE_PLAYER_H_

#include <string>

class Player {
public:
    Player();
	virtual ~Player();
	int decrPoints();
    int getPlayerPos();
    int getPlayerPoints();
    int getSequenceNo();
    std::string toString();
};

#endif /* TEST_CODE_GAMESTATE_PLAYER_H_ */
