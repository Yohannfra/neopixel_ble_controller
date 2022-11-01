#include "host/ble_hs.h"
#include "host/ble_uuid.h"
#include "services/gap/ble_svc_gap.h"
#include "services/gatt/ble_svc_gatt.h"
#include "services/neopixe_grid/neopixel_grid_service.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

static const char *TAG = "GATT_SVR";

static const struct ble_gatt_svc_def gatt_svr_svcs[] = {
    {
        .type = BLE_GATT_SVC_TYPE_PRIMARY,
        .uuid = BLE_UUID128_DECLARE(GATT_GRID_SERVICE_UUID),
        .characteristics =
            (struct ble_gatt_chr_def[]){
                {
                    /* Characteristic: Grid send command */
                    .uuid = BLE_UUID16_DECLARE(GATT_GRID_SERVICE_SEND_CMD_UUID),
                    .access_cb = gatt_svr_chr_access_grid_cmd_send,
                    .val_handle = &grid_service_handle,
                    .flags = BLE_GATT_CHR_F_WRITE_NO_RSP | BLE_GATT_CHR_F_WRITE,
                },
                {
                    /* Characteristic: Grid get all */
                    .uuid = BLE_UUID16_DECLARE(GATT_GRID_SERVICE_GET_ALL_UUID),
                    .access_cb = gatt_svr_chr_access_grid_get_all,
                    .flags = BLE_GATT_CHR_F_READ,
                },
                {
                    /* Characteristic: Notifications from button */
                    .uuid = BLE_UUID16_DECLARE(GATT_GRID_SERVICE_BUTTON_UUID),
                    .access_cb = gatt_svr_chr_access_button,
                    .val_handle = &button_service_handle,
                    .flags = BLE_GATT_CHR_F_READ | BLE_GATT_CHR_F_NOTIFY,
                },
                {
                    0, /* No more characteristics in this service */
                },
            },
    },
    {
        0, /* No more services */
    },
};

int gatt_svr_init(void)
{
    int rc;

    ble_svc_gap_init();
    ble_svc_gatt_init();

    rc = ble_gatts_count_cfg(gatt_svr_svcs);
    if (rc != 0) {
        return rc;
    }

    rc = ble_gatts_add_svcs(gatt_svr_svcs);
    if (rc != 0) {
        return rc;
    }

    return 0;
}
