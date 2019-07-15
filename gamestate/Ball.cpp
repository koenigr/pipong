/*
 * Ball.cpp
 *
 *  Created on: 29.06.2019
 *      Author: koenigr
 */
#include <stdio.h>

#include "Ball.h"


struct ball_pos {
	int x;
	int y;
};

struct direction {
	int x;
	int y;
};

int velocity;

ball_pos pos;
direction dir;

Ball::Ball() {
	pos.x = 0;
	pos.y = 0;
	dir.x = 0;
	dir.y = 0;
	velocity = 1; // TODO
}

Ball::~Ball() {}

void Ball::toString(char ball_str[]) {
//    if (sizeof(ball_str)/sizeof(ball_str[0]) < 6) {
//        printf("Array to small!!\n");
//        exit(1);
//    }
    ball_str[0] = (char) pos.x;
    ball_str[1] = (char) pos.y;
}

