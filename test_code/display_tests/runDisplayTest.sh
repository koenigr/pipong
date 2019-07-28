#/bin/bash

g++ 	DisplayTest.cpp \
	../../display/Display.cpp \
	../../display/Canvas.cpp \
	../../display/OLEDDisplay.cpp \
	../../display/Print.cpp \
	../../gamestate/GameState.cpp \
	../../gamestate/Player.cpp \
	../../gamestate/Ball.cpp \
	-lmraa -std=c++11 -pthread \
	-o DisplayTest

if [ $? -eq 0 ]; then
	./DisplayTest
fi
