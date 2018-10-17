#include "mgos.h"
#include "Unit/SwitchUnit.h"
#include "Unit/TemperatureSensorUnit.h"
#include "Unit/VisitSensorUnit.h"
#include <common/mg_str.h>
#include "ArduinoJson.h"
#include "mgos_wifi.h"

int module_id = 0;

void registration()
{
    LOG(LL_INFO, ("Register -> begin"));

    char topic[20];
    sprintf(topic, "modules/%d/register", module_id);

    LOG(LL_INFO, ("Register -> topic=%s", topic));

    // Get IP
    char ip[16];
    mgos_net_ip_info ip_info;
    mgos_net_get_ip_info(MGOS_NET_IF_TYPE_WIFI, MGOS_NET_IF_WIFI_STA, &ip_info);
    mgos_net_ip_to_str(&ip_info.ip, ip);

    // Prepare JSON message
    char message[100];
    DynamicJsonBuffer json(100);
    JsonObject &root = json.createObject();
    root["ip"] = ip;
    root["device_id"] = mgos_sys_config_get_device_id();
    size_t length = root.printTo(message);

    if (mgos_mqtt_pub(topic, message, length, 2, false)) {
        LOG(LL_INFO, ("Register -> done: %s", message));
    } else {
        LOG(LL_INFO, ("Register -> failed"));
    }
}

void init(void *arg)
{
    LOG(LL_INFO, ("Init -> Start"));

    const char* type = mgos_sys_config_get_app_unit_type();
    const int unit_id = mgos_sys_config_get_app_unit_id();

    module_id = mgos_sys_config_get_app_module_id();
    if (module_id) {
        registration();
    } else {
        LOG(LL_INFO, ("Init -> No module_id setting. Stop."));
        return;
    };

    if (mg_strcmp(mg_mk_str(type), mg_mk_str("TemperatureSensorUnit")) == 0) {
        const int pin = mgos_sys_config_get_app_temperature_unit_pin();
        auto unit = new TemperatureSensorUnit(unit_id, pin);
    } else if (mg_strcmp(mg_mk_str(type), mg_mk_str("SwitchUnit")) == 0) {
        const int pin = mgos_sys_config_get_app_switch_unit_pin();
        auto unit = new SwitchUnit(unit_id, pin);
    } else if (mg_strcmp(mg_mk_str(type), mg_mk_str("VisitSensorUnit")) == 0) {
        const int leftPin = mgos_sys_config_get_app_visit_unit_left_pin();
        const int rightPin = mgos_sys_config_get_app_visit_unit_right_pin();
        const int emitterPin = mgos_sys_config_get_app_visit_unit_emitter_pin();
        auto unit = new VisitSensorUnit(unit_id, leftPin, rightPin, emitterPin);
    } else {
        LOG(LL_INFO, ("Init -> No unit started!"));
    }
}

void ping(void *arg)
{
    char topic[20];
    sprintf(topic, "modules/%d/ping", module_id);

    mgos_mqtt_pub(topic, "ping", 4, 1, false);
}

enum mgos_app_init_result mgos_app_init(void)
{
    LOG(LL_INFO, ("Init"));

    mgos_set_timer(20000, 0, init, NULL);
    mgos_set_timer(30000, true, ping, NULL);

    return MGOS_APP_INIT_SUCCESS;
}