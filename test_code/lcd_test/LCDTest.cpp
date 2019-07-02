#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <chrono>

#include "OLEDDisplay.h"

using namespace GFX;

void testCircle() {
	OLEDDisplay disp(128, 128);

	disp.setBgColor(COLOR_BLACK);
	disp.setDrawColor(COLOR_WHITE);
	disp.clearScreen();
	disp.enable();

	disp.fillCircle(60, 60, 10);

	disp.drawLine(1, 20, 1, 100);
	disp.drawLine(20, 1, 100, 1);
	disp.drawLine(120, 20, 120, 100);
	disp.drawLine(20, 120, 100, 120);


	disp.flush();
	std::this_thread::sleep_for(std::chrono::seconds(60));
}

int main(void) {
	printf("Starting\n");
	testCircle();
	return 0;
}
