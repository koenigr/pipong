#include "../../input/InputManager.h"
#include <iostream>
#include "unistd.h"

int main() {

    InputManager::init();

    std::cout << "Starting\n";

    while(true) {

        bool pressed = InputManager::startButtonPressed();
        if (pressed) {
           std::cout << "Pressed\n";
        }
        usleep(100 * 1000);
    }

}
