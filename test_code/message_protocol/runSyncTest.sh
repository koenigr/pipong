#!/bin/bash

clear

g++ SyncCountdown.cpp 	../../message_protocol/MessageProtocol.cpp \
                        ../../gamestate/GameState.cpp \
                        ../../gamestate/Ball.cpp \
                        ../../gamestate/Player.cpp \
                        -o SyncTest -std=c++11

if [ $? -eq 0 ]; then
    ./SyncTest
fi
