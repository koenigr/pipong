#/bin/bash

g++ 	ButtonTest.cpp \
	#../../display/Display.cpp \
	#../../display/Canvas.cpp \
	../../display/OLEDDisplay.cpp \
	#../../display/Print.cpp \
	../../input/InputManager.cpp \
	#../../gamestate/GameState.cpp \
	#../../gamestate/Player.cpp \
	#../../gamestate/Ball.cpp \
	-lmraa -std=c++11 -pthread \
	-o ButtonTest

if [ $? -eq 0 ]; then
	./ButtonTest
fi
