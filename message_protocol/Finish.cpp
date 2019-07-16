#include "stdio.h"
#include "Finish.h"
#include <string.h>

void Finish::createFinish(char out_str[], int player_self){
    sprintf(out_str, "%c", player_self);
}
