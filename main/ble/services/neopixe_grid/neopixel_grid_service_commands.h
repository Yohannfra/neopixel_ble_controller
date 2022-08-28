#ifndef NEOPIXEL_GRID_SERVICE_COMMANDS_H
#define NEOPIXEL_GRID_SERVICE_COMMANDS_H

#include "neopixel_grid.h"

#include <stdint.h>

typedef enum {
    GRID_CLEAR = 0x01,
    GRID_SET_PIXEL = 0x02,
    GRID_SET_ALL_SINGLE_COLOR = 0x03,
    GRID_SET_ALL_PIXELS = 0x04,
    GRID_SET_BRIGHTNESS = 0x05,
    GRID_TURN_ON = 0x06,
    GRID_TURN_OFF = 0x07,
} grid_cmd_e;

typedef struct __attribute__((__packed__)) {
    uint8_t x;
    uint8_t y;
    rgb_color_t color;
} grid_cmd_set_pixel_payload_t;
_Static_assert(sizeof(grid_cmd_set_pixel_payload_t) == 5, "Invalid struct size");

typedef struct __attribute__((__packed__)) {
    rgb_color_t color;
} grid_cmd_set_all_single_color_payload_t;
_Static_assert(sizeof(grid_cmd_set_all_single_color_payload_t) == 3, "Invalid struct size");

typedef struct __attribute__((__packed__)) {
    rgb_color_t colors[NP_GRID_SIZE][NP_GRID_SIZE];
} grid_cmd_set_all_pixels_payload_t;
_Static_assert(sizeof(grid_cmd_set_all_pixels_payload_t) == (NP_GRID_SIZE * NP_GRID_SIZE) * sizeof(rgb_color_t),
    "Invalid struct size");

typedef struct __attribute__((__packed__)) {
    uint8_t brightness;
} grid_cmd_set_brightness_payload_t;
_Static_assert(sizeof(grid_cmd_set_brightness_payload_t) == 1, "Invalid struct size");

#endif
