#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "my_ble.h"
#include "neopixel_grid.h"
#include "nvs_flash.h"

static const char *TAG = "MAIN";

static neopixel_grid_t np1 = {
    .grid_size = 5,
    .pin = GPIO_NUM_32,
};

void app_main()
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    np_grid_init(&np1);

    ESP_LOGI(TAG, "Starting neopixel ble controller");

    my_ble_init();

    np_grid_demo(&np1);

    while (1) {
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}
