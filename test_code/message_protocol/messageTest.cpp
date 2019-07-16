#include "../../message_protocol/MessageProtocol.h"
#include "../../message_protocol/Request.h"
#include "../../Parameters.h"
#include "../../gamestate/GameState.h"

#define BUFSIZE 1024

int main() {

	MessageProtocol mp;
    GameState gs;
    int player_self = 2;

	// REQUEST TESTS

    char request[REQUEST_SIZE];

    mp.createRequest(request, player_self);
	printf("created request: %s\n", request);
    printf("request length: %lu\n", sizeof(request));

	// RESPONSE TESTS

    char response[RESPONSE_SIZE];
    printf("response size 1: %lu\n", sizeof(response));

    mp.createResponse(response, player_self);
    printf("created response: %s\n", response);
    printf("response length: %lu\n", sizeof(response));

    // PLAYER TESTS

    char player_state[PLAYER_SIZE];

    mp.createPlayerState(gs, player_state, player_self);
    printf("created player_state: %s\n", player_state);
    printf("player_state length: %lu\n", sizeof(player_state));

//    // BALL TESTS

//    char response[RESPONSE_SIZE];

//    mp.createResponse(response, ip);
//    printf("created response: %s\n", response);
//    printf("response length: %lu\n", sizeof(response));

    // COLLISION TESTS

    char collision[COLLISION_SIZE];

    mp.createCollision(collision, player_self);
    printf("created collision: %s\n", collision);
    printf("collision length: %lu\n", sizeof(collision));

    // FINISH TESTS

    char finish[FINISH_SIZE];

    mp.createFinish(gs, finish, player_self);
    printf("created finish: %s\n", finish);
    printf("finish length: %lu\n", sizeof(finish));

}
