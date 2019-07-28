#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <mraa.h>

class InputManager
{
private:
    static int ct;
    static mraa_gpio_context bt_ct;
public:
    static void gpio_dir(mraa_gpio_context g, mraa_gpio_dir_t dir);
    static mraa_pgio_context gpio_init(int pin, mraa_gpio_dir_t dir);

    static void init();
    static bool startButtonPressed();
};

#endif // INPUTMANAGER_H
