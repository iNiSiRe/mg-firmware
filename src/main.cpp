#include "mgos.h"
#include "Unit/SwitchUnit.h"
#include "Unit/TemperatureSensorUnit.h"

void init(void *arg)
{
    const char* type = mgos_sys_config_get_app_unit_type();
    const int unit_id = mgos_sys_config_get_app_unit_id();

    if (strcmp(type, "TemperatureSensorUnit") == 0) {
        const int pin = mgos_sys_config_get_app_temperature_unit_pin();
        auto unit = new TemperatureSensorUnit(unit_id, pin);
    } else if (strcmp(type, "SwitchUnit") == 0) {
        const int pin = mgos_sys_config_get_app_switch_unit_pin();
        auto unit = new SwitchUnit(unit_id, pin);
    } else {
        LOG(LL_INFO, ("No unit started!"));
    }
}

void ping(void *arg)
{
    mgos_mqtt_pub("ping", "ping", 4, 1, false);
}

enum mgos_app_init_result mgos_app_init(void)
{
    mgos_set_timer(20000, 0, init, NULL);
    mgos_set_timer(30000, true, ping, NULL);

    return MGOS_APP_INIT_SUCCESS;
}
