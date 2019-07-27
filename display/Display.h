#ifndef DISPLAY_H
#define DISPLAY_H

#include "../gamestate/GameState.h"

class Display
{
private:
    static void drawPlayer(const GameState gs);
    static void drawBall(const GameState gs);
public:

    static void drawHello();
    static void drawGameState(const GameState gs);
    static void drawPoints(const GameState gs);
};

#endif // DISPLAY_H
