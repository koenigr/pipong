#include "../../gamestate/Player.h"
#include <iostream>

int main() {
    Player* player_arr[4];
    player_arr[0]->init(0,3);
    player_arr[1]->init(1,3);
    std::cout << player_arr[0]->toString() << "\n";
    std::cout << player_arr[1]->toString() << "\n";
}
