#include "../../input/InputManager.cpp"
#include <iostream>


using namespace GFX;

int main() {

    InputManager::init();

    while(true) {

        std::cout << InputManager::startButtonPressed() << std::endl;

    }

}
