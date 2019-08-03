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
#include "../states/StateManager.h"

#include <stdio.h>
#include <iostream>
#include <sstream>

GameState::~GameState() {
    //std::cout << "!!!!!!!!!!!!!!!    GameState destructor called\n";
}

void GameState::init(int player_no) {

    std::cout << "\nGameState::init() start...\n";

    player_self = player_no;
    player_arr[0].init(0, player_self);
    player_arr[1].init(1, player_self);
    player_arr[2].init(2, player_self);
    player_arr[3].init(3, player_self);
    player_arr[player_self].setPlayerActive(true);

    ball.setAngle(player_self, 26.4);

    std::cout << "GameState::init() " << toString() << std::endl;

    std::cout << "Gamestate::init() end\n\n";
}

unsigned int GameState::getCountdown() {
    return countdown;
}

void GameState::setCountdown(const unsigned int cd) {
    countdown = cd;
}

void GameState::decrCountdown() {
    if (countdown > 0) {
        countdown -= 1;
    }
}

// A player knows only his own point in the main loop?????
int GameState::decrPoints() {
    return player_arr[player_self].decrPoints();
}

int GameState::setPoints(int player_no, int points) {
    player_arr[player_no].setPoints(points);
    return player_arr[player_no].getPoints();
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
    return getSelf().getFrame();
}

// increment is only needed for own player
unsigned int GameState::incrFrameNo() {

    player_arr[player_self].incrFrame();
    return getSelf().getFrame();
}

unsigned int GameState::setFrame(int const player_no, unsigned int const new_frame) {

    player_arr[player_no].setFrame(new_frame);
    return player_arr[player_no].getFrame();
}

void GameState::resetAllFrames() {
    for (int i = 0; i < 4; i++) {
        player_arr[i].setFrame(0);
    }
}

int GameState::getPlayerNo() const {
    return player_self;
}

int GameState::setPosition(int player_no, int new_position) {
    player_arr[player_no].setPosition(new_position);
    return player_arr[player_no].getPosition();
}
int GameState::getPosition(int player_no) const {
    return player_arr[player_no].getPosition();
}

int GameState::getRound() const {
    return round;
}

int GameState::incrRound() {
    return round;
}

std::string GameState::toString() const {
    std::stringstream x;
    x << "PlayerSelf: " << player_self << std::endl;
    x << "FrameNo: " << getFrameNo() << std::endl;
    x << ball.toString() << std::endl;
    x << player_arr[0].toString() << std::endl;
    x << player_arr[1].toString() << std::endl;
    x << player_arr[2].toString() << std::endl;
    x << player_arr[3].toString() << std::endl;
    std::string s = x.str();
    return s;
}

void GameState::checkForReflection() {

    std::cout << "GameState::checkForReflection() start...\n";


    if(ball.getPosY() - BALL_WIDTH <= 1) {
        if (last_reflection_wall != 0) ball.reflectBall(0);
        last_reflection_wall = 0;
    }
    else if(ball.getPosY() + BALL_WIDTH >= 126) {
        if (last_reflection_wall != 1) {
            ball.reflectBall(1);
            std::cout << "GameState::checkForReflection() COLLISION ALARM <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n";
            checkForScoringZoneCollision();
        }
        last_reflection_wall = 1;
    }
    else if(ball.getPosX() - BALL_WIDTH <= 1) {
        if (last_reflection_wall != 2) ball.reflectBall(2);
        last_reflection_wall = 2;
    }
    else if(ball.getPosX() + BALL_WIDTH >= 126) {
        if (last_reflection_wall != 3) ball.reflectBall(3);
        last_reflection_wall = 3;
    }

    std::cout << "GameState::checkForReflection() end\n";
}


void GameState::checkForScoringZoneCollision() {
    bool Ycond = ball.getPosY() + BALL_WIDTH >= 126;
    bool XcondR = ball.getPosX() - BALL_WIDTH > getSelf().getRightEndX();
    bool xcondL = ball.getPosX() + BALL_WIDTH < getSelf().getLeftEndX();
    if (Ycond && ( XcondR || xcondL)) {
        // TODO
        std::cout << ">>>>>>>>>>>>>>>>>>> COLLISION\n";
        StateManager::setState(COLLISION_STATE);
        // ball.resetBall(2); // TODO seed
    }
    // TODO
}

void GameState::updateBall() {

    std::cout << "GameState::updateBall() before reflection" << getBall().toString() << std::endl;
    checkForReflection();
    std::cout << "GameState::updateBall() between reflection and update" << getBall().toString() << std::endl;
    ball.updateBall();
    std::cout << "GameState::updateBall() after update" << getBall().toString() << std::endl;
}

void GameState::newRound(const int seed) {
    // TODO paddle width. decrPoints bei Player nur, wenn er verloren hat
    incrRound();
    ball.resetBall(seed);
    ball.incrVelocity();
    player_arr[player_self].decrPoints();
}

void GameState::setPlayerActive(const bool isActive, const int player_no) {
    player_arr[player_no].setPlayerActive(isActive);
}
