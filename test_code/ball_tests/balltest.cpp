#include "../../gamestate/GameState.h"

#include <string>
#include <iostream>

GameState gs;

int main() {
    std::cout << gs.getBall().toString() << std::endl;
    for (int i = 0; i < 10; i++) {
        gs.updateBall();
        std::cout << gs.getBall().toString() << std::endl;
    }
}
