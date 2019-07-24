#ifndef DISPLAY_H
#define DISPLAY_H

#include "../gamestate/GameState.h"

class Display
{
private:
    static void drawPlayer(int player_no, GameState gs);
public:
    static void drawGameState(GameState gs);
};

#endif // DISPLAY_H
