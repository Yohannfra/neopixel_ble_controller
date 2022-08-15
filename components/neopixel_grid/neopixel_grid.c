#include "neopixel_grid.h"

#include "driver/rmt.h"
#include "esp_log.h"

#include <string.h>

static const char *TAG = "NEOPIXEL_GRID";

static rgb_color_t grid[NP_GRID_SIZE * NP_GRID_SIZE];
static bool is_on = true;

esp_err_t np_grid_init(neopixel_grid_t *np)
{
    rmt_config_t config = RMT_DEFAULT_CONFIG_TX(np->pin, RMT_CHANNEL_0);
    config.clk_div = 2; // set counter clock to 40MHz

    ESP_ERROR_CHECK(rmt_config(&config));
    ESP_ERROR_CHECK(rmt_driver_install(config.channel, 0, 0));

    led_strip_config_t strip_config = LED_STRIP_DEFAULT_CONFIG(np->pin, (led_strip_dev_t)config.channel);
    strip_config.max_leds = NP_GRID_SIZE * NP_GRID_SIZE;
    np->stp = led_strip_new_rmt_ws2812(&strip_config);
    if (!np->stp) {
        ESP_LOGE(TAG, "install WS2812 driver failed");
    }

    np_grid_clear(np);

    return ESP_OK;
}

esp_err_t np_grid_set_brightness(neopixel_grid_t *np, uint8_t new_brightness)
{
    if (new_brightness >= 1 && new_brightness <= 20) {
        np->brightness = new_brightness;
        ESP_LOGI(TAG, "Setting brightness: %d", new_brightness);
        np_grid_turn_on(np); // apply brightness
        return ESP_OK;
    }
    ESP_LOGE(TAG, "Invalid brightness '%d', it must between 1 and 20", new_brightness);
    return ESP_ERR_INVALID_ARG;
}

esp_err_t np_grid_clear(neopixel_grid_t *np)
{
    ESP_LOGI(TAG, "Clearing grid");
    memset(grid, 0, sizeof(grid));
    return np->stp->clear(np->stp, 100);
}

esp_err_t np_grid_set_pixel(neopixel_grid_t *np, uint8_t x, uint8_t y, rgb_color_t color)
{
    esp_err_t ret = ESP_OK;

    if (!is_on) {
        ESP_LOGE(TAG, "Grid is not on, call np_grid_turn_on()");
        return ESP_FAIL;
    }

    uint32_t idx = (y == 0) ? x : (x == 0) ? y * NP_GRID_SIZE : x + (y * NP_GRID_SIZE);

    if (y % 2) {
        idx -= x;
        idx += (NP_GRID_SIZE - 1) - x;
    }

    ESP_LOGI(TAG, "Setting led at x:%d y:%d with color r:%d g:%d b:%d", x, y, color.r, color.g, color.b);
    ret |= np->stp->set_pixel(np->stp, idx, color.r / (21 - np->brightness), color.g / (21 - np->brightness),
        color.b / (21 - np->brightness));
    ret |= np->stp->refresh(np->stp, 100);
    grid[idx] = color;

    return ret;
}

esp_err_t np_grid_set_grid_single_color(neopixel_grid_t *np, rgb_color_t color)
{
    esp_err_t ret = ESP_OK;

    if (!is_on) {
        ESP_LOGE(TAG, "Grid is not on, call np_grid_turn_on()");
        return ESP_FAIL;
    }

    ESP_LOGI(TAG, "Setting grid with color r:%d g:%d b:%d", color.r, color.g, color.b);
    for (int i = 0; i < NP_GRID_SIZE * NP_GRID_SIZE; i++) {
        grid[i] = color;
    }
    np_grid_turn_on(np);

    return ret;
}

esp_err_t np_grid_turn_off(neopixel_grid_t *np)
{
    esp_err_t ret = ESP_OK;

    ESP_LOGI(TAG, "Turning off grid");
    ret = np->stp->clear(np->stp, 100);
    is_on = false;

    return ret;
}

esp_err_t np_grid_turn_on(neopixel_grid_t *np)
{
    esp_err_t ret = ESP_OK;

    ESP_LOGI(TAG, "Turning on grid");
    is_on = true;
    for (int i = 0; i < NP_GRID_SIZE * NP_GRID_SIZE; i++) {
        ret |= np->stp->set_pixel(np->stp, i, grid[i].r / (21 - np->brightness), grid[i].g / (21 - np->brightness),
            grid[i].b / (21 - np->brightness));
    }
    ret |= np->stp->refresh(np->stp, 100);

    return ret;
}
