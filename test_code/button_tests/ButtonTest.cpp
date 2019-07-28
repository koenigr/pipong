#include "../../input/InputManager.h"
#include <iostream>


int main() {

    InputManager::init();

    while(true) {

        std::cout << InputManager::startButtonPressed() << std::endl;

    }

}
