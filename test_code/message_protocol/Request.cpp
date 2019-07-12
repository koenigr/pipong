#include "stdio.h"
#include "Request.h"
#include <string.h>

Request::Request() {}

Request::Request(char out_str[], char ip_addr[], int port) {
    printf("Request::Request out_str length %lu\n", strlen(out_str));
    printf("Request::Request received out_str: %s\n", out_str);
}
