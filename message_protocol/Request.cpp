#include "stdio.h"
#include "Request.h"
#include <string.h>

char req[] = "REQ";

Request::Request() {}

Request::Request(char out_str[], char ip_addr[]) {
    sprintf(out_str, "%s %s", req,  ip_addr);
}
