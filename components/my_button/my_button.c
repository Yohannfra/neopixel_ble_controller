#include "my_button.h"

esp_err_t my_button_init(my_button_handle_t *handle)
{
    gpio_config_t conf = {
        .pin_bit_mask = (1ULL << handle->pin),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = (handle->direction == UP) ? GPIO_PULLUP_ENABLE : GPIO_PULLUP_DISABLE,
        .pull_down_en = (handle->direction == DOWN) ? GPIO_PULLDOWN_ENABLE : GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };

    return gpio_config(&conf);
}

bool my_button_is_pressed(my_button_handle_t *handle)
{
    if (handle->direction == UP) {
        return !gpio_get_level(handle->pin);
    } else {
        return gpio_get_level(handle->pin);
    }
}
