#include "Display.h"
#include "../gamestate/GameState.h"
#include <iostream>

void Display::drawPlayer(int player_no, GameState gs) {
    Player player = gs.getPlayer(player_no);
    std::cout << "(" << player.getLeftEndX() << "," << player.getLeftEndY() << "),("
              << player.getRightEndX() << "," << player.getRightEndY() << ")\n";
}

void Display::drawGameState(GameState gs) {
    drawPlayer(gs.getPlayerNo(), gs);
}
