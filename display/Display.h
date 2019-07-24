#ifndef DISPLAY_H
#define DISPLAY_H

#include "../gamestate/GameState.h"

class Display
{
public:
    Display();
    void drawPlayer(int player_no, GameState gs);
};

#endif // DISPLAY_H
