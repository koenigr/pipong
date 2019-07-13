#include "GamestateMsg.h"
#include "MessageProtocol.h"
#include "Parameters.h"
#include "Request.h"
#include "Parameters.h"

int main() {

	MessageProtocol mp;
	char ip[] = "10.1.1.20";
	int port = 2222;

	// REQUEST TESTS

	char request[BUFSIZE];

	mp.createRequest(request, ip, port);
	printf("created request: %s\n", request);
	printf("request length: %lu\n", strlen(request));

	// RESPONSE TESTS

	char response[BUFSIZE];

	mp.createResponse(response, ip, port);
	printf("created response: %s\n", response);
	printf("response length: %lu\n", strlen(response));

	// GAMESTATE TESTS


}
