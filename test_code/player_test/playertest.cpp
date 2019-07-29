#include "../../gamestate/GameState.h"
#include "../../gamestate/Player.h"

#include <iostream>

int main() {

    GameState gs0;
    gs0.init(0);
    //std::cout << gs0.toString() << std::endl;
//    gs0.setPlayerActive(1,1);
//    gs0.setPlayerActive(1,2);
//    gs0.setPlayerActive(1,3);
    std::cout << gs0.toString() << std::endl;
    std::cout << gs0.getSelf().toString() << std::endl;

    GameState gs1;
    gs1.init(1);
    //std::cout << gs1.toString() << std::endl;
//    gs1.setPlayerActive(1,0);
//    gs1.setPlayerActive(1,2);
//    gs1.setPlayerActive(1,3);
    std::cout << gs1.toString() << std::endl;
    std::cout << gs1.getSelf().toString() << std::endl;

    GameState gs2;
    gs2.init(2);
    //std::cout << gs2.toString() << std::endl;
//    gs2.setPlayerActive(1,0);
//    gs2.setPlayerActive(1,1);
//    gs2.setPlayerActive(1,3);
    std::cout << gs2.toString() << std::endl;
    std::cout << gs2.getSelf().toString() << std::endl;

    GameState gs3;
    gs3.init(3);
    //std::cout << gs3.toString() << std::endl;
//    gs3.setPlayerActive(1,0);
//    gs3.setPlayerActive(1,1);
//    gs3.setPlayerActive(1,2);
    std::cout << gs3.toString() << std::endl;
    std::cout << gs3.getSelf().toString() << std::endl;

}
