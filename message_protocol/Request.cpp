#include "stdio.h"
#include "Request.h"
#include <string.h>

char req[] = "REQ";

Request::Request() {}

Request::Request(char out_str[], int player_self) {
    sprintf(out_str, "%s %s", req,  ip_addr);
}
