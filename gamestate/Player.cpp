/*
 * Player.cpp
 *
 *  Created on: 29.06.2019
 *      Author: koenigr
 */

#include "Player.h"
#include <string>

int playerPos;
int points;

Player::Player() {
	playerPos = 0;
	points = 5;
}

Player::~Player() {}

int Player::decrPoints() {
	points -= 1;
	return points;
}

int Player::getPlayerPos() {
    return playerPos;
}

int Player::getPlayerPoints() {
    return points;
}


