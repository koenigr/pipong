/*
 * GameState.h
 *
 *  Created on: 29.06.2019
 *      Author: koenigr
 */

#ifndef TEST_CODE_GAMESTATE_GAMESTATE_H_
#define TEST_CODE_GAMESTATE_GAMESTATE_H_

#include <string>

#include "Player.h"
#include "Ball.h"

class GameState {
public:
    ~GameState();
    void init(int player_self);
    int decrPoint();
    Player getSelf();
    Player getPlayer(int i);
    Ball getBall();
    unsigned int getFrameNo();
    unsigned int incrFrameNo();
    int getPlayerNo();
    int getRound();
    int incrRound();
};

#endif /* TEST_CODE_GAMESTATE_GAMESTATE_H_ */
