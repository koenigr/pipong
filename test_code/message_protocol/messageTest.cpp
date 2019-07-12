#include "Gamestate.h"
#include "MessageProtocol.h"
#include "Parameters.h"
#include "Request.h"
#include "Parameters.h"

#define BUFSIZE 1024

int main() {

	MessageProtocol mp;

	char request[BUFSIZE];
	char ip[] = "1.2,3,4";
	int port = 1234;

	mp.createRequest(request, ip, port);
	printf("created request: %s\n", request);

}
