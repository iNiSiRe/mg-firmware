#include "Unit.h"
#include "mgos.h"
#include <mgos_mqtt.h>
#include "mgos_wifi.h"
#include "ArduinoJson.h"

void Unit::register_on_server()
{
    if (!registration) {
        return;
    }

    LOG(LL_INFO, ("Register begin"));

    char topic[20];
    sprintf(topic, "units/%d/register", id);

    LOG(LL_INFO, ("Register: %s", topic));

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

    if (mgos_mqtt_pub(topic, message, length, 1, 0)) {
        LOG(LL_INFO, ("Register done: %s", message));
    } else {
        LOG(LL_INFO, ("Register failed"));
    }
}

Unit::Unit(const int id, const bool registration) : id(id), registration(registration)
{

}
