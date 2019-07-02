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
int X_MAX = 125;
int Y_MIN = 0;
int Y_MAX = 125;
int L_WIDTH = 50;

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

void ball() {

        disp.fillCircle(60, 60, 10);
}

void line_p1(int pos) {

        disp.drawLine(X_MIN, pos - L_WIDTH / 2, X_MIN, pos + L_WIDTH / 2);

}

void line_p2(int pos) {

        disp.drawLine(pos - L_WIDTH, Y_MIN, pos + L_WIDTH, Y_MIN);

}

void line_p3(int pos) {

        disp.drawLine(X_MAX, pos - L_WIDTH, X_MAX, pos + L_WIDTH);

}

void line_p4(int pos) {

        disp.drawLine(pos - L_WIDTH, Y_MAX, pos + L_WIDTH, Y_MAX);

}


int main(void) {
	init();
	printf("Starting\n");

	int i = 0;
    while(true) {

	int mv = sin(i)*20;

	disp.clearScreen();
	ball();
	line_p1(60 + mv);
	line_p2(60 + mv);
	line_p3(60 + mv);
	line_p4(60 + mv);
	draw();
	usleep(1000);
	i += 1;
    }

	return 0;
}
