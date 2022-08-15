#ifndef RGB_COLOR_H
#define RGB_COLOR_H

#include <stdint.h>

typedef struct __attribute__((__packed__)) {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb_color_t;
_Static_assert(sizeof(rgb_color_t) == 3, "Invalid struct size");

#endif
