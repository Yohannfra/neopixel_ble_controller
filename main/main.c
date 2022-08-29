#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "grid_storage.h"
#include "my_ble.h"
#include "neopixel_grid.h"
#include "nvs_flash.h"

static const char *TAG = "MAIN";

neopixel_grid_t np_grid = NP_GRID_DEFAULT;

void app_main()
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    np_grid_init(&np_grid);

    ESP_LOGI(TAG, "Starting neopixel ble controller");

    // blink grid
    np_grid_set_grid_single_color(&np_grid, (rgb_color_t){0, 0xff, 0});
    vTaskDelay(500 / portTICK_PERIOD_MS);
    np_grid_clear(&np_grid);

    // restore brightness
    if (grid_storage_has_brightness()) {
        uint8_t brightness = 0;
        ESP_ERROR_CHECK(grid_storage_load_brightness(&brightness));
        np_grid_set_brightness(&np_grid, brightness);
    }

    // restore pixels
    if (grid_storage_has_pixels()) {
        ESP_LOGI(TAG, "A grid was found in nvs, loading it");
        rgb_color_t saved_grid[NP_GRID_SIZE][NP_GRID_SIZE];
        ESP_ERROR_CHECK(grid_storage_load_pixels(saved_grid));
        np_grid_set_full_grid(&np_grid, saved_grid);
    }

    my_ble_init();

    while (1) {
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}
