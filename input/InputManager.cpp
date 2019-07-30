#include "InputManager.h"
#include "../mraa_libs/OLEDDisplay.h"
#include <cstring>
#include <mraa.h>
#include <iostream>

using namespace GFX;

int InputManager::ct;
mraa_gpio_context InputManager::bt_ct;

#define ADDR_MPU            0x68
#define MPU_ACCEL_OUT       0x3B

double min;
double max;

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

int16_t InputManager::decodeS16BE(uint8_t *buf) {
    return (buf[0] << 8) | buf[1];
}

int InputManager::getPlayerPos(double accel) {
  return 63 + 7*(int)(accel*10);
}

void InputManager::getAccel(mraa_i2c_context i2c, double *data) {
    uint8_t buf[2];
    memset(buf, 0, sizeof(buf));
    mraa_i2c_read_bytes_data(i2c, MPU_ACCEL_OUT, buf, 2);
    double f = 2.0 / 32768.0;
        std::cout << "f: " << f << std::endl;
        data[0] = decodeS16BE(buf + 0) * f;
        std::cout << "acceleration inside: " << data[0] << std::endl;
}

int InputManager::getPlayerPosition() {
    double accel[3];

    std::cout << "min " << min << " max " << max << std::endl;

    mraa_i2c_context i2c = mraa_i2c_init(0);
    mraa_i2c_address(i2c, ADDR_MPU);
    getAccel(i2c, accel);
    if (accel[0] > max) max = accel[0];
    if (accel[0] < min) min = accel[0];
    int player_pos;
    player_pos = getPlayerPos(accel[0]);
    std::cout << "player position: " << player_pos << std::endl;
    return player_pos;
}
