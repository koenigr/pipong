#include "Display.h"
#include "../gamestate/GameState.h"
#include <iostream>
#include <cstring>
#include <mraa.h>

#include "../mraa_libs/OLEDDisplay.h"

using namespace GFX;

OLEDDisplay disp(128, 128);

void Display::init() {
    disp.setBgColor(COLOR_BLACK);
    disp.setDrawColor(COLOR_WHITE);
    disp.clearScreen();
    disp.enable();
}

void Display::flush() {

    disp.flush();

}

void Display::draw(char* buf) {

    disp.clearScreen();
    disp.setCursor(0,0);
    //std::cout << "Display::draw buffer: " << buf << std::endl;
    disp.print(buf);

}

void Display::drawHello() {

    disp.flush();
    std::string display_text = "\n\n\nWelcome to PiPong :)\n Please wait until\nall player are active\n"
                       "then press the center\nbutton to start\nsynchronization.";
    char buf[BUFSIZE];
    memset(buf, 0, BUFSIZE);
    sprintf(buf, display_text);
    //std::cout << "Check buffer content: " << buf << std::endl;
    draw(buf);
}

void Display::drawWaitForPeers(const GameState gs) {
    disp.flush();
    std::stringstream s = "Waiting for peers\n";
    s << "Player 0: " << gs.getPlayer(0).isActive() << \n;
    s << "Player 1: " << gs.getPlayer(1).isActive() << \n;
    s << "Player 2: " << gs.getPlayer(2).isActive() << \n;
    s << "Player 3: " << gs.getPlayer(3).isActive() << \n;
    std::string display_text = s.str();
    char buf[BUFSIZE];
    memset(buf, 0, BUFSIZE);
    sprintf(buf, 0, display_text);
    draw(buf);
}

void Display::drawPlayer(const GameState gs) {
    std::cout << "Player_self: " << gs.getPlayerNo() << "\n";
    std::cout << "TODO: Player rotate into wrong direction\n";
    for (int i = 0; i < 4; i++) {
        Player player = gs.getPlayer(i);
        std::cout << "Player " << i
                << ": (" << player.getLeftEndX() << "," << player.getLeftEndY() << "),("
                << player.getRightEndX() << "," << player.getRightEndY() << ")\n";
    }
}

void Display::drawBall(const GameState gs) {
    std::cout << "Ball " << gs.getBall().toString() << std::endl;
}

void Display::drawPoints(const GameState gs) {

    for (int i = 0; i < 4; i++) {

        std::cout << "Player " << i << ": ";
        if (gs.getPlayer(i).isActive()) {
            std::cout << gs.getPlayer(i).getPoints();
        } else {
            std::cout << "x";
        }
        std::cout << std::endl;

    }
}

void Display::drawGameState(const GameState gs) {
    drawPlayer(gs);
    drawBall(gs);
}
