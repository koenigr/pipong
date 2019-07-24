#include "../../gamestate/GameState.h"

#include <string>
#include <iostream>

GameState gs;

int main(int argc, char* argv[]) {
    if (argc > 1) {
        gs.init(atoi(argv[1]));
    }
    std::cout << gs.getBall().toString() << std::endl;
    std::cout << "Player number: " << gs.getPlayerNo() << std::endl;
    for (int i = 0; i < 200; i++) {
        gs.updateBall();
        std::cout << gs.getBall().toString() << std::endl;
    }
}
