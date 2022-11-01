#ifndef MY_BLE_H
#define MY_BLE_H

#include "esp_err.h"

#include <stdbool.h>

esp_err_t my_ble_init();

uint16_t my_ble_get_conn_handle();

bool my_ble_is_connected();

#endif
