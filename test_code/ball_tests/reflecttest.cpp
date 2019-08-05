#include "../../gamestate/Ball.h"

#include <iostream>

int main() {
    Ball ball;

    std::cout << "Ball angle: " << ball.getAngle() << std::endl;

    ball.setAngle(1, 10);
    ball.reflectBall(1);

    ball.setAngle(1, 170);
    ball.reflectBall(3);

    ball.setAngle(1, 170);
    ball.reflectBall(0);

    ball.setAngle(1, 190);
    ball.reflectBall(2);


}
