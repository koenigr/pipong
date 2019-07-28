#/bin/bash

clear

g++ 	ButtonTest.cpp \
	../../input/OLEDDisplay.cpp \
	../../input/Canvas.cpp \
	../../input/Print.cpp \
	../../input/InputManager.cpp \
	-lmraa -std=c++11 -pthread \
	-o ButtonTest

if [ $? -eq 0 ]; then
	./ButtonTest
fi
