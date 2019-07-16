#include "Response.h"
#include <string>
#include <stdio.h>

#include "../Parameters.h"

void Response::createResponse(char out_arr[], int player_self){
    out_arr[0] = RESPONSE + '0';
    out_arr[1] = player_self + '0';
    out_arr[2] = '\0';
}
