#include "../../gamestate/Ball.h"

#include <iostream>

int main() {
    Ball ball;

    std::cout << "Ball angle: " << ball.getAngle() << std::endl;

    ball.setAngle(1, 10);
    ball.reflectBall(1);
    std::cout << "Ball angle should be: 350 " << ball.getAngle() << std::endl;

    ball.setAngle(1, 45);
    ball.reflectBall(1);
    std::cout << "Ball angle should be: 45 " << ball.getAngle() << std::endl;

    ball.setAngle(1, 70);
    ball.reflectBall(3);
    std::cout << "Ball angle should be: 110 " << ball.getAngle() << std::endl;

    ball.setAngle(1, 90);
    ball.reflectBall(3);
    std::cout << "Ball angle should be: 90 " << ball.getAngle() << std::endl;

    ball.setAngle(1, 110);
    ball.reflectBall(3);
    std::cout << "Ball angle should be: 70 " << ball.getAngle() << std::endl;

    ball.setAngle(1, 135);
    ball.reflectBall(3);
    std::cout << "Ball angle should be: 135 " << ball.getAngle() << std::endl;


    ball.setAngle(1, 170);
    ball.reflectBall(0);
    std::cout << "Ball angle should be: 190 " << ball.getAngle() << std::endl;


    ball.setAngle(1, 180);
    ball.reflectBall(0);
    std::cout << "Ball angle should be: 180 " << ball.getAngle() << std::endl;


    ball.setAngle(1, 200);
    ball.reflectBall(0);
    std::cout << "Ball angle should be: 150 " << ball.getAngle() << std::endl;


    ball.setAngle(1, 225);
    ball.reflectBall(0);
    std::cout << "Ball angle should be: 225 " << ball.getAngle() << std::endl;


    ball.setAngle(1, 240);
    ball.reflectBall(2);
    std::cout << "Ball angle should be: 300 " << ball.getAngle() << std::endl;


    ball.setAngle(1, 270);
    ball.reflectBall(2);
    std::cout << "Ball angle should be: 270 " << ball.getAngle() << std::endl;

    ball.setAngle(1, 300);
    ball.reflectBall(2);
    std::cout << "Ball angle should be: 330 " << ball.getAngle() << std::endl;

    ball.setAngle(1, 315);
    ball.reflectBall(1);
    std::cout << "Ball angle should be: 315 " << ball.getAngle() << std::endl;

    ball.setAngle(1, 350);
    ball.reflectBall(1);
    std::cout << "Ball angle should be: 10 " << ball.getAngle() << std::endl;

    ball.setAngle(1, 360);
    ball.reflectBall(1);
    std::cout << "Ball angle should be: 360 " << ball.getAngle() << std::endl;
}
