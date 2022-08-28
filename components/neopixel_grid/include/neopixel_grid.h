#ifndef NEOPIXEL_GRID_H
#define NEOPIXEL_GRID_H

#include "driver/gpio.h"
#include "led_strip.h"
#include "rgb_color.h"

#define NP_GRID_SIZE 5

typedef struct {
    gpio_num_t pin;
    led_strip_t *stp;
    uint8_t brightness; // 1 - 20
    rgb_color_t grid[NP_GRID_SIZE][NP_GRID_SIZE];
    bool is_on;
} neopixel_grid_t;

#define NP_GRID_DEFAULT                                                                                                \
    {                                                                                                                  \
        .pin = GPIO_NUM_32, .stp = NULL, .brightness = 1, .grid = {{{0, 0, 0}}}, .is_on = true,                        \
    }

esp_err_t np_grid_init(neopixel_grid_t *np);

esp_err_t np_grid_clear(neopixel_grid_t *np);

esp_err_t np_grid_set_brightness(neopixel_grid_t *np, uint8_t new_brightness);

esp_err_t np_grid_set_pixel(neopixel_grid_t *np, uint8_t x, uint8_t y, rgb_color_t color);

esp_err_t np_grid_set_grid_single_color(neopixel_grid_t *np, rgb_color_t color);

esp_err_t np_grid_set_full_grid(neopixel_grid_t *np, rgb_color_t grid[NP_GRID_SIZE][NP_GRID_SIZE]);

esp_err_t np_grid_turn_off(neopixel_grid_t *np);

esp_err_t np_grid_turn_on(neopixel_grid_t *np);

esp_err_t np_grid_refresh(neopixel_grid_t *np);

void np_grid_print_pixels(rgb_color_t pixels[NP_GRID_SIZE][NP_GRID_SIZE]);

#endif
