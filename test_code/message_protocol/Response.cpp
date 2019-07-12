#include "stdio.h"
#include "Response.h"
#include <string.h>

char res[] = "RES";

Response::Response() {}

Response::Response(char out_str[], char ip_addr[], int port) {
    sprintf(out_str, "%s %s %d", res,  ip_addr, port);
}
