/*
 * Player.cpp
 *
 *  Created on: 29.06.2019
 *      Author: koenigr
 */

#include "Player.h"
#include "../Parameters.h"

#include <string>
#include <iostream>

Player::Player() {}

void Player::init(int player_this, int player_self) {
    playerPos = 0;
    points = INIT_PLAYER_POINTS;
    player_sequence = 3; // TODO!!!
    player_no = player_this;
    x_axis = (player_no + player_self) % 2;
    oth_axis = ((player_no + player_self) % 4) > 1;
    std::cout << "Axis: " << std::to_string(x_axis) << "\n";
}

Player::~Player() {}


int Player::decrPoints() {
	points -= 1;
	return points;
}

int Player::getPlayerPos() const {
    return playerPos;
}

int Player::getPlayerPoints() const {
    return points;
}

int Player::getSequenceNo() const {
    return player_sequence;
}

std::string Player::toString() const {

    std::string player_to_string = "Player " + std::to_string(player_no);
    player_to_string += " position: " + std::to_string(playerPos);
    player_to_string += " points: " + std::to_string(points);
    player_to_string += " sequence: " + std::to_string(player_sequence);
    player_to_string += " axis: " + std::to_string(x_axis);
    player_to_string += " oth_axis: " + std::to_string(oth_axis);
    player_to_string += " (" + std::to_string(getLeftEndX());
    player_to_string += "," + std::to_string(getLeftEndY());
    player_to_string += "),(" + std::to_string(getRightEndX());
    player_to_string += "," + std::to_string(getRightEndY()) + ")";

    return player_to_string;
}

int Player::getLeftEndX() const {
    return (DISPLAY_SIZE/2 + playerPos - PADDLE_WIDTH/2)*(!x_axis)
            +DISPLAY_SIZE*(oth_axis)*(x_axis);
}

int Player::getRightEndX() const {
    return (DISPLAY_SIZE/2 + playerPos + PADDLE_WIDTH/2)*(!x_axis)
            +DISPLAY_SIZE*(oth_axis)*(x_axis);
}

int Player::getLeftEndY() const {
    return (DISPLAY_SIZE/2 + playerPos - PADDLE_WIDTH/2)*(x_axis)
            +DISPLAY_SIZE*(oth_axis)*(!x_axis);
}

int Player::getRightEndY() const {
    return (DISPLAY_SIZE/2 + playerPos + PADDLE_WIDTH/2)*(x_axis)
            +DISPLAY_SIZE*(oth_axis)*(!x_axis);
}

int Player::getPlayerNo() const {
    return player_no;
}

