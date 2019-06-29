/*
 * Ball.cpp
 *
 *  Created on: 29.06.2019
 *      Author: koenigr
 */

#include "Ball.h"

struct ball_pos {
	int x;
	int y;
};

struct direction {
	int x;
	int y;
};

ball_pos pos;
direction dir;

Ball::Ball() {
	pos.x = 0;
	pos.y = 0;
	dir.x = 0;
	dir.y = 0;
}

Ball::~Ball() {}

