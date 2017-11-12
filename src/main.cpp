#include "mgos.h"
#include "Unit/SwitchUnit.h"

enum mgos_app_init_result mgos_app_init(void)
{
    UNUSED auto unit = new SwitchUnit(2);

    return MGOS_APP_INIT_SUCCESS;
}
