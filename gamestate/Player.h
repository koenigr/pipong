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
    // playerPos relative to center of display, ie 0 = DISPLAY_SIZE / 2
    int playerPos;
    int points;
    int player_sequence;// TODO!!!!! long unsigned int?
    // player displayed at 0=x_axis or 1=y_axis
    int x_axis;
    // other axis is at 0=0 or 1=DISPLAY_SIZE
    int oth_axis;
    int player_no;
public:
    Player();
    virtual ~Player();
    void init(int player_this, int player_self);
    int decrPoints();
    int getPlayerPos();
    int getPlayerPoints();
    int getSequenceNo();
    int getLeftEndX();
    int getRightEndX();
    int getLeftEndY();
    int getRightEndY();
    int getPlayerNo();
    std::string toString();
};

#endif /* TEST_CODE_GAMESTATE_PLAYER_H_ */
