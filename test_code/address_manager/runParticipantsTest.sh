#!/bin/bash

clear

g++     createParticipants.cpp \
        ../../network/AddressManager.cpp \
        ../../tools/Tools.cpp \
        -o ParticipantsTest \
        --std=c++11

if [ $? -eq 0 ]; then
    ./ParticipantsTest
fi
