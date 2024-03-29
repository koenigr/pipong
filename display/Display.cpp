#include "Display.h"
#include "../gamestate/GameState.h"
#include "../gamestate/Ball.h"
#include <iostream>
#include <cstring>
#include <mraa.h>
#include <sstream>

#include "../mraa_libs/OLEDDisplay.h"

using namespace GFX;

OLEDDisplay disp(128, 128);

void Display::init() {
    disp.setBgColor(COLOR_BLACK);
    disp.setDrawColor(COLOR_WHITE);
    disp.clearScreen();
    disp.enable();
}

void Display::clear() {
    disp.clearScreen();
    disp.setCursor(0,0); // ??
}

void Display::flush() {
    disp.flush();
}

void Display::drawHello() {

    clear();
    std::string display_text = "\n\n\nWelcome to PiPong :)\n Please wait until\nall player are active\n"
                       "then press the center\nbutton to start\nsynchronization.";
    char buf[BUFSIZE];
    memset(buf, 0, BUFSIZE);
    sprintf(buf, display_text.c_str());
    //std::cout << "Check buffer content: " << buf << std::endl;
    disp.print(buf);
    flush();
}

void Display::drawWaitForPeers(const GameState gs) {
    clear();
    std::stringstream s;
    s << "Waiting for peers\n";
    for (int i = 0; i <= 3; i++) {
        s << "Player " << i << ": ";
        if (gs.getPlayer(i).isActive()) {s << "active";}
        else {s << "-";}
        s << std::endl;
    }
    std::string display_text = s.str();
    char buf[BUFSIZE];
    memset(buf, 0, BUFSIZE);
    sprintf(buf, display_text.c_str());
    disp.print(buf);
    flush();
}

void Display::drawPlayer(const GameState gs) {
    for (int i = 0; i < 4; i++) {
        Player player = gs.getPlayer(i);
        // std::cout << ">>>>>>>>>>> " << player.toString() << std::endl;
        disp.drawLine(player.getLeftEndX(), player.getLeftEndY(), player.getRightEndX(), player.getRightEndY());
    }
}

void Display::drawBall(const GameState gs) {
    disp.fillCircle(gs.getBall().getPosX(), gs.getBall().getPosY(), BALL_WIDTH);
}

void Display::drawPoints(const GameState gs) {

    clear();
    std::stringstream s;
    s << "\n\n\nPress\nup button\nto restart\ndn button\nto finish\n";
    for (int i = 0; i < 4; i++) {

        s << "Player " << i << ": ";
        if (gs.getPlayer(i).isActive()) {
            s << gs.getPlayer(i).getPoints() << std::endl;
        } else {
            s << "-" << std::endl;
        }

    }
    std::string display_text = s.str();

    char buf[BUFSIZE];
    memset(buf, 0, BUFSIZE);
    sprintf(buf, display_text.c_str());

    disp.print(buf);
    flush();
}

void Display::drawGameState(const GameState gs) {
    clear();
    drawPlayer(gs);
    drawBall(gs);
    flush();
}

void Display::drawGameState(bool draw_ball, const GameState gs) {
    clear();
    drawPlayer(gs);
    if (draw_ball) drawBall(gs);
    flush();
}
