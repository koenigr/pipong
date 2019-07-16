/*
 * MessageProtocol.cpp
 *
 *  Created on: 29.06.2019
 *      Author: koenigr
 */

#include "MessageProtocol.h"

#include "../Parameters.h"
#include "Request.h"
#include "Response.h"
#include "PlayerState.h"
#include "Collision.h"
#include "Finish.h"

Request req;
Response res;
PlayerState ps;
Collision col;
Finish fnsh;

void MessageProtocol::createRequest(char out_str[], int player_self) {
  req.createRequest(out_str, player_self);
}

void MessageProtocol::createResponse(char out_str[], int player_self) {
  res.createResponse(out_str, player_self);
}

void MessageProtocol::createPlayerState(GameState gs, char out_str[], int player_self) {
    ps.createPlayerState(gs, out_str, player_self);
}

void MessageProtocol::createCollision(char out_str[], int player_state) {
    col.createCollision(out_str, player_state);
}

void MessageProtocol::createFinish(GameState gs, char out_str[], int player_state) {
    fnsh.createFinish(gs, out_str, player_state);
}


void MessageProtocol::evalMessage(char in_str[]) {
    switch(in_str[0]) {
        case REQUEST + '0':
            break;
        case RESPONSE + '0':
            break;
        case PLAYER + '0':
            break;
        case COLLISION + '0':
            break;
        case FINISH + '0':
            break;
        default:
            printf("Wrong message type %s\n", in_str[0]);
            exit(1);
    }
}

void MessageProtocol::evalRequest(char in_str[]) {

}

void MessageProtocol::evalResponse(char in_str[]) {

}

void MessageProtocol::evalPlayerState(char in_str[]) {

}

void MessageProtocol::evalCollision(char in_str[]) {

}

void MessageProtocol::evalFinish(char in_str[]) {

}
