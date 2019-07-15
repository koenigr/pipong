/*
 * Ball.h
 *
 *  Created on: 29.06.2019
 *      Author: koenigr
 */

#ifndef TEST_CODE_GAMESTATE_BALL_H_
#define TEST_CODE_GAMESTATE_BALL_H_

class Ball {
public:
	Ball();
    std::string toString();
    float increaseVel();
	virtual ~Ball();
};

#endif /* TEST_CODE_GAMESTATE_BALL_H_ */
