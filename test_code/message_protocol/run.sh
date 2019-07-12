#!/bin/bash

g++ messageTest.cpp MessageProtocol.cpp Request.cpp Response.cpp GamestateMsg.cpp ../GameState/GameState.cpp -o MessageTest -std=c++11
