#include <mgos.h>
#include "VisitSensorUnit.h"
#include <mgos_pwm.h>

VisitSensorUnit::VisitSensorUnit(const int id, const int leftPin, const int rightPin, const int emitterPin) :
    emitterPin(emitterPin),
    leftPin(leftPin),
    rightPin(rightPin),
    Unit(id)
{
    register_on_server();

//    mgos_set_timer(1000, 0, VisitSensorUnit::emitterToggle, NULL);
    mgos_set_timer(100, MGOS_TIMER_REPEAT, VisitSensorUnit::sensorLoop, this);

//    mgos_gpio_set_pull(leftPin, MGOS_GPIO_PULL_UP);
//    mgos_gpio_set_pull(rightPin, MGOS_GPIO_PULL_UP);

    mgos_gpio_set_mode(leftPin, MGOS_GPIO_MODE_INPUT);
    mgos_gpio_set_mode(rightPin, MGOS_GPIO_MODE_INPUT);
//    mgos_gpio_set_mode(emitterPin, MGOS_GPIO_MODE_OUTPUT);
//
    mgos_gpio_set_int_handler_isr(leftPin, MGOS_GPIO_INT_EDGE_ANY, VisitSensorUnit::interruptionHandler, this);
    mgos_gpio_set_int_handler_isr(rightPin, MGOS_GPIO_INT_EDGE_ANY, VisitSensorUnit::interruptionHandler, this);

    mgos_gpio_enable_int(leftPin);
    mgos_gpio_enable_int(rightPin);
}

void VisitSensorUnit::emitterToggle(void *arg)
{
    for (;;) {
        mgos_gpio_write(14, 1);
        mgos_usleep(10);
        mgos_gpio_write(14, 0);
        mgos_usleep(16);
    }
//    auto self = static_cast<VisitSensorUnit*>(arg);
    mgos_gpio_toggle(14);

}

void VisitSensorUnit::sensorLoop(void *arg)
{
    auto self = static_cast<VisitSensorUnit*>(arg);

    unsigned long current = (unsigned long) (mgos_uptime() * 1000);

    if (self->state == BEGIN) {
        return;
    }

    if (current - self->changedAt >= self->resetTime) {
        self->state = BEGIN;
        self->direction = NONE;
        self->detectedDirection = NONE;

        LOG(LL_INFO, ("Reset state"));
    }

    if (self->detectedDirection != NONE) {

        if (self->detectedDirection == IN) {
            self->count++;
        } else {
            self->count--;
        }

        LOG(LL_INFO, ("Detected direction -> %d, count=%d", self->detectedDirection, self->count));
    }
}

void VisitSensorUnit::intersection(int beam, int value) {

    State newState;

    if (beam == 1 && value == 1) {
        newState = R1;
    } else if (beam == 1 && value == 0) {
        newState = R0;
    } else if (beam == 2 && value == 1) {
        newState = L1;
    } else if (beam == 2 && value == 0) {
        newState = L0;
    } else {
        newState = BEGIN;
    }

    if (debug) {
        LOG(LL_INFO, ("%d ? %d", this->state, newState));
    }

    if (direction == NONE) {

        switch (newState) {
            case L1:

                if (state == BEGIN) {
                    this->setState(newState);
                    this->direction = IN;
                }

                break;

            case R1:

                if (state == BEGIN) {
                    this->setState(newState);
                    this->direction = OUT;
                }

                break;
        }

    } else if (direction == IN) {

        switch (newState) {
            case R1:

                if (state == L1) {
                    this->setState(newState);
                }

                break;

            case L0:

                if (state == R1) {
                    this->setState(newState);
                }
                break;

            case R0:

                if (state == L0) {
                    this->setState(newState);
                    detectedDirection = IN;
                }
                break;
        }

    } else if (direction == OUT) {

        switch (newState) {
            case L1:

                if (state == R1) {
                    this->setState(newState);
                }

                break;

            case R0:

                if (state == L1) {
                    this->setState(newState);
                }

                break;

            case L0:

                if (state == R0) {
                    this->setState(newState);
                    detectedDirection = OUT;
                }
                break;

        }

    }

}

void VisitSensorUnit::setState(State state) {

    unsigned long current = (unsigned long) (mgos_uptime() * 1000);

    if (debug) {
        LOG(LL_INFO, ("%d -> %d | %d", this->state, state, current - changedAt));
    }

    this->state = state;
    this->changedAt = current;

}

void VisitSensorUnit::interruptionHandler(int pin, void *arg)
{

    auto self = static_cast<VisitSensorUnit*>(arg);

    int value = mgos_gpio_read(pin) ? 0 : 1;

    self->intersection(pin == self->leftPin ? 1 : 2, value);

}
