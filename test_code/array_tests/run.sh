#!/bin/bash

clear; g++ arraytest.cpp ../../gamestate/Player.cpp -o playerTest --std=c++11

if [ $? -eq 0 ]; then
  ./playerTest
fi
