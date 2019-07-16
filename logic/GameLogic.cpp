/*
 * GameLogic.cpp
 *
 *  Created on: 29.06.2019
 *      Author: koenigr
 */

#include "GameLogic.h"
#include "../gamestate/GameState.h"

GameLogic::GameLogic() {
	// TODO Auto-generated constructor stub

}

GameLogic::~GameLogic() {
	// TODO Auto-generated destructor stub
}

void GameLogic::updateBall(GameState gs) {
    gs.getBall().setPosX(gs.getBall().getPosX() + gs.getBall().getVelX());
    gs.getBall().setPosY(gs.getBall().getPosY() + gs.getBall().getVelY());
}

bool GameLogic::checkForPaddleCollision(GameState gs) {
    return true;
}

bool GameLogic::checkForScoringZoneCollision(GameState gs) {
    return false;
}


