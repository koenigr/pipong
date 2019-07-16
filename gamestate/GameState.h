/*
 * GameState.h
 *
 *  Created on: 29.06.2019
 *      Author: koenigr
 */

#ifndef TEST_CODE_GAMESTATE_GAMESTATE_H_
#define TEST_CODE_GAMESTATE_GAMESTATE_H_

#include "Player.h"
#include <string>

class GameState {
public:
    GameState();
    void init(int player_self);
    int decrPoint();
    Player getPlayer(int i);
};

#endif /* TEST_CODE_GAMESTATE_GAMESTATE_H_ */
