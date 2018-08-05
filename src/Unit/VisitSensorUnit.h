//
// Created by inisire on 22.06.18.
//

#ifndef FIRMWARE_VISITSENSORUNIT_H
#define FIRMWARE_VISITSENSORUNIT_H

#include "Unit.h"
#include <VisitSensor/VisitSensor.h>

class VisitSensorUnit : Unit
{

private:
    VisitSensor sensor;
    
public:
    VisitSensorUnit(int id, int leftPin, int rightPin);

};


#endif //FIRMWARE_VISITSENSORUNIT_H
