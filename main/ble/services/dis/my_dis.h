#ifndef MY_DIS_H
#define MY_DIS_H

#include "host/ble_gatt.h"

#include <stdint.h>

#define GATT_DEVICE_INFO_UUID       0x180A
#define GATT_MANUFACTURER_NAME_UUID 0x2A29
#define GATT_MODEL_NUMBER_UUID      0x2A24

int gatt_svr_chr_access_device_info(
    uint16_t conn_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt *ctxt, void *arg);

#endif
