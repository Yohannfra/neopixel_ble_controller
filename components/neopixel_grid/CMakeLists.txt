idf_component_register(
    SRCS
        "neopixel_grid.c"
        "led_strip_rmt_ws2812.c"
        "./grid_storage.c"

    INCLUDE_DIRS
        "include"

    REQUIRES
        nvs_flash
    )
