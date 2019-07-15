/*
 * Player.h
 *
 *  Created on: 29.06.2019
 *      Author: koenigr
 */

#ifndef TEST_CODE_GAMESTATE_PLAYER_H_
#define TEST_CODE_GAMESTATE_PLAYER_H_

class Player {
public:
	Player();
 	void toString(char player_str[]);
	virtual ~Player();
	int decrPoints();
};

#endif /* TEST_CODE_GAMESTATE_PLAYER_H_ */
