/*
 * GameState.cpp
 *
 *  Created on: 29.06.2019
 *      Author: koenigr
 */

#include "GameState.h"
#include "Ball.h"
#include "Player.h"
#include <string>
#include "../Parameters.h"

#include <stdio.h>
#include <iostream>
#include <sstream>

GameState::~GameState() {
    //std::cout << "!!!!!!!!!!!!!!!    GameState destructor called\n";
}

void GameState::init(int player_no) {

    std::cout << "\nInitializing Gamestate\n";

    player_self = player_no;
    player_arr[0].init(0, player_self);
    player_arr[1].init(1, player_self);
    player_arr[2].init(2, player_self);
    player_arr[3].init(3, player_self);

    ball.setAngle(player_self, 26.4);

    std::cout << "player self: " << player_self << "\n";
    std::cout << "frame number: " << frame_no << "\n";
    std::cout << "ball: " << ball.toString() << "\n";
    std::cout <<  player_arr[0].toString() << "\n";
    std::cout <<  player_arr[1].toString() << "\n";
    std::cout <<  player_arr[2].toString() << "\n";
    std::cout <<  player_arr[3].toString() << "\n";

    std::cout << "Gamestate Initialization completed\n\n";
}

// A player knows only his own point in the main loop
int GameState::decrPoint() {
    return player_arr[player_self].decrPoints();
}

Player GameState::getSelf() const {
    return player_arr[player_self];
}

Player GameState::getPlayer(int i) const {
    return player_arr[i];
}

Ball GameState::getBall() const {
    return ball;
}

unsigned int GameState::getFrameNo() const {
    return frame_no;
}

unsigned int GameState::incrFrameNo() {
    frame_no += 1;
    return frame_no;
}

int GameState::getPlayerNo() const {
    return player_self;
}

int GameState::getRound() const {
    return round;
}

int GameState::incrRound() {
    return round;
}

std::string GameState::toString() const {
    std::stringstream x;
    x << "FrameNo: " << getFrameNo() << "\n";
    x << ball.toString() << std::endl;
    x << player_arr[0].toString() << std::endl;
    x << player_arr[1].toString() << std::endl;
    x << player_arr[2].toString() << std::endl;
    x << player_arr[3].toString() << std::endl;
    std::string s = x.str();
    return s;
}

void GameState::updateBall() {
    checkForPaddleCollision();
    checkForScoringZoneCollision();
    ball.updateBall();
}

void GameState::checkForPaddleCollision() {
    if(ball.getPosY() - BALL_WIDTH <= 1) ball.reflectBall(0);
    else if(ball.getPosY() + BALL_WIDTH >= 126) ball.reflectBall(1);
    else if(ball.getPosX() - BALL_WIDTH <= 1) ball.reflectBall(2);
    else if(ball.getPosX() + BALL_WIDTH >= 126) ball.reflectBall(3);
}

void GameState::checkForScoringZoneCollision() {
    // TODO: move it to state manager
 // ResetBall
}

void GameState::newRound(const int seed) {
    // TODO
    incrRound();
    ball.resetBall(seed);
    ball.incrVelocity();
}

void GameState::setPlayerActive(const bool isActive, const int player_no) {
    player_arr[player_no].setPlayerActive(isActive);
}
