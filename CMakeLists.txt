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
        src/Hardware/Platform.cpp src/Hardware/Platform.h)

SET(MONGOOSE_DIR /usr/local/lib/mos)

add_subdirectory(
        vendor/mcu-libraries
)

include_directories(firmware
        ${MONGOOSE_DIR}/mongoose-os/fw/src
        ${MONGOOSE_DIR}/mongoose-os/fw/include
        ${MONGOOSE_DIR}/mongoose-os/
        ${MONGOOSE_DIR}/mqtt/src
        ${MONGOOSE_DIR}/mqtt/include
        ${MONGOOSE_DIR}/dht/src
        ${MONGOOSE_DIR}/dht/include
        ${MONGOOSE_DIR}/ArduinoJson/src
        deps/wifi/include
        deps/wifi/src
        build/gen/
        vendor/mcu-libraries
)

add_executable(firmware ${SOURCE_FILES})