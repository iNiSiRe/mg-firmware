#include "mgos.h"
#include "SwitchUnit.h"

SwitchUnit::SwitchUnit(UNUSED const int id)
{
    char topic[20];

    sprintf(topic, "units/%d", id);

    mgos_mqtt_sub(topic, &SwitchUnit::handler, this);
}

void SwitchUnit::handler(UNUSED struct mg_connection *c, UNUSED const char *topic, UNUSED int topic_len, const char *msg,  UNUSED int msg_len, void *userdata)
{
    ((SwitchUnit*) (userdata))->handler(msg_len, msg);
}

void SwitchUnit::handler(int msg_len, const char * msg)
{
    LOG(LL_INFO, ("Test handler, %.*s", msg_len, msg));
}
