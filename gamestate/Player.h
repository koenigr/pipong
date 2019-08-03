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
    int position;
    int points;
    // player displayed at 0=x_axis or 1=y_axis
    int x_axis;
    // other axis is at 0=0 or 1=DISPLAY_SIZE
    int oth_axis;
    int player_no;
    bool active;
    unsigned int frame;

    int paddle_width = PADDLE_WIDTH_;

public:
    Player();
    virtual ~Player();
    void init(int player_this, int player_self);
    bool setPlayerActive(bool isActive);
    bool isActive() const;

    unsigned int getFrame();
    unsigned int incrFrame();
    unsigned int setFrame(unsigned int const new_frame);

    int decrPoints();
    int setPoints(int new_points);
    int getPoints() const;

    int setPosition(int new_position);
    int getPosition() const;

    void decrPaddleWidth();
    int getPaddleWidth() const;

    int getLeftEndX() const;
    int getRightEndX() const;
    int getLeftEndY() const;
    int getRightEndY() const;

    int getPlayerNo() const;

    std::string toString() const;
};

#endif /* TEST_CODE_GAMESTATE_PLAYER_H_ */
