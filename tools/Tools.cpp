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
#include <string>
#include <iostream>


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




void Tools::print_address(struct sockaddr_in addr, std::string message) {

    std::cout << "Tools::print_address start...\n";

    char str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(addr.sin_addr), str, INET_ADDRSTRLEN);
    std::cout << "Address: " << message << str << "\n";

    std::cout << "Tools::print_address end\n";

}
