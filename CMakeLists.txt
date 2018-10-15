cmake_minimum_required(VERSION 3.6)
project(firmware)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/main.cpp
        src/Unit/SwitchUnit.cpp src/Unit/SwitchUnit.h
        src/define.h
        src/Unit/TemperatureSensorUnit.cpp src/Unit/TemperatureSensorUnit.h
        src/Unit/Unit.cpp src/Unit/Unit.h
        src/Unit/VisitSensorUnit.cpp src/Unit/VisitSensorUnit.h
)

SET(MONGOOSE_DIR vendor)

include_directories(firmware
        deps/modules/mongoose-os/fw/src
        deps/modules/mongoose-os/fw/include
        deps/modules/mongoose-os/
        ${MONGOOSE_DIR}/mqtt/src
        ${MONGOOSE_DIR}/mqtt/include
        ${MONGOOSE_DIR}/dht/src
        ${MONGOOSE_DIR}/dht/include
        ${MONGOOSE_DIR}/ArduinoJson/src
        deps/wifi/include
        deps/wifi/src
        deps/pwm/include
        deps/pwm/src
        build/gen/
        deps/bt-common/src
        deps/bt-common/include
)

add_executable(firmware ${SOURCE_FILES})