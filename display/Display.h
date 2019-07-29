#ifndef DISPLAY_H
#define DISPLAY_H

#include "../gamestate/GameState.h"

class Display
{
private:
    static void drawPlayer(const GameState gs);
    static void drawBall(const GameState gs);
    static void flush();
    static void draw(char* buf);
public:
    static void init();
    static void drawHello();
    static void drawWaitForPeers(const GameState gs);
    static void drawGameState(const GameState gs);
    static void drawPoints(const GameState gs);
};

#endif // DISPLAY_H
