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
#define REQUEST_SIZE 2
#define RESPONSE_SIZE 0
#define PLAYER_SIZE 0
#define BALL_SIZE 0
#define COLLISION_SIZE 0
#define FINISH_SIZE 0

// Opcodes
#define REQUEST 0
#define RESPONSE 1
#define PLAYER 2
#define BALL 3
#define COLLISION 4
#define FINISH 5

#endif /* PARAMETERS_H_ */
