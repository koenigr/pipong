#include "../../input/InputManager.h"
#include <iostream>


int main() {

    InputManager::init();

    while(true) {

        int old = true;
        int new = InputManager::startButtonPressed();
        if (old != new) {
            std::cout << InputManager::startButtonPressed() << std::endl;
        }
        old = new;
    }

}
