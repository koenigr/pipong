#include "../../input/InputManager.cpp"
#include <iostream>

int main() {

    InputManager::init();

    while(true) {

        std::cout << InputManager::startButtonPressed() << std::endl;

    }

}
