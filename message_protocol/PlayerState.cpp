#include "stdio.h"
#include "PlayerState.h"
#include <string.h>

void PlayerState::createPlayerState(char out_str[], int player_self){
    sprintf(out_str, "%c", player_self);
}
