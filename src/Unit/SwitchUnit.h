#ifndef FIRMWARE_SWITCHUNIT_H
#define FIRMWARE_SWITCHUNIT_H

#include "mgos_mqtt.h"
#include "../define.h"

class SwitchUnit {

public:
    SwitchUnit(int id);

    void handler(int msg_len, const char *msg);
    static void handler(struct mg_connection *c, const char *topic, int topic_len, const char *msg, int msg_len, void *userdata);
};


#endif //FIRMWARE_SWITCHUNIT_H
