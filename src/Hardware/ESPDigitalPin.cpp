//
// Created by inisire on 22.06.18.
//

#include "ESPDigitalPin.h"

ESPDigitalPin::ESPDigitalPin(const int pin) : DigitalPin(pin) {

}

void ESPDigitalPin::write(int value)
{
    mgos_gpio_write(id, value == 1);
}

void ESPDigitalPin::setMode(PinMode mode)
{
    mgos_gpio_mode gpio_mode = mode == PinMode::INPUT
                               ? mgos_gpio_mode::MGOS_GPIO_MODE_INPUT
                               : mgos_gpio_mode::MGOS_GPIO_MODE_OUTPUT;

    mgos_gpio_set_mode(id, gpio_mode);
}

int ESPDigitalPin::read()
{
    return mgos_gpio_read(id);
}
