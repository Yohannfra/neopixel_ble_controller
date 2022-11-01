#ifndef HON_BUTTON_H
#define HON_BUTTON_H

#include "driver/gpio.h"

#include <stdbool.h>

typedef enum
{
    UP,
    DOWN,
    NONE
} my_gpio_pull_direction_e;

typedef struct {
    gpio_num_t pin;
    my_gpio_pull_direction_e direction;
} my_button_handle_t;

esp_err_t my_button_init(my_button_handle_t *handle);

bool my_button_is_pressed(my_button_handle_t *handle);

#endif  // HON_BUTTON_H
