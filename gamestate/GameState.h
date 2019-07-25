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
private:
    Ball ball;
    Player player_arr[4];
    int player_self;
    unsigned int frame_no = 0;
    int round = 1;

    void checkForPaddleCollision();
    void checkForScoringZoneCollision();

public:
    ~GameState();
    void init(int player_self);
    int decrPoint();
    Player getSelf() const;
    Player getPlayer(int i) const;
    Ball getBall() const;
    unsigned int getFrameNo() const;
    unsigned int incrFrameNo();
    int getPlayerNo() const;
    int getRound() const;
    int incrRound();
    std::string toString() const;
    void updateBall();
    void newRound(const int seed);
    void setPlayerActive(const bool isActive, const int player_no);
};

#endif /* TEST_CODE_GAMESTATE_GAMESTATE_H_ */
