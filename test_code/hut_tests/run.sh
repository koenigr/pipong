#!/bin/bash

echo "Compiling LCDTest"
g++ LCDTest.cpp Canvas.cpp Print.cpp OLEDDisplay.cpp -lmraa -pthread -std=c++11 -o LCDTest


echo "Run LCDTest"
./LCDTest
