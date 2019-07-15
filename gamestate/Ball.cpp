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

float* Ball::increaseVel() {
  float vel[2];
  vel[0] = vel_x;
  vel[1] = vel_y;
  return vel;
}

std::string Ball::toString() {
  return std::to_string(pos_x) + std::string(" ") + std::to_string(pos_y)
          + std::string(" ") +std::to_string(vel_x) + std::string(" ") + std::to_string(vel_y);
}

