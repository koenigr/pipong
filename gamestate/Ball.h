/*
 * Ball.h
 *
 *  Created on: 29.06.2019
 *      Author: koenigr
 */

#ifndef TEST_CODE_GAMESTATE_BALL_H_
#define TEST_CODE_GAMESTATE_BALL_H_

#include "../Parameters.h"

#include <string>

class Ball {
private:

    float pos_x = DISPLAY_SIZE / 2;
    float pos_y = DISPLAY_SIZE / 2;
    float angle;
    float velocity = INIT_VELOCITY;
    unsigned int ball_frame = 0;

public:
    Ball();
    ~Ball();
    int getPosX() const;
    int getPosY() const;
    float getAngle() const;
    float getVelocity() const;
    void resetVelocity();
    void resetBall(const int player_self, const int seed);
    int setPosX(int posX);
    int setPosY(int posY);
    float incrVelocity();
    float setAngle(int player_self, float new_angle);
    void updateBall();
    void reflectBall(int side);
    std::string toString() const;
};

#endif /* TEST_CODE_GAMESTATE_BALL_H_ */
