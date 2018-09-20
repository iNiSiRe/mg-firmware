//
// Created by inisire on 22.06.18.
//

#include "VisitSensorUnit.h"

VisitSensorUnit::VisitSensorUnit(const int id, const int leftPin, const int rightPin) : Unit(id), sensor(leftPin, rightPin) {

}
