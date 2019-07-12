#include "stdio.h"
#include "GamestateMsg.h"
#include <string.h>

#include "../GameState/GameState.h"


char gmstMsg[] = "GMST";

GamestateMsg::GamestateMsg() {}

GamestateMsg::GamestateMsg(char out_str[], GameState gamestate) {
    sprintf(out_str, "%s", gmstMsg);
}
