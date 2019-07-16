#include "stdio.h"
#include "Finish.h"
#include <string>
#include "../gamestate/GameState.h"

#include "../Parameters.h"

void Finish::createFinish(GameState gs, char out_arr[], int player_self){
    out_arr[0] = FINISH + '0';
    out_arr[1] = player_self + '0';
    out_arr[2] = gs.getPlayer(player_self).getPlayerPoints() + '0';
    out_arr[3] = '\0';
}
