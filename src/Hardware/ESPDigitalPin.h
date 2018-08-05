#ifndef FIRMWARE_ESPDIGITALPIN_H
#define FIRMWARE_ESPDIGITALPIN_H

#include <Hardware/DigitalPin.h>
#include <mgos.h>

class ESPDigitalPin : DigitalPin {

public:
    ESPDigitalPin(const int id) : DigitalPin(id) {};

    int read() override;
    void write(int value) override;
    void setMode(PinMode mode) override;

};


#endif //FIRMWARE_ESPDIGITALPIN_H
