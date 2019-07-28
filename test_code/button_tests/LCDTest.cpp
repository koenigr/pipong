#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "math.h"

#include <chrono>

#include "OLEDDisplay.h"

using namespace GFX;

OLEDDisplay disp(128, 128);
int X_MIN = 0;
int X_MAX = 127;
int Y_MIN = 0;
int Y_MAX = 127;
int L_WIDTH = 50;
int B_RAD = 10;

void init() {

	disp.setBgColor(COLOR_BLACK);
	disp.setDrawColor(COLOR_WHITE);
	disp.clearScreen();
	disp.enable();

}



void draw() {
	disp.flush();
//	std::this_thread::sleep_for(std::chrono::seconds(1));
}

struct ball_pos {

	int posX = 0;
	int posY = 0;
	int velX = 4;
	int velY = 6;
} b_pos;

//struct ball_pos b_pos;

void compute_ball_pos() {

	if ( (b_pos.posX < X_MIN + B_RAD && b_pos.velX < 0) || (b_pos.posX > X_MAX - B_RAD && b_pos.velX > 0) ) {
		b_pos.velX = -b_pos.velX;
	}

	if ( (b_pos.posY < Y_MIN + B_RAD && b_pos.velY < 0) || (b_pos.posY > Y_MAX - B_RAD && b_pos.velY > 0)) {
		b_pos.velY = -b_pos.velY;
	}

	b_pos.posX += b_pos.velX;
	b_pos.posY += b_pos.velY;

}


void ball(int posX, int posY) {

        disp.fillCircle(posX, posY, B_RAD);
}

void line_p1(int pos) {

        disp.drawLine(X_MIN, pos - L_WIDTH / 2, X_MIN, pos + L_WIDTH / 2);

}

void line_p2(int pos) {

        disp.drawLine(pos - L_WIDTH / 2, Y_MIN, pos + L_WIDTH / 2, Y_MIN);

}

void line_p3(int pos) {

        disp.drawLine(X_MAX, pos - L_WIDTH / 2, X_MAX, pos + L_WIDTH / 2);

}

void line_p4(int pos) {

        disp.drawLine(pos - L_WIDTH / 2, Y_MAX, pos + L_WIDTH / 2, Y_MAX);

}


int main(void) {
	init();
	printf("Starting\n");

	int i = 0;
    while(true) {

	int mv = sin(i)*20;
	compute_ball_pos();

	disp.clearScreen();
	ball(b_pos.posX, b_pos.posY);
	line_p1(60 + mv);
	line_p2(60 + mv);
	line_p3(60 + mv);
	line_p4(60 + mv);
	draw();
	usleep(100000);
	i += 1;
    }

	return 0;
}
