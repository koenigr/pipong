clear

g++ udp.cpp ../../gamestate/GameState.cpp ../../gamestate/Ball.cpp ../../gamestate/Player.cpp --std=c++11 -o SendState.cpp

if [ $? -eq 0 ]; then
	./SendState.cpp
fi
