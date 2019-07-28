#include "../../input/InputManager.cpp"
#include <iostream>
#include "../../display/Display.cpp"

int main() {

    InputManager::init();

    while(true) {

        std::cout << InputManager::startButtonPressed() << std::endl;

    }

}
