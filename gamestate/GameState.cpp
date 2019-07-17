/*
 * GameState.cpp
 *
 *  Created on: 29.06.2019
 *      Author: koenigr
 */

#include "GameState.h"
#include "Ball.h"
#include "Player.h"
#include <string>

#include <stdio.h>

Ball ball;

Player player_arr[4];
int player_self;
unsigned int sequence_no = 0;

GameState::GameState() {}

void GameState::init(int player_no) {
    player_self = player_no;
}

// A player knows only his own point in the main loop
int GameState::decrPoint() {
    return player_arr[player_self].decrPoints();
}

Player GameState::getSelf() {
    return player_arr[player_self];
}

Player GameState::getPlayer(int i) {
    return player_arr[i];
}

Ball GameState::getBall() {
    return ball;
}

unsigned int GameState::getSequenceNo() {
    return sequence_no;
}

unsigned int GameState::incrSequenceNo() {
    sequence_no += 1;
    return sequence_no;
}

int GameState::getPlayerNo() {
    return player_self;
}

