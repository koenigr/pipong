#include "../../display/Display.h"
#include "../../gamestate/GameState.h"
#include <iostream>

int main()  {

GameState gs;
gs.init(0);

std::cout << "Draw Hello:\n";

Display::drawHello();

std::cout << "Draw gamstate:\n";

Display::drawGameState(gs);

std::cout << "Draw Points\n";

Display::drawPoints(gs);

}
