#!/bin/bash


gamestate     message_protocol  pipong.cpp  test_code
display   inputmanager  network           README.md   todo.txt
docs      logic         Parameters.h      states      tools


clear

g++ pipong.cpp \
    network/*.cpp \
    tools/*.cpp \
    message_protocol/*.cpp \
    gamestate/*.cpp \
    test_code/*.cpp \
    display/*.cpp \
    logic/*.cpp \
    states/*.cpp \
    -o PiPong -std=c++11 -Wall -Wextra -Wpedantic 
#-Werror
