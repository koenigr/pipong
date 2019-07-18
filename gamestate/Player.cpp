/*
 * Player.cpp
 *
 *  Created on: 29.06.2019
 *      Author: koenigr
 */

#include "Player.h"
#include "../Parameters.h"

#include <string>

int playerPos;
int points;
int player_sequence; // TODO!!!!!

Player::Player() {
	playerPos = 0;
    points = INIT_PLAYER_POINTS;
    player_sequence = 3; // TODO!!!!
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

int Player::getSequenceNo() {
    return player_sequence;
}

std::string Player::toString() {

    std::string player_to_string = "Player";

    player_to_string += " position: " + std::to_string(playerPos);
    player_to_string += " points: " + std::to_string(points);
    player_to_string += " sequence: " + std::to_string(player_sequence);

    return player_to_string;
}


