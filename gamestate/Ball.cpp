/*
 * Ball.cpp
 *
 *  Created on: 29.06.2019
 *      Author: koenigr
 */
#include <stdio.h>
#include <string>

#include "Ball.h"

// position
int pos_x;
int pos_y;
// velocity
float vel_x;
float vel_y;

Ball::Ball() {
    pos_x = 0;
    pos_y = 0;
    vel_x = 1.0;
    vel_y = 1.0;
}

Ball::~Ball() {}

void Ball::increaseVel() {

}

int Ball::getPosX() {
    return pos_x;
}

int Ball::getPosY() {
    return pos_y;
}

int Ball::getVelX() {
    return vel_x;
}

int Ball::getVelY() {
    return vel_y;
}
