# esp-idf-template

This is a template application to start an ESP-IDF project.

## Features

- Boilerplate blinking code that uses a custom led component
- Full-featured Makefile to use **idf.py** faster
- sdkconfig.default file to configure ESP-IDF
- test directory with basic **Unity** firmware that tests the led component
- The CMakeLists.txt generate a **compile_commands.json** by default and add **-fdiagnostics-color=always** to print all build errors with colors

## Requirements

- [Install ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/get-started/index.html)
- [Install ESP_ADF](https://docs.espressif.com/projects/esp-adf/en/latest/get-started/index.html) (optional)

## Get started

1. Clone this repository
2. Configure ESP-IDF for your needs with **make config** or by editing the **sdkconfig.default**
3. Build with **make**
4. Flash with **make flash**

## Add ESP-ADF

Just uncomment this line in the CMakeLists.txt, same in the **tests** directory
```cmake
# include($ENV{ADF_PATH}/CMakeLists.txt)
```

## Run the test firmware

1. Go to the **tests** directory
2. Build with **make**
3. Flash and watch tests logs with **make flash_and_monitor**
