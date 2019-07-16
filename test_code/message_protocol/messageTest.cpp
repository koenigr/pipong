#include "../../message_protocol/MessageProtocol.h"
#include "../../message_protocol/Request.h"
#include "../../Parameters.h"

#define BUFSIZE 1024

int main() {

	MessageProtocol mp;
	char ip[] = "10.1.1.20";
	int port = 2222;
    int player_self = 2;

	// REQUEST TESTS

    char request[REQUEST_SIZE];

    mp.createRequest(request, player_self);
	printf("created request: %s\n", request);
	printf("request length: %lu\n", strlen(request));

	// RESPONSE TESTS

    char response[RESPONSE_SIZE];

    mp.createResponse(response, ip);
    printf("created response: %s\n", response);
    printf("response length: %lu\n", strlen(response));

    // PLAYER TESTS

    char response[RESPONSE_SIZE];

    mp.createResponse(response, ip);
    printf("created response: %s\n", response);
    printf("response length: %lu\n", strlen(response));

    // BALL TESTS

    char response[RESPONSE_SIZE];

    mp.createResponse(response, ip);
    printf("created response: %s\n", response);
    printf("response length: %lu\n", strlen(response));

    // COLLISION TESTS

    char response[RESPONSE_SIZE];

    mp.createResponse(response, ip);
    printf("created response: %s\n", response);
    printf("response length: %lu\n", strlen(response));

    // FINISH TESTS

    char response[RESPONSE_SIZE];

    mp.createResponse(response, ip);
    printf("created response: %s\n", response);
    printf("response length: %lu\n", strlen(response));



	// GAMESTATE TESTS


}
