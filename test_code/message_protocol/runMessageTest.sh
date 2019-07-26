#!/bin/bash

clear

g++ messageTest.cpp 	../../message_protocol/MessageProtocol.cpp \
                        ../../gamestate/GameState.cpp \
			../../gamestate/Ball.cpp \
			../../gamestate/Player.cpp \
			-o MessageTest -std=c++11

if [ $? -eq 0 ]; then
    ./MessageTest
fi
