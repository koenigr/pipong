!#/bin/bash

clear

g++ gamestate_tests.cpp ../../gamestate/GameState.cpp ../../gamestate/Ball.cpp ../../gamestate/Player.cpp -std=c++11 -o GameStateTest

if [ $? -eq 0 ]; then
    ./GameStateTest
fi
