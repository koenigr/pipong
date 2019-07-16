#include "GamestateMsg.h"
#include "MessageProtocol.h"
#include "Parameters.h"
#include "Request.h"
#include "Parameters.h"

#define BUFSIZE 1024

int main() {

	MessageProtocol mp;
	char ip[] = "10.1.1.20";
	int port = 2222;
    int player_self = 2;

	// REQUEST TESTS

    char request[2];

    mp.createRequest(request, player_self);
	printf("created request: %s\n", request);
	printf("request length: %lu\n", strlen(request));

	// RESPONSE TESTS

	char response[BUFSIZE];

    mp.createResponse(response, ip);
	printf("created response: %s\n", response);
	printf("response length: %lu\n", strlen(response));

	// GAMESTATE TESTS


}
