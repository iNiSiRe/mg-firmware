cmake_minimum_required(VERSION 3.8)
project(firmware)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/main.cpp
        src/Unit/SwitchUnit.cpp src/Unit/SwitchUnit.h
        src/define.h
)

SET(MONGOOSE_DIR /usr/local/lib/mos)

include_directories(firmware
        ${MONGOOSE_DIR}/mongoose-os/fw/src
        ${MONGOOSE_DIR}/mongoose-os/
        ${MONGOOSE_DIR}/mqtt/src
        ${MONGOOSE_DIR}/mqtt/include
)

add_executable(firmware ${SOURCE_FILES})