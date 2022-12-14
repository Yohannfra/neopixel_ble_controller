#include "neopixel_grid_service.h"

#include "grid_storage.h"
#include "host/ble_uuid.h"
#include "neopixel_grid.h"
#include "neopixel_grid_service_commands.h"
#include "services/gap/ble_svc_gap.h"
#include "services/gatt/ble_svc_gatt.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

static const char *TAG = "NEOPIXEL_GRID_SERVICE";

uint16_t grid_service_handle;
uint16_t button_service_handle;

extern neopixel_grid_t np_grid;

int gatt_svr_chr_access_grid_cmd_send(
    uint16_t conn_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt *ctxt, void *arg)
{
    ESP_LOGI(TAG, "INTO grid cmd send callback, received a payload of %d bytes: ", ctxt->om->om_len);
    ESP_LOG_BUFFER_HEXDUMP(TAG, ctxt->om->om_data, ctxt->om->om_len, ESP_LOG_INFO);

    if (ctxt->op != BLE_GATT_ACCESS_OP_WRITE_CHR || ctxt->om->om_len < 1) {
        ESP_LOGE(TAG, "INVALID OPERATION");
        return 0;
    }

    const uint8_t command = ctxt->om->om_data[0];
    const uint8_t *payload = ctxt->om->om_data + 1;
    const int size = ctxt->om->om_len - 1;

    switch (command) {
        case GRID_CLEAR:
            ESP_LOGI(TAG, "GRID_CLEAR");
            np_grid_clear(&np_grid);
            grid_storage_save_pixels(np_grid.grid);
            break;

        case GRID_SET_PIXEL: {
            ESP_LOGI(TAG, "GRID_SET_PIXEL");
            if (size != sizeof(grid_cmd_set_pixel_payload_t)) {
                ESP_LOGE(TAG, "INVALID COMMAND SIZE");
                return 0;
            }
            grid_cmd_set_pixel_payload_t *pl = (grid_cmd_set_pixel_payload_t *)payload;
            np_grid_set_pixel(&np_grid, pl->x, pl->y, (rgb_color_t){pl->color.r, pl->color.g, pl->color.b});
            np_grid_refresh(&np_grid);
            grid_storage_save_pixels(np_grid.grid);
        } break;

        case GRID_SET_ALL_SINGLE_COLOR: {
            ESP_LOGI(TAG, "GRID_SET_ALL_SINGLE_COLOR");
            if (size != sizeof(grid_cmd_set_all_single_color_payload_t)) {
                ESP_LOGE(TAG, "INVALID COMMAND SIZE");
                return 0;
            }
            grid_cmd_set_all_single_color_payload_t *pl = (grid_cmd_set_all_single_color_payload_t *)payload;
            np_grid_set_grid_single_color(&np_grid, (rgb_color_t){pl->color.r, pl->color.g, pl->color.b});
            grid_storage_save_pixels(np_grid.grid);
        } break;

        case GRID_SET_ALL_PIXELS: {
            ESP_LOGI(TAG, "GRID_SET_ALL_PIXELS");
            if (size != sizeof(grid_cmd_set_all_pixels_payload_t)) {
                ESP_LOGE(TAG, "INVALID COMMAND SIZE");
                return 0;
            }
            grid_cmd_set_all_pixels_payload_t *pl = (grid_cmd_set_all_pixels_payload_t *)payload;
            np_grid_set_full_grid(&np_grid, pl->colors);
            grid_storage_save_pixels(np_grid.grid);
        } break;

        case GRID_SET_BRIGHTNESS: {
            ESP_LOGI(TAG, "GRID_SET_BRIGHTNESS");
            if (size != sizeof(grid_cmd_set_brightness_payload_t)) {
                ESP_LOGE(TAG, "INVALID COMMAND SIZE");
                return 0;
            }
            grid_cmd_set_brightness_payload_t *pl = (grid_cmd_set_brightness_payload_t *)payload;
            np_grid_set_brightness(&np_grid, pl->brightness);
            grid_storage_save_brightness(np_grid.brightness);
        } break;

        case GRID_TURN_ON:
            ESP_LOGI(TAG, "GRID_TURN_ON");
            np_grid_turn_on(&np_grid);
            break;

        case GRID_TURN_OFF:
            ESP_LOGI(TAG, "GRID_TURN_OFF");
            np_grid_turn_off(&np_grid);
            break;
    }
    return 0;
}

int gatt_svr_chr_access_grid_get_all(
    uint16_t conn_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt *ctxt, void *arg)
{
    ESP_LOGI(TAG, "Into grid get all callback");

    return os_mbuf_append(ctxt->om, (uint8_t *)np_grid.grid, sizeof(np_grid.grid));
}

static uint8_t button_service_counter = 0;

void notify_button_service(int16_t conn_handle)
{
    struct os_mbuf *om;

    button_service_counter++;

    if (conn_handle > -1) {
        om = ble_hs_mbuf_from_flat(&button_service_counter, sizeof(button_service_counter));
        ESP_LOGI(TAG, "Notifying conn=%d", conn_handle);
        int rc = ble_gattc_notify_custom((uint16_t)conn_handle, button_service_handle, om);
        if (rc != 0) {
            ESP_LOGE(TAG, "error notifying; rc=%d", rc);
            return;
        }
    }
}

int gatt_svr_chr_access_button(
    uint16_t conn_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt *ctxt, void *arg)
{
    ESP_LOGI(TAG, "Into button service read callback");

    return os_mbuf_append(ctxt->om, &button_service_counter, sizeof(button_service_counter));
}
