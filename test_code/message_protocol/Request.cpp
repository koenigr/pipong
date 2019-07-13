#include "stdio.h"
#include "Request.h"
#include <string.h>

char req[] = "REQ";

Request::Request() {}

Request::Request(char out_str[], char ip_addr[], int port) {
    sprintf(out_str, "%s %s %d", req,  ip_addr, port);
}
