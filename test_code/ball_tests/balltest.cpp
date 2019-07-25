#include "../../gamestate/GameState.h"

#include <string>
#include <iostream>

GameState gs;

int main(int argc, char* argv[]) {
    if (argc > 1) {
        gs.init(atoi(argv[1]));
    }
    else {
        gs.init((0));
    }
    std::cout << gs.getBall().toString() << std::endl;
    std::cout << "Player number: " << gs.getPlayerNo() << std::endl;

//    for (int i = 0; i < 200; i++) {
//        gs.updateBall();
//        std::cout << gs.getBall().toString() << std::endl;
//    }

    gs.setPlayerActive(false, 0);
    gs.setPlayerActive(false, 1);
    gs.setPlayerActive(false, 2);
    gs.setPlayerActive(false, 3);

    gs.newRound(3);
    std::cout << gs.toString() << std::endl;
    gs.newRound(4);
    std::cout << gs.toString() << std::endl;
    gs.newRound(5);
    std::cout << gs.toString() << std::endl;
}
