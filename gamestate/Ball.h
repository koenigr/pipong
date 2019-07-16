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
public:
    Ball();
    void increaseVel();
    int getPosX();
    int getPosY();
    int getVelX();
    int getVelY();
    int setPosX(int posX);
    int setPosY(int posY);
	virtual ~Ball();
};

#endif /* TEST_CODE_GAMESTATE_BALL_H_ */
