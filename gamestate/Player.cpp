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

int playerPos;
int points;
int player_sequence;// TODO!!!!! long unsigned int?
// player displayed at 0=x_axis or 1=y_axis
int x_axis;
int player_no;

Player::Player() {}

void Player::init(int player_this, int player_self) {
    playerPos = 0;
    points = INIT_PLAYER_POINTS;
    player_sequence = 3; // TODO!!!
    player_no = player_this;
    x_axis = (player_no + player_self) % 2;
    std::cout << "Axis: " << std::to_string(x_axis) << "\n";
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

    std::string player_to_string = "Player " + std::to_string(player_no);
    player_to_string += " position: " + std::to_string(playerPos);
    player_to_string += " points: " + std::to_string(points);
    player_to_string += " sequence: " + std::to_string(player_sequence);
    player_to_string += " axis: " + std::to_string(x_axis);

    return player_to_string;
}

int Player::getLeftEnd() {

}

int Player::getRightEnd() {

}

int Player::getPlayerNo() {
    return player_no;
}

