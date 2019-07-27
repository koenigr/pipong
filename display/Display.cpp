#include "Display.h"
#include "../gamestate/GameState.h"
#include <iostream>




void Display::drawHello() {
    std::cout << "Welcome to PiPong:)\n";
    std::cout << "Please press a button to start synchronization...\n";
}

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

void Display::drawPoints(const GameState gs) {

    for (int i = 0; i < 4; i++) {

        std::cout << "Player " << i << ": ";
        if (gs.getPlayer(0).isActive()) {
            std::cout << gs.getPlayer(0).getPoints();
        } else {
            std::cout << "x";
        }
        std::cout << std::endl;

    }
}

void Display::drawGameState(const GameState gs) {
    drawPlayer(gs);
    drawBall(gs);
}
