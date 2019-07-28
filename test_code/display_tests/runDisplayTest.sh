#/bin/bash

g++ 	DisplayTest.cpp \
	../../display/Display.cpp \
	../../gamestate/GameState.cpp \
	../../gamestate/Player.cpp \
	../../gamestate/Ball.cpp \
	-lmraa -std=c++11 \
	-o DisplayTest

if [ $? -eq 0 ]; then
	./DisplayTest
fi
