#!/bin/bash

clear

g++ pipong.cpp \
    network/*.cpp \
    tools/*.cpp \
    message_protocol/*.cpp \
    gamestate/*.cpp \
    display/*.cpp \
    logic/*.cpp \
    states/*.cpp \
    -o PiPong -std=c++11 -Wall -Wextra -Wpedantic 
#-Werror

if [ $? -eq 0 ]; then
  ./PiPong 2
fi
