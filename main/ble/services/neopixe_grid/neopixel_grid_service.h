#ifndef NEOPIXEL_GRID_SERVICE_H
#define NEOPIXEL_GRID_SERVICE_H

#include "host/ble_hs.h"

#include <stdint.h>

#define GATT_GRID_SERVICE_UUID                                                                                         \
    0xd2, 0x70, 0xac, 0xb2, 0xa0, 0xb4, 0x49, 0x78, 0x84, 0x52, 0x77, 0xf7, 0xe5, 0xbb, 0x72, 0x8e

#define GATT_GRID_SERVICE_SEND_CMD_UUID 0xbeb6
#define GATT_GRID_SERVICE_GET_ALL_UUID 0xcad8

extern uint16_t grid_service_handle;

int gatt_svr_chr_access_grid_cmd_send(
    uint16_t conn_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt *ctxt, void *arg);

int gatt_svr_chr_access_grid_get_all(
    uint16_t conn_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt *ctxt, void *arg);

#endif
