#include "stdio.h"
#include "Response.h"
#include <string.h>

char res[] = "RES";

Response::Response() {}

Response::Response(char out_str[], char ip_addr[]) {
    sprintf(out_str, "%s %s", res,  ip_addr);
}
