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

GameState::GameState() {}

void GameState::init(int player_no) {
    printf("Player points: %d\n", player_arr[0].getPlayerPoints());
    player_self = player_no;
}

// A player knows only his own point in the main loop
int GameState::decrPoint() {
    return player_arr[player_self].decrPoints();
}

Player GameState::getPlayer(int i) {
    return player_arr[i];
}

