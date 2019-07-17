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
unsigned int frame_no = 0;

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

unsigned int GameState::getFrameNo() {
    return frame_no;
}

unsigned int GameState::incrFrameNo() {
    frame_no += 1;
    return frame_no;
}

int GameState::getPlayerNo() {
    return player_self;
}

