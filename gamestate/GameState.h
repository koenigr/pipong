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
#include "../Parameters.h"

class GameState {
private:
    Ball ball;
    Player player_arr[4];
    int player_self;
    int round = 1;
    unsigned int countdown = COUNTDOWN;

    void checkForPaddleCollision();
    void checkForScoringZoneCollision();

public:
    ~GameState();
    void init(int player_self);
    void setPlayerActive(const bool isActive, const int player_no);

    unsigned int getCountdown();
    void setCountdown(const unsigned int cd);

    int decrPoint();
    int setPoints(int player_no, int points);

    Player getSelf() const;
    Player getPlayer(int i) const;
    Ball getBall() const;

    unsigned int getFrameNo() const;
    unsigned int incrFrameNo(const int actual_state);
    unsigned int setFrame(int const actual_state, int const player_no, unsigned int const new_frame);

    int getPlayerNo() const;

    int setPosition(int player_no, int new_position);
    int getPosition(int player_no) const;

    int getRound() const;
    int incrRound();
    void newRound(const int seed);

    std::string toString() const;
    void updateBall();
};

#endif /* TEST_CODE_GAMESTATE_GAMESTATE_H_ */
