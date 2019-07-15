/*
 * GameState.cpp
 *
 *  Created on: 29.06.2019
 *      Author: koenigr
 */

#include "GameState.h"

#include "Ball.h"
#include "Player.h"
#include <string.h>
#include <stdio.h>

Ball ball;
Player p1; // TODO var
Player p2;
Player p3;
Player p4;

int GameState::decrPoint(Player p) {
	return p.decrPoints();
}

void GameState::toString(char gmst_str[]) {
    snprintf(gmst_str, 3, "jjj");
}
