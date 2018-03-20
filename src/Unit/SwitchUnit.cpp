#include "mgos.h"
#include "SwitchUnit.h"

SwitchUnit::SwitchUnit(const int id, const int pin) : Unit(id), pin(pin)
{
    char topic[20];

    sprintf(topic, "units/%d", id);

    mgos_mqtt_sub(topic, &SwitchUnit::handler, this);
    mgos_gpio_set_mode(pin, MGOS_GPIO_MODE_OUTPUT);

    register_on_server();
}

void SwitchUnit::handler(UNUSED struct mg_connection *c, UNUSED const char *topic, UNUSED int topic_len, const char *msg,  UNUSED int msg_len, void *userdata)
{
    ((SwitchUnit*) (userdata))->handler(msg_len, msg);
}

void SwitchUnit::handler(int msg_len, const char * msg)
{
    LOG(LL_INFO, ("Test handler, %.*s", msg_len, msg));

    bool enabled;

    json_scanf(msg, msg_len, "{enabled: %B}", &enabled);

    mgos_gpio_write(pin, enabled);

    LOG(LL_INFO, ("Test parser: %d", enabled));
}


