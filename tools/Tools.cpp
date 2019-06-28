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
#include <arpa/inet.h>

struct timeval tp;

long int Tools::getms()  // @suppress("Unused static function")
{
     gettimeofday(&tp, NULL);
     return tp.tv_sec * 1000 + tp.tv_usec / 1000;
}


void Tools::error(const char *msg) // @suppress("Unused static function")
{
    perror(msg);
    exit(1);
}




void Tools::print_address(struct sockaddr_in addr, char message[]) {

    char str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(addr.sin_addr), str, INET_ADDRSTRLEN);
    printf("%s Address: %s\n",message, str);

}
