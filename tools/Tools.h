/*
 * Tools.h
 *
 *  Created on: 27.06.2019
 *      Author: koenigr
 */

#ifndef TOOLS_H_
#define TOOLS_H_

#include <sys/time.h>

class Tools {

	static long int getms(timeval tp);
	static void error(const char *msg);

};

#endif /* TOOLS_H_ */
