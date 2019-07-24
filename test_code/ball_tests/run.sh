clear

g++ balltest.cpp ../../gamestate/Ball.cpp ../../gamestate/Player.cpp ../../gamestate/GameState.cpp --std=c++11 -o BallTest

./BallTest $1
