//
// Created by inisire on 20.09.18.
//

#ifndef FIRMWARE_PLATFORM_H
#define FIRMWARE_PLATFORM_H

#include <Platform.h>
#include <mgos_gpio.h>

namespace hardware {

    class Platform : public inisire_mcu_libraries::Platform {

    public:

        enum PinState {
            HIGH = 1,
            LOW = 0
        };

        enum PinMode {
            INPUT = MGOS_GPIO_MODE_INPUT,
            OUTPUT = MGOS_GPIO_MODE_OUTPUT
        };

        void setPinMode(int pin, PinMode mode);
        int analogRead(int pin) override;
        

        unsigned int millis() override;

        void print(const char *string) override;

        void println(const char *string) override;

    };

}

namespace inisire_mcu_libraries {

    Platform * platform = new hardware::Platform();

}

#endif //FIRMWARE_PLATFORM_H
