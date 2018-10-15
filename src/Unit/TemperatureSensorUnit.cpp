#include <stdint.h>
#include <mgos_dht.h>
#include "mgos.h"
#include "TemperatureSensorUnit.h"
#include <ArduinoJson.h>

TemperatureSensorUnit::TemperatureSensorUnit(int id, int pin) : Unit(id) {

    char topic[20];
    sprintf(topic, "units/%d", id);
    mgos_mqtt_sub(topic, &TemperatureSensorUnit::handler, this);

    this->sensor = mgos_dht_create(pin, DHT22);

    if (this->sensor == NULL) {
        LOG(LL_INFO, ("Error init DHT22"));
    }

    this->register_on_server();

    mgos_set_timer(15000, true, &TemperatureSensorUnit::timer, this);
}

void TemperatureSensorUnit::handler(int msg_len, const char *msg) {

    LOG(LL_INFO, ("Test handler, %.*s", msg_len, msg));

}

void TemperatureSensorUnit::handler(struct mg_connection *c, const char *topic, int topic_len, const char *msg, int msg_len, void *userdata) {

    ((TemperatureSensorUnit*) (userdata))->handler(msg_len, msg);

}

void TemperatureSensorUnit::timer(void *arg) {

    ((TemperatureSensorUnit*) (arg))->updateTemperature();

}

void TemperatureSensorUnit::updateTemperature()
{

    float t = mgos_dht_get_temp(this->sensor);
    float h = mgos_dht_get_humidity(this->sensor);

    LOG(LL_INFO, ("Temperature: %f", t));

    char topic[20];
    sprintf(topic, "units/%d/indicators", this->id);

    char message[100];
    DynamicJsonBuffer json(100);
    JsonObject &root = json.createObject();
    root["temperature"] = t;
    root["humidity"] = h;
    size_t length = root.printTo(message);

    mgos_mqtt_pub(topic, message, length, 1, 0);
}
