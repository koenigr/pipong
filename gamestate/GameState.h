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
#include "../network/UDPSocket.h"

class GameState {
private:
    Ball ball;
    Player player_arr[4];
    int player_self;
    int round = 1;
    unsigned int countdown = COUNTDOWN_START_VAL;
    int last_reflection_wall = -1;

    void checkForReflection(UDPSocket &pi_socket);
    void checkForScoringZoneCollision();

public:
    ~GameState();
    void init(int player_self);
    void setPlayerActive(const bool isActive, const int player_no);

    unsigned int getCountdown();
    void setCountdown(const unsigned int cd);
    void decrCountdown();

    int decrPoints();
    int setPoints(int player_no, int points);

    Player getSelf() const;
    Player getPlayer(int i) const;
    Ball getBall() const;

    void setBallPos(int posX, int posY, int player_out);
    void setBallAngle(float angle, int player_out);

    unsigned int getFrameNo() const;
    unsigned int incrFrameNo();
    unsigned int setFrame(int const player_no, unsigned int const new_frame);
    void resetAllFrames();

    int getPlayerNo() const;

    int setPosition(int player_no, int new_position);
    int getPosition(int player_no) const;

    int getRound() const;
    int incrRound();
    void newRound(const int seed);

    std::string toString() const;
    void updateBall(UDPSocket &pi_socket);
};

#endif /* TEST_CODE_GAMESTATE_GAMESTATE_H_ */
