/*
 * GameLogic.h
 *
 *  Created on: 29.06.2019
 *      Author: koenigr
 */

#ifndef LOGIC_GAMELOGIC_H_
#define LOGIC_GAMELOGIC_H_

class GameLogic {
public:
	GameLogic();
	virtual ~GameLogic();
    void updateBall(GameState gs);
    bool checkForPaddleCollision(GameState gs);
    bool checkForScoringZoneCollision(GameState gs);
};

#endif /* LOGIC_GAMELOGIC_H_ */
