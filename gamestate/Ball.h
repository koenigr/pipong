/*
 * Ball.h
 *
 *  Created on: 29.06.2019
 *      Author: koenigr
 */

#ifndef TEST_CODE_GAMESTATE_BALL_H_
#define TEST_CODE_GAMESTATE_BALL_H_

#include <string>

class Ball {
private:

    float pos_x = DISPLAY_SIZE / 2;
    float pos_y = DISPLAY_SIZE / 2;
    float angle = 33.333; //36.4  TODO init random angle
    float velocity = INIT_VELOCITY;

public:
    int getPosX() const;
    int getPosY() const;
    float getAngle() const;
    float getVelocity() const;
    void resetBall(const int seed);
    int setPosX(int posX);
    int setPosY(int posY);
    float incrVelocity();
    float setAngle(int player_self, float new_angle);
    void updateBall();
    void reflectBall(int side);
    std::string toString() const;
};

#endif /* TEST_CODE_GAMESTATE_BALL_H_ */
