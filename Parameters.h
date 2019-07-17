/*
 * Parameters.h
 *
 *  Created on: 28.06.2019
 *      Author: koenigr
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef PARAMETERS_H_
#define PARAMETERS_H_

#define BUFSIZE 1024

// message sizes
#define REQUEST_SIZE 3
#define RESPONSE_SIZE 3
#define PLAYER_SIZE 5 // TODO
#define BALL_SIZE 2  // TODO
#define COLLISION_SIZE 2 // TODO
#define FINISH_SIZE 4

// Opcodes

#define MSGTYPE_REQUEST 0
#define RESPONSE 1
#define PLAYER 2
#define BALL 3
#define COLLISION 4
#define FINISH 5

#endif /* PARAMETERS_H_ */
