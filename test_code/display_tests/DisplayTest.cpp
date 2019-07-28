#include "../../display/Display.h"
#include "../../gamestate/GameState.h"
#include <iostream>
#include "unistd.h"

int main()  {

GameState gs;
gs.init(0);

Display::init();

std::cout << "Draw Hello:\n";

while(true) {

    Display::drawHello();
    usleep(100000);

}

std::cout << "Draw gamstate:\n";

Display::drawGameState(gs);

std::cout << "Draw Points\n";

Display::drawPoints(gs);

}
