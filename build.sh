#!/bin/bash

g++ pipong.cpp \
    network/*.cpp \
    tools/*.cpp \
    message_protocol/*.cpp \
    gamestate/*.cpp \
    -o PiPong -std=c++11 -Wall -Wextra -Wpedantic 
#-Werror
