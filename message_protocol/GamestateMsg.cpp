#include "stdio.h"
#include "GamestateMsg.h"
#include <string.h>

#include "../gamestate/GameState.h"


char gmstMsg[] = "GMST";

GamestateMsg::GamestateMsg() {}

GamestateMsg::GamestateMsg(char out_str[], GameState gamestate) {
    char gmst_str[];
    gamestate.toString(gmst_str);
    sprintf(out_str, "%s %s", gmstMsg, gmst_str);
}
