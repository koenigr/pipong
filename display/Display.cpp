#include "Display.h"
#include "../gamestate/GameState.h"
#include <iostream>

Display::Display()
{

}

void Display::drawPlayer(int player_no, GameState gs) {
    Player player = gs.getPlayer(player_no);
    int left = player.getLeftEndX();
    int right = player.getRightEndY();
    std::cout << "(" << player.getLeftEndX() << "," << player.getLeftEndY() << "),("
              << player.getRightEndX() << "," << player.getRightEndY() << ")\n";
}
