cmake_minimum_required(VERSION 3.5)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-fdiagnostics-color=always)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

project(neopixel_ble_controller)
