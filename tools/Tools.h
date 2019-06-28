/*
 * Tools.h
 *
 *  Created on: 27.06.2019
 *      Author: koenigr
 */

#ifndef TOOLS_H_
#define TOOLS_H_

class Tools {

public:
	static long int getms();
	static void error(const char *msg);
	static void print_address(struct sockaddr_in addr, char message[]);

};

#endif /* TOOLS_H_ */
