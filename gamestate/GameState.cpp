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

Ball ball;
Player p1; // TODO var
Player p2;
Player p3;
Player p4;

void GameState::decrPoint(Player p) {
	int points = p.decrPoints();
}

void GameState::toString(char gmst_str[]) {
    strlcpy(gmst_str, "jjj", 3);
}
