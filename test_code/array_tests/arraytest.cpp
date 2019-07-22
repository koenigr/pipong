#include "../../gamestate/Player.h"
#include <iostream>

int main() {
    Player* player_arr[2];

    std::cout << "player_arr addr: " << player_arr << "\n";
    std::cout << "player 0 addr: " << player_arr[0] << "\n";
    std::cout << "player 1 addr: " << player_arr[1] << "\n";

    player_arr[0] = new Player();
    player_arr[1] = new Player();

    std::cout << "player_arr addr: " << player_arr << "\n";
    std::cout << "player 0 addr: " << player_arr[0] << "\n";
    std::cout << "player 1 addr: " << player_arr[1] << "\n";

    player_arr[0]->init(0,3);

    std::cout << "player_arr addr: " << player_arr << "\n";
    std::cout << "player 0 addr: " << player_arr[0] << "\n";
    std::cout << "player 1 addr: " << player_arr[1] << "\n";

    std::cout << player_arr[0]->getPlayerNo() << "\n";
    std::cout << player_arr[1]->getPlayerNo() << "\n";

    player_arr[1]->init(1,3);

    std::cout << player_arr[0]->getPlayerNo() << "\n";
    std::cout << player_arr[1]->getPlayerNo() << "\n";


    std::cout << "player_arr addr: " << player_arr << "\n";
    std::cout << "player 0 addr: " << player_arr[0] << "\n";
    std::cout << "player 1 addr: " << player_arr[1] << "\n";


    std::cout << player_arr[0]->toString() << "\n";
    std::cout << player_arr[1]->toString() << "\n";
    std::cout << player_arr[0]->getPlayerNo() << "\n";
    std::cout << player_arr[1]->getPlayerNo() << "\n";



    Player* p1;
    Player* p2;

    std::cout << "Complete different player: " << p1->toString() << std::endl;
    std::cout << "Complete different player: " << p2->toString() << std::endl;


    p1->init(0,2);
    p2->init(4,2);

    std::cout << "Complete different player: " << p1->toString() << std::endl;
    std::cout << "Complete different player: " << p2->toString() << std::endl;


    Player* p = new Player();
    std::cout << "Again a new player: " << p->toString() << std::endl;

}
