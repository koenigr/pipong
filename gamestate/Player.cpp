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

Player::~Player() {}

void Player::init(int player_this, int player_self) {

    std::cout << "Player:init() start\n";

    position = 0;
    points = INIT_PLAYER_POINTS;
    player_no = player_this;
    x_axis = (player_this > 1) && (player_self <=1) || (player_this <= 1) && (player_self > 1);
    oth_axis =  ((player_self <= 1) && (!(player_self % 2) ^ ((player_this % 2) ^ (player_this > 1)))) || ((player_self > 1) &&  (!(player_this % 2)^(player_self % 2)));
    active = false;
    frame = 0;

    std::cout << "Player:init() end\n";
}

unsigned int Player::getFrame() {
    return frame;
}

unsigned int Player::incrFrame() {
    frame++;
    return frame;
}

unsigned int Player::setFrame(unsigned int const new_frame) {
    frame = new_frame;
    return frame;
}

int Player::decrPoints() {
	points -= 1;
	return points;
}

int Player::setPoints(int new_points) {
   points = new_points;
   return points;
}

int Player::getPoints() const {
    return points;
}

int Player::setPosition(int new_position) {
    position = new_position;
    if (position < -63) position = -63;
    if (position > 127) position = 127;
    return position;
}

int Player::getPosition() const {
    return position;
}

std::string Player::toString() const {

    std::string player_to_string = "Player " + std::to_string(player_no);
    player_to_string += " position: " + std::to_string(position);
    player_to_string += " points: " + std::to_string(points);
    player_to_string += " frame: " + std::to_string(frame);
    player_to_string += " axis: " + std::to_string(x_axis);
    player_to_string += " oth_axis: " + std::to_string(oth_axis);
    player_to_string += " (" + std::to_string(getLeftEndX());
    player_to_string += "," + std::to_string(getLeftEndY());
    player_to_string += "),(" + std::to_string(getRightEndX());
    player_to_string += "," + std::to_string(getRightEndY()) + ")";

    return player_to_string;
}

int Player::getLeftEndX() const {
    std::cout << " displaysize/2: " << DISPLAY_SIZE/2 << " position: " << position << " PaddleWIdth " << PADDLE_WIDTH / 2 << std::endl;
    if (!isActive()) return DISPLAY_SIZE * x_axis * oth_axis;
    return (DISPLAY_SIZE/2 - position - PADDLE_WIDTH /2)*(!x_axis)
            +DISPLAY_SIZE * x_axis * oth_axis;
}

int Player::getRightEndX() const {
    if (!isActive()) return DISPLAY_SIZE * !(x_axis * !oth_axis);
    return (DISPLAY_SIZE/2 - position + PADDLE_WIDTH /2)*(!x_axis)
            +DISPLAY_SIZE * x_axis * oth_axis;
}

int Player::getLeftEndY() const {
    if (!isActive()) return DISPLAY_SIZE * !x_axis * oth_axis ;
    return (DISPLAY_SIZE/2 - position - PADDLE_WIDTH /2)*(x_axis)
            +DISPLAY_SIZE * !x_axis * oth_axis;
}

int Player::getRightEndY() const {
    if (!isActive()) return DISPLAY_SIZE * !(!x_axis*!oth_axis);
    return (DISPLAY_SIZE/2 - position + PADDLE_WIDTH /2)*(x_axis)
            +DISPLAY_SIZE * !x_axis * oth_axis;
}

int Player::getPlayerNo() const {
    return player_no;
}

bool Player::setPlayerActive(bool isActive) {
    active = isActive;
    return active;
}

bool Player::isActive() const {
    return active;
}
