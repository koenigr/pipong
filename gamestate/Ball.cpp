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

int Ball::setPosX(int posX) {
    pos_x = posX;
    return pos_x;
}

int Ball::setPosY(int posY) {
    pos_y = posY;
    return pos_y;
}

std::string Ball::toString() {

    std::string ball_to_string = "Ball";

    ball_to_string += " posX: " + std::to_string(pos_x);
    ball_to_string += " posY: " + std::to_string(pos_y);
    ball_to_string += " velX: " + std::to_string(vel_x);
    ball_to_string += " velY: " + std::to_string(vel_y);

    return ball_to_string;
}
