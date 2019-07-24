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

#include <stdio.h>
#include <iostream>

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
    std::string gs_str = "FrameNo: " + std::to_string(getFrameNo());
    return gs_str;
}

void GameState::updateBall() {
    // TODO
    // if ...
    ball.updateBall();
    // if checkPaddleCollision: reflectBall
    // if checkScoringZone: ResetBall
}

bool GameState::checkForPaddleCollision() {
    return true;
}

bool GameState::checkForScoringZoneCollision() {
    return false;
}

void GameState::newRound() {
    // TODO
    // incr ROund
    // new angle ...
    ball.resetBall();
    ball.incrVelocity();
}

