//
// Created by inisire on 20.09.18.
//

#include <mgos.h>
#include "Platform.h"

namespace hardware {

    void Platform::setPinMode(int pin, PinMode mode) {
        mgos_gpio_set_mode(pin, MGOS_GPIO_MODE_INPUT);
    }

    int Platform::analogRead(int pin) {
        return mgos_gpio_read(pin);
    }

    unsigned int Platform::millis() {

        return (unsigned int) mgos_uptime() * 1000;
    }

    void Platform::print(const char *string) {

    }

    void Platform::println(const char *string) {

    }

}