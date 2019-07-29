#!/bin/bash

clear

g++ pipong.cpp \
    network/*.cpp \
    tools/*.cpp \
    message_protocol/*.cpp \
    gamestate/*.cpp \
    display/*.cpp \
    states/*.cpp \
    input/*.cpp \
    mraa_libs/*.cpp \
    -o PiPong \
    -std=c++11 -lmraa -pthread \
    -Wall -Wextra -Wpedantic 
#-Werror

if [ $? -eq 0 ]; then
  ./PiPong $1 $2
fi
