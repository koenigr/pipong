#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <mraa.h>

class InputManager
{
private:
    static int ct;
    static mraa_gpio_context bt_ct;
    static int getPlayerPos(double accel);
    static void getAccel(mraa_i2c_context i2c, double *data);
    static int decodeS16BE(uint8_t *buf);
public:
    static void gpio_dir(mraa_gpio_context g, mraa_gpio_dir_t dir);
    static _gpio* gpio_init(int pin, mraa_gpio_dir_t dir);

    static void init();
    static bool startButtonPressed();
    static int getPlayerPosition();
};

#endif // INPUTMANAGER_H
