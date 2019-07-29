#/bin/bash

clear

g++     playertest.cpp \
        ../../gamestate/GameState.cpp \
        ../../gamestate/Player.cpp \
        ../../gamestate/Ball.cpp \
        -std=c++11 \
        -o PlayerTest

if [ $? -eq 0 ]; then
    ./PlayerTest
fi
