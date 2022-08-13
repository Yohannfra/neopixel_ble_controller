#include "neopixel_grid.h"

#include "driver/rmt.h"
#include "esp_log.h"

static const char *TAG = "NEOPIXEL_GRID";

esp_err_t np_grid_init(neopixel_grid_t *np)
{
    rmt_config_t config = RMT_DEFAULT_CONFIG_TX(np->pin, RMT_CHANNEL_0);
    config.clk_div = 2; // set counter clock to 40MHz

    ESP_ERROR_CHECK(rmt_config(&config));
    ESP_ERROR_CHECK(rmt_driver_install(config.channel, 0, 0));

    led_strip_config_t strip_config = LED_STRIP_DEFAULT_CONFIG(np->pin, (led_strip_dev_t)config.channel);
    strip_config.max_leds = np->grid_size * np->grid_size;
    np->stp = led_strip_new_rmt_ws2812(&strip_config);
    if (!np->stp) {
        ESP_LOGE(TAG, "install WS2812 driver failed");
    }

    np_grid_clear(np);

    return ESP_OK;
}

esp_err_t np_grid_clear(neopixel_grid_t *np)
{
    return np->stp->clear(np->stp, 100);
}

esp_err_t np_grid_set_pixel(neopixel_grid_t *np, uint8_t x, uint8_t y, uint8_t red, uint8_t green, uint8_t blue)
{
    esp_err_t ret = ESP_OK;

    uint32_t idx = (y == 0) ? x : (x == 0) ? y * np->grid_size : x + (y * np->grid_size);

    if (y % 2) {
        idx -= x;
        idx += (np->grid_size - 1) - x;
    }

    ESP_LOGI(TAG, "Setting led index: x:%d y:%d %d", x, y, idx);
    ret |= np->stp->set_pixel(np->stp, idx, red, green, blue);
    ret |= np->stp->refresh(np->stp, 100);

    return ret;
}

void np_grid_demo(neopixel_grid_t *np)
{
    int x = 0;
    int y = 0;

    while (1) {
        np_grid_clear(np);
        np_grid_set_pixel(np, x, y, 127, 0, 0);
        x++;
        if (x == 5) {
            y++;
            x = 0;
            if (y == 5) {
                y = 0;
            }
        }
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}
