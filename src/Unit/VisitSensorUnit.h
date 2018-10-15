#ifndef FIRMWARE_VISITSENSORUNIT_H
#define FIRMWARE_VISITSENSORUNIT_H

#include "Unit.h"

class VisitSensorUnit : public Unit
{

public:

    enum Direction {
        NONE = 0,
        IN = 1,
        OUT
    };

    enum State {
        BEGIN = 0,
        L1 = 1,
        R1 = 2,
        L0 = 3,
        R0 = 4
    };

    int count = 0;

    unsigned long changedAt = 0;
    int resetTime = 1000;
    bool debug = true;

    State state = BEGIN;
    Direction direction = NONE;

    const int leftPin, rightPin, emitterPin;

    VisitSensorUnit(int id, int leftPin, int rightPin, int emitterPin);
    static void sensorLoop(void *arg);

    void intersection(int beam, int value);
    void setState(State state);

    static void interruptionHandler(int pin, void *arg);

    Direction detectedDirection = NONE;

    void sendDirection();
};


#endif //FIRMWARE_VISITSENSORUNIT_H
