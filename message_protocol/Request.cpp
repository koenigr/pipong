#include "Request.h"
#include <string.h>
#include <stdio.h>

#include "Opcode.h"

char req[] = "REQ";

Request::Request() {}

void Request::createRequest(char out_arr[], int player_self) {
    out_arr[0] = REQUEST;
    out_arr[1] = player_self;
}
