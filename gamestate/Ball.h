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
    float pos_x;
    float pos_y;
    float angle;
    float velocity;

public:
    Ball();
    int getPosX() const;
    int getPosY() const;
    float getAngle() const;
    float getVelocity() const;
    void resetBall();
    int setPosX(int posX);
    int setPosY(int posY);
    float incrVelocity();
    float setAngle(float new_angle);
    void updateBall();
    void reflectBall();
    std::string toString() const;
	virtual ~Ball();
};

#endif /* TEST_CODE_GAMESTATE_BALL_H_ */
