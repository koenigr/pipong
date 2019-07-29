#/bin/bash

clear

g++ 	ButtonTest.cpp \
        ../../mraa_libs/OLEDDisplay.cpp \
        ../../mraa_libs/Canvas.cpp \
        ../../mraa_libs/Print.cpp \
        ../../mraa_libs/InputManager.cpp \
	-lmraa -std=c++11 -pthread \
	-o ButtonTest

if [ $? -eq 0 ]; then
	./ButtonTest
fi
