#include "stdio.h"
#include "Response.h"
#include <string.h>

Response::Response() {}

void Response::createResponse(char out_str[], int player_self){
    sprintf(out_str, "%c", player_self);
}
