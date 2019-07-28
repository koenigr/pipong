#include "InputManager.h"
#include "../display/OLEDDisplay.h"
#include <cstring>
#include <mraa.h>


void InputManager::gpio_dir(mraa_gpio_context g, mraa_gpio_dir_t dir) {

  while(1) {

    mraa_result_t r = mraa_gpio_dir(g, dir);
    if (r == MRAA_SUCCESS) break;
    usleep(100 * 1000);
  }

}

mraa_gpio_context InputManager::gpio_init(int pin, mraa_gpio_dir_t dir) {

    mraa_gpio_context c = mraa_gpio_init(pin);
    gpio_dir(c, dir);
    return c;

}

void InputManager::init() {

    bt_ct = gpio_init(38, MRAA_GPIO_IN);

}

bool InputManager::startButtonPressed() {

    ct = !mraa_gpio_read(bt_ct);
    return ct;
}
