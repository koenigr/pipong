/*
 * Player.h
 *
 *  Created on: 29.06.2019
 *      Author: koenigr
 */

#ifndef TEST_CODE_GAMESTATE_PLAYER_H_
#define TEST_CODE_GAMESTATE_PLAYER_H_

#include <string>

class Player {
private:
    int playerPos;
    int points;
    int player_sequence;// TODO!!!!! long unsigned int?
    // player displayed at 0=x_axis or 1=y_axis
    int x_axis;
    int player_no;
public:
    Player();
    virtual ~Player();
    void init(int player_this, int player_self);
    int decrPoints();
    int getPlayerPos();
    int getPlayerPoints();
    int getSequenceNo();
    int getLeftEnd();
    int getRightEnd();
    int getPlayerNo();
    std::string toString();
};

#endif /* TEST_CODE_GAMESTATE_PLAYER_H_ */
