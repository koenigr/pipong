/*
 * Ball.cpp
 *
 *  Created on: 29.06.2019
 *      Author: koenigr
 */
#include <stdio.h>
#include <string>
#include <math.h>
#include <iostream>
#include <stdlib.h>

#include "Ball.h"
#include "../Parameters.h"

Ball::Ball() {}
Ball::~Ball() {}

// The ball position is internally stored as float but must be returned as int
int Ball::getPosX() const {
    return pos_x;
}

// The ball position is internally stored as float but must be returned as int
int Ball::getPosY() const {
    return pos_y;
}

float Ball::getAngle() const {
    return angle;
}

float Ball::getVelocity() const {
    return velocity;
}

void Ball::resetBall(const int seed) {
    pos_x = DISPLAY_SIZE / 2;
    pos_y = DISPLAY_SIZE / 2;
    srand(seed);
    angle = rand() * 360.0 / RAND_MAX;
}

float Ball::incrVelocity() {
    velocity += VELOCITY_INCR;
    return velocity;
}

float Ball::setAngle(int player_self, float new_angle) {
    angle = new_angle;
    switch (player_self) {
    case 0:
        angle += 0.0;
        break;
    case 1:
        angle += 180.0;
        break;
    case 2:
        angle += 270.0;
        break;
    case 3:
        angle += 90.0;
        break;
    default:
        std::cout << "Invalid player number\n";
        exit(1);
    }

    angle = fmod(angle, 360);
    return angle;
}


/*
 * +-1-+
 * |   |
 * 2   3
 * |   |
 * +-0-+
 */
void Ball::reflectBall(int side) {
    switch (side) {
    case 0:
        angle = fmod(360 + 180 - angle, 360);
        break;
    case 1:
        angle = fmod(360 + 180 - angle, 360);
        break;
    case 2:
        angle = fmod(360 - angle, 360);
        break;
    case 3:
        angle = fmod(360 - angle, 360);
        break;
    default:
        std::cout << "Invalid side\n";
        exit(1);
    }

    angle -= 5;
}

void Ball::updateBall() {
    pos_x += velocity * sin(angle * PI / 180.0);
    pos_y += velocity * cos(angle * PI / 180.0);
    std::cout << "Ball:updateBall() " << ball_frame << std::endl;
    ball_frame += 1;
    std::cout << "Ball:updateBall() " << ball_frame << std::endl;
//    std::cout << "Ball::updateBall() " << pos_x << "," << pos_y << std::endl;
}


std::string Ball::toString() const {

    std::string ball_to_string = "Ball";

    ball_to_string += " ball_frame: " + std::to_string(ball_frame);
    ball_to_string += " posX: " + std::to_string(pos_x);
    ball_to_string += " posY: " + std::to_string(pos_y);
    ball_to_string += " angle: " + std::to_string(angle);
    ball_to_string += " velocity: " + std::to_string(velocity);

    return ball_to_string;
}
