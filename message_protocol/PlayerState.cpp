#include "stdio.h"
#include "PlayerState.h"
#include <string>

#include "../Parameters.h"
#include "../gamestate/GameState.h"

void PlayerState::createPlayerState(GameState gs, char out_arr[], int player_self){
    // TODO general header
    out_arr[0] = PLAYER + '0';
    out_arr[1] = player_self + '0';
    out_arr[2] = gs.getPlayer(player_self).getSequenceNo() + '0'; // TODO passt nicht in ein char
    out_arr[3] = gs.getPlayer(player_self).getPlayerPos() + '0'; // TODO passt nicht in ein char, vllt pos/10 + pos % 10
    out_arr[4] = '\0';
    //TODO pno seq pos
}
