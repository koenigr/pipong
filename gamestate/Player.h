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
    std::string toString();
	virtual ~Player();
	int decrPoints();
};

#endif /* TEST_CODE_GAMESTATE_PLAYER_H_ */
