#ifndef GRID_STORAGE_H
#define GRID_STORAGE_H

#include "neopixel_grid.h"

#include <stdbool.h>

bool grid_storage_has_pixels(void);
esp_err_t grid_storage_load_pixels(rgb_color_t grid[NP_GRID_SIZE][NP_GRID_SIZE]);
esp_err_t grid_storage_save_pixels(rgb_color_t grid[NP_GRID_SIZE][NP_GRID_SIZE]);

bool grid_storage_has_brightness(void);
esp_err_t grid_storage_load_brightness(uint8_t *brightness);
esp_err_t grid_storage_save_brightness(uint8_t brightness);

#endif
