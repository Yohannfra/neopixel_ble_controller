#ifndef NEOPIXEL_GRID_H
#define NEOPIXEL_GRID_H

#include "driver/gpio.h"
#include "led_strip.h"

typedef struct {
    uint32_t grid_size;
    gpio_num_t pin;
    led_strip_t *stp;
    uint8_t brightness; // 1 - 20
} neopixel_grid_t;

esp_err_t np_grid_init(neopixel_grid_t *np);

esp_err_t np_grid_clear(neopixel_grid_t *np);

esp_err_t np_grid_set_brightness(neopixel_grid_t *np, uint8_t new_brightness);

esp_err_t np_grid_set_pixel(neopixel_grid_t *np, uint8_t x, uint8_t y, uint8_t red, uint8_t green, uint8_t blue);

void np_grid_demo(neopixel_grid_t *np);

#endif
