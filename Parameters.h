/*
 * Parameters.h
 *
 *  Created on: 28.06.2019
 *      Author: koenigr
 */

#ifndef PARAMETERS_H_
#define PARAMETERS_H_

// General
#define BUFSIZE 1024
#define FRAMERATE 10 // 30
#define DISPLAY_SIZE 127
#define PI 3.14159265
#define COUNTDOWN_START_VAL 10 // 50

// Ball
#define INIT_VELOCITY 5 // pixel per frame
#define VELOCITY_INCR 0.5
#define BALL_WIDTH 10

// Player
#define INIT_PLAYER_POINTS 5
#define PADDLE_WIDTH 30

// STATES
#define WAIT_STATE -1
#define FINDPEERS_STATE 0
#define GAME_STATE 1
#define COLLISION_STATE 2
#define FINISH_STATE 3

#endif /* PARAMETERS_H_ */
