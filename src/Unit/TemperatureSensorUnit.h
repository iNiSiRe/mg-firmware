#ifndef FIRMWARE_TEMPERATURESENSORUNIT_H
#define FIRMWARE_TEMPERATURESENSORUNIT_H

#include "mgos_mqtt.h"
#include "Unit.h"

class TemperatureSensorUnit : Unit {

private:

    struct mgos_dht * sensor = NULL;

public:
    TemperatureSensorUnit(int id, int pin);
    static void handler(struct mg_connection *c, const char *topic, int topic_len, const char *msg, int msg_len, void *userdata);
    void handler(int msg_len, const char *msg);

    static void timer(void *arg);
    void updateTemperature();
};


#endif //FIRMWARE_TEMPERATURESENSORUNIT_H
