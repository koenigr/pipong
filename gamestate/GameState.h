/*
 * GameState.h
 *
 *  Created on: 29.06.2019
 *      Author: koenigr
 */

#ifndef TEST_CODE_GAMESTATE_GAMESTATE_H_
#define TEST_CODE_GAMESTATE_GAMESTATE_H_

#include "Player.h"

class GameState {
public:
	int decrPoint(Player p);
        void toString(char gmst_str[]);
};

#endif /* TEST_CODE_GAMESTATE_GAMESTATE_H_ */
