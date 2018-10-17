#include "Unit.h"
#include "mgos.h"
#include <mgos_mqtt.h>

void Unit::register_on_server()
{

}

Unit::Unit(const int id, const bool registration) : id(id), registration(registration)
{

}
