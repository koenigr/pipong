/*
 * Tools.cpp
 *
 *  Created on: 27.06.2019
 *      Author: koenigr
 */

#include "Tools.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

struct timeval tp;

static long int getms(timeval tp)  // @suppress("Unused static function")
{
     gettimeofday(&tp, NULL);
     return tp.tv_sec * 1000 + tp.tv_usec / 1000;
}


static void error(const char *msg) // @suppress("Unused static function")
{
    perror(msg);
    exit(1);
}
