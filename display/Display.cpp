#include "Display.h"
#include "../gamestate/GameState.h"
#include <iostream>

void Display::drawPlayer(const GameState gs) {
    std::cout << "Player_self: " << gs.getPlayerNo() << "\n";
    std::cout << "TODO: Player rotate into wrong direction\n";
    for (int i = 0; i < 4; i++) {
        Player player = gs.getPlayer(i);
        std::cout << "Player " << i
                << ": (" << player.getLeftEndX() << "," << player.getLeftEndY() << "),("
                << player.getRightEndX() << "," << player.getRightEndY() << ")\n";
    }
}

void Display::drawBall(const GameState gs) {
    std::cout << "Ball " << gs.getBall().toString() << std::endl;
}

void Display::drawGameState(const GameState gs) {
    drawPlayer(gs);
    drawBall(gs);
}
