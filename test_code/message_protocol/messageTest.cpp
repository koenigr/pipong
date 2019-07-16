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

    char player_state[PLAYER_SIZE];

    mp.createPlayerState(player_state, ip);
    printf("created player_state: %s\n", player_state);
    printf("player_state length: %lu\n", strlen(player_state));

//    // BALL TESTS

//    char response[RESPONSE_SIZE];

//    mp.createResponse(response, ip);
//    printf("created response: %s\n", response);
//    printf("response length: %lu\n", strlen(response));

    // COLLISION TESTS

    char collision[COLLISION_SIZE];

    mp.createCollision(collision, ip);
    printf("created collision: %s\n", collision);
    printf("collision length: %lu\n", strlen(collision));

    // FINISH TESTS

    char finish[FINISH_SIZE];

    mp.createFinish(finish, ip);
    printf("created finish: %s\n", finish);
    printf("finish length: %lu\n", strlen(finish));

}
