!#/bin/bash

clear

g++ gamestate_tests.cpp ../../gamestate/GameState.cpp ../../gamestate/Ball.cpp ../../gamestate/Player.cpp -std=c++11 -o GameStateTest
