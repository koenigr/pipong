#include "Request.h"
#include <string>
#include <stdio.h>

#include "../Parameters.h"

void Request::createRequest(char out_arr[], int player_self) {
    out_arr[0] = REQUEST + '0';
    out_arr[1] = player_self + '0';
}
