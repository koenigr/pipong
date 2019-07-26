#!/bin/bash

clear

g++ playerTest.cpp 	../../message_protocol/MessageProtocol.cpp \
                        ../../gamestate/GameState.cpp \
                        ../../gamestate/Ball.cpp \
                        ../../gamestate/Player.cpp \
                        -o PlayerTest -std=c++11

if [ $? -eq 0 ]; then
    ./PlayerTest
fi
