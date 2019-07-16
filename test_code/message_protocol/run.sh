#!/bin/bash

clear

g++ messageTest.cpp 	../../message_protocol/MessageProtocol.cpp \
			../../message_protocol/Request.cpp \
			../../message_protocol/Response.cpp  \
			../../gamestate/Player.cpp \
			../../gamestate/Ball.cpp \
			../../gamestate/GameState.cpp \
			-o MessageTest -std=c++11

if [ $? -eq 0 ]; then
    ./MessageTest
fi
